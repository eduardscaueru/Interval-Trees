#ifndef _POZITIE_LIBERA_H_
#define _POZITIE_LIBERA_H_

#include <stdio.h>
#include <stdlib.h>
#include "arbori_intervale.h"


typedef struct date_intrare {
    int numarul_maxim_din_intrari;
    int numar_intrari;
    int *intrari;
} DateIntrare;


DateIntrare* citeste_fisier_in(char *nume_fisier_intrare);

// functie care rezolva problema cu arbori de intervale
int* calculeaza_vector_raspuns(DateIntrare *date_intrare);

// functie care rezolva problema cu 2 for-uri
int* calculeaza_vector_raspuns_trivial(DateIntrare *date_intrare);


#endif