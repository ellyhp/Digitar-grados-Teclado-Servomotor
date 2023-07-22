#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 13, d4 = A0, d5 = A1, d6 = A4, d7 = A5;
LiquidCrystal LCD(rs, en, d4, d5, d6, d7);

const byte numRows = 4;
const byte numCols = 4;

Servo servomotor;

char keymap[numRows][numCols] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[numRows] = {11, 10, 9, 8}; //filas 0 a 3
byte colPins[numCols] = {7, 6, 5, 4}; //Columnas 0 a 3

Keypad teclado = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

String gradostemp = "";

int grados = 0;


void setup()
{
  LCD.begin(16, 2);
  LCD.print("CAMBIA LOS");
  LCD.setCursor(0, 1);
  LCD.print("GRADOS");
  delay(2000);
  LCD.clear();
  Serial.begin(9600);
  servomotor.attach(3);
  Serial.print("DIGITE GRADOS: ");
  servomotor.write(0);
  LCD.setCursor(0, 0);
  LCD.print("Digite Grados:");
}


void loop() {
  char key = teclado.getKey();
  if (key)
  {
    if (key == '#')
    {
      Serial.println("");
      grados = gradostemp.toInt();
      if (grados <= 180)
      {
        servomotor.write(grados);
        delay(1000);
        LCD.clear();
        gradostemp = "";
        Serial.print("DIGITE GRADOS: ");
        LCD.setCursor(0, 0);
        LCD.print("Digite Grados:");
      }
      else
      {
        Serial.println("VALOR NO PERMITIDO, EL RANGO ES DE 0 A 180");
        LCD.setCursor(0, 0);
        LCD.print("Grados Superados");
        LCD.setCursor(0, 1);
        LCD.print("Limite 180");
        delay(1000);
        LCD.clear();
        Serial.print("DIGITE GRADOS: ");
        LCD.setCursor(0, 0);
        LCD.print("Digite Grados:");
        gradostemp = "";
      }
    }
    else if (key == '*')
    {
      // Borrar última tecla agregada
      gradostemp = gradostemp.substring(0, gradostemp.length() - 1);
      Serial.print("\b \b"); // Borra el último carácter impreso en la consola
      LCD.setCursor(0, 1);
      LCD.print(gradostemp + " "); // Borra el último carácter impreso en la pantalla LCD
    }
    else
    {
      gradostemp = gradostemp + key;
      Serial.print(key);
      LCD.setCursor(0, 1);
      LCD.print(gradostemp);
    }
  }

}
