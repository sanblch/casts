#include "qt-core.h"
#include "qt-mainwindow.h"

using namespace core::internal;

namespace core {

static ICore *m_instance = nullptr;
static MainWindow *m_mainwindow = nullptr;

ICore *ICore::instance() { return m_instance; }

QMainWindow *ICore::mainWindow() {
  return m_mainwindow;
}

ICore::ICore(MainWindow *mainwindow) {
  m_instance = this;
  m_mainwindow = mainwindow;
}

ICore::~ICore() {
  m_instance = nullptr;
  m_mainwindow = nullptr;
}

} // namespace core
