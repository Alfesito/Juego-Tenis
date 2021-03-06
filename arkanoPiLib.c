#include "arkanoPiLib.h"

int ladrillos_basico[NUM_FILAS_DISPLAY][NUM_COLUMNAS_DISPLAY] = {
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
};

//------------------------------------------------------
// FUNCIONES DE VISUALIZACION (ACTUALIZACION DEL OBJETO PANTALLA QUE LUEGO USARA EL DISPLAY)
//------------------------------------------------------

void PintaMensajeInicialPantalla (tipo_pantalla *p_pantalla, tipo_pantalla *p_pantalla_inicial) {
	int i, j = 0;

	for(i=0;i<NUM_FILAS_DISPLAY;i++) {
		for(j=0;j<NUM_COLUMNAS_DISPLAY;j++) {
			p_pantalla->matriz[i][j] = p_pantalla_inicial->matriz[i][j];
		}
	}

	return;
}

void ReseteaPantalla (tipo_pantalla *p_pantalla) {
	int i=0, j=0;

	for(i=0;i<NUM_FILAS_DISPLAY;i++) {
		for(j=0;j<NUM_COLUMNAS_DISPLAY;j++) {
			p_pantalla->matriz[i][j] = 0;
		}
	}
}

void PausaPantalla (tipo_pantalla *p_pantalla) {
	int i=0, j=0;

	for(i=0;i<NUM_FILAS_DISPLAY;i++) {
		for(j=0;j<NUM_COLUMNAS_DISPLAY;j++) {
			p_pantalla->matriz[i][j];
		}
	}
}


//------------------------------------------------------
// FUNCIONES DE INICIALIZACION / RESET
//------------------------------------------------------

void InicializaLadrillos(tipo_pantalla *p_ladrillos) {
	int i=0, j=0;

	for(i=0;i<NUM_FILAS_DISPLAY;i++) {
		for(j=0;j<NUM_COLUMNAS_DISPLAY;j++) {
			p_ladrillos->matriz[i][j] = ladrillos_basico[i][j];
		}
	}
}

void PausaLadrillos(tipo_pantalla *p_ladrillos) {
	int i=0, j=0;

	for(i=0;i<NUM_FILAS_DISPLAY;i++) {
		for(j=0;j<NUM_COLUMNAS_DISPLAY;j++) {
			p_ladrillos->matriz[i][j];
		}
	}
}

void InicializaPelota(tipo_pelota *p_pelota) {
	// Aleatorizamos la posicion inicial de la pelota
	p_pelota->x = rand() % NUM_COLUMNAS_DISPLAY;
	p_pelota->y = 2 + rand() % (NUM_FILAS_DISPLAY-2); // 2 evita que aparezca encima de ladrillos y para que no empiece demasiado pegada al suelo de la pantalla

	// Pelota inicialmente en el centro de la pantalla
	//p_pelota->x = NUM_COLUMNAS_DISPLAY/2 - 1;
	//p_pelota->y = NUM_FILAS_DISPLAY/2 -1 ;

	InicializaPosiblesTrayectorias(p_pelota);

	// Trayectoria inicial
	//p_pelota->trayectoria.xv = 0;
	//p_pelota->trayectoria.yv = 1;
	CambiarDireccionPelota(p_pelota, rand() % p_pelota->num_posibles_trayectorias);
}

void PausaPelota(tipo_pelota *p_pelota) {
	p_pelota->x;
	p_pelota->y;
}

void InicializaPala(tipo_pala *p_pala) {
	// Pala inicialmente en el centro de la pantalla
	p_pala->x = NUM_COLUMNAS_DISPLAY/2 - p_pala->ancho/2;
	p_pala->y = NUM_FILAS_DISPLAY - 1;
	p_pala->ancho = NUM_COLUMNAS_PALA;
	p_pala->alto = NUM_FILAS_PALA;
}

void PausaPala(tipo_pala *p_pala) {
	// Pala inicialmente en el centro de la pantalla
	p_pala->x;
	p_pala->y;
	p_pala->ancho = NUM_COLUMNAS_PALA;
	p_pala->alto = NUM_FILAS_PALA;
}

