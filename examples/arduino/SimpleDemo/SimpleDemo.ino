/**
 * MatriXDeck - Simple Demo
 * 
 * This example demonstrates basic functionality of the MatriXDeck hardware:
 * - Display graphics on the LED matrix
 * - Read button presses
 * - Read joystick position
 * - Use motion sensor
 * - Make sounds
 * 
 * Created by MatriXDeck Team, 2023
 * Released under MIT License
 */

#include <MatriXDeck.h>

// Create MatriXDeck instance
MatriXDeck deck;

// Variables to store current state
int mode = 0;          // Current display mode
int lastButtonState = 0;  // Last button state for detecting presses
unsigned long lastUpdate = 0;  // Time of last update

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  Serial.println("MatriXDeck Simple Demo");
  
  // Initialize the MatriXDeck
  if (!deck.begin()) {
    Serial.println("Failed to initialize MatriXDeck. Check connections.");
    while (1);  // Halt if initialization failed
  }
  
  Serial.println("MatriXDeck initialized successfully!");
  
  // Play startup sound
  deck.playTone(440, 100);  // A4
  delay(150);
  deck.playTone(554, 100);  // C#5
  delay(150);
  deck.playTone(659, 300);  // E5
  
  // Show welcome message
  deck.clearDisplay();
  deck.drawText(1, 5, "HELLO", MATRIX_COLOR_GREEN);
  deck.updateDisplay();
  delay(2000);
}

void loop() {
  // Check buttons for mode change
  if (deck.readButton(0) && !lastButtonState) {  // Button A pressed
    lastButtonState = 1;
    mode = (mode + 1) % 5;  // Cycle through modes
    deck.playTone(330, 50);  // Play a tone on button press
    Serial.print("Switched to mode: ");
    Serial.println(mode);
  } else if (!deck.readButton(0) && lastButtonState) {
    lastButtonState = 0;  // Button released
  }
  
  // Update display based on current mode
  unsigned long currentTime = millis();
  if (currentTime - lastUpdate > 50) {  // Update every 50ms
    lastUpdate = currentTime;
    
    // Clear the display first
    deck.clearDisplay();
    
    // Display content based on current mode
    switch (mode) {
      case 0:
        drawBouncingBall();
        break;
      case 1:
        drawJoystickPosition();
        break;
      case 2:
        drawMotionData();
        break;
      case 3:
        drawAudioLevel();
        break;
      case 4:
        drawButtonStatus();
        break;
    }
    
    // Update the display
    deck.updateDisplay();
  }
}

// Draw a bouncing ball animation
void drawBouncingBall() {
  static float x = 16;
  static float y = 8;
  static float vx = 0.3;
  static float vy = 0.2;
  
  // Move the ball
  x += vx;
  y += vy;
  
  // Bounce off edges
  if (x < 1 || x > MATRIX_WIDTH - 2) {
    vx = -vx;
    deck.playTone(220, 10);  // Play a bounce sound
  }
  if (y < 1 || y > MATRIX_HEIGHT - 2) {
    vy = -vy;
    deck.playTone(330, 10);  // Play a bounce sound
  }
  
  // Draw the ball
  deck.drawCircle(x, y, 2, MATRIX_COLOR_RED);
  
  // Add text label for this mode
  deck.drawText(1, 1, "BALL", MATRIX_COLOR_GREEN);
}

// Draw a visualization of the joystick position
void drawJoystickPosition() {
  // Read joystick values (0-1023)
  int joyX = deck.readJoystick(0);
  int joyY = deck.readJoystick(1);
  
  // Map to display coordinates
  int x = map(joyX, 0, 1023, 0, MATRIX_WIDTH - 1);
  int y = map(joyY, 0, 1023, 0, MATRIX_HEIGHT - 1);
  
  // Draw a crosshair at the joystick position
  deck.drawLine(x, 0, x, MATRIX_HEIGHT - 1, MATRIX_COLOR_GREEN);
  deck.drawLine(0, y, MATRIX_WIDTH - 1, y, MATRIX_COLOR_GREEN);
  deck.fillRect(x-1, y-1, 3, 3, MATRIX_COLOR_RED);
  
  // Add text label for this mode
  deck.drawText(1, 1, "JOY", MATRIX_COLOR_AMBER);
}

// Display motion sensor data
void drawMotionData() {
  // Read accelerometer values
  float ax = deck.readAccelerometer(0);
  float ay = deck.readAccelerometer(1);
  
  // Map acceleration to display coordinates
  int x = constrain(MATRIX_WIDTH / 2 + ax * 2, 0, MATRIX_WIDTH - 1);
  int y = constrain(MATRIX_HEIGHT / 2 + ay * 2, 0, MATRIX_HEIGHT - 1);
  
  // Draw a dot representing the tilt
  deck.fillRect(x-1, y-1, 3, 3, MATRIX_COLOR_RED);
  
  // Draw a box around the edge
  deck.drawRect(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_COLOR_GREEN);
  
  // Add text label for this mode
  deck.drawText(1, 1, "MPU", MATRIX_COLOR_GREEN);
}

// Display audio level meter
void drawAudioLevel() {
  // Read microphone level
  int micLevel = deck.readMicrophone();
  
  // Map to a number of bars to display
  int numBars = map(micLevel, 0, 1023, 0, MATRIX_WIDTH - 2);
  
  // Draw the level meter
  for (int i = 0; i < numBars; i++) {
    int color = MATRIX_COLOR_GREEN;
    if (i > (MATRIX_WIDTH - 2) * 0.7) color = MATRIX_COLOR_RED;
    else if (i > (MATRIX_WIDTH - 2) * 0.3) color = MATRIX_COLOR_AMBER;
    
    deck.drawLine(i + 1, MATRIX_HEIGHT - 1, i + 1, MATRIX_HEIGHT - 5, color);
  }
  
  // Add text label for this mode
  deck.drawText(1, 1, "MIC", MATRIX_COLOR_GREEN);
}

// Display button status
void drawButtonStatus() {
  // Check all buttons
  bool btnA = deck.readButton(0);
  bool btnB = deck.readButton(1);
  bool btnX = deck.readButton(2);
  bool btnY = deck.readButton(3);
  bool btnJoy = deck.readButton(4);
  
  // Draw button states
  deck.fillRect(4, 4, 4, 4, btnA ? MATRIX_COLOR_RED : MATRIX_COLOR_GREEN);
  deck.fillRect(24, 4, 4, 4, btnB ? MATRIX_COLOR_RED : MATRIX_COLOR_GREEN);
  deck.fillRect(4, 11, 4, 4, btnX ? MATRIX_COLOR_RED : MATRIX_COLOR_GREEN);
  deck.fillRect(24, 11, 4, 4, btnY ? MATRIX_COLOR_RED : MATRIX_COLOR_GREEN);
  deck.fillRect(14, 7, 4, 4, btnJoy ? MATRIX_COLOR_RED : MATRIX_COLOR_GREEN);
  
  // Add labels
  deck.drawText(1, 1, "BTN", MATRIX_COLOR_AMBER);
} 