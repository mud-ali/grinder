#include <Servo.h>

// Sensor default value
int val = 0;

//pins for components
const int sensor = 9;
const int led = 13;
const int GRINDER_PIN = 7
const int PUSHER_PIN = 3

//references to servos
Servo pusher;
Servo grinder;

//the following values are, ironically, subject to change
const int PUSHER_MOVE_TIME = 1000;
const int GRIND_INCREMENT = 2000;
const int GRIND_COUNT = 5;

void setup() {
    Serial.begin(9600);
    pinMode(led, OUTPUT);
    pinMode(sensor, INPUT);
    pusher.attach(PUSHER_PIN);
    grinder.attach(GRINDER_PIN);
}

void loop(){
    val = digitalRead(sensor);
    //using LED for testing
    digitalWrite(led, val);
    
    if (val == HIGH) {
        //TODO: figure out timing function (or math it based on height of model)
        
        //start pushing
        pusher.write(180);//adjust speed
        delay(PUSHER_MOVE_TIME);
        
        //stop pushing
        pusher.write(90);
        Serial.println("pusher reached bottom");
        
        //start grinding
        for(int i=0;i<GRIND_COUNT;i++){
            //switch directions every turn 
            grinder.write(i%2 == 0 ? 180: 0); 
            delay(GRIND_INCREMENT);
            Serial.println("grinder grinded "+String(i)+" times");
        }
        
        //once grinding is done, bring pusher back up
        pusher.write(0);
        delay(PUSHER_MOVE_TIME);
        pusher.write(90);
        Serial.println("pusher reached top");        
    } else {
        //make sure pusher and grinder are in neutral position
        pusher.write(90);
        grinder.write(90);
    }

}
