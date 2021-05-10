#include "teclado_TL04.h"

char tecladoTL04[4][4] = { { '1', '2', '3', 'C' }, { '4', '5', '6', 'D' }, {
		'7', '8', '9', 'E' }, { 'A', '0', 'B', 'F' } };

// Maquina de estados: lista de transiciones
// {EstadoOrigen, CondicionDeDisparo, EstadoFinal, AccionesSiTransicion }
fsm_trans_t fsm_trans_excitacion_columnas[] = { { TECLADO_ESPERA_COLUMNA,
		CompruebaTimeoutColumna, TECLADO_ESPERA_COLUMNA, TecladoExcitaColumna },
		{ -1, NULL, -1, NULL }, };

fsm_trans_t fsm_trans_deteccion_pulsaciones[] = { { TECLADO_ESPERA_TECLA,
		CompruebaTeclaPulsada, TECLADO_ESPERA_TECLA, ProcesaTeclaPulsada }, {
		-1, NULL, -1, NULL }, };

//------------------------------------------------------
// PROCEDIMIENTOS DE INICIALIZACION DE LOS OBJETOS ESPECIFICOS
//------------------------------------------------------

void InicializaTeclado(TipoTeclado *p_teclado) {
	// A completar por el alumno...
	// ...
	p_teclado->columna_actual = COLUMNA_1;
	p_teclado->teclaPulsada.col = -1;
	p_teclado->teclaPulsada.row = -1;

	for (int i = 0; i < NUM_COLUMNAS_TECLADO; i++) {
		pinMode(teclado.columnas[i], OUTPUT);
		digitalWrite(teclado.columnas[i], LOW);
	}

	for (int i = 0; i < NUM_FILAS_TECLADO; i++) {
		pinMode(teclado.filas[i], INPUT);
		pullUpDnControl(teclado.filas[i], PUD_DOWN);
		wiringPiISR(teclado.filas[i], INT_EDGE_RISING, teclado.rutinas_ISR[i]);
	}

	teclado.tmr_duracion_columna = tmr_new(timer_duracion_columna_isr);
	tmr_startms((tmr_t*) (teclado.tmr_duracion_columna),
			TIMEOUT_COLUMNA_TECLADO);
}

//------------------------------------------------------
// OTROS PROCEDIMIENTOS PROPIOS DE LA LIBRERIA
//------------------------------------------------------

void ActualizaExcitacionTecladoGPIO(int columna) {
	// A completar por el alumno
	// ...
	switch (columna) {
	case COLUMNA_1:
		digitalWrite(GPIO_KEYBOARD_COL_1, HIGH);
		digitalWrite(GPIO_KEYBOARD_COL_2, LOW);
		digitalWrite(GPIO_KEYBOARD_COL_3, LOW);
		digitalWrite(GPIO_KEYBOARD_COL_4, LOW);
		break;
	case COLUMNA_2:
		digitalWrite(GPIO_KEYBOARD_COL_1, LOW);
		digitalWrite(GPIO_KEYBOARD_COL_2, HIGH);
		digitalWrite(GPIO_KEYBOARD_COL_3, LOW);
		digitalWrite(GPIO_KEYBOARD_COL_4, LOW);
		break;
	case COLUMNA_3:
		digitalWrite(GPIO_KEYBOARD_COL_1, LOW);
		digitalWrite(GPIO_KEYBOARD_COL_2, LOW);
		digitalWrite(GPIO_KEYBOARD_COL_3, HIGH);
		digitalWrite(GPIO_KEYBOARD_COL_4, LOW);
		break;
	case COLUMNA_4:
		digitalWrite(GPIO_KEYBOARD_COL_1, LOW);
		digitalWrite(GPIO_KEYBOARD_COL_2, LOW);
		digitalWrite(GPIO_KEYBOARD_COL_3, LOW);
		digitalWrite(GPIO_KEYBOARD_COL_4, HIGH);
		break;
	}

	tmr_startms((tmr_t*) (teclado.tmr_duracion_columna),
			TIMEOUT_COLUMNA_TECLADO);
	//Se inicializa al ActualizaExcitacionTecladoGPIO cada vez que se actualiza
}

