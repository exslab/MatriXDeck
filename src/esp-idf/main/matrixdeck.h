/**
 * MatriXDeck ESP-IDF Implementation
 * 
 * Header file for the MatriXDeck LED matrix hardware
 *
 * Created by MatriXDeck Team, 2023
 * Released under MIT License
 */

#ifndef MATRIXDECK_H
#define MATRIXDECK_H

#include <stdbool.h>
#include <stdint.h>
#include "driver/gpio.h"
#include "driver/adc.h"
#include "driver/i2c.h"
#include "driver/ledc.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pin definitions
#define MATRIX_DATA_PIN       GPIO_NUM_23
#define MATRIX_CLK_PIN        GPIO_NUM_18
#define MATRIX_CS_PIN         GPIO_NUM_5
#define BUTTON_A_PIN          GPIO_NUM_32
#define BUTTON_B_PIN          GPIO_NUM_33
#define BUTTON_X_PIN          GPIO_NUM_25
#define BUTTON_Y_PIN          GPIO_NUM_26
#define JOYSTICK_X_PIN        ADC1_CHANNEL_6  // GPIO34
#define JOYSTICK_Y_PIN        ADC1_CHANNEL_7  // GPIO35
#define JOYSTICK_BTN_PIN      GPIO_NUM_27
#define SPEAKER_PIN           GPIO_NUM_19
#define MIC_PIN               ADC1_CHANNEL_0  // GPIO36

// I2C pins for MPU6050
#define I2C_SDA_PIN           GPIO_NUM_21
#define I2C_SCL_PIN           GPIO_NUM_22
#define I2C_PORT              I2C_NUM_0
#define MPU6050_ADDR          0x68

// Matrix dimensions
#define MATRIX_WIDTH          32
#define MATRIX_HEIGHT         16

// Colors
#define MATRIX_COLOR_OFF      0
#define MATRIX_COLOR_RED      1
#define MATRIX_COLOR_GREEN    2
#define MATRIX_COLOR_AMBER    3

/**
 * Accelerometer and gyroscope data structure
 */
typedef struct {
    float accel_x;
    float accel_y;
    float accel_z;
    float gyro_x;
    float gyro_y;
    float gyro_z;
    float temp;
} mpu6050_data_t;

/**
 * Initialize the MatriXDeck hardware
 * 
 * @return true if initialization successful, false otherwise
 */
bool matrixdeck_init(void);

/**
 * Update the LED matrix with current buffer contents
 */
void matrixdeck_update_display(void);

/**
 * Clear the display buffer
 */
void matrixdeck_clear_display(void);

/**
 * Set a pixel in the buffer
 * 
 * @param x X coordinate (0-31)
 * @param y Y coordinate (0-15)
 * @param color Color (0=off, 1=red, 2=green, 3=amber)
 */
void matrixdeck_set_pixel(uint8_t x, uint8_t y, uint8_t color);

/**
 * Draw a line in the buffer
 * 
 * @param x0 Start X coordinate
 * @param y0 Start Y coordinate
 * @param x1 End X coordinate
 * @param y1 End Y coordinate
 * @param color Color (0=off, 1=red, 2=green, 3=amber)
 */
void matrixdeck_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);

/**
 * Draw a rectangle in the buffer
 * 
 * @param x X coordinate of top-left corner
 * @param y Y coordinate of top-left corner
 * @param w Width of rectangle
 * @param h Height of rectangle
 * @param color Color (0=off, 1=red, 2=green, 3=amber)
 */
void matrixdeck_draw_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);

/**
 * Draw a filled rectangle in the buffer
 * 
 * @param x X coordinate of top-left corner
 * @param y Y coordinate of top-left corner
 * @param w Width of rectangle
 * @param h Height of rectangle
 * @param color Color (0=off, 1=red, 2=green, 3=amber)
 */
void matrixdeck_fill_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);

/**
 * Draw a circle in the buffer
 * 
 * @param x X coordinate of center
 * @param y Y coordinate of center
 * @param r Radius
 * @param color Color (0=off, 1=red, 2=green, 3=amber)
 */
void matrixdeck_draw_circle(uint8_t x, uint8_t y, uint8_t r, uint8_t color);

/**
 * Draw text in the buffer
 * 
 * @param x X coordinate of top-left corner
 * @param y Y coordinate of top-left corner
 * @param text Text to draw
 * @param color Color (0=off, 1=red, 2=green, 3=amber)
 * @param size Text size multiplier
 */
void matrixdeck_draw_text(uint8_t x, uint8_t y, const char* text, uint8_t color, uint8_t size);

/**
 * Read the state of a button
 * 
 * @param button Button to read (0=A, 1=B, 2=X, 3=Y, 4=Joystick)
 * @return true if button is pressed, false otherwise
 */
bool matrixdeck_read_button(uint8_t button);

/**
 * Read the joystick position
 * 
 * @param axis Axis to read (0=X, 1=Y)
 * @return Analog joystick position (0-4095)
 */
int matrixdeck_read_joystick(uint8_t axis);

/**
 * Read motion sensor data
 * 
 * @param data Pointer to mpu6050_data_t structure to fill with data
 * @return true if successful, false otherwise
 */
bool matrixdeck_read_motion(mpu6050_data_t* data);

/**
 * Play a tone on the speaker
 * 
 * @param frequency Frequency in Hz
 * @param duration Duration in milliseconds
 */
void matrixdeck_play_tone(uint16_t frequency, uint16_t duration);

/**
 * Read the microphone level
 * 
 * @return Audio level (0-4095)
 */
int matrixdeck_read_microphone(void);

#ifdef __cplusplus
}
#endif

#endif // MATRIXDECK_H 