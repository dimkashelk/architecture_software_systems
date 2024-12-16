#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent):
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  work_now_(false)
{
  ui->setupUi(this);
  connect(ui->button_start_stop, &QPushButton::clicked, this, &MainWindow::start_stop);
}
MainWindow::~MainWindow()
{
  delete ui;
}
void MainWindow::start_stop()
{
  // TODO: реализовать метод
}
