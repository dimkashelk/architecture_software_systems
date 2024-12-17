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
  order_manager_(stack_size_),
  warehouse_manager_(count_robots_, order_manager_),
  clients_(count_clients_)
{
  ui->setupUi(this);
  initUI();
  init_model();
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
  if (count_clients_ > 0)
  {
    --count_clients_;
    clients_.pop_back();
    set_clients_count();
  }
}
void MainWindow::increase_clients_count()
{
  clients_.push_back(std::make_shared < dimkashelk::Client >(count_clients_, order_manager_));
  clients_.rbegin()->get()->start();
  ++count_clients_;
  set_clients_count();
}
void MainWindow::decrease_clients_delay()
{
  if (client_delay_ > 0)
  {
    --client_delay_;
    update_clients_delay();
  }
}
void MainWindow::increase_clients_delay()
{
  ++client_delay_;
  update_clients_delay();
}
void MainWindow::update_clients_delay() const
{
  for (size_t i = 0; i < clients_.size(); ++i)
  {
    clients_[i]->set_delay(client_delay_);
  }
  set_clients_delay();
}
void MainWindow::decrease_robots()
{
  --count_robots_;
  warehouse_manager_.pop_back_robot();
  set_robots_count();
}
void MainWindow::increase_robots()
{
  ++count_robots_;
  warehouse_manager_.add_robot();
  set_robots_count();
}
void MainWindow::decrease_stack()
{
  if (stack_size_ > 0)
  {
    --stack_size_;
    order_manager_.decrement_stack();
    set_stack_size();
  }
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
void MainWindow::initUI() const
{
  set_clients_count();
  set_clients_delay();
  set_robots_count();
  set_stack_size();
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
void MainWindow::init_model()
{
  for (size_t i = 0; i < count_clients_; i++)
  {
    clients_.push_back(std::make_shared < dimkashelk::Client >(i, order_manager_));
  }
}
