#ifndef EVENT_H
#define EVENT_H

#include "../entity_management/entity_manager.h"
class EventManager;

class Event {
public:

    virtual void execute() = 0;
};


#endif