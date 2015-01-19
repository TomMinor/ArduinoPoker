#ifndef TASK_H
#define TASK_H

#include "gui_dealergui.h"

class GUI_Task
{
public:
    GUI_Task();
    virtual void execute() = 0;
private:
};

#endif // TASK_H
