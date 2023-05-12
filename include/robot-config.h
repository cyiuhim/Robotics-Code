using namespace vex;

extern brain Brain;

extern controller Controller1;
//cataput = front
extern motor fl; //front left, stacked on top
extern motor fr; //front right, stacked on top
extern motor ml; //front left, stacked on bottom
extern motor mr; //front right, stacked on bottom
extern motor bl; //back left
extern motor br; //back right
extern motor cata; //catapult
extern motor roller; //roller, intake shared motor
extern pneumatics boost; //left catapult booster

extern rotation catalimit; //catapult rotation sensor for reload
extern inertial in1; //inertial sensor for heading
extern encoder xtrack; //horizontal tracking wheel 
extern encoder ytrack; //forward/backward tracking wheel
extern pneumatics expand1; //left expansion
extern pneumatics expand2; //right expansion
extern pneumatics intake; //intake lift for disc stack 

void vexcodeInit(void);
