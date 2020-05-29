/*
 * StackSmashingDetector.h - Copyright (c) 2020 - Olivier Poncet
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
#ifndef __INO_SSD_StackSmashingDetector_h__
#define __INO_SSD_StackSmashingDetector_h__

// ---------------------------------------------------------------------------
// configuration
// ---------------------------------------------------------------------------

#ifndef STACK_SMASHING_DETECTOR_SERIAL
#define STACK_SMASHING_DETECTOR_SERIAL Serial
#endif

#ifndef STACK_SMASHING_DETECTOR_ACTIVE
#define STACK_SMASHING_DETECTOR_ACTIVE 1
#endif

// ---------------------------------------------------------------------------
// StackSmashingDetector
// ---------------------------------------------------------------------------

class StackSmashingDetector
{
public: // public interface
    StackSmashingDetector(const __FlashStringHelper* string = nullptr) __attribute__((always_inline));
   ~StackSmashingDetector() __attribute__((always_inline));

    void check(const __FlashStringHelper* string = nullptr);

private: // private interface
   const uint32_t _canary;
};

// ---------------------------------------------------------------------------
// StackSmashingDetector traits
// ---------------------------------------------------------------------------

struct StackSmashingDetectorTraits
{
    static constexpr uint32_t CANARY = 0xDEADBEEF;

    static void enter(const void* ssd, const uint32_t canary, const __FlashStringHelper* string = nullptr);
    static void leave(const void* ssd, const uint32_t canary, const __FlashStringHelper* string = nullptr);
    static void check(const void* ssd, const uint32_t canary, const __FlashStringHelper* string = nullptr);
    static void panic();
};

// ---------------------------------------------------------------------------
// StackSmashingDetector implementation
// ---------------------------------------------------------------------------

inline
StackSmashingDetector::StackSmashingDetector(const __FlashStringHelper* string)
    : _canary(StackSmashingDetectorTraits::CANARY)
{
#if defined(STACK_SMASHING_DETECTOR_ACTIVE) && (STACK_SMASHING_DETECTOR_ACTIVE > 0)
    StackSmashingDetectorTraits::enter(this, _canary, string);
#else
    (void)(string); /* ignore warning */
#endif
}

inline
StackSmashingDetector::~StackSmashingDetector()
{
#if defined(STACK_SMASHING_DETECTOR_ACTIVE) && (STACK_SMASHING_DETECTOR_ACTIVE > 0)
    StackSmashingDetectorTraits::leave(this, _canary, nullptr);
#endif
}

inline
void StackSmashingDetector::check(const __FlashStringHelper* string)
{
#if defined(STACK_SMASHING_DETECTOR_ACTIVE) && (STACK_SMASHING_DETECTOR_ACTIVE > 0)
    StackSmashingDetectorTraits::check(this, _canary, string);
#else
    (void)(string); /* ignore warning */
#endif
}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------

#endif /* __INO_SSD_StackSmashingDetector_h__ */
