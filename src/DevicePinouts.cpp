/*
   Copyright 2024 Sebastian Pineda (spineda.wpi.alum@gmail.com)

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "DevicePinouts.hpp"
#include "hardware/gpio.h"

namespace pins {

void ActivateAlarm() { gpio_put(pins::SPEAKER, 1); }

void ToggleStatusLED() {
  if (gpio_get(STATUS_LED)) {
    gpio_put(STATUS_LED, 0);
  } else {
    gpio_put(STATUS_LED, 1);
  }
}

void SetupPins() {
  gpio_init(MOTION_DETECTOR);
  gpio_init(SPEAKER);
  gpio_init(PHOTO_RESISTOR);
  gpio_init(STATUS_LED);
}

} // namespace pins
