/* ******************************************
   * Système de Contrôle de la Température  *
   * P F E Licence éléctronique             *
   * Université MED BOUDIAF de M'Sila       *
   * Créé: Vendredi 17 mai 2019             *
   * PAR : ABDELALI Oussama ;               *
   * Processor: ATmega328P                  *
   * Compiler:  Arduino AVR                 *
   ******************************************
 */
#include <LiquidCrystal.h>         
LiquidCrystal lcd(3, 2, 7, 6, 5, 4); 
const int inPin    = A0;//CAPTEUR LM35 
const int LDR      = A1;//CAPTEUR de lumière (LDR) 
const int RELAY1   = 8; //VENTILATEUR
const int RELAY2   = 9; //Chauffage
const int RELAY3   = 10;//l'éclairage
const int BUZZER   = 11;//Buzzer
const int up_key   = 0; //Bouton haut
const int down_key = 1; //Bouton bas
      int SetPoint = 25;//Température référence début
      int sensorValue = 0; // variable pour stocker la valeur provenant du capteur de lumière
/*
   ----------------------------------------------------------------------------------------------------------------
                                              SETUP
   ----------------------------------------------------------------------------------------------------------------					      
*/
void setup()
{
  lcd.begin(16,2);
  pinMode(RELAY1,OUTPUT);  
  pinMode(RELAY2,OUTPUT);
  pinMode(RELAY3,OUTPUT);
  pinMode(BUZZER,OUTPUT);
  pinMode(up_key,INPUT);
  pinMode(down_key,INPUT);
  pinMode(LDR, INPUT);
  digitalWrite(up_key,HIGH);
  digitalWrite(down_key,HIGH);
  /*
   ----------------------------------------------------------------------------------------------------------------
                                             LOOP
   ----------------------------------------------------------------------------------------------------------------					      
*/
}
void loop()
{
  int value = analogRead(inPin); 
  lcd.setCursor(0,1);
  int millivolts = (value / 1024.0) * 5000; 
  int temp = millivolts / 10; //10mV/C
/*
 ================================
        AFFICHEUR LCD
 ================================
*/
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TEMPERATURE:");
  lcd.setCursor(12,0);
  lcd.print(temp);
  lcd.print(" C");
  lcd.setCursor(0,1);
  lcd.print("REFERENCE  :");
  lcd.print(SetPoint);
  lcd.print(" C");
  delay(1000);
 /*
 ================================
         L'éclairage
 ================================
 */
 int ldrStatus = analogRead(LDR);
 if (ldrStatus <= 200) {

digitalWrite(RELAY3, LOW);
} 
else 
{
digitalWrite(RELAY3, HIGH);


}
 /*
 ================================
          LE BOUTON
 ================================
 */

   if(digitalRead(down_key)==LOW)
  {
    if(SetPoint>0)
    {
      SetPoint--;    
    }
  }
  if(digitalRead(up_key)==LOW)
  {
    if(SetPoint<60)
    {
      SetPoint++;
    }
  }
 /*
 ================================
   Réglage de la Température
 ================================
 */
if(temp> SetPoint)
{
   digitalWrite(RELAY1,HIGH); 
   digitalWrite(RELAY2,LOW);


}
else
{
  digitalWrite(RELAY1,LOW);
  digitalWrite(RELAY2,HIGH);
}
if(temp == SetPoint)
{
   digitalWrite(RELAY1,LOW); 
   digitalWrite(RELAY2,LOW);


}

/*
 ================================
            BUZZER
 ================================
*/
int DANGER = 60;
if (temp > DANGER)
{
  digitalWrite(BUZZER,HIGH);
  delay(500);
  digitalWrite(BUZZER,LOW);
  delay(1000);
}
else
{
 digitalWrite(BUZZER,LOW);

}
}
