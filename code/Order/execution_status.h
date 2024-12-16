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
    EXECUTION_REJECTED = 5
  };
  inline std::string executionStatusToString(const ExecutionStatus executionStatus)
  {
    switch (executionStatus)
    {
      case EXECUTION_CREATE:
        return "CREATE";
      case EXECUTION_IN_STACK:
        return "IN_STACK";
      case EXECUTION_RUN:
        return "RUN";
      case EXECUTION_DONE:
        return "DONE";
      case EXECUTION_FAILED:
        return "FAILED";
      default:
        return "UNKNOWN";
    }
  }
}
#endif
