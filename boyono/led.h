#define PIN_L1 6
#define PIN_L2 7
#define PIN_L3 8
#define BRILLO_PIN A0

#define ROJO 0
#define AMARILLO 1
#define VERDE 2
#define AZUL 3
#define ROSA 4
#define CELESTE 5
#define NARANJA 6
#define BLANCO 7

#define SEMAFORO_GAME    0
#define SEMAFORO_NIGHT   1
#define SIMON_GAME       2
#define EFECTO_LUZ_NOCHE 3
#define OFF 4
#define MAX_GAME 5

extern const unsigned char colors[8][3];
extern unsigned char game_i;
extern unsigned char game_ilast;
