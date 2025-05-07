/**
 * MatriXDeck.cpp - Implementation of MatriXDeck library
 * 
 * Created by MatriXDeck Team, 2023
 * Released under MIT License
 */

#include "MatriXDeck.h"

// Constructor
MatriXDeck::MatriXDeck() {
  // Initialize buffer to all off
  memset(displayBuffer, MATRIX_COLOR_OFF, MATRIX_WIDTH * MATRIX_HEIGHT);
}

// Initialize hardware
bool MatriXDeck::begin() {
  // Set pin modes for buttons
  pinMode(BUTTON_A_PIN, INPUT_PULLUP);
  pinMode(BUTTON_B_PIN, INPUT_PULLUP);
  pinMode(BUTTON_X_PIN, INPUT_PULLUP);
  pinMode(BUTTON_Y_PIN, INPUT_PULLUP);
  pinMode(JOYSTICK_BTN_PIN, INPUT_PULLUP);
  
  // Set pin modes for analog inputs
  pinMode(JOYSTICK_X_PIN, INPUT);
  pinMode(JOYSTICK_Y_PIN, INPUT);
  pinMode(MIC_PIN, INPUT);
  
  // Set up speaker pin
  pinMode(SPEAKER_PIN, OUTPUT);
  
  // Set up LED matrix pins
  pinMode(MATRIX_DATA_PIN, OUTPUT);
  pinMode(MATRIX_CLK_PIN, OUTPUT);
  pinMode(MATRIX_CS_PIN, OUTPUT);
  
  // Initialize I2C for MPU6050
  Wire.begin();
  
  // Initialize MPU6050
  if (!mpu.begin()) {
    return false;
  }
  
  // Configure MPU6050
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  
  // Initial display update
  updateDisplay();
  
  return true;
}

// Update the LED matrix display
void MatriXDeck::updateDisplay() {
  // For now, just a placeholder for the actual implementation
  // that would drive the LED matrix hardware
  
  digitalWrite(MATRIX_CS_PIN, LOW);
  
  // Send data to the LED matrix
  for (int y = 0; y < MATRIX_HEIGHT; y++) {
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      uint8_t pixelValue = displayBuffer[y * MATRIX_WIDTH + x];
      
      // Send pixel data (in actual implementation, this would 
      // use the appropriate protocol for the matrix hardware)
      digitalWrite(MATRIX_CLK_PIN, LOW);
      digitalWrite(MATRIX_DATA_PIN, pixelValue & 0x01); // Red bit
      digitalWrite(MATRIX_CLK_PIN, HIGH);
      
      digitalWrite(MATRIX_CLK_PIN, LOW);
      digitalWrite(MATRIX_DATA_PIN, (pixelValue & 0x02) >> 1); // Green bit
      digitalWrite(MATRIX_CLK_PIN, HIGH);
    }
  }
  
  digitalWrite(MATRIX_CS_PIN, HIGH);
}

// Clear the display buffer
void MatriXDeck::clearDisplay() {
  memset(displayBuffer, MATRIX_COLOR_OFF, MATRIX_WIDTH * MATRIX_HEIGHT);
}

// Set a pixel in the buffer
void MatriXDeck::setPixel(uint8_t x, uint8_t y, uint8_t color) {
  if (x >= MATRIX_WIDTH || y >= MATRIX_HEIGHT) {
    return;
  }
  
  displayBuffer[y * MATRIX_WIDTH + x] = color & 0x03;
}

// Draw a line in the buffer
void MatriXDeck::drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color) {
  // Bresenham line algorithm
  int dx = abs(x1 - x0);
  int dy = abs(y1 - y0);
  int sx = (x0 < x1) ? 1 : -1;
  int sy = (y0 < y1) ? 1 : -1;
  int err = dx - dy;
  
  while (true) {
    setPixel(x0, y0, color);
    
    if (x0 == x1 && y0 == y1) {
      break;
    }
    
    int e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dx) {
      err += dx;
      y0 += sy;
    }
  }
}

