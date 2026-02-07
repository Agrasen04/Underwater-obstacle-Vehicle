/*************************************************************
 * * Project: AquaStrider ROV Control
 * Author: Tuesday PG2
 * Date: October 13, 2025
 * * This code adapts a previous 3-motor car project to control
 * a 3-thruster underwater ROV using Blynk.
 * * Motor 1 (Right Thruster): GPIO 4, 5
 * Motor 2 (Left Thruster):  GPIO 12, 13
 * Motor 3 (Vertical Thruster): GPIO 16, 17
 * *************************************************************/

// --- Blynk Credentials ---
#define BLYNK_TEMPLATE_ID "TMPL3KWGpgdwx"
#define BLYNK_TEMPLATE_NAME "AquaStrider UnderWaterROV"
#define BLYNK_AUTH_TOKEN "qmzd428RzTnnn43trfFtT1HJdp7Lm78d"

#define BLYNK_PRINT Serial

// --- Libraries ---
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// --- WiFi Credentials ---
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "IITRPR";
char pass[] = "V#6qF?pyM!bQ$%NX";

// --- Pin Definitions ---

// Motor 1: Right Horizontal Thruster (L298N Driver 1, Outputs 1 & 2)
int RIGHT_THRUSTER_FWD = 5;  // IN2
int RIGHT_THRUSTER_REV = 4;  // IN1

// Motor 2: Left Horizontal Thruster (L298N Driver 1, Outputs 3 & 4)
int LEFT_THRUSTER_FWD = 13; // IN4
int LEFT_THRUSTER_REV = 12; // IN3

// Motor 3: Vertical Thruster (L298N Driver 2, Outputs 1 & 2)
int VERTICAL_THRUSTER_UP   = 17; // IN5 
int VERTICAL_THRUSTER_DOWN = 16; // IN6 


// --- Blynk Virtual Pin Handlers ---
// V0: Move Forward
// Both horizontal thrusters push forward
BLYNK_WRITE(V0) { 
  Serial.println("V0: Move Forward");
  digitalWrite(RIGHT_THRUSTER_FWD, param.asInt());
  digitalWrite(LEFT_THRUSTER_FWD,  param.asInt());
}

// V1: Move Backward
// Both horizontal thrusters push backward (reverse)
BLYNK_WRITE(V1) { 
  Serial.println("V1: Move Backward");
  digitalWrite(RIGHT_THRUSTER_REV, param.asInt());
  digitalWrite(LEFT_THRUSTER_REV,  param.asInt());
}

// V2: Turn Left
// Right thruster pushes forward, Left thruster pushes backward
BLYNK_WRITE(V2) {
  Serial.println("V2: Turn Left");
  digitalWrite(RIGHT_THRUSTER_FWD, param.asInt());
  digitalWrite(LEFT_THRUSTER_REV,  param.asInt());
}

// V3: Turn Right
// Left thruster pushes forward, Right thruster pushes backward
BLYNK_WRITE(V3) { 
  Serial.println("V3: Turn Right");
  digitalWrite(LEFT_THRUSTER_FWD,  param.asInt());
  digitalWrite(RIGHT_THRUSTER_REV, param.asInt());
}

// V4: Move Up (Ascend)
// Vertical thruster pushes water down (lifting ROV up)
BLYNK_WRITE(V4) { 
  Serial.println("V4: Move Up (Ascend)");
  digitalWrite(VERTICAL_THRUSTER_UP, param.asInt());
}

// V5: Move Down (Descend)
// Vertical thruster pushes water up (pulling ROV down)
BLYNK_WRITE(V5) { 
  Serial.println("V5: Move Down (Descend)");
  digitalWrite(VERTICAL_THRUSTER_DOWN, param.asInt());
}

// --- Main Setup ---
void setup()
{
  // Start Serial Monitor for debugging
  Serial.begin(115200);
  Serial.println("AquaStrider ROV Booting...");

  // Set all motor control pins to OUTPUT
  pinMode(RIGHT_THRUSTER_FWD, OUTPUT);
  pinMode(RIGHT_THRUSTER_REV, OUTPUT);
  pinMode(LEFT_THRUSTER_FWD,  OUTPUT);
  pinMode(LEFT_THRUSTER_REV,  OUTPUT);
  pinMode(VERTICAL_THRUSTER_UP,   OUTPUT);
  pinMode(VERTICAL_THRUSTER_DOWN, OUTPUT);

  // Ensure all motors are off at startup
  digitalWrite(RIGHT_THRUSTER_FWD, LOW);
  digitalWrite(RIGHT_THRUSTER_REV, LOW);
  digitalWrite(LEFT_THRUSTER_FWD,  LOW);
  digitalWrite(LEFT_THRUSTER_REV,  LOW);
  digitalWrite(VERTICAL_THRUSTER_UP,   LOW);
  digitalWrite(VERTICAL_THRUSTER_DOWN, LOW);
  
  // Connect to Blynk
  Blynk.begin(auth, ssid, pass);
  Serial.println("Connected to Blynk!");
}

// --- Main Loop ---
void loop()
{
  Blynk.run();
}