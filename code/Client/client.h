#ifndef CLIENT_H
#define CLIENT_H
#include <atomic>
#include <memory>
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
    explicit Client(OrderManager &order_manager);
    const std::vector < std::shared_ptr < Order > > &get_orders() const;
    ~Client();

  private:
    void generate_order();
    void run();
    std::vector < std::shared_ptr < Order > > orders_;
    OrderManager &order_manager_;
    std::thread worker_thread_;
    std::atomic < bool > stop_flag_;
    mutable std::mutex mtx_;
  };
}
#endif
