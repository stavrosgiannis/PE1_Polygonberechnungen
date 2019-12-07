#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PATH "C:\\Users\\Stavros\\source\\repos\\PE1_Polygonberechnungen\\PE1_Polygonberechnungen\\Debug\\"
#define ARRAY_SIZE( array ) ( sizeof( array ) / sizeof( array[0] ) )

//index 1 - X; index 2 - Y
double center_values[2];
int countPoints = 0;
double surface = 0;
double INPUT_HOLES[2];

int getMathMinimum(double X_LENGTH, double Y_LENGTH) {
	if (X_LENGTH > Y_LENGTH) return Y_LENGTH;
	if (Y_LENGTH > X_LENGTH) return X_LENGTH;
	if (Y_LENGTH == X_LENGTH) return X_LENGTH;
}

double calc_GauﬂElling_polygon_surface(double x[], double y[]) {
	if ((x == NULL) || (y == NULL)) return 0; // auf leere Argumente testen
	int n = countPoints; // Anzahl der Ecken des Polygons
	if (n < 3) return 0; // ein Polygon hat mindestens drei Eckpunkte
	double a = 0.0;
	for (size_t i = 0; i < n; i++)
	{
		a += (y[i] + y[(i + 1) % n]) * (x[i] - x[(i + 1) % n]);
	}
	surface = abs(a / 2.0);
	return abs(a / 2.0);
}

//Berechnung des Schwerpunkts
double calc_geo_schwerpunkt(double x[], double y[]) {
	if ((x == NULL) || (y == NULL)) return 0; // auf leere Argumente testen
	int n = countPoints;
	if (n < 3) return 0; // ein Polygon hat mindestens drei Eckpunkte
	for (size_t i = 0; i < countPoints; i++)
	{
		center_values[0] += (x[i] + x[i + 1]) * ((x[i] * y[i + 1]) - (x[i + 1] * y[i]));
		center_values[1] += (y[i] + y[i + 1]) * ((x[i] * y[i + 1]) - (x[i + 1] * y[i]));
	}

	center_values[0] = abs(center_values[0] / (6 * calc_GauﬂElling_polygon_surface(x, y)));
	center_values[1] = abs(center_values[1] / (6 * calc_GauﬂElling_polygon_surface(x, y)));
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

	double x[100];
	double y[100];

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
		printf("Lese Eckpunkt: %6.2f[X]/%6.2f[Y]\n", x[i], y[i]);
		i++;
		countPoints++;
	}

	// output results
	printf("\nErgebnisse:\n");
	calc_GauﬂElling_polygon_surface(x, y);
	printf("\nDie Gesamtflaeche betraegt: %fm%c", surface, 253);

	calc_geo_schwerpunkt(x, y);
	printf("\nDer Flaechenschwerpunkt liegt bei: %.6f[X]/%.6f[Y]\n\n", center_values[0], center_values[1]);

	printf("--------------------------------------------------------\n");

	//Abfrage der Lochposition
	printf("Bitte geben sie die gewuenschte Lochposition an(x/y):\n");
	scanf("%lf/%lf", &INPUT_HOLES[0], &INPUT_HOLES[1]);
	//Even-Odd-Berechnung
	if (pnpoly(countPoints, x, y, INPUT_HOLES[0], INPUT_HOLES[1]))
	{
		printf("Der gegebene Punkt befindet sich innerhalb des Polygons");
	}
	else printf("Der gegebene Punkt befindet sich ausserhalb des Polygons");

	// finally close the input file and clean up memory
	fclose(fp);

	// wait for user input before closing terminal
	scanf("%c", &resp);
	while (getchar() != '\n');
}