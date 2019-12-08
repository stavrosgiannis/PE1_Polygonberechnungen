#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define ARRAY_SIZE( array ) ( sizeof( array ) / sizeof( array[0] ) )

//index 1 - X; index 2 - Y
double center_values[2];

//Anzahl der Points
int countPoints = 0;

//User Input von einem Punkt
double INPUT_CHECK_POINTS[2];

//directory	path string
char cwd[100];

//Summenbildung der Polygon Fläche
double get_polygon_surface(double x[], double y[]) {
	if ((x == NULL) || (y == NULL)) return 0; // auf leere Argumente testen
	int n = countPoints; // Anzahl der Ecken des Polygons
	if (n < 3) return 0; // ein Polygon hat mindestens drei Eckpunkte
	double a = 0.0;
	for (size_t i = 0; i < n; i++)
	{
		a += (y[i] + y[(i + 1) % n]) * (x[i] - x[(i + 1) % n]);
	}
	return (a / 2.0);
}

//Berechnung des Polygon Schwerpunkts
double get_polygon_Schwerpunkt(double x[], double y[]) {
	if ((x == NULL) || (y == NULL)) return 1; // auf leere Argumente testen
	int n = countPoints;
	if (n < 3) return 1; // ein Polygon hat mindestens drei Eckpunkte
	for (size_t i = 0; i < countPoints; i++)
	{
		center_values[0] += (x[i] + x[(i + 1) % n]) * ((x[i] * y[(i + 1) % n]) - (x[(i + 1) % n] * y[i]));
		center_values[1] += (y[i] + y[(i + 1) % n]) * ((x[i] * y[(i + 1) % n]) - (x[(i + 1) % n] * y[i]));
	}

	center_values[0] = center_values[0] / (6 * get_polygon_surface(x, y));
	center_values[1] = center_values[1] / (6 * get_polygon_surface(x, y));
	return 0;
}

//Even-Odd bestimmen ob der punkt innerhalb/außerhalb ist
int pnpoly(int nvert, double* vertx, double* verty, double testx, double testy)
{
	int i, j, c = 0;
	for (i = 0, j = nvert - 1; i < nvert; j = i++) {
		if (((verty[i] > testy) != (verty[j] > testy)) && (testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i]))
			c = !c;
	}
	return c;
}

//Bestimmung des Workspaces für den File Path
char getDIR() {
#include <io.h>

	char* getcwd(char* buf, size_t size);
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("Current working directory: %s\n", cwd);
		return cwd;
	}
	else {
		printf("getcwd() error");
		return "";
	}
}

int main()
{
	// variables for reading the measurements from file
	FILE* fp;
	size_t len = 0;
	char resp;

	double INPUT_x_coordinates[100];
	double INPUT_y_coordinates[100];

	// open the input file "polygon.txt" for reading
	getDIR();
	printf("Full Path: %s\n", strcat(cwd, "\\polygon.txt"));
	fp = fopen(cwd, "r");
	if (fp == NULL)
	{
		// if file could not be opened (wrong path, not readable, ...)
		// output a short message and immediately exit
		printf("\nBitte vergewissere dich, dass die 'polygon.txt' im oben angegebenen Pfad liegt!\n");
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
		len = fscanf(fp, "%lf %lf", &INPUT_x_coordinates[i], &INPUT_y_coordinates[i]);

		if (len == EOF)
			break;
		else if (len == 0) {
			printf("Unerwartetes Zeichen in der Eingabedatei.");
			scanf("%c", &resp);
			exit(EXIT_FAILURE);
		}
		if (len > 100) {
			printf("Es sind nicht mehr als 100 Eckpunkte erlaubt!");
			exit(EXIT_FAILURE);
		}
		printf("Lese Eckpunkt: %6.2f[X]/%6.2f[Y]\n", INPUT_x_coordinates[i], INPUT_y_coordinates[i]);
		i++;
		countPoints++;
	}

	// output results
	printf("\nErgebnisse:");
	get_polygon_surface(INPUT_x_coordinates, INPUT_y_coordinates);
	printf("\nDie Gesamtflaeche betraegt: %f%c", get_polygon_surface(INPUT_x_coordinates, INPUT_y_coordinates), 253);

	get_polygon_Schwerpunkt(INPUT_x_coordinates, INPUT_y_coordinates);
	printf("\nDer Flaechenschwerpunkt liegt bei: %.6f[X]/%.6f[Y]\n\n", center_values[0], center_values[1]);

	printf("--------------------------------------------------------\n");

	//Abfrage der Lochposition
	printf("Bitte geben sie die gewuenschte Lochposition an(x/y):\n");
	scanf("%lf/%lf", &INPUT_CHECK_POINTS[0], &INPUT_CHECK_POINTS[1]);
	//Even-Odd-Berechnung
	if (pnpoly(countPoints, INPUT_x_coordinates, INPUT_y_coordinates, INPUT_CHECK_POINTS[0], INPUT_CHECK_POINTS[1]))
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