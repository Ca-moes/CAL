/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku()
{
	this->initialize();
}

/**
 * Inicia um Sudoku com um conte�do inicial.
 * Lan�a excep��o IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem n�meros repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9])
{
	this->initialize();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (nums[i][j] != 0)
			{
				int n = nums[i][j];
				numbers[i][j] = n;
				lineHasNumber[i][n] = true;
				columnHasNumber[j][n] = true;
				block3x3HasNumber[i / 3][j / 3][n] = true;
				countFilled++;
			}
		}
	}
}

void Sudoku::initialize()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int n = 0; n < 10; n++)
			{
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}
		}
	}

	this->countFilled = 0;
}

/**
 * Obtem o conte�do actual (s� para leitura!).
 */
int** Sudoku::getNumbers()
{
	int** ret = new int*[9];

	for (int i = 0; i < 9; i++)
	{
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++)
			ret[i][a] = numbers[i][a];
	}

	return ret;
}

/**
 * Verifica se o Sudoku j� est� completamente resolvido
 */
bool Sudoku::isComplete()
{
	return countFilled == 9 * 9;
}


/**
 * Resolve o Sudoku.
 * Retorna indica��o de sucesso ou insucesso (sudoku imposs�vel).
 */
bool Sudoku::solve()
{
    return solve(0,0);
}

/**
 * Imprime o Sudoku.
 */
void Sudoku::print()
{
    for (int i = 0; i < 9; i++)
    {
        for (int a = 0; a < 9; a++)
            cout << this->numbers[i][a] << " ";

        cout << endl;
    }
}

bool Sudoku::solve(int i, int j) {
    // se o i passar de 8, passa para a linha seguinte com i=0
    if (i > 8) {
        i = 0;
        j++;
    }

    // Base case - Sudoku Feito
    if (isComplete() ||  j > 8)
        return true;

    // Check if this box is already solved
    if (numbers[i][j] != 0) {
        // ultima posi��o, chegou ao fim do sudoku, retorna true
        if (i == 8 && j == 8)
            return true;
        else
            return solve(i + 1, j);  // resolve a proxima posi��o
    }

    // Estando numa box "0", verifica todos os numeros de 1 a 9 l�
    for (int n = 1; n <= 9; n++) {
        // se o numero n�o estiver na coluna, linha e caixa, marca essa tentativa com checkbox()
        if (!lineHasNumber[i][n] && !columnHasNumber[j][n] && !block3x3HasNumber[i / 3][j / 3][n]) {
            checkBox(i, j, n);
            // tenta resolver a box seguinte, caso consiga, retorna true
            if (solve(i + 1, j))
                return true;
            else{
                uncheckBox(i, j, n); // caso n�o tenha conseguido resolver quer dizer que com este numero,
                // qualquer combina��o de numeros a seguir n�o d� solu��es, logo volta a p�r a 0
            }
        }
    }

    // Solu��o errada
    return false;
}

void Sudoku::checkBox(int i, int j, int n) {
    numbers[i][j] = n;
    lineHasNumber[i][n] = true;
    columnHasNumber[j][n] = true;
    block3x3HasNumber[i / 3][j / 3][n] = true;
    countFilled++;
}

void Sudoku::uncheckBox(int i, int j, int n) {
    numbers[i][j] = 0;
    lineHasNumber[i][n] = false;
    columnHasNumber[j][n] = false;
    block3x3HasNumber[i / 3][j / 3][n] = false;
    countFilled--;
}