#ifndef ROBOT_C

#define ROBOT_C

int motorSet(signed char port, signed char pwr) {
  motor[port] = pwr;
  return pwr;
}

#endif
