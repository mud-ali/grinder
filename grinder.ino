#include <Servo.h>

// Sensor default value
int val = LOW;

//pins for components
const int sensor = 9;
const int led = 13;
const int GRINDER_PIN = 7;
const int PUSHER_PIN = 3;

//references to servos
Servo pusher;
Servo grinder;

const int PUSHER_MOVE_TIME = 660;
const int GRIND_INCREMENT = 2000;
const int GRIND_COUNT = 3;

void setup() {
    Serial.begin(9600);
    pinMode(led, OUTPUT);
    pinMode(sensor, INPUT);
    pusher.attach(PUSHER_PIN);
    grinder.attach(GRINDER_PIN);
    pusher.write(92);
    grinder.write(0);
}

void loop() {
    val = digitalRead(sensor);

    //using LED for debugging
    digitalWrite(led, val);

    if (val == 1) {
        grind();
        pusher.write(92);
        grinder.write(0);
    }
}

void grind() {
    //start pushing
    pusher.write(180);
    delay(PUSHER_MOVE_TIME);
    
    //stop pushing
    pusher.write(92);
    Serial.println("pusher reached bottom");
    
    //start grinding
    for (int i=0;i<GRIND_COUNT;i++) {
        //switch directions every turn 
        grinder.write(i % 2 == 0 ? 180: 90); 
        delay(GRIND_INCREMENT);
        Serial.println("grinder grinded "+String(i)+" times");
    }
    
    //once grinding is done, bring pusher back up
    pusher.write(0);

    //working against friction + gravity
    //so we need to turn the servo a little longer
    delay(PUSHER_MOVE_TIME + 100);
    pusher.write(92);
    Serial.println("pusher reached top"); 
    val = LOW;
}