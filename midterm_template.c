#include <stdio.h>
#include <stdlib.h>

#define N 10 // Do NOT change this line!

FILE *fp;

typedef struct point2d
{
	int xVal;
	int yVal;
} point2d;

void fill(char filename[], point2d P[])
{
	/*
	This function opens and reads from the input file.  You 
	should close the file when you are done with it.  Read 
	the points into the array of structures in this function.

	Don't forget to check if the file name is valid.
	*/

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Error, file cannot be opened!\n");
		exit(1);
	}

	int i = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%d %d", &P[i].xVal, &P[i].yVal);
		i++;

		// for testing
		//printf("%d: (%2d, %2d)\n", i, P[i].xVal, P[i].yVal);
	}

	fclose(fp);
}

int getdist(point2d p, point2d q)
{
	/*
	This function gets the distance between 2 points and
	returns that value.

	Yes, you need to do some math here...
	*/
	// formula is sqrt(Px-Qx)^2 + (Py-Qy)^2
	return (((p.xVal - q.xVal) * (p.xVal - q.xVal)) + (p.yVal - q.yVal) * ((p.yVal - q.yVal)) / 2);
}

void closest(point2d P[], int G[2 * N][2 * N])
{
	/*
	This function finds the 2 points that are the closest.

	You should call the getdist() function from inside here.
	*/

	// find the 2 points that are closest

	int minDistance = getdist(P[0], P[1]);
	point2d p1 = P[0];
	point2d p2 = P[1];
	for (int i = 0; i < N; ++i)
	{
		for (int j = i + 1; j < N; ++j)
		{
			int distance = getdist(P[i], P[j]);
			if (distance < minDistance)
			{
				minDistance = distance;
				p1 = P[i];
				p2 = P[j];
			}
		}
	}
	// set values in G to unique values
	G[p1.xVal][p1.yVal] = 2;
	G[p2.xVal][p2.yVal] = 2;
}

void grid(point2d P[], int G[2 * N][2 * N])
{
	/*
	This function will transfer all the points from your
	structure into a 2D array used as the grid.

	You will call the closest() function from inside here.
	
	*/
	// set G for each of the N points

	for (int i = 0; i < N; ++i)
	{
		G[P[i].xVal][P[i].yVal] = 1;
	}

	closest(P, G);
}

void printpoints(char filename[], point2d P[])
{
	/*
	This function will print off the list of all the 
	points you have in the following form:

	num: ( x, y)

	ex.
	0: ( 4, 1)

	** Note the spacing!

	You need to open the output file here and write to it.
	*/
	fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("Error, file cannot be opened!\n");
		exit(1);
	}

	for (int i = 0; i < N; ++i)
	{

		fprintf(fp, "%d: (%2d, %2d)\n", i, P[i].xVal, P[i].yVal);
	}
	fclose(fp);
}

void printgridxy(char filename[], int G[2 * N][2 * N])
{
	fp = fopen(filename, "a");
	if (fp == NULL)
	{
		printf("Error, file cannot be opened!\n");
		exit(1);
	}
	for (int i = 0; i < 50; ++i)
	{
		fprintf(fp, "-");
	}
	fprintf(fp, "\n");

	/*
	This function will print out your 2D array (the grid)

	Use ' ' for spots without a point,
	use '*' for spots with a point,
	use 'X' for the 2 points that are closest.

	Put 1 space between each element, for example you should
	print "* " instead of just "*".


	You should also have a top and bottom made of 50 hyphens (-)

	This should be printed to the same file as the points were.
		Be careful not to overwrite the file!
	*/
	for (int row = 0; row < N * 2; ++row)
	{
		for (int col = 0; col < N * 2; ++col)
		{
			int x = col;
			int y = (2 * N) - row;
			if (G[x][y] == 1)
			{
				fprintf(fp, "* ");
			}
			else if (G[x][y] == 2)
			{
				fprintf(fp, "X ");
			}
			else
			{
				fprintf(fp, " ");
			}
		}
		fprintf(fp, "\n");
	}

	for (int i = 0; i < 50; ++i)
	{
		fprintf(fp, "-");
	}
	fprintf(fp, "\n");

	fclose(fp);
}

int main(int argc, char *argv[])
{
	/*
	Do not change anything in main!  Also do not change the #define
	at the top of the program.

	There is one exception to this, you may change the "type" for the
	structure you made if you don't use my naming scheme.
	*/
	if (argc != 3)
	{
		printf("Syntax Error: ./a.out <infile> <outfile>\n");
		exit(1);
	}

	point2d P[N]; //  <-- This is the only line you are allowed to change.
	int G[2 * N][2 * N] = {0};

	fill(argv[1], P);
	grid(P, G);
	printpoints(argv[2], P);
	printgridxy(argv[2], G);

	return 0;
}