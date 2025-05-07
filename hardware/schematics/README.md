# MatriXDeck Hardware Schematics

This directory contains the electronic schematics for the MatriXDeck hardware.

## Files

- `matrixdeck_main.pdf` - Main board schematic
- `matrixdeck_main.kicad_sch` - KiCad schematic source file
- `matrixdeck_main.kicad_pcb` - KiCad PCB layout source file
- `matrixdeck_balance_robot.pdf` - Balance Robot expansion schematic
- `matrixdeck_balance_robot.kicad_sch` - KiCad schematic source for Balance Robot expansion

## Hardware Overview

The MatriXDeck hardware consists of the following main components:

1. **ESP32-WROOM-32D** microcontroller module
2. **32x16 LED Matrix** (dual-color red/green)
3. **MPU6050** 6-axis motion sensor
4. **Speaker and microphone** circuit
5. **Control inputs** (joystick and buttons)
6. **Power management** (battery charging and regulation)
7. **I/O expansion** header

## Component Selection

### Microcontroller
- ESP32-WROOM-32D module with dual-core processor and onboard WiFi/Bluetooth

### LED Matrix
- 32x16 (512 LEDs) dual-color (red/green) LED matrix
- Controlled via shift registers for efficient updating

### Motion Sensor
- MPU6050 6-axis motion sensor
- Connected via I²C interface

### Audio
- Piezo speaker driven by PWM output
- MEMS microphone with amplifier circuit

### Inputs
- Analog joystick with X/Y axes and button
- 4 tactile buttons for game-style control

### Power
- 2000mAh Li-Po battery
- TP4056 charging IC with USB-C connector
- 3.3V low-dropout regulator

## Design Notes

1. The PCB is designed to fit within the planned case dimensions (120mm x 70mm).
2. Power management includes low-battery protection and charging indicator.
3. All components are mounted on a single PCB to minimize assembly complexity.
4. Expansion header provides access to unused GPIO pins, I²C, SPI, and power.

## Manufacturing Notes

- PCB: 2-layer, FR4, 1.6mm thickness
- Component placement is optimized for pick-and-place assembly
- SMD components are used where possible for size reduction
- Min. trace width: 8mil
- Min. trace spacing: 8mil

## Revisions

| Revision | Date | Description |
|----------|------|-------------|
| v0.1 | TBD | Initial prototype design |
| v0.2 | TBD | Design updates after prototype testing |
| v1.0 | TBD | Production release version | 