#ifndef _CONSTANT_H_
#define _CONSTANT_H_

/* graphic constants*/
//frame
#define FRAME_INTERVAL 1/30.

//window
#define WINDOW_SIZE 1600
#define WINDOW_POSITION_X 100
#define WINDOW_POSITION_Y 100

//camera
#define CAMERA_EYE_X 10
#define CAMERA_EYE_Y 10
#define CAMERA_EYE_Z 50

#define CAMERA_VIEW_X 0
#define CAMERA_VIEW_Y -8
#define CAMERA_VIEW_Z 0

#define CAMERA_UP_X 0
#define CAMERA_UP_Y 1
#define CAMERA_UP_Z 0

//floor
#define FLOOR_HEIGHT -10
#define FLOOR_WIDTH_MIN -200
#define FLOOR_WIDTH_MAX 200

//particle
#define PARTICLE_POINT_NUMBER 12
#define PARTICLE_RADIUS 1.

/* game parameter constants*/
#define MAX_PARTICLES 100

/* physic constants*/
#define GRAVITY_VALUE -0.05

#endif
