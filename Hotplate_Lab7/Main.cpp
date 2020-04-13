#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const int ROWS = 20;
const int COLUMNS = 20;

// A function that will print the hotplate 
void print(double hotplate[20][20])
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			cout << fixed << setw(3) << setprecision(1) << hotplate[i][j];
		}
		cout << endl;
	}
}

// A function to find the average of 4 cells
double average(double hotplate[20][20], double oldhotplate[20][20])
{
	double difference = 100;
	double biggestDifference = 0;

		for (int i = 1; i < ROWS - 1; i++)
		{
		
			for (int j = 1; j < COLUMNS - 1; j++)
			{
				hotplate[i][j] = (oldhotplate[i][j - 1] + oldhotplate[i - 1][j] + oldhotplate[i][j + 1] + oldhotplate[i + 1][j]) / 4;

				difference = abs(hotplate[i][j] - oldhotplate[i][j]);
				
				if (difference > biggestDifference)
				{
					biggestDifference = difference;
				}
			}

		}
		return biggestDifference;
}

// Swap the values from original array to new array
void swap(double hotplate[20][20], double oldhotplate[20][20])
{
	for (int i = 1; i < ROWS - 1; i++)
	{
		for (int j = 1; j < COLUMNS - 1; j++)
		{
			oldhotplate[i][j] = hotplate[i][j];
		}
	}
}


// Initializes the arrays to be used
void initialize(double hotplate[20][20])
{
	const int DIMENSIONS = 20;

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			hotplate[i][j]=0;
		}
	}

	for (int i = 1; i < DIMENSIONS - 1; i++)
	{
		hotplate[0][i] = 100;
		hotplate[ROWS-1][i] = 100;
	}
	
}

// Exports the values separated with commas for use in Excel
void exportCSV(double hotplate[20][20], ostream& os)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			os << hotplate[i][j] << ",";
		}
		os << endl;
	}
}


int main()
{
	double hotplate[ROWS][COLUMNS];
	double oldhotplate[ROWS][COLUMNS];
	
	
	// Intialize and print first iteration
	initialize(hotplate);
	print(hotplate);
	// Intialize copy of array
	initialize(oldhotplate);
	// Average out second iteration and print
	average(hotplate, oldhotplate);
	print(hotplate);
	// Continue to find nth iterations until the change in degree is .1
	double changeDegree = 100;
	while (changeDegree > .1)
	{
		changeDegree = average(hotplate, oldhotplate);
		swap(hotplate, oldhotplate);
	}
	// Prepare to export to Excel
	ofstream fout("lab6output.csv");

	exportCSV(hotplate, fout);

	fout.close();
	
	system("pause");
	return 0;
}