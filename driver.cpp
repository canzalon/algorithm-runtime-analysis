/*****************************************************************************
Project: algorithm-runtime-analysis
Author: Christopher Anzalone
File: driver.cpp

Description: 

In this project I have implemented an insertion, heap, and quick 
sort to sort arrays of randomly generated numbers of varying length. There 
are k experiments carried out, with five trials for each sorting algorithm, 
each trial with an array of psuedo-randomly generated numbers of length n; 
where 1 <= k <= 10, n = 100k. Thus, altogether there are 15 trials per 
experiment; five trials per sorting algorithm. In each experiment, the arrays 
are sorted with the each of the sort algorithms mentioned above, and the 
runtime for each algorithm is measured using the Windows library functions 
QueryPerformanceCounter() and QueryPerformanceFrequency(). The average 
runtime of the five trials for each sorting algorithm for each experiment is 
recorded. The idea behind these trials is to examine how efficient each of 
these sorting algorithms are upon completion on sorting arrays of varying 
size, with equal degrees of randomosity (that is, random numbers between 1-9). 

The program saves three files to its directory; raw_data.txt, 
console_output.txt, and summary.txt. The raw_data file saves, for each trial 
of each sorting algorithm of each experiment, all of the number arrays before 
and after the respective sorts, along with the calculated runtimes of each of 
those trials. The console_output file saves only the runtimes of each of the 
trials, along with the average runtimes of each algorithm's five trials. The 
summary file, contains perhaps the most important data for the entire 
experiment, all of the average runtimes for each sorting algorithm of each k 
experiment. 

The data from this program has been compared to theoretical calculations of 
how each algorithm should perform with each varying array of length n. All of 
the aforementioned files are included in the repository. 
*****************************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <fstream>
#include "algoOption.h"
#include <cmath>

using namespace std;

int MIN_ARRAY_SIZE = 101; 
int MAX_ARRAY_SIZE = 1001;
int ITERATION_START = 1;

/*vars for heap sort*/
int heap_size;
int nx;

/*vars for quicksort*/
int q;

void randArrayGen(int * A, int arrLength);

/*Insertion Sort function*/
void insertionSort(int * A, int length);

/*Heap Sort functions*/
void swap(int &, int&);
void maxHeapify(int * A, int i/*, int currentSize*/);
void buildMaxHeap(int * A, int currentSize);
void heapSort(int * A, int currentSize);
int Left(int i);
int Right(int i);

/*Quicksort function*/
void quickSort(int * A, int p, int r);
int partition(int * A, int p, int r);

void quickSort(int * A, int p, int r)
{  
	if (p < r)
	{
		q = partition(A, p, r);
		quickSort(A, p, q-1);
		quickSort(A, q+1, r);
	}
}

int partition(int * A, int p, int r)
{
	int x = A[r];
	int i = p - 1;

	for (int j = p; j < r; j++)
	{
		if (A[j] <= x)
		{
			i = i + 1; 
			swap(A[i], A[j]);
		}
	}

	swap(A[i+1], A[r]);

	return (i+1);
	
}

void swap(int &x,int &y)
{
    int temp=x;
    x=y;
    y=temp;
}

void maxHeapify(int * A, int i/*, int currentSize*/)
{
	int left = Left(i);

	int right = Right(i);

	int largest;

	if ((left <= heap_size) && (A[left] > A[i]))
	{
		largest = left;
	}
	else
	{
		largest = i;
	}

	if ((right <= heap_size) && (A[right] > A[largest]))
	{
		largest = right;
	}

	if (largest != i)
	{
		swap(A[i], A[largest]);
		maxHeapify(A, largest/*, currentSize*/);
	}
}

void buildMaxHeap(int * A, int currentSize)
{
	double m = ((double)heap_size) / 2;  //reduce this eventually

	for (int i = floor(m); i > /*1*/0; i--)
	{
		maxHeapify(A, i/*, currentSize*/);
	}
}

void heapSort(int * A, int currentSize)
{
	nx = heap_size = currentSize;
	
	buildMaxHeap(A, currentSize);

	heap_size = heap_size - 1;

	for (int i = heap_size; i > /*2*/1; i--)
	{
		swap(A[1], A[/*heap_size*/i]);
		heap_size = heap_size - 1;
		maxHeapify(A, 1/*, currentSize*/);
	}
}

int Left(int i)
{
	return (2 * i);
}

int Right(int i)
{
	return ( (2 * i) + 1);
}

