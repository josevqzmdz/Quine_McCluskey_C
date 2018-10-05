/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: jose
 *
 * Created on 2 de octubre de 2018, 09:44 PM
 * 
 * https://arxiv.org/ftp/arxiv/papers/1410/1410.1059.pdf
 * 
 */

#include <cstdlib>
#include <stdio.h>
using namespace std;

/*
 * 
 */

int i, j, temp, NumberOfVariable, NumberOfAllMinterm, NumberOfDontCare, NumberOfEPI=0,
        NumberOfRemainingMT, NumberOfRemainingPI, NumberOfPI=0, PotEPINo=0, NumberOfPossibleEPI=1,
        MinimumNo=0, Groupable=1;
int *MintermIndicesDecimal, *MintermIndicesDecimal_DontCare, **Minterm_Binary, ****Column, **PI_Index,
        **EPI_Index, *NumberCounter, *ReducedPIChart_X, **ReducedPIChart_Y, **ReducedPIChart, *For,
        **Potential_EPI, *NoOfPIForEPI;

void DecimalToBinary();
int OneCounter(int *binary, int NumberOfDigit);
int Combination(int n, int ColumnNo, int k);
int IsPowerOfTwo(int n);
int IsDontCare(int MT);
void ShowResult();
void Recursion_For_Loop(int m);

