#include "iplugin.hpp"
#include "shared_library.hpp"

#include <chrono>
#include <csignal>
#include <execinfo.h>
#include <iostream>
#include <thread>
#include <unistd.h>

class Manager {
public:
  std::map<std::string, std::tuple<std::shared_ptr<micro::shared_library>,
                                   std::shared_ptr<micro::iplugin>>>
      plugins;

  std::unique_ptr<micro::iplugin> get_plugin(const std::string &nm) {
    if (auto it = plugins.find(nm); it != std::end(plugins)) {
      return nullptr;
    }
    std::unique_ptr<micro::iplugin> ret = nullptr;
    if (auto dll = std::make_shared<micro::shared_library>(nm);
        dll && dll->is_loaded()) {
      if (auto loader = dll->get<import_plugin_cb_t>("import_plugin"); loader) {
        if ((ret = loader())) {
          std::cout << "Second: "
                    << dynamic_cast<micro::math_plugin *>(ret.get())->add(2, 3)
                    << std::endl;
          plugins[nm] = {dll, nullptr};
        }
      }
    }
    return ret;
  }

  void unload_plugins() {
    for (auto &plugin : plugins)
      if (std::get<0>(plugin.second)->is_loaded())
        std::get<0>(plugin.second)->unload();
  }
};

static void signal_handler(int s) {
  void *array[10];

  // get void*'s for all entries on the stack
  auto size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", s);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  std::exit(s);
}

int main() {
  std::signal(SIGABRT, &signal_handler);
  std::signal(SIGTERM, &signal_handler);
  std::signal(SIGKILL, &signal_handler);
  std::signal(SIGQUIT, &signal_handler);
  std::signal(SIGINT, &signal_handler);
  std::signal(SIGSEGV, &signal_handler);

  auto manager = std::make_unique<Manager>();

  auto plugin = manager->get_plugin("plugin1");
  std::cout << "Third: "
            << dynamic_cast<micro::math_plugin *>(plugin.get())->add(2, 3)
            << std::endl;
}
