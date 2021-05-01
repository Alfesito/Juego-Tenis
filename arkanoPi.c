#include "arkanoPi.h"

int flags = 0;
int pausa = 0;
int scores = 0;
int speed = 0;
int bestscore = 0;
int lifes = 3;//El usuario empieza con tres vidas
int nivel = 1;
char *info="";
int play=1;

TipoSistema sistema;

// Declaracion del objeto teclado
TipoTeclado teclado = { .columnas = {
// A completar por el alumno...
// ...
		GPIO_KEYBOARD_COL_1,
		GPIO_KEYBOARD_COL_2,
		GPIO_KEYBOARD_COL_3,
		GPIO_KEYBOARD_COL_4 },
	.filas = {
// A completar por el alumno...
// ...
		GPIO_KEYBOARD_ROW_1,
		GPIO_KEYBOARD_ROW_2,
		GPIO_KEYBOARD_ROW_3,
		GPIO_KEYBOARD_ROW_4 },
	.rutinas_ISR = {
		// A completar por el alumno...
		// ...
		teclado_fila_1_isr,
		teclado_fila_2_isr,
		teclado_fila_3_isr,
		teclado_fila_4_isr },

// A completar por el alumno...
// ...
	};

// Declaracion del objeto display
TipoLedDisplay led_display = {
	.pines_control_columnas = {
// A completar por el alumno...
// ...
			GPIO_LED_DISPLAY_COL_1,
			GPIO_LED_DISPLAY_COL_2,
			GPIO_LED_DISPLAY_COL_3,
			GPIO_LED_DISPLAY_COL_4
		},
	.filas = {
// A completar por el alumno...
// ...
			GPIO_LED_DISPLAY_ROW_1,
			GPIO_LED_DISPLAY_ROW_2,
			GPIO_LED_DISPLAY_ROW_3,
			GPIO_LED_DISPLAY_ROW_4,
			GPIO_LED_DISPLAY_ROW_5,
			GPIO_LED_DISPLAY_ROW_6,
			GPIO_LED_DISPLAY_ROW_7
		},
// A completar por el alumno...
// ...
	/*	.rutinas_ISR = {

		},*/
	};

//------------------------------------------------------
// FUNCIONES DE CONFIGURACION/INICIALIZACION
//------------------------------------------------------

// int ConfiguracionSistema (TipoSistema *p_sistema): procedimiento de configuracion
// e inicializacion del sistema.
// Realizará, entra otras, todas las operaciones necesarias para:
// configurar el uso de posibles librerías (e.g. Wiring Pi),
// configurar las interrupciones externas asociadas a los pines GPIO,
// configurar las interrupciones periódicas y sus correspondientes temporizadores,
// la inicializacion de los diferentes elementos de los que consta nuestro sistema,
// crear, si fuese necesario, los threads adicionales que pueda requerir el sistema
// como el thread de exploración del teclado del PC
int ConfiguraInicializaSistema(TipoSistema *p_sistema) {
	int result = 0;
	//Faltan cosas
	//p_sistema->arkanoPi.p_pantalla = &(led_display.pantalla);

	piLock(SYSTEM_FLAGS_KEY);
	flags = 0;
	piUnlock(SYSTEM_FLAGS_KEY);

	wiringPiSetupGpio();
	InicializaTeclado(&teclado);
	InicializaLedDisplay(&led_display);
	p_sistema->arkanoPi.p_pantalla = &(led_display.pantalla);
	p_sistema->arkanoPi.tmr_actualizacion_juego = tmr_new(tmr_actualizacion_juego_isr);


	piLock(STD_IO_BUFFER_KEY);
	printf("\nIniciando el juego...\n");
	printf("\nBOTONES DE ARKANOPI"
			"\nBotón para encender y resetear -> 1"
			"\nBotón de movimiento a la izquierda -> 4"
			"\nBotón de movimiento a la derecha -> 6"
			"\nBotón de pausa y jugar después de pausa -> F"
			"\nBotón para apagar el juego -> C\n");
	piUnlock(STD_IO_BUFFER_KEY);

	//
	piLock(STD_IO_BUFFER_KEY);
	// sets up the wiringPi library
	if (wiringPiSetupGpio() < 0) {
		printf("Unable to setup wiringPi\n");
		piUnlock(STD_IO_BUFFER_KEY);
		return -1;
	}

	// Lanzamos thread para exploracion del teclado convencional del PC
	//result = piThreadCreate (thread_explora_teclado_PC);
	/*
	if (result != 0) {
		printf("Thread didn't start!!!\n");
		piUnlock(STD_IO_BUFFER_KEY); //
		return -1;
	}*/

	piUnlock(STD_IO_BUFFER_KEY);

	return result;
	//return 1;
}

