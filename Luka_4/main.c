#include <stdlib.h>
#include <stdio.h>
#include "knjiznica.h"

#define MAX_LINE_LENGTH 100
#define MAX_FILE_ROWS 500

struct FloatVector2d {
	int* leta;
	float* povpTmp;
	float* padavine;
	int* sneg;
	int size;

};
struct FloatVector2d fv2dConstructor(int allocSize) {
	struct FloatVector2d fv;
	fv.leta = malloc(sizeof(int) * allocSize);
	fv.povpTmp = malloc(sizeof(float) * allocSize);
	fv.padavine = malloc(sizeof(float) * allocSize);
	fv.sneg = malloc(sizeof(int) * allocSize);
	fv.size = 0;
	return fv;
}
void addRow(struct FloatVector2d* fv, int leto, float povpTmp, float padavine, float sneg) {
	int index = fv->size;
	fv->leta[index] = leto;
	fv->povpTmp[index] = povpTmp;
	fv->padavine[index] = padavine;
	fv->sneg[index] = sneg;
	fv->size += 1;
}

void fv2dDestructor(struct FloatVector2d* fv) {
	free(fv->leta);
	free(fv->padavine);
	free(fv->povpTmp);
	free(fv->sneg);
}
void printTable(struct FloatVector2d* fv) {
	printf("Leto:  Povprecna temperature (*C):   Padavine (mm):  St. dni s snezno odejo:\n");
	for (int i = 0; i < fv->size; i++) {
		printf("%d      %f                  %f      %d  \n", fv->leta[i], fv->povpTmp[i], fv->padavine[i], fv->sneg[i]);
	}
}

void sortVectorByTemp(struct FloatVector2d* fv) {
	int size = fv->size;
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (fv->povpTmp[j] > fv->povpTmp[j + 1]) {
				swap(&fv->povpTmp[j], &fv->povpTmp[j + 1]);
				swap(&fv->leta[j], &fv->leta[j + 1]);
				swap(&fv->padavine[j], &fv->padavine[j + 1]);
				swap(&fv->sneg[j], &fv->sneg[j + 1]);
			}
		}
	}
}

void readFile(const char* filePath, struct FloatVector2d* fv) { //prebere datoteko
	FILE* file;
	char line[MAX_LINE_LENGTH];

	if (fopen_s(&file, filePath, "r") != 0) {
		perror("Error opening file");
		return;
	}
	fgets(line, sizeof(line), file);
	while (fgets(line, sizeof(line), file)) {

		int leto, sneg;
		float povpTmp, padavine;
		sscanf_s(line, "%d, %f, %f, %d", &leto, &povpTmp, &padavine, &sneg);
		addRow(fv, leto, povpTmp, padavine, sneg);
	}

	fclose(file);
}

void minMaxIndex(float* arr, int size, int* minIndex, int* maxIndex) {
	*minIndex = 0;
	*maxIndex = 0;
	for (int i = 1; i < size; i++) {
		if (arr[i] > arr[*maxIndex]) {
			*maxIndex = i;
		}
		if (arr[i] < arr[*minIndex]) {
			*minIndex = i;
		}
	}
}


int main() {
	FILE* file;
	if (freopen_s(&file, "statisticna_analiza.txt", "w", stdout) != 0) { //preusmerimo standardni izhod v datoteko
		perror("Ni slo odpret datoteke");							
		return 1;
	}

	struct FloatVector2d vector = fv2dConstructor(MAX_FILE_ROWS);
	readFile("podatki.txt", &vector);
	printTable(&vector);
	int size = vector.size;

	float medianaTmp = mediana(vector.povpTmp, size);
	float povprecjeTmp = average(vector.povpTmp, size);
	float stdDev = deviacija(vector.povpTmp, size);
	printf("Mediana temperatur: %f\n", medianaTmp);
	printf("Povprecje temperatur: %f\n", povprecjeTmp);
	printf("Deviacija temperatur: %f\n", stdDev);

	sortVectorByTemp(&vector);
	int tempMin1 = vector.leta[0];
	int tempMin2 = vector.leta[1];
	int tempMin3 = vector.leta[2];
	int tempMax1 = vector.leta[size - 1];
	int tempMax2 = vector.leta[size - 2];
	int tempMax3 = vector.leta[size - 3];
	printf("Najtoplejsa leta: %d, %d, %d\n", tempMax1, tempMax2, tempMax3);
	printf("Najhladnejsa leta: %d, %d, %d\n", tempMin1, tempMin2, tempMin3);


	float medianaPadavine = mediana(vector.padavine, size);
	float povprecjePadavine = average(vector.padavine, size);
	float stdDevPadavine = deviacija(vector.padavine, size);
	printf("Mediana padavin: %f\n", medianaPadavine);
	printf("Povprecje padavin: %f\n", povprecjePadavine);
	printf("Deviacija padavin: %f\n", stdDevPadavine);
	int minIndex;
	int maxIndex;
	minMaxIndex(vector.padavine, size, &minIndex, &maxIndex);
	printf("Najbolj suho leto: %d\n", vector.leta[minIndex]);
	printf("Najbolj mokro leto: %d\n", vector.leta[maxIndex]);

	normaliziraj(0, 365, vector.sneg, size);
	minMaxIndex(vector.sneg, size, &minIndex, &maxIndex);
	printf("Leto s najvec snega: %d\n", vector.leta[maxIndex]);
	printf("Leto s najmanj snega: %d\n", vector.leta[minIndex]);

	fv2dDestructor(&vector);
	fclose(file);

}