#include "iplugin.hpp"
#include <QLineEdit>

class wplugin1 : public micro::widget_plugin {
public:
  wplugin1(int v, const std::string &nm) : micro::widget_plugin(v, nm) {}

  ~wplugin1() override {}

  QWidget* widget() override {
    return new QLineEdit();
  }
};

// extern function, that declared in "iplugin.hpp", for export the plugin from dll
std::unique_ptr<micro::iplugin> import_plugin() {
  return std::make_unique<wplugin1>(micro::make_version(1,0), "wplugin1");
}
