#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent):
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  work_now_(false)
{
  ui->setupUi(this);
  connect(ui->button_start_stop, &QPushButton::clicked, this, &MainWindow::start_stop);
  connect(ui->button_clients_count_decrease, &QPushButton::clicked, this, &MainWindow::decrease_clients);
  connect(ui->button_clients_count_increase, &QPushButton::clicked, this, &MainWindow::increase_clients);
  connect(ui->button_clients_delay_decrease, &QPushButton::clicked, this, &MainWindow::decrease_clients_delay);
  connect(ui->button_clients_delay_increase, &QPushButton::clicked, this, &MainWindow::increase_clients_delay);
  connect(ui->button_robots_decrease, &QPushButton::clicked, this, &MainWindow::decrease_robots);
  connect(ui->button_robots_increase, &QPushButton::clicked, this, &MainWindow::increase_robots);
  connect(ui->button_stack_decrease, &QPushButton::clicked, this, &MainWindow::decrease_stack);
  connect(ui->button_stack_increase, &QPushButton::clicked, this, &MainWindow::increase_stack);
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
void MainWindow::decrease_stack()
{
  // TODO: реализовать метод
}
void MainWindow::increase_stack()
{
  // TODO: реализовать метод
}
