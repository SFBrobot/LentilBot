#ifndef SYS_CTL_H

#define SYS_CTL_H

typedef struct {
  signed char mtrPorts[6],
    revPorts[6],
    pwr;
} System;

typedef System Sys;

Sys* initSys(Sys* sys,
  signed char mtrPort1,
  signed char mtrPort2,
  signed char mtrPort3,
  signed char mtrPort4,
  signed char mtrPort5,
  signed char mtrPort6,
  signed char rev1,
  signed char rev2,
  signed char rev3,
  signed char rev4,
  signed char rev5,
  signed char rev6) {

  sys->mtrPorts[0] = mtrPort1;
  sys->mtrPorts[1] = mtrPort2;
  sys->mtrPorts[2] = mtrPort3;
  sys->mtrPorts[3] = mtrPort4;
  sys->mtrPorts[4] = mtrPort5;
  sys->mtrPorts[5] = mtrPort6;

  sys->revPorts[0] = (rev1 > 0)
    ? 1
    : 0;
  sys->revPorts[1] = (rev2 > 0)
    ? 1
    : 0;
  sys->revPorts[2] = (rev3 > 0)
    ? 1
    : 0;
  sys->revPorts[3] = (rev4 > 0)
    ? 1
    : 0;
  sys->revPorts[4] = (rev5 > 0)
    ? 1
    : 0;
  sys->revPorts[5] = (rev6 > 0)
    ? 1
    : 0;
  return sys;
}

Sys* initSys(Sys* sys,
  signed char mtrPort1,
  signed char mtrPort2,
  signed char mtrPort3,
  signed char mtrPort4,
  signed char mtrPort5,
  signed char rev1,
  signed char rev2,
  signed char rev3,
  signed char rev4,
  signed char rev5) {

  sys->mtrPorts[0] = mtrPort1;
  sys->mtrPorts[1] = mtrPort2;
  sys->mtrPorts[2] = mtrPort3;
  sys->mtrPorts[3] = mtrPort4;
  sys->mtrPorts[4] = mtrPort5;
  sys->mtrPorts[5] = -1;

  sys->revPorts[0] = (rev1 > 0)
    ? 1
    : 0;
  sys->revPorts[1] = (rev2 > 0)
    ? 1
    : 0;
  sys->revPorts[2] = (rev3 > 0)
    ? 1
    : 0;
  sys->revPorts[3] = (rev4 > 0)
    ? 1
    : 0;
  sys->revPorts[4] = (rev5 > 0)
    ? 1
    : 0;
  sys->revPorts[5] = -1;
  return sys;
}

Sys* initSys(Sys* sys,
  signed char mtrPort1,
  signed char mtrPort2,
  signed char mtrPort3,
  signed char mtrPort4,
  signed char rev1,
  signed char rev2,
  signed char rev3,
  signed char rev4) {

  sys->mtrPorts[0] = mtrPort1;
  sys->mtrPorts[1] = mtrPort2;
  sys->mtrPorts[2] = mtrPort3;
  sys->mtrPorts[3] = mtrPort4;
  sys->mtrPorts[4] = 
    sys->mtrPorts[5] = -1;

  sys->revPorts[0] = (rev1 > 0)
    ? 1
    : 0;
  sys->revPorts[1] = (rev2 > 0)
    ? 1
    : 0;
  sys->revPorts[2] = (rev3 > 0)
    ? 1
    : 0;
  sys->revPorts[3] = (rev4 > 0)
    ? 1
    : 0;
  sys->revPorts[4] =
    sys->revPorts[5] = -1;
  return sys;
}

Sys* initSys(Sys* sys,
  signed char mtrPort1,
  signed char mtrPort2,
  signed char mtrPort3,
  signed char rev1,
  signed char rev2,
  signed char rev3) {

  sys->mtrPorts[0] = mtrPort1;
  sys->mtrPorts[1] = mtrPort2;
  sys->mtrPorts[2] = mtrPort3;
  sys->mtrPorts[3] =
    sys->mtrPorts[4] = 
    sys->mtrPorts[5] = -1;

  sys->revPorts[0] = (rev1 > 0)
    ? 1
    : 0;
  sys->revPorts[1] = (rev2 > 0)
    ? 1
    : 0;
  sys->revPorts[2] = (rev3 > 0)
    ? 1
    : 0;
  sys->revPorts[3] =
    sys->revPorts[4] =
    sys->revPorts[5] = -1;
  return sys;
}

Sys* initSys(Sys* sys,
  signed char mtrPort1,
  signed char mtrPort2,
  signed char rev1,
  signed char rev2) {

  sys->mtrPorts[0] = mtrPort1;
  sys->mtrPorts[1] = mtrPort2;
  sys->mtrPorts[2] =
    sys->mtrPorts[3] =
    sys->mtrPorts[4] = 
    sys->mtrPorts[5] = -1;

  sys->revPorts[0] = (rev1 > 0)
    ? 1
    : 0;
  sys->revPorts[1] = (rev2 > 0)
    ? 1
    : 0;
  sys->revPorts[2] =
    sys->revPorts[3] =
    sys->revPorts[4] =
    sys->revPorts[5] = -1;
  return sys;
}

Sys* initSys(Sys* sys,
  signed char mtrPort1,
  signed char rev1) {

  sys->mtrPorts[0] = mtrPort1;
  sys->mtrPorts[1] =
    sys->mtrPorts[2] =
    sys->mtrPorts[3] =
    sys->mtrPorts[4] = 
    sys->mtrPorts[5] = -1;

  sys->revPorts[0] = (rev1 > 0)
    ? 1
    : 0;
  sys->revPorts[1] =
    sys->revPorts[2] =
    sys->revPorts[3] =
    sys->revPorts[4] =
    sys->revPorts[5] = -1;
  return sys;
}

signed char upSysPwr(Sys* sys, signed char pwr) {
  sys->pwr = pwr;
  for(int i = 0; i < 6; i++) {
    if(sys->mtrPorts[i] > 0) {
      if(sys->revPorts[i] > 0)
        motorSet(mtrPorts[i]-1, -sys->pwr);
      else if(sys->revPorts[i] == 0)
        motorSet(mtrPorts[i]-1, sys->pwr);
      else
        return sys->pwr;
    }
    else
      return sys->pwr;
  }
  return sys->pwr;
}

#endif
