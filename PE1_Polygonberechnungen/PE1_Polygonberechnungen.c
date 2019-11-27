#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ARRAY_SIZE( array ) ( sizeof( array ) / sizeof( array[0] ) )

//int getArrayMin(int* x, int size) {
//	int min = x[0], i;
//	for (i = 1; i < size; i++) {
//		if (x[i] < min) {
//			min = x[i];
//		}
//	}
//	return min;
//}

int getMathMinimum(double X_LENGTH, double Y_LENGTH) {
	if (X_LENGTH > Y_LENGTH) return Y_LENGTH;
	if (Y_LENGTH > X_LENGTH) return X_LENGTH;
	if (Y_LENGTH == X_LENGTH) return X_LENGTH;
}

double calc_GauﬂElling_polygon_surface(double x[], double y[]) {
	if ((x == NULL) || (y == NULL)) return 0; // auf leere Argumente testen
	int n = getMathMinimum(ARRAY_SIZE(x), ARRAY_SIZE(y)); // Anzahl der Ecken des Polygons
	if (n < 3) return 0; // ein Polygon hat mindestens drei Eckpunkte
	double a = 0.0;
	for (size_t i = 0; i < n; i++)
	{
		a += (y[i] + y[(i + 1) % n]) * (x[i] - x[(i + 1) % n]);
	}
	return n;
}

int main()
{
	// variables for reading the measurements from file
	FILE* fp;
	size_t len = 0;
	char resp;

	double x_t[] = { 7.0, 8.0, 4.0, 1.0, 1.0 };
	double y_t[] = { 0.0, 7.0, 9.0, 6.0, 2.0 };

	printf("\nLength: %d", ARRAY_SIZE(x_t));

	printf("\n%f\n", calc_GauﬂElling_polygon_surface(x_t, y_t));

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