#include "timing.h"

static double framesPerSecond = 0;

double FramesPerSecond(double seconds)
{
    framesPerSecond = (framesPerSecond * 0.9) + (1.0 / seconds * 0.1);
    return framesPerSecond;
}