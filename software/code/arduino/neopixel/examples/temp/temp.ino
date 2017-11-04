// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            6
#define NUMPIXELS      180

int temperatureSensor[4] = {A0, A1,A2,A3}; // select the input pin for the potentiometer
int samplingInterval = 2000;
int sampleNumber = 0;
int numberOfSamples = 15;
float averageTemperature = 0;  // variable to store the value coming from the sensor
float previousTemperature = 10000;
int difference = -1;

int brightness = 0;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  Serial.begin(9600);
  Serial.println("Starting experiment...");
  Serial.print("Brightness: ");
  Serial.println(brightness);
  
  pixels.begin(); // This initializes the NeoPixel library.
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,15,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  Serial.println("N , T1 , T2 , T3 , T4 , Tavg");
}

void loop() {
 while(abs(averageTemperature-previousTemperature)>=difference){
    previousTemperature = averageTemperature;
    ++sampleNumber;
    averageTemperature = 0; // reset average
    // read data from all sensor and find the average
    Serial.print(sampleNumber);
    Serial.print(" , ");
    for(int i=0; i<4; ++i){
      int value = getTemperature(analogRead(temperatureSensor[i]));//getTemperature(analogRead(temperatureSensor[i]));
      Serial.print(value);
      Serial.print(" , ");
      averageTemperature += value;
    }
    averageTemperature /= 4;
    Serial.println((int)averageTemperature);
    // delay to next sample
    delay(samplingInterval);
  }
}

int getTemperature(float temp){
  return (temp*5/1024-0.5)/0.01;
}
