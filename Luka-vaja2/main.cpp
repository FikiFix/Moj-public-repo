#include <iostream>
#include "knjiznica.h"
int main() {
    std::vector<float> numbers = {1,4,5,2,3,6};
    std::cout <<"Max vrednost: " <<max(&numbers) << "\n";
    std::cout <<"Min vrednost: " <<min(&numbers) << "\n";
    std::cout << "Povprecje: " << avarige(&numbers) << "\n";
    bubbleSortUp(&numbers);
    std:: cout << "Bubble sort navzgor: \n";
    printVector(&numbers);
    bubbleSortDown(&numbers);
    std:: cout << "Bubble sort navzdol: \n";
    printVector(&numbers);
    std::cout <<"Mediana: "<< mediana(&numbers) << "\n";
    std::cout << "Standardni odklon: " << standardniOdklon(&numbers) << "\n";
    std::vector<float> norm = nomaliziraj(1, 2, &numbers);
    std:: cout << "Normalizacija med 1 in 2: \n";
    printVector(&norm);
    std:: cout << "Nakljucni vektor dolzine 10, na intervalu [1,7]: \n";
    std::vector<float> randVect = randomVector(10, 1, 7);
    printVector(&randVect);
    return 0;
}