void InicializaPosiblesTrayectorias(tipo_pelota *p_pelota) {
	p_pelota->num_posibles_trayectorias = 0;
	p_pelota->posibles_trayectorias[ARRIBA_IZQUIERDA].xv = -1;
	p_pelota->posibles_trayectorias[ARRIBA_IZQUIERDA].yv = -1;
	p_pelota->num_posibles_trayectorias++;
	p_pelota->posibles_trayectorias[ARRIBA].xv = 0;
	p_pelota->posibles_trayectorias[ARRIBA].yv = -1;
	p_pelota->num_posibles_trayectorias++;
	p_pelota->posibles_trayectorias[ARRIBA_DERECHA].xv = 1;
	p_pelota->posibles_trayectorias[ARRIBA_DERECHA].yv = -1;
	p_pelota->num_posibles_trayectorias++;
	p_pelota->posibles_trayectorias[ABAJO_DERECHA].xv = 1;
	p_pelota->posibles_trayectorias[ABAJO_DERECHA].yv = 1;
	p_pelota->num_posibles_trayectorias++;
	p_pelota->posibles_trayectorias[ABAJO].xv = 0;
	p_pelota->posibles_trayectorias[ABAJO].yv = 1;
	p_pelota->num_posibles_trayectorias++;
	p_pelota->posibles_trayectorias[ABAJO_IZQUIERDA].xv = -1;
	p_pelota->posibles_trayectorias[ABAJO_IZQUIERDA].yv = 1;
	p_pelota->num_posibles_trayectorias++;

	//p_pelota->posibles_trayectorias[IZQUIERDA].xv = -1;
	//p_pelota->posibles_trayectorias[IZQUIERDA].yv = 0;
	//p_pelota->num_posibles_trayectorias++;
	//p_pelota->posibles_trayectorias[DERECHA].xv = 1;
	//p_pelota->posibles_trayectorias[DERECHA].yv = 0;
	//p_pelota->num_posibles_trayectorias++;
}

void PintaLadrillos(tipo_pantalla *p_ladrillos, tipo_pantalla *p_pantalla) {
	int i=0, j=0;

	for(i=0;i<NUM_FILAS_DISPLAY;i++) {
		for(j=0;j<NUM_COLUMNAS_DISPLAY;j++) {
			p_pantalla->matriz[i][j] = p_ladrillos->matriz[i][j];
		}
    }
}

void PintaPala(tipo_pala *p_pala, tipo_pantalla *p_pantalla) {
	int i=0, j=0;

	for(i=0;i<NUM_FILAS_PALA;i++) {
		for(j=0;j<NUM_COLUMNAS_PALA;j++) {
			if (( (p_pala->y+i >= 0) && (p_pala->y+i < NUM_FILAS_DISPLAY) ) &&
				( (p_pala->x+j >= 0) && (p_pala->x+j < NUM_COLUMNAS_DISPLAY) ))
				p_pantalla->matriz[p_pala->y+i][p_pala->x+j] = 1;
		}
	}
}

void PintaPelota(tipo_pelota *p_pelota, tipo_pantalla *p_pantalla) {
	if( (p_pelota->x >= 0) && (p_pelota->x <= NUM_COLUMNAS_DISPLAY) ) {
		if( (p_pelota->y >= 0) && (p_pelota->y < NUM_FILAS_DISPLAY) ) {
			p_pantalla->matriz[p_pelota->y][p_pelota->x] = 8;
		}
		else {
			printf("\n\nPROBLEMAS!!!! posicion y=%d de la pelota INVALIDA!!!\n\n", p_pelota->y);
			fflush(stdout);
		}
	}
	else {
		printf("\n\nPROBLEMAS!!!! posicion x=%d de la pelota INVALIDA!!!\n\n", p_pelota->x);
		fflush(stdout);
	}
}

void ActualizaPantalla(tipo_arkanoPi* p_arkanoPi, int debug) {

    // Borro toda la pantalla
	ReseteaPantalla((tipo_pantalla*)(p_arkanoPi->p_pantalla));

    // Pinta los ladrillos
	PintaLadrillos(
		(tipo_pantalla*)(&(p_arkanoPi->ladrillos)),
		(tipo_pantalla*)(p_arkanoPi->p_pantalla));

    // Pinta la pala
	PintaPala(
		(tipo_pala*)(&(p_arkanoPi->pala)),
		(tipo_pantalla*)(p_arkanoPi->p_pantalla));

	// Pinta la pelota
	PintaPelota(
		(tipo_pelota*)(&(p_arkanoPi->pelota)),
		(tipo_pantalla*)(p_arkanoPi->p_pantalla));

	if (debug) {
		printf("\nDESPUES DE PintaPelota\n");
		fflush(stdout);
		PintaPantallaPorTerminal((tipo_pantalla*)(p_arkanoPi->p_pantalla));
	}
}

