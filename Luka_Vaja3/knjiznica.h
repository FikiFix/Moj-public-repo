#pragma once
#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

float mini(float* arr, int size); //najmanjša vrednost v arrayu
float maxi(float* arr, int size); //najveèja vrednost v arrayu
void swap(float* v1, float* v2);  //zamenja vrednost dveh spremenljivk
float average(float* arr, int size); //povpreèje
void bubbleSort_Up(float* arr, int size); //sortira od najmanjšega do najveèjetga
void bubbleSort_Down(float* arr, int size); // sortira od najveèjega do manjšega
void printArray(float* arr, int size); //izpiše array v konzolo
float mediana(float* arr, int size); //izraèuna mediano
float deviacija(float* arr, int size); //izraèuna standardno deviacijo
int randomInt(int low, int high); //vrne nakljuèno int vrednost na intervalu (low, high)
float* generateArr(int size, int low, int high); //tvori nakljuèn array: size - kolko elementov, low - najmanjša vrednost, high - najveèja vrednost
void normaliziraj(float lowerBount, float upperBount, float* arr, int size); //normalizira array med vrednosti lowBount in highBount