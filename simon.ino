#include "led.h"

unsigned char setuped_simon=0;

#define SIZE_SIMON 50
unsigned char speed_l;
unsigned char sequence[SIZE_SIMON];
unsigned char index_seq;

#define BUT_L3 5
#define BUT_L2 4
#define BUT_L1 2

void setup_simon() {
   int i;
   for (i=0; i<SIZE_SIMON;i++)
     {
      sequence[i]=random(0,3);
     } 
   index_seq=0;
   setuped_simon=1;
}

unsigned char color_lump (unsigned char lump)
{
  if (lump==0)
     return VERDE;
  if (lump==1)
     return AMARILLO;
  if (lump==2)
     return ROJO;
}

void show_lump_simon(unsigned char index)
{
 clear_leds(0);
 clear_leds(1);
 clear_leds(2);
 delay(200);         
 set_color_lump(index, color_lump(index)); 
 delay(1000/((20/10)+1));
 clear_leds(0);
 clear_leds(1);
 clear_leds(2);       
}

void show_simon(unsigned char large) {
  int i;
  for (i=0;i<=large;i++){
      show_lump_simon(sequence[i]);
  }
}

unsigned char read_user_seq(void) {
  while(1) {
     if (game_i!=game_ilast)
        return 3;
     if (digitalRead(BUT_L1)== HIGH)
        return 0;
     if (digitalRead(BUT_L2)== HIGH)
        return 1;        
     if (digitalRead(BUT_L3)== HIGH)
        return 2;
  }
}

void show_error(void) {
   unsigned char i;
   for (i=0; i<3 ; i++) {
      clear_leds(0);
      clear_leds(1);
      clear_leds(2);
      delay(200);      
      show_crux_lump(0, ROJO);
      show_crux_lump(1, ROJO);
      show_crux_lump(2, ROJO);
      delay(450);
// sound      
   }
}

void show_correct(void) {
   unsigned char i;
   for (i=0; i<3 ; i++) {
      clear_leds(0);
      clear_leds(1);
      clear_leds(2);      
      delay(200);
      show_tilde_lump(0, VERDE);
      show_tilde_lump(1, VERDE);
      show_tilde_lump(2, VERDE);
      delay(450);
// sound      
   }
}

void show_win(void) {
   unsigned char i;
   for (i=0;i<SIZE_SIMON;i++){
      clear_leds(0);
      clear_leds(1);
      clear_leds(2);
      delay(2);   
      show_fire_lump(random(0,3), random(0,7));
      delay(400);
  }
}  

void run_simon(void) {
  unsigned char i;
  unsigned char user;
  show_simon(index_seq);
  for (i=0; i<=index_seq; i++)
     {
      user=read_user_seq();
      if (user==3) {
         setuped_simon=0;
         break;
      }
      show_lump_simon(user);
      if (user!= sequence[i])
        {
          show_error();
          index_seq=0;
          setuped_simon=0;
          break;
        }
     }
  if (setuped_simon!=0)
    {      
      show_correct();
      index_seq++;
      if (index_seq== SIZE_SIMON){
         index_seq=0;
         setuped_simon=0;
         show_win();
         randomSeed(analogRead(A0)*analogRead(A1)+millis());
      }
    }
}    
  
void simon_run (void) {
  if (setuped_simon==0)
     setup_simon();  
  run_simon();
}

  
