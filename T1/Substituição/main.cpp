/*
    Objetivo: Implementar um trabalho que seja capaz de cifrar e descifrar usando algoritmos
    de céasar, Transposição e Vigenère.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(){
    char letras[256], letrasAux[256], chave[256], character[1];
    int i = 0, j = 0, indiceRand,cont = 0, criptografar = 0, numCaracteres = 0, contador = 0;;

    /* initialize random seed: */
    srand (time(NULL));

    FILE *arquivo;
    FILE *arquivoResposta;
    FILE *arquivoChave;

    printf("Digite 1 para criptografar e 2 para decriptografar\n");
    scanf("%d",&criptografar);

    for(i = 0 ; i < 256; i++){
        letrasAux[i] = i;
        letras[i] = i;
         //chave[i] = i;
    }

    if(criptografar == 1){
        for(j = 255; j >= 0; j--){
            if(j == 0){
                indiceRand = 0;
            } else{
                indiceRand = rand() %j;
            }

            chave[cont] = letrasAux[indiceRand];  //Gravar na posição do caracter o valor do caracter.
            letrasAux[indiceRand] = letrasAux[j];
            cont ++;
        }
        arquivoChave = fopen("Arquivo Chave.dat", "wb+");
        j = 0;

        for(j = 0; j <= 255; j++){
            i = chave[j];
            fwrite(&i,1, 1, arquivoChave);
        }
    }else{
        arquivoChave = fopen("Arquivo Chave.dat", "rb+");
        i = 0;
        if(arquivo != NULL){
            while(!feof(arquivoChave)){
                fread(character,sizeof(character),1,arquivoChave);
                if(i <= 255){
                    chave[i] = character[0];
                    i++;
                }
            }
        }
    }

    i = 0;
    if(criptografar == 1){
        arquivo = fopen("Substituição.txt", "r+");
    }else{
        arquivo = fopen("Criptografado.dat", "rb+");
    }
    i = 0;
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
         arquivo = fopen("Substituição.txt", "r+");
         arquivoResposta = fopen("Criptografado.dat", "wb+");
    }else{
        arquivo = fopen("Criptografado.dat", "rb+");
        arquivoResposta = fopen("Descriptografado.txt", "w+");
    }

    if(arquivo != NULL){
        while(!feof(arquivo)){
            if(contador < numCaracteres){
                fread(character,sizeof(character),1,arquivo);
                if(criptografar == 1){
                    i = chave[character[0]];
                }else{

                    for(j = 0; j <= 255; j++){
                        if(chave[j] == character[0]){
                            i = letras[j];
                        }
                    }
                }

                fwrite(&i,1, 1, arquivoResposta);
                contador++;
            }else{
                break;
            }
        }
        fclose(arquivo);
    }else{
        printf("\n\nNão foi possível abrir o arquivo\n\n");
    }
    fclose(arquivoChave);
}

