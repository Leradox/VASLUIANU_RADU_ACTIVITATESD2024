#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Biblioteca Biblioteca;
typedef struct Nod Nod;

struct Biblioteca {
    char* nume;
    int nrCarti;
    int nrCititori;
};

struct Nod {
    Biblioteca info;
    Nod* next;
    Nod* prev;
};
typedef struct ListaDubla ListaDubla;
struct ListaDubla {
    Nod* head;
    Nod* tail;
};





Biblioteca initializare(const char* nume, int nrCarti, int nrCititori) {
    Biblioteca b;
    b.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(b.nume, nume);
    b.nrCarti = nrCarti;
    b.nrCititori = nrCititori;
    return b;
}

void inserareInceput(ListaDubla* listadubla, Biblioteca b) {
    Nod* nod = (Nod*)malloc(sizeof(Nod));
    nod->info = b;
    nod->next = listadubla->head;
    nod->prev = NULL;
    if (listadubla->head)
    {
      listadubla->head->prev = nod;
    
    }
    else {
       
        listadubla->tail = nod;
    }
    listadubla->head = nod;

}
void afisaseListaInceput(ListaDubla listadubla)
{
    while (listadubla.head)
    {
        printf("Bibilioteca: %s, Nr cititotri: %d, Nr. Carti: %d\n" , listadubla.head->info.nume, listadubla.head->info.nrCititori, listadubla.head->info.nrCarti);
        listadubla.head = listadubla.head->next;
    }
    printf("\n");
    
}

void stergeNodNume(ListaDubla* listadubla, const char* nume)
{
    Nod* aux = listadubla->head;
    while (aux && strcmp(nume,aux->info.nume)!=0)
    {
        aux = aux->next;
    }
    if (aux)
    {
        if (aux == listadubla->head)
        {
            if (aux == listadubla->tail)
            {
                listadubla->head = NULL;
                listadubla->tail = NULL;
                
            }
            else
            {
                listadubla->head = listadubla->head->next;
                listadubla->head->prev = NULL;
            }
            
        }
        else
        {
            if (aux == listadubla->tail)
            {
                aux->prev->next = NULL;
                listadubla->tail = aux->prev;
            }
            else
            {
                aux->next->prev = aux->prev;
                aux->prev->next = aux->next;
            }
        }
        free(aux->info.nume);
        free(aux);

    }
}
int nrCartiTotal(ListaDubla listadubla)
{
    int rezultat = 0;
    while (listadubla.tail)
    {
        rezultat += listadubla.tail->info.nrCarti;
        listadubla.tail = listadubla.tail->prev;

    }
    return rezultat;
}

void stergereLista(ListaDubla* listadubla)
{
    while (listadubla->head)
    {
        free(listadubla->head->info.nume);
        Nod* aux = listadubla->head;

        listadubla->head = listadubla->head->next;
        free(aux);
    }
   
    listadubla->head = NULL;
    listadubla->tail = NULL;
}

void main() {
   
    Biblioteca b1 = initializare("Mihai Eminescu", 150, 30);
    Biblioteca b2 = initializare("Ioan Slavici", 200, 30);
    Biblioteca b3 = initializare("Tudor Arghezi", 100, 15);
   
    ListaDubla listadubla;
    listadubla.head = NULL;
    listadubla.tail = NULL; 
    inserareInceput(&listadubla, b1);
    inserareInceput(&listadubla, b2);
    inserareInceput(&listadubla, b3);
    afisaseListaInceput(listadubla);

    //stergeNodNume(&listadubla, "Ioan Slavici");
    //afisaseListaInceput(listadubla);
    //stergeNodNume(&listadubla, "Mihai Eminescu");
    //afisaseListaInceput(listadubla);
    //stergeNodNume(&listadubla, "Tudor Arghezi");
    //afisaseListaInceput(listadubla);

    int rezultat = nrCartiTotal(listadubla);
    printf("Nr total de carti %d", rezultat);
    stergereLista(&listadubla);
    afisaseListaInceput(listadubla);

}