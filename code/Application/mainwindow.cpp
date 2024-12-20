#include "mainwindow.h"
#include <qguiapplication.h>
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent):
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  work_now_(false),
  run_threads_(true),
  stack_size_(10),
  count_clients_(3),
  count_robots_(5),
  client_delay_(2),
  order_manager_(stack_size_),
  warehouse_manager_(count_robots_, order_manager_)
{
  ui->setupUi(this);
  initUI();
  init_model();
}
MainWindow::~MainWindow()
{
  delete ui;
  work_now_ = false;
  run_threads_ = false;
  if (logger_thread_.joinable())
  {
    logger_thread_.join();
  }
}
void MainWindow::start_stop()
{
  if (work_now_)
  {
    stop();
  }
  else
  {
    starter_ = std::thread(&MainWindow::start, this);
  }
  work_now_ = !work_now_;
}
void MainWindow::start() const
{
  for (const auto &client: clients_)
  {
    client->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(client_delay_ * 1000 / count_clients_));
  }
  warehouse_manager_.start();
}
void MainWindow::stop() const
{
  for (const auto &client: clients_)
  {
    client->stop();
  }
}
void MainWindow::decrease_clients_count()
{
  if (count_clients_ > 0)
  {
    dimkashelk::EventManager::getInstance().logEvent("(MainWindow) remove client " + (*clients_.rbegin())->to_string());
    clients_.pop_back();
    ui->table_clients->removeRow(ui->table_clients->rowCount() - 1);
    --count_clients_;
    set_clients_count();
  }
}
void MainWindow::increase_clients_count()
{
  clients_.push_back(std::make_shared < dimkashelk::Client >(count_clients_, order_manager_));
  clients_.back()->set_delay(client_delay_);
  ui->table_clients->insertRow(ui->table_clients->rowCount());
  dimkashelk::EventManager::getInstance().logEvent("(MainWindow) add client " + (*clients_.rbegin())->to_string());
  if (work_now_)
  {
    clients_.back()->start();
  }
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
  for (const auto &client: clients_)
  {
    client->set_delay(client_delay_);
  }
  set_clients_delay();
}
void MainWindow::decrease_robots()
{
  if (count_robots_ > 1)
  {
    --count_robots_;
    warehouse_manager_.pop_back_robot();
    ui->table_robots->removeRow(ui->table_robots->rowCount() - 1);
    set_robots_count();
  }
}
void MainWindow::increase_robots()
{
  ++count_robots_;
  warehouse_manager_.add_robot();
  ui->table_robots->insertRow(ui->table_robots->rowCount());
  set_robots_count();
}
void MainWindow::decrease_stack()
{
  if (stack_size_ > 1)
  {
    --stack_size_;
    order_manager_.decrement_stack();
    set_stack_size();
  }
}
void MainWindow::increase_stack()
{
  ++stack_size_;
  order_manager_.increment_stack();
  set_stack_size();
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
void MainWindow::update_logs() const
{
  while (run_threads_)
  {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    QStringList string_list;
    {
      std::lock_guard lock(dimkashelk::EventManager::getInstance().getMutex());
      auto new_logs = dimkashelk::EventManager::getInstance().getEvents();
      std::ranges::transform(new_logs, std::back_inserter(string_list),
                             [](const std::string &item)
                             {
                               return QString::fromStdString(item);
                             });
      dimkashelk::EventManager::getInstance().freeEvents();
    }
    ui->logs->addItems(string_list);
    ui->logs->scrollToBottom();
  }
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
  init_table_robot();
  init_table_clients();
}
void MainWindow::init_table_robot() const
{
  ui->table_robots->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->table_robots->setColumnCount(3);
  ui->table_robots->setHorizontalHeaderLabels({"№ прибора", "Коэффициент использования", "Относительный коэффициент"});
  for (size_t i = 0; i < count_robots_; ++i)
  {
    ui->table_robots->insertRow(ui->table_robots->rowCount());
    ui->table_robots->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
    ui->table_robots->setItem(i, 1, new QTableWidgetItem(QString::number(0)));
    ui->table_robots->setItem(i, 2, new QTableWidgetItem(QString::number(0)));
  }
}
void MainWindow::init_table_clients() const
{
  constexpr size_t count_columns = 9;
  ui->table_clients->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->table_clients->setColumnCount(count_columns);
  ui->table_clients->setHorizontalHeaderLabels({
    "№ источника", "Количество заявок", "p", "Отказы", "Тпреб", "Тбп", "Тобсл", "Дбп", "Добсл"
  });
  for (size_t i = 0; i < count_clients_; ++i)
  {
    ui->table_clients->insertRow(ui->table_clients->rowCount());
    ui->table_clients->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
    for (size_t j = 1; j < count_columns; ++j)
    {
      ui->table_clients->setItem(i, j, new QTableWidgetItem(QString::number(0)));
    }
  }
}
void MainWindow::init_model()
{
  for (size_t i = 0; i < count_clients_; i++)
  {
    clients_.push_back(std::make_shared < dimkashelk::Client >(i, order_manager_));
  }
  logger_thread_ = std::thread(&MainWindow::update_logs, this);
  statistics_clients_thread_ = std::thread(&MainWindow::update_statistics_clients, this);
  statistics_robots_thread_ = std::thread(&MainWindow::update_statistics_robots, this);
}
void MainWindow::update_statistics_clients() const
{
  while (run_threads_)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    for (size_t i = 0; i < count_clients_; i++)
    {
      ui->table_clients->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
      ui->table_clients->setItem(i, 1, new QTableWidgetItem(QString::number(clients_[i]->get_orders_count())));
      ui->table_clients->setItem(i, 2, new QTableWidgetItem(QString::number(clients_[i]->get_failure_rate())));
      ui->table_clients->setItem(i, 3, new QTableWidgetItem(QString::number(clients_[i]->get_rejected_count())));
      ui->table_clients->setItem(i, 4, new QTableWidgetItem(QString::number(clients_[i]->get_average_stay_time())));
      ui->table_clients->setItem(i, 5, new QTableWidgetItem(QString::number(clients_[i]->get_average_waiting_time())));
      ui->table_clients->setItem(i, 6, new QTableWidgetItem(QString::number(clients_[i]->get_average_execution_time())));
      ui->table_clients->setItem(i, 7, new QTableWidgetItem(QString::number(clients_[i]->get_waiting_time_variance())));
      ui->table_clients->setItem(i, 8, new QTableWidgetItem(QString::number(clients_[i]->get_execution_time_variance())));
    }
  }
}
void MainWindow::update_statistics_robots() const
{
  while (run_threads_)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    auto percents = warehouse_manager_.get_statistics();
    for (size_t i = 0; i < count_robots_; i++)
    {
      ui->table_robots->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
      ui->table_robots->setItem(i, 1, new QTableWidgetItem(QString::number(percents[i].first)));
      ui->table_robots->setItem(i, 2, new QTableWidgetItem(QString::number(percents[i].second)));
    }
  }
}
