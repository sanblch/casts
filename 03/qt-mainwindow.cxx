#include "qt-mainwindow.h"
#include "qt-core.h"

namespace core {
namespace internal {

MainWindow::MainWindow() : m_coreImpl(new ICore(this)) {}

MainWindow::~MainWindow() {
  delete m_coreImpl;
  m_coreImpl = nullptr;
}

} // namespace internal
} // namespace core
