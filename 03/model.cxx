#include "qt-core.h"
#include "qt-mainwindow.h"

#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#pragma pop_macro("slots")

#include <iostream>

namespace py = pybind11;

class CorePlugin;

static CorePlugin *m_instance = nullptr;

class CorePlugin {
  std::unique_ptr<core::internal::MainWindow> m_mainWindow;

public:
  CorePlugin() {
    m_mainWindow = std::make_unique<core::internal::MainWindow>();
    m_instance = this;
  }
};

PYBIND11_MODULE(pyplotter, m) {
  m.def("init", []() { new CorePlugin(); });
  m.def("fin", [m_instance]() { delete m_instance; });
  m.def(
      "mainWindow", []() {
                      py::object type = py::module::import("PySide2.QtWidgets").attr("QMainWindow");
                      // std::cout << core::ICore::mainWindow() << std::endl;
                      py::object obj = py::module::import("shiboken2").attr("wrapInstance")(reinterpret_cast<size_t>(core::ICore::mainWindow()), type);
                      // py::object obj = py::cast(core::ICore::mainWindow());
                      return obj;
                    },
      py::return_value_policy::take_ownership);
}
