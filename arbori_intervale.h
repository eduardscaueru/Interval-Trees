#ifndef _ADI_H_
#define _ADI_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct interval {
    int capat_stanga;
    int capat_dreapta;
} Interval;


typedef struct nod {
    int info;
    Interval *interval;
    struct nod *copil_stanga;
    struct nod *copil_dreapta;
} Nod;


typedef struct adi {
    Nod* radacina;
    int dimensiune;
    int valoare_predifinita_raspuns_copil;
    void (*f_actualizare)(Nod *nod, int valoare_ce_modifica);
    int (*f_combinare_raspunsuri_copii)(int raspuns_stanga, int raspuns_dreapta);
} ArboreDeIntervale;

/** functii necesare pentru primele doua taskuri **/
ArboreDeIntervale* construieste_arbore(int capat_stanga, int capat_dreapta,
                    int valoare_predifinita_raspuns_copil,
                    void (*f_actualizare)(Nod *nod, int v_actualizare),
                    int (*f_combinare_raspunsuri_copii)(int raspuns_stanga, int raspuns_dreapta));

void actualizare_interval_in_arbore(ArboreDeIntervale *arbore, 
                                        Interval *interval, int v_actualizare);

void actualizare_interval_pentru_nod(ArboreDeIntervale *arbore, Nod *nod, 
                                        Interval *interval, int v_actualizare);

int interogare_interval_in_arbore(ArboreDeIntervale *arbore, Interval *interval);

int interogare_interval_pentru_nod(ArboreDeIntervale *arbore, Nod *nod, Interval *interval);


/** functii (poate?) utile pentru bonus, NU trebuie implementare neaparat **/

void seteaza_info_in_arbore_la_valoare_capat_dreapta(ArboreDeIntervale* arbore);

void seteaza_info_in_nod_la_valoare_capat_dreapta(Nod* nod);

#endif