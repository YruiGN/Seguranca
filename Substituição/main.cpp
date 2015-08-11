/*
    Objetivo: Implementar um trabalho que seja capaz de cifrar e descifrar usando algoritmos
    de céasar, Transposição e Vigenère.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(){
    char letras[255], letrasAux[255], chave[255], character[1], numCaracteres;
    int i = 0, j = 0, indiceRand,cont = 0, criptografar = 0;

    /* initialize random seed: */
    srand (time(NULL));

    for(i = 0; i < 256; i++){
        letrasAux[i] = '\0';
        letras[i] = '\0';
    }

    for(i = 32 ; i < 256; i++){
        letrasAux[i] = i;
        letras[i] = i;
    }

    for(j = 255; j >= 0; j--){
        if(j == 0){
            indiceRand = 0;
        } else{
            indiceRand = rand() %j;
        }

        chave[cont] = letrasAux[indiceRand];
        letrasAux[indiceRand] = letrasAux[j];
        cont ++;
    }

    FILE *arquivoChave = fopen("Arquivo Chave.txt", "w+");

    //fprintf(arquivoChave,"%s", "Chave do algoritmo de substituição\n\n");
    for(i = 32; i < 256; i ++){
        fprintf(arquivoChave,"%c | %c\n", letras[i], chave[i]);
        printf("%c",letras[i]);
        system("pause");
    }

    fclose(arquivoChave);

    printf("Digite 1 para criptografar e 2 para decriptografar:\n");
    scanf("%d",&criptografar);
    fflush(stdin);

    FILE *arquivo = fopen("Substituição.txt", "r+");
    FILE *arquivoResposta;

    if(arquivo != NULL){
        while(!feof(arquivo)){
            character[0] = '\0';
            fread(character,sizeof(character),1,arquivo);
            if(character[0] != '\0'){
                numCaracteres ++;
            }
        }
    }

    fclose(arquivo);
    arquivo = fopen("Substituição.txt", "r+");

    if(criptografar == 1){
        arquivoResposta = fopen("Criptografado.txt", "w+");
    }else
    {
        arquivoResposta = fopen("Descriptografado.txt", "w+");
    }

}

