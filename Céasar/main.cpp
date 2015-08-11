/*
    Objetivo: Implementar um trabalho que seja capaz de cifrar e descifrar usando algoritmos
    de céasar, Transposição e Vigenère.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int criptografar = 0, chave, i, numCaracteres = 0, contador = 0;
    char character[1];

    FILE *arquivo = fopen("Céasar.txt", "r+");
    FILE *arquivoResposta;

    printf("Digite 1 para criptografar e 2 para decriptografar\n");
    scanf("%d",&criptografar);

    printf("Digite a chave\n");
    scanf("%d",&chave);

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
    arquivo = fopen("Céasar.txt", "r+");

    if(criptografar == 1){
        arquivoResposta = fopen("Criptografado.txt", "w+");
    }else
    {
        arquivoResposta = fopen("Descriptografado.txt", "w+");
    }

    if(arquivo != NULL){
        while(!feof(arquivo)){
            if(contador < numCaracteres){
                fread(character,sizeof(character),1,arquivo);
                if(criptografar == 1){
                    i = (character[0] + chave) % 256;
                    fprintf(arquivoResposta,"%c",i);
                }else{
                    i = (character[0] + 256 - chave) % 256;
                    fprintf(arquivoResposta,"%c",i);
                }
                contador++;
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



/*

int main()
{
    int criptografar = 0, chave, i;
    char character[1];

    FILE *arquivo = fopen("Céasar.txt", "r+");
    FILE *arquivoResposta;

    printf("Digite 1 para criptografar e 2 para decriptografar\n");
    scanf("%d",&criptografar);

    printf("Digite a chave\n");
    scanf("%d",&chave);


    if(criptografar == 1){
        arquivoResposta = fopen("Criptografado.txt", "w+");
    }else
    {
        arquivoResposta = fopen("Descriptografado.txt", "w+");
    }

    if(arquivo != NULL){
        while(!feof(arquivo)){
            character[0] = '\0';
            fread(character,sizeof(character),1,arquivo);
            if(criptografar == 1){
                if(character[0] != '\0'){
                    i = (character[0] + chave) % 256;
                    fprintf(arquivoResposta,"%c",i);
                }
            }else{
                if(character[0] != '\0'){
                    i = (character[0] + 256 - chave) % 256;
                    fprintf(arquivoResposta,"%c",i);
                }
            }
        }
        fclose(arquivo);
    }else{
        printf("\n\nNão foi possível abrir o arquivo\n\n");
    }
    fclose(arquivoResposta);
}
*/
