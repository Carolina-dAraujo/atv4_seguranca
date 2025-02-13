#include <stdio.h>
#include <string.h>

void func(char *str) {
    char buffer[10];
    strcpy(buffer, str); // Vulnerabilidade: não há verificação do tamanho da entrada
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        func(argv[1]);
        printf("Programa executado com sucesso.\n");
    } else {
        printf("Por favor, forneça uma string como argumento.\n");
    }
    return 0;
}
