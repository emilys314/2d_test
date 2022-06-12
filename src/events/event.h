#ifndef EVENT_H
#define EVENT_H

#include "../entity_management/entity_manager.h"

class Event {
private:


public:

    virtual void execute(Entity_Manager &entity_manager) = 0;
};


#endif