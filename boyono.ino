#include <Adafruit_NeoPixel.h>
#include "led.h"


#define DELAY_MAX 300
#define BUZZ 12
#define BUT_CHANGE 3
#define BUT_L3 5
#define BUT_L2 4
#define BUT_L1 2

void setup() {                
  // initialize shift register PINS
  pinMode(BUZZ, OUTPUT);
  pinMode(BUT_L3, INPUT);
  pinMode(BUT_L2, INPUT);
  pinMode(BUT_L1, INPUT);  
  pinMode(BUT_CHANGE, INPUT);
  attachInterrupt(1, button_attention, RISING);  
  init_leds();
  Serial.begin(115200);
  randomSeed(analogRead(A0)*analogRead(A1)); 
}

unsigned char game_i=0;
unsigned char game_ilast=0;
unsigned char game=0;

void button_attention() {
  while(TCNT0!=0);
  do {
      while(TCNT0!=254);
      while(TCNT0!=253);      
  }
  while ((digitalRead(BUT_CHANGE))==HIGH);
  while(TCNT0!=250);
  while(TCNT0!=249);  
  while(TCNT0!=248);    
  game_i++;
}

//================================================================================
// The Main LOOP                                                                  
//================================================================================
void loop() {           // R, B, G
  while(1){
     if (game_i != game_ilast){
       game_ilast=game_i;
       game++;
       if (game >= MAX_GAME)
           game=0;
     }
     switch (game) {
        case SEMAFORO_GAME:
            semaforo_lights();
        break;
        case SEMAFORO_NIGHT:
            semaforo_nightlight();
        break;
        case SIMON_GAME:
            simon_run();
        break;
        case LUZ_NOCHE:
            nightlight();
        break;  
        case EFECTO_LUZ_NOCHE:
            nightlight_efect();
        break;
        case OFF:
            clear_leds(0);
            clear_leds(1);            
            clear_leds(2);            
        break;        
     }
  }
}
