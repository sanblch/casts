#include "qt-classic-widget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

QtClassicWidget::QtClassicWidget(QWidget *parent) : QWidget(parent) {
  m_button = new QPushButton("Button1", this);
  m_edit = new QLineEdit(this);

  auto vlayout = new QVBoxLayout;
  vlayout->addWidget(m_button);
  vlayout->addWidget(m_edit);

  setLayout(vlayout);
}
