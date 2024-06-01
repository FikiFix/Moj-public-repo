#include "knjiznica.h"
#define MAX_LINE_LENGTH 100
#define MAX_FILE_LEN 1500 //kolko vrstic največ ma lahko datoteka

struct floatVector {
	float* floatArr;
	int size;
	float avarige;
};

struct floatVector createFloatVector(int size) { //nardi float vector
	struct floatVector fv;
	fv.floatArr = (float*)malloc(sizeof(float) * size);
	fv.size = 0;
	return fv;
}

void addToFv(struct floatVector* vector, float element) { //doda element v float vector
	int index = vector->size;
	vector->floatArr[index] = element;
	vector->size += 1;
}
void printFv(struct floatVector* vector) { //izpiše float vector
	int size = vector->size;
	for (int i = 0; i < size; i++) {
		printf("%f ", vector->floatArr[i]);
	}printf("\n");
}

float stringToFloat(char* str) { //string pretvori v float
	char* endptr;
	float num = strtof(str, &endptr);
	return num;
}

void readFile(const char* filePath, struct floatVector* vector) { //prebere datoteko
	FILE* file;
	char line[MAX_LINE_LENGTH];

	if (fopen_s(&file, filePath, "r") != 0) {
		perror("Error opening file");
		return;
	}

	while (fgets(line, sizeof(line), file)) {
		float floatVal = stringToFloat(line);
		addToFv(vector, floatVal);
	}

	fclose(file);
}

struct floatVector calculateFunction(struct floatVector* inputVector) { //računa toto funkcijo iz navodil: f(x) = x^2 + 2 ⋅ x + 4,
	int size = inputVector->size;
	struct floatVector outputVector = createFloatVector(size); //to pol vrnemo
	for (int i = 0; i < size; i++) {
		float x = inputVector->floatArr[i];
		float y = x * x + 2 * x + 4; //računam funkcijo
		addToFv(&outputVector, y);
	}
	return outputVector;
}

struct floatVector gX(int size) { //kreira g(x) iz navodil naloge - vektor števil med -1 in 1

	struct floatVector ret = createFloatVector(size); //ta vektor vrnemo pol

	for (int i = 0; i < size; i++) {

		int sign = randomInt(0, 1); //kreiramo predznak. 1 - negativno, 0 - pozitivno

		float value = randomInt(0, 10);
		value = value / 10; //value je število med 0 in 10. Delomo ga z 10, da dobimo vrednost med 0 in 1 na 1 decimalko
		if (sign == 1) {
			value = value * (-1); //če mamo negativen predznak ga dodamo
		}
		addToFv(&ret, value);

	}

	return ret;

}

struct floatVector addVectors(struct floatVector* fv1, struct floatVector* fv2) { //sešteje 2 vektorja
	float buff[2] = { fv1->size, fv2->size };
	int size = mini(buff, 2); //vzamemo manjšo vrednost. To je tolko samo da če slučajno nista enaka da ne crkne program

	struct floatVector ret = createFloatVector(size);
	if (fv1->size != fv2->size) {
		printf("Opozorilo: neenaki dolžini vektorjev. \n");
	}

	for (int i = 0; i < size; i++) {
		float sum = fv1->floatArr[i] + fv2->floatArr[i];
		addToFv(&ret, sum);
	}
	ret.avarige = average(ret.floatArr, size);//povprečje seštetih vektorjev
	return ret;
}


int main() {
	srand(time(NULL)); //seme za naključna števila

	struct floatVector fv = createFloatVector(MAX_FILE_LEN);
	readFile("podatki.txt", &fv);
	bubbleSort_Up(fv.floatArr, fv.size);
	struct floatVector funkcija = calculateFunction(&fv);
	struct floatVector gx = gX(fv.size);
	struct floatVector hx = addVectors(&funkcija, &gx);
	//printFv(&gx);
	printf("Povprecje: %f", hx.avarige); //povprečje seštetih vektorjev


	FILE* file;
	if (freopen_s(&file, "urejeni_podatki.txt", "w", stdout) != 0) { //tu spodaj vbistvu standardni izhod preusmerimo v datoteko
		perror("Ni slo odpret datoteke");							//standardni izhod je to kaj izpisujemo z printf
		return 1;
	}

	printf("Sortirani vhodni podatki: \n\n");
	printFv(&fv);
	printf("\n\n");

	printf("f(x): \n\n");
	printFv(&funkcija);
	printf("\n\n");

	printf("g(x): \n\n");
	printFv(&gx);
	printf("\n\n");

	printf("h(x): \n\n");
	printFv(&hx);
	printf("\n\n");

	printf("Povprecje: %f\n\n", hx.avarige); //povprečje seštetih vektorjev
	printf("\n\n");

	fclose(file);

}