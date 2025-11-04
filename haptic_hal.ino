#include <Arduino.h>

// Configuration
const int NUM_MOTORS = 4;
const int MOTOR_PINS[NUM_MOTORS] = {3, 5, 6, 9};  // PWM-capable pins
const int SERIAL_BAUD = 115200;

// Structure to track active vibration events

struct VibeEvent {
    int motor_id;      // 1-4
    float intensity;   // 0.0-1.0
    unsigned long end_time;  // millis() when vibration should stop
    bool active;       // whether this event is currently active
};

// Array to track active vibration events
VibeEvent active_events[NUM_MOTORS];

// Function declarations
void parseCommand(const String& cmd);
void startVibration(int motor_id, float intensity, unsigned long duration_ms);
void stopVibration(int motor_id);
void updateActiveVibrations();

void setup() {
    // Initialize serial
    Serial.begin(SERIAL_BAUD);
    while (!Serial) {
        ; // wait for serial port to connect
    }
    
    // Initialize motor pins
    for (int i = 0; i < NUM_MOTORS; i++) {
        pinMode(MOTOR_PINS[i], OUTPUT);
        digitalWrite(MOTOR_PINS[i], LOW);
    }
    
    // Initialize event array
    for (int i = 0; i < NUM_MOTORS; i++) {
        active_events[i].motor_id = i + 1;
        active_events[i].active = false;
    }
    
    Serial.println("Haptic HAL Ready");
}

void loop() {
    // Check for incoming commands
    if (Serial.available()) {
        String cmd = Serial.readStringUntil('\n');
        parseCommand(cmd);
    }
    
    // Update active vibrations
    updateActiveVibrations();
}

void parseCommand(const String& cmd) {
    // Check if command starts with 'v:'
    if (!cmd.startsWith("v:")) {
        Serial.println("Error: Invalid command format.);
        return;
    }
    
    // Parse command components
    int motor_id = cmd.substring(2).toInt();
    int intensity_start = cmd.indexOf(':', 2) + 1;
    int duration_start = cmd.indexOf(':', intensity_start) + 1;
    
    if (motor_id < 1 || motor_id > NUM_MOTORS) {
        Serial.println("Error: Invalid motor ID");
        return;
    }
    
    float intensity = cmd.substring(intensity_start, duration_start - 1).toFloat();
    unsigned long duration_ms = cmd.substring(duration_start).toInt();
    
    // Validate intensity
    if (intensity < 0.0 || intensity > 1.0) {
        Serial.println("Error: Intensity out of range");
        return;
    }
    
    // Start vibration
    startVibration(motor_id, intensity, duration_ms);
}

void startVibration(int motor_id, float intensity, unsigned long duration_ms) {
    // Convert motor_id (1-4) to array index (0-3)
    int idx = motor_id - 1;
    
    // Calculate PWM value (0-255)
    int pwm_value = (int)(intensity * 255);
    
    // Set up new vibration event
    active_events[idx].intensity = intensity;
    active_events[idx].end_time = millis() + duration_ms;
    active_events[idx].active = true;
    
    // Start motor
    digitalWrite(MOTOR_PINS[idx], pwm_value);
}

void stopVibration(int motor_id) {
    int idx = motor_id - 1;
    active_events[idx].active = false;
    digitalWrite(MOTOR_PINS[idx], 0);
}

void updateActiveVibrations() {
    unsigned long current_time = millis();
    
    // Check each motor for expired vibrations
    for (int i = 0; i < NUM_MOTORS; i++) {
        if (active_events[i].active && current_time >= active_events[i].end_time) {
            stopVibration(active_events[i].motor_id);
        }
    }
} 