void InicializaArkanoPi(tipo_arkanoPi *p_arkanoPi, int debug) {
	ResetArkanoPi(p_arkanoPi);
	ActualizaPantalla(p_arkanoPi, debug);
}

void ResetArkanoPi(tipo_arkanoPi *p_arkanoPi) {
	ReseteaPantalla((tipo_pantalla*)(p_arkanoPi->p_pantalla));
	InicializaLadrillos((tipo_pantalla*)(&(p_arkanoPi->ladrillos)));
	InicializaPelota((tipo_pelota*)(&(p_arkanoPi->pelota)));
	InicializaPala((tipo_pala*)(&(p_arkanoPi->pala)));
}

void PausaArkanoPi(tipo_arkanoPi *p_arkanoPi){
	PausaPantalla((tipo_pantalla*)(p_arkanoPi->p_pantalla));
	PausaLadrillos((tipo_pantalla*)(&(p_arkanoPi->ladrillos)));
	PausaPelota((tipo_pelota*)(&(p_arkanoPi->pelota)));
	PausaPala((tipo_pala*)(&(p_arkanoPi->pala)));
}

void CambiarDireccionPelota(tipo_pelota *p_pelota, enum t_direccion direccion) {
	if((direccion < 0)||(direccion > p_pelota->num_posibles_trayectorias)) {
		printf("[ERROR!!!!][direccion NO VALIDA!!!!][%d]", direccion);
		return;
	}
	else {
		p_pelota->trayectoria.xv = p_pelota->posibles_trayectorias[direccion].xv;
		p_pelota->trayectoria.yv = p_pelota->posibles_trayectorias[direccion].yv;
	}
}

void ActualizaPosicionPala(tipo_pala *p_pala, enum t_direccion direccion) {
	switch (direccion) {
		case DERECHA:
			// Dejamos que la pala rebase parcialmente el límite del area de juego
			if( p_pala->x + 1 + p_pala->ancho <= NUM_COLUMNAS_DISPLAY + 2 )
				p_pala->x = p_pala->x + 1;
			break;
		case IZQUIERDA:
			// Dejamos que la pala rebase parcialmente el límite del area de juego
			if( p_pala->x - 1 >= -2)
					p_pala->x = p_pala->x - 1;
			break;
		default:
			printf("[ERROR!!!!][direccion NO VALIDA!!!!][%d]", direccion);
			break;
	}
}

void ActualizaPosicionPelota (tipo_pelota *p_pelota) {
	p_pelota->x += p_pelota->trayectoria.xv;
	p_pelota->y += p_pelota->trayectoria.yv;
}

int CompruebaReboteLadrillo (tipo_arkanoPi *p_arkanoPi) {
	int p_posible_ladrillo_x = 0;
	int p_posible_ladrillo_y = 0;

	p_posible_ladrillo_x = p_arkanoPi->pelota.x + p_arkanoPi->pelota.trayectoria.xv;

	if ( ( p_posible_ladrillo_x < 0) || ( p_posible_ladrillo_x > NUM_COLUMNAS_DISPLAY ) ) {
		printf("\n\nERROR GRAVE!!! p_posible_ladrillo_x = %d!!!\n\n", p_posible_ladrillo_x);
		fflush(stdout);
		exit(-1);
	}

	p_posible_ladrillo_y = p_arkanoPi->pelota.y + p_arkanoPi->pelota.trayectoria.yv;

	if ( ( p_posible_ladrillo_y < 0) || ( p_posible_ladrillo_y >= NUM_FILAS_DISPLAY ) ) {
		printf("\n\nERROR GRAVE!!! p_posible_ladrillo_y = %d!!!\n\n", p_posible_ladrillo_y);
		fflush(stdout);
	}

	if(p_arkanoPi->ladrillos.matriz[p_posible_ladrillo_y][p_posible_ladrillo_x] > 0 ) {
		// La pelota ha entrado en el area de ladrillos
		// y descontamos el numero de golpes que resta para destruir el ladrillo
		p_arkanoPi->ladrillos.matriz[p_posible_ladrillo_y][p_posible_ladrillo_x] = p_arkanoPi->ladrillos.matriz[p_posible_ladrillo_y][p_posible_ladrillo_x] - 1;
		//scores++;
		return 1;
	}
	return 0;
}

