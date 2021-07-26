#include<stdio.h>
#include <fstream>
#include<stdlib.h>
#include<GL/glut.h>
#include <iostream>
#include<Windows.h>
#pragma warning(disable:4996)
using namespace std;


int a[250];
int count1 = 0;
char random[30] = "random250.txt";
char sorted[30] = "sorted250.txt";
char reversed[30] = "reversed250.txt";
int random250[250], sorted250[250], reversed250[250];
int selectSort = 0;
int L[250], R[250];

void display1(int);
void mergeSort(int[], int, int);
void merge(int a[], int l, int m, int r);
void quickSort(int[], int, int);
void swap(int*, int*);
int partition(int[], int, int);
void keyboard(char, int, int);
void copy();



//display contents of array for debugging purposes 
void displayArray(int a[])
{
	for (int i = 0; i < 250; i++)
	{
		printf("%d\n", a[i]);
	}
}
//reading from file 
void readFile(char Fname[], int storage[])
{

	ifstream take(Fname);
	for (int i = 0; i < 250; i++)
	{
		take >> storage[i];
	}

}
//function to load dataset from file having 250 numbers in random, ascending and descending order.

void Load()
{
	readFile(random, random250);
	readFile(sorted, sorted250);
	readFile(reversed, reversed250);
}


void myInit(void)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1538, 0, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void bsort(void)
{
	int i = 0, j = 0, tmp;
	for (i = 0; i < 250; i++) {   // loop n times - 1 per element
		for (j = 0; j < 250 - i - 1; j++) { // last i elements are sorted already
			display1(j + 1);
			if (a[j] > a[j + 1]) {
				count1++;// swap if order is broken
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}

		}
		if (count1 == 0)
			return;
	}
}





void merge(int a[], int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;

	// Create temp arrays


	// Copy data to temp arrays L[] and R[]
	for (int i = 0; i < n1; i++)
		L[i] = a[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = a[m + 1 + j];

	// Merge the temp arrays back into arr[l..r]

	// Initial index of first subarray
	int i = 0;

	// Initial index of second subarray
	int j = 0;

	// Initial index of merged subarray
	int k = l;

	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			a[k] = L[i];
			i++;
		}
		else {
			a[k] = R[j];
			j++;
		}
		count1++;
		display1(k);
		k++;
	}

	// Copy the remaining elements of
	// L[], if there are any
	while (i < n1) {
		a[k] = L[i];
		i++;
		display1(k);
		k++;

	}


	// Copy the remaining elements of
	// R[], if there are any
	while (j < n2) {
		a[k] = R[j];
		j++;
		display1(k);
		k++;
	}
}



void mergeSort(int a[], int l, int r) {
	if (l >= r) {
		return;//returns recursively
	}
	int m = l + (r - l) / 2;
	mergeSort(a, l, m);
	mergeSort(a, m + 1, r);
	merge(a, l, m, r);
}




