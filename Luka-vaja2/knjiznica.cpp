//
// Created by 38668 on 21. 05. 2024.
//

#include "knjiznica.h"

float max(std::vector<float>* numbers){
    float max = std::numeric_limits<float>::min(); //najmanjša možna vrednost za float
    for(auto&i:*numbers){ //gremo skozi števila. Če je katero večje od max, to število postane max
        if (i>max){
            max = i;
        }
    }
    return max;
}

float min(std::vector<float>* numbers){
    float min = std::numeric_limits<float>::max(); //največja možna vrednost za float
    for(auto&i : *numbers){
        if (i < min){
            min = i;
        }
    }
    return min;
}

float avarige(std::vector<float>* numbers){
    size_t length = numbers->size(); //size_t - podatkovni tip za shranjevanje velikosti. Ista fora ko int, samo bol fancy
    float sum = 0;
    for(auto&i : *numbers){
        sum += i;
    }
    return sum/length;
}

void printVector(std::vector<float>* numbers){
    for(auto&i : *numbers){
        std::cout << i << " ";
    }std::cout << "\n";
}
void bubbleSortUp(std::vector<float>* numbers) {
    size_t size = numbers->size();
    bool swapped;

    for (size_t i = 0; i < size - 1; i++) {
        swapped = false;
        for (size_t k = 0; k < size - i - 1; k++) {
            if ((*numbers)[k] > (*numbers)[k + 1]) {
                std::swap((*numbers)[k], (*numbers)[k + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void bubbleSortDown(std::vector<float>* numbers) {
    size_t size = numbers->size();
    bool swapped;

    for (size_t i = 0; i < size - 1; i++) {
        swapped = false;
        for (size_t k = 0; k < size - i - 1; k++) {
            if ((*numbers)[k] < (*numbers)[k + 1]) {
                std::swap((*numbers)[k], (*numbers)[k + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}
float mediana(std::vector<float>* numbers){
    bubbleSortUp(numbers);
    int size = (int)numbers->size(); //število elementov
    bool liho = size%2; //0 - sodo, 1 - liho
    int index;

    if(liho){
        index = size/2; //vzamemo sredino
        return (*numbers)[index];
    }
    //else : size je sodo
    index = size/2;
    return ((*numbers)[index - 1] + (*numbers)[index])/2; //povprečje srednih 2 elementov
}
float standardniOdklon(std::vector<float>* numbers){
    size_t size = numbers->size();
    float avg = avarige(numbers);
    float buff = 0;
    for(auto&i : *numbers){
        buff += (i - avg)*(i - avg); //iz formule prepisano. 2x zato kr je kvadrat
    }
    return std::sqrt(buff/size); //sqrt - koren
}

std::vector<float> nomaliziraj(float lowerBount, float upperBount, std::vector<float>* numbers){

    std::vector<float> norm; //tu so normalizirane vrednosti

    float minV = min(numbers);
    float maxV = max(numbers);
    for(auto& i: *numbers){
        float buff = lowerBount + ((i - minV)/(maxV - minV))* (upperBount - lowerBount); //formula iz interneta
        norm.push_back(buff);
    }
    return norm;
}

int randomInt(int low, int top) { //naključni int na podanem intervalu
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(low, top);

    return distr(gen);
}

std::vector<float> randomVector(int size, int low, int top){
    std::vector<float> ret;
    for (int i = 0; i< size; i++){
        int buff = randomInt(low, top);
        ret.push_back((float)buff);
    }
    return ret;
}