#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
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
  void start_stop();
  void decrease_clients();
  void increase_clients();
  void decrease_robots();
  void increase_robots();
};
#endif