void swap(int* a, int* b)
{
	count1++;
	int t = *a;
	*a = *b;
	*b = t;
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(int a[], int low, int high)
{
	int pivot = a[high]; // pivot
	int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot
		if (a[j] < pivot)
		{
			display1(j);
			i++; // increment index of smaller element
			swap(&a[i], &a[j]);
		}
	}
	swap(&a[i + 1], &a[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int a[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(a, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(a, low, pi - 1);
		quickSort(a, pi + 1, high);
	}
}






//function to display the array elements in the 
//form of lines

void display1(int j)
{

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	char ascending[] = "Ascending ";
	char random[] = "Random";
	char descending[] = "Descending";
	char swap[] = "Swaps:";
	char comparision[] = "Comparisions:";
	char mergesort[] = "Merge Sort";
	char bubblesort[] = "Bubble Sort";
	char quicksort[] = "Quick Sort";

	glColor3f(1, 0, 0);

	glRasterPos2i(600, 950);

	if (selectSort == 1 || selectSort == 2 || selectSort == 3) {
		for (int i = 0; i < strlen(bubblesort); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, bubblesort[i]);
	}
	else if (selectSort == 4 || selectSort == 5 || selectSort == 6) {
		for (int i = 0; i < strlen(mergesort); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, mergesort[i]);
	}
	else if (selectSort == 7 || selectSort == 8 || selectSort == 9) {
		for (int i = 0; i < strlen(quicksort); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, quicksort[i]);
	}



	glRasterPos2i(1300, 950);

	if (selectSort == 1 || selectSort == 4 || selectSort == 7) {
		for (int i = 0; i < strlen(ascending); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ascending[i]);
	}
	else if (selectSort == 2 || selectSort == 5 || selectSort == 8) {
		for (int i = 0; i < strlen(random); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, random[i]);
	}
	else if (selectSort == 3 || selectSort == 6 || selectSort == 9) {
		for (int i = 0; i < strlen(descending); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, descending[i]);
	}


	//displaying comparisions and swaps
	if (selectSort == 4 || selectSort == 5 || selectSort == 6)
	{
		glRasterPos2i(1300, 900);
		for (int i = 0; i < strlen(comparision); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, comparision[i]);
		}

		glRasterPos2i(1450, 900);
		char s[256];
		sprintf(s, "%d", count1);
		for (int i = 0; i < strlen(s); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
		}
	}
	else
	{
		glRasterPos2i(1300, 900);
		for (int i = 0; i < strlen(swap); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, swap[i]);
		}

		glRasterPos2i(1370, 900);
		char s[256];
		sprintf(s, "%d", count1);
		for (int i = 0; i < strlen(s); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
		}
	}



	float mul;
	if (selectSort == 2 || selectSort == 5 || selectSort == 8)
		mul = 1.4;
	else
		mul = 2.5;

	glLineWidth(2);
	//sleep called for n*logn time complexity
	if (selectSort == 1 || selectSort == 4 || selectSort == 5 || selectSort == 6 || selectSort == 8)
		_sleep(1);


	//displaying lines
	glBegin(GL_LINES);
	for (int i = 0; i < 250; i++) {
		glColor3f(1, 0, 0);
		if (j == 251)
			glColor3f(1, 1, 0);
		if (i == j)
			glColor3f(0, 0, 1);
		glVertex2f(120 + i * 5, 150);
		glVertex2f(120 + i * 5, 150 + a[i] * mul);
	}
	glEnd();
	glFlush();
}


//copying the original array elements 
void copy()
{
	for (int i = 0; i < 250; i++)
	{
		if (selectSort == 1 || selectSort == 4 || selectSort == 7)
			a[i] = sorted250[i];
		else if (selectSort == 2 || selectSort == 5 || selectSort == 8)
			a[i] = random250[i];
		else
			a[i] = reversed250[i];
	}
}


//main display function
void display()
{
	glClearColor(0, 0, 0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	glColor3f(1, .7, 0);
	glVertex2i(0, 0);
	glColor3f(1, 0.5, 0);
	glVertex2i(1538, 0);
	glColor3f(1, 0.5,0);
	glVertex2i(1538, 1000);
	glColor3f(1, .4, 0);
	glVertex2i(0, 1000);
	glEnd();




	int x = 10;
	for (int i = 1; i < 30; i++)
	{
		int elem = rand() % 50;
		glColor3f(1, 0, 0);
		glEnable(GL_POLYGON_MODE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_QUADS);
		glVertex2f(x + 40, 150);
		glVertex2f(x + 40, 150 + elem * 7);
		glVertex2f(x + 25, 150 + elem * 7);
		glVertex2f(x + 25, 150);
		glEnd();

		x += 60;
		glFlush();

	}


	//text--------------------------

	char subject[] = "COMPUTER GRAPHICS";
	char title[] = "VISUALIZATION OF SORTING ALGORITHMS";
	char usn1[] = "USN:1RN18CS087";
	char usn2[] = "USN:1RN18CS088";
	char name2[] = "Rohith N";
	char name1[] = "Rohit Rajesh Joshi";
	glColor3f(0, 0, 1);

	glRasterPos2i(630, 900);
	for (int i = 0; i < strlen(subject); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, subject[i]);
	}

	glRasterPos2i(500, 850);
	for (int i = 0; i < strlen(title); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, title[i]);
	}

	glRasterPos2i(300, 700);
	for (int i = 0; i < strlen(usn1); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, usn1[i]);
	}

	glRasterPos2i(300, 650);
	for (int i = 0; i < strlen(name1); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, name1[i]);
	}

	glRasterPos2i(1000, 700);
	for (int i = 0; i < strlen(usn2); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, usn2[i]);
	}

	glRasterPos2i(1000, 650);
	for (int i = 0; i < strlen(name2); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, name2[i]);
	}

	copy();



	//selecting the sorting algorithms and array type
	if (selectSort == 1 || selectSort == 2 || selectSort == 3) {
		count1 = 0;
		display1(0);
		bsort();
		display1(251);
	}

	else if (selectSort == 4 || selectSort == 5 || selectSort == 6) {
		count1 = 0;
		display1(0);
		mergeSort(a, 0, 249);
		display1(251);
	}
	else if (selectSort == 7 || selectSort == 8 || selectSort == 9) {
		count1 = 0;
		display1(0);
		quickSort(a, 0, 249);
		display1(251);
	}

	glFlush();

}


void keyboard(unsigned char key, int x, int y)
{

	if (key == 'r')
		selectSort = 0;
	else if (key == 'q')
		exit(0);

	glutPostRedisplay();

}
void menufunc(int value)
{
	if (value == 0)
		exit(0);
	selectSort = value;
	glutPostRedisplay();
}
int main(int argc, char** argv)
{

	bool played = PlaySound("dropit_silentpartner.wav", NULL, SND_LOOP | SND_ASYNC);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1538, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Sort");
	glutDisplayFunc(display);
	Load();

	glutKeyboardFunc(keyboard);

	int menu2 = glutCreateMenu(menufunc);
	glutAddMenuEntry("Ascending ", 1);
	glutAddMenuEntry("Random", 2);
	glutAddMenuEntry("Descending", 3);

	int menu3 = glutCreateMenu(menufunc);
	glutAddMenuEntry("Ascending", 4);
	glutAddMenuEntry("Random", 5);
	glutAddMenuEntry("Descending", 6);

	int menu4 = glutCreateMenu(menufunc);
	glutAddMenuEntry("Ascending", 7);
	glutAddMenuEntry("Random", 8);
	glutAddMenuEntry("Descending", 9);

	int menu1 = glutCreateMenu(menufunc);
	glutAddSubMenu("Bubble Sort", menu2);
	glutAddSubMenu("Merge Sort", menu3);
	glutAddSubMenu("Quick Sort", menu4);
	glutCreateMenu(menufunc);
	glutAddSubMenu("Algorithms", menu1);
	glutAddMenuEntry("Exit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	myInit();

	glutMainLoop();
	return 1;
}