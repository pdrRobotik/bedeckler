#include <FtduinoSimple.h>
#include <AccessNode.h>

int i3Wert = 0;
RobotikInterConnect* ric;
int counter = 0;
bool isClicked = false;


void setup() {
    ric = new RobotikInterConnect("bedeckler");
    ftduino.motor_set(Ftduino::M2, Ftduino::LEFT);
    while (!ftduino.input_get(Ftduino::I2)) delay(1);
    ftduino.motor_set(Ftduino::M2, Ftduino::OFF);

    ftduino.motor_set(Ftduino::M1, Ftduino::LEFT);
    while (!ftduino.input_get(Ftduino::I5)) delay(1);
    ftduino.motor_set(Ftduino::M1, Ftduino::OFF);

    ftduino.motor_set(Ftduino::M3, Ftduino::LEFT);
    while (!ftduino.input_get(Ftduino::I6)) delay(1);
    ftduino.motor_set(Ftduino::M3, Ftduino::OFF);

}
void loop() {
  // put your main code here, to run repeatedly:
  run();
}

//

void run() {
  ric->send("mfc","websocket","OK");
  ftduino.output_set(Ftduino::O8, Ftduino::HI);

  while (ftduino.input_get(Ftduino::I1)) delay(1);
  delay(500);

  ftduino.output_set(Ftduino::O8, Ftduino::OFF);

  ftduino.output_set(Ftduino::O7, Ftduino::HI); //Deckel drauf
  delay(6000);
  ftduino.output_set(Ftduino::O7, Ftduino::OFF);

  ftduino.motor_set(Ftduino::M2, Ftduino::RIGHT); //Deckler zurück
  while (!ftduino.input_get(Ftduino::I3)) delay(1);
    ftduino.motor_set(Ftduino::M2, Ftduino::OFF);

  ftduino.output_set(Ftduino::O8, Ftduino::HI); //Band an

  while (ftduino.input_get(Ftduino::I4)) delay(1); //Sensor 2
  delay(2000);

  ftduino.output_set(Ftduino::O8, Ftduino::OFF);

  ftduino.motor_set(Ftduino::M1, Ftduino::RIGHT); //Presse
  delay(2400);
  ftduino.motor_set(Ftduino::M1, Ftduino::LEFT);
  while (!ftduino.input_get(Ftduino::I5)) delay(1);
    ftduino.motor_set(Ftduino::M1, Ftduino::OFF);
  
  ftduino.motor_set(Ftduino::M3, Ftduino::RIGHT);
  delay(2500);
  ftduino.motor_set(Ftduino::M3, Ftduino::OFF);

  ftduino.output_set(Ftduino::O8, Ftduino::HI);

  ftduino.motor_set(Ftduino::M2, Ftduino::LEFT);
    while (!ftduino.input_get(Ftduino::I2)) delay(1);
    ftduino.motor_set(Ftduino::M2, Ftduino::OFF);

  ric->send("mfc","websocket","NEXT");
  ftduino.motor_set(Ftduino::M3, Ftduino::LEFT);
    while (!ftduino.input_get(Ftduino::I6)) delay(1);
    ftduino.motor_set(Ftduino::M3, Ftduino::OFF);

  delay(500);
}
