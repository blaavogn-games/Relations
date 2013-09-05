#include "inc/col/math/MathEssential.h"


bool MathEssential::fIsEqual(float a, float b, float maxDif)
{
    if(std::fabs(a-b) < maxDif){
        return true;
    }
    return false;
}

float MathEssential::toRadians(float f){
    return f * 3.1415926f / 180;
}

float MathEssential::toDegrees(float f){
    return f * 180 / 3.1415926f;
}
