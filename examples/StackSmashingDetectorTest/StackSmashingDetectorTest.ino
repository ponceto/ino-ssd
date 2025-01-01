/*
 * StackSmashingDetectorTest.ino - Copyright (c) 2014-2025 - Olivier Poncet
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
#include <StackSmashingDetector.h>

// ---------------------------------------------------------------------------
// setup
// ---------------------------------------------------------------------------

void setup()
{
    Serial.begin(115200);
}

// ---------------------------------------------------------------------------
// loop
// ---------------------------------------------------------------------------

void loop()
{
    const StackSmashingDetector stack_begin(F("begin"));
    char buffer[32];
    const StackSmashingDetector stack_end(F("end"));

    Serial.println(::strcpy(buffer, "this strcpy will do a buffer overflow"));
}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
