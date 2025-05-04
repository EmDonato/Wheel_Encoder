# Encoder Library for Arduino

This is a lightweight and easy-to-use Arduino library for handling rotary encoders to measure motor speed in terms of **ticks**, **revolutions**, and **RPM** (rotations per minute).

## Features

- Count encoder ticks  
- Calculate number of revolutions  
- Estimate motor speed (RPM)  
- Customizable encoder resolution  
- Timestamp and tick interval handling for speed computation  
- Simple and intuitive API  

## Installation

1. Download or clone this repository.  
2. Copy the `Encoder.h` and `Encoder.cpp` files into your Arduino project folder.  
3. Include the library in your sketch:

   ```cpp
   #include "Encoder.h"
## Usage
### Initialization

Create an Encoder object. You can optionally specify the encoder resolution (number of ticks per revolution):

    ```cpp
     Encoder encoder1;      // default resolution = 20
     Encoder encoder2(100); // custom resolution

### Tick Management

Call addTick() inside the encoder's interrupt service routine (ISR) to count each encoder pulse:
         ```cpp
         void encoderISR() {
             encoder1.addTick();
         }

Attach the ISR in setup():
     ```cpp
     attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), encoderISR, RISING);

### Reading Encoder Data
   ```cpp
   int ticks       = encoder1.getTicks();
   float revs      = encoder1.getRevolutions();
   float rpm       = encoder1.getRPM();
   ```
To calculate RPM, you need to provide the time between ticks (or revolutions):
   ```cpp
   unsigned long now = micros();
   encoder1.setTickInterval(now - previousTime);  // time in µs
   previousTime = now;
   encoder1.setTimestamp(now);                   // optional: store current timestamp
   ```
### Resetting the Encoder

Reset all internal counters and timers:
```cpp
   encoder1.reset();
```   
### API Reference

| Method                                      | Description                                          |
|---------------------------------------------|------------------------------------------------------|
| `Encoder()`                                 | Default constructor (20 ticks/rev)                   |
| `Encoder(int resolution)`                   | Constructor with custom resolution                   |
| `void addTick()`                            | Increments tick count (call in ISR)                  |
| `int getTicks()`                            | Returns total tick count                             |
| `float getRevolutions()`                    | Returns number of revolutions                        |
| `float getRPM()`                            | Returns estimated speed in RPM                       |
| `void changeResolution(int newRes)`         | Changes encoder resolution                           |
| `void setTimestamp(unsigned long time)`     | Sets last timestamp (in µs)                          |
| `unsigned long getTimestamp()`              | Returns last stored timestamp                        |
| `void setTickInterval(unsigned long time)`  | Sets time between ticks (in µs)                      |
| `unsigned long getTickInterval()`           | Returns tick interval                                |
| `void reset()`                              | Resets ticks, timestamp, and tick interval to zero   |

## Example
  ```cpp
  #include "Encoder.h"
  
  Encoder encoder(100);
  unsigned long prevTime = 0;
  
  void setup() {
      Serial.begin(9600);
      attachInterrupt(digitalPinToInterrupt(2), encoderISR, RISING);
      prevTime = micros();
  }
  
  void loop() {
      unsigned long now = micros();
      encoder.setTickInterval(now - prevTime);
      prevTime = now;
      encoder.setTimestamp(now);
  
      Serial.print("Ticks: ");
      Serial.print(encoder.getTicks());
      Serial.print(" | RPM: ");
      Serial.println(encoder.getRPM());
  
      delay(100);
  }
  
  void encoderISR() {
      encoder.addTick();
  }
  ```
