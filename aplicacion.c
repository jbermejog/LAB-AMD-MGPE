
/* Laboratorio álgebra y matemática discreta:
* Implementación del método de eliminación gaussiana por el método de pivotaje parcial escalado
* Author: Javier Bermejo
* Licencia: GNU : https://github.com/jbermejog/MGPE/blob/main/LICENSE
* Creado para el trabajo de laboratorio UNIR 2023
* Documentación y usos 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    float A[10][10];          /* Matriz inicial */
    float B[20], C[20];       /* Vector auxiliar intercambios filas */
    int i, j, k, n, w, s;     /* Variables de índices */
    int t = 0, rep_count = 0; /* Usadas para contadores */
    float q = 0;              /* Resultado division */
    float resul_line = 0;     /* valor de los resultados de las divisiones de orden fila */

    /* Muestra las restricciones y solicita el orden de la matriz */
    printf("\nImplementación del método de eliminación guassiana por el método del pivotaje parcial escalado.\n");
    printf("Restricciones a cumplir por la matriz de entrada:\n");
    printf("- La matriz debe ser rango mínimo 2 y máximo 10.\n");
    printf("- Los valores deben estar entre -100 y 100.\n");
    printf("- No introducir filas que contengan los mismos valores.\n");
    printf("- No introducir filas que sean combinaciones lineales de otras.\n");
    printf("\nIntroduce el orden de la matriz (ejemplo 3): ");
    scanf("%d", &n);

    /* Validamos límites orden de la matriz*/
    if (n <= 1 || n > 10)
    {
        printf("\nRestricción incumplida, el orden de la matriz debe estar entre 2 y 10.\n Otro día será, Bye, Bye ...\n\n");
        return -1;
    }

    /* Bucle en el que solicitamos los valores de la matriz */
    printf("Introduce los elementos de la matriz fila por fila, tal y como se indica:\n\n");
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= (n); j++)
        {
            printf("Valor para A(%d,%d): ", i, j);
            scanf("%f", &A[i][j]);
            if (fabs(A[i][j]) > 100.0)
            {
                printf("\nRestricción incumplida, el valor para los elementos deben estar entre -100 y 100, otro día será. Bye, Bye ...\n\n");
                return -1;
            }
        }
    }

    /* Verificamos que no se repite el mismo valor en toda la fila */
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j < n; j++)
        {
            /* verificamos si son iguales y aumentamos variable contador de repetidos */
            if (A[i][j] == A[i][j + 1])
            {
                rep_count++;
            }
            /* Mostramos error de restriccion*/
            if (rep_count == n - 1)
            {
                printf("\nRestricción incumplida, los valores de los elemento de la fila no pueden ser iguales. Otro día será. Bye, Bye ...\n\n");
                return -1;
            }
        }
        /* reset de la variable repeticiones para la siguiente fila */
        rep_count = 0;
    }

    /* Mostramos la matriz introducida */
    printf("\n La matriz introducida es: \n");
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            /* Mostramos los elementos de ese par con 2 decimales */
            printf("%.2f     ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    /* Bucle para las diagonales y verificar valor absoluto mayor*/
    for (i = 1; i < n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            /* Cuando los valores de i y j son iguales es una diagonal */
            if (i == j)
            {
                /* Bucle en cada pivote hace ordanamiento de filas y calculo 0*/
                for (s = i + 1; s <= n; s++)
                {
                    /* Verificamos si el valor es mayor */
                    if (fabs(A[s][j]) > fabs(A[i][j]))
                    {
                        for (w = 1; w <= n; w++)
                        /* Guardamos en vectores auxiliares */
                        {
                            B[w] = A[s][w]; /* fila mayor */
                            C[w] = A[i][w]; /* fila menor */
                        }
                        /* intercambiamos posiciones de las filas */
                        for (w = 1; w <= n; w++)
                        {
                            A[i][w] = B[w]; /* Guardamos la fila mayor */
                            A[s][w] = C[w]; /* Guardamos la fila menor */
                        }
                    }
                }
                // /* Evaluamos el caso de digagonal sea 0 con precision visto en clase para el error, no se puede resolver */
                // if (A[i][j] < 0.001 && A[i][j] >= 0)
                // {
                //     printf("La matriz no se puede resover.\nTodos los valores posibles para los pivotes son 0 para la posición A(%i,%i).\n Otro día será, Bye, Bye ...\n\n", i, j);
                //     return -1;
                // }
                /* Si el valor del pivote es correcto, se realiza el calculo para la triangulacion */
                for (s = i + 1; s <= n; s++)
                {
                    /* Calculamos el valor de q fijo para hacer 0 los valores de las columnas inferiores */
                    q = A[s][j] / A[i][j];
                    for (k = 1; k <= n; k++)
                    {
                        /* Restamos a la fila el resultado obtenido por el valor del pivote */
                        A[s][k] = A[s][k] - q * A[i][k];
                    }
                }
            }
        }
    }

    /*  Evaluamos si la ultima posicion de la diagonal es 0, en ese caro la solucion no es valida */
    /* Posibilidades: se ha introducido ese valor para esa posición o hay filas dependientes, mostramos error */
    if (A[n][n] < 0.001 && A[n][n] >= 0)
    {
        t = 0;
        for (j = 1; j <= n; j++)
        {
            /* recorremos última fila */
            if (A[n][j] == 0)
            {
                t++;
            }
        }
        /* Mostramos error */
        if (t == n)
        {
            printf("ERROR: La matriz no se puede resolver.\n Los valores de la última fila son 0, verifica la dependencia de filas, otro día será, Bye, Bye ...\n\n");
            return -1;
        }
        else
        {
            printf("ERROR: La matriz no se puede resolver.\n El valor de la última diagonal es 0, otro día será, Bye, Bye ...\n\n");
            return -1;
        }
    }

    /* Mostramos la matriz obtenida sin reducir como se pide*/
    printf("\n La matriz obtenida sin reducir es: \n");
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            printf("%.2f     ", A[i][j]);
        }
        printf("\n\n");
    }
    return 0;
}