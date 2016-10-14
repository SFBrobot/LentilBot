#define ROBOT_C

#ifdef ROBOT_C
#include "prosRobotcFuncs.h"
#endif

#include "lnStarBot/sysCtl.h"
#include "pid.h"

#include "lnStarBot/V2/auton.h"




Sys Lift,
  Claw,
  rDrive,
  lDrive;

task main() {

  int stick[4];
  unsigned char 

  while(true) {

    for(int i = 0; i < 4; i++)
      stick[i] = (abs(vexRT[i]) >= 15)
        ? vexRT[i]
        : 0;

    if(tank) {
      upSysPwr(&lDrive, stick[2]);
      upSysPwr(&rDrive, stick[1]);
    }
    else {
      upSysPwr(&lDrive, stick[2] + stick[0]);
      upSysPwr(&rDrive, stick[2] - stick[0]);
    }

    if(vexRT[Btn5U] ^ vexRT[Btn5D]) {
      if(vexRT[Btn5U])
        upSysPwr(&Lift, 127);
      else
        upSysPwr(&Lift, -127);
    }
    else
      upSysPwr(&Lift, 0);

    if(vexRT[Btn5U] ^ vexRT[Btn5D]) {
      if(vexRT[Btn5U])
        upSysPwr(&Claw, 127);
      else
        upSysPwr(&Claw, -127);
    }
    else
      upSysPwr(&Claw, 0);

    wait1Msec(20);
  }
}