//------------------------------------------------------
// FUNCIONES DE ENTRADA O DE TRANSICION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

int CompruebaTimeoutColumna(fsm_t *this) {
	int result = 0;
	TipoTeclado *p_teclado;
	p_teclado = (TipoTeclado*) (this->user_data);
	// A completar por el alumno...
	// ...

	piLock(KEYBOARD_KEY);
	result = (p_teclado->flags & FLAG_TIMEOUT_COLUMNA_TECLADO);
	piUnlock(KEYBOARD_KEY);

	return result;
}

int CompruebaTeclaPulsada(fsm_t *this) {
	int result = 0;
	TipoTeclado *p_teclado;
	p_teclado = (TipoTeclado*) (this->user_data);
	// A completar por el alumno
	// ...

	piLock(KEYBOARD_KEY);
	result = (p_teclado->flags & FLAG_TECLA_PULSADA);
	piUnlock(KEYBOARD_KEY);

	return result;
}

//------------------------------------------------------
// FUNCIONES DE SALIDA O DE ACCION DE LAS MAQUINAS DE ESTADOS
//------------------------------------------------------

void TecladoExcitaColumna(fsm_t *this) {
	TipoTeclado *p_teclado;
	p_teclado = (TipoTeclado*) (this->user_data);
	// A completar por el alumno
	// ...
	piLock(KEYBOARD_KEY);
	teclado.flags &= (~FLAG_TIMEOUT_COLUMNA_TECLADO);
	piUnlock(KEYBOARD_KEY);

	p_teclado->columna_actual++;
	int col_act = p_teclado->columna_actual;

	if (p_teclado->columna_actual < 4) {
		p_teclado->columna_actual = col_act;
	} else {
		p_teclado->columna_actual = 0;
	}

	// Llamada a ActualizaExcitacionTecladoGPIO con columna a activar como argumento
	ActualizaExcitacionTecladoGPIO(p_teclado->columna_actual);
	tmr_startms((tmr_t*) (teclado.tmr_duracion_columna),
				TIMEOUT_COLUMNA_TECLADO);
}

void ProcesaTeclaPulsada(fsm_t *this) {
	TipoTeclado *p_teclado;
	p_teclado = (TipoTeclado*) (this->user_data);
	// A completar por el alumno
	// ...

	piLock(KEYBOARD_KEY);
	teclado.flags &= (~FLAG_TECLA_PULSADA);
	piUnlock(KEYBOARD_KEY);

	switch (p_teclado->teclaPulsada.col) {
	case COLUMNA_1:
		//IZQUIERDA
		if (p_teclado->teclaPulsada.row == FILA_2) {
			piLock(SYSTEM_FLAGS_KEY);
			flags |= FLAG_MOV_IZQUIERDA;
			piUnlock(SYSTEM_FLAGS_KEY);
			p_teclado->teclaPulsada.row = -1;
			p_teclado->teclaPulsada.col = -1;
		//ENCENDIO O RESETEO
		} else if (p_teclado->teclaPulsada.row == FILA_1) {
			piLock(SYSTEM_FLAGS_KEY);
			flags |= FLAG_BOTON;
			piUnlock(SYSTEM_FLAGS_KEY);

			p_teclado->teclaPulsada.row = -1;
			p_teclado->teclaPulsada.col = -1;
		}
		break;

	case COLUMNA_2:

		break;

	case COLUMNA_3:
		//DERECHA
		if (p_teclado->teclaPulsada.row == FILA_2) {

			piLock(SYSTEM_FLAGS_KEY);
			flags |= FLAG_MOV_DERECHA;
			piUnlock(SYSTEM_FLAGS_KEY);

			p_teclado->teclaPulsada.row = -1;
			p_teclado->teclaPulsada.col = -1;
		}
		break;
		
	case COLUMNA_4:
		//FIN DE JUEGO
		if (p_teclado->teclaPulsada.row == FILA_1) {
			piLock (SYSTEM_FLAGS_KEY);
			flags |=FLAG_FIN_JUEGO;
			piUnlock (SYSTEM_FLAGS_KEY);
			p_teclado->teclaPulsada.row = -1;
			p_teclado->teclaPulsada.col = -1;
		}
		//PAUSA
		if (p_teclado->teclaPulsada.row == FILA_4) {
			//Si el timeout no es cero, el sistema no esta en pausa,
			//por lo tanto se puede pausar
			if(speed!=0){
				piLock (SYSTEM_FLAGS_KEY);
				flags |=FLAG_PAUSA;
				piUnlock (SYSTEM_FLAGS_KEY);
			}
			//Si el timeout del sistema está en cero, es que está pausado,
			//por lo que se pondrá a jugar de nuevo
			if(speed==0){
				piLock (SYSTEM_FLAGS_KEY);
				flags |=FLAG_FINAL_PAUSA;
				piUnlock (SYSTEM_FLAGS_KEY);
			}


			p_teclado->teclaPulsada.row = -1;
			p_teclado->teclaPulsada.col = -1;
		}
		break;

	default:
		break;
	}
}

