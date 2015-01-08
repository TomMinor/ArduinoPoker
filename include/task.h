#ifndef TASK_H
#define TASK_H

#include "dealergui.h"

class Task
{
public:
    Task();
    virtual void execute() = 0;
private:
};

#endif // TASK_H
