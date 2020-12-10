#include "qt-classic-widget.h"

#include <QApplication>
#include <QGridLayout>
#include <QMainWindow>

#pragma push_macro("slots")
#undef slots
#include <pybind11/embed.h>
#pragma pop_macro("slots")

#include <iostream>

namespace py = pybind11;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  py::scoped_interpreter guard{};

  auto mainWindow = new QWidget;

  auto widget1 = new QtClassicWidget;

  auto layout = new QVBoxLayout;

  py::object obj = py::module::import("barfoo").attr("BarFoo")();
  py::tuple tupl = py::module::import("shiboken2").attr("getCppPointer")(obj);
  layout->addWidget(reinterpret_cast<QWidget*>(tupl[0].cast<size_t>()));

  layout->addWidget(widget1);

  mainWindow->setLayout(layout);
  mainWindow->show();

  return app.exec();
}
