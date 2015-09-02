/*
    Objetivo: Implementar um trabalho que seja capaz de cifrar e descifrar usando algoritmos
    de transposição, Transposição e Vigenère.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int criptografar = 0, chave, i,numLinhas = 0, linha = 0, coluna = 0;
    double numCaracteres =0.0;
    char character[1];

    FILE *arquivo;
    FILE *arquivoResposta;

    printf("Digite 1 para criptografar e 2 para decriptografar:\n");
    scanf("%d",&criptografar);

    printf("Digite a chave:\n");
    scanf("%d",&chave);

    if(criptografar == 1){
         arquivo = fopen("Transposição.txt", "r+");
    }else{
        arquivo = fopen("Criptografado.dat", "rb+");
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

    numLinhas = ceil(numCaracteres/chave);

    printf("chave %d, numero de linhas %d, num %f\n",chave, numLinhas,numCaracteres);


    char matrizCrip[1][numLinhas][chave], matrizDescrip[1][chave][numLinhas];
    fclose(arquivo);

    if(criptografar == 1){
         arquivo = fopen("Transposição.txt", "r+");
    }else{
        arquivo = fopen("Criptografado.dat", "rb+");
    }

    if(arquivo != NULL){
        while(!feof(arquivo)){
            if(criptografar == 1){
                for(linha = 0; linha < numLinhas; linha ++){
                    for(coluna = 0; coluna < chave; coluna++){
                        character[0] = ' ';
                        fread(character,sizeof(character),1,arquivo);
                        matrizCrip[0][linha][coluna] = character[0];
                    }
                }
            }
            else{
                for(linha = 0; linha < chave; linha ++){
                    for(coluna = 0; coluna < numLinhas; coluna++){
                        character[0] = ' ';
                        fread(character,sizeof(character),1,arquivo);
                        matrizDescrip[0][linha][coluna] = character[0];
                    }
                }
            }
             break;
        }
        fclose(arquivo);

        if(criptografar == 1){
            arquivoResposta = fopen("Criptografado.dat", "wb+");
            for(coluna = 0; coluna < chave; coluna++){
                for(linha = 0; linha < numLinhas; linha ++){
                    fwrite(&matrizCrip[0][linha][coluna], 1, 1, arquivoResposta);
                }
            }
        }else
        {
            arquivoResposta = fopen("Descriptografado.txt", "w+");
            for(coluna = 0; coluna < numLinhas; coluna++){
                for(linha = 0; linha < chave; linha ++){
                    fwrite(&matrizDescrip[0][linha][coluna], 1, 1, arquivoResposta);
                }
            }
        }
        fclose(arquivoResposta);

    }else{
        printf("\n\nNão foi possível abrir o arquivo\n\n");
    }
}
