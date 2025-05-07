# MatriXDeck API Documentation

This directory contains comprehensive documentation for the MatriXDeck API across all supported platforms.

## Supported Platforms

The MatriXDeck hardware can be programmed using three different approaches:

1. **Arduino** - Familiar C++ based API using the Arduino framework
2. **MicroPython** - Python-based API for rapid development
3. **ESP-IDF** - Native ESP32 framework for maximum performance and control

Each platform has its own API documentation with equivalent functionality.

## API Overview

The MatriXDeck API is organized into the following functional categories:

### Display Functions

Functions for controlling the 32x16 LED matrix display:

- Pixel manipulation (setting individual pixels)
- Drawing primitives (lines, rectangles, circles)
- Text rendering
- Display buffer management

### Input Functions

Functions for reading user input devices:

- Button state (A, B, X, Y buttons)
- Joystick position and button
- Touch inputs (if supported by hardware version)

### Sensor Functions

Functions for accessing the onboard sensors:

- Accelerometer data (X, Y, Z axes)
- Gyroscope data (X, Y, Z axes)
- Temperature sensor
- Microphone input level

### Connectivity Functions

Functions for wireless communication:

- WiFi configuration and connection
- Bluetooth setup and pairing
- Web server and client operations
- MQTT communication

### Audio Functions

Functions for audio output:

- Tone generation
- Simple waveform synthesis
- Audio playback (if supported by hardware version)

### System Functions

Functions for system management:

- Power control and battery monitoring
- Sleep and wake modes
- Memory management
- File system operations

## Example Usage

Each platform's documentation includes example code to demonstrate API usage. Basic examples include:

- Display patterns and animations
- Reading and responding to button presses
- Using the accelerometer for motion detection
- Playing simple melodies
- Connecting to WiFi networks

## Function Reference

Detailed documentation for each function is provided in a consistent format:

```
functionName(parameter1, parameter2, ...)

Description: Detailed description of what the function does
Parameters:
  - parameter1: Type and description
  - parameter2: Type and description
Return value: Type and description of return value
Example:
  Code example showing how to use the function
Notes:
  Any special considerations or limitations
```

## Platform-Specific API Details

Please refer to the platform-specific documentation files for detailed information:

- [Arduino API Documentation](arduino.md)
- [MicroPython API Documentation](micropython.md)
- [ESP-IDF API Documentation](esp-idf.md) 