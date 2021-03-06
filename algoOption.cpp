/*****************************************************************************
Project: algorithm-runtime-analysis
Author: Christopher Anzalone
File: algoOption.cpp

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

#include "algoOption.h"  
#include <iostream>

using namespace std;

algoOption::algoOption()
{
	option = 0;
}

algoOption::algoOption(int init)
{
	option = init;
}

void algoOption::valueCheck()
{
	if (option > 2)
	{
		option = 0;
	}

}

void algoOption::nextAlgo()
{
	option++;
}

int algoOption::algoReturn()
{
	return option;
}

void algoOption::setValue(int value)
{
	option = value;
}

void algoOption::currentAlgo(int value)  
{
	if (value < 5)
	{
		cout << "Insertion Sort";
	}
	else if (value < 10)
	{
		cout << "Heap Sort";
	}
	else //if (value < 15)
	{
		cout << "Quick Sort";
	}
}