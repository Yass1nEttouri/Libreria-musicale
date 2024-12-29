#include "libreria_musicale.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void intro() {
    printf("Benvenuto nella libreria musicale!\n");
    printf("1. Visualizza tutti i brani\n");
    printf("2. Cerca un brano\n");
    printf("3. Aggiungi un brano\n");
    printf("4. Rimuovi un brano\n");
    printf("5. Importa libreria\n");
    printf("6. Esporta libreria\n");
    printf("7. Assegna una valutazione ad una canzone\n");
    printf("8. Esci\n");
}

void print_rate(unsigned int rate) {
    for (int i = 0; i < rate; i++) {
        printf("★");
    }
    for (int i = rate; i < 5; i++) {
        printf("☆"); 
    }
    printf("\n");
}

void print_songs(canzone* libreria, unsigned int size){
    printf("\n");
    if (size == 0){
        printf("Nessun brano presente.\n");
        return;
    }

    printf("Canzoni:\n");
    for (int j=0; j<size; j++){
        printf("%d. %s by %s (%.2f minutes) - %s   ",
        j+1,
        libreria[j].titolo,
        libreria[j].autore,
        libreria[j].durata,
        libreria[j].genere);
        print_rate(libreria[j].valutazione);
    }
}

/* canzone* init_library(canzone* libreria, unsigned int* size, char* title, char* autor, char* genre, float duration){
    
    if (libreria == NULL) return NULL;

    strcpy(libreria[*size].titolo, title);
    strcpy(libreria[*size].autore, autor);
    strcpy(libreria[*size].genere, genre);
    libreria[*size].durata = duration;

    if(size > 0) (*size)++;

    return libreria;
} */

canzone* add_new_song(canzone* libreria,unsigned int* size){

    if(*size > CAPACITY || libreria == NULL) return NULL;

    do{
        if(find_song(libreria, *size, libreria[*size].titolo) != -1)
            printf("Brano già esistente nella libreria,riprova.\n");
        printf("Inserisci dati nuovo brano titolo,autore,durata(in minuti):\n");
        printf("Inserisci titolo:");
        scanf("%29s",libreria[*size].titolo);
        printf("Inserisci autore:");
        scanf("%29s",libreria[*size].autore);
        printf("Inserisci durata(in minuti):");
        scanf("%f",&libreria[*size].durata);
        printf("Inserisci il genere della canzone:");
        scanf("%29s",libreria[*size].genere);
    }while(find_song(libreria, *size, libreria[*size].titolo) != -1);

    (*size)++;
    return libreria;
}

canzone *delete_song(canzone* libreria,unsigned int* size, const char *title){

    if(libreria == NULL) return NULL;

    if(!find_song(libreria, *size, title)) return NULL;

    for (int j = 0; j < (*size)- 1; j++) {
        libreria[j] = libreria[j + 1];
    }
    (*size)--;
    return libreria;
}


int find_song(canzone* libreria, unsigned int size,const char *title){

    if(libreria == NULL) return -1;

    for(int i=0; i<size; i++){
        if(strcmp(libreria[i].titolo,title) == 0) return i;
    }

    return -1;
}


canzone* rate_song(canzone* libreria, unsigned int size, const char *title){

    if(libreria == NULL) return NULL;

    int index = find_song(libreria, size, title);
    if(index == -1) return NULL;

    int value = 1;
    do{
        if((value < 1 || value > 5))
            printf("Valutazione non valida riprova\n");
        printf("Assegna una valutazione alla canzone (1-5):");
        scanf("%d",&libreria[index].valutazione);
        int value = libreria[index].valutazione;
    }while(!(value >= 1 && value<=5));
    
    return libreria;
}

void trim(char* str) {
    char* end;

    // Rimuove spazi iniziali
    while (*str == ' ') str++;

    // Rimuove spazi finali
    end = str + strlen(str) - 1;
    while (end > str && *end == ' ') end--;

    // Aggiunge il terminatore
    *(end + 1) = '\0';
}

bool import_library(canzone* libreria, unsigned int* size, const char* file_name){

    if(libreria == NULL) return false;

    char title[30];
    char autor[30];
    char genre[30];
    int number;
    unsigned int duration;

    FILE *file;
    char pathname[200] = "/home/yassine/Scrivania/Primo-anno/PROG-2/project_libreria_musicale/";
    strcat(pathname, file_name);
    file = fopen(pathname,"r");
    if(file == NULL){
        perror("Errore: apertura del file.\n");
        return false;
    }

    char buffer[500]; // Buffer per una riga intera
    while (*size < CAPACITY && fgets(buffer, sizeof(buffer), file) != NULL) {
        // Parsing della riga
        if (sscanf(buffer, "%*d. %49[^b] by %49[^()] (%f minutes) - %49[^\n]\n",
                   libreria[*size].titolo,
                   libreria[*size].autore,
                   &libreria[*size].durata,
                   libreria[*size].genere) == 4) {
            // Rimuove spazi in eccesso
            trim(libreria[*size].titolo);
            trim(libreria[*size].autore);
            trim(libreria[*size].genere);

            (*size)++;
        } else {
            printf("Errore nella lettura della riga: %s\n", buffer);
        }
    }
/*     while( (*size) < CAPACITY && fscanf(file, "%*d. %49[^b] by %49[^()] (%f minutes) - %29[^\n]\n",
        libreria[*size].titolo, 
        libreria[*size].autore, 
        &libreria[*size].durata, 
        libreria[*size].genere) == 4){
            (*size)++;
    } */
    fclose(file);
    return true;
}

bool export_library(canzone* libreria,unsigned int size, const char* file_name){

    if(libreria == NULL) return false;

    FILE *file;
    char pathname[200] = "/home/yassine/Scrivania/Primo-anno/PROG-2/project_libreria_musicale/";
    strcat(pathname, file_name);
    file = fopen(pathname,"w");
    if(file == NULL){
        perror("Errore: apertura del file.\n");
        return false;
    }

    for (int i = 0; i < size; i++){
        fprintf(file, "%d. %s by %s (%.2f minutes) - %s\n",
        i+1,
        libreria[i].titolo, 
        libreria[i].autore, 
        libreria[i].durata, 
        libreria[i].genere);
    }
    
    fclose(file);
    return true;
}