#pragma once

#include <Arduino.h>

#include "display_config.h"

// Match the vendor example's landscape memory layout:
// 250 columns, each column storing 122 vertical pixels packed into 16 bytes.
constexpr int EPD_BUFFER_SIZE = ((SCREEN_HEIGHT + 7) / 8) * SCREEN_WIDTH;

void epdInit();
void epdSleep();
void epdDisplayImage(const uint8_t* image);
