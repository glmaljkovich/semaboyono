#include "led.h"
#include "pitches.h"

unsigned char setuped_simon=0;

#define SIZE_SIMON 4
#define BUZZER 11
unsigned char speed_l;
unsigned char sequence[SIZE_SIMON];
unsigned char index_seq;

void setup_simon() {
   int i;
   for (i=0; i<SIZE_SIMON;i++)
     {
      sequence[i]=random(0,3);
     }
   index_seq=0;
   setuped_simon=1;
}

unsigned char color_lamp (unsigned char lamp)
{
  if (lamp==0)
     return VERDE;
  if (lamp==1)
     return AMARILLO;
  if (lamp==2)
     return ROJO;
}

void show_lamp_simon(unsigned char index)
{
 clear_leds(0);
 clear_leds(1);
 clear_leds(2);
 delay(200);
 set_color_lamp(index, color_lamp(index));
 delay(1000/((20/10)+1));
 clear_leds(0);
 clear_leds(1);
 clear_leds(2);
}

void show_simon(unsigned char large) {
  int i;
  for (i=0;i<=large;i++){
      show_lamp_simon(sequence[i]);
  }
}

unsigned char read_user_seq(void) {
  while(1) {
     if (game_i!=game_ilast)
        return 3;
     if (digitalRead(GREEN_BUTTON)== HIGH){
//       playNote('c', 120);
//       tone(8, NOTE_C8, 1000/4);
       return 0;
     }

     if (digitalRead(BLUE_BUTTON)== HIGH){
//       playNote('f', 120);
//       tone(8, NOTE_E7, 1000/4);
       return 1;
     }

     if (digitalRead(RED_BUTTON)== HIGH){
//       playNote('C', 120);
//       tone(8, NOTE_G6, 1000/4);
       return 2;
     }
  }
}

void show_error(void) {
   unsigned char i;
   for (i=0; i<3 ; i++) {
      clear_leds(0);
      clear_leds(1);
      clear_leds(2);
      delay(200);
      show_crux_lamp(0, ROJO);
      show_crux_lamp(1, ROJO);
      show_crux_lamp(2, ROJO);
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
      show_tilde_lamp(0, VERDE);
      show_tilde_lamp(1, VERDE);
      show_tilde_lamp(2, VERDE);
      delay(450);
// sound
   }
   delay(500);
    clear_leds(0);
    clear_leds(1);
    clear_leds(2);
}

void show_three_dots(void) {
   unsigned char i;
   for (i=0; i<3 ; i++) {
      clear_leds(0);
      clear_leds(1);
      clear_leds(2);
      delay(200);
      show_dot_lamp(0, ROJO);
      show_dot_lamp(1, AMARILLO);
      show_dot_lamp(2, VERDE);
      delay(450);
// sound
   }
}

void show_win(void) {
   unsigned char i;
   for (i=0;i<10;i++){
      clear_leds(0);
      clear_leds(1);
      clear_leds(2);
      delay(2);
      show_fire_lamp(random(0,3), random(0,7));
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
      show_lamp_simon(user);
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
  if (setuped_simon==0){
    show_three_dots();
    setup_simon();
  }
  run_simon();
}
