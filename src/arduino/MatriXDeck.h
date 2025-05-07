/**
 * MatriXDeck.h - Main library for MatriXDeck
 * 
 * This library provides functions to control the LED matrix, sensors, 
 * buttons, and other hardware components of the MatriXDeck device.
 * 
 * Created by MatriXDeck Team, 2023
 * Released under MIT License
 */

#ifndef MATRIXDECK_H
#define MATRIXDECK_H

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_GFX.h>

// Pin definitions
#define MATRIX_DATA_PIN       23
#define MATRIX_CLK_PIN        18
#define MATRIX_CS_PIN         5
#define BUTTON_A_PIN          32
#define BUTTON_B_PIN          33
#define BUTTON_X_PIN          25
#define BUTTON_Y_PIN          26
#define JOYSTICK_X_PIN        34
#define JOYSTICK_Y_PIN        35
#define JOYSTICK_BTN_PIN      27
#define SPEAKER_PIN           19
#define MIC_PIN               36

// Matrix dimensions
#define MATRIX_WIDTH          32
#define MATRIX_HEIGHT         16

// Colors
#define MATRIX_COLOR_OFF      0
#define MATRIX_COLOR_RED      1
#define MATRIX_COLOR_GREEN    2
#define MATRIX_COLOR_AMBER    3

class MatriXDeck {
public:
    /**
     * Constructor
     */
    MatriXDeck();
    
    /**
     * Initialize the MatriXDeck hardware
     * 
     * @return true if initialization successful, false otherwise
     */
    bool begin();
    
    /**
     * Update the LED matrix with current buffer contents
     */
    void updateDisplay();
    
    /**
     * Clear the display buffer
     */
    void clearDisplay();
    
    /**
     * Set a pixel in the buffer
     * 
     * @param x X coordinate (0-31)
     * @param y Y coordinate (0-15)
     * @param color Color (0=off, 1=red, 2=green, 3=amber)
     */
    void setPixel(uint8_t x, uint8_t y, uint8_t color);
    
    /**
     * Draw a line in the buffer
     * 
     * @param x0 Start X coordinate
     * @param y0 Start Y coordinate
     * @param x1 End X coordinate
     * @param y1 End Y coordinate
     * @param color Color (0=off, 1=red, 2=green, 3=amber)
     */
    void drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);
    
    /**
     * Draw a rectangle in the buffer
     * 
     * @param x X coordinate of top-left corner
     * @param y Y coordinate of top-left corner
     * @param w Width of rectangle
     * @param h Height of rectangle
     * @param color Color (0=off, 1=red, 2=green, 3=amber)
     */
    void drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
    
    /**
     * Draw a filled rectangle in the buffer
     * 
     * @param x X coordinate of top-left corner
     * @param y Y coordinate of top-left corner
     * @param w Width of rectangle
     * @param h Height of rectangle
     * @param color Color (0=off, 1=red, 2=green, 3=amber)
     */
    void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
    
    /**
     * Draw a circle in the buffer
     * 
     * @param x X coordinate of center
     * @param y Y coordinate of center
     * @param r Radius
     * @param color Color (0=off, 1=red, 2=green, 3=amber)
     */
    void drawCircle(uint8_t x, uint8_t y, uint8_t r, uint8_t color);
    
    /**
     * Draw text in the buffer
     * 
     * @param x X coordinate of top-left corner
     * @param y Y coordinate of top-left corner
     * @param text Text to draw
     * @param color Color (0=off, 1=red, 2=green, 3=amber)
     * @param size Text size multiplier
     */
    void drawText(uint8_t x, uint8_t y, const char* text, uint8_t color, uint8_t size = 1);
    
    /**
     * Read the state of a button
     * 
     * @param button Button to read (0=A, 1=B, 2=X, 3=Y, 4=Joystick)
     * @return true if button is pressed, false otherwise
     */
    bool readButton(uint8_t button);
    
    /**
     * Read the joystick position
     * 
     * @param axis Axis to read (0=X, 1=Y)
     * @return Analog joystick position (0-1023)
     */
    int readJoystick(uint8_t axis);
    
    /**
     * Read accelerometer data
     * 
     * @param axis Axis to read (0=X, 1=Y, 2=Z)
     * @return Acceleration value in m/s²
     */
    float readAccelerometer(uint8_t axis);
    
    /**
     * Read gyroscope data
     * 
     * @param axis Axis to read (0=X, 1=Y, 2=Z)
     * @return Rotation rate in degrees/s
     */
    float readGyroscope(uint8_t axis);
    
    /**
     * Play a tone on the speaker
     * 
     * @param frequency Frequency in Hz
     * @param duration Duration in milliseconds
     */
    void playTone(uint16_t frequency, uint16_t duration);
    
    /**
     * Read the microphone level
     * 
     * @return Audio level (0-1023)
     */
    int readMicrophone();
    
private:
    uint8_t displayBuffer[MATRIX_WIDTH * MATRIX_HEIGHT];
    Adafruit_MPU6050 mpu;
};

#endif // MATRIXDECK_H 