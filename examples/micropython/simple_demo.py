"""
MatriXDeck - Simple MicroPython Demo

This example demonstrates basic functionality of the MatriXDeck hardware:
- Display graphics on the LED matrix
- Read button presses
- Read joystick position
- Use motion sensor
- Make sounds

Created by MatriXDeck Team, 2023
Released under MIT License
"""

import time
from matrixdeck import MatriXDeck, MATRIX_COLOR_RED, MATRIX_COLOR_GREEN, MATRIX_COLOR_AMBER

# Create MatriXDeck instance
deck = MatriXDeck()

# Variables to store current state
mode = 0          # Current display mode
last_button_state = False  # Last button state for detecting presses
last_update = 0  # Time of last update

def setup():
    print("MatriXDeck Simple Demo")
    
    # Initialize the MatriXDeck
    if not deck.begin():
        print("Failed to initialize MatriXDeck. Check connections.")
        return False
    
    print("MatriXDeck initialized successfully!")
    
    # Play startup sound
    deck.play_tone(440, 100)  # A4
    time.sleep_ms(150)
    deck.play_tone(554, 100)  # C#5
    time.sleep_ms(150)
    deck.play_tone(659, 300)  # E5
    
    # Show welcome message
    deck.clear_display()
    deck.draw_text(1, 5, "HELLO", MATRIX_COLOR_GREEN)
    deck.update_display()
    time.sleep_ms(2000)
    
    return True

def loop():
    global mode, last_button_state, last_update
    
    # Check buttons for mode change
    current_button_state = deck.read_button(0)  # Button A
    if current_button_state and not last_button_state:  # Button A pressed
        mode = (mode + 1) % 5  # Cycle through modes
        deck.play_tone(330, 50)  # Play a tone on button press
        print("Switched to mode:", mode)
    last_button_state = current_button_state
    
    # Update display based on current mode
    current_time = time.ticks_ms()
    if time.ticks_diff(current_time, last_update) > 50:  # Update every 50ms
        last_update = current_time
        
        # Clear the display first
        deck.clear_display()
        
        # Display content based on current mode
        if mode == 0:
            draw_bouncing_ball()
        elif mode == 1:
            draw_joystick_position()
        elif mode == 2:
            draw_motion_data()
        elif mode == 3:
            draw_audio_level()
        elif mode == 4:
            draw_button_status()
        
        # Update the display
        deck.update_display()

# Bouncing ball animation variables
ball_x = 16.0
ball_y = 8.0
vx = 0.3
vy = 0.2

def draw_bouncing_ball():
    global ball_x, ball_y, vx, vy
    
    # Move the ball
    ball_x += vx
    ball_y += vy
    
    # Bounce off edges
    if ball_x < 1 or ball_x > 30:
        vx = -vx
        deck.play_tone(220, 10)  # Play a bounce sound
    if ball_y < 1 or ball_y > 14:
        vy = -vy
        deck.play_tone(330, 10)  # Play a bounce sound
    
    # Draw the ball
    deck.draw_circle(int(ball_x), int(ball_y), 2, MATRIX_COLOR_RED)
    
    # Add text label for this mode
    deck.draw_text(1, 1, "BALL", MATRIX_COLOR_GREEN)

def draw_joystick_position():
    # Read joystick values (0-4095)
    joy_x = deck.read_joystick(0)
    joy_y = deck.read_joystick(1)
    
    # Map to display coordinates (adjust based on your joystick's range)
    x = int(joy_x * 31 / 4095)
    y = int(joy_y * 15 / 4095)
    
    # Draw a crosshair at the joystick position
    deck.draw_line(x, 0, x, 15, MATRIX_COLOR_GREEN)
    deck.draw_line(0, y, 31, y, MATRIX_COLOR_GREEN)
    deck.fill_rect(x-1, y-1, 3, 3, MATRIX_COLOR_RED)
    
    # Add text label for this mode
    deck.draw_text(1, 1, "JOY", MATRIX_COLOR_AMBER)

def draw_motion_data():
    # Read accelerometer values
    ax = deck.read_accelerometer(0)
    ay = deck.read_accelerometer(1)
    
    # Map acceleration to display coordinates
    x = int(16 + ax * 2)
    y = int(8 + ay * 2)
    
    # Constrain to display bounds
    x = max(0, min(31, x))
    y = max(0, min(15, y))
    
    # Draw a dot representing the tilt
    deck.fill_rect(x-1, y-1, 3, 3, MATRIX_COLOR_RED)
    
    # Draw a box around the edge
    deck.draw_rect(0, 0, 32, 16, MATRIX_COLOR_GREEN)
    
    # Add text label for this mode
    deck.draw_text(1, 1, "MPU", MATRIX_COLOR_GREEN)

def draw_audio_level():
    # Read microphone level
    mic_level = deck.read_microphone()
    
    # Map to a number of bars to display
    num_bars = int(mic_level * 30 / 4095)
    
    # Draw the level meter
    for i in range(num_bars):
        color = MATRIX_COLOR_GREEN
        if i > 20:
            color = MATRIX_COLOR_RED
        elif i > 10:
            color = MATRIX_COLOR_AMBER
        
        deck.draw_line(i + 1, 15, i + 1, 11, color)
    
    # Add text label for this mode
    deck.draw_text(1, 1, "MIC", MATRIX_COLOR_GREEN)

def draw_button_status():
    # Check all buttons
    btn_a = deck.read_button(0)
    btn_b = deck.read_button(1)
    btn_x = deck.read_button(2)
    btn_y = deck.read_button(3)
    btn_joy = deck.read_button(4)
    
    # Draw button states
    deck.fill_rect(4, 4, 4, 4, MATRIX_COLOR_RED if btn_a else MATRIX_COLOR_GREEN)
    deck.fill_rect(24, 4, 4, 4, MATRIX_COLOR_RED if btn_b else MATRIX_COLOR_GREEN)
    deck.fill_rect(4, 11, 4, 4, MATRIX_COLOR_RED if btn_x else MATRIX_COLOR_GREEN)
    deck.fill_rect(24, 11, 4, 4, MATRIX_COLOR_RED if btn_y else MATRIX_COLOR_GREEN)
    deck.fill_rect(14, 7, 4, 4, MATRIX_COLOR_RED if btn_joy else MATRIX_COLOR_GREEN)
    
    # Add labels
    deck.draw_text(1, 1, "BTN", MATRIX_COLOR_AMBER)

# Initialize the demo
if setup():
    # Main loop
    try:
        while True:
            loop()
            time.sleep_ms(10)  # Small delay to prevent hogging the CPU
    except KeyboardInterrupt:
        print("Demo stopped")
    finally:
        # Clean up
        deck.clear_display()
        deck.update_display() 