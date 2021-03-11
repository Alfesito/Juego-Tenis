#include "teclado_TL04.h"

char tecladoTL04[4][4] = {
	{'1', '2', '3', 'C'},
	{'4', '5', '6', 'D'},
	{'7', '8', '9', 'E'},
	{'A', '0', 'B', 'F'}
};

// Maquina de estados: lista de transiciones
// {EstadoOrigen, CondicionDeDisparo, EstadoFinal, AccionesSiTransicion }
fsm_trans_t fsm_trans_excitacion_columnas[] = {
	{ TECLADO_ESPERA_COLUMNA, CompruebaTimeoutColumna, TECLADO_ESPERA_COLUMNA, TecladoExcitaColumna },
	{-1, NULL, -1, NULL },
};

fsm_trans_t fsm_trans_deteccion_pulsaciones[] = {
	{ TECLADO_ESPERA_TECLA, CompruebaTeclaPulsada, TECLADO_ESPERA_TECLA, ProcesaTeclaPulsada},
	{-1, NULL, -1, NULL },
};

//------------------------------------------------------
// PROCEDIMIENTOS DE INICIALIZACION DE LOS OBJETOS ESPECIFICOS
//------------------------------------------------------

void InicializaTeclado(TipoTeclado *p_teclado) {
	// A completar por el alumno...
	// ...

	teclado.tmr_duracion_columna = tmr_new (timer_duracion_columna_isr);
	tmr_startms((tmr_t*)(teclado.tmr_duracion_columna), TIMEOUT_COLUMNA_TECLADO);
}

//------------------------------------------------------
// OTROS PROCEDIMIENTOS PROPIOS DE LA LIBRERIA
//------------------------------------------------------

void ActualizaExcitacionTecladoGPIO (int columna) {
	// A completar por el alumno
	// ...


	switch(columna){
		case COLUMNA_1:

			break;
		case COLUMNA_2:

			break;
		case COLUMNA_3:

			break;
		case COLUMNA_4:

			break;
		default:

			break;
	}

	tmr_startms((tmr_t*)(teclado.tmr_duracion_columna), TIMEOUT_COLUMNA_TECLADO);
	//Se inicializa al ActualizaExcitacionTecladoGPIO cada vez que se actualiza
}

//------------------------------------------------------
// FUNCIONES DE ENTRADA O DE TRANSICION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

int CompruebaTimeoutColumna (fsm_t* this) {
	int result = 0;
	TipoTeclado *p_teclado;
	p_teclado = (TipoTeclado*)(this->user_data);
	// A completar por el alumno...
	// ...

	piLock(SYSTEM_FLAGS_KEY);
	result = (flags & FLAG_TIMEOUT_COLUMNA_TECLADO);
	piUnlock(SYSTEM_FLAGS_KEY);

	return result;
}

int CompruebaTeclaPulsada (fsm_t* this) {
	int result = 0;
	TipoTeclado *p_teclado;
	p_teclado = (TipoTeclado*)(this->user_data);
	// A completar por el alumno
	// ...

	piLock(SYSTEM_FLAGS_KEY);
	result = (flags & FLAG_TECLA_PULSADA);
	piUnlock(SYSTEM_FLAGS_KEY);

	return result;
}

//------------------------------------------------------
// FUNCIONES DE SALIDA O DE ACCION DE LAS MAQUINAS DE ESTADOS
//------------------------------------------------------

void TecladoExcitaColumna (fsm_t* this) {
	TipoTeclado *p_teclado;
	p_teclado = (TipoTeclado*)(this->user_data);
	// A completar por el alumno
	// ...

	// Llamada a ActualizaExcitacionTecladoGPIO con columna a activar como argumento
	ActualizaExcitacionTecladoGPIO(p_teclado->columna_actual);

	piLock(SYSTEM_FLAGS_KEY);
	flags &= ~FLAG_TIMEOUT_COLUMNA_TECLADO;
	piUnlock(SYSTEM_FLAGS_KEY);
}

void ProcesaTeclaPulsada (fsm_t* this) {
	TipoTeclado *p_teclado;
	p_teclado = (TipoTeclado*)(this->user_data);
	// A completar por el alumno
	// ...
/*
	switch(p_teclado->teclaPulsada->col){
		case COLUMNA_1:
			switch(p_teclado->teclaPulsada->row){
				case FILA_1:
					piLock (STD_IO_BUFFER_KEY);
					printf("Tecla pulsada: '1'\n");
					piUnlock (STD_IO_BUFFER_KEY);
				break;
				case FILA_2:

				break;
				case FILA_3:

				break;
				case FILA_4:

				break;
			}
			break;
		case COLUMNA_2:

			break;
		case COLUMNA_3:

			break;
		case COLUMNA_4:

			break;
	}
*/

	piLock(SYSTEM_FLAGS_KEY);
	flags &= ~FLAG_TECLA_PULSADA;
	piUnlock(SYSTEM_FLAGS_KEY);
}


//------------------------------------------------------
// SUBRUTINAS DE ATENCION A LAS INTERRUPCIONES
//------------------------------------------------------

void teclado_fila_1_isr (void) {
	// A completar por el alumno
	// ...
	piLock(SYSTEM_FLAGS_KEY);
	flags &= ~FLAG_TECLA_PULSADA;
	piUnlock(SYSTEM_FLAGS_KEY);
}

void teclado_fila_2_isr (void) {
	// A completar por el alumno
	// ...
	piLock(SYSTEM_FLAGS_KEY);
	flags &= ~FLAG_TECLA_PULSADA;
	piUnlock(SYSTEM_FLAGS_KEY);
}

void teclado_fila_3_isr (void) {
	// A completar por el alumno
	// ...
	piLock(SYSTEM_FLAGS_KEY);
	flags &= ~FLAG_TECLA_PULSADA;
	piUnlock(SYSTEM_FLAGS_KEY);
}

void teclado_fila_4_isr (void) {
	// A completar por el alumno
	// ...
	piLock(SYSTEM_FLAGS_KEY);
	flags &= ~FLAG_TECLA_PULSADA;
	piUnlock(SYSTEM_FLAGS_KEY);
}

void timer_duracion_columna_isr (union sigval value) {
	// A completar por el alumno
	// ...
	piLock(SYSTEM_FLAGS_KEY);
	flags &= ~FLAG_TECLA_PULSADA;
	piUnlock(SYSTEM_FLAGS_KEY);
}
