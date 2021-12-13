
//Camera RCA
#define WIDTH 85
#define HEIGHT 60
#define MINCAM 11
#define MAXCAM 83
#define CENTCAML 35
#define CENTCAMR 36
#define WIDTH_REAL (MAXCAM-MINCAM)

//Servo
#define CENTRO_SERVO 18400 //18518
#define LIBERDADE_SERVO 220
#define ESQUERDA_SERVO (CENTRO_SERVO-LIBERDADE_SERVO)
#define DIREITO_SERVO (CENTRO_SERVO+LIBERDADE_SERVO)

//Processing
#define LINENOW 0
#define WIDTH_TRACK 56
#define DELTA_AMOSTRA_MIN 47
#define MIN_ERRO 62
#define MAX_ERRO -MIN_ERRO
#define RANGE_ERRO (MAX_ERRO-MIN_ERRO)
#define TRAVA_ATIVO 22
#define MIN_DESTRAVA (WIDTH_TRACK-5)
#define MAX_DESTRAVA (WIDTH_TRACK+5)

//Tracao
#define MAX_PWM_MOTOR 1 //1  Nivel Baixo
#define MIN_PWM_MOTOR 999
#define DIFERENCIAL_ATIVO TRAVA_ATIVO

#define REG_TRACAO 500 // 700
//#define REG_TRACAO 999 // 700
#define MIN_TRACAO 900
#define MAX_TRACAO 700

//#define REG_TRACAO 999//800
//#define MIN_TRACAO 999//900
//#define MAX_TRACAO 999//500

//PID
#define KP 1.5

//Proporcional Servo

#define RANGE_SERVO (DIREITO_SERVO-ESQUERDA_SERVO)

