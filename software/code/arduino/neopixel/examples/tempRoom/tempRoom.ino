// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            6
#define NUMPIXELS      180
#define GREEN_LED      12

int temperatureSensor[5] = {A0,A1,A2,A3,A4}; // select the input pin for the potentiometer
int samplingInterval = 2000;
int sampleNumber = 0;
int numberOfSamples = 15;
float averageTemperature = 50;  // variable to store the value coming from the sensor
float roomTemperature = 10000;
int difference = 3;

int px_value[11] = {0,26,51,77,102,128,153,179,204,230,255};
int brightness  = px_value[0];

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pinMode(GREEN_LED,OUTPUT); // green led
  Serial.begin(9600);
  Serial.println("Cooling down experiment...");
  
  pixels.begin(); // This initializes the NeoPixel library.
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(brightness,brightness,brightness)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  Serial.println("N , Tavg, Troom");
}

void loop() {
 if(abs(averageTemperature)>=21){
    roomTemperature = getTemperature(analogRead(temperatureSensor[0]));
    ++sampleNumber;
    averageTemperature = 0; // reset average
    // read data from all sensor and find the average
    for(int i=0; i<4; ++i){
      int value = getTemperature(analogRead(temperatureSensor[i+1]));//getTemperature(analogRead(temperatureSensor[i]));
      averageTemperature += value;
    }
    averageTemperature /= 4;
    Serial.print(sampleNumber);
    Serial.print(" , ");
    Serial.print((int)averageTemperature);
    Serial.print(" , ");
    Serial.println((int)roomTemperature);
    // delay to next sample
    delay(samplingInterval);
    digitalWrite(GREEN_LED,LOW);
  }else{
    digitalWrite(GREEN_LED,HIGH);
  }
}

int getTemperature(float temp){
  return (temp*5/1024-0.5)/0.01;
}
