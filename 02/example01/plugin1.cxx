#include "iplugin.hpp"
#include <iostream>

class plugin1 final : public micro::math_plugin {
public:
  plugin1(int v, const std::string &nm)
    : micro::math_plugin(v, nm) {}

  ~plugin1() override {
    std::cout << "~plugin1();" << std::endl;
  }

  int add(int a, int b) override {
    return a + b + 5;
  }
};

// extern function, that declared in "iplugin.hpp", for export the plugin from dll
std::unique_ptr<micro::iplugin> import_plugin() {
  auto a = std::make_unique<plugin1>(micro::make_version(1,0), "plugin1");
  std::cout << "First: " << a.get()->add(2, 3) << std::endl;
  return a;
}
