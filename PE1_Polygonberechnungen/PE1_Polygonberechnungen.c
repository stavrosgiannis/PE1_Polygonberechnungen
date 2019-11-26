#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int getArrayMin(int* x, int size) {
	int min = x[0], i;
	for (i = 1; i < size; i++) {
		if (x[i] < min) {
			min = x[i];
		}
	}
	return min;
}

int getArrayLength(double _INPUT_ARRAY[]) {
	int size;
	size = sizeof(_INPUT_ARRAY) / sizeof(_INPUT_ARRAY[0]);
	return size;
}

int calc_GaußElling_polygon_surface(double x[], double y[]) {
	if ((x == NULL) || (y == NULL)) return 0.0;
	int n = getArrayMin(x, getArrayLength(x));

	return n;
}

int main()
{
	// variables for reading the measurements from file
	FILE* fp;
	size_t len = 0;
	char resp;

	double x_t[20];
	double y_t[20];

	double x;
	double y;

	// open the input file "polygon.txt" for reading
	fp = fopen("polygon.txt", "r");
	if (fp == NULL)
	{
		// if file could not be opened (wrong path, not readable, ...)
		// output a short message and immediately exit
		printf("Eingabedatei kann nicht geoeffnet werden.\n");
		scanf("%c", &resp);
		exit(EXIT_FAILURE);
	}

	// print program header
	printf("\n\nProgramm zur Berechnung eines Polygons\n");
	printf("--------------------------------------------------------\n");

	// the following loop reads a new value in every iteration
	// until the end of the file or some invalid token is found
	while (1)
	{
		len = fscanf(fp, "%lf %lf", &x, &y);

		if (len == EOF)
			break;
		else if (len == 0) {
			printf("Unerwartetes Zeichen in der Eingabedatei.");
			scanf("%c", &resp);
			exit(EXIT_FAILURE);
		}

		printf("Lese Eckpunkt: %6.2f/%6.2f\n", x, y);
	}

	// output results
	printf("\nErgebnisse:\n");
	printf("-----------\n\n");

	// finally close the input file and clean up memory
	fclose(fp);

	// wait for user input before closing terminal
	scanf("%c", &resp);
}