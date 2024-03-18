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

#include <cstddef>
#include <cstdint>

#include "DevicePinouts.hpp"
#include "hardware/gpio.h"
#include "include/State.hpp"
#include "pico/time.h"
#include "pico/types.h"

state::State current_state(state::State::LightOff);
std::uint16_t seconds_since_alarm{};

void HandleMotionInterrupt(uint, std::uint32_t) {
  switch (current_state) {
  case state::State::LightOff:
    break;
  case state::State::LightOnActive:
    seconds_since_alarm = 0;
    break;
  case state::State::LightOnStale:
    gpio_put(pins::SPEAKER, 0);
    seconds_since_alarm = 0;
    break;
  }
}

int main(void) {
  pins::SetupPins();
  gpio_set_irq_enabled_with_callback(pins::MOTION_DETECTOR, GPIO_IRQ_EDGE_RISE,
                                     1, &HandleMotionInterrupt);

  while (1) {
    pins::ToggleStatusLED();
    current_state = state::DetermineRoomState(seconds_since_alarm);

    switch (current_state) {
    case state::State::LightOff:
      seconds_since_alarm = 0;
      continue;
      break;
    case state::State::LightOnActive:
      seconds_since_alarm++;
      continue;
      break;
    case state::State::LightOnStale:
      pins::ActivateAlarm();
      seconds_since_alarm = 0;
      break;
    }

    sleep_ms(1000);
  }

  return 0;
}
