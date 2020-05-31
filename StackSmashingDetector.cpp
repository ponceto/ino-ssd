/*
 * StackSmashingDetector.cpp - Copyright (c) 2020 - Olivier Poncet
 *
 * This file is part of the StackSmashingDetector library
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <Arduino.h>
#include "StackSmashingDetector.h"

// ---------------------------------------------------------------------------
// StackSmashingDetector
// ---------------------------------------------------------------------------

void StackSmashingDetectorTraits::enter(const void* ssd, const uint32_t canary, const __FlashStringHelper* string)
{
    STACK_SMASHING_DETECTOR_SERIAL.print(F("SSD enter: canary at 0x"));
    STACK_SMASHING_DETECTOR_SERIAL.print(reinterpret_cast<unsigned int>(ssd), 16);
    if(string != nullptr) {
        STACK_SMASHING_DETECTOR_SERIAL.print(',');
        STACK_SMASHING_DETECTOR_SERIAL.print(' ');
        STACK_SMASHING_DETECTOR_SERIAL.print(string);
    }
    if(canary != CANARY) {
        panic();
    }
    STACK_SMASHING_DETECTOR_SERIAL.println();
}

void StackSmashingDetectorTraits::leave(const void* ssd, const uint32_t canary, const __FlashStringHelper* string)
{
    STACK_SMASHING_DETECTOR_SERIAL.print(F("SSD leave: canary at 0x"));
    STACK_SMASHING_DETECTOR_SERIAL.print(reinterpret_cast<unsigned int>(ssd), 16);
    if(string != nullptr) {
        STACK_SMASHING_DETECTOR_SERIAL.print(',');
        STACK_SMASHING_DETECTOR_SERIAL.print(' ');
        STACK_SMASHING_DETECTOR_SERIAL.print(string);
    }
    if(canary != CANARY) {
        panic();
    }
    STACK_SMASHING_DETECTOR_SERIAL.println();
}

void StackSmashingDetectorTraits::check(const void* ssd, const uint32_t canary, const __FlashStringHelper* string)
{
    STACK_SMASHING_DETECTOR_SERIAL.print(F("SSD check: canary at 0x"));
    STACK_SMASHING_DETECTOR_SERIAL.print(reinterpret_cast<unsigned int>(ssd), 16);
    if(string != nullptr) {
        STACK_SMASHING_DETECTOR_SERIAL.print(',');
        STACK_SMASHING_DETECTOR_SERIAL.print(' ');
        STACK_SMASHING_DETECTOR_SERIAL.print(string);
    }
    if(canary != CANARY) {
        panic();
    }
    STACK_SMASHING_DETECTOR_SERIAL.println();
}

void StackSmashingDetectorTraits::panic()
{
    STACK_SMASHING_DETECTOR_SERIAL.println(F(" *** Stack Smashing Detected *** "));
    STACK_SMASHING_DETECTOR_SERIAL.println(F("KERNEL PANIC"));
    do {
        _NOP();
    } while(true);
}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
