#pragma warning(disable:4996)
#include<stdio.h>
#include<malloc.h>

typedef struct {
	int id;
	int nrMedii;
	float* medii;
}Elev;

typedef struct {
	Elev info;
	struct Nod* st, * dr;
}Nod;

void inserareArbore(Nod** radacina, Elev e) {
	if ((*radacina) == NULL) {
		if ((*radacina)->info.id > e.id) {
			inserareArbore(&((*radacina)->st), e);
		}
		else {
			inserareArbore(&((*radacina)->dr), e);
		}
	}
	else
	{
		Nod* nod = (Nod*)malloc(sizeof(Nod));
		nod->info = e;
		nod->st = NULL;
		nod->dr = NULL;
		*radacina = nod;
	}
}
Elev citireElev(FILE*f) {
	Elev e ;
	fscanf(f, "%d", &e.id);
	fscanf(f, "%d", &e.nrMedii);
	e.medii = (float*)malloc(sizeof(float)* e.nrMedii);
	for (int i = 0; i < e.nrMedii; i++) {
		fscanf(f, "%f", &e.medii[i]);
	}
	return e;
}


Nod* citireFisier(char* numeFisier) {
	Nod* arbore = NULL;
	if (numeFisier) {
		FILE* f = fopen(numeFisier, "r");
		int nrElevi;
		fscanf(f, "%d", &nrElevi);
		for (int i = 0; i < nrElevi; i++) {
			Elev e = citireElev(f);
			inserareArbore(&arbore, e);
		}
		fclose(f);
	}
	else {
		return NULL;
	}
	
	return arbore;
}

void afisareElev(Elev e) {
	printf("Elevul cu id-ul *d are mediile\n", e.id);
	for (int i = 0; i < e.nrMedii; i++) {
		printf("%5.2f", e.medii[i]);
	}
	printf("\n");
}
void afisareInOrder(Nod* arbore) {
	if (arbore != NULL) {
		afisareInOrder(arbore->st);
		afisareElev(arbore->info);
		afisareInOrder(arbore->dr);
	}
}
float calculeazaMedieElev(Elev e) {
	if (e.nrMedii != 0) {
		float suma = 0;
		for (int i = 0; i < e.nrMedii; i++) {
			suma += e.medii[i];
		}
		return suma / e.nrMedii;
	}
	else {
		printf("Elevul nu are medii!");
	}
}

float calculeazaSumaNote(Nod* arbore,int* nrNote) {
	if (arbore != NULL)
	{
		float suma = 0;
		for (int i = 0; i < arbore->info.nrMedii; i++) {
			suma += arbore->info.medii[i];
		}
		float sumas=calculeazaSumaNote(arbore->st, nrNote + arbore->info.nrMedii);
		float sumad=calculeazaSumaNote(arbore->dr, nrNote + arbore->info.nrMedii);
		return suma + sumas + sumad;
		
	}
	else {
		return 0;
	}
}
float calculeazaMedieGenerala(Nod* arbore) {
	float nrNote = 0;
	float suma = calculeazaSumaNote(arbore, &nrNote);
	return suma / nrNote;
}

void main() {
	Nod* arbore = citireFisier("elevi.txt");

	afisareInOrder(arbore);

}