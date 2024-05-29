#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

float mini(float* arr, int size); //najmanj�a vrednost v arrayu
float maxi(float* arr, int size); //najve�ja vrednost v arrayu
void swap(float* v1, float* v2);  //zamenja vrednost dveh spremenljivk
float average(float* arr, int size); //povpre�je
void bubbleSort_Up(float* arr, int size); //sortira od najmanj�ega do najve�jetga
void bubbleSort_Down(float* arr, int size); // sortira od najve�jega do manj�ega
void printArray(float* arr, int size); //izpi�e array v konzolo
float mediana(float* arr, int size); //izra�una mediano
float deviacija(float* arr, int size); //izra�una standardno deviacijo
int randomInt(int low, int high); //vrne naklju�no int vrednost na intervalu (low, high)
float* generateArr(int size, int low, int high); //tvori naklju�n array: size - kolko elementov, low - najmanj�a vrednost, high - najve�ja vrednost
void normaliziraj(float lowerBount, float upperBount, float* arr, int size); //normalizira array med vrednosti lowBount in highBount