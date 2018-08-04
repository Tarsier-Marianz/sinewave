/*
    Sources: https://www.electronicshub.org/sinusoidal-waveform/
             https://www.electronics-tutorials.ws/accircuits/sinusoidal-waveform.html

    Am       = is the amplitude of the waveform.
    ωt       = is the angular frequency of the waveform in radian/sec.
    Φ (phi)  = is the phase angle in degrees or radians that the waveform
               has shifted either left or right from the reference point.

    NOTES
    2π        = 360 deg
    360deg/2π = 57.3 deg

    FORMULAS
    ƒ        = 1/T
    ω        = 2πƒ   or 2π/t  (rad/sec) angular velocity

*/


/*initializing output Analog pins */
int PIN_PHASE1          = A0;   // Pin0 of arduino analog
int PIN_PHASE2          = A1;   // Pin1 of arduino analog
int PIN_PHASE3          = A2;   // Pin2 of arduino analog

/*declaration of variables handling values */
float freq              = 60;     // 60Hz by default
float Am                = 2.5;     // let us set amplitude to 20

void setup() {
  Serial.begin(115200);
  /* setting PINs as an output pin*/
  pinMode(PIN_PHASE1, OUTPUT);
  pinMode(PIN_PHASE2, OUTPUT);
  pinMode(PIN_PHASE3, OUTPUT);
}

void loop() {
  generate_sinusoidal();
}

void generate_sinusoidal() {
  float angle     = 2 * PI / 3;                       // convert constant angle offset 120 degree to radian (source: see above sources)
  float time_sec  = millis() / 1000.0;                // convert milli to second
  float T         = time_sec / freq;                  // calculate the period by 1/f (seconds)
  float aV        = 2 * PI * freq;                    // ω = calculate angular velocity using formula 2πƒ (rad/sec)
  float y1        = Am + Am * sin ( aV * T );         // and now the formula to to get the value in generating Sinusoidal
  float y2        = Am + Am * sin ( aV * T - angle ); // for the second phase
  float y3        = Am + Am * sin ( aV * T + angle ); // for the third phase

  printToAnalogPinouts(y1, y2, y3);                   // write values to analog pins
  printToSerial(Am, y1, y2, y3);                      // print values to serial output monitor
}

void printToAnalogPinouts(float y1, float y2, float y3) {
  analogWrite(PIN_PHASE1, y1);
  analogWrite(PIN_PHASE2, y2);
  analogWrite(PIN_PHASE3, y3);
}

void printToSerial(float amp, float y1, float y2, float y3) {
  Serial.print(amp);
  Serial.print(", ");
  Serial.print(y1);
  Serial.print(", ");
  Serial.print(y2);
  Serial.print(", ");
  Serial.println(y3);
}

