#include <FtduinoSimple.h>
#include <AccessNode.h>

int i3Wert = 0;
RobotikInterConnect* ric;
int counter = 0;
bool isClicked = false;


void setup() { //############## Aktuelle Labels an Maschiene sind korrekt ##############
    ric = new RobotikInterConnect("bedeckler");

    ftduino.motor_set(Ftduino::M2, Ftduino::LEFT); //Deckelmodul fährt in Ausgansposition
    while (!ftduino.input_get(Ftduino::I2)) delay(1);
    ftduino.motor_set(Ftduino::M2, Ftduino::OFF);

    ftduino.motor_set(Ftduino::M1, Ftduino::LEFT); //Pressmodul fährt in Ausgansposition
    while (!ftduino.input_get(Ftduino::I5)) delay(1);
    ftduino.motor_set(Ftduino::M1, Ftduino::OFF);

    ftduino.motor_set(Ftduino::M3, Ftduino::LEFT); //Schranke fährt in Ausgansposition
    while (!ftduino.input_get(Ftduino::I6)) delay(1);
    ftduino.motor_set(Ftduino::M3, Ftduino::OFF);

}
void loop() {
  // put your main code here, to run repeatedly:
  run();
}

//

void run() {
  ftduino.output_set(Ftduino::O8, Ftduino::OFF); //Hauptförderband aus

  ric->send("mfc","websocket","OK"); //ric Anbindung -> sendet OK
  ric->read_wait(); //Bedeckler wartet auf GO von ric

  ftduino.output_set(Ftduino::O8, Ftduino::HI); //Hauptförderband an

  while (ftduino.input_get(Ftduino::I1)) delay(1); // Lichtsensor 1 wartet auf Eingabe
  delay(800);

  ftduino.output_set(Ftduino::O8, Ftduino::OFF); //Hauptförderband aus

  ftduino.output_set(Ftduino::O7, Ftduino::HI); //Deckelspirale an
  delay(6000);
  ftduino.output_set(Ftduino::O7, Ftduino::OFF); //Deckelspirale aus

  ftduino.motor_set(Ftduino::M2, Ftduino::RIGHT); //Deckelmodul fährt zurück
  while (!ftduino.input_get(Ftduino::I3)) delay(1);
    ftduino.motor_set(Ftduino::M2, Ftduino::OFF); //Deckelmodul stoppt an Schalter

  ftduino.output_set(Ftduino::O8, Ftduino::HI); //Hauptförderband an

  while (ftduino.input_get(Ftduino::I4)) delay(1); //Lichtsensor 2 wartet auf Eingabe
  delay(2000);

  ftduino.output_set(Ftduino::O8, Ftduino::OFF); //Hauptförderband aus

  ftduino.motor_set(Ftduino::M1, Ftduino::RIGHT); //Pressmodul fährt runter / presst
  delay(2400);
  ftduino.motor_set(Ftduino::M1, Ftduino::LEFT); //Pressmodul fährt hoch
  while (!ftduino.input_get(Ftduino::I5)) delay(1);
    ftduino.motor_set(Ftduino::M1, Ftduino::OFF); //Pressmodul stoppt an Schalter
  
  ftduino.motor_set(Ftduino::M3, Ftduino::RIGHT); //Schranke geht auf
  delay(2500);
  ftduino.motor_set(Ftduino::M3, Ftduino::OFF); //Schranke aus

  ric->send("mfc","websocket","NEXT"); //Bedeckler sendet NEXT an ric
  ric->read_wait(); //Bedeckler wartet auf GO von ric

  ftduino.output_set(Ftduino::O8, Ftduino::HI); //Hauptförderband an

  ftduino.motor_set(Ftduino::M2, Ftduino::LEFT); //Deckelmodul fährt in Ausgansposition
    while (!ftduino.input_get(Ftduino::I2)) delay(1);
    ftduino.motor_set(Ftduino::M2, Ftduino::OFF);

  ftduino.motor_set(Ftduino::M3, Ftduino::LEFT); //Schranke fährt in Ausgangsposition
    while (!ftduino.input_get(Ftduino::I6)) delay(1);
    ftduino.motor_set(Ftduino::M3, Ftduino::OFF);

  delay(500);
}