int CompruebaReboteParedesVerticales (tipo_arkanoPi arkanoPi) {
	// Comprobamos si la nueva posicion de la pelota excede los limites de la pantalla
	if((arkanoPi.pelota.x + arkanoPi.pelota.trayectoria.xv >= NUM_COLUMNAS_DISPLAY) ||
		(arkanoPi.pelota.x + arkanoPi.pelota.trayectoria.xv < 0)) {
		// La pelota rebota contra la pared derecha o izquierda
		return 1;
	}
	return 0;
}

int CompruebaReboteTecho (tipo_arkanoPi arkanoPi) {
	// Comprobamos si la nueva posicion de la pelota excede los limites de la pantalla
	if(arkanoPi.pelota.y + arkanoPi.pelota.trayectoria.yv < 0) {
		// La pelota rebota contra la pared derecha o izquierda
		return 1;
	}
	return 0;
}

int CompruebaRebotePala (tipo_arkanoPi arkanoPi) {
	if(arkanoPi.pelota.trayectoria.yv > 0) { // Esta condicion solo tiene sentido si la pelota va hacia abajo en la pantalla
		if ((arkanoPi.pelota.x + arkanoPi.pelota.trayectoria.xv >= arkanoPi.pala.x ) &&
			(arkanoPi.pelota.x + arkanoPi.pelota.trayectoria.xv < arkanoPi.pala.x + NUM_COLUMNAS_PALA)) {
				if ((arkanoPi.pelota.y + arkanoPi.pelota.trayectoria.yv >= arkanoPi.pala.y) &&
					(arkanoPi.pelota.y + arkanoPi.pelota.trayectoria.yv < arkanoPi.pala.y + NUM_FILAS_PALA)) {
					return 1;
				}
		}
	}
	return 0;
}

int CompruebaFallo (tipo_arkanoPi arkanoPi) {
	// Comprobamos si no hemos conseguido devolver la pelota
	if(arkanoPi.pelota.y + arkanoPi.pelota.trayectoria.yv >= NUM_FILAS_DISPLAY) {
		// Hemos fallado
		return 1;
	}
	return 0;
}

int CalculaLadrillosRestantes(tipo_pantalla *p_ladrillos) {
	int i=0, j=0;
	int numLadrillosRestantes;

	numLadrillosRestantes = 0;

	for(i=0;i<NUM_FILAS_DISPLAY;i++) {
		for(j=0;j<NUM_COLUMNAS_DISPLAY;j++) {
			if(p_ladrillos->matriz[i][j] != 0) {
				numLadrillosRestantes++;
			}
		}
	}

	return numLadrillosRestantes;
}

//------------------------------------------------------
// FUNCIONES DE TRANSICION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

int CompruebaBotonPulsado (fsm_t* this) {
	int result = 0;

	piLock (SYSTEM_FLAGS_KEY);
	result = (flags & FLAG_BOTON);
	piUnlock (SYSTEM_FLAGS_KEY);

	return result;
}

int CompruebaMovimientoIzquierda(fsm_t* this) {
	int result = 0;

	piLock (SYSTEM_FLAGS_KEY);
	result = (flags & FLAG_MOV_IZQUIERDA);
	piUnlock (SYSTEM_FLAGS_KEY);

	return result;
}

int CompruebaMovimientoDerecha(fsm_t* this) {
	int result = 0;

	piLock (SYSTEM_FLAGS_KEY);
	result = (flags & FLAG_MOV_DERECHA);
	piUnlock (SYSTEM_FLAGS_KEY);

	return result;
}

int CompruebaTimeoutActualizacionJuego (fsm_t* this) {
	int result = 0;

	piLock (SYSTEM_FLAGS_KEY);
	result = (flags & FLAG_TIMER_JUEGO);
	piUnlock (SYSTEM_FLAGS_KEY);

	return result;
}

int CompruebaFinalJuego(fsm_t* this) {
	int result = 0;

	piLock (SYSTEM_FLAGS_KEY);
	result = (flags & FLAG_FIN_JUEGO);
	piUnlock (SYSTEM_FLAGS_KEY);

	return result;
}


