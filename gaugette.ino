

#import "Command.h"
#import "SwitecX25.h"

Command cmd;

// 6 steps per rotation, so 60 degrees per step
// 180:1 gear ration
// 1/3 degree per step
// 315 degrees full-scale-deflection

unsigned char motor1pins[4] = {8,9,10,11};
SwitecX25 motor1(315 * 3, motor1pins);

void setup(void) {
  Serial.begin(9600);
  Serial.println("Gaugette!");
  motor1.zero();  
}

void loop(void) {
  motor1.update();
  if (cmd.parseInput()) {
    cmd.dump();
    switch (cmd.command) {
      case 'z':
        motor1.zero();
        break;
      case 's':
        motor1.setPosition(cmd.value[1]);
        break;
    }
  }
}



