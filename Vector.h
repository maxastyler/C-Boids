#ifndef VECTOR2
#define VECTOR2

#include <math.h>

struct Vec2
{
    float x;
    float y;
    Vec2(float _x, float _y): x(_x), y(_y){};
    Vec2():x(0),y(0){};
    float length();
    Vec2 normalised();
    void normalise();
    void limit(float);
    
    Vec2 operator+ (Vec2);
    Vec2 operator- (Vec2);

    void operator+=(Vec2);
    void operator-=(Vec2);

    Vec2 operator* (float);
    Vec2 operator/ (float);

    void operator*=(float);
    void operator/=(float);
    
    float dot(Vec2);

};

#endif
