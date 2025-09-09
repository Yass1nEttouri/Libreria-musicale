#include <stdlib.h>
#include <stdio.h>
#include "libreria_musicale.h"

int main(){

    int scelta;
    char title[30];
    canzone* libreria;
    unsigned int currentSize = 0;
    char file[40];

    libreria = (canzone *)malloc(CAPACITY * sizeof(canzone));
    if(libreria == NULL){
        printf("Errore: allocazione libreria fallita.\n");
        return -1;
    }

    //init_library(libreria, currentSize, "", "", "", 0.0);
    printf("\nBenvenuto nella libreria musicale!\n");
    do{
        intro();
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
                int campo = 0;
                int indiceBrano = 0;
                printf("\n");
                printf("Inserisci l'indice del brano da modificare:");
                scanf("%d",&indiceBrano);
                printf("Inserisci il campo che vorresti modificare(1-5):");
                scanf("%d",&campo);
                if(edit_song_info(libreria, indiceBrano, campo))
                    printf("Informazioni modificate con successo\n");
                else
                    printf("Errore: modifica informazioni canzone fallita.");
            break;
            
            case 6:
                printf("\n");
                printf("Inserisci il nome del file dal quale importare la libreria\n");
                scanf("%39s",file);
                if(import_library(libreria, &currentSize, file))
                    printf("Libreria importata con successo da '%s'.\n",file);
                else
                    printf("Errore: libreria non importata.");
            break;

            case 7:
                printf("\n");
                printf("Inserisci il nome del file nel quale esportare la libreria\n");
                scanf("%39s",file);
                if(export_library(libreria, currentSize, file))
                    printf("Libreria esportata con successo in '%s'.\n",file);
                else
                    printf("Errore: libreria non esportata.");
            break;

            case 8:
                int criterio = 0;
                char ascDesc[4];
                printf("\n");
                printf("Inserisci il criterio di ordinamento(1-5): ");
                scanf("%d",&criterio);
                if(criterio == 4 || criterio == 5){
                    printf("Inserisci tipo ordinamento crescente/decrescente - asc/desc:");
                    scanf("%4s",ascDesc);
                }
                printf("critero:%s\n",ascDesc);
                sort_library(libreria, currentSize, criterio, ascDesc);                   
            break;

            case 9:
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
    }while(scelta != 10);
    free(libreria);
    printf("Uscita dal programma...\n");
    printf("Memoria liberata.\n");

    return 0;
}