// Draw a rectangle in the buffer
void MatriXDeck::drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color) {
  drawLine(x, y, x+w-1, y, color);
  drawLine(x, y+h-1, x+w-1, y+h-1, color);
  drawLine(x, y, x, y+h-1, color);
  drawLine(x+w-1, y, x+w-1, y+h-1, color);
}

// Draw a filled rectangle in the buffer
void MatriXDeck::fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color) {
  for (int i = y; i < y + h; i++) {
    for (int j = x; j < x + w; j++) {
      setPixel(j, i, color);
    }
  }
}

// Draw a circle in the buffer
void MatriXDeck::drawCircle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color) {
  // Bresenham circle algorithm
  int x = r;
  int y = 0;
  int err = 0;

  while (x >= y) {
    setPixel(x0 + x, y0 + y, color);
    setPixel(x0 + y, y0 + x, color);
    setPixel(x0 - y, y0 + x, color);
    setPixel(x0 - x, y0 + y, color);
    setPixel(x0 - x, y0 - y, color);
    setPixel(x0 - y, y0 - x, color);
    setPixel(x0 + y, y0 - x, color);
    setPixel(x0 + x, y0 - y, color);

    y += 1;
    if (err <= 0) {
      err += 2 * y + 1;
    }
    if (err > 0) {
      x -= 1;
      err -= 2 * x + 1;
    }
  }
}

// Draw text in the buffer
void MatriXDeck::drawText(uint8_t x, uint8_t y, const char* text, uint8_t color, uint8_t size) {
  // This is a placeholder - actual implementation would use
  // a font rendering library (like Adafruit_GFX)
  
  // Simplified implementation for basic text rendering
  uint8_t cursor_x = x;
  uint8_t cursor_y = y;
  
  for (size_t i = 0; i < strlen(text); i++) {
    char c = text[i];
    
    // Very basic 3x5 font for each character
    // This would be replaced with a proper font library
    switch (c) {
      case 'A':
        drawLine(cursor_x, cursor_y+5, cursor_x+1, cursor_y, color);
        drawLine(cursor_x+1, cursor_y, cursor_x+2, cursor_y+5, color);
        drawLine(cursor_x, cursor_y+3, cursor_x+2, cursor_y+3, color);
        break;
      // Add more characters as needed
      default:
        // Draw a small box for unknown characters
        fillRect(cursor_x, cursor_y, 3, 5, color);
        break;
    }
    
    cursor_x += 4 * size; // Move cursor for next character
  }
}

// Read the state of a button
bool MatriXDeck::readButton(uint8_t button) {
  switch (button) {
    case 0: return !digitalRead(BUTTON_A_PIN);
    case 1: return !digitalRead(BUTTON_B_PIN);
    case 2: return !digitalRead(BUTTON_X_PIN);
    case 3: return !digitalRead(BUTTON_Y_PIN);
    case 4: return !digitalRead(JOYSTICK_BTN_PIN);
    default: return false;
  }
}

// Read the joystick position
int MatriXDeck::readJoystick(uint8_t axis) {
  if (axis == 0) {
    return analogRead(JOYSTICK_X_PIN);
  } else if (axis == 1) {
    return analogRead(JOYSTICK_Y_PIN);
  }
  return 0;
}

// Read accelerometer data
float MatriXDeck::readAccelerometer(uint8_t axis) {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  switch (axis) {
    case 0: return a.acceleration.x;
    case 1: return a.acceleration.y;
    case 2: return a.acceleration.z;
    default: return 0;
  }
}

// Read gyroscope data
float MatriXDeck::readGyroscope(uint8_t axis) {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  switch (axis) {
    case 0: return g.gyro.x * 57.295779513; // Convert to degrees/s
    case 1: return g.gyro.y * 57.295779513;
    case 2: return g.gyro.z * 57.295779513;
    default: return 0;
  }
}

// Play a tone on the speaker
void MatriXDeck::playTone(uint16_t frequency, uint16_t duration) {
  tone(SPEAKER_PIN, frequency, duration);
}

// Read the microphone level
int MatriXDeck::readMicrophone() {
  return analogRead(MIC_PIN);
} 