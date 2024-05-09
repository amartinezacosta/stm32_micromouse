#ifndef MOTION_PROFILE_H_
#define MOTION_PROFILE_H_

typedef enum
{
  ACCELERATING,
  CRUISING,
  DECELERATING,
  FINISHED
}motion_state_t;

typedef struct
{
  motion_state_t state;
  float target_velocity;
  float final_velocity;
  float target_position;
  float acceleration;
  float velocity;
  float position;
}motion_profile_t;

void motion_profile_start(motion_profile_t * const self,
  float target_velocity,
  float final_velocity,
  float target_position,
  float acceleration);
float motion_profile_update(motion_profile_t * const self);
float motion_profile_decelerate_distance(float v0, float vf);

#endif