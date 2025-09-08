#include "libreria_musicale.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void intro() {
    printf("\nAzioni\n");
    printf("1. Visualizza tutti i brani\n");
    printf("2. Cerca un brano\n");
    printf("3. Aggiungi un brano\n");
    printf("4. Rimuovi un brano\n");
    printf("5. Importa libreria\n");
    printf("6. Esporta libreria\n");
    printf("7. Ordina canzoni per:\n");
    printf(" 1-titolo\n 2-autore\n 3-genere\n 4-valutazione(asc o desc)\n 5-durata(asc o desc)\n");
    printf("8. Assegna una valutazione ad una canzone\n");
    printf("9. Esci\n");
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
        scanf("%39s",libreria[*size].titolo);
        printf("Inserisci autore:");
        scanf("%39s",libreria[*size].autore);
        printf("Inserisci durata(in minuti):");
        scanf("%f",&libreria[*size].durata);
        printf("Inserisci il genere della canzone:");
        scanf("%39s",libreria[*size].genere);
    }while(find_song(libreria, *size, libreria[*size].titolo) != -1);

    (*size)++;
    return libreria;
}

canzone *delete_song(canzone* libreria,unsigned int* size, const char* title){

    if(libreria == NULL) return NULL;
    
    int index = find_song(libreria, *size, title); 
    if(index == -1) return libreria;

    for (int j = index; j < (*size) - 1; j++){
        libreria[j] = libreria[j + 1];
    }
    (*size)--;

    canzone* temp = realloc(libreria, (*size) * sizeof(canzone));
    if(temp == NULL || *size == 0) libreria  = temp;

    return libreria;
}


int find_song(canzone* libreria, unsigned int size,const char* title){

    if(libreria == NULL) return -1;

    for(int i=0; i<size; i++){
        if(strcmp(libreria[i].titolo,title) == 0) return i;
    }
    return -1;
}


canzone* rate_song(canzone* libreria, unsigned int size, const char* title){

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
    if (str == NULL || *str == '\0') return; 

    char *start = str;               
    while (*start == ' ') start++;   

    char *end = start + strlen(start) - 1; 
    while (end > start && *end == ' ') end--; 
    *(end + 1) = '\0';              

    memmove(str, start, strlen(start) + 1); 
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

/*     char buffer[500]; 
    while (*size < CAPACITY && fgets(buffer, sizeof(buffer), file) != NULL){
        if (sscanf(buffer, "%*d. %49[^'] by %49[^()] (%f minutes) - %49[^\n]\n",
                   libreria[*size].titolo,
                   libreria[*size].autore,
                   &libreria[*size].durata,
                   libreria[*size].genere) == 4) {
            // removing excessive spaces in strings
            trim(libreria[*size].titolo);
            trim(libreria[*size].autore);
            trim(libreria[*size].genere);

            (*size)++;
        }else
            printf("Errore nella lettura della riga: %s\n", buffer);
    } */
   
    char buffer[500];

    while (*size < CAPACITY && fgets(buffer, sizeof(buffer), file) != NULL) {

        // rimozione \n finale
        buffer[strcspn(buffer, "\n")] = '\0';

        // trovare il primo punto dopo l’indice (es: "1.")
        char *after_number = strchr(buffer, '.');
        if (!after_number) {
            printf("Formato non valido: %s\n", buffer);
            continue;
        }
        after_number += 2; // salta ". " e posizionati all’inizio del titolo

        // trovare " by "
        char *pos_by = strstr(after_number, " by ");
        if (!pos_by) {
            printf("Formato non valido (manca 'by'): %s\n", buffer);
            continue;
        }

        // titolo = da after_number fino a pos_by
        *pos_by = '\0';
        strcpy(libreria[*size].titolo, after_number);

        // dopo "by" c’è l’autore fino a "("
        char *pos_paren = strchr(pos_by + 4, '(');
        if (!pos_paren) {
            printf("Formato non valido (manca '('): %s\n", buffer);
            continue;
        }
        *pos_paren = '\0';
        strcpy(libreria[*size].autore, pos_by + 4);

        // Durata dentro "(X.YY minutes)"
        float durata = 0.0f;
        if (sscanf(pos_paren + 1, "%f minutes)", &durata) != 1) {
            printf("Errore lettura durata: %s\n", buffer);
            continue;
        }
        libreria[*size].durata = durata;

        // Genere dopo il trattino "-"
        char *pos_dash = strchr(pos_paren + 1, '-');
        if (!pos_dash) {
            printf("Formato non valido (manca '-'): %s\n", buffer);
            continue;
        }
        strcpy(libreria[*size].genere, pos_dash + 2); // salta "- "

        //rimozione spazi extra
        trim(libreria[*size].titolo);
        trim(libreria[*size].autore);
        trim(libreria[*size].genere);

        (*size)++;
    }
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
//criterio in inglese 
void sort_library(canzone* libreria, unsigned int size, int criterio, char* asc_desc){
    if (libreria == NULL || size == 0) return;

    for (unsigned int i = 0; i < size - 1; i++) {
        for (unsigned int j = 0; j < size - i - 1; j++) {
            bool swap = false;
            switch (criterio) {

                case 1: // titolo
                    if (strcmp(libreria[j].titolo, libreria[j + 1].titolo) > 0) swap = true;
                    break;

                case 2: // autore
                    if (strcmp(libreria[j].autore, libreria[j + 1].autore) > 0) swap = true;
                    break;

                case 3: // genere
                    if (strcmp(libreria[j].genere, libreria[j + 1].genere) > 0) swap = true;
                    break;

                case 4: // valutazione
                    if(asc_desc == "asc"){
                        if (libreria[j].valutazione > libreria[j + 1].valutazione) swap = true;
                        else swap = false;
                    }else if(asc_desc == "desc"){
                        if (libreria[j].valutazione < libreria[j + 1].valutazione) swap = true;
                        else swap = false;
                    }else{
                        printf("Errore: tipo di ordinamento non valido (opzioni: asc oppure desc)\n");
                        return;
                    }
                    break;

                case 5: // durata
                    if(asc_desc == "asc"){
                        if (libreria[j].durata > libreria[j + 1].durata) swap = true;
                        else swap = false;
                    }else if(asc_desc == "desc"){
                        if (libreria[j].durata < libreria[j + 1].durata) swap = true;
                        else swap = false;
                    }else{
                        printf("Errore: tipo di ordinamento non valido (opzioni: asc oppure desc)\n");
                        return;
                    }
                    break;

                default:
                    printf("Criterio non valido.\n");
                    return;
            }
            if (swap) {
                canzone temp = libreria[j];
                libreria[j] = libreria[j + 1];
                libreria[j + 1] = temp;
            }
        }
    }
}

// Favorite list operations : 

// func add to favorites
// func remove from favorites
// func check presence of a specific song in the list
// func clear the list




