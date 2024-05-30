#ifndef PID_H_
#define PID_H_

typedef struct
{
  float setpoint;
  float actual;
  float kp;
  float ki;
  float kd;
  float integral;
  float integral_max;
  float last_error;
  float max_output;
  float min_output;
  float tau;
}pid_t;

void pid_init(pid_t * const self, 
  float kp, float ki, float kd,
  float integral_max, float tau,
  float max_output, float min_output);
float pid_update(pid_t * const self, float actual);
void pid_update_setpoint(pid_t * const self, float setpoint);
void pid_update_kp(pid_t * const self, float kp);
void pid_update_kd(pid_t * const self, float kd);
void pid_update_ki(pid_t * const self, float ki);

#endif