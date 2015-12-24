#include <Adafruit_DotStar.h>
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET
#include "car.h"

#define NUMPIXELS 60                             // Number of LEDs in strip
#define DATAPIN   4
#define CLOCKPIN  5
#define BAUD      9600
#define CREATE    5
#define MAXCARS   5


Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

// COLOR CODE
// hex   Green Red   Blue
// 0x    00    00    00

uint32_t leds[NUMPIXELS];
uint32_t off = 0x000000;

int createCar = 0;
Car* cars[MAXCARS];

void setup() {
    Serial.begin(BAUD);
    while (!Serial);

    Serial.println("Random number generator started.");

    for (int i = 0; i < MAXCARS; i++) {
        Car *car = new Car(leds, NUMPIXELS, i);
        cars[i] = car;
    }

    for (int i = 0; i < NUMPIXELS; i++)
        leds[i] = off;

    strip.begin();                               // Initialize pins for output
    strip.show();                                // Turn all LEDs off ASAP
    Serial.println("LED's ready.");
    Serial.println("Simulation starting.");
}

void loop() {
    // Counter for each interation
    if (createCar++ == CREATE) {
        // Serial.println("Create car?");
        createCar = 0;

        for (int i = 0; i < MAXCARS; i++) {
            // Is car disabled
            // Serial.print("Car ");
            // Serial.print(i);
            // Serial.println(" inactive car?");
            // 0 = Active
            // 1 = Disabled
            // Serial.println(!cars[i]->isActive());
            // If disabled
            if (!cars[i]->isActive()) {
                // Serial.println("Creating new car!");
                // Serial.print("Car number: ");
                // Serial.println(cars[i]->create());
                cars[i]->create();
                cars[i]->setActive(true);
                
                // Serial.print("Start: ");
                // Serial.print(cars[i]->getStart());
                // Serial.print(", End: ");
                // Serial.print(cars[i]->getEnd());
                // Serial.print(", Length: ");
                // Serial.print(cars[i]->getPathLength());
                // Serial.print(", Head: ");
                // Serial.print(cars[i]->getHead());
                // Serial.print(", Tail: ");
                // Serial.println(cars[i]->getTail());
                
                // Serial.println("Car created!");
                break;
            }
        }
    }

    for (int i = 0; i < NUMPIXELS; i++)
        leds[i] = off;
    
    for (int i = 0; i < MAXCARS; i++)
        Serial.println(cars[i]->nextStep());

    for (int i = 0; i < NUMPIXELS; i++) {
        strip.setPixelColor(i, leds[i]);
        delay(1);    
    }

    strip.show();
    delay(10); 
}
