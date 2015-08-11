/*
    Objetivo: Implementar um trabalho que seja capaz de cifrar e descifrar usando algoritmos
    de céasar, Transposição e Vigenère.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define T 300

int main()
{
    int criptografar = 0, i, tamanho = 0, contador = 0, controlChar = 0, numCaracteres = 0;

    char character[1], chaveArquivo[T];

    for(i = 0; i < T; i++){
        chaveArquivo[i] = '\0';
    }

    FILE *arquivo = fopen("Vigenère.txt", "r+");
    FILE *arquivoResposta;

    printf("Digite 1 para criptografar e 2 para decriptografar:\n");
    scanf("%d",&criptografar);
    fflush(stdin);
    printf("Digite a chave:\n");
    gets(chaveArquivo);

    for(i = 0; i < T; i++){
        if (chaveArquivo[i] != '\0'){
            tamanho ++;
        }
    }

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
    arquivo = fopen("Vigenère.txt", "r+");


    if(criptografar == 1){
        arquivoResposta = fopen("Criptografado.txt", "w+");
    }else
    {
        arquivoResposta = fopen("Descriptografado.txt", "w+");
    }

    if(arquivo != NULL){
        while(!feof(arquivo)){
            controlChar ++;
            if(contador == tamanho){
                contador = 0;
            }
            if(controlChar <= numCaracteres){
                fread(character,sizeof(character),1,arquivo);
                if(criptografar == 1){
                    fprintf(arquivoResposta, "%c", (character[0] + chaveArquivo[contador]) % 256);
                }else{
                    fprintf(arquivoResposta, "%c", (character[0] + 256 - chaveArquivo[contador]) % 256);
                }
                contador ++;
            }else{
                break;
            }
        }
        fclose(arquivo);
    }else{
        printf("\n\nNão foi possível abrir o arquivo\n\n");
    }
    fclose(arquivoResposta);

}
