#pragma once
#include "Arduino.h"
#include "../Pacotes.hpp"
#include "../Debug.hpp"

enum Estado {
    ON,
    // RELEASE,
    OFF,
    // PUSH,
};

void ConfiguraTouchs(TouchStatus* touch0, TouchStatus* touch2);

bool GestaoBotaoTouch0 (TouchStatus* touch);
bool GestaoBotaoTouch2 (TouchStatus* touch);
