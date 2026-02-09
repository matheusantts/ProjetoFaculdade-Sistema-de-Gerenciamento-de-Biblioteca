#include <stdio.h>
#include <stdlib.h>

char nomeCompleto[100];

int main(void) {

    printf("Digite o nome do player:\n");
    scanf("%s", nomeCompleto);
    printf("Nome do player: %s\n", nomeCompleto);

    return 0;
}