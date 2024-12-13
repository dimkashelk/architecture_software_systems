#ifndef CLIENT_H
#define CLIENT_H
#include <atomic>
#include <mutex>
#include <thread>
#include <vector>
#include <Order/order.h>

namespace dimkashelk
{
  class OrderManager;
  class Client
  {
  public:
    Client();
    void generate_order();
    const std::vector < Order > &get_orders() const;
    ~Client();

  private:
    std::vector < Order > orders_;
    OrderManager &order_manager_;
    std::thread worker_thread_;
    std::atomic < bool > stop_flag_;
    mutable std::mutex mtx_;
  };
}
#endif
