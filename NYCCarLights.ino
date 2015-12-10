#include <Adafruit_DotStar.h>
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET
#include "car.h"

#define NUMPIXELS 60                             // Number of LEDs in strip
#define DATAPIN   4
#define CLOCKPIN  5
#define BAUD      9600
#define CREATE    20
#define MAXCARS   5

Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
int head = 0, tail = -2;
// hex   Green Red   Blue
// 0x    00    00    00
uint32_t colors[] = { 0x000000
                    , 0x010101
                    , 0x020202
                    , 0x030303
                    , 0x040404
                    , 0x050505
                    };
int colorLength = sizeof(colors)/sizeof(uint32_t);
int createCar = 0;
Car* cars[MAXCARS];

void setup() {
    Serial.begin(BAUD);
    while (!Serial);

    Serial.println("Random number generator started.");

    for (int i = 0; i < MAXCARS; i++) {
        Car *car = new Car(&strip);
        cars[i] = car;
    }

    strip.begin();                               // Initialize pins for output
    strip.show();                                // Turn all LEDs off ASAP
    Serial.println("LED's ready.");
    Serial.println("Simulation starting.");
}

void loop() {

    if (createCar++ == CREATE) {
        createCar = 0;
        Serial.println("Creating new car.");

        for (int i = 0; i < MAXCARS; i++) {
            
            if (!cars[i]->isActive()) {
                cars[i]->create();
                cars[i]->setActive(true);
                
                Serial.print("Start: ");
                Serial.print(cars[i]->getStart());
                Serial.print(", End: ");
                Serial.print(cars[i]->getEnd());
                Serial.print(", Length: ");
                Serial.print(cars[i]->getPathLength());
                Serial.print(", Head: ");
                Serial.print(cars[i]->getHead());
                Serial.print(", Tail: ");
                Serial.println(cars[i]->getTail());
                
                Serial.println("Car created!");
                break;
            }
        }
    }

    for (int i = 0; i < colorLength; i++) {
        strip.setPixelColor(head, colors[i]);
        strip.setPixelColor(tail, colors[colorLength - i - 1]);

        strip.show();
        delay(5); 
    }

    if(++head >= NUMPIXELS) {
        head = 0;
    }

    if(++tail >= NUMPIXELS) {
        tail = 0;
    }
}
