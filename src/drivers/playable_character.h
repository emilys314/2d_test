#ifndef PLAYERABLE_CHARACTER_H
#define PLAYERABLE_CHARACTER_H

#include <stdio.h>
#include "parent_driver.h"

class PlayableCharacter : public Driver {
private:

public:
    PlayableCharacter() {

    }

    void check_inputs() {
        printf("PlayableCharacter check_input");
    }
};

#endif