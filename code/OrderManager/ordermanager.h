#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

namespace dimkashelk
{
  class OrderManager {
  public:
    void add_order(const Order& order) {
      std::lock_guard<std::mutex> lock(_mutex);
      _order_stack.add_order(order);
    }

    void failed_order(Order& order) {
      std::lock_guard<std::mutex> lock(_mutex);
      _order_stack.set_status(order, ExecutionStatus::Failed);
      _order_stack.remove_first();
    }
    void done_order(Order& order) {
      std::lock_guard<std::mutex> lock(_mutex);
      _order_stack.set_status(order, ExecutionStatus::Done);
      _order_stack.remove_first();
    }
  private:
    OrderStack _order_stack;
    mutable std::mutex _mutex;
  };
}
#endif
