
void nightlight(void){
   set_color_lamp(0, AMARILLO);
   set_color_lamp(1, AMARILLO);
   set_color_lamp(2, AMARILLO);
}

#define LIGHT_DELAY 50
#define MAX_VALUE 600
#define STEP 10
#define MIN_VALUE 30

unsigned percent[3]={MIN_VALUE+3*STEP,MAX_VALUE-2*STEP, MAX_VALUE/2};
unsigned char color_n[3]={0,1,2};
unsigned delta[3] ={STEP,STEP,STEP};

void inc_percen(unsigned * per, unsigned * del, unsigned char * col_n)
{
  int i;
  for (i=0;i<3;i++) {
     per[i]=per[i]+del[i];
     if (per[i] > MAX_VALUE) {
        del[i]=-STEP;
     }
     if (per[i] == MIN_VALUE) {
        del[i]=STEP;
        col_n[i]=random(0,7);
     }
  }
}

void nightlight_efect (void) {
  delay(LIGHT_DELAY);
  set_color_lamp_aten(0, color_n[0], percent[0]);
  set_color_lamp_aten(1, color_n[1], percent[1]);
  set_color_lamp_aten(2, color_n[2], percent[2]);
  inc_percen(percent,delta, color_n);
}  
  
  
