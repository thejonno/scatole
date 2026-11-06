#ifndef FUNZIONI_SCA
#define FUNZIONI_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//buffer messaggio
struct mbuff{
	char* buff_avv;
	int max_avv;
	int avv_mancati;
	char* messaggio;
};

struct sca{
	struct sca* step_back;
	struct sca* step_forw;
	char* contenuto;
	int id;
};

char* crea_fs();
void stampa_fs();
char* crea_input_s();
struct sca* crea_scatola();
void stampa_sca();
void lega_sca();
void vis_lista();
struct sca* sposta_cursore();
struct sca* elimina_sca();
char guarda_steps();
struct sca* crea_autosca();
char* crea_autofs();
struct sca* crea_autolista();
struct sca* scorri_sca();
void invia_messaggio();
void uint_in_charr();
unsigned int charr_to_uint();
void stampa_buff_avv();
void riscrivi_contenuto();


#endif