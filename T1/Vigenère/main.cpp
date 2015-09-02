/*
    Objetivo: Implementar um trabalho que seja capaz de cifrar e descifrar usando algoritmos
    de c�asar, Transposi��o e Vigen�re.
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

    FILE *arquivo;
    FILE *arquivoResposta;

    printf("Digite 1 para criptografar e 2 para decriptografar:\n");
    scanf("%d",&criptografar);
    fflush(stdin);
    printf("Digite a chave:\n");
    gets(chaveArquivo);

    if(criptografar == 1){
         arquivo = fopen("Vigen�re.txt", "r+");
    }else{
        arquivo = fopen("Criptografado.dat", "rb+");
    }

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

    if(criptografar == 1){
         arquivo = fopen("Vigen�re.txt", "r+");
    }else{
        arquivo = fopen("Criptografado.dat", "rb+");
    }


    if(criptografar == 1){
        arquivoResposta = fopen("Criptografado.dat", "wb+");
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
                    i = (character[0] + chaveArquivo[contador]) % 256;
                    fwrite(&i, 1, 1, arquivoResposta);
                }else{
                    i = (character[0] + 256 - chaveArquivo[contador]) % 256;
                    fwrite(&i, 1, 1, arquivoResposta);
                }
                contador ++;
            }else{
                break;
            }
        }
        fclose(arquivo);
    }else{
        printf("\n\nN�o foi poss�vel abrir o arquivo\n\n");
    }
    fclose(arquivoResposta);

}
