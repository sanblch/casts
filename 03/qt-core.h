#pragma once

#include <QMainWindow>

namespace core {
namespace internal { class MainWindow; }

class ICore : public QObject {
  Q_OBJECT

  friend class internal::MainWindow;

  explicit ICore(internal::MainWindow *mw);
  ~ICore() override;

public:
  static ICore *instance();
  static QMainWindow *mainWindow();
};
} // namespace core
