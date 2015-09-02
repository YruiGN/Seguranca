/*
    Objetivo: Implementar um trabalho que seja capaz de descifrar usando algoritmos
    de céasar, Transposição e Vigenère.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int achou = 0;

int Dceasar(char nomeArquivoCrip[100], char nomeArquivoDescrip[100]);
int Dvigener(char nomeArquivoCrip[100], char nomeArquivoDescrip[100]);
int Dsubstituicao(char nomeArquivoCrip[100], char nomeArquivoDescrip[100]);
int Dtransposicao(char nomeArquivoCrip[100], char nomeArquivoDescrip[100], double numCaracteres, int chave, char *texto);

int main()
{
    char nomeArquivoCrip[100], nomeArquivoDescrip[100], character[1], *texto, *textoDescrip;
    int i = 1, j = 0, retorno, caracterInt, parada, y_n = 0;
    double numCaracteres = 0;

    FILE *arquivoDescrip;

    printf("Digite o nome do arquivo descriptografado:\n");
    gets(nomeArquivoDescrip);

    printf("Digite o nome do arquivo criptografado:\n");
    gets(nomeArquivoCrip);

    Dceasar(nomeArquivoCrip, nomeArquivoDescrip);
    if(achou == 0){
        Dsubstituicao(nomeArquivoCrip, nomeArquivoDescrip);
    }

    if(achou == 0){
        arquivoDescrip = fopen(nomeArquivoDescrip, "rb");

        if(arquivoDescrip != NULL){
            while(!feof(arquivoDescrip)){
                character[0] = '\0';
                fread(character,1,1,arquivoDescrip);
                if(character[0] != '\0'){
                    numCaracteres ++;
                }
            }
        }else{
            printf("\nArquivo nao encontrado\n");
            system("pause");
        }
        fclose(arquivoDescrip);

        texto        = (char*) malloc((numCaracteres) * sizeof(char));
        textoDescrip = (char*) malloc((numCaracteres) * sizeof(char));

        arquivoDescrip = fopen(nomeArquivoDescrip, "rb");

        i = 0;
        if(arquivoDescrip != NULL){
             while(!feof(arquivoDescrip) ){
                textoDescrip[0] = '\0';
                fread(textoDescrip,sizeof(char),1,arquivoDescrip);

                if(textoDescrip[0] != '\0'){
                    caracterInt = (textoDescrip[0] + 256) % 256;
                    texto[i] = caracterInt;
                    i++;
                }
             }
        }else{
            printf("\nArquivo nao encontrado\n");
        }

        fclose(arquivoDescrip);

        parada = 100;
        y_n    = 0;
        for(j = 2; j <= numCaracteres; j++){
            if(j < parada){
                retorno = Dtransposicao(nomeArquivoCrip, nomeArquivoDescrip, numCaracteres, j, texto);
            }
            else{
                printf("A chave esta em %d",parada);
                printf(" deseja continuar por mais %d?[1(sim)/0(nao)]\n",parada);
                scanf("%d",&y_n);
                if(y_n == 1){
                    parada += parada;
                }
                else{
                    break;
                }
            }
            if(retorno == 1){
                break;
            }
        }
    }

    if(achou == 0){
        printf("\nNao e transposicao.\n");
        Dvigener(nomeArquivoCrip, nomeArquivoDescrip);
    }
    return 0;
}

int Dceasar(char nomeArquivoCrip[100], char nomeArquivoDescrip[100]){
    char characterCrip[1], characterDescrip[1];
    int chaveAnterior = 0, chaveAtual = 0, controleCaracter = 0;

    FILE *arquivoCrip;
    FILE *arquivoDescrip;

    arquivoCrip = fopen(nomeArquivoCrip, "rb");
    arquivoDescrip = fopen(nomeArquivoDescrip, "rb");

    if(arquivoCrip != NULL && arquivoDescrip != NULL){
        while(!feof(arquivoCrip) && !feof(arquivoDescrip)){
            characterCrip[0] = '\0';
            characterDescrip[0] = '\0';
            fread(characterCrip,sizeof(characterCrip),1,arquivoCrip);
            fread(characterDescrip,sizeof(characterDescrip),1,arquivoDescrip);

            chaveAtual = (characterCrip[0] - characterDescrip[0] + 256) % 256;

            if(characterCrip[0] != '\0' || characterDescrip[0] != '\0'){
                if(chaveAnterior != 0 || controleCaracter != 0){
                    if(chaveAtual != chaveAnterior){
                        printf("Nao e Ceasar\n");
                        fclose(arquivoCrip);
                        fclose(arquivoDescrip);
                        return 0;
                    }
                }else{
                    chaveAnterior = chaveAtual;
                    controleCaracter++;
                }
            }
        }
    }else{
        printf("Nao foi possivel abrir o arquivo");
        return 0;
    }
    fclose(arquivoCrip);
    fclose(arquivoDescrip);
    printf("E Ceasar UHUU, chave %d\n", chaveAnterior);
    achou = 1;
    return 0;
}

int Dsubstituicao(char nomeArquivoCrip[100], char nomeArquivoDescrip[100]){
    char characterCrip[1], characterDescrip[1];
    int i = 0, characterCripInt = 0, characterDescripInt = 0, chave[256];

    FILE *arquivoCrip;
    FILE *arquivoDescrip;

    arquivoCrip = fopen(nomeArquivoCrip, "rb");
    arquivoDescrip = fopen(nomeArquivoDescrip, "rb");

    for(i = 0 ; i < 256; i++){
        chave[i] = '\0';
    }

    i = 0;
    if(arquivoCrip != NULL && arquivoDescrip != NULL){
        while(!feof(arquivoCrip) || !feof(arquivoDescrip)){
            if(feof(arquivoCrip)){
                fclose(arquivoCrip);
                fclose(arquivoDescrip);
                printf("Nao e Substituicao. Arquivos com tamanhos diferentes!");
                return 0;
            }
            if(feof(arquivoDescrip)){
                fclose(arquivoCrip);
                fclose(arquivoDescrip);
                printf("Nao e Substituicao. Arquivos com tamanhos diferentes!");
                return 0;
            }
            i++;
            characterCrip[0] = '\0';
            characterDescrip[0] = '\0';
            fread(characterCrip,sizeof(characterCrip),1,arquivoCrip);
            fread(characterDescrip,sizeof(characterDescrip),1,arquivoDescrip);
            characterCripInt = (characterCrip[0] + 256) % 256;
            characterDescripInt = (characterDescrip[0] + 256) % 256;

            if(characterCrip[0] != '\0' || characterDescrip[0] != '\0'){
                if(chave[characterCripInt] == '\0'){
                    chave[characterCripInt] = characterDescripInt;
                }else{
                    if(chave[characterCripInt] != characterDescripInt){
                        fclose(arquivoCrip);
                        fclose(arquivoDescrip);
                        printf("Nao e Substituicao caracteres repetidos na chave!\n");
                        return 0;
                    }
                }
            }
        }
    }
    else{
        printf("Nao foi possivel abrir o arquivo");
        return 0;
    }
    fclose(arquivoCrip);
    fclose(arquivoDescrip);
    printf("E substituicao!");
    achou = 1;
    return 0;
}

int Dtransposicao(char nomeArquivoCrip[100], char nomeArquivoDescrip[100], double numCaracteres, int chave, char *texto){
    char *textoCrip;
    int i = 0, numLinhas = 0, linha = 0, coluna = 0, characterCripInt = 0;
    textoCrip    = (char*) malloc((numCaracteres) * sizeof(char));

    if(chave == 0){
        chave = 1;
    }
    numLinhas = ceil(numCaracteres/chave);
    char matrizCrip[1][chave][numLinhas];

    FILE *arquivoCrip;
    //FILE *arquivoFinal;

    arquivoCrip = fopen(nomeArquivoCrip, "rb");
    //arquivoFinal = fopen("Final.dat","wb+");
    if(arquivoCrip != NULL){
         while(!feof(arquivoCrip) ){
            for(linha = 0; linha < chave; linha ++){
                for(coluna = 0; coluna < numLinhas; coluna++){
                    textoCrip[0] = '\0';
                    fread(textoCrip,sizeof(char),1,arquivoCrip);
                    if(textoCrip[0] != '\0'){
                        characterCripInt = (textoCrip[0] + 256) % 256;
                        matrizCrip[0][linha][coluna] = characterCripInt;
                        i++;
                    }
                }
            }
         }
    }else{
        printf("Nao foi possivel abrir o arquivo");
        return 0;
    }

    i = 0;
    for(coluna = 0; coluna < numLinhas; coluna++){
        for(linha = 0; linha < chave; linha ++){
            if(i < numCaracteres){
                if(texto[i] == matrizCrip[0][linha][coluna]){
                    //fwrite(&matrizCrip[0][linha][coluna],sizeof(char),1,arquivoFinal);
                    i++;
                }
                else{
                    free(textoCrip);
                    //fclose(arquivoFinal);
                    fclose(arquivoCrip);
                    return 0;
                }
            }
        }
    }

    printf("achou, Transposicao chave: %d\n", chave);
    achou = 1;
    //fclose(arquivoFinal);
    fclose(arquivoCrip);
    free(textoCrip);
    return 1;
}


int Dvigener(char nomeArquivoCrip[100], char nomeArquivoDescrip[100]){
    char characterCrip[1], characterDescrip[1];
    int chaveAtual = 0;

    FILE *arquivoCrip;
    FILE *arquivoDescrip;
    FILE *arquivoFinal;

    arquivoCrip = fopen(nomeArquivoCrip, "rb");
    arquivoDescrip = fopen(nomeArquivoDescrip, "rb");

    arquivoFinal = fopen("ArquivoVigenere.dat","wb+");
    if(arquivoCrip != NULL && arquivoDescrip != NULL){
        while(!feof(arquivoCrip) && !feof(arquivoDescrip)){
            characterCrip[0] = '\0';
            characterDescrip[0] = '\0';
            fread(characterCrip,sizeof(characterCrip),1,arquivoCrip);
            fread(characterDescrip,sizeof(characterDescrip),1,arquivoDescrip);

            chaveAtual = (characterCrip[0] - characterDescrip[0] + 256) % 256;

            fwrite(&chaveAtual, 1, 1, arquivoFinal);
        }
    }else{
        printf("Nao foi possivel abrir o arquivo");
        return 0;
    }
    printf("Gerado o arquivo de Vigenere para conferencia!");
    fclose(arquivoCrip);
    fclose(arquivoDescrip);
    return 0;
}

/*
int Dtransposicao(char nomeArquivoCrip[100], char nomeArquivoDescrip[100], double numCaracteres, int chave){
    char characterCrip[1], characterDescrip[1];
    int numLinhas = 0, linha = 0, coluna = 0, characterCripInt, characterDescripInt, cont = 0;

    FILE *arquivoCrip;
    FILE *arquivoDescrip;
    FILE *arquivoFinal;

    if(chave == 0){
        chave = 1;
    }
    numLinhas = ceil(numCaracteres/chave);

    //printf("chave %d, numero de linhas %d, num %f\n",chave, numLinhas,numCaracteres);

    char matrizCrip[1][chave][numLinhas];

    arquivoDescrip = fopen(nomeArquivoDescrip, "rb");

    arquivoCrip = fopen(nomeArquivoCrip, "rb");

    for(linha = 0; linha < chave; linha ++){
        for(coluna = 0; coluna < numLinhas; coluna++){
            matrizCrip[0][linha][coluna] = '\0';
        }
    }

    cont = 0;
    if(arquivoCrip != NULL){
        while(!feof(arquivoCrip) && cont < numCaracteres){
            for(linha = 0; linha < chave; linha ++){
                for(coluna = 0; coluna < numLinhas; coluna++){
                    if(cont != numCaracteres){
                        fread(characterCrip,sizeof(characterCrip),1,arquivoCrip);
                        characterCripInt = characterCrip[0];
                        matrizCrip[0][linha][coluna] = characterCripInt;
                        cont ++;
                    }
                }
            }
        }
    }else{
         printf("\nNao foi possivel abrir o arquivo.");
        return 0;
    }
    fclose(arquivoCrip);

    cont = 0;
    arquivoFinal = fopen("Final.dat", "wb+");
        if(arquivoDescrip != NULL  && cont < numCaracteres){
            while(!feof(arquivoDescrip)){
                for(coluna = 0; coluna < numLinhas; coluna++){
                    for(linha = 0; linha < chave; linha ++){
                        characterDescrip[0] = '\0';
                        fread(characterDescrip,sizeof(characterDescrip),1,arquivoDescrip);
                        if((characterDescrip[0] + 256) % 256 == ((matrizCrip[0][linha][coluna]+ 256) % 256) && characterDescrip[0] != '\0'){
                            fwrite(&matrizCrip[0][linha][coluna], 1, 1, arquivoFinal);
                            cont++;
                        }
                        else{
                            //printf("\nerro: %x\n",matrizCrip[0][linha][coluna]);
                            //printf("\nerro2: %x\n",characterDescrip[0]);
                            return 0;
                        }
                    }
                }
            }
    }
    fclose(arquivoDescrip);
    fclose(arquivoFinal);
    return 1;
}*/

