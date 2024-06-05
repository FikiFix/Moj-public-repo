#include "knjiznica.h"
#include <float.h>  // For FLT_MAX

float mini(float* arr, int size) {

    float min_value = arr[0];
    for (int i = 1; i < size; i++) {
        if (min_value > arr[i]) {
            min_value = arr[i];
        }
    }
    return min_value;
}

float maxi(float* arr, int size) {
    float maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (maxVal < arr[i]) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

void swap(float* a, float* b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

float average(float* arr, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum / size;
}
void bubbleSort_Up(float* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void bubbleSort_Down(float* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}
void printArray(float* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%f ", arr[i]);
    }printf("\n");
}

float mediana(float* arr, int size) {

    float* arr_copy = (float*)malloc(size * sizeof(float));
    if (arr_copy == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        arr_copy[i] = arr[i];
    }

    bubbleSort_Up(arr_copy, size);

    bool lihaDolzina = size % 2; // 1 - odd, 0 - even

    float median;
    if (lihaDolzina) {
        int sredina = size / 2;
        median = arr_copy[sredina];
    }
    else { 
        int midd1 = size / 2 - 1;
        int midd2 = midd1 + 1;
        median = (arr_copy[midd1] + arr_copy[midd2]) / 2.0;
    }

    free(arr_copy);

    return median;
}

float deviacija(float* arr, int size) {
    float avg = average(arr, size);
    float squareSum = 0;
    for (int i = 0; i < size; i++) {
        float diff = arr[i] - avg;
        squareSum += diff * diff;
    }
    return sqrt(squareSum / size);
}

int randomInt(int low, int high) {

    int randomNumber = rand() % (high - low + 1) + low;

    return randomNumber;
}

float* generateArr(int size, int low, int high) {
    float* arr = malloc(sizeof(float) * size);

    for (int i = 0; i < size; i++) {
        int randomIntValue = randomInt(low, high);
        arr[i] = (float)randomIntValue;
    }
    return arr;
}

void normaliziraj(float lowerBount, float upperBount, float* arr, int size) {

    float minV = mini(arr, size);
    float maxV = maxi(arr, size);
    for (int i = 0; i < size; i++) {
        float buff = lowerBount + ((arr[i] - minV) / (maxV - minV)) * (upperBount - lowerBount); //formula iz interneta
        arr[i] = buff;
    }
}