#define UPD_TIME 50
#define RED_LIGHT 2
#define YEL_LIGHT 1
#define GRN_LIGHT 0

unsigned char semaforo_stat=0;
unsigned char internal_count=0;

void semaforo_lights (void) {
  delay(UPD_TIME);
  internal_count++;
  switch(semaforo_stat) {
    case ROJO:
        clear_leds(YEL_LIGHT);
        clear_leds(GRN_LIGHT);
        set_color_lamp(RED_LIGHT, ROJO);
        if (internal_count>=80) {
            semaforo_stat++;
            internal_count=0;
        }
     break;
     case AMARILLO:   
        set_color_lamp(YEL_LIGHT, AMARILLO);
        if (internal_count>=30) {
            semaforo_stat++;
            internal_count=0;
        }
     break;
     case VERDE:   
        clear_leds(RED_LIGHT);
        clear_leds(YEL_LIGHT);
        set_color_lamp(GRN_LIGHT, VERDE);
        if (internal_count>=100) {
            semaforo_stat++;
            internal_count=0;
        }
     break;
     default:   
        clear_leds(GRN_LIGHT);
        set_color_lamp(YEL_LIGHT, AMARILLO);
        if (internal_count>=30) {
            semaforo_stat=0;
            internal_count=0;
        }
     break;
  }
}

#define AMARILLO_ON  0
#define AMARILLO_OFF 1
void semaforo_nightlight(void){
  delay(UPD_TIME);
  internal_count++;
  switch(semaforo_stat) {
    case AMARILLO_ON:
        clear_leds(RED_LIGHT);
        clear_leds(GRN_LIGHT);
        set_color_lamp(YEL_LIGHT, AMARILLO);
        if (internal_count>=15) {
            semaforo_stat++;
            internal_count=0;
        }
     break;
     default :   
        clear_leds(RED_LIGHT);
        clear_leds(GRN_LIGHT);
        clear_leds(YEL_LIGHT);
        if (internal_count>=15) {
            semaforo_stat=0;
            internal_count=0;
        }
     break;
  }
}
  

