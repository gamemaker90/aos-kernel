#ifndef _AOS_C_VECTOR2F_
#define _AOS_C_VECTOR2F_

#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>

typedef struct aos_vector2 vector2f;

struct aos_vector2
{
    vector2f(*add)(vector2f, vector2f, vector2f);
    float(*angle)(vector2f, vector2f);
    float(*dot)(vector2f, vector2f);
    float(*get_x)(void);
    float(*get_y)(void);
    float(*length_squared)(void);
    
};

#endif