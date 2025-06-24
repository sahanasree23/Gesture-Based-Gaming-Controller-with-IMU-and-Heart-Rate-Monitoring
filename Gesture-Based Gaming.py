from serial import Serial
from pynput.keyboard import Controller, Key
import time
arduino_port = "COM9" # Replace with your Arduino's port
baud_rate = 9600
keyboard = Controller()
# Sensitivity and thresholds
tilt_threshold = 8000 # Threshold for accelerometer tilt
jump_threshold = 15000 # Threshold for Z-axis acceleration
# Connect to Arduino
try:
 arduino = Serial(arduino_port, baud_rate, timeout=1)
 time.sleep(2) # Allow time for connection
 print(f"Connected to Arduino on {arduino_port}")
except Exception as e:
 print(f"Could not connect to Arduino: {e}")
 exit()
def parse_serial_data(data):
 """
 Parse the serial data received from Arduino.
 """
 try:
 # Split data into components
 parts = data.split("|")
 ax = int(parts[0].split(":")[1])
 ay = int(parts[1].split(":")[1])
 az = int(parts[2].split(":")[1])
 return ax, ay, az
 except Exception as e:
 print(f"Error parsing data: {e}")
 return None, None, None
while True:
 if arduino.in_waiting > 0: # Check if data is available
 data = arduino.readline().decode('utf-8').strip()
 ax, ay, az = parse_serial_data(data) # Call to parse the data
 # Print accelerometer and heart rate data
 if ax is not None and ay is not None and az is not None:
if ax > tilt_threshold:
 keyboard.press("w") # Forward
 else:
 keyboard.release("w")
 if ax < -tilt_threshold:
 keyboard.press("s") # Backward
 else:
 keyboard.release("s")
 if ay > tilt_threshold:
 keyboard.press("a") # Left
 else:
 keyboard.release("a")
 if ay < -tilt_threshold:
 keyboard.press("d") # Right
 else:
 keyboard.release("d")
 # Map Z-axis tilt to jump
 if az > jump_threshold:
 keyboard.press(Key.space) # Jump
 else:
 keyboard.release(Key.space)