int main()
{
	/*output stream objects*/
	ofstream testFile;
	testFile.open("raw_data.txt");

	ofstream consoleSave;
	consoleSave.open("console_output.txt");

	ofstream summaryFile;
	summaryFile.open("summary.txt");
	
	/*counter to control algorithm used
	  0-insertion, 1-heap, 2-quick*/
	//int algoOption = 0;
	algoOption algoSwitch;

	bool noAlgoExec = false;

	/*For debugging purposes; keep track of value of cycles that have occured throughout analysis*/
	int cycle = 0;

	/*current number of elements in array*/
	int n = MIN_ARRAY_SIZE;

	/*int array object*/
	int * currentArray;

	/*storage for the 5 run times, including the average value*/
	//int * avgRT;
	double * avgRT;
	int avgArrLength = 5;
	double averageRT = 0.0;

	/*var to hold run time of trial*/
	double currentRT;

	/*counter variables for determining run times*/
	__int64 start = 0, end = 0, freq = 0; //REMEMBER TO REINITIALIZE TO 0 AT END OF LOOP BELOW
	
	//LARGE_INTEGER start, end, freq;

	/*Experiment k of n size array*/
	while (n <= MAX_ARRAY_SIZE)
	{	
		//testFile.open("test_output.txt");

		cycle = 0;

		//cout << "\nExperiment of size n = " << n - 1 << " ...\n";
		//consoleSave << "\nExperiment of size n = " << n - 1 << " ...\n";

		cout << "----------------------------------------------" << endl;
		cout << " SIZE: " << n - 1 << endl;
		cout << "----------------------------------------------" << endl;

		consoleSave << "----------------------------------------------" << endl;
		consoleSave << " SIZE: " << n - 1 << endl;
		consoleSave << "----------------------------------------------" << endl;

		/*Formatting for output test file*/
//		testFile << "===================================================\n\n";
		testFile << "----------------------------------------------" << endl;
		testFile << " SIZE: " << n - 1 << endl;
		testFile << "----------------------------------------------" << endl;

		summaryFile << "----------------------------------------------" << endl;
		summaryFile << " SIZE: " << n - 1 << endl;
		summaryFile << "----------------------------------------------" << endl;

		//// Incorporate code for involving the other algorithms, loop through each

		/*Loop through the three algorithms for each array size n*/
		for (algoSwitch.setValue(0); algoSwitch.algoReturn() < 3; algoSwitch.nextAlgo())  //FIX LOOP, MAY NOT NEED THIS LOOP
		{

			/*Allocate memory for avg list and initialize*/
			avgRT = new double[avgArrLength];
			for (int x = 0; x < avgArrLength; x++)
			{
				avgRT[x] = 0.0;
			}

			/*Label algorithm being measured in current five-trial measurement of size n */
			if (algoSwitch.algoReturn() == 0)
			{
				cout << " -Insertion Sort:" << endl;
				consoleSave << " -Insertion Sort:" << endl;
				testFile << " \n-Insertion Sort:" << endl;
				summaryFile << " \n-Insertion Sort:" << endl;
			}
			else if (algoSwitch.algoReturn() == 1)
			{
				cout << " -Heap Sort:" << endl;
				consoleSave << " -Heap Sort:" << endl;
				testFile << " \n-Heap Sort:" << endl;
				summaryFile << " \n-Heap Sort:" << endl;
			}
			else 
			{
				cout << " -Quick Sort:" << endl;
				consoleSave << " -Quick Sort:" << endl;
				testFile << " \n-Quick Sort:" << endl;
				summaryFile << " \n-Quick Sort:" << endl;
			}

			/*Loop for each array sort, occurs five times, then avg RT is taken*/
			for (int y = 0; y < 5; y++)
			{
				cycle++;

				int currentSize = n;

				/*initialize integer array to be sorted*/
				currentArray = new int[currentSize];
				for (int x = 0; x < currentSize; x++)
				{
					currentArray[x] = 0;
				}

				//call random number gen for array
				randArrayGen(currentArray, currentSize);

				//print array values before sort to file
				testFile << "\nA[]" << " of trial [" << y + 1 << "] BEFORE sort " << ": ";
				for (int x = 1; x < currentSize; x++)  //---CHANGE TO X = ITERATION_START AFTER TESTING TO HIDE 0TH ELEMENT
				{
					//cout<<"\nA"<<"["<<x<<"]"<<": "<<currentArray[x]<<endl;
					testFile << currentArray[x] << " ";
				}

				if (algoSwitch.algoReturn() == 0)  //insertion
				{
					/*Begin timer*/
					QueryPerformanceCounter((LARGE_INTEGER *)&start);

					/*Insertion sort*/
					insertionSort(currentArray, currentSize);

					/*Finish timer, number of ticks that have passed: (end-start)*/
					QueryPerformanceCounter((LARGE_INTEGER *)&end);
				}
				else if (algoSwitch.algoReturn() == 1)  //heap
				{
					/*Begin timer*/
					QueryPerformanceCounter((LARGE_INTEGER *)&start);

					/*Heap sort*/
					heapSort(currentArray, currentSize/*-1*/);

					/*Finish timer, number of ticks that have passed: (end-start)*/
					QueryPerformanceCounter((LARGE_INTEGER *)&end);
				}
				else if (algoSwitch.algoReturn() == 2)  //quick 
				{	
					//cout << " -Quick Sort:" << endl;
					//consoleSave << " -Quick Sort:" << endl;
					//testFile << " \n-Quick Sort:" << endl;

					/*Begin timer*/
					QueryPerformanceCounter((LARGE_INTEGER *)&start);

					/*Quick sort*/
					quickSort(currentArray, 1, currentSize-1);

					/*Finish timer, number of ticks that have passed: (end-start)*/
					QueryPerformanceCounter((LARGE_INTEGER *)&end);
				}
				else
				{
					noAlgoExec = true;
				}

				if (noAlgoExec)
				{
					cout << "ERROR: NO ALGORITHM EXECUTED IN CYCLE " << cycle;  
					cout << " DURING ALGORITHM ";
					algoSwitch.currentAlgo(cycle);
					cout << " DURING EXPERIMENT n = " << n << endl;
					return 1;
				}

				/*Get frequency of ticks*/
				QueryPerformanceFrequency((LARGE_INTEGER *)&freq);

				/*Obtain actual time passed*/
				currentRT = (end-start) * 1.0 / freq;

				//convert time to microseconds

				//print current rt to screen
				cout << " \n   RT of trial " << y + 1 << ":  " << currentRT << " s" << endl; 
				consoleSave << " \n   RT of trial " << y + 1 << ":  " << currentRT << " s" << endl;

				//print current rt to file
				testFile << " \n  RT of trial " << y + 1 << ":  " << currentRT << " s" << endl; 

				/*save current runtime to avg array*/
				avgRT[y] = currentRT;

				//print array values after sort to file
				testFile << "\nA[]" << " of trial [" << y + 1 << "] AFTER sort " << ": ";
				for (int x = 1; x < currentSize; x++) //---CHANGE TO X = ITERATION_START AFTER TESTING TO HIDE 0TH ELEMENT
				{
					//cout<<"\nA"<<"["<<x<<"]"<<": "<<currentArray[x]<<endl;
					testFile << currentArray[x] << " ";
				}

				testFile << endl;
				cout << endl;
				consoleSave << endl;

				/*Re-initialize variables for next loop*/
				currentRT = 0.0;
				start = 0;
				end = 0;
				freq = 0;
				delete currentArray;
			}

		

			/*Determine average value of the five runs*/
			//averageRT = 0.0;
			for (int x = 0; x < avgArrLength; x++)
			{
				averageRT = averageRT + avgRT[x];
			}

			averageRT = averageRT / (double)avgArrLength;



			//print avg to screen
			cout << "      Average of experiment " << n - 1 << ": " << averageRT << " s\n" << endl;
			consoleSave << "      Average of experiment " << n - 1 << ": " << averageRT << " s\n" << endl;

			//print avg to file
			testFile << "\nAverage of experiment " << n - 1 << ": " << averageRT << " s\n" << endl;

			summaryFile << "\nAverage of experiment " << n - 1 << ": " << averageRT << " s\n" << endl;

		}

		/*deallocate dynamic memory*/
		//delete currentArray;
		delete avgRT;

		averageRT = 0.0;

		/*additional 100 elements for next experiment*/
		n=n+100;
	}

	cout << "\n\n Analysis Complete. \n\n\n" << endl;
	testFile << "\n\n Analysis Complete. \n\n" << endl;
	consoleSave << "\n\n Analysis Complete. \n\n" << endl;

	cout<<"NOTE:\n";
	cout<<" Raw data has been saved to 'raw_data.txt'"<<endl;
	cout<<" Copy of full console output saved to 'console_output.txt'"<<endl;
	cout<<" Summary of average runtimes saved to 'summary.txt'\n"<<endl;

	/*close files*/
	testFile.close();
	consoleSave.close();
	summaryFile.close();

	return 0;
}

void insertionSort(int * currentArray, int currentSize)
{
	int key = 0;  //var for temp value of elem j
	int i = 0;  //var to ref value before key for comparison
		
	//note: j references (i+1)th elem to compare with ith elem

	/*iteration through array from element 2 to n for comparisons of j+1 (i=j-1) and j+2*/
	for (int j=2; j < currentSize; j++)
	{
		/*establish sub-array by saving last elem of comparisons to key & for possible movement*/
		key = currentArray[j];

		/*establish pointer for elem before jth element before looping*/
		i = j - 1;

		/*comparison and swap if (i=j-1) > j, reverse iterating through array until i < 1*/
		while ( (i > 0) && (currentArray[i] > key) )
		{
			currentArray[i+1] = currentArray[i];
			i = i - 1;
		}

		/*establish greater value in this jth iteration*/
		currentArray[i + 1] = key;
	}
}

void randArrayGen(int * A, int arrLength)
{
	int randNum;

	for (int x = ITERATION_START; x < arrLength; x++)
	{
		/*generate rand num btwn 1 and 9 for array element*/
		randNum = rand() % 9 + 1; 

		/*store random number in array element x*/
		A[x] = randNum;
		
		randNum = 0;
	}

}