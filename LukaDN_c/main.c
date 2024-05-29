#include <stdio.h>
#include "knjiznica.h"
int main() {
    srand(time(NULL));
    int size = 4;
    float* arr = generateArr(size, 0, 10);
    printf("Zacetni array: \n");
    printArray(arr, size);

    float minimum = mini(arr, size);
    printf("Min: %f\n", minimum);

    float maximum = maxi(arr, size);
    printf("Max: %f\n", maximum);

    float avg = average(arr, size);
    printf("Povprecje: %f\n", avg);

    printf("Sortiran arr - navzgor: \n");
    bubbleSort_Up(arr, size);
    printArray(arr, size);

    printf("Sortiran arr - navzdol: \n");
    bubbleSort_Down(arr, size);
    printArray(arr, size);

    float medianaa = mediana(arr, size);
    printf("Mediana: %f\n", medianaa);

    float stdDev = deviacija(arr, size);
    printf("Standardna deviacija/odklon: %f\n", stdDev);

    printf("Normaliziran arr med 2 in 3: \n");
    normaliziraj(2, 3, arr, size);
    printArray(arr, size);

    return 0;
}