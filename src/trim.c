#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void trim(char* str) {
    if (str == NULL || *str == '\0') return; // Gestione di stringhe NULL o vuote

    char *start = str;               // Punta all'inizio della stringa originale
    while (*start == ' ') start++;   // Avanza oltre gli spazi iniziali

    char *end = start + strlen(start) - 1; // Punta all'ultimo carattere
    while (end > start && *end == ' ') end--; // Torna indietro sugli spazi finali
    *(end + 1) = '\0';               // Aggiungi il terminatore di stringa

    memmove(str, start, strlen(start) + 1); // Sposta la stringa "trimmata" all'inizio
}

int main() {
  char str[] = ("   Hello, World!   ");
  trim(str);
  printf("trim:%s\n",str);
  
  return 0;
}