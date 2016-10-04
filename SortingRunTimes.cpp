/********************************************************************************************
Name: Gavin Wolf		Z#: 15289719
Course: COT 4400: Design and Analysis of Algorithms
Professor: Dr. Mihaela Cardei
Due Date: 10/22/2015
Programming Assignment 3

Description: This program implements three sorting algorithms, InsertionSort, HeapSort and
 MergeSort, and measures their actual run-times over a number of trials and a range of
 input sizes.
*********************************************************************************************/

#include <iostream>
#include <chrono>

using namespace std;

//Function declarations
void InsertionSort(int *A, int n);
void MaxHeapify(int *A, int i, int n);
void HeapSort(int *A, int n);
void BuildMaxHeap(int *A, int n);
void Merge(int *A, int p, int q, int r);
void MergeSort(int *A, int p, int r);

//Array declarations
int A[11][20001]; //+1 to account for C++'s 0-based indexing
int B[20001]; //+1 to account for C++'s 0-based indexing
int L[10002]; //+1 to account for C++'s 0-based indexing, +1 to account for sentinel value
int R[10002]; //+1 to account for C++'s 0-based indexing, +1 to account for sentinel value

int main()
{
	/********************************************************************************************
	Set up master table A, from which arrays to sort will be pulled
	*********************************************************************************************/
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 20000; j++)
		{
			A[i][j] = rand();
		}
	}

	/********************************************************************************************
	Simulation and measurements for InsertionSort. Runs 10 sorts for each input size: 
	 1000, 2000, 3000, ... , 20000
	*********************************************************************************************/	
	cout << "\nInsertionSort results: number of elements, average running time in microseconds\n";

	for (int n = 1000; n <= 20000; n = n + 1000)
	{
		int sumTime = 0; //Will be used to calculate the average
			
		for (int i = 1; i <= 10; i++)
		{
			//Copy section of master table A into array B
			for (int j = 1; j <= n; j++)
			{
				B[j] = A[i][j];
			}

			auto t1 = std::chrono::high_resolution_clock::now(); //Start time of execution
			InsertionSort(B, n);
			auto t2 = std::chrono::high_resolution_clock::now(); //Stop time of execution
			auto sortTime = t2 - t1; //Execution time
			long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

			sumTime += microseconds; //When loop exits, this will be the sum of all 10 trials
		}
		int averageTime = sumTime / 10;
		cout << n << "\n" << averageTime << endl;
	}

	/********************************************************************************************
	Simulation and measurements for HeapSort. Runs 10 sorts for each input size:
	 1000, 2000, 3000, ... , 20000
	*********************************************************************************************/
	cout << "\nHeapSort results: number of elements, average running time in microseconds\n";

	for (int n = 1000; n <= 20000; n = n + 1000)
	{
		int sumTime = 0; //Will be used to calculate the average

		for (int i = 1; i <= 10; i++)
		{
			//Copy section of master table A into array B
			for (int j = 1; j <= n; j++)
			{
				B[j] = A[i][j];
			}

			auto t1 = std::chrono::high_resolution_clock::now(); //Start time of execution
			BuildMaxHeap(B, n);
			HeapSort(B, n);
			auto t2 = std::chrono::high_resolution_clock::now(); //Stop time of execution
			auto sortTime = t2 - t1; //Execution time
			long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

			sumTime += microseconds; //When loop exits, this will be the sum of all 10 trials
		}
		int averageTime = sumTime / 10;
		cout << n << "\n" << averageTime << endl;
	}

	/********************************************************************************************
	Simulation and measurements for MergeSort. Runs 10 sorts for each input size:
	 1000, 2000, 3000, ... , 20000
	*********************************************************************************************/
	cout << "\nMergeSort results: number of elements, average running time in microseconds\n";

	for (int n = 1000; n <= 20000; n = n + 1000)
	{
		int sumTime = 0; //Will be used to calculate the average

		for (int i = 1; i <= 10; i++)
		{
			//Copy section of master table A into array B
			for (int j = 1; j <= n; j++)
			{
				B[j] = A[i][j];
			}

			auto t1 = std::chrono::high_resolution_clock::now(); //Start time of execution
			MergeSort(B, 1, n);
			auto t2 = std::chrono::high_resolution_clock::now(); //Stop time of execution
			auto sortTime = t2 - t1; //Execution time
			long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

			sumTime += microseconds; //When loop exits, this will be the sum of all 10 trials
		}
		int averageTime = sumTime / 10;
		cout << n << "\n" << averageTime << endl;
	}

	return 0;
}

/********************************************************************************************
InsertionSort algorithm
*********************************************************************************************/
void InsertionSort(int *A, int n)
{
	int key, //The value being "inserted"
		i; //Index to insert key after

	for (int j = 2; j <= n; j++)
	{
		key = A[j];
		i = j - 1;
		while (i > 0 && A[i] > key)
		{
			A[i + 1] = A[i]; //Shift elements greater than key
			i--;
		}
		A[i + 1] = key; //Insert key
	}
}

/********************************************************************************************
HeapSort algorithm
*********************************************************************************************/
void HeapSort(int *A, int n)
{
	BuildMaxHeap(A, n);

	for (int i = n; i >= 2; i--)
	{
		//exchange A[i] <--> A[n]
		int temp = A[1];
		A[1] = A[n];
		A[n] = temp;

		n = n - 1;

		MaxHeapify(A, 1, n);
	}
}

/********************************************************************************************
MergeSort algorithm
*********************************************************************************************/
void MergeSort(int *A, int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2; //want the floor of this expression; int division --> will get floor
		MergeSort(A, p, q);
		MergeSort(A, q + 1, r);
		Merge(A, p, q, r);
	}
}

/********************************************************************************************
MaxHeapify. A helper function for HeapSort
*********************************************************************************************/
void MaxHeapify(int *A, int i, int n)
{
	int l = 2 * i; //Left child
	int r = 2 * i + 1; //Right child

	int largest;
	if (l <= n && A[l] > A[i])
		largest = l;
	else
		largest = i;
	if (r <= n && A[r] > A[largest])
		largest = r;
	if (largest != i)
	{
		//exchange A[i] <--> A[largest]
		int temp = A[i];
		A[i] = A[largest];
		A[largest] = temp;

		MaxHeapify(A, largest, n);
	}
}

/********************************************************************************************
BuildMaxHeap. A helper function for HeapSort
*********************************************************************************************/
void BuildMaxHeap(int *A, int n)
{
	for (int i = n / 2; i >= 1; i--) //want floor of n / 2; will get that with int division
		MaxHeapify(A, i, n);
}

/********************************************************************************************
Merge. A helper function for MergeSort
*********************************************************************************************/
void Merge(int *A, int p, int q, int r)
{
	int n1 = q - p + 1; //Last index of left array, AND size of L array (before sentinel)
	int n2 = r - q; //Last index of right array, AND size of R array (before sentinel)

	for (int i = 1; i <= n1; i++)
		L[i] = A[p + i - 1];

	for (int j = 1; j <= n2; j++)
		R[j] = A[q + j];

	//Note: algorithm pseudocode uses infinity. For this program, RAND_MAX + 1 will work
	// because it will be larger than any number in an array generated using the rand() function
	L[n1 + 1] = RAND_MAX + 1;
	R[n2 + 1] = RAND_MAX + 1;

	int i = 1;
	int j = 1;

	for (int k = p; k <= r; k++)
	{
		if (L[i] <= R[j])
		{
			A[k] = L[i];
			i = i + 1;
		}
		else
		{
			A[k] = R[j];
			j = j + 1;
		}
	}
}