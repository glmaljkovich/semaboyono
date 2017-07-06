#include "led.h"

const unsigned char colors[8][3]={{255, 0, 0},
                                         {255, 130, 0},
                                         {0, 255, 0},
                                         {0, 0, 255},
                                         {255, 0, 255},
                                         {0, 200, 255},
                                         {255, 45, 0},
                                         {255, 255, 240}};

Adafruit_NeoPixel strip[3] = {Adafruit_NeoPixel(7, PIN_L1, NEO_GRB + NEO_KHZ800), Adafruit_NeoPixel(7, PIN_L2, NEO_GRB + NEO_KHZ800), Adafruit_NeoPixel(7, PIN_L3, NEO_GRB + NEO_KHZ800)};
void init_leds(void)
{
  pinMode(PIN_L1, OUTPUT);
  pinMode(PIN_L2, OUTPUT);
  pinMode(PIN_L3, OUTPUT);
  strip[0].begin();
  strip[0].show(); // Initialize all pixels to 'off'
  strip[1].begin();
  strip[1].show(); // Initialize all pixels to 'off'
  strip[2].begin();
  strip[2].show(); // Initialize all pixels to 'off'
}

void color_init (unsigned char * var, unsigned char * col)
{
  var[0]=col[0];
  var[1]=col[1];
  var[2]=col[2];
}

unsigned char aten_calc (unsigned char value, unsigned at){
  unsigned long aux=(((unsigned long)(value))*at)/1024;
  return ((unsigned char) (aux));
}

void update_led_aten(unsigned char l,unsigned char r, unsigned char g, unsigned char b, unsigned char n, unsigned aten)
{
 strip[l].setPixelColor(n,aten_calc(r,aten), aten_calc(b,aten), aten_calc(g,aten));
}

void update_leds_aten(unsigned char l,unsigned char r, unsigned char g, unsigned char b, unsigned aten)
{
 int i;
 for (i=0; i<8; i++) {
      update_led_aten(l,r,g,b,i,aten);
 }
strip[l].show();
}

void update_leds(unsigned char l,unsigned char r, unsigned char g, unsigned char b)
{
 int i;
 unsigned aten;
 aten = (analogRead(BRILLO_PIN));
 if (aten < 100)
    aten=0;
 if (aten > 924)
    aten=1024;
 update_leds_aten(l,r,g,b,aten);
}

void update_led(unsigned char l,unsigned char r, unsigned char g, unsigned char b, unsigned char n)
{
 unsigned aten;
 aten = (analogRead(BRILLO_PIN));
 if (aten < 100)
    aten=0;
 if (aten > 924)
    aten=1024;
 strip[l].clear();
 update_led_aten(l,r,g,b,n,aten);
 strip[l].show();
}

void update_led_not_show(unsigned char l,unsigned char r, unsigned char g, unsigned char b, unsigned char n)
{
 unsigned aten;
 aten = (analogRead(BRILLO_PIN));
 update_led_aten(l,r,g,b,n,aten);
}

void clear_leds(unsigned char l){
   strip[l].clear();
   strip[l].show();
}

void set_color_lamp (unsigned char lamp, unsigned char color) {
    unsigned char col[3];
    color_init(&col[0],(unsigned char *)&colors[color][0]);
    update_leds(lamp,col[0],col[1],col[2]);
}

void set_color_lamp_aten (unsigned char lamp, unsigned char color, unsigned aten) {
    unsigned char col[3];
    color_init(&col[0],(unsigned char *)&colors[color][0]);
    update_leds_aten(lamp,col[0],col[1],col[2], aten);
}

void show_crux_lamp (unsigned char lamp, unsigned char color) {
    unsigned char col[3];
    color_init(&col[0],(unsigned char *)&colors[color][0]);
    update_led_not_show(lamp,col[0],col[1],col[2],0);
    update_led_not_show(lamp,col[0],col[1],col[2],1);
    update_led_not_show(lamp,col[0],col[1],col[2],3);
    update_led_not_show(lamp,col[0],col[1],col[2],4);
    update_led_not_show(lamp,col[0],col[1],col[2],6);
    strip[lamp].show();
}

void show_dot_lamp (unsigned char lamp, unsigned char color){
    unsigned char col[3];
    color_init(&col[0],(unsigned char *)&colors[color][0]);
    update_led_not_show(lamp,col[0],col[1],col[2],6);
    strip[lamp].show();
}


void show_tilde_lamp (unsigned char lamp, unsigned char color) {
    unsigned char col[3];
    color_init(&col[0],(unsigned char *)&colors[color][0]);
    update_led_not_show(lamp,col[0],col[1],col[2],1);
    if (lamp!=0)
       update_led_not_show(lamp,col[0],col[1],col[2],3);
    else
       update_led_not_show(lamp,col[0],col[1],col[2],0);
    update_led_not_show(lamp,col[0],col[1],col[2],4);
    update_led_not_show(lamp,col[0],col[1],col[2],6);
    strip[lamp].show();
}

void show_fire_lamp (unsigned char lamp, unsigned char color) {
    unsigned char col[3];
    color_init(&col[0],(unsigned char *)&colors[color][0]);
    update_led(lamp,col[0],col[1],col[2],6);
    delay(200);
    clear_leds(lamp);
    col[0]=col[0]>>2;
    col[1]=col[1]>>2;
    col[2]=col[2]>>2;
    update_led_not_show(lamp,col[0],col[1],col[2],0);
    update_led_not_show(lamp,col[0],col[1],col[2],1);
    update_led_not_show(lamp,col[0],col[1],col[2],2);
    update_led_not_show(lamp,col[0],col[1],col[2],3);
    update_led_not_show(lamp,col[0],col[1],col[2],4);
    update_led_not_show(lamp,col[0],col[1],col[2],5);
    strip[lamp].show();
    delay(100);
    col[0]=col[0]>>2;
    col[1]=col[1]>>2;
    col[2]=col[2]>>2;
    update_led_not_show(lamp,col[0],col[1],col[2],0);
    update_led_not_show(lamp,col[0],col[1],col[2],1);
    update_led_not_show(lamp,col[0],col[1],col[2],2);
    update_led_not_show(lamp,col[0],col[1],col[2],3);
    update_led_not_show(lamp,col[0],col[1],col[2],4);
    update_led_not_show(lamp,col[0],col[1],col[2],5);
    strip[lamp].show();
}
