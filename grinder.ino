#include <Servo.h>

int led = 13;
int sensor = 9;
int state = LOW;
Servo pusher;
Servo grinder;
int val = 0;
//the following values are, ironically, subject to change
const int PUSHER_MOVE_TIME = 1000;
const int GRIND_INCREMENT = 1000;
const int GRIND_COUNT = 5;

void setup() {
    pinMode(led, OUTPUT);
    pinMode(sensor, INPUT);
    Serial.begin(9600);
    pusher.attach(3);
    grinder.attach(7);
}

void loop(){
    val = digitalRead(sensor);
    digitalWrite(led, val);
    //start pushing
    //**TODO**: figure out timing function (or math it based on height of model)
    pusher.write(40);//adjust speed
    delay(PUSHER_MOVE_TIME);
    //stop pushing
    pusher.write(90);
    Serial.println("pusher reached bottom");
    
    //start grinding
    for(int i=0;i<GRIND_COUNT;i++){
        grinder.write(40); //adjust speed
        delay(GRIND_INCREMENT/2);
        grinder.write(90); 
        delay(GRIND_INCREMENT/2);
        Serial.println("grinder grinded "+i+" times");
    }
    //once grinding is done, bring pusher back up
    pusher.write(-40);
    delay(PUSHER_MOVE_TIME);
    pusher.write(90);
    Serial.println("pusher reached top");

}
