#include "mainwindow.h"

#include <qguiapplication.h>

#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent):
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  work_now_(false),
  stack_size_(5),
  count_clients_(2),
  count_robots_(3),
  client_delay_(5),
  clients_(count_clients_)
{
  ui->setupUi(this);
  connect(ui->button_start_stop, &QPushButton::clicked, this, &MainWindow::start_stop);
  connect(ui->button_clients_count_decrease, &QPushButton::clicked, this, &MainWindow::decrease_clients_count);
  connect(ui->button_clients_count_increase, &QPushButton::clicked, this, &MainWindow::increase_clients_count);
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
void MainWindow::decrease_clients_count()
{
  // TODO: реализовать метод
}
void MainWindow::increase_clients_count()
{
  // TODO: реализовать метод
}
void MainWindow::decrease_clients_delay()
{
  // TODO: реализовать метод
}
void MainWindow::increase_clients_delay()
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
void MainWindow::set_clients_count() const
{
  ui->label_clients_count->setText(QString::number(count_clients_));
}
void MainWindow::set_clients_delay() const
{
  ui->label_clients_delay->setText(QString::number(client_delay_));
}
void MainWindow::set_robots_count() const
{
  ui->label_robots->setText(QString::number(count_robots_));
}
void MainWindow::set_stack_size() const
{
  ui->label_stack->setText(QString::number(stack_size_));
}