int CompruebaPausa(fsm_t* this) {
	int result = 0;

	piLock (SYSTEM_FLAGS_KEY);
	result = (flags & FLAG_PAUSA);
	piUnlock (SYSTEM_FLAGS_KEY);

	return result;
}

int CompruebaFinalPausa(fsm_t* this) {
	int result = 0;

	piLock (SYSTEM_FLAGS_KEY);
	result = (flags & FLAG_FINAL_PAUSA);
	piUnlock (SYSTEM_FLAGS_KEY);

	return result;
}


//------------------------------------------------------
// FUNCIONES DE ACCION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

// void InicializaJuego (void): funcion encargada de llevar a cabo
// la oportuna inicialización de toda variable o estructura de datos

void InicializaJuego(fsm_t* this) {
	tipo_arkanoPi *p_arkanoPi;
	p_arkanoPi = (tipo_arkanoPi*)(this->user_data);

	p_arkanoPi->score=0;
	info="";
	info="Iniciando juego";

	piLock(SYSTEM_FLAGS_KEY);
	flags &= ~FLAG_BOTON;
	piUnlock(SYSTEM_FLAGS_KEY);

	InicializaArkanoPi(p_arkanoPi, 0);	//valor del parametro debug?? 1?

	tmr_startms((tmr_t*)(p_arkanoPi->tmr_actualizacion_juego), TIMEOUT_ACTUALIZA_JUEGO);
	pseudoWiringPiEnableDisplay(1);
}

// void MuevePalaIzquierda (void): funcion encargada de ejecutar
// el movimiento hacia la izquierda contemplado para la pala.
// Debe garantizar la viabilidad del mismo mediante la comprobación
// de que la nueva posición correspondiente a la pala no suponga
// que ésta rebase o exceda los límites definidos para el área de juego
// (i.e. al menos uno de los leds que componen la raqueta debe permanecer
// visible durante todo el transcurso de la partida).

void MuevePalaIzquierda (fsm_t* this) {
	tipo_arkanoPi* p_arkanoPi;
	p_arkanoPi = (tipo_arkanoPi*)(this->user_data);

	piLock (SYSTEM_FLAGS_KEY);
	flags &= ~FLAG_MOV_IZQUIERDA;
	piUnlock (SYSTEM_FLAGS_KEY);

	ActualizaPosicionPala(&(p_arkanoPi->pala), IZQUIERDA);		//para pasar la direcciopn y que me diga el puntero

	piLock(MATRIX_KEY);
	ActualizaPantalla(p_arkanoPi,0);
	piUnlock(MATRIX_KEY);
}

// void MuevePalaDerecha (void): función similar a la anterior
// encargada del movimiento hacia la derecha.
void MuevePalaDerecha (fsm_t* this) {
	tipo_arkanoPi* p_arkanoPi;
	p_arkanoPi = (tipo_arkanoPi*)(this->user_data);

	//
	piLock (SYSTEM_FLAGS_KEY);
	flags &= ~FLAG_MOV_DERECHA;
	piUnlock (SYSTEM_FLAGS_KEY);

	ActualizaPosicionPala(&(p_arkanoPi->pala), DERECHA);

	piLock(MATRIX_KEY);
	ActualizaPantalla(p_arkanoPi,0);
	piUnlock(MATRIX_KEY);

}

// void ActualizarJuego (void): función encargada de actualizar la
// posición de la pelota conforme a la trayectoria definida para ésta.
// Para ello deberá identificar los posibles rebotes de la pelota para,
// en ese caso, modificar su correspondiente trayectoria (los rebotes
// detectados contra alguno de los ladrillos implicarán adicionalmente
// la eliminación del ladrillo). Del mismo modo, deberá también
// identificar las situaciones en las que se dé por finalizada la partida:
// bien porque el jugador no consiga devolver la pelota, y por tanto ésta
// rebase el límite inferior del área de juego, bien porque se agoten
// los ladrillos visibles en el área de juego.

