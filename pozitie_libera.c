#include "pozitie_libera.h"


DateIntrare* citeste_fisier_in(char *nume_fisier_intrare) {
    // TODO citeste datele din fisier si populeaza pointerul la structura
    DateIntrare *input = (DateIntrare*)malloc(sizeof(DateIntrare));
    FILE *f = fopen(nume_fisier_intrare, "r");

    fscanf(f, "%d%d", &input->numarul_maxim_din_intrari, &input->numar_intrari);
    input->intrari = (int*)malloc(sizeof(int) * (input->numarul_maxim_din_intrari + 1));
    for(int i = 0; i < input->numar_intrari; i++)
    {
    	fscanf(f, "%d", &input->intrari[i]);
    }
    fclose(f);

    return input;
}

void actualizare_cu_delta(Nod *nod, int v2) {
    nod->info += v2;
}

int interogare(int r1, int r2) {
    return r1 + r2;
}

int* calculeaza_vector_raspuns(DateIntrare *date_intrare) {
    // TODO creeaza vectorul raspuns folosind arbori de intervale
    int *sol = (int*)malloc(sizeof(int) * (date_intrare->numarul_maxim_din_intrari + 1)), i;
    ArboreDeIntervale *arbore = construieste_arbore(0, date_intrare->numarul_maxim_din_intrari, -1, actualizare_cu_delta, interogare);
	for(i = 0; i < date_intrare->numarul_maxim_din_intrari + 1; i++)
    {
    	sol[i] = -1;
    }

    for(i = 0; i < date_intrare->numar_intrari; i++)
    {
    	if(sol[date_intrare->intrari[i]] == -1)
    	{
    		Interval *interval = (Interval*)malloc(sizeof(Interval));
            interval->capat_stanga = date_intrare->intrari[i];
            interval->capat_dreapta = date_intrare->intrari[i];
    		actualizare_interval_in_arbore(arbore, interval, date_intrare->intrari[i]);
    		sol[date_intrare->intrari[i]] = date_intrare->intrari[i];
    	}
    	else
    	{
    		
    	}
    }

    return sol;
}


int* calculeaza_vector_raspuns_trivial(DateIntrare *date_intrare) {
    // TODO creeaza vectorul raspuns folosind 2 for-uri
    int *sol = (int*)malloc(sizeof(int) * (date_intrare->numarul_maxim_din_intrari + 1)), i, j;
    for(i = 0; i < date_intrare->numarul_maxim_din_intrari + 1; i++)
    {
    	sol[i] = -1;
    }

    for(i = 0; i < date_intrare->numar_intrari; i++)
    {
    	if(sol[date_intrare->intrari[i]] == -1)
    	{
    		sol[date_intrare->intrari[i]] = date_intrare->intrari[i];
    	}
    	else
    	{
    		for(j = date_intrare->intrari[i] - 1; j >= 0; j--)
    		{
    			if(sol[j] == -1)
    			{
    				sol[j] = date_intrare->intrari[i];
    				break;
    			}
    		}
    	}
    }
    
    return sol;
}