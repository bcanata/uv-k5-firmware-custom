/* Copyright 2023 Dual Tachyon
 * https://github.com/DualTachyon
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 */

#ifndef APP_APRS_H
#define APP_APRS_H

#include <stdint.h>
#include <stdbool.h>

#define APRS_CALLSIGN "TA1ANW"
#define APRS_LATITUDE 40.993361
#define APRS_LONGITUDE 27.598504

void APRS_SendPacket(void);
void APRS_EncodePosition(uint8_t *buffer, uint16_t *length);
void APRS_EncodeAX25(uint8_t *buffer, uint16_t *length, const char *payload);

#endif