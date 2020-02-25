#include "321Hlib/Autons/auton.h"


using namespace okapi;
#define red 1
#define blue -1
void largeZone7Cube(int side){
//Start in red square, preload aligned with nearby cube, S curve to side of 4 stack, take 4 stack, go back and get the aligned cubes, get the cube near the zone, and score. 7 cubes.
chassisProfile->generatePath({{0_in, 0_in, 0_deg}, {100_in, 0_in, 0_deg}}, "throughFirstRow");
//flipout();





}
