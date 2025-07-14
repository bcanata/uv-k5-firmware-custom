#!/bin/sh

# This script compiles a minimal version of the firmware with fewer features
# to fit within the flash memory constraints

echo "🔍 Minimal compilation..."
docker run --rm -v "$PWD/compiled-firmware:/app/compiled-firmware" uvk5 /bin/bash -c "\
    cd /app && make -s \
    ENABLE_SPECTRUM=0 \
    ENABLE_FMRADIO=0 \
    ENABLE_VOX=0 \
    ENABLE_AIRCOPY=0 \
    ENABLE_FEAT_F4HWN_GAME=0 \
    ENABLE_FEAT_F4HWN_SPECTRUM=0 \
    ENABLE_FEAT_F4HWN_PMR=0 \
    ENABLE_FEAT_F4HWN_GMRS_FRS_MURS=0 \
    ENABLE_NOAA=0 \
    ENABLE_AUDIO_BAR=0 \
    ENABLE_RSSI_BAR=0 \
    ENABLE_FEAT_F4HWN_RESUME_STATE=0 \
    ENABLE_FEAT_F4HWN_CHARGING_C=0 \
    ENABLE_FEAT_F4HWN_INV=0 \
    ENABLE_FEAT_F4HWN_CTR=0 \
    ENABLE_FEAT_F4HWN_NARROWER=0 \
    ENABLE_FEAT_F4HWN_RESCUE_OPS=0 \
    ENABLE_FEAT_F4HWN_RX_TX_TIMER=0 \
    ENABLE_FEAT_F4HWN_SLEEP=0 \
    ENABLE_FEAT_F4HWN_CA=0 \
    ENABLE_FLASHLIGHT=0 \
    ENABLE_SCAN_RANGES=0 \
    ENABLE_COPY_CHAN_TO_VFO=0 \
    EDITION_STRING=Minimal \
    TARGET=f4hwn.minimal \
    && cp f4hwn.minimal* compiled-firmware/"
