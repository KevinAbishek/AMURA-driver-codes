/*
 * Setup values for UART comms port, jog buttons, limit switches, buzzer, microscopy lamp, X and Y stepper speed, resolution and power settings
 */

void setup ()
{
  pinMode (XRESETpin, OUTPUT) ;
  pinMode (YRESETpin, OUTPUT) ;
  pinMode (B1, INPUT_PULLUP) ;
  pinMode (B2, INPUT_PULLUP) ;
  pinMode (LED1, OUTPUT) ;
  pinMode (xLIM,  INPUT)  ;
  pinMode (yLIM,  INPUT)  ;
  pinMode (buzz,  OUTPUT)  ;
  analogWrite (LED1, inten)  ;
  analogWrite (buzz,  0)  ;
  digitalWrite (XRESETpin, HIGH) ;
  digitalWrite (YRESETpin, HIGH) ;
  delay (10) ;
  digitalWrite (XRESETpin, LOW) ;
  digitalWrite (YRESETpin, LOW) ;
  delay (1) ;
  Serial.begin (115200) ;
  delay (1000) ;
  pinMode (XSTEPpin, OUTPUT) ;
  pinMode (YSTEPpin, OUTPUT) ;
  pinMode (XDIRpin, OUTPUT) ;
  pinMode (YDIRpin, OUTPUT) ;
  Xstepper.begin (60, s, 2, 0, 1, 0, i) ;
  Ystepper.begin (60, s, 2, 0, 1, 0, i) ;
  delay(10) ;
}
