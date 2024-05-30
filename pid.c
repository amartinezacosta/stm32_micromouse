#include "pid.h"

void pid_init(pid_t * const self, 
  float kp, float ki, float kd,
  float integral_max, float tau,
  float max_output, float min_output)
{
  self->setpoint = 0.0;
  self->actual = 0.0;
  self->integral = 0.0;
  self->last_error = 0.0;
  self->integral_max = integral_max;
  self->kp = kp;
  self->ki = ki;
  self->kd = kd;
  self->max_output = max_output;
  self->min_output = min_output;
  self->tau = tau;
}

float pid_update(pid_t * const self, float actual)
{
  float error = self->setpoint - actual;
  float p_term = self->kp * error;
  
  self->integral += (self->ki * error) * self->tau;
  if(self->integral > self->integral_max) 
    self->integral = self->integral_max;
  
  float d_term = (error - self->last_error) / self->tau;
  float control_output = p_term + self->integral + d_term;

  if(control_output > self->max_output)
    control_output = self->max_output;
  
  if(control_output < self->min_output)
    control_output = self->min_output;

  return control_output;
}

inline void pid_update_setpoint(pid_t * const self, float setpoint)
{
  self->setpoint = setpoint;
}

inline void pid_update_kp(pid_t * const self, float kp)
{
  self->kp = kp;
}

inline void pid_update_kd(pid_t * const self, float kd)
{
  self->kd = kd;
}

inline void pid_update_ki(pid_t * const self, float ki)
{
  self->ki = ki;
}