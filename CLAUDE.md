# Quansheng UV‑K5/K6/5R Custom Firmware — *F4HWN Fork*

**Repository**: [https://github.com/armel/uv-k5-firmware-custom](https://github.com/armel/uv-k5-firmware-custom)
**License**: Apache‑2.0
**Targets**: Quansheng UV‑K5 / UV‑K6 / UV‑5R (v2.1.27 MCU: DP32G030)

---

## 1. Purpose

A fully open‑source re‑implementation and feature‑rich fork of DualTachyon’s stock UV‑K5 firmware, merging in work from **OneOfEleven**, **Fagci (spectrum analyser)**, and **Egzumer**, then extended by **Armel F4HWN**.
The goal is to unlock extra radio capabilities, refine the UI, and provide several specialised firmware flavours while keeping the entire build reproducible.

---

## 2. Repository Layout (high‑level)

| Path                                                | Role                                                                         |
| --------------------------------------------------- | ---------------------------------------------------------------------------- |
| `app/`                                              | Application‑level features (DTMF, spectrum, breakout game, RescueOps logic…) |
| `ui/`                                               | Rendering engine, menus, bitmaps, fonts                                      |
| `driver/`                                           | Hardware access for BK4819 RF chip, GPIO, backlight, EEPROM, UART            |
| `bsp/dp32g030/`                                     | Minimal BSP & CMSIS wrappers for the DP32G030 MCU                            |
| `hardware/`                                         | Register definitions & low‑level peripherals                                 |
| `utils/`, `helper/`                                 | Battery calcs, boot‑mode helpers, packer `fw‑pack.py`                        |
| `Makefile`, `compile‑with‑docker.*`, `win_make.bat` | Build entry points                                                           |
| `start.S`, `firmware.ld`                            | Reset vector & linker script                                                 |

---

## 3. Firmware Flavours

| Variant       | Highlights                                                     |
| ------------- | -------------------------------------------------------------- |
| **Bandscope** | Adds the Fagci real‑time spectrum analyser                     |
| **Broadcast** | Includes commercial FM receiver (65–108 MHz)                   |
| **Basic**     | Spectrum + FM, but strips VOX, Aircopy, etc.                   |
| **RescueOps** | Presets & UI tweaks for first‑responders (fire, sea, mountain) |
| **Game**      | Easter‑egg Breakout mini‑game                                  |

> **Tip:** Flash size is tight; choose the variant matching your needs.

---

## 4. Key Enhancements (vs. Egzumer baseline)

* **Power presets**: Low1‑Low5 (\~20 mW → 1 W), Mid ≈ 2 W, High ≈ 5 W, plus user‑definable level.
* **Improved S‑meter** following IARU R1 spec; hard‑coded S0/S9 levels.
* **Extensive UI overhaul** — always‑visible menu index, ‘Main‑Only’, ‘Dual’ and ‘Cross’ screen modes, tiny/ classic fonts, RX/TX timers, USB indicator relocation, etc.
* **New/renamed menus**: `SetPwr`, `SetPTT`, `SetTOT`, `SetCtr`, `SetInv`, `SetEOT`, `SetMet`, `SetGUI`, `TXLock`, `SetTmr`, `SetOff`, `SetNFM`, `SysInf`.
* **Scan‑list system**: 3 user lists + list‑0 (channels w/o list) with quick keyboard shortcuts and resume-on‑start.
* **Hot‑keys**: `F+UP/DOWN` adjusts squelch, `F+F1/F2` steps, `F+8/9` back‑light toggles, long‑press `MENU` for temporary channel skip, etc.
* **AM‑RX fix** enabled by default, PWM noise reduction, cleaner startup, many bug‑fixes and refactors.

---

## 5. Building

1. **Toolchain**: `arm-none-eabi‑gcc` 10.3.1 (Ubuntu 22.04 default). Other versions risk oversize binaries.
2. **Quick paths**

   * **GitHub Codespaces**: press **Code → Codespaces → Create** → run `./compile-with-docker.sh <variant>`.
   * **Docker**: execute the same script locally for the smallest output (\~1 kB smaller than native builds).
   * **Windows**: `winget` installs GIT, Python 3.8, GNU Make & ARM toolchain → `win_make.bat`.
3. Artifacts are placed in `compiled-firmware/` as `firmware.packed.bin` (flashable with the web flasher or `k5prog`).

---

## 6. Flashing & Safety Notes

* **Back‑up first!** Dump the radio EEPROM using [`k5prog`](https://github.com/sq5bpf/k5prog).
* There is **no warranty**; flashing can brick your unit. Proceed at your own risk and common sense.
* A dedicated **CHIRP driver** is required — see [https://github.com/armel/uv-k5-chirp-driver](https://github.com/armel/uv-k5-chirp-driver).

---

## 7. Credits

DualTachyon → OneOfEleven → Fagci → Egzumer → **Armel F4HWN** ✨
Plus many other contributors listed in the repo.

---

## 8. License

Apache License 2.0 — see `LICENSE` for full text.

