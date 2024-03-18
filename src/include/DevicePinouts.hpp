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

#ifndef SRC_INCLUDE_DEVICEPINOUTS_HPP_
#define SRC_INCLUDE_DEVICEPINOUTS_HPP_

#include <cstdint>
namespace pins {
constexpr std::uint8_t MOTION_DETECTOR(1);
constexpr std::uint8_t SPEAKER(10);
constexpr std::uint8_t PHOTO_RESISTOR(34);
constexpr std::uint8_t STATUS_LED(5);

void ActivateAlarm();
void ToggleStatusLED();
void SetupPins();

} // namespace pins

#endif // SRC_INCLUDE_DEVICEPINOUTS_HPP_
