#include "inc/col/math/MathEssential.h"

bool MathEssential::fIsEqual(float a, float b, float maxDif)
{
    if(std::fabs(a-b) < maxDif){
        return true;
    }
    return false;
}
