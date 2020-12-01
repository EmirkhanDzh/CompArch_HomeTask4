# include <iostream>
# include <iostream>
# include <string>
# include <thread>
# include <omp.h>

using namespace std;

// Dzhaparov Emirkhan BSE197 8 var

// ���������� ��������� ����.(���-�� ����� ������� ������� �������)
const int numOfEquations = 4;

// ���������� ����������� ���� ���� ������� ������ ������ �������.
// (���-�� �������� ������� ������� ������� �� �������� ������ ������)
const int numOfVariablesWithRightElems = 5;

/// <summary>
/// ������� ������������ ���������� ������� 3 x 3 �� ������ ���������� � ������.
/// </summary>
/// <param name="matrix"> �������, ������������ ������� ���������.</param>
/// <returns> ������������ ������� 2 x 2.</returns>
double MinorOfElem(double matrix[numOfEquations-1][numOfEquations-1])
{
	// ����������, ���������� �������� ������������ ������� 3 x 3.
	double det = 0;

	// � ���� ���������� ����� ��������� ������� ������� 2 x 2 ��� ��������� ������ ������.
	double matrixOfMinor[numOfEquations - 1][numOfEquations - 1];

	// ������ �� ��������� ������ ������.
	for (int i = 0; i < numOfEquations-1; i++)
	{
		// ����������� ������� 2 x 2 ������ i-�� �������� ������ ������.
		for (int j = 0; j < numOfEquations - 2; j++)
		{
			// ���������� j-�� ������ ������� 2 x 2.
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

		// ���������� ������������ ������� ������� �� ������ ���������� �� ������.
		double minorDet = matrixOfMinor[0][0] * matrixOfMinor[1][1] - matrixOfMinor[1][0] * matrixOfMinor[0][1];

		// �������� �� �������� ����� ���� ����� ������� ��������, ��� �������� ��������� �����.
		if (i % 2 == 0)
			det += matrix[0][i] * minorDet;
		else
			det -= matrix[0][i] * minorDet;
	}
	return det;
}

/// <summary>
/// ������� ������������ ������� ������� ������� �� ������ ���������� �� n-�� ������.
/// � ������ ������ ���������� ������������ ������� ������������ �� ������ ������.</summary>
/// <param name="mainMatrix"> ������� ������� ����.</param>
/// <returns> ������������ ������� �������.</returns>
double DetOfMainMatrix(double mainMatrix[numOfEquations][numOfVariablesWithRightElems])
{
	// ����������, ���������� �������� ������������ ������� 4 x 4.
	double det = 0;

	// � ���� ���������� ����� ��������� ������� ������� 3 x 3 ��� ��������� ������ ������.
	double matrixOfMinor[numOfEquations-1][numOfEquations-1];

	// ������ �� ��������� ������ ������.
	for (int i = 0; i < numOfEquations; i++)
	{
		// ����������� ������� 3 x 3 ������ i-�� �������� ������ ������.
		for (int j = 0; j < numOfEquations - 1; j++)
		{
			// ���������� j-�� ������ ������� 3 x 3.
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

		// ���������� ������������ ������� ������� �� ������ ���������� �� ������.
		double minorDet = MinorOfElem(matrixOfMinor);

		// �������� �� �������� ����� ���� ����� ������� ��������, ��� �������� ��������� �����.
		if (i % 2 == 0)
			det += mainMatrix[0][i] * minorDet;
		else
			det -= mainMatrix[0][i] * minorDet;
	}
	return det;

}

/// <summary>
/// ��������� �� ������ � ������ ������������� ������� �������.
/// </summary>
void ShowError()
{
	cout << "\nThe value of MainMatrix's determinant equals 0.\nThe Kramer's formules are unavailable in this case.";
}

/// <summary>
/// ����� ������� ��������� �� �������.
/// </summary>
/// <param name="mainMatrix"> ������� �������, �����������, �� ������� ��������� ������� ��������� �� �������.</param>
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
	// ������� ������� �������, ����������� �������� ������ ������.
	double mainMatrix[numOfEquations][numOfVariablesWithRightElems];

	// ���� ������������� �������� ��������� ������� � �������.
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



	// ���������� ������������ ������� �������.
	double detOfMainMatrix = DetOfMainMatrix(mainMatrix);

	// ����� � ������� ������� ���������.
	ShowTheSystem(mainMatrix);

	// �������� �� ������������� ������� �������.
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
					// ������������� ������� ��� i-�� ��������, ������������ ����� ������ i-��� ������� �� ������� ������ ������.
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
						// ���������� ��������� (������������ ������� � �������� � ��������) ��� ������ �������.
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