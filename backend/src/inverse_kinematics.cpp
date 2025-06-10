#include <inverse_kinematics.hpp>
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
float HL(float X,float Y){
    if(Y<0){
        return sqrt(sqr(X)+sqr(Y));
    }
    return -sqrt(sqr(X)+sqr(Y));
}
float J1(float X,float Y){
    if(X*Y>=0){
        return J1_HALF(X, Y);
    }
    return PI-J1_HALF(-X, Y);

}
float J3(float H,float Z){
    if(H>=0){
        return J3_HALF(H, Z)-PI/2;
    }
    return PI-J3_HALF(-H, Z)+PI/2;
}
float J2(float H,float Z){
    if(H>=0){
        return J2_HALF(H, Z);
    }
    return PI-J2_HALF(-H, Z);
}


