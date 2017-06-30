#include "led.h"
#include "pitches.h"

unsigned char setuped_simon=0;

#define SIZE_SIMON 4
#define BUZZER 11
unsigned char speed_l;
unsigned char sequence[SIZE_SIMON];
unsigned char index_seq;

// Declaramos algunas variables para los efectos musicales
int length = 15;                  // Numero de notas de la melodia
char notes[] = "ccggaagffeeddc "; // Notas de la melodia (cada letra es una nota distinta)
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };  // Duracion de cada tono en un array
int tempo = 120;  //Tempo de la melodia
int wait = 500;                // Retraso segun la secuencia se incrementa
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

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
       tone(8, NOTE_C8, 1000/4);
       return 0;
     }

     if (digitalRead(BLUE_BUTTON)== HIGH){
//       playNote('f', 120);
       tone(8, NOTE_E7, 1000/4);
       return 1;
     }

     if (digitalRead(RED_BUTTON)== HIGH){
//       playNote('C', 120);
       tone(8, NOTE_G6, 1000/4);
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
}

void show_win(void) {
   unsigned char i;
   for (i=0;i<SIZE_SIMON;i++){
      clear_leds(0);
      clear_leds(1);
      clear_leds(2);
      delay(2);
      show_fire_lamp(random(0,3), random(0,7));
      delay(400);
  }
}

// Funcion para definir las notas y sus frecuencias
 void playNote(char note, int duration) {
   char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
   int tones[] = { 2100, 1700, 1519, 1000, 1275, 1136, 1014, 612 };

   for (int i = 0; i < 8; i++) {
      if (names[i] == note) {
        playtone(tones[i], duration);
      }
   }
 }



// Funcion para definir las notas segun la duración y el tono
 void playtone(int tone, int duration) {
   for (long i = 0; i < duration * 1000L; i += tone *2) {
     digitalWrite(BUZZER, HIGH);
     delayMicroseconds(tone);
     digitalWrite(BUZZER, LOW);
     delayMicroseconds(tone);
   }
 }

void elPlaytone(){
    // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void greeting() {
// digitalWrite(led_rojo, HIGH);
// digitalWrite(led_verde, HIGH);
// digitalWrite(led_amarillo, HIGH);
// digitalWrite(led_azul, HIGH);

for (int i = 0; i < length; i++) {
 if (notes[i] == ' ') {
   delay(beats[i] * tempo); // rest
 } else {
   playNote(notes[i], beats[i] * tempo);
 }
 delay(tempo / 2);
}
  delay(500);
}

void run_simon(void) {
  unsigned char i;
  unsigned char user;
  show_simon(index_seq);
  // digitalWrite(11, HIGH);
  // greeting();
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
  if (setuped_simon==0)
     setup_simon();
  run_simon();
}
