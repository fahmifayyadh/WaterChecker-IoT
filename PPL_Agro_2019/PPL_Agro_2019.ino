#include <DallasTemperature.h>
#include <OneWire.h>

#include <DFRobot_PH.h>



#define sensor_ph A0 //input sensor1
#define buzzer 5 //buzzer dan led merah
#define ledHijau 3 //led hijau
 DFRobot_PH ph;
#define sensor_ds18b20 2 //input sensor2
 
OneWire oneWire(sensor_ds18b20);
 
DallasTemperature sensors(&oneWire); //penggunaan interface 1 wire untuk pengaksesan


float tegangan,nilaiph,suhu;

 
void setup()
{
    Serial.begin(115200);  //serial monitor
    ph.begin(); //mulai untuk pembacaan sensor ph meter
    sensors.begin(); //mulai untuk pembacaan sensor ds18b20
    pinMode(buzzer, OUTPUT);
    pinMode(ledHijau, OUTPUT);
}
 
void loop()
{
  sensors.requestTemperatures(); 
  static unsigned long timepoint = millis();
    if(millis()-timepoint>1000U){                 //time interval: 1s
        timepoint = millis();
        tegangan = analogRead(sensor_ph)/2500.0*5000; //mengubah tegangan analog menjadi digital dan menjadi tegangan
        suhu = sensors.getTempCByIndex(00);
        nilaiph = ph.readPH(tegangan,suhu);  //konversi tegangan menjadi ph meter dengan kompensasi suhu
        Serial.print("Celsius temperature: ");
        Serial.print(suhu,1); //nilai pembacaan suhu
        Serial.print("^C  pH:");
        Serial.println(nilaiph,2); //nilai pembacaan ph meter
    }
    ph.calibration(tegangan,suhu); 
    
String status1 = "baik";
String status2 = "kurang";
String statusfix;
if (suhu < 22 || nilaiph <8.6 || suhu > 32 || nilaiph > 9.3){
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledHijau, LOW);
//  Serial.print(status2);
//  statusfix=status2;

  }else if (suhu >= 22 || nilaiph >= 8.6 || suhu <= 32 || nilaiph <= 9.3){
  digitalWrite(ledHijau, HIGH);
  digitalWrite(buzzer, LOW);
//    Serial.print(status1);
//    statusfix=status1;

  }
}
