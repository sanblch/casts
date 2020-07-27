#pragma once

#include "qt-core.h"
#include <QMainWindow>

namespace core {
namespace internal {

class MainWindow : public QMainWindow {
  Q_OBJECT

  ICore *m_coreImpl = nullptr;

public:
  MainWindow();
  ~MainWindow() override;
};

} // namespace internal
} // namespace core
