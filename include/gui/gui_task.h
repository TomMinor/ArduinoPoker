#ifndef TASK_H
#define TASK_H

//OBSELETE

#include "gui_dealergui.h"

namespace GUI
{

class Task
{
public:
    Task();
    virtual void execute() = 0;
private:
};

}

#endif // TASK_H