int main(int argc, char** argv) {
    int k, l, m, n, x, y, LogicProbe;
    
    //prepara informacion para el calculo
    
    printf("¿Cuantas variables contienen los minterminos \n?");
    scanf("%d", &NumberOfVariable);
    
    while(NumberOfVariable <= 0){
        printf("el numero de variables debe de ser mayor a 0, por favor intente otra vez: \n\n");
        printf("Por favor proporcione la informacion de la suma de los min terminos. ¡Cuantas variables"
                " contiene?");
        scanf("%d", &NumberOfVariable);
    }
    
    printf("¡Cuantos minterminos (Incluyendo 'los que no importan') contiene? ");
    scanf("%d", &NumberOfAllMinterm);
    
    while(NumberOfAllMinterm > pow(2, NumberOfVariable) || NumberOfAllMinterm <= 0){
        printf("el numero de minterminos no puede ser mayor que 2^%d ni puede ser menor que 1 \n", NumberOfVariable);
        printf("¿Cuantos minterminos (incluyendo 'los que no importan') contiene?\n");
        scanf("%d", &NumberOfAllMinterm);
    }
    
    printf("¿Cuantos minterminos 'que no importan' contiene?\n");
    scanf("%d", &NumberOfDontCare);
    
    while(NumberOfDontCare >= NumberOfAllMinterm || NumberOfDontCare < 0){
        printf("El numero de minterminos que no importan no puede ser mayor que el numero de "
                "todos los minterminos ni puede ser menor que 0. Favor de intentar otra vez. \n");
        printf("¿Cuantos minterminos que no importan hay?\n");
        scanf("%d", &NumberOfDontCare);
    }
    
    // graba los indices decimales representando cada mintermino
    MintermIndicesDecimal = (int *)malloc(NumberOfAllMinterm * sizeof(int));
    
    // graba los decimales representando cada mintermino que no importa
    MintermIndicesDecimal_DontCare = (int *)malloc(NumberOfDontCare * sizeof(int));
    
    for(i = 0; i < NumberOfAllMinterm; i++){
        if(i == 0) printf("Por favor introduzca los indices del primer "
                "mintermino (en modo ascendiente): ");
        
        else if (i == 1) printf("Por favor introduzca los indices del 2nd"
                " mintermino (en modo ascendiente): ");
        
        else if (i == 2) printf("Por favor introduzca los indices del 3er "
                "mintermino (en modo ascendiente)");
        else printf("Por favor introduzca los indices del mintermino %d (en modo"
                " ascendente): ");
        
        scanf("%d", &MintermIndicesDecimal[i]);
        if (i != 0 && MintermIndicesDecimal[i] <= MintermIndicesDecimal[i-1]){
            printf("Los numeros no estan en orden ascendente, por favor introduzca"
                    " todos los decimales otra vez");
            i =- 1;
        }
        else if(MintermIndicesDecimal[i] >= pow(2, NumberOfVariable)){
            printf("\n El numero debe ser menor que %d, por favor re-introduzca "
                    "todos los indices otra vez");
            i =- 1;
        }
    }
    
    if(NumberOfDontCare != 0){
        printf("\n\n ¡Cuales de estos son terminos que no importan?");
        for( i = 0; i < NumberOfDontCare; i++){
            if (i == 0){
                printf("Por favor introduzca el indice decimal del primer (1) mintermino que no importa (en modo ascendiente)\n");
            }
            else if( i == 1){
                printf("Por favor introduzca el indice decimal del segundo (2) mintermino que no importa (en modo ascendiente)\n");
            }
            else if (i == 2){
                printf("Por favor introduzca el indice decimal del tercer (3) mintermino que no importa (en modo ascendiente)\n");
            }
            else{
                printf("Por favor introduzca el indice decimal del mintermino %d que no importa en modo ascendiente: \n", i+1);
                scanf("%d", &MintermIndicesDecimal_DontCare[i]);
                if (i != 0 && MintermIndicesDecimal_DontCare[i] <= MintermIndicesDecimal_DontCare[i - 1]){
                    printf("Los numeros no estan en orden ascendiente, por favor re-introduzca los indices otra vez \n\n");
                    i =- 1;
                }
                else if(MintermIndicesDecimal[i] >= pow(2, NumberOfVariable)){
                    printf("\n El numero debe de ser menor que %d, por favor re-introduzca todos los indices otra vez. \n\n", pow(2, NumberOfVariable));
                    i =- 1;
                }
            }
        }
        Minterm_Binary = (int **)malloc(NumberOfAllMinterm*sizeof(int*));
        for(i=0; i<= NumberOfAllMinterm; i++){
            Minterm_Binary[i] = (int *)malloc((NumberOfVariable+4)*sizeof(int));
        }
        DecimalToBinary();
        for(i=0; i<NumberOfAllMinterm; i++){
            Minterm_Binary[i][NumberOfVariable] = OneCounter(Minterm_Binary[i], NumberOfVariable);
            
            Minterm_Binary[i][NumberOfVariable + 1] = 0;
            // '0' significa que no se ha agrupado, '1' significa que si ha sido agrupado con otros terminos
            
            Minterm_Binary[i][NumberOfVariable + 2] = MintermIndicesDecimal[i];
            // este es el mintermino original
            
            Minterm_Binary[i][NumberOfVariable + 3] = MintermIndicesDecimal[i];
            // estos son todos los minterminos que consisten
        }
        
        Column = (int ****malloc((NumberOfVariable + 1)*sizeof(int**));
        for( i = 0; i < NumberOfVariable + 1; i++){
            for(j = 0; j < NumberOfVariable + 1 - i; j++){
                Column[i][j] = (int**)malloc(Combination(NumberOfVariable, i, j)*sizeof(int*));
                // columna[i][j] contiene todos los terminos con j '1's en su indice binario en la columna (i+1)
                
            }
            
            for(k=0; k < Combination(NumberOfVariable, i, j); k++){
                    Column[i][j]=(int**)malloc(Combination(NumberOfVariable, i, j)*sizeof(int*));
                    for(k=0; k < Combination(NumberOfVariable, i, j); k++){
                        Column[i][j][k] = NULL;
                    // esta column[i][j][k] represents a term with in the jj '1's in their binary indices in the (i+1)th columnn 
                    }
            }      
        }
        
        for(i =0; i < NumberOfVariable+1; i++){
            for(j=0, k = 0; j < NumberOfAllMinterm; j++){
                if(Minterm_Binary[j][NumberOfVariable] == i){
                    Column[0][i][k++] = Minterm_Binary[j];
                    //prepara la primer columna
                }
            }
        }
    }
    
    // performando la agrupacion
    
    for(i = 0; i < NumberOfVariable+1; i++){
        if(Groupable){
            Groupable=0;
            for(j=0; j < NumberOfVariable-i; j++){
                int p, position;
                m=0;
                for(k=0; k < Combination(NumberOfVariable, i, j); k++){
                    if( Column[i][j+1][1] != NULL && Column[i][j+1][1][NumberOfVariable+2+i] > Column[i][j][k][NumberOfVariable+2+i] &&
                            IsPowerOfTwo(Column[i][j+1][1][NumberOfVariable+2+i] - Column[i][j][k][NumberOfVariable+2+i])){
                        LogicProbe = 0 - i;
                        // esta prueba logica se utiliza para comprobar si estos dos
                        // terminos tienen la misma posicion de "-" (representado como "2")
                        for(n=1; n <= i; n++){
                            for(p=1; p <= i; p++){
                                
                                if(Column[i][j+1][1][NumberOfVariable+1+n] == Column[i][j][k][NumberOfVariable+1+p]){
                                    LogicProbe++;
                                }
                                
                                if(LogicProbe==0){
                                   Groupable = 1;
                                   Column[i][j][k][NumberOfVariable+1] = 1;
                                   Column[i][j+1][1][NumberOfVariable+1] = 1;
                                   Column[i+1][j][m] = (int *)malloc((NumberOfVariable+4+i+pow(2, i+1))*sizeof(int));
                                   
                                   for(n=0; n <= NumberOfVariable+1+i; n++){
                                       Column[i+1][j][m] = (int *)malloc((NumberOfVariable+4+i+pow(2,i+1))*sizeof(int));
                                       
                                       for(n = 0; n <= NumberOfVariable+1+i; n++){
                                           Column[i+1][j][m][n] = Column[i][j][k][n];
                                           Column[i+1][j][m][n] = 0;
                                           position = log((Column[i][j+1][1][NumberOfVariable+2+i] - Column[i][j][k][NumberOfVariable+2+i])) / log(2);
                                           
                                           Column[i+1][j][m][NumberOfVariable-1-position] = 2;
                                           Column[i+1][j][m][NumberOfVariable+1] = 0;
                                           Column[i+1][j][m][NumberOfVariable+2+i] = position;
                                           
                                           for(p = 0; p < pow(2,i); p++){
                                               Column[i+1][j][m][NumberOfVariable+4+i+p] = Column[i][j][k][NumberOfVariable+3+i+p];
                                           }
                                           
                                           for(p = pow(2, i); p < pow(2, i+1); p++){
                                               Column[i+1][j][m][NumberOfVariable+4+i+p]=Column[i][j+1][l][NumberOfVariable+3+i+p-(int)pow(2,i)];
                                           }
                                           
                                           m++;
                                           
                                       }
                                   }
                                }
                            }
                        }
                    }
                }
                // numbercounter cuenta cuantas veces ocurre el indice decimal
                NumberCounter = (int *) malloc(pow(2, NumberOfVariable)*sizeof(int));
                for(i = 0; i < pow(2, NumberOfVariable); i++){
                    NumberCounter[i] = 0;
                }
                
                // graba el primer implicante (los duplicados seran eliminados)
                PI_Index = (int **)malloc(NumberOfAllMinterm*sizeof(int*));
                
                for(i = 0; i < NumberOfAllMinterm; i++){
                    
                    PI_Index[i] = (int *)malloc(3*sizeof(int));
                }
                
                for(i = 0; i < NumberOfVariable+1; i++){
                    for(j = 0; j < NumberOfVariable+1-i; j++){
                        for(k = 0; k < Combination(NumberOfVariable, i, j); k++){
                            if(Column[i][j][k] != NULL && Column[i][j][k][NumberOfVariable+1] == 0){
                                LogicProbe = 0 - pow(2, i);
                                // logicprobe se utiliza para comprobar si este PI es un duplicado
                                for(l = k-1; l >= 0; l--){
                                    if(LogicProbe != 0){
                                        LogicProbe = 0 - pow(2, i);
                                        //TODO: pag 17
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    return 0;
}

