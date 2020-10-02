#include "arbori_intervale.h"

Nod *alocare_nod(int st, int dr)
{
	Nod *nou_nod = (Nod*)malloc(sizeof(Nod));
	nou_nod->copil_stanga = NULL;
	nou_nod->copil_dreapta = NULL;
	nou_nod->info = 0;
	nou_nod->interval = (Interval*)malloc(sizeof(Interval));
	nou_nod->interval->capat_stanga = st;
	nou_nod->interval->capat_dreapta = dr;

	return nou_nod;
}

void creare(Nod **nod, int st, int dr)
{
	(*nod) = alocare_nod(st, dr);
	if(st < dr)
	{
		int mijloc = (st + dr)/2;
		creare(&((*nod)->copil_stanga), st, mijloc);
		creare(&((*nod)->copil_dreapta), mijloc + 1, dr);
	}
}

ArboreDeIntervale *construieste_arbore(int capat_stanga, int capat_dreapta,
        int valoare_predifinita_raspuns_copil,
        void (*f_actualizare)(Nod *nod, int v_actualizare),
        int (*f_combinare_raspunsuri_copii)(int raspuns_stanga, int raspuns_dreapta)) {
    // TODO implementati functia de constructie a arborelui prezentata in enunt
    // TODO initializati campurile unui ArboreDeIntervale*
    ArboreDeIntervale *arbore = (ArboreDeIntervale*)malloc(sizeof(ArboreDeIntervale));
    arbore->radacina = NULL;
    arbore->dimensiune = 1;
    arbore->valoare_predifinita_raspuns_copil = valoare_predifinita_raspuns_copil;
    arbore->f_actualizare = f_actualizare;
    arbore->f_combinare_raspunsuri_copii = f_combinare_raspunsuri_copii;
    creare(&arbore->radacina, capat_stanga, capat_dreapta);

    return arbore;
}


void actualizare_interval_pentru_nod(ArboreDeIntervale *arbore, Nod *nod,
                                        Interval *interval, int v_actualizare) {
    // TODO implementati functia de actualizare pentru un nod
    // Hint: pentru a actualiza un nod cand este cazul folositi arbore->f_actualizare(nod, v_actualizare);
    if(interval->capat_stanga <= nod->interval->capat_stanga && nod->interval->capat_dreapta <= interval->capat_dreapta)
    {
    	arbore->f_actualizare(nod, v_actualizare);
    }
    else
    {
    	int mijloc = (nod->interval->capat_stanga + nod->interval->capat_dreapta)/2;
    	if(interval->capat_stanga <= mijloc)
    	{
    		actualizare_interval_pentru_nod(arbore, nod->copil_stanga, interval, v_actualizare);
    	}
    	if(mijloc < interval->capat_dreapta)
    	{
    		actualizare_interval_pentru_nod(arbore, nod->copil_dreapta, interval, v_actualizare);
    	}
    	arbore->f_actualizare(nod, v_actualizare);
    }
}


// Functia este deja implementata, se cheama functia de mai sus cu radacina arborelui
void actualizare_interval_in_arbore(ArboreDeIntervale *arbore, 
                                        Interval *interval, int v_actualizare) {
    actualizare_interval_pentru_nod(arbore, arbore->radacina, interval, v_actualizare);
}


int interogare_interval_pentru_nod(ArboreDeIntervale *arbore, Nod *nod, Interval *interval) {
    // TODO implementati functia de interogare pentru un nod prezentata in enunt
    // Hint: cand vreti sa calculati combinarea raspunsurilor folositi
    // arbore->f_combinare_raspunsuri_copii(raspuns_copil_stanga, raspuns_copil_drepta)
   	int val_st = 0, val_dr = 0;

    if(interval->capat_stanga <= nod->interval->capat_stanga && nod->interval->capat_dreapta <= interval->capat_dreapta)
    {
    	return nod->info;
    }
    else
    {
    	int mijloc = (nod->interval->capat_stanga + nod->interval->capat_dreapta)/2;
    	if(interval->capat_stanga <= mijloc)
    	{
    		val_st = interogare_interval_pentru_nod(arbore, nod->copil_stanga, interval);
    	}
    	if(mijloc < interval->capat_dreapta)
    	{
    		val_dr = interogare_interval_pentru_nod(arbore, nod->copil_dreapta, interval); 
    	}
    	return arbore->f_combinare_raspunsuri_copii(val_st, val_dr);
    }
}


// Functia este deja implementata, se cheama functia de mai sus cu radacina arborelui
int interogare_interval_in_arbore(ArboreDeIntervale *arbore, Interval *interval) {
    return interogare_interval_pentru_nod(arbore, arbore->radacina, interval);
}


// ----- DOAR pentru bonus si DOAR daca considerati ca e necesara ----- //
void seteaza_info_in_nod_la_valoare_capat_dreapta(Nod* nod) {
    // TODO cred ca e destul de clar ce vrea sa faca functia asta
    
}


void seteaza_info_in_arbore_la_valoare_capat_dreapta(ArboreDeIntervale* arbore) {
    seteaza_info_in_nod_la_valoare_capat_dreapta(arbore->radacina);
}
