#include <Servo.h>
#include <stdlib.h>

Servo myservo_upper;
Servo myservo_lower;

#define DELAY_VALUE 10
#define SENSOR_MARGINE 5

const int servo_pin1 = 9;
const int servo_pin2 = 10;
const int left_sensor_pin = A0;                 // photoresistor1
const int middle_sensor_pin = A1;               // photoresistor0
const int right_sensor_pin = A2;                // photoresistor2
int pos = 0;                                    // variable to store the servo position

int position_upper = 0;
int position_lower = 0;

typedef struct  s_sens {
    int   brightness;
    char  position;
}   t_sens;

t_sens One, Three, Two = {0};

void setup() {
    myservo_upper.attach(servo_pin1);
    myservo_lower.attach(servo_pin2);
    Serial.begin(9600);
}

void update_sensor_values_and_move()
{
    Two.brightness = analogRead(middle_sensor_pin);
    One.brightness = analogRead(left_sensor_pin);
    Three.brightness = analogRead(right_sensor_pin);
    myservo_upper.write(position_upper);
    myservo_lower.write(position_lower);
    delay(DELAY_VALUE);
}

void loop()
{
    Two.brightness = analogRead(middle_sensor_pin);
    One.brightness = analogRead(left_sensor_pin);
    Three.brightness = analogRead(right_sensor_pin);

    while(Three.brightness - One.brightness > SENSOR_MARGINE  && position_upper < 180){
        position_upper += 1;
        update_sensor_values_and_move();
    }
    while (Three.brightness - Two.brightness > SENSOR_MARGINE && position_lower < 180) {
        position_lower += 1;
        update_sensor_values_and_move();
    }
    while (One.brightness - Three.brightness > SENSOR_MARGINE && position_upper > 0) {
        position_upper -= 1;
        update_sensor_values_and_move();
    }
    while (Two.brightness - Three.brightness > SENSOR_MARGINE && position_lower > 0) {
        position_lower -= 1;
        update_sensor_values_and_move();
    }
    while (One.brightness - Two.brightness > SENSOR_MARGINE && position_lower < 180) {
        position_lower += 1;
        update_sensor_values_and_move();
    }
    while (Two.brightness - One.brightness > SENSOR_MARGINE && position_lower > 0) {
        position_lower -= 1;
        update_sensor_values_and_move();
    }
}