//------------------------------------------------------
// FUNCIONES LIGADAS A THREADS ADICIONALES
//------------------------------------------------------
/*
 PI_THREAD (thread_explora_teclado_PC) {
 int teclaPulsada;

 while(1) {
 delay(10); // Wiring Pi function: pauses program execution for at least 10 ms

 piLock (STD_IO_BUFFER_KEY);

 if(kbhit()) {
 teclaPulsada = kbread();

 switch(teclaPulsada) {
 case 'a':
 piLock (SYSTEM_FLAGS_KEY);
 flags |= FLAG_MOV_IZQUIERDA;
 piUnlock (SYSTEM_FLAGS_KEY);
 break;

 case 'c':
 piLock (SYSTEM_FLAGS_KEY);
 flags |= FLAG_TIMER_JUEGO;
 piUnlock (SYSTEM_FLAGS_KEY);
 break;

 case 'd':
 piLock (SYSTEM_FLAGS_KEY);
 flags |= FLAG_MOV_DERECHA;
 piUnlock (SYSTEM_FLAGS_KEY);
 break;

 case 't':
 //Editar por el alumno..

 piLock (SYSTEM_FLAGS_KEY);
 flags |= FLAG_BOTON;
 piUnlock (SYSTEM_FLAGS_KEY);
 printf("Tecla T pulsada!\n");
 fflush(stdout);
 break;

 case 'q':
 exit(0);
 break;

 default:
 printf("INVALID KEY!!!\n");
 break;
 }
 }

 piUnlock (STD_IO_BUFFER_KEY);
 }
 }*/

// wait until next_activation (absolute time)
void delay_until(unsigned int next) {
	unsigned int now = millis();
	if (next > now) {
		delay(next - now);
	}
}

int main() {

	unsigned int next;

	// Maquina de estados: lista de transiciones
	// {EstadoOrigen, CondicionDeDisparo, EstadoFinal, AccionesSiTransicion }
	fsm_trans_t arkanoPi[] =
			{ 		{ WAIT_START, CompruebaBotonPulsado, WAIT_PUSH, InicializaJuego },
					{ WAIT_PUSH, CompruebaTimeoutActualizacionJuego, WAIT_PUSH,ActualizarJuego },
					{ WAIT_PUSH,CompruebaMovimientoIzquierda, WAIT_PUSH,MuevePalaIzquierda },
					{ WAIT_PUSH,CompruebaMovimientoDerecha, WAIT_PUSH,MuevePalaDerecha },
					{ WAIT_PUSH,CompruebaPausa, WAIT_PUSH, PausaJuego },
					{ WAIT_PUSH,CompruebaFinalPausa, WAIT_PUSH, FinalPausaJuego },
					{ WAIT_PUSH, CompruebaFinalJuego, WAIT_END, FinalJuego },
					{ WAIT_END, CompruebaBotonPulsado, WAIT_START,ReseteaJuego },
					{ -1, NULL, -1, NULL }, };

	// Configuracion e incializacion del sistema
	ConfiguraInicializaSistema(&sistema);
	// ..

	fsm_t *arkanoPi_fsm = fsm_new(WAIT_START, arkanoPi, &sistema.arkanoPi);

	fsm_t *teclado_fsm = fsm_new(TECLADO_ESPERA_COLUMNA,
			fsm_trans_excitacion_columnas, &(teclado));
	fsm_t *tecla_fsm = fsm_new(TECLADO_ESPERA_TECLA,
			fsm_trans_deteccion_pulsaciones, &(teclado));
	fsm_t *display_fsm = fsm_new(DISPLAY_ESPERA_COLUMNA,
			fsm_trans_excitacion_display, &(led_display));

	next = millis();
	while (1) {
		fsm_fire(arkanoPi_fsm);
		fsm_fire(teclado_fsm);
		fsm_fire(tecla_fsm);
		fsm_fire(display_fsm);

		next += CLK_MS;
		delay_until(next);
	}
	tmr_destroy((tmr_t*) (sistema.arkanoPi.tmr_actualizacion_juego));
	//fsm_destroy(arkanoPi_fsm);
	//fsm_destroy(teclado_fsm);
	//fsm_destroy(tecla_fsm);
	//fsm_destroy((tmr_t*) led_display.tmr_refresco_display);
	//fsm_destroy((tmr_t*) teclado.tmr_duracion_columna);
	//fsm_destroy(display_fsm);

	return 0;
}
