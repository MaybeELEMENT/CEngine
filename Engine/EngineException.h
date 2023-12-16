#ifndef ENGINEEXCEPTION_HEADER
#define ENGINEEXCEPTION_HEADER
#include <string>
class EngineException {
public:
    std::string msg;
    EngineException(std::string message) {
        this->msg = message;
    }
};
#endif