# include <iostream>
# include <iostream>
# include <string>
# include <thread>
# include <omp.h>

using namespace std;

// Dzhaparov Emirkhan BSE197 8 var

// Количество уравнений СЛАУ.(кол-во строк главной матрицы системы)
const int numOfEquations = 4;

// Количество неизвестных плюс один столбец правых частей системы.
// (кол-во столбцов главной матрицы системы со столбцом правых частей)
const int numOfVariablesWithRightElems = 5;

/// <summary>
/// Подсчет определителя квадратной матрицы 3 x 3 по методу разложения в строку.
/// </summary>
/// <param name="matrix"> Матрица, определитель которой считается.</param>
/// <returns> Определитель матрицы 2 x 2.</returns>
double MinorOfElem(double matrix[numOfEquations-1][numOfEquations-1])
{
	// Переменная, хранящаяся значение определителя матрицы 3 x 3.
	double det = 0;

	// В этой переменной будут храниться матрицы миноров 2 x 2 для элементов первой строки.
	double matrixOfMinor[numOfEquations - 1][numOfEquations - 1];

	// Проход по элементам первой строки.
	for (int i = 0; i < numOfEquations-1; i++)
	{
		// Составление матрицы 2 x 2 минора i-го элемента первой строки.
		for (int j = 0; j < numOfEquations - 2; j++)
		{
			// Заполнение j-ой строки матрицы 2 x 2.
			int k, posOfCol;
			for (k = 0, posOfCol = 0; k < numOfEquations; k++)
			{
				if (k != i)
				{
					matrixOfMinor[j][posOfCol] = matrix[j + 1][k];
					posOfCol++;
				}
			}
		}

		// Вычисление определителя матрицы системы по методу разложения по строке.
		double minorDet = matrixOfMinor[0][0] * matrixOfMinor[1][1] - matrixOfMinor[1][0] * matrixOfMinor[0][1];

		// Проверка на четность суммы двух обеих позиций элемента, для которого считается минор.
		if (i % 2 == 0)
			det += matrix[0][i] * minorDet;
		else
			det -= matrix[0][i] * minorDet;
	}
	return det;
}

/// <summary>
/// Подсчет определителя главной матрицы системы по методу разложения по n-ой строке.
/// В данном случае разложение определителя матрицы производится по первой строке.</summary>
/// <param name="mainMatrix"> Главная матрица СЛАУ.</param>
/// <returns> Определитель матрицы системы.</returns>
double DetOfMainMatrix(double mainMatrix[numOfEquations][numOfVariablesWithRightElems])
{
	// Переменная, хранящаяся значение определителя матрицы 4 x 4.
	double det = 0;

	// В этой переменной будут храниться матрицы миноров 3 x 3 для элементов первой строки.
	double matrixOfMinor[numOfEquations-1][numOfEquations-1];

	// Проход по элементам первой строки.
	for (int i = 0; i < numOfEquations; i++)
	{
		// Составление матрицы 3 x 3 минора i-го элемента первой строки.
		for (int j = 0; j < numOfEquations - 1; j++)
		{
			// Заполнение j-ой строки матрицы 3 x 3.
			int k, posOfCol;
			for (k = 0, posOfCol = 0; k < numOfEquations; k++)
			{
				if (k != i)
				{
					matrixOfMinor[j][posOfCol] = mainMatrix[j + 1][k];
					posOfCol++;
				}
					
			}
		}

		// Вычисление определителя матрицы системы по методу разложения по строке.
		double minorDet = MinorOfElem(matrixOfMinor);

		// Проверка на четность суммы двух обеих позиций элемента, для которого считается минор.
		if (i % 2 == 0)
			det += mainMatrix[0][i] * minorDet;
		else
			det -= mainMatrix[0][i] * minorDet;
	}
	return det;

}

