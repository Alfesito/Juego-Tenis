
#include "arkanoPi.h"

volatile int flags = 0;

TipoSistema sistema;

// Declaracion del objeto teclado
TipoTeclado teclado = {
	.columnas = {
		// A completar por el alumno...
		// ...
	},
	.filas = {
		// A completar por el alumno...
		// ...
	},
	.rutinas_ISR = {
		// A completar por el alumno...
		// ...
	},

	// A completar por el alumno...
	// ...
};

// Declaracion del objeto display
TipoLedDisplay led_display = {
	.pines_control_columnas = {
		// A completar por el alumno...
		// ...
	},
	.filas = {
		// A completar por el alumno...
		// ...
	},
	// A completar por el alumno...
	// ...
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
int ConfiguraInicializaSistema (TipoSistema *p_sistema) {
	int result = 0;

	//
	piLock (SYSTEM_FLAGS_KEY);
	flags = 0;
	piUnlock (SYSTEM_FLAGS_KEY);

	InicializaJuego(p_sistema);

	piLock (STD_IO_BUFFER_KEY);
	printf("\nIniciando el juego...\n");
	piUnlock (STD_IO_BUFFER_KEY);


	//
	piLock (STD_IO_BUFFER_KEY);

	// sets up the wiringPi library
	if (wiringPiSetupGpio() < 0) {
		printf ("Unable to setup wiringPi\n");
		piUnlock (STD_IO_BUFFER_KEY);
		return -1;
	}

	// Lanzamos thread para exploracion del teclado convencional del PC
	result = piThreadCreate (thread_explora_teclado_PC);

	if (result != 0) {
		printf ("Thread didn't start!!!\n");
		piUnlock (STD_IO_BUFFER_KEY); //
		return -1;
	}

	piUnlock (STD_IO_BUFFER_KEY);

	return result;
	//return 1;
}

//------------------------------------------------------
// FUNCIONES LIGADAS A THREADS ADICIONALES
//------------------------------------------------------

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

				case 's':
					//Editar por el alumno..

					piLock (SYSTEM_FLAGS_KEY);
					flags |= FLAG_FIN_JUEGO;
					piUnlock (SYSTEM_FLAGS_KEY)
					printf("Tecla S pulsada!\n");
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
}

// wait until next_activation (absolute time)
void delay_until (unsigned int next) {
	unsigned int now = millis();
	if (next > now) {
		delay (next - now);
	}
}

int main () {
	unsigned int next;

	// Maquina de estados: lista de transiciones
	// {EstadoOrigen, CondicionDeDisparo, EstadoFinal, AccionesSiTransicion }
	fsm_trans_t arkanoPi[] = {
		{ WAIT_START, CompruebaBotonPulsado, WAIT_PUSH, InicializaJuego },
		{ WAIT_PUSH, CompruebaTimeoutActualizacionJuego, WAIT_PUSH, ActualizarJuego },
		{ WAIT_PUSH, CompruebaMovimientoIzquierda, WAIT_PUSH, MuevePalaIzquierda },
		{ WAIT_PUSH, CompruebaMovimientoDerecha, WAIT_PUSH, MuevePalaDerecha },
		{ WAIT_PUSH, CompruebaFinalJuego, WAIT_END, FinalJuego },
		{ WAIT_END,  CompruebaBotonPulsado, WAIT_START, ReseteaJuego },
		{-1, NULL, -1, NULL },
	};

	// Configuracion e incializacion del sistema
	ConfiguraInicializaSistema (&sistema);

	fsm_t* arkanoPi_fsm = fsm_new (WAIT_START, arkanoPi, &sistema);

	// ..
	// Configuracion e inicializacion del sistema:
	ConfiguraInicializaSistema(arkanoPi_fsm);

	next = millis();
	while (1) {
		fsm_fire (arkanoPi_fsm);

		// A completar por el alumno...
		// ...

		next += CLK_MS;
		delay_until (next);
	}

	fsm_destroy (arkanoPi_fsm);
}
