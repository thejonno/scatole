#include "funzioni_sca.h"

//questa funzione prende un puntatore ad una stringa e crea
// una stringa che al suo inizio contine la sua lunghezza
char* crea_fs(char *s, int lun){
	int lun_vera = sizeof(char)*lun + sizeof(int) + sizeof(char);
	char* s_ptr = malloc(lun_vera);
	*(int*)s_ptr = lun;
	
	for(int i =0; i<lun; i++){
		s_ptr[i+sizeof(int)] = s[i];
	}
	s_ptr[lun_vera -1] = 0;
	return s_ptr;
}

//questa funione stampa una stringa di lunghezza predeterminata
void stampa_fs(char* fs){
	int lunghezza = *(int*)fs;
	
	for(int i =0; i< lunghezza; i++){
		printf("%c", fs[i+sizeof(int)]);
	}
}

//questa funzione crea una stringa dall'input dell'utente
char* crea_input_s(char *buff){
	int lun =0;
	char c;
	
	while((c =getchar()) && c!= '~' && lun <= 255){
		buff[lun]=c;
		lun++;
	}
	
	int lun_vera = sizeof(char)*lun + sizeof(int) + sizeof(char);
	char* str_ptr = malloc(lun_vera);
	*(int*)str_ptr = lun;
	
	for(int i =0; i < lun; i++){
		str_ptr[i+sizeof(int)] = buff[i];
	}
	str_ptr[lun_vera-1] = 0;
	return str_ptr;
}

//questa funzione crea una stringa da un puntatore a char
char* crea_autofs(char* s){
	int lun = 0;
	char c= 'a';
	while(c != 0){c = s[lun];lun++;}
	
	int lun_vera = sizeof(int) + sizeof(char)*(lun +1);
	char* str_ptr = malloc(lun_vera);
	
	*(int*) str_ptr = lun;
	for(int i = 0; i< lun; i++){
		str_ptr[i+sizeof(int)]=s[i];
	}
	str_ptr[lun_vera-1] = 0;
	return str_ptr;
}

//questa funzione crea una scatola
struct sca* crea_scatola(int* id){
	(*id)++;
	char buff[256];
	struct sca* sca_ptr = malloc(sizeof(struct sca));
	sca_ptr->id = *id;
	sca_ptr->contenuto = crea_input_s(buff);
	sca_ptr->step_back =NULL;
	sca_ptr->step_forw = NULL;
	return sca_ptr;
}

//quesa funzione crea una scatola con una stringa prefatta
struct sca* crea_autosca(int* id, char*s){
	(*id)++;
	struct sca* sca_ptr = malloc(sizeof(struct sca));
	sca_ptr->id = *id;
	sca_ptr->contenuto = crea_autofs(s);
	sca_ptr->step_back =NULL;
	sca_ptr->step_forw = NULL;
	return sca_ptr;
}

//questa funzione stampa una scatola
void stampa_sca(struct sca* sca){
	stampa_fs(sca->contenuto);
}

//questa funzione lega due scatole insieme
void lega_sca(struct sca* sca_1, struct sca* sca_2){
	sca_1->step_forw = sca_2;
	sca_2->step_back = sca_1;
}

//questa funzione stampa la lista delle scatole
void vis_lista(struct sca* ult_sca, struct sca* sca_sel){
	
	struct sca* sca_corr = sca_sel;
	int i =0;
	
	while(sca_corr->step_back != NULL && i<5){
		sca_corr =sca_corr->step_back;
		i++;
		}
		
		i =0;
	while(sca_corr!= NULL&&i<10){
		if(sca_sel == sca_corr){
			printf("[%d]*", sca_corr->id);
			sca_corr =sca_corr->step_forw;
		}
		
		else{
			printf("[%d]", sca_corr->id);
			sca_corr =sca_corr->step_forw;
		}
		i++;
	}	
}


//questa funzione sposta il cursore avanti o indietro
struct sca* sposta_cursore(struct sca* sca_sel, int com){
	if(sca_sel->step_forw != NULL && com == 77){sca_sel = sca_sel->step_forw;}
	if(sca_sel->step_back != NULL && com == 75){sca_sel = sca_sel->step_back;}
	return sca_sel;
}


//questa funzione stabilisce quale degli estremi di una scatola, puntano a NULL
// 'e' -> entrambi
// 'b' -> step_back
// 'f' -> step_forw
// 'n' -> nessuno
char guarda_steps(struct sca* s){
	char c;
	if (s->step_back ==NULL){
		c= 'b';
		if(s->step_forw == NULL){
			c = 'e';	
		}
	}
	else if(s->step_forw == NULL){
		c = 'f';
	}
	else{c = 'n';}
	return c;
}

//questa funzione prende un intero per decidere a che scatola puntare
//id negativi sono usati per scatole in posizioni speciali
struct sca* scorri_sca(struct sca* ult_sca,int id_to_find){
	struct sca* ptr_sca = ult_sca;
	
	if(id_to_find > ult_sca->id){ /*messaggio errore */ return ptr_sca;}
	while(ptr_sca != NULL){
		if(ptr_sca->id == id_to_find){break;}
		
		if(ptr_sca->step_back!=NULL){
			ptr_sca = ptr_sca->step_back;
			}
		char c = guarda_steps(ptr_sca);
		if (c=='b' || c=='e'){break;}
	}
	return ptr_sca;
}