void ActualizarJuego (fsm_t* this) {
	tipo_arkanoPi* p_arkanoPi;
	p_arkanoPi = (tipo_arkanoPi*)(this->user_data);

	info="Jugando...        ";

	piLock (SYSTEM_FLAGS_KEY);
	flags &= ~FLAG_TIMER_JUEGO;
	piUnlock (SYSTEM_FLAGS_KEY);
	
	
	if(CompruebaReboteParedesVerticales(*p_arkanoPi)){
		//PAREDES SIN REBOTE VERTICAL EN EL NIVEL 3
		if(nivel==3){
			//Si la pelota se encuentra en los limites verticales de la matriz
			//Las coordenadas de la pelota cambian, y se actualizan al lado contrario
			if(p_arkanoPi->pelota.x >= NUM_COLUMNAS_DISPLAY){
				p_arkanoPi->pelota.x = 0;
			}else if(p_arkanoPi->pelota.x <= 0){
				p_arkanoPi->pelota.x = 7;
			}
		}else{
			p_arkanoPi->pelota.trayectoria.xv = -p_arkanoPi->pelota.trayectoria.xv;
		}
	}
	if(CompruebaReboteTecho(*p_arkanoPi)){//
		p_arkanoPi->pelota.trayectoria.yv = -p_arkanoPi->pelota.trayectoria.yv;
	}
	
	//Si la pelota no choca con la pala, se produce un fallo y se resta 1 a las vidas
	if(CompruebaFallo(*p_arkanoPi)) {
		lifes--;
		//Mientra la variable vidas sea mayor que cero, el juego seguira ejecutandose
		//Cada vez que se pierde una vida, se empieza desde 0
		if(lifes>=0){
			p_arkanoPi->score=0;

			InicializaPelota(&(p_arkanoPi->pelota));
			InicializaLadrillos((tipo_pantalla*)(&(p_arkanoPi->ladrillos)));

			tmr_startms((tmr_t*)(p_arkanoPi->tmr_actualizacion_juego), TIMEOUT_ACTUALIZA_JUEGO);

		}else{
			lifes = 0;
			info="Has perdido         ";
			piLock(SYSTEM_FLAGS_KEY);
			flags |= FLAG_FIN_JUEGO;
			piUnlock(SYSTEM_FLAGS_KEY);
			//exit(0);
		}
		return;
	}else if(CompruebaRebotePala(*p_arkanoPi)){
		//Cuando al pelota choca con la pala, se produce un sonido de choque
		printf("%c",7);
		switch(p_arkanoPi->pelota.x + p_arkanoPi->pelota.trayectoria.xv - p_arkanoPi->pala.x){
			case 0:
				CambiarDireccionPelota(&(p_arkanoPi->pelota),ARRIBA_IZQUIERDA);
				break;
			case 1:
				CambiarDireccionPelota(&(p_arkanoPi->pelota),ARRIBA);
				break;
			case 2:
				CambiarDireccionPelota(&(p_arkanoPi->pelota),ARRIBA_DERECHA);
				break;
		}
	}
	
	//Si la pelota destruye un ladrillo, se suma 1 a la variable scores
	if(CompruebaReboteLadrillo(p_arkanoPi)){
		p_arkanoPi->score++;
		p_arkanoPi->pelota.trayectoria.yv = -p_arkanoPi->pelota.trayectoria.yv;
		//Cuando al pelota choca con la pala, se produce un sonido de choque
		printf("%c",7);
		//Cuando el nivel del juego es 3, puede producirse errores si la pelota está en la coordenada y=1 y x=0 o x=7,
		//por ello con esta condición nos aseguramos que no se produzca ningún error mientras jugamos.
		if(nivel==3){
				if(p_arkanoPi->pelota.x >= NUM_COLUMNAS_DISPLAY){
					p_arkanoPi->pelota.x = 0;
				}else if(p_arkanoPi->pelota.x <= 0){
					p_arkanoPi->pelota.x = 7;
				}
		}

		if(CalculaLadrillosRestantes(&(p_arkanoPi->ladrillos)) <= 0){
			info="Has perdido         ";
			piLock(SYSTEM_FLAGS_KEY);
			flags |= FLAG_FIN_JUEGO;
			piUnlock(SYSTEM_FLAGS_KEY);
			//exit(0);
		}
	}

	ActualizaPosicionPelota(&(p_arkanoPi->pelota));
	//Sistema de niveles por puntos
	if(p_arkanoPi->score < 3){
		nivel=1;
		speed = TIMEOUT_ACTUALIZA_JUEGO;
	}else if(p_arkanoPi->score < 5){
		nivel=2;
		speed=1300;
	}else if(p_arkanoPi->score < 10){
		nivel=3;
		speed=1000;

	}else if(p_arkanoPi->score >= 10){
		info="Has ganado!!        ";

		piLock(SYSTEM_FLAGS_KEY);
		flags |= FLAG_FIN_JUEGO;
		piUnlock(SYSTEM_FLAGS_KEY);

	}else{
		speed = TIMEOUT_ACTUALIZA_JUEGO;
	}
	
	//Se guarda en la variable bestscore la mejor marca de todos los intentos,
	//luego se muestra por pantalla en el marcador
	if(p_arkanoPi->score>bestscore){
		bestscore=p_arkanoPi->score;
	}

	piLock(MATRIX_KEY);
	ActualizaPantalla(p_arkanoPi,0);
	piUnlock(MATRIX_KEY);

	tmr_startms((tmr_t*)(p_arkanoPi->tmr_actualizacion_juego), speed);
}

