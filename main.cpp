#include <iostream>
#include <math.h>
using namespace std;

/*

    PRUEBA DE MEDIAS

    Consiste en determinar el promedio de los n numeros que contiene el conjunto r[i], mediante
    la sig ecuacion:

        r' = (1/n) * sumatoria(r[i]) donde i=1 hasta n

    una de las propiedades del conjunto r[i
    es que el valor esperado sea igual a 0.5. La prueba que busca determinar lo
    anterior es la llamada prueba de medias, en la cual se plantean las siguientes hipotesis


    la prueba de medias consiste en determinar el promedio de los N numeros que contienen el
    conjunto RI mediante la sig ecuacion:

    r' = (1 / N) SUMATORIA(i=1, hasta n, donde r[i]

    si el valor de r festada (r') se encuentra entre los limites de aceptacion, se concluye que no se puede
    rechazar el conjunto r[i] tiene un valor esperado de 0.5 con un nivel de aceptacion de 1 - sigma (Z); en
    caso contrario se rechazan los conjuntos r[i] tiene un valor de 0.5.

    Para el calculo de los limites de aceptacion se utiliza el estadistico Z en el subindice Z / 2, el cual
    se determina por medio de la tabla de distribucion normal estandar. Ejemplo:

    Considere los 40 numeros del conjunto r[i] que son los siguientes: determine si tienen un valor esperado de 0.5 con
    un nivel de aceptacion del 95%

*/

int main()
{
    cout << "introducir la cantidad de digitos a probar << endl;
    int n;
    // cantidad de numeros en el conjunto == n
    cin >> n;

    double r[n];
    double suma;
    for(i=0; i < n; i++){
        cout << "introduzca el " << n << "numero";}
        cin >> r[i];
        suma = suma + r[i];
    }
    r_negada = (1/n) * suma;

    double Ll = (1/2)

    return 0;
}
