/*** Nao mudar esse código aqui ***/

//Camera RCA
#define WIDTH 85
#define HEIGHT 60
#define MINCAM 12
#define MAXCAM 82
#define WIDTH_REAL (MAXCAM-MINCAM)
#define CENTCAML (WIDTH_REAL/2)
#define CENTCAMR (CENTCAML+1)

//Servo
#define CENTRO_SERVO 18518 //FUTABA 18518                 TOWERPRO 18400
#define LIBERDADE_SERVO 320  // FUTABA 320                TOWERPRO 220
#define ESQUERDA_SERVO (CENTRO_SERVO-LIBERDADE_SERVO)
#define DIREITO_SERVO (CENTRO_SERVO+LIBERDADE_SERVO)








/*** Mudar apartir daqui ***/

//Algoritmo de Limiarização
#define DELTAAMOSTRA_MIN 40
#define DELTA_AMOSTRA_MIN 47
#define LIMIAR_PADRAO 85

//linhas de processamento
#define LINENOW 0
#define LINEBOOST 26

//Algoritmo de Deteccao de Bordas
#define WIDTH_TRACK 64//64
#define WIDTH_TRACK_RANGE 10

//Sistema de Controle
#define MIN_ERRO 29
#define SATURARERROIN 30

//Boost
#define WIDTH_BOOST 36
#define WIDTH_BOOST_TRACK 16 //19
#define NUMBER_RETAS 10//20
#define NUMBER_CURVAS 10//20
#define CICLOS_FREIO 16 // 60 ciclos equals to 1 sec


//Timers
#define TIME_PARADA 28 //28 equals to 14 secs
#define TIME_IMPULSOINICIAL 2 //2 equals to 1 sec

//Parada
#define RANGEATIVOERRO 6








/*** Nao mudar esse código aqui ***/

//Sistema de Controle
#define REFERENCE CENTCAML
#define MAX_ERRO -MIN_ERRO
#define RANGE_ERRO (MAX_ERRO-MIN_ERRO)

//Boost
#define LIMBOOSTL (CENTCAMR - (WIDTH_BOOST/2))
#define LIMBOOSTR (CENTCAML + (WIDTH_BOOST/2))
