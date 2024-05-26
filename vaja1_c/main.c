#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>


#define MAX_LINE_LENGTH 256
#define MAX_WORD_COUNT 100
#define MAX_WORD_LEN 100
#define FILE_PATH "besede.txt"

struct WordArr {
	char stringArr[MAX_LINE_LENGTH][MAX_WORD_LEN];
	int count; //koliko elementov mam v arr
	int nextIndex; //index za dodajanje novega elementa

};
struct WordArr newWordArr() { //konstruktor za word arr
	struct WordArr a;
	a.count = 0;
	a.nextIndex = 0;
	return a;
}

void addWord(struct WordArr* array, const char* str) {
	if (array->nextIndex < MAX_WORD_COUNT) {
		strncpy_s(array->stringArr[array->nextIndex], sizeof(array->stringArr[array->nextIndex]), str, _TRUNCATE);
		array->nextIndex += 1;
		array->count += 1;
	}
	else {
		printf("Array is full, cannot add more words.\n");
	}
}

bool exists(struct WordArr* array, const char* str) {
	int iterLen = array->count;
	for (int i = 0; i < iterLen; i++) {
		int cmp = strcmp(array->stringArr[i], str);
		if (cmp == 0) {
			return true;
		}
	}
	return false;
}


void printWords(struct WordArr* array) { //izpiše vse besede
	int iterLen = array->count;
	for (int i = 0; i < iterLen; i++) {
		printf("%s\n", array->stringArr[i]);
	}
}
void readFile(const char* filePath, struct WordArr* wordArr) { //prebere datoteko
	FILE* file;
	char line[MAX_LINE_LENGTH];

	if (fopen_s(&file, filePath, "r") != 0) {
		perror("Error opening file");
		return;
	}

	while (fgets(line, sizeof(line), file)) {
		
		addWord(wordArr, line);
	}

	fclose(file);
}

int getRandomNumber(int max) {
	// Nastavimo seme generatorja nakljuènih števil
	srand(time(NULL));

	// Generiramo nakljuèno število na intervalu [0, max)
	int randomNumber = rand() % max;

	return randomNumber;
}

void appendWordToFile(const char* filePath, const char* word, struct WordArr* wordArr) {
	if (exists(wordArr, word)) {
		printf("Beseda je ze noter!\n");
		return;
	};
	FILE* file;
	errno_t err = fopen_s(&file, filePath, "a");
	if (err != 0) {
		perror("Error opening file");
		return;
	}
	fprintf(file, "%s", word);
	fclose(file);
}

void appendPrompt(struct WordArr* array) { //toèka 3 iz navodil
	printWords(array);
	printf("Ali zelis vstaviti besedo v datoteko? y + enter za DA");
	char eval[10];  //damo eval 10 da ponesreèi ne pride do buffer owerflowa. Paè èe se zatipkamo al pa kaj takega
	char input[40];
	fgets(eval, sizeof(eval), stdin);
	if (eval[0] == 'y') {
		printf("Vnesite besedo: \n");
		fgets(input, sizeof(input), stdin);
		appendWordToFile(FILE_PATH, input, array);
		return;
	}
	printf("Te pa nic :)\n");
}

char* getRandomWord(struct WordArr* array) {
	int random = getRandomNumber(array->count);
	return array->stringArr[random];
}

char* hideWord(const char* word, int len) {
	char* hidden = malloc(len + 1);
	if (hidden == NULL) {
		printf("Memory allocation failed\n");
		return NULL;
	}

	for (int i = 0; i < len; i++) {
		hidden[i] = '_';
	}
	hidden[len] = '\0'; // Èe maš probleme fukni vun. Nvm zkj dobim buffer owerrun kot warning

	printf("%s\n", hidden); 

	return hidden;
}

bool evalUserInput(char* word, char* hidden, char chr, int len) {
	bool ret = false;
	for (int i = 0; i < len; i++) {
		if (word[i] == chr) {
			hidden[i] = chr;
			ret = true;
		}
	}
	return ret;
}
void processWord(char* word) {
	int length = strlen(word) - 1;
	printf("Odgovor: ");
	printf("%s\n", word);
	char* hidden = hideWord(word, length);

	int count = length;
	int chances = 10;
	char input[5]; //damo input 5 da ponesreèi ne pride do buffer owerflowa. Paè èe se zatipkamo al pa kaj takega
	while (count > 0 && chances > 0) {
		printf("Vnesite crko: \n");
		fgets(input, sizeof(input), stdin);
		bool eval = evalUserInput(word, hidden, input[0], length);
		if (eval) {
			count--;
		}
		else {
			chances--;
		}

		printf("%s\n", hidden);

	}


}
int main() {
	struct WordArr wordArr = newWordArr();
	readFile(FILE_PATH, &wordArr);
	appendPrompt(&wordArr);
	char* word = getRandomWord(&wordArr);
	processWord(word);
}