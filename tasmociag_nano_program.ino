#include "Servo.h" //Biblioteka służąca do obsługi serwomechanizmu
#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

HX711 scale;
long reading = 0;
long calibration = 0;


Servo myserv;  // Utworzenie obiektu myservo
int pos = 0; //Początkowa pozycja serwa
Servo myserv1;  // Utworzenie obiektu myservo
int pos1 = 0; //Początkowa pozycja serwa
Servo myserv2;  // Utworzenie obiektu myservo
int pos2 = 0; //Początkowa pozycja serwa
Servo myserv3;  // Utworzenie obiektu myservo
int pos3 = 0; //Początkowa pozycja serwa
int pojemnik_0 = 0;
int pojemnik_1 = 0;
int pojemnik_2 = 0;
int pojemnik_3 = 0;

void setup() {
  //tenso calibration
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  delay(3000);
  if (scale.is_ready()) {
    reading = scale.read();
  }
  delay(300);
  if (scale.is_ready()) {
    reading += scale.read();
  }
  delay(300);
  if (scale.is_ready()) {
    reading += scale.read();
  }
  calibration = (reading / 3);
  Serial.println("calibration ");
  Serial.println(calibration);


  //tenso end
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  myserv.attach(8);  //Przyłaczenie serwomechanizmu do pinu 8 w Arduino
  myserv1.attach(9);  //Przyłaczenie serwomechanizmu do pinu 9 w Arduino
  myserv2.attach(10);  //Przyłaczenie serwomechanizmu do pinu 10 w Arduino
  myserv3.attach(11);  //Przyłaczenie serwomechanizmu do pinu 11 w Arduino

  //  procedura kalibracji
  for (pos = 0; pos <= 125; pos += 1) 
  {
    myserv.write(pos); //ustawienie zadanej pozycji
    delay(5); //Czas na zmiane pozycji
  }
  delay(200);
  for (pos = 125; pos >= 0; pos -= 1) 
  {
    myserv.write(pos); //ustawienie zadanej pozycji
    delay(5); //Czas na zmiane pozycji
  }

  delay(200);
  for (pos = 0; pos <= 30; pos += 1) 
  {
    myserv1.write(pos); //ustawienie zadanej pozycji
    delay(5); //Czas na zmiane pozycji
  }
  delay(200);
  for (pos = 30; pos >= 0; pos -= 1) 
  {
    myserv1.write(pos); //ustawienie zadanej pozycji
    delay(5); //Czas na zmiane pozycji
  }
  delay(200);
  for (pos = 0; pos <= 30; pos += 1) 
  {
    myserv2.write(pos); //ustawienie zadanej pozycji
    delay(5); //Czas na zmiane pozycji
  }
  delay(200);
  for (pos = 30; pos >= 0; pos -= 1) 
  {
    myserv2.write(pos); //ustawienie zadanej pozycji
    delay(5); //Czas na zmiane pozycji
  }
  delay(200);
  for (pos = 0; pos <= 30; pos += 1) 
  {
    myserv3.write(pos); //ustawienie zadanej pozycji
    delay(5); //Czas na zmiane pozycji
  }
  delay(200);
  for (pos = 30; pos >= 0; pos -= 1) 
  {
    myserv3.write(pos); //ustawienie zadanej pozycji
    delay(5); //Czas na zmiane pozycji
  }
  delay(3000);
  //koniec kalibrowania serwomechanizmów
  wypisz_ile();
}

void wypisz_ile()
{
  int print_clear = 0;
  for (print_clear = 0; print_clear < 20; print_clear++)
  {
    Serial.println("");
  }
  Serial.print("pojemnik_0 ");
  Serial.println(pojemnik_0);
  Serial.print("pojemnik_1 ");
  Serial.println(pojemnik_1);
  Serial.print("pojemnik_2 ");
  Serial.println(pojemnik_2);
  Serial.print("pojemnik_3 ");
  Serial.println(pojemnik_3);
  for (print_clear = 0; print_clear < 9; print_clear++)
  {
    Serial.println("");
  }
}

int wait_step_motor = 4;
int i = 0;
void step_motor(int steps)
{
  for (i = 0; i < steps; i++)
  {
    digitalWrite(4, HIGH);
    delay(wait_step_motor);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    delay(wait_step_motor);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    delay(wait_step_motor);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    delay(wait_step_motor);
    digitalWrite(7, LOW);
  }
}
void loop() {
  //tenso rading
  if (scale.is_ready())
  {
    long reading = 0;
    for (int y = 0; y < 3; y++)
    {
      reading += ((scale.read() - calibration)) / 2;
      delay(300);
    }
    reading = reading / 3;
    //Serial.print("HX711 reading: ");
    //Serial.println(reading);


    if (reading > 3000)
    {
      //servo 0
      for (pos = 0; pos <= 125; pos += 1) //Zmiana pozycji (dodawanie) do 180 stopni
      {
        myserv.write(pos); //ustawienie zadanej pozycji
        delay(4); //Czas na zmiane pozycji
      }
      delay(1000);
      for (pos = 125; pos >= 0; pos -= 1) //Zmiana pozycji (dodawanie) do 180 stopni
      {
        myserv.write(pos); //ustawienie zadanej pozycji
        delay(2); //Czas na zmiane pozycji
      }
      delay(1000);
    }
    if (reading > 3000 && reading < 7000)
    {
      //servo 1
      step_motor(150);
      delay(2000);
      for (pos = 0; pos <= 35; pos += 1) //Zmiana pozycji (dodawanie) do 180 stopni
      {
        myserv1.write(pos); //ustawienie zadanej pozycji
        delay(5); //Czas na zmiane pozycji
      }
      delay(2000);
      for (pos = 35; pos >= 0; pos -= 1) //Zmiana pozycji (dodawanie) do 180 stopni
      {
        myserv1.write(pos); //ustawienie zadanej pozycji
        delay(5); //Czas na zmiane pozycji
      }
      pojemnik_0++;
      wypisz_ile();
      delay(3000);
    }
    if (reading > 7000 && reading < 18000)
    {
      //serwo 2
      step_motor(600);
      delay(2200);
      for (pos = 0; pos <= 35; pos += 1) //Zmiana pozycji (dodawanie) do 180 stopni
      {
        myserv2.write(pos); //ustawienie zadanej pozycji
        delay(5); //Czas na zmiane pozycji
      }
      delay(2000);
      for (pos = 35; pos >= 0; pos -= 1) //Zmiana pozycji (dodawanie) do 180 stopni
      {
        myserv2.write(pos); //ustawienie zadanej pozycji
        delay(5); //Czas na zmiane pozycji
      }
      pojemnik_1++;
      wypisz_ile();
      delay(3000);
    }
    if (reading > 18000 && reading < 30000)
    {
      //serwo 3
      step_motor(1200);
      delay(2000);
      for (pos = 0; pos <= 35; pos += 1) //Zmiana pozycji (dodawanie) do 180 stopni
      {
        myserv3.write(pos); //ustawienie zadanej pozycji
        delay(5); //Czas na zmiane pozycji
      }
      delay(2000);
      for (pos = 35; pos >= 0; pos -= 1) //Zmiana pozycji (dodawanie) do 180 stopni
      {
        myserv3.write(pos); //ustawienie zadanej pozycji
        delay(5); //Czas na zmiane pozycji
      }
      pojemnik_2++;
      wypisz_ile();
      delay(3000);
    }
    if (reading > 30000)
    {
      step_motor(1500);
      pojemnik_3++;
      wypisz_ile();
    }

  }
  else
  {
    Serial.println("HX711 not found.");
  }
  delay(500);
}
