#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <random>

using namespace std;

vector<string> readLines(const string& filePath) {
    vector<string> besede;
    ifstream file(filePath); // odprem datoteko

    if (!file.is_open()) { // Če je napaka ne odpri
        cerr << "Failed to open the file." << endl;
        return vector<string>{};
    }

    string vrstica;
    while (getline(file, vrstica)) {
        besede.push_back(vrstica);
    }
    file.close();
    return besede;
}

void printVector(const vector<string>& vect) { // Print the vector to console
    for (const auto& i : vect) {
        cout << i << endl; // Print each element on a new line
    }
}
int getRandomInt(int upperLimit){ //vrne random int na intervalu (0, upperLimit)
    random_device rd;      //to je vse iz dokumentacije. Vrjetno te nebo nič o tem spraševal kr to samo bog ve kak deluje
    mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, upperLimit - 1);
    int random = dis(gen);
    return random;
}

string getRandomWord(vector<string>& besede){ //vrne random besedo iz vektorja
    int index = getRandomInt(besede.size() - 1);
    return besede[index];
}

string generateBuffer(string& beseda){ //vrne podčrtaje za besedo, primer: filip -> _____
    string ret;
    for(auto& i: beseda){
        ret += '_';
    }
    return ret;
}

void promptUser(string* wordBuffer, string* word, int* count){
    size_t wordSize = word->size();
    char crka;
    cout << "Vnesite crko za ugibanje\n"; // \n - to pomeni nova vrstica
    cin >> crka;
    for(int i = 0; i < wordSize; i++){
        if ((*word)[i] == crka){
            (*wordBuffer)[i] = crka;
            *count -= 1;
        }
    }
}

void insertWord(string& filePath){
    string word;
    cout << "Vnesite besedo: \n";
    cin >> word;
    vector <string> besede = readLines(filePath);
    for(auto&i : besede){
        if (i == word){
            cerr << "Beseda je ze noter!\n";
            break;
        }
    }
    ofstream file(filePath, ios::app);
    if (!file.is_open()) { //če je prišlo do napake
        cerr << "Failed to open the file: " << filePath << endl;
        return;
    }
    word = '\n' + word; // pred besedo dodamo še novo vrstico
    file << word << endl;
    file.close();
}

//prilagodi si path datoteke besede.txt če boš slučajno mogo. Pizda je kr mi cmake deva .exe file v subdirektorij
//če boš slučajno zaganjal na Linux ti lahko popravim to, za windows pa nvm kak se to nardi.
int main() {
    string filePath = "../besede.txt"; // pot do datoteke
    cout << "Ali želite vnesti novo besedo? - za ja vnesi 'y'\n";

    char insertCheck;
    cin >> insertCheck;
    if (insertCheck == 'y'){
        insertWord(filePath);
    }

    vector<string> besede = readLines(filePath);
    string beseda = getRandomWord(besede);
    string buffer = generateBuffer(beseda);

    printVector(besede);

    int poskusi = 10;
    int count = (int)beseda.size();

    while(poskusi){
        cout << buffer << "\n";
        promptUser(&buffer, &beseda, &count);
        poskusi --;
        if(count == 0){
            cout << "\nUganil si!\n";
            break;
        }
    }
    if (!poskusi){
        cout << "Zgubil si igro. Ni vec poskusov\n";
    }

    return 0;
}