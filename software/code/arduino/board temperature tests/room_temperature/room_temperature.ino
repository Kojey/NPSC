/**
 * @brief: Get average temperature of the board using four temperature sensors
 * @author: Othniel Konan
 * @version: v1.0
 * @date: 2 Nov 2017
 */
#define RED_LED     8
#define GREEN_LED   9
int temperatureSensor[4] = {A0, A1,A2,A3}; // select the input pin for the potentiometer
int samplingInterval = 2000;
int sampleNumber = 0;
int numberOfSamples = 15;
float averageTemperature = 0;  // variable to store the value coming from the sensor
float roomTemperature = 25;
int difference = -1;

void setup() {
  delay(samplingInterval);
  pinMode(RED_LED,OUTPUT);  // RED led
  pinMode(GREEN_LED,OUTPUT);  // GREEN led
  Serial.begin(9600);
  Serial.println("Board cooling down");
  Serial.println("Sample , Board , Room");
}

void loop() {
  // get room temperature
  roomTemperature = getTemperature(analogRead(temperatureSensor[4]));
  // update LEDs status based on the difference between the board 
  //  temperature and the room temperature
  if(abs(averageTemperature-roomTemperature)>=difference){
    ++sampleNumber;
    averageTemperature = 0; // reset average
    // read data from all sensor and find the average
    Serial.print(sampleNumber);
    Serial.print(" , ");
    for(int i=0; i<4; ++i){
      int value = getTemperature(analogRead(temperatureSensor[i]));
      averageTemperature += value;
    }
    averageTemperature /= 4;
    Serial.print(averageTemperature);
    Serial.print(" , ");
    // delay to next sample
    delay(samplingInterval);
    digitalWrite(RED_LED,HIGH);
    digitalWrite(GREEN_LED,LOW);
  }else{
    digitalWrite(RED_LED,LOW);
    digitalWrite(GREEN_LED,HIGH);
  }
  Serial.println(roomTemperature);
}

int getTemperature(float temp){
  return (temp*5/1024-0.5)/0.01;
}

