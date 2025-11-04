import time
import serial

class HapticController:
    def __init__(self, port='/dev/cu.usbmodem101', baudrate=115200):
        self.serial = serial.Serial(port, baudrate, timeout=1)
        print(f"Connected to {port} at {baudrate} baud")
        # Wait for Arduino to initialize
        time.sleep(2)

    def send_vibration_command(self, motor_id: int, intensity: float, duration_ms: int):
        """Send a vibration command to motor ID."""
        cmd = f"v:{motor_id}:{intensity}:{duration_ms}\n"
        self.serial.write(cmd.encode())
        
        # # Wait for response or timeout
        # response = self.serial.readline().decode().strip()
        # if response:
        #     print(f"Response: {response}")

    def send_pause(self, motor_id: int, duration_ms: int):
        """Send a pause command to a specific motor."""
        cmd = f"p:{motor_id}:{duration_ms}\n"
        self.serial.write(cmd.encode())

    def run_pattern(self, pattern: list):
        """Run a pattern of vibration steps and pauses."""
        for step in pattern:
            if step["type"] == "pause":
                time.sleep(step["duration"] / 1000)  # Convert ms to seconds
            elif step["type"] == "vibrate":
                self.send_vibration_command(step["motor"], step["intensity"], step["duration"])
                time.sleep(step["duration"] / 1000)

    def close(self):
        """Close the serial connection."""
        self.serial.close()

# Sample patterns
def left_to_right(num_motors: int, intensity: float = 1.0, duration: int = 1, pause_duration: int = 100):
    """Create a pattern that vibrates motors from left to right with pauses between steps."""
    pattern = []
    for i in range(1, num_motors + 1):
        pattern.append({"type": "vibrate", "motor": i, "intensity": intensity, "duration": duration})
        if i < num_motors:  # Don't add pause after the last vibration
            pattern.append({"type": "pause", "duration": pause_duration})
    return pattern

def right_to_left(num_motors: int, intensity: float = 1.0, duration: int = 1, pause_duration: int = 100):
    """Create a pattern that vibrates motors from right to left with pauses between steps."""
    pattern = []
    for i in range(num_motors, 0, -1):
        pattern.append({"type": "vibrate", "motor": i, "intensity": intensity, "duration": duration})
        if i > 1:  # Don't add pause after the last vibration
            pattern.append({"type": "pause", "duration": pause_duration})
    return pattern

def all_vibrate(num_motors: int, intensity: float = 1.0, duration: int = 1):
    """Create a pattern that vibrates all motors simultaneously."""
    pattern = []
    # First vibrate all motors
    for i in range(1, num_motors + 1):
        pattern.append({"type": "vibrate", "motor": i, "intensity": intensity, "duration": duration})
    return pattern

def confirm(motor: int, intensity: float = 1.0, duration: int = 1, gap: int = 100):
    """Double-tap pattern to confirm an action."""
    return [
        {"type": "vibrate", "motor": motor, "intensity": intensity, "duration": duration},
        {"type": "pause", "duration": gap},
        {"type": "vibrate", "motor": motor, "intensity": intensity, "duration": duration}
    ]

def cancel(motor: int, intensity: float = 1.0, duration: int = 300):
    """Strong pulse fade to signify cancellation or negation."""
    return [
        {"type": "vibrate", "motor": motor, "intensity": intensity, "duration": duration},
        {"type": "pause", "duration": 200},
        {"type": "vibrate", "motor": motor, "intensity": intensity * 0.5, "duration": duration},
        {"type": "pause", "duration": 200},
        {"type": "vibrate", "motor": motor, "intensity": intensity * 0.25, "duration": duration}
    ]


# Example usage
if __name__ == "__main__":
    try:
        controller = HapticController()
        
        # Run sample patterns
        num_motors = 4
        
        controller.run_pattern(left_to_right(num_motors, pause_duration=200))
        controller.run_pattern(right_to_left(num_motors, pause_duration=200))
        controller.run_pattern(all_vibrate(num_motors))
        
    except KeyboardInterrupt:
        pass
    finally:
        controller.close() 
