//                        161 0xA1  1010 0001 Force Field
//                        164 0xA4  1010 1000 Green Buoy (meaning Starboard, or Right)
//                        168 0xA8  1010 0100 Red Buoy (meaning Port, or Left)
//                        162 0xA2  1010 0011 Virtual Wall field (working with Roomba 650)
//


//Bit 0 - 1ms on, 3 ms off -___
//Bit 1 - 3ms on, 1 ms of ---_


int green[] = {1, 1, 1, 0   ,   1, 0, 0, 0 ,    1, 1, 1, 0   ,   1, 0, 0, 0 ,     1, 1, 1, 0  ,  1, 0, 0, 0 ,   1, 0, 0, 0 ,   1, 0, 0, 0  };
int red[] =   {1, 1, 1, 0   ,   1, 0, 0, 0 ,    1, 1, 1, 0   ,   1, 0, 0, 0 ,     1, 0, 0, 0  ,  1, 1, 1, 0 ,   1, 0, 0, 0 ,   1, 0, 0, 0  };
int field[] = {1, 1, 1, 0   ,   1, 0, 0, 0 ,    1, 1, 1, 0   ,   1, 0, 0, 0 ,     1, 0, 0, 0  ,  1, 0, 0, 0 ,   1, 1, 1, 0 ,   1, 1, 1, 0  };



void setup() {
  pinMode(11, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);


  // set up Timer 2
  TCCR2A = _BV (COM2A0) | _BV(WGM21);  // CTC, toggle OC2A on Compare Match
  TCCR2B = _BV (CS20);   // No prescaler
  OCR2A =  209;          // compare A register value (210 * clock speed)
  //  = 13.125 nS , so frequency is 1 / (2 * 13.125) = 38095

  DDRD = DDRD | B11111100;// this is safer as it sets pins 2 to 7 as outputs
  // without changing the value of pins 0 & 1, which are RX & TX


  PORTD = B01000000;// sets digital pins 7,5,3 HIGH
}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i = 0; i < 32; i++)
  {
    byte b = 0;
    if (green[i] == 1)  b = b |  B10000000;
    if (red[i] == 1)    b = b |  B01000000;
    if (field[i] == 1)  b = b |  B00100000;
    PORTD = b;

    delayMicroseconds(1000);
  }

  delay(100);

}
