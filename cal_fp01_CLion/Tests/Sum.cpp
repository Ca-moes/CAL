/*
 * Sum.cpp
 */

#include "Sum.h"

string calcSum(int* sequence, int size)
{
    string output = "";
    int sum[size];
    int s, sIndex;

    // Para percorrer os tamanhos, 1, 2, 3, .. até size
    for (int m = 1; m <= size; ++m) {
        // para assegurar que no segundo if do for abaixo entra na primeira vez
        s = 99999;
        // percorre os indices a analisar desde o inicial até que cabe com tamanho m
        for (int i = 0; i <= size-m; i++) {
            // se o tamanho for 1, a soma é o valor na sequencia
            if (m == 1)
                sum[i] = sequence[i];
            else{
                // pega na soma que guardou para cada indice e adicona o valor do tamanho que está a considerar
                // ex, para m=3 e i=0
                // em sum[0] já tem o valor de sequence [0] + sequence[1] e adiciona sequence[2 (0+3-1)]
                sum[i] = sum[i] + sequence[i + m - 1];
            }
            // se o valor da soma for um simo (caso haja mais do que uma opção retorna a primeira por causa de ser < e nao <=)
            if (sum[i] < s) {
                // o valor da soma é guardado em s/ o valor do index é quardado em sIndex
                s = sum[i];
                sIndex = i;
            }
        }
        output += to_string(sum[sIndex]) + "," + to_string(sIndex) + ";";
    }

	return output;
}

