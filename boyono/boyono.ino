
#include <Adafruit_NeoPixel.h>
#include "led.h"


int maxDelay = 300;
int potentiometer = 12;
int selectorButton = 3;
int button1 = 2;
int button2 = 4;
int button3 = 5; 

void setup() {                
  // initialize shift register PINS
  pinMode(potentiometer, OUTPUT);
  pinMode(button3, INPUT);
  pinMode(button2, INPUT);
  pinMode(button1, INPUT);  
  pinMode(selectorButton, INPUT);
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
  while ((digitalRead(selectorButton))==HIGH);
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
