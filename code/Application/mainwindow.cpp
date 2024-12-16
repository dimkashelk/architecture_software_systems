#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent):
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  work_now_(false)
{
  ui->setupUi(this);
  connect(ui->button_start_stop, &QPushButton::clicked, this, &MainWindow::start_stop);
  connect(ui->button_clients_decrease, &QPushButton::clicked, this, &MainWindow::decrease_clients);
  connect(ui->button_clients_increase, &QPushButton::clicked, this, &MainWindow::increase_clients);
  connect(ui->button_robots_decrease, &QPushButton::clicked, this, &MainWindow::decrease_robots);
  connect(ui->button_robots_increase, &QPushButton::clicked, this, &MainWindow::increase_robots);
}
MainWindow::~MainWindow()
{
  delete ui;
}
void MainWindow::start_stop()
{
  // TODO: реализовать метод
}
void MainWindow::decrease_clients()
{
  // TODO: реализовать метод
}
void MainWindow::increase_clients()
{
  // TODO: реализовать метод
}
void MainWindow::decrease_robots()
{
  // TODO: реализовать метод
}
void MainWindow::increase_robots()
{
  // TODO: реализовать метод
}
