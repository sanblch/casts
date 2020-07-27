#pragma once

#include <QWidget>

class QLineEdit;
class QPushButton;

class QtClassicWidget : public QWidget {
  Q_OBJECT
  QLineEdit* m_edit;
  QPushButton* m_button;
public:
  QtClassicWidget(QWidget* parent = nullptr);
};
