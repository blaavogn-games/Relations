#ifndef MATHESSENTIAL_H
#define MATHESSENTIAL_H
#include <cmath>

class MathEssential{

    public:
        static bool fIsEqual(float a, float b, float maxDif = 0.00001f);
        static float toRadians(float f);
        static float toDegrees(float f);

};

#endif
