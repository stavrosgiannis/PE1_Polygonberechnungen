#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PATH "C:\\Users\\Stavros\\source\\repos\\PE1_Polygonberechnungen\\PE1_Polygonberechnungen\\Debug\\"
#define ARRAY_SIZE( array ) ( sizeof( array ) / sizeof( array[0] ) )

int getMathMinimum(double X_LENGTH, double Y_LENGTH) {
	if (X_LENGTH > Y_LENGTH) return Y_LENGTH;
	if (Y_LENGTH > X_LENGTH) return X_LENGTH;
	if (Y_LENGTH == X_LENGTH) return X_LENGTH;
}
//ARRAY_SIZE sizeof - kann nicht über die Funktion mitgegeben werden
double calc_GaußElling_polygon_surface(double x[], double y[], int X_LENGTH, int Y_LENGTH) {
	if ((x == NULL) || (y == NULL)) return 0; // auf leere Argumente testen
	int n = getMathMinimum(X_LENGTH, Y_LENGTH); // Anzahl der Ecken des Polygons
	if (n < 3) return 0; // ein Polygon hat mindestens drei Eckpunkte
	double a = 0.0;
	for (size_t i = 0; i < n; i++)
	{
		a += (y[i] + y[(i + 1) % n]) * (x[i] - x[(i + 1) % n]);
	}
	return abs(a / 2.0);
}

int pnpoly(int nvert, double* vertx, double* verty, double testx, double testy)
{
	int i, j, c = 0;
	for (i = 0, j = nvert - 1; i < nvert; j = i++) {
		if (((verty[i] > testy) != (verty[j] > testy)) &&
			(testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i]))
			c = !c;
	}
	return c;
}

int main()
{
	// variables for reading the measurements from file
	FILE* fp;
	size_t len = 0;
	char resp;

	double x_t[] = { 1.0, 5.0, -3.0, 1.0 };
	double y_t[] = { 0.0, 4.0, 8.0, 0.0 };

	printf("\nLength: %d", ARRAY_SIZE(x_t));
	printf("\nMath.Min: %d", getMathMinimum(ARRAY_SIZE(x_t), ARRAY_SIZE(y_t)));
	double x[3];
	double y[3];

	// open the input file "polygon.txt" for reading
	fp = fopen(PATH "polygon.txt", "r");
	if (fp == NULL)
	{
		// if file could not be opened (wrong path, not readable, ...)
		// output a short message and immediately exit
		printf("\nEingabedatei kann nicht geoeffnet werden.\n");
		scanf("%c", &resp);
		exit(EXIT_FAILURE);
	}

	// print program header
	printf("\n\nProgramm zur Berechnung eines Polygons\n");
	printf("--------------------------------------------------------\n");

	// the following loop reads a new value in every iteration
	// until the end of the file or some invalid token is found
	int i = 0;

	while (1)
	{
		len = fscanf(fp, "%lf %lf", &x[i], &y[i]);

		if (len == EOF)
			break;
		else if (len == 0) {
			printf("Unerwartetes Zeichen in der Eingabedatei.");
			scanf("%c", &resp);
			exit(EXIT_FAILURE);
		}
		printf("Lese Eckpunkt: %6.2f/%6.2f\n", x[i], y[i]);
		i++;
	}

	// output results
	printf("\nErgebnisse:\n");
	printf("\n%f m%c", calc_GaußElling_polygon_surface(x_t, y_t, ARRAY_SIZE(x_t), ARRAY_SIZE(y_t)), 253);
	printf("\n%f m%c", calc_GaußElling_polygon_surface(x, y, ARRAY_SIZE(x), ARRAY_SIZE(y)), 253);

	printf("\n-----------\n\n");

	// finally close the input file and clean up memory
	fclose(fp);

	// wait for user input before closing terminal
	scanf("%c", &resp);
}