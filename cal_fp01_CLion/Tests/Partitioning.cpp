/*
 * Partioning.cpp
 */

#include "Partitioning.h"


int s_recursive(int n, int k) {
    // formula dada no exercicio
    // S(n,k) = S(n-1,k-1) + k S(n-1,k), se 1 < k < n
    // S(n,k) = 1, se k=1 ou k=n
    return k == 1 || k == n ? 1 : s_recursive(n - 1, k - 1) + k * s_recursive(n - 1, k);
}

int s_dynamic(int n,int k)
{
    int s[k];
    // Initialize the array with 1's
    fill_n(s, k, 1);

    for (int i = 0; i < n - k; i++) {
        for (int j = 1; j < k; j++) {
            // valor atual = valor anterior + valor atual antigo * something
            s[j] = (j + 1) * s[j] + s[j - 1];
        }
    }

    return s[k - 1];
}


int b_recursive(int n)
{
    // formula dada no exercicio
    // 𝐵(𝑛) = ∑_k=1 ^n 𝑆(𝑛, 𝑘)
    int sum = 0;
    for (int k = 1; k <= n ; ++k)
        sum += s_recursive(n, k);
	return sum;
}

int b_dynamic(int n)
{
    int sum = 0;
    for (int k = 1; k <= n; k++)
        sum += s_dynamic(n, k);
    return sum;
}


