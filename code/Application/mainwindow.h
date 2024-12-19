#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <client.h>
#include <warehousemanager.h>
QT_BEGIN_NAMESPACE

namespace Ui
{
  class MainWindow;
}

QT_END_NAMESPACE
class MainWindow final: public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

private:
  Ui::MainWindow *ui;
  bool work_now_;
  bool run_logs_;
  size_t stack_size_;
  size_t count_clients_;
  size_t count_robots_;
  size_t client_delay_;
  dimkashelk::OrderManager order_manager_;
  dimkashelk::WarehouseManager warehouse_manager_;
  std::vector < std::shared_ptr < dimkashelk::Client > > clients_;
  std::thread logger_thread_;
  void start_stop();
  void start() const;
  void stop() const;
  void decrease_clients_count();
  void increase_clients_count();
  void decrease_clients_delay();
  void increase_clients_delay();
  void update_clients_delay() const;
  void decrease_robots();
  void increase_robots();
  void decrease_stack();
  void increase_stack();
  void set_clients_count() const;
  void set_clients_delay() const;
  void set_robots_count() const;
  void set_stack_size() const;
  void update_logs() const;
  void initUI() const;
  void init_table_robot() const;
  void init_model();
};
#endif
