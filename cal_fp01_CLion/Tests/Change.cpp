/*
 * Change.cpp
 */

#include "Change.h"

/* ALINEA C
 *  v   i   |   k           0   1   2   3   4   5   6   7   8   9
 *          |
 *  0   0   |   minCoins    0   0   0   0   0   0   0   0   0   0
 *          |   lastCoin    0   0   0   0   0   0   0   0   0   0
 *          |
 *  1   1   |   minCoins    0   1   2   3   4   5   6   7   8   9
 *          |   lastCoin    0   1   1   1   1   1   1   1   1   1
 *          |
 *  2   2   |   minCoins    0   1   1   2   2   3   3   4   4   5
 *          |   lastCoin    0   1   2   1   2   1   2   1   2   1
 *          |
 *  5   3   |   minCoins    0   1   1   2   2   1   2   2   3   3
 *          |   lastCoin    0   1   2   1   2   5   1   2   1   2
 */

string calcChange(int m, int numCoins, int *coinValues)
{
    if (m == 0)
        return "";

    int minCoins[m + 1];  // quantidade de moedas usadas
    int lastCoin[m + 1];  // ultima moeda adicionada

    fill_n(minCoins, m+1, 0);
    fill_n(lastCoin, m+1, 0);

    // percorre quantas moedas é para usar, usando 1, 2, 3...
    for (int i = 1; i <= numCoins; i++ ) {
        // montante a ter em consideração desde o valor da moeda até ao valor do montante requeridp
        for (int k = coinValues[i-1]; k <= m; k++) {
            // ...==0 quando compara com i=1 para puder adicionar a 1ª moeda
            // se a quant. moedas usadas no montante a ter em conta for maior que
            //      quant. moedas usadas com o montante atual menos o valor da moeda maior
            // OU SEJA se ao adicionar a moeda nova o numero minimo de moedas diminui
            if (minCoins[k] == 0 || 1 + minCoins[k - coinValues[i-1]] < minCoins[k]) {
                //atualiza o numero minimo de moedas: passa a ser 1 <- a moeda adicionada +
                //                                              o numero minimo de moedas do montante tirando o valor da moeda considerada
                minCoins[k] = 1 + minCoins[k - coinValues[i-1]];
                //atualiza também a ultima moeda para ser a moeda de maior valor
                lastCoin[k] = coinValues[i - 1];
            }
            // não entra no if, a moeda não serve, então não mudam os arrays
        }
    }

    string output = "";
    int temp = m;

    if (minCoins[m] == 0)
        return "-";

    for (int i = 0; i < minCoins[m]; i++) {
        output += to_string(lastCoin[temp]) + ";";
        temp -= lastCoin[temp];
    }

    return output;
}


