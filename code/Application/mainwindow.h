#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <client.h>
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
  size_t stack_size_;
  size_t count_clients_;
  size_t count_robots_;
  size_t client_delay_;
  std::vector < std::shared_ptr < dimkashelk::Client > > clients_;
  void start_stop();
  void decrease_clients_count();
  void increase_clients_count();
  void decrease_clients_delay();
  void increase_clients_delay();
  void decrease_robots();
  void increase_robots();
  void decrease_stack();
  void increase_stack();
  void set_clients_count() const;
  void set_clients_delay() const;
  void set_robots_count() const;
  void set_stack_size() const;
};
#endif
