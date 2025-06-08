#pragma once

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
#define J3L 13

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


