"""
MatriXDeck MicroPython Library

A library for controlling the MatriXDeck LED matrix hardware from MicroPython.

Created by MatriXDeck Team, 2023
Released under MIT License
"""

import machine
import time
from micropython import const

# Pin definitions
MATRIX_DATA_PIN = const(23)
MATRIX_CLK_PIN = const(18)
MATRIX_CS_PIN = const(5)
BUTTON_A_PIN = const(32)
BUTTON_B_PIN = const(33)
BUTTON_X_PIN = const(25)
BUTTON_Y_PIN = const(26)
JOYSTICK_X_PIN = const(34)
JOYSTICK_Y_PIN = const(35)
JOYSTICK_BTN_PIN = const(27)
SPEAKER_PIN = const(19)
MIC_PIN = const(36)

# Matrix dimensions
MATRIX_WIDTH = const(32)
MATRIX_HEIGHT = const(16)

# Colors
MATRIX_COLOR_OFF = const(0)
MATRIX_COLOR_RED = const(1)
MATRIX_COLOR_GREEN = const(2)
MATRIX_COLOR_AMBER = const(3)

class MatriXDeck:
    """
    Main class for controlling the MatriXDeck hardware
    """
    
    def __init__(self):
        """Initialize MatriXDeck instance with default settings"""
        self.display_buffer = bytearray(MATRIX_WIDTH * MATRIX_HEIGHT)
        
        # Initialize pins
        self.matrix_data = machine.Pin(MATRIX_DATA_PIN, machine.Pin.OUT)
        self.matrix_clk = machine.Pin(MATRIX_CLK_PIN, machine.Pin.OUT)
        self.matrix_cs = machine.Pin(MATRIX_CS_PIN, machine.Pin.OUT)
        
        self.button_a = machine.Pin(BUTTON_A_PIN, machine.Pin.IN, machine.Pin.PULL_UP)
        self.button_b = machine.Pin(BUTTON_B_PIN, machine.Pin.IN, machine.Pin.PULL_UP)
        self.button_x = machine.Pin(BUTTON_X_PIN, machine.Pin.IN, machine.Pin.PULL_UP)
        self.button_y = machine.Pin(BUTTON_Y_PIN, machine.Pin.IN, machine.Pin.PULL_UP)
        self.joystick_btn = machine.Pin(JOYSTICK_BTN_PIN, machine.Pin.IN, machine.Pin.PULL_UP)
        
        self.joystick_x = machine.ADC(machine.Pin(JOYSTICK_X_PIN))
        self.joystick_x.atten(machine.ADC.ATTN_11DB)  # Full range: 0-3.3V
        
        self.joystick_y = machine.ADC(machine.Pin(JOYSTICK_Y_PIN))
        self.joystick_y.atten(machine.ADC.ATTN_11DB)  # Full range: 0-3.3V
        
        self.mic = machine.ADC(machine.Pin(MIC_PIN))
        self.mic.atten(machine.ADC.ATTN_11DB)
        
        self.speaker_pwm = machine.PWM(machine.Pin(SPEAKER_PIN))
        self.speaker_pwm.deinit()  # Start with speaker off
        
        # Initialize I2C for MPU6050
        self.i2c = machine.I2C(0, scl=machine.Pin(22), sda=machine.Pin(21))
        
        try:
            from mpu6050 import MPU6050
            self.mpu = MPU6050(self.i2c)
            self.has_mpu = True
        except ImportError:
            self.has_mpu = False
            print("MPU6050 module not found. Motion sensing disabled.")
    
    def begin(self):
        """Initialize hardware and clear display"""
        self.clear_display()
        self.update_display()
        return True
    
    def update_display(self):
        """Update the LED matrix with current buffer contents"""
        self.matrix_cs.value(0)
        
        # Send data to the LED matrix
        for y in range(MATRIX_HEIGHT):
            for x in range(MATRIX_WIDTH):
                pixel_value = self.display_buffer[y * MATRIX_WIDTH + x]
                
                # Send red bit
                self.matrix_clk.value(0)
                self.matrix_data.value(pixel_value & 0x01)
                self.matrix_clk.value(1)
                
                # Send green bit
                self.matrix_clk.value(0)
                self.matrix_data.value((pixel_value & 0x02) >> 1)
                self.matrix_clk.value(1)
        
        self.matrix_cs.value(1)
    
    def clear_display(self):
        """Clear the display buffer"""
        for i in range(len(self.display_buffer)):
            self.display_buffer[i] = MATRIX_COLOR_OFF
    
    def set_pixel(self, x, y, color):
        """Set a pixel in the buffer"""
        if x < 0 or x >= MATRIX_WIDTH or y < 0 or y >= MATRIX_HEIGHT:
            return
        
        self.display_buffer[y * MATRIX_WIDTH + x] = color & 0x03
    
    def draw_line(self, x0, y0, x1, y1, color):
        """Draw a line in the buffer using Bresenham's algorithm"""
        dx = abs(x1 - x0)
        dy = abs(y1 - y0)
        sx = 1 if x0 < x1 else -1
        sy = 1 if y0 < y1 else -1
        err = dx - dy
        
        while True:
            self.set_pixel(x0, y0, color)
            
            if x0 == x1 and y0 == y1:
                break
            
            e2 = 2 * err
            if e2 > -dy:
                err -= dy
                x0 += sx
            if e2 < dx:
                err += dx
                y0 += sy
    
    def draw_rect(self, x, y, w, h, color):
        """Draw a rectangle outline"""
        self.draw_line(x, y, x+w-1, y, color)
        self.draw_line(x, y+h-1, x+w-1, y+h-1, color)
        self.draw_line(x, y, x, y+h-1, color)
        self.draw_line(x+w-1, y, x+w-1, y+h-1, color)
    
    def fill_rect(self, x, y, w, h, color):
        """Draw a filled rectangle"""
        for i in range(y, y+h):
            for j in range(x, x+w):
                self.set_pixel(j, i, color)
    
    def draw_circle(self, x0, y0, r, color):
        """Draw a circle outline using Bresenham's algorithm"""
        x = r
        y = 0
        err = 0
        
        while x >= y:
            self.set_pixel(x0 + x, y0 + y, color)
            self.set_pixel(x0 + y, y0 + x, color)
            self.set_pixel(x0 - y, y0 + x, color)
            self.set_pixel(x0 - x, y0 + y, color)
            self.set_pixel(x0 - x, y0 - y, color)
            self.set_pixel(x0 - y, y0 - x, color)
            self.set_pixel(x0 + y, y0 - x, color)
            self.set_pixel(x0 + x, y0 - y, color)
            
            y += 1
            if err <= 0:
                err += 2 * y + 1
            if err > 0:
                x -= 1
                err -= 2 * x + 1
    
    def draw_text(self, x, y, text, color, size=1):
        """
        Draw text on the display
        Very simple implementation with basic 3x5 font
        """
        cursor_x = x
        cursor_y = y
        
        # Very basic character definitions (3x5 pixels)
        # Only for a subset of characters
        chars = {
            'A': [
                [0, 1, 0],
                [1, 0, 1],
                [1, 1, 1],
                [1, 0, 1],
                [1, 0, 1]
            ],
            'B': [
                [1, 1, 0],
                [1, 0, 1],
                [1, 1, 0],
                [1, 0, 1],
                [1, 1, 0]
            ],
            # Add more characters as needed
        }
        
        for char in text:
            if char in chars:
                char_pattern = chars[char]
                for cy in range(5):
                    for cx in range(3):
                        if char_pattern[cy][cx]:
                            if size == 1:
                                self.set_pixel(cursor_x + cx, cursor_y + cy, color)
                            else:
                                self.fill_rect(cursor_x + cx*size, cursor_y + cy*size, size, size, color)
            else:
                # Unknown character, draw a small box
                self.fill_rect(cursor_x, cursor_y, 3*size, 5*size, color)
            
            cursor_x += (4 * size)  # Character width plus spacing
    
    def read_button(self, button):
        """Read the state of a button (True if pressed)"""
        if button == 0:
            return not self.button_a.value()
        elif button == 1:
            return not self.button_b.value()
        elif button == 2:
            return not self.button_x.value()
        elif button == 3:
            return not self.button_y.value()
        elif button == 4:
            return not self.joystick_btn.value()
        return False
    
    def read_joystick(self, axis):
        """Read the joystick position (0-4095)"""
        if axis == 0:
            return self.joystick_x.read()
        elif axis == 1:
            return self.joystick_y.read()
        return 0
    
    def read_accelerometer(self, axis):
        """Read accelerometer data"""
        if not self.has_mpu:
            return 0
        
        accel = self.mpu.get_accel_data()
        if axis == 0:
            return accel['x']
        elif axis == 1:
            return accel['y']
        elif axis == 2:
            return accel['z']
        return 0
    
    def read_gyroscope(self, axis):
        """Read gyroscope data"""
        if not self.has_mpu:
            return 0
        
        gyro = self.mpu.get_gyro_data()
        if axis == 0:
            return gyro['x']
        elif axis == 1:
            return gyro['y']
        elif axis == 2:
            return gyro['z']
        return 0
    
    def play_tone(self, frequency, duration):
        """Play a tone on the speaker"""
        try:
            self.speaker_pwm = machine.PWM(machine.Pin(SPEAKER_PIN))
            self.speaker_pwm.freq(frequency)
            self.speaker_pwm.duty(512)  # 50% duty cycle
            time.sleep_ms(duration)
            self.speaker_pwm.deinit()
        except Exception as e:
            print("Error playing tone:", e)
    
    def read_microphone(self):
        """Read the microphone level (0-4095)"""
        return self.mic.read() 