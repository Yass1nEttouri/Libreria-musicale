#include <stdlib.h>
#include <stdio.h>
#include "libreria_musicale.h"

int main(){

    intro();

    int scelta;
    char title[30];
    canzone* libreria;
    unsigned int currentSize = 0;
    char file[40];
    libreria = (canzone *)malloc(CAPACITY * sizeof(canzone));
    if(libreria == NULL){
        printf("Errore: allocazione liibreria fallita.\n");
        return -1;
    }

    //init_library(libreria, currentSize, "", "", "", 0.0);

    do{
        printf("\n");
        printf("Scegli un'opzione:");
        scanf("%d",&scelta);

        switch(scelta){
            case 1:
                print_songs(libreria, currentSize);
            break;

            case 2:
                printf("\n");
                printf("Inserisci il titolo del brano da cercare:");
                scanf("%29s",title);
                if(find_song(libreria, currentSize, title) == -1)
                    printf("Brano non presente all'interno dell'album.\n");
                else
                    printf("Brano presente all'interno dell'album.\n");
            break;

            case 3:
                printf("\n");
                if(add_new_song(libreria, &currentSize) != NULL)
                    printf("Brano aggiunto con successo.\n");
                else
                    printf("Errore: il brano non e' stato aggiunto all'album.\n");
            break;

            case 4:
                printf("\n");
                printf("Inserisci il titolo del brano da eliminare:");
                scanf("%29s",title);
                if(delete_song(libreria, &currentSize, title) != NULL)
                    printf("Brano eliminato con successo.\n");
                else    
                    printf("Errore: brano non eliminato.\n");
            break;

            case 5:
                printf("\n");
                printf("Inserisci il nome del file dal quale importare la libreria\n");
                scanf("%39s",file);
                if(import_library(libreria, &currentSize, file))
                    printf("Libreria importata con successo da '%s'.\n",file);
                else
                    printf("Errore: libreria non importata.");
            break;

            case 6:
                printf("\n");
                printf("Inserisci il nome del file nel quale esportare la libreria\n");
                scanf("%39s",file);
                if(export_library(libreria, currentSize, file))
                    printf("Libreria esportata con successo in '%s'.\n",file);
                else
                    printf("Errore: libreria non esportata.");
            break;

            case 7:
                printf("\n");
                printf("Inserisci il titolo del brano da valutare:");
                scanf("%29s",title);
                if(rate_song(libreria, currentSize, title) != NULL)
                    printf("Brano valutato con successo\n");
                else    
                    printf("Errore: il brano non è stato valutato\n");
            break;

            default:
                printf("...\n");
            break;
        }
    }while(scelta != 8);
    free(libreria);
    printf("Uscita dal programma...\n");
    printf("Memoria liberata.\n");

    return 0;
}
