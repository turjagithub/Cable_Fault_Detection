// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int sms_count=0;
// define phase control pins
int phase[3] = {7, 8, 9}; 


//*********************************************************
int distance(int inputVoltage) {
  if (inputVoltage >= 890 && inputVoltage < 950) {
    return 8;
  }
  else if (inputVoltage >= 845 && inputVoltage < 880) {
    return 6;
  }
  else if (inputVoltage >= 750 && inputVoltage < 845) {
    return 4;
  }
  else if (inputVoltage >= 400 && inputVoltage < 750) {
    return 2;
  }

  else return 0 ;

}
//*********************************************************

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
Serial.begin(9600);
  // set pin mode for phase relays
  for (int j = 0; j < 3; j++) {
    pinMode(phase[j], OUTPUT);
  }

}

void loop() {
  digitalWrite(phase[0], HIGH);
  delay(500);
  int dist1 = distance(analogRead(A0));
  if (dist1 == 0) {
    lcd.setCursor(0, 0);
    lcd.write("R: ");
    lcd.setCursor(3, 0);
    lcd.write("NF   ");
  }
  else {
    lcd.setCursor(0, 0);
    lcd.write("R: ");
    lcd.setCursor(3, 0);
    lcd.print(dist1);
    lcd.setCursor(4, 0);
    lcd.write(" KM");
     while(sms_count<3)
  {
init_sms();
send_data("Fault happend in phase R in" + String (dist1)+ "KM");
//send_data("KM");
send_sms();
delay(100);
  }}
  digitalWrite(phase[0], LOW);
  //================================================
  digitalWrite(phase[1], HIGH);
  delay(500);
  int dist2 = distance(analogRead(A0));
  if (dist2 == 0) {
    lcd.setCursor(8, 0);
    lcd.write("Y: ");
    lcd.setCursor(11, 0);
    lcd.write("NF   ");
  }
  else {
    lcd.setCursor(8, 0);
    lcd.write("Y: ");
    lcd.setCursor(11, 0);
    lcd.print(dist2);
    lcd.setCursor(12, 0);
    lcd.write(" KM");
     while(sms_count<3)
  {
init_sms();
send_data("Fault happend in phase Y in" + String (dist2)+ "KM");
//send_data("KM");
send_sms();
delay(100);
  }
  }
  digitalWrite(phase[1], LOW);
  //=================================================
  digitalWrite(phase[2], HIGH);
  delay(500);
  int dist3 = distance(analogRead(A0));
  if (dist3 == 0) {
    lcd.setCursor(0, 1);
    lcd.write("G: ");
    lcd.setCursor(3, 1);
    lcd.write("NF   ");
  }
  else {
    lcd.setCursor(0, 1);
    lcd.write("G: ");
    lcd.setCursor(3, 1);
    lcd.print(dist3);
    lcd.setCursor(4, 1);
    lcd.write(" KM");
   while(sms_count<3)
  {
init_sms();
send_data("Fault happend in phase G in" + String (dist3)+ "KM");
//send_data("KM");
send_sms();
delay(100);
  }}
  digitalWrite(phase[2], LOW);
}

void init_sms()
{
Serial.println("AT+CMGF=1");
delay(1000);
Serial.println("AT+CMGS=\"+8801638543713\"\r");
delay(200);
}

void send_data(String message)
{
Serial.println(message);
delay(200);
}
void send_sms()
{
Serial.write(26);
sms_count++;
}


