#ifndef AUTON_H

#define AUTON_H



bool leftRedAuton() {
  int startTime;
  startTime = nSysTime;
  if(nSysTime - startTime <= 15000)
    return true;
  else
    return false;
}

bool rightRedAuton() {
  int startTime;
  startTime = nSysTime;
  if(nSysTime - startTime <= 15000)
    return true;
  else
    return false;
}





bool leftBlueAuton() {
  int startTime;
  startTime = nSysTime;
  if(nSysTime - startTime <= 15000)
    return true;
  else
    return false;
}

bool rightBlueAuton() {
  int startTime;
  startTime = nSysTime;
  if(nSysTime - startTime <= 15000)
    return true;
  else
    return false;
}



#endif
