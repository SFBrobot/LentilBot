#include "lnStarBot/clawCtl.h"
#include "lnStarBot/liftCtl.h"
#include "lnStarBot/driveCtl.h"
#include "pid.h"

#include "lnStarBot/auton.h"

const char rDriveMtrCt = 2,
  lDriveMtrCt = 2,
  rDriveMtrPorts[2] = {8, 9},
  lDriveMtrPorts[2] = {2, 3},
  liftMtrCt = 4,
  liftMtrPorts[4] = {4, 5, 6, 7},
  clawMtrCt = 2,
  clawMtrPorts[2] = {1, 10};

task main() {

  int stick[4];

  while(true) {

    for(int i = 0; i < 4; i++)
      stick[i] = (abs(vexRT[i]) >= 15)
        ? vexRT[i]
        : 0;

    if(tank)
      driveCtl(&lDriveMtrPorts, lDriveMtrCt,
        &rDriveMtrPorts, rDriveMtrCt,
        tank(&drivePwr, stick[2], stick[1]);
    else
      driveCtl(&lDriveMtrPorts, lDriveMtrCt,
        &rDriveMtrPorts, rDriveMtrCt,
        arcade(&drivePwr, stick[2], stick[0]);

    if(vexRT[Btn5U] ^ vexRT[Btn5D]) {
      if(vexRT[Btn5U])
        liftCtl(&liftMtrPorts, liftMtrCt, 127);
      else
        liftCtl(&liftMtrPorts, liftMtrCt, -127);
    }
    else
      liftCtl(&liftMtrPorts, liftMtrCt, 0);

    if(vexRT[Btn5U] ^ vexRT[Btn5D]) {
      if(vexRT[Btn5U])
        clawCtl(&clawMtrPorts, clawMtrCt, 127);
      else
        clawCtl(&clawMtrPorts, clawMtrCt, -127);
    }
    else
      clawCtl(&clawMtrPorts, clawMtrCt, 0);

    wait1Msec(20);
  }
}
