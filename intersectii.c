#include "intersectii.h"


// functie ajutatoare
void afiseaza_lista_intervale(ListaIntervale2D *lista) {
    int i;
    for (i = 0; i < lista->dimensiune; i++) {
        Interval2D *interv = lista->intervale[i];
        printf("{punct stanga x: %d, punct stanga y: %d, punct dreapta x: %d, punct dreapta y: %d}\n",
                    interv->punct_stanga->x, interv->punct_stanga->y,
                    interv->punct_dreapta->x, interv->punct_dreapta->y);
    }
}


ListaIntervale2D* citeste_intrare(char *nume_fisier_intrare) {
    // TODO citeste intervalele din fisierul dat ca parametru
    // si le salveaza in lista de intervale
    ListaIntervale2D *lista_intervale = (ListaIntervale2D*)malloc(sizeof(ListaIntervale2D));
    FILE *f = fopen(nume_fisier_intrare, "r");
    int n, i, x1, y1, x2, y2;

    fscanf(f, "%d", &n);
    lista_intervale->intervale = (Interval2D**)malloc(sizeof(Interval2D*) * n);
    lista_intervale->dimensiune = n;

    for(i = 0; i < n; i++)
    {
        lista_intervale->intervale[i] = (Interval2D*)malloc(sizeof(Interval2D));
        lista_intervale->intervale[i]->punct_stanga = (Punct2D*)malloc(sizeof(Punct2D));
        lista_intervale->intervale[i]->punct_dreapta = (Punct2D*)malloc(sizeof(Punct2D));
        fscanf(f, "%d %d %d %d", &x1, &y1, &x2, &y2);
        lista_intervale->intervale[i]->punct_stanga->x = x1;
        lista_intervale->intervale[i]->punct_stanga->y = y1;
        lista_intervale->intervale[i]->punct_dreapta->x = x2;
        lista_intervale->intervale[i]->punct_dreapta->y = y2;
    }
    fclose(f);

    return lista_intervale;
}

// ! Functie pentru actualizarea in arbore
// ! O veti da ca parametru cand initializati arborele
void actualizare_cu_delta(Nod *nod, int v2) {
    nod->info += v2;
}

// ! Functie pentru combinarea raspunsurilor in arbore
// ! O veti da ca parametru cand initializati arborele
int suma_raspunsurilor(int r1, int r2) {
    return r1 + r2;
}

int compare(const void *a, const void *b)
{
    const PuncteSortate *elem1 = a;
    const PuncteSortate *elem2 = b;

    if(elem1->punct->x < elem2->punct->x)
        return -1;
    else if(elem1->punct->x > elem2->punct->x)
        return 1;
    else
        return 0;
}

int calculeaza_numar_intersectii(ListaIntervale2D *lista) {
    // TODO calculati numarul de intersectii folosind arbori de intervale conform enuntului
    // Hint: initializarea arborelui: 
    // ArboreDeIntervale *arbore = construieste_arbore(0, y_max, 0, actualizare_cu_delta, suma_raspunsurilor);
    int n = lista->dimensiune, y_max = -1, i, k = 0, sol = 0, nr = 0;

    for(i = 0; i < n; i++)
    {
        if(lista->intervale[i]->punct_dreapta->y > y_max) y_max = lista->intervale[i]->punct_dreapta->y;
    }

    ArboreDeIntervale *arbore = construieste_arbore(0, y_max, 0, actualizare_cu_delta, suma_raspunsurilor);
    PuncteSortate *puncte_sortate = (PuncteSortate*)malloc(sizeof(PuncteSortate) * n * 2);

    for(i = 0; i < n; i++)
    {
        puncte_sortate[k].punct = lista->intervale[i]->punct_stanga;
        puncte_sortate[k].interval = lista->intervale[i];
        puncte_sortate[k+1].punct = lista->intervale[i]->punct_dreapta;
        puncte_sortate[k+1].interval = lista->intervale[i];
        k += 2;
    }

    qsort(puncte_sortate, 2*n, sizeof(PuncteSortate), compare);

    for(k = 0; k < 2*n; k++)
    {
        if(puncte_sortate[k].interval->punct_dreapta->y == puncte_sortate[k].interval->punct_stanga->y && puncte_sortate[k].punct == puncte_sortate[k].interval->punct_stanga)
        {
            Interval *interval = (Interval*)malloc(sizeof(Interval));
            interval->capat_stanga = puncte_sortate[k].punct->y;
            interval->capat_dreapta = puncte_sortate[k].punct->y;
            actualizare_interval_in_arbore(arbore, interval, 1);
        }
        if(puncte_sortate[k].interval->punct_dreapta->y == puncte_sortate[k].interval->punct_stanga->y && puncte_sortate[k].punct == puncte_sortate[k].interval->punct_dreapta)
        {
            Interval *interval = (Interval*)malloc(sizeof(Interval));
            interval->capat_stanga = puncte_sortate[k].punct->y;
            interval->capat_dreapta = puncte_sortate[k].punct->y;
            actualizare_interval_in_arbore(arbore, interval, -1);
        }
        if(puncte_sortate[k].interval->punct_dreapta->x == puncte_sortate[k].interval->punct_stanga->x)
        {
            if(nr % 2 == 1)
            {
                Interval *interval = (Interval*)malloc(sizeof(Interval));
                interval->capat_stanga = puncte_sortate[k].interval->punct_stanga->y;
                interval->capat_dreapta = puncte_sortate[k].interval->punct_dreapta->y;
                sol += interogare_interval_in_arbore(arbore, interval);
            }
            nr++;
        }
    }

    return sol;
}


int calculeaza_numar_intersectii_trivial(ListaIntervale2D *lista) {
    // TODO: solutia triviala, verific fiecare segment cu fiecare segment daca se intersecteaza 
    int sol = 0, i, n = lista->dimensiune, j;

    for(i = 0; i < n; i++)
    {
        if(lista->intervale[i]->punct_stanga->x == lista->intervale[i]->punct_dreapta->x)
        {
            for(j = 0; j < n; j++)
            {
                if(lista->intervale[j]->punct_stanga->y == lista->intervale[j]->punct_dreapta->y)
                {
                    if(lista->intervale[i]->punct_stanga->x >= lista->intervale[j]->punct_stanga->x
                        && lista->intervale[i]->punct_stanga->x <= lista->intervale[j]->punct_dreapta->x
                        && lista->intervale[j]->punct_stanga->y >= lista->intervale[i]->punct_stanga->y
                        && lista->intervale[j]->punct_stanga->y <= lista->intervale[i]->punct_dreapta->y)
                    {
                        sol++;
                    }
                }
            }
        }
    }

    return sol;
}
