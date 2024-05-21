
#ifndef LUKA_VAJA2_KNJIZNICA_H
#define LUKA_VAJA2_KNJIZNICA_H
#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <random>

float max(std::vector<float>* numbers);
float min(std::vector<float>* numbers);
float avarige(std::vector<float>* numbers);
void bubbleSortUp(std:: vector<float>* numbers); //najmanjši do največji
void bubbleSortDown(std:: vector<float>* numbers); //največji do najmanjši
void printVector(std::vector<float>* numbers);
float mediana(std::vector<float>* numbers);
float standardniOdklon(std::vector<float>* numbers);
std::vector<float> nomaliziraj(float lowerBount, float upperBount, std::vector<float>* numbers);
int randomInt(int low, int top);
std::vector<float> randomVector(int size, int low, int high);



#endif //LUKA_VAJA2_KNJIZNICA_H
