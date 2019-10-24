#include "iplugin.hpp"
#include "shared_library.hpp"

#include <QApplication>
#include <QHBoxLayout>
#include <QWidget>

#include <csignal>
#include <execinfo.h>
#include <iostream>
#include <unistd.h>

static std::map<std::string, std::tuple<std::shared_ptr<micro::shared_library>,
                                        std::shared_ptr<micro::iplugin>>>
    plugins;

static std::shared_ptr<micro::iplugin> get_plugin(const std::string &nm) {
  if (auto it = plugins.find(nm); it != std::end(plugins)) {
    return std::get<1>(it->second);
  }
  std::shared_ptr<micro::iplugin> ret = nullptr;
  if (auto dll = std::make_shared<micro::shared_library>(nm);
      dll && dll->is_loaded()) {
    if (auto loader = dll->get<import_plugin_cb_t>("import_plugin"); loader) {
      if ((ret = loader())) {
        plugins[nm] = {dll, ret};
      }
    }
  }
  return ret;
}

static void signal_handler(int s) {
  for (auto it = std::begin(plugins); it != std::end(plugins); ++it) {
    std::get<0>((*it).second).reset();
    std::get<1>((*it).second).reset();
    std::cout << "Reset" << std::endl;
  }
  plugins.clear();
  std::exit(s);
}

static void signal_handler_tr(int s) {
  void *array[10];

  // get void*'s for all entries on the stack
  auto size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", s);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  std::exit(s);
}

int main(int argc, char* argv[]) {
  std::signal(SIGABRT, &signal_handler);
  std::signal(SIGTERM, &signal_handler);
  std::signal(SIGKILL, &signal_handler);
  std::signal(SIGQUIT, &signal_handler);
  std::signal(SIGINT, &signal_handler);
  std::signal(SIGSEGV, &signal_handler_tr);

  QApplication app(argc, argv);

  QWidget widget;
  widget.show();

  QHBoxLayout* l = new QHBoxLayout();

  auto plugin = get_plugin("wplugin1");
  auto wgt = dynamic_cast<micro::widget_plugin *>(plugin.get())->widget();
  wgt->setParent(&widget);
  l->addWidget(wgt);
  widget.setLayout(l);

  app.exec();
}