/*

int Dtransposicao(char nomeArquivoCrip[100], char nomeArquivoDescrip[100], double numCaracteres, int chave, char *texto){
    char *textoCrip;
    int i = 0, numLinhas = 0, linha = 0, coluna = 0;
    textoCrip    = (char*) malloc((numCaracteres) * sizeof(char));

    if(chave == 0){
        chave = 1;
    }
    numLinhas = ceil(numCaracteres/chave);
    char matrizCrip[1][chave][numLinhas];

    FILE *arquivoFinal;
    FILE *arquivoCrip;

    arquivoCrip = fopen(nomeArquivoCrip, "r");

    if(arquivoCrip != NULL){
         while(!feof(arquivoCrip) ){
            for(linha = 0; linha < chave; linha ++){
                for(coluna = 0; coluna < numLinhas; coluna++){
                    textoCrip[0] = '\0';
                    fread(textoCrip,sizeof(char),1,arquivoCrip);
                    if(textoCrip[0] != '\0'){
                        matrizCrip[0][linha][coluna] = textoCrip[0];
                        i++;
                    }
                }
            }
         }
    }

    fclose(arquivoCrip);
    i = 0;
    for(coluna = 0; coluna < numLinhas; coluna++){
        for(linha = 0; linha < chave; linha ++){
            if(i < numCaracteres){

                if(texto[i] == matrizCrip[0][linha][coluna]){

                    i++;
                }else{
                    return 0;
                }
            }
        }
    }

    printf("achou, Transposicao chave: %d\n", chave);
    system("pause");
    return 1;
}*/
