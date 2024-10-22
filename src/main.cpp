/*
It works !!!!
make sure to install the right lib:
arduino-libraries/Servo@^1.2.2
*/
//inverse scamatic math stuff
#include "HardwareSerial.h"
#include <math.h>

#define PI 3.14159265358979323846 
#define sqr(a) a*a

float radians_2_degree(float r){
    
    float d = r*180/PI;

    while(d<0||d>=360){
        Serial.print("original: ");
        Serial.println(d);
        if(d>=360){
            d-=360;
        }else if(d<0){
            d+= 360;
        }
    }
    if(d > 180){
        Serial.println("warning d > 180 ");
    }
    return d;
}

//all units in cm
#define J2L 4.9
#define J3L 4.9



#define J3_HALF(Y,Z) (acos( \
            (sqr(J3L)+sqr(J2L)-sqr(Z)-sqr(Y))/ \
            (2*J2L*J3L)) \
        )
float J3(float Y,float Z){
    if(Y>=0){
        return J3_HALF(Y, Z)-PI/2;
    }
    return PI-J3_HALF(-Y, Z)+PI/2;
}

#define J3_R(Y,Z) radians_2_degree(J3(Y,Z))

#define B(Y,Z) acos( \
            (sqr(Z)+sqr(Y)+sqr(J2L)-sqr(J3L))/ \
            (2*sqrt(sqr(Z)+sqr(Y))*J2L)\
        )

#define A(Y,Z) atan(Z/Y)

#define J2_HALF(Y,Z) (B(Y,Z)-A(Y,Z))
float J2(float Y,float Z){
    if(Y>=0){
        return J2_HALF(Y, Z);
    }
    return PI-J2_HALF(-Y, Z);
}
#define J2_R(Y,Z) radians_2_degree(J2(Y,Z))


#include <Arduino.h>
#include <Servo.h>

Servo j2;
Servo j3;

void setup() {
    Serial.begin(9600);
    j2.attach(5);
    j3.attach(3);
    j2.write(90);
    j3.write(90);
    delay(2000);
}

void set_arm(float y, float z){
    float j2_a = J2_R(y, -z);
    float j3_a = J3_R(y, -z);
    j2.write(j2_a);
    j3.write(j3_a);
    Serial.print(j2_a);
    Serial.print(", ");
    Serial.println(j3_a);
    delay(2000);
}

void loop() {
    //set_arm(-2*4.9,0);
    set_arm(2*4.9,0);
    set_arm(-2*4.9,0);
    //set_arm(-4.9,4.9);
    //set_arm(9.0,0.0);
    
}