// void FinalJuego (void): función encargada de mostrar en la ventana de
// terminal los mensajes necesarios para informar acerca del resultado del juego.

void FinalJuego (fsm_t* this) {

	info="Juego terminado       ";

	piLock (SYSTEM_FLAGS_KEY);
	flags &= ~FLAG_FIN_JUEGO;
	piUnlock (SYSTEM_FLAGS_KEY);

	//pseudoWiringPiEnableDisplay(0);
	//NO se utiliza la ultima sentencia para que se puede imprimir la informacion del juego
}

//void ReseteaJuego (void): función encargada de llevar a cabo la
// reinicialización de cuantas variables o estructuras resulten
// necesarias para dar comienzo a una nueva partida.

void ReseteaJuego (fsm_t* this) {
	tipo_arkanoPi* p_arkanoPi;
	p_arkanoPi = (tipo_arkanoPi*)(this->user_data);

	info="Reseteo       ";

	piLock (SYSTEM_FLAGS_KEY);
	flags &= ~FLAG_BOTON;
	piUnlock(SYSTEM_FLAGS_KEY);

	ResetArkanoPi(p_arkanoPi);
	p_arkanoPi->score=0;
	lifes=3;

}

//void PausaJuego (void): función encargada de llevar a cabo la
// pausa de la partida.
void PausaJuego(fsm_t* this){
	tipo_arkanoPi* p_arkanoPi;
	p_arkanoPi = (tipo_arkanoPi*)(this->user_data);

	info="Pausa        ";

	piLock (SYSTEM_FLAGS_KEY);
	flags &= ~FLAG_PAUSA;
	piUnlock(SYSTEM_FLAGS_KEY);

	PausaArkanoPi(p_arkanoPi);

	piLock(MATRIX_KEY);
	ActualizaPantalla(p_arkanoPi,0);
	piUnlock(MATRIX_KEY);
	//El timeout del timer es cero para que el juego se quede congelado
	speed=0;
	tmr_startms((tmr_t*)(p_arkanoPi->tmr_actualizacion_juego), speed);
}

//void PausaJuego (void): función encargada de llevar a cabo el
// fin de pausa de la partida
void FinalPausaJuego(fsm_t* this){
	tipo_arkanoPi* p_arkanoPi;
	p_arkanoPi = (tipo_arkanoPi*)(this->user_data);

	piLock (SYSTEM_FLAGS_KEY);
	flags &= ~FLAG_FINAL_PAUSA;
	piUnlock(SYSTEM_FLAGS_KEY);
	//Determina el valor del timeout después de la pausa, segun el número de scores
	if(p_arkanoPi->score < 5){
		speed=1300;
	}else if(p_arkanoPi->score < 10){
		speed=1000;
	}else{
		speed = TIMEOUT_ACTUALIZA_JUEGO;
	}

	tmr_startms((tmr_t*)(p_arkanoPi->tmr_actualizacion_juego), speed);
}

//------------------------------------------------------
// SUBRUTINAS DE ATENCION A LAS INTERRUPCIONES
//------------------------------------------------------

void tmr_actualizacion_juego_isr(union sigval value) {
	// A completar por el alumno
	// ...
	piLock (SYSTEM_FLAGS_KEY);
	flags |= FLAG_TIMER_JUEGO;
	piUnlock(SYSTEM_FLAGS_KEY);
}
