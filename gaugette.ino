

#import "Command.h"
#import "SwitecX25.h"

Command cmd;

// 6 steps per rotation, so 60 degrees per step of motor
// 180:1 gear ration
// 1/3 degree per step of needle
// 315 degrees full-scale-deflection of needle

SwitecX25 motor1(233 * 3, 8, 9, 10, 11);
SwitecX25 motor2(233 * 3, 4, 5, 6, 7);
SwitecX25 *motors[] = {&motor1,&motor2};
const unsigned int motorCount = sizeof(motors)/sizeof(*motors);

void zero()
{
  for (int i=0;i<motorCount;i++) {
    SwitecX25 *motor = motors[i];
    motor->currentStep = motor->steps-1;
    motor->targetStep = 0;
    motor->vel = 0;
    motor->dir = 0;
  }
  
  boolean done = false;
  while (!done) {
    done = true;
    for (int i=0;i<motorCount;i++) {
      SwitecX25 *motor = motors[i];
      if (motor->currentStep>0) {
        motor->stepDown();
        done = false;
      }
    }
    delayMicroseconds(600);        
  }
}

void setup(void) {
  Serial.begin(9600);
  Serial.print(motorCount);
  Serial.print(" motors. ");
  Serial.println("Go!");
  zero();
}

void loop(void) {
  motor1.update();
  motor2.update();
  if (cmd.parseInput()) {
    //cmd.dump();
    if (cmd.address[1]<motorCount) {
      SwitecX25 *motor = motors[cmd.address[1]];
      switch (cmd.command) {
        case 'z':
          motor->zero();        
          break;
        case 's':
          motor->setPosition(cmd.value[1]);
          break;
        case 'r':
          motor->setRange(cmd.value[1],cmd.value[2]);
          break;
      }
    }
  }
}