//------------------------------------------------------
// SUBRUTINAS DE ATENCION A LAS INTERRUPCIONES
//------------------------------------------------------

void teclado_fila_1_isr(void) {
	// A completar por el alumno
	// ...
	if (millis() < teclado.debounceTime[FILA_1]) {
		teclado.debounceTime[FILA_1] = millis() + DEBOUNCE_TIME;
		return;
	}

	piLock(KEYBOARD_KEY);
	teclado.flags |= FLAG_TECLA_PULSADA;
	teclado.teclaPulsada.row = FILA_1;
	teclado.teclaPulsada.col = teclado.columna_actual;
	piUnlock(KEYBOARD_KEY);

	teclado.debounceTime[FILA_1] = millis() + DEBOUNCE_TIME;
}

void teclado_fila_2_isr(void) {
	// A completar por el alumno
	// ...
	if (millis() < teclado.debounceTime[FILA_2]) {
		teclado.debounceTime[FILA_2] = millis() + DEBOUNCE_TIME;
		return;
	}

	piLock(KEYBOARD_KEY);
	teclado.flags |= FLAG_TECLA_PULSADA;
	teclado.teclaPulsada.row = FILA_2;
	teclado.teclaPulsada.col = teclado.columna_actual;
	piUnlock(KEYBOARD_KEY);

	teclado.debounceTime[FILA_2] = millis() + DEBOUNCE_TIME;
}

void teclado_fila_3_isr(void) {
	// A completar por el alumno
	// ...
	if (millis() < teclado.debounceTime[FILA_3]) {
		teclado.debounceTime[FILA_3] = millis() + DEBOUNCE_TIME;
		return;
	}

	piLock(KEYBOARD_KEY);
	teclado.flags |= FLAG_TECLA_PULSADA;
	teclado.teclaPulsada.row = FILA_3;
	teclado.teclaPulsada.col = teclado.columna_actual;
	piUnlock(KEYBOARD_KEY);

	teclado.debounceTime[FILA_3] = millis() + DEBOUNCE_TIME;
}

void teclado_fila_4_isr(void) {
	// A completar por el alumno
	// ...
	if (millis() < teclado.debounceTime[FILA_4]) {
		teclado.debounceTime[FILA_4] = millis() + DEBOUNCE_TIME;
		return;
	}

	piLock(KEYBOARD_KEY);
	teclado.flags |= FLAG_TECLA_PULSADA;
	teclado.teclaPulsada.row = FILA_4;
	teclado.teclaPulsada.col = teclado.columna_actual;
	piUnlock(KEYBOARD_KEY);

	teclado.debounceTime[FILA_4] = millis() + DEBOUNCE_TIME;
}

void timer_duracion_columna_isr(union sigval value) {
	// A completar por el alumno
	// ...
	piLock(KEYBOARD_KEY);
	teclado.flags |= FLAG_TIMEOUT_COLUMNA_TECLADO;
	piUnlock(KEYBOARD_KEY);
}