/// <summary>
/// Сообщение об ошибке в случае вырожденности матрицы системы.
/// </summary>
void ShowError()
{
	cout << "\nThe value of MainMatrix's determinant equals 0.\nThe Kramer's formules are unavailable in this case.";
}

/// <summary>
/// Вывод системы уравнений на консоль.
/// </summary>
/// <param name="mainMatrix"> Матрица системы, расширенная, по которой выводится система уравнений на консоль.</param>
void ShowTheSystem(double mainMatrix[numOfEquations][numOfVariablesWithRightElems]) 
{
	cout << "\nThe System of Linear Equations:\n";
	for (int i = 0; i < numOfEquations; i++) {
		for (int j = 0; j < numOfVariablesWithRightElems; j++) {
			if (j != numOfVariablesWithRightElems - 1)
				if (j != numOfVariablesWithRightElems - 2)
					cout << mainMatrix[i][j] << "*X" << j + 1 <<"  " << "+"<< "  ";
				else
					cout << mainMatrix[i][j] << "*X" << j + 1<<"  ";
			else
				cout << "= " << mainMatrix[i][j] << std::endl;
		}
	}
}

int main()
{
	// Главная матрица система, расширенная столбцом правых частей.
	double mainMatrix[numOfEquations][numOfVariablesWithRightElems];

	// Ввод пользователем значения элементов системы с консоли.
	string inputedValue = "";
	bool corrArg = false;
	for (int i = 0; i < numOfEquations; i++)
	{
		for (int j = 0; j < numOfVariablesWithRightElems; j++)
		{
			
			while (!corrArg)
			{
				try
				{
					if (j == numOfVariablesWithRightElems - 1)
					{
						cout <<"Input the value of right side's elem of the system:\n" ;
						cout << "B" << "_" << i + 1 << " := ";
					}
					else
					{
						cout << "Input the coefficient of the system:\n";
						cout << "C" << "_" << i + 1 << "_" << j + 1 << " := ";
					}
					cin >> inputedValue;
					mainMatrix[i][j] = stod(inputedValue);
					corrArg = true;
				}
				catch (invalid_argument)
				{
					cout << "Incorrect argument was inputed!\n";
					corrArg = false;;
				}
				catch (out_of_range)
				{
					cout << "The argument was too big!\n";
					corrArg = false;
				}
				catch (exception)
				{
					cout << "Incorrect argument was inputed!\n";
					corrArg = false;
				}
			}
			corrArg = false;
		}
	}



	// Вычисление определителя матрицы системы.
	double detOfMainMatrix = DetOfMainMatrix(mainMatrix);

	// Вывод в консоль системы уравнений.
	ShowTheSystem(mainMatrix);

	// Проверка на вырожденность матрицы системы.
	if (detOfMainMatrix == 0)
	{
		ShowError();
	}
	else
	{
		double values[4];
		cout << "\nThe values of X:\n";
		#pragma omp parallel num_threads(4)
		{
			#pragma omp for
				for(int iterator = 0; iterator < 4; iterator++)
				{
					// Промежуточная матрица для i-го элемента, получающаяся путем замены i-ого столбца на столбец правых частей.
					double tempMatrix[numOfEquations][numOfVariablesWithRightElems];
					for (int i = 0; i < numOfEquations; i++)
					{
						for (int j = 0; j < numOfEquations; j++)
						{
							if (j != iterator)
							{
								tempMatrix[i][j] = mainMatrix[i][j];
							}
							else
							{
								tempMatrix[i][j] = mainMatrix[i][numOfVariablesWithRightElems-1];
							}
						}
					}
						// Нахождение числителя (определителя матрицы с заменным с столбцом) для формул Крамера.
						double det = DetOfMainMatrix(tempMatrix);
						values[iterator] = det / detOfMainMatrix ;
				}
		}
		cout << values[0] << endl;
		cout << values[1] << endl;
		cout << values[2] << endl;
		cout << values[3] << endl;
	}
	return 0;
}