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

#include "app/aprs.h"
#include "driver/bk4819.h"
#include "radio.h"
#include "misc.h"
#include <string.h>
#include <stdio.h>

static uint8_t aprs_packet[256];
static uint16_t aprs_packet_length;

void APRS_EncodePosition(uint8_t *buffer, uint16_t *length)
{
    char aprs_message[128];
    
    // Convert latitude to APRS format (DDMM.MMN)
    int lat_deg = (int)APRS_LATITUDE;
    float lat_min = (APRS_LATITUDE - lat_deg) * 60.0;
    char lat_dir = (APRS_LATITUDE >= 0) ? 'N' : 'S';
    
    // Convert longitude to APRS format (DDDMM.MME)
    int lon_deg = (int)APRS_LONGITUDE;
    float lon_min = (APRS_LONGITUDE - lon_deg) * 60.0;
    char lon_dir = (APRS_LONGITUDE >= 0) ? 'E' : 'W';
    
    // Format APRS position message
    snprintf(aprs_message, sizeof(aprs_message), 
             "!%02d%05.2f%c/%03d%05.2f%c>UV-K5 APRS", 
             lat_deg, lat_min, lat_dir, 
             lon_deg, lon_min, lon_dir);
    
    APRS_EncodeAX25(buffer, length, aprs_message);
}

void APRS_EncodeAX25(uint8_t *buffer, uint16_t *length, const char *payload)
{
    uint16_t pos = 0;
    
    // AX.25 Flag (0x7E)
    buffer[pos++] = 0x7E;
    
    // Destination address (APRS)
    buffer[pos++] = 'A' << 1;
    buffer[pos++] = 'P' << 1;
    buffer[pos++] = 'R' << 1;
    buffer[pos++] = 'S' << 1;
    buffer[pos++] = ' ' << 1;
    buffer[pos++] = ' ' << 1;
    buffer[pos++] = 0x60;  // SSID + reserved bits
    
    // Source address (Your callsign)
    const char *callsign = APRS_CALLSIGN;
    for (int i = 0; i < 6; i++) {
        if (i < (int)strlen(callsign)) {
            buffer[pos++] = callsign[i] << 1;
        } else {
            buffer[pos++] = ' ' << 1;
        }
    }
    buffer[pos++] = 0x61;  // SSID + end bit
    
    // Control field (UI frame)
    buffer[pos++] = 0x03;
    
    // Protocol ID (No layer 3)
    buffer[pos++] = 0xF0;
    
    // Information field (payload)
    for (size_t i = 0; i < strlen(payload); i++) {
        buffer[pos++] = payload[i];
    }
    
    // End flag
    buffer[pos++] = 0x7E;
    
    *length = pos;
}

void APRS_SendPacket(void)
{
    // Setup FSK mode for 1200 baud APRS
    BK4819_WriteRegister(BK4819_REG_58,
        (1u << 13) |    // FSK TX mode selection (FFSK 1200/1800)
        (7u << 10) |    // FSK RX mode selection (FFSK 1200/1800)
        (3u << 8)  |    // FSK RX gain
        (0u << 6)  |    // Reserved
        (0u << 4)  |    // FSK preamble type
        (1u << 1)  |    // FSK RX bandwidth (FFSK 1200/1800)
        (1u << 0));     // Enable
    
    // Encode APRS position packet
    APRS_EncodePosition(aprs_packet, &aprs_packet_length);
    
    // Convert to 16-bit words for transmission
    uint16_t fsk_buffer[36];
    for (int i = 0; i < 36 && i * 2 < aprs_packet_length; i++) {
        if (i * 2 + 1 < aprs_packet_length) {
            fsk_buffer[i] = (aprs_packet[i * 2 + 1] << 8) | aprs_packet[i * 2];
        } else {
            fsk_buffer[i] = aprs_packet[i * 2];
        }
    }
    
    // Setup radio for transmission
    RADIO_SetTxParameters();
    
    // Send the packet
    BK4819_SendFSKData(fsk_buffer);
    
    // Disable PA
    BK4819_SetupPowerAmplifier(0, 0);
    BK4819_ToggleGpioOut(BK4819_GPIO1_PIN29_PA_ENABLE, false);
}