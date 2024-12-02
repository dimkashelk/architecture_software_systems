#ifndef EXECUTION_STATUS_H
#define EXECUTION_STATUS_H

namespace dimkashelk
{
  enum ExecutionStatus
  {
    EXECUTION_CREATE = 0,
    EXECUTION_IN_STACK = 1,
    EXECUTION_RUN = 2,
    EXECUTION_DONE = 3,
    EXECUTION_FAILED = 4,
  };
}
#endif
