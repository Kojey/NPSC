/**
 * @brief: Get average temperature of the board using four temperature sensors
 * @author: Othniel Konan
 * @version: v1.0
 * @date: 2 Nov 2017
 */
int temperatureSensor[5] = {A0, A1,A2,A3, A4}; // select the input pin for the potentiometer
int samplingInterval = 2000;
int sampleNumber = 0;
int numberOfSamples = 15;
float averageTemperature = 0;  // variable to store the value coming from the sensor
float previousTemperature = 10000;
int difference = -1;
void setup() {
  Serial.begin(9600);
  delay(samplingInterval);
  
  Serial.println("Current drawn: X A");
  Serial.println("Sample,T1,T2,T3,T4,Tavg");
}

void loop() {
 while(abs(averageTemperature-previousTemperature)>=difference){
    previousTemperature = averageTemperature;
    ++sampleNumber;
    averageTemperature = 0; // reset average
    // read data from all sensor and find the average
    Serial.print(sampleNumber);
    Serial.print(',');
    for(int i=0; i<4; ++i){
      int value = getTemperature(analogRead(temperatureSensor[i]));//getTemperature(analogRead(temperatureSensor[i]));
      Serial.print(value);
      Serial.print(',');
      averageTemperature += value;
    }
    averageTemperature /= 4;
    Serial.println(averageTemperature);
    // delay to next sample
    delay(samplingInterval);
  }
}

int getTemperature(float temp){
  return (temp*5/1024-0.5)/0.01;
}