struct sca* elimina_sca(int*id, struct sca* sca_sel, struct sca** ult_sca){
	char c =guarda_steps(sca_sel);
	struct sca* ptr_sca = sca_sel;
	struct sca* sca_corr= sca_sel;
	int skip_flag =0;
	
	
	switch(c){	
		case 'n': 	sca_sel->step_forw->step_back = sca_sel->step_back;
					sca_sel->step_back->step_forw = sca_sel->step_forw;
					ptr_sca = sca_sel->step_back;
					while(sca_corr != NULL){sca_corr->id = sca_corr->id-1;
											sca_corr=sca_corr->step_forw;}
					break;
					
		case 'b':	sca_sel->step_forw->step_back = NULL;
					ptr_sca = sca_sel->step_forw;
					while(sca_corr != NULL){	sca_corr->id = sca_corr->id-1;
											sca_corr=sca_corr->step_forw;}
					ptr_sca = sca_sel->step_forw;
					break;
		case 'f': 	sca_sel->step_back->step_forw = NULL;
					ptr_sca = sca_sel->step_back;
					*ult_sca= (*ult_sca)->step_back;
					break;
		case 'e': 	printf("ERRORE: E' necessaria almeno una scatola!!\n");
					skip_flag =1;
					break;
		
	}
	if(skip_flag != 1){free(sca_sel->contenuto); free(sca_sel);(*id)--;}
	return ptr_sca;
}


//questa funzione traduce un numero in una stringa
//il numero puo' avere al massimo 12 cifre
char* inum_to_cnum(unsigned int num){
	int i = 0;
	unsigned int num_c = num;
	//conto il numero di cifre
	while(num>0){
		num /=10;
		i++;
	}
	num = num_c; 	//gioco di parole tra num_c che
					//puo' essere completato sia con 'copy' che con 'cifre'
	num_c = i;
	char* buff_2 = malloc(sizeof(char)*(num_c+1));
	char buff_1[num_c];

	
	for(int i = 0; i < num_c; i++){
		buff_1[i] = (num %10) +'0';
		num /=10;
	}
	for(int i = 0; i < num_c ; i++){
		buff_2[i] = buff_1[num_c -i-1];
	}
	buff_2[num_c] = 0;
	
	return buff_2;
}



//questa funzione crea x autoscatole
//assegna ad ognuna una stringa con un numero che va da uno a x
struct sca* crea_autolista(		int *id,
								unsigned int num_sca,
 								struct sca* s_ini,
								struct sca** ult_sca){
									
	for (int i = 0; i< num_sca; i++){
	struct sca* s1 =crea_autosca(id, inum_to_cnum(i +1));
	lega_sca(s_ini, s1);
	s_ini=s1;
	if(i == num_sca-1){*ult_sca = s_ini;}
	}
	return *ult_sca;
}
 
 
//questa funzione cambia il valore di 4 byte di un array di char in un unsigned int
void uint_in_charr(char* arr,int indice, int valore){
		*(unsigned int*)&arr[indice] = valore;
}

//questa funzione fa l'opposto della precedente
unsigned int charr_to_uint(char* arr, int indice){
	unsigned int valore = *(unsigned int*)&arr[indice];
	return valore;
}

 
//questa funzione copia un messaggio da un puntatore a messaggio ad un buffer
//inizia a copiare il messaggio da uno specifico byte del buffer_avvisi
//max_avv e' il numero di byte massimo
void invia_messaggio(char* buff_avvisi, int max_avv, char* messaggio, int* avvisi_mancati){
	int inzio_messaggio = *(unsigned int*)buff_avvisi;
	
	//siccome il byte inziale non puo' essere 0
	//uso 0 per indicare che il buff e' pieno
	if (inzio_messaggio == 0){(*avvisi_mancati)++; return;}	
		
	char* avviso = crea_autofs(messaggio);
	//calcolo se la stringa ci stara', se non ci sta'
	//interrompo la stringa e incremento i messaggi mancati
	if(inzio_messaggio + *(int*)avviso >= max_avv){(*avvisi_mancati)++;return;}
	int i =0;
	for (; i<*(int*)avviso; i++){
		buff_avvisi[i+inzio_messaggio] = avviso[i+sizeof(int)];
	}
	/*setto il byte di buff avvisi in modo che sia uguale a quanto era prima piu lun string*/
	uint_in_charr(buff_avvisi, 0, *(unsigned int*)buff_avvisi+ i);
	free(avviso);	
}


//questa funzione stampa il buff avvisi
void stampa_buff_avv(char*buff_avv, int max_avv){
	for(int i=0; i<*(unsigned int*)buff_avv - 4; i++){
		printf("%c", buff_avv[sizeof(unsigned int) + i]);
	}
}

//questa funzione permette di riscrivere il contenuto di una scatola
void riscrivi_contenuto(struct sca* sca_sel, char*buff){
	free(sca_sel->contenuto);
	printf("riscrivi il contenuto della scatola:\n\n\n");
	sca_sel->contenuto = crea_input_s(buff);
}


//questa funzione crea una sezione di lista usando crea_autolista
//e degli input dall'utente
void crea_sezione_lista(){
	
}


























