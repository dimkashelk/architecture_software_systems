#ifndef ROBOT_H
#define ROBOT_H
#include <atomic>
#include <condition_variable>
#include <optional>
#include <mutex>
#include <thread>
#include <Order/order.h>

namespace dimkashelk
{
  /*!
  \brief Робот, выполняющий заказ

  Класс робота, выполняющего заказ на перемещение объекта.
*/
  class Robot
  {
  public:
    /*!
    Конструктор по умолчанию, создает пустого робота без заказов
    */
    Robot();
    /*!
    Метод, устанавливающий заказ для исполнения
    \param order Заказ, который роботу необходимо выполнить
    \throw std::runtime_error Выбрасывает исключение, если робот выполняет перемещение другого заказа
    */
    void set_order(const Order &order);
    /*!
    Метод, запускающий исполнение заказа
    Заказ будет выполнен в отдельном потоке, созданном в данном методе
    \throw std::runtime_error Выбрасывает исключение, если робот выполняет перемещение другого заказа
    \throw std::logic_error Выбрасывает исключение, если для робота не установлен заказ
    */
    void start_order();
    bool available() const;
    ~Robot();
  private:
    void finish_order();
    void run();
    size_t calculate_wait_time() const;
    std::optional < Order > current_order_{};
    bool work_now_;
    std::atomic < bool > stop_flag_;
    mutable std::mutex mtx_{};
    std::condition_variable cv_{};
    std::thread worker_thread_{};
  };
}
#endif
