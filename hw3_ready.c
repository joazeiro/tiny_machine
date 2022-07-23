// CDA3103 - Group Project, HW3 - Summer 2022
// Maria Eduarda Joazeiro Gomes, Sierra Sesto, Dishang Shah, and Andrew Anchieta

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPROGRAMSIZE 1024
#define MAXMEMORYSIZE 10

typedef struct instruction {
	int opCode;
	int address;
} instruction;

void initialPrint(int PC, int A, int *IM) {
	printf("PC = %d | A = %d, DM = [", PC, A);

	for (int i = 0; i < MAXMEMORYSIZE; i++)
		i != MAXMEMORYSIZE - 1? printf("%d, ", IM[i]): printf("%d", IM[i]);

	printf("]\n\n");
}

void fetch(int *PC, int *MAR, instruction *MDR, instruction *IR, instruction *IM) {
	*MAR = *PC;
	(*PC)++;
	MDR->opCode = IM[*MAR].opCode;
	MDR->address = IM[*MAR].address;
	*IR = *MDR;
}

// Main machine function
void tinyMachine(instruction *IM) {
	int MAR = 0, MAR2, MDR2, PC = 10, A = 0, DM[MAXMEMORYSIZE] = {0};
	instruction MDR, IR;

	while (IR.opCode != 7) {
		initialPrint(PC, A, DM); // Prints data memory, accumulator, and counter
		fetch(&PC, &MAR, &MDR, &IR, IM);

		switch (IR.opCode) {
			case 1: // Loads data from memory address to accumulator
				MAR2 = IR.address;
				printf("Loading memory location %d to accumulator...\n", MAR2);
				MDR2 = DM[MAR2];
				A = MDR2;
				break;
			case 2: // Adds value from memory address to accumulator
				MAR2 = IR.address;
				printf("Loading memory location %d to be added to accumulator value %d...\n", MAR2, A);
				MDR2 = DM[MAR2];
				A += MDR2;
				break;
			case 3: // Stores value from accumulator to memory address
				MAR2 = IR.address;
				printf("Storing accumulator to memory location %d...\n", MAR2);
				MDR2 = A;
				DM[MAR2] = MDR2;
				break;
			case 4: // Subtracts value in accumulator by value in memory address
				MAR2 = IR.address;
				printf("Loading memory location %d to be subtracted from accumulator value %d...\n", MAR2, A);
				MDR2 = DM[MAR2];
				A -= MDR2; 
				break;
			case 5: // User input
				printf("Input value:\n");
				scanf("%d", &A);
				break;
			case 6: // Outputs value in accumulator
				printf("Outputting accumulator to screen...\n");
				printf("%d\n", A);
				break;
			case 7: // Will end program by breaking from switch statement and while loop
				printf("Ending program...\n");
				break;
			case 8: // Jumps to specified address from memory address
				printf("Jumping to memory location %d...\n", IR.address);
				PC = IR.address;
				break;
			case 9: // SKIPZ
				if (A == 0)
					PC++;
				break;
			default: // If theres another integer in the memory, it gets ignored
				break;
		}
	}
}

void readFile(char *name) {
	// Declaring/Initializing variables
	FILE *in = fopen(name, "r");
	instruction IM[MAXPROGRAMSIZE]; // Virtual memory structure array

	// Checks if file with given name exists
	if (in == NULL) {
		fprintf(stderr, "This file name does not exist.");
		return;
	}

	printf("Assembling Program...\n");

	// Assembles the instructions from the file to the memory
	for (int i = 10; !feof(in); i++)
		fscanf(in, "%d %d", &IM[i].opCode, &IM[i].address);

	fclose(in);
	printf("Program Assembled.\n\nRun.\n\n");
	tinyMachine(IM);
}

int main(int argc, char **argv) {
	readFile(argv[1]); // Takes file name and passes it to function to read and execute it
	printf("\nProgram complete.\n");
	return 0;
}