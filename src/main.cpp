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

#define degree_2_radian(d) (((float)d)/180*PI)

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

float HL(float X,float Y){
    if(Y<0){
        return sqrt(sqr(X)+sqr(Y));
    }
    return -sqrt(sqr(X)+sqr(Y));
}
#define L(H,Z) sqrt(sqr(H)+sqr(Z))

#define J1_HALF(X,Y) atan(X/Y)
float J1(float X,float Y){
    if(X*Y>=0){
        return J1_HALF(X, Y);
    }
    return PI-J1_HALF(-X, Y);

}
#define J1_R(X,Y) radians_2_degree(J1(X,Y))

#define J3_HALF(H,Z) (acos( \
            (sqr(J3L)+sqr(J2L)-sqr(L(H,Z)))/ \
            (2*J2L*J3L)) \
        )
float J3(float H,float Z){
    if(H>=0){
        return J3_HALF(H, Z)-PI/2;
    }
    return PI-J3_HALF(-H, Z)+PI/2;
}

#define J3_R(H,Z) radians_2_degree(J3(H,Z))

#define B(H,Z) acos( \
            (sqr(L(H,Z))+sqr(J2L)-sqr(J3L))/ \
            (2*L(H,Z)*J2L)\
        )

#define A(H,Z) atan(Z/H)

#define J2_HALF(H,Z) (B(H,Z)-A(H,Z))
float J2(float H,float Z){
    if(H>=0){
        return J2_HALF(H, Z);
    }
    return PI-J2_HALF(-H, Z);
}
#define J2_R(H,Z) radians_2_degree(J2(H,Z))


#include <Arduino.h>
#include <Servo.h>

Servo j1;
Servo j2;
Servo j3;
Servo gripper;

void setup() {
    Serial.begin(9600);
    j1.attach(6);
    j2.attach(5);
    j3.attach(3);
    gripper.attach(9);
    j1.write(90);
    j2.write(90);
    j3.write(90);
    gripper.write(0);
    delay(2000);
    gripper.write(30);
}

void set_arm(float x,float y, float z){
    float j1_a = J1_R(x, y);
    float j2_a = J2_R(HL(x,y), -z);
    float j3_a = J3_R(HL(x,y), -z);
    j1.write(j1_a);
    j2.write(j2_a);
    j3.write(j3_a);
    Serial.print(j1_a);
    Serial.print(", ");
    Serial.print(j2_a);
    Serial.print(", ");
    Serial.println(j3_a);
}

void move_arm(float x, float y, float z){
    set_arm(x,y,z);
    delay(2000);
    float a_j1 = degree_2_radian(j1.read());
    float a_j2 = degree_2_radian(j2.read());
    float a_j3 = degree_2_radian(j3.read());
    Serial.print("set to ");
    Serial.print(a_j1);Serial.print(" ");
    Serial.print(a_j2);Serial.print(" ");
    Serial.print(a_j3);Serial.print(" ");
    Serial.println(" ");
}

void loop() {
    /*
    set_arm(0,2*4.9,0);
    set_arm(0,4.9,-4.9);
    set_arm(0,0,2*4.9);
    set_arm(0,-2*4.9,0);
    set_arm(0,-4.9,-4.9);
    */
    move_arm(5,5,0);
    move_arm(-5,5,0);
    move_arm(-5,-5,0);
    move_arm(5,-5,0);
}

