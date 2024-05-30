#include "motion_profile.h"
#include "MicromouseConfig.h"

void motion_profile_start(motion_profile_t * const self,
  float target_velocity,
  float final_velocity,
  float target_position,
  float acceleration)
{
  self->velocity = 0.0;
  self->position = 0.0;
  self->acceleration = acceleration;
  self->final_velocity = final_velocity;
  self->target_velocity = target_velocity;
  self->target_position = target_position;
  self->state = ACCELERATING;
}

float motion_profile_update(motion_profile_t * const self)
{
  switch(self->state)
  {
    case ACCELERATING:
    self->velocity += self->acceleration*SENSOR_SYSTICK_PERIOD;
    if(self->velocity > self->target_velocity)
    {
      self->velocity = self->target_velocity;
      self->state = CRUISING;
    }
    break;
    case CRUISING:
    {
      float position_delta = self->target_position - self->position;
      float brake_distance = motion_profile_decelerate_distance(self->velocity,
        self->final_velocity);
      if(position_delta < brake_distance)
      {
        self->state = DECELERATING;
      }
    }
    break;
    case DECELERATING:
    self->velocity -= self->acceleration*SENSOR_SYSTICK_PERIOD;
    if(self->velocity < 0.0)
    {
      self->velocity = 0.0;
      self->state = FINISHED;
    }
    break;
    case FINISHED:
      return MAZE_CELL_CENTER_DISTANCE;
    break;
  }

  self->position += self->velocity*SENSOR_SYSTICK_PERIOD;
  return self->position;
}

float motion_profile_decelerate_distance(float v0, float vf)
{
  return ((v0*v0 - vf*vf)/(2*FORWARD_ACCELERATION));
}