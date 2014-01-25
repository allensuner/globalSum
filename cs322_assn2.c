/*************************\
*	Author: Allen Suner		 *
*	CSCI 322: Assignment 2 *
\*************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** PROTOTYPES **/
void partition (int cores, int cycle);

void receiveValueFromCore (int n, int value);

void sendValueToCore (int n, int value);

void idle ();

/** MAIN **/
int main (int argc, char **argv) {

	int cores = strtol(argv[1], NULL, 10); /* cores is the number of cores with 
																						which	the program will be run	*/

	if (cores == 1) {
		printf("Global sum cannot be computed with just 1 core.");
		return 0;
	} else if (cores == 0) {
		printf("Global sum cannot be computed with 0 cores.");
		return 0;
	}

	partition(cores, 1); /* Begin to partition */

	return 0;
}

/*
Partition is a recursive function that takes in
number of cores, the cycle that the recursion is in.
If the number of cores happen to be odd, then the last
core must idle until an even number is reached. Once a
power of two is achieved, the algorithm becomes trivial.
*/
void partition (int cores, int cycle) {
	int isEven = cores % 2; /* is 0 or 1 */
	int i;
	int coreOffset = (int)pow((double)2, (double)cycle);

	if (cores != 0 && cores != 1) {
		printf("Cycle: %d\tCore offset is %d\tCores used = %d\n", cycle, coreOffset, cores);
		if (isEven == 0) {
			//number of cores is even!
			for (i = 0; i < cores; i++) {
				if (i%2 == 0) {
					receiveValueFromCore(i-1, 0);
					printf("Core %d receives value from core %d.\n", i, i+1);
				} else {
					sendValueToCore(i-1, 0);
					printf("Core %d sends value to core %d.\n", i, i-1);
				}
			}
			partition((cores/2), (cycle+1));
		} else if (isEven == 1) {
			//number of cores is odd!
			for (i = 0; i < cores; i++) {
				if (i%2 == 0) {
					//even core
					if (i == cores-1) {
						idle();
						printf("Core %d has idled.\n", i);
					} else {
						receiveValueFromCore(i+1, 0);
						printf("Core %d receives value from core %d.\n", i, i+1);
					}
				} else {
					//odd core
					sendValueToCore(i-1, 0);
					printf("Core %d sends value to core %d.\n", i, i-1);
				}
			}
			partition(((int)ceil((double)cores/2.0)), (cycle+1));
		}
	} else {
		return;
	}
}

void receiveValueFromCore (int n, int value) { }

void sendValueToCore (int n, int value) { }

void idle () { }
