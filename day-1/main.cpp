#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void deconstruct(const string& input, string& direction, int& distance) {
    direction = input.substr(0, 1);
    distance  = stoi(input.substr(1));
}

int main() {

    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        perror("Could not open your file");
        return 1;
    }

    const int dialStart = 50;
    int dialPosition = dialStart;
    int pointsToZero = 0;

    string input;
    while (getline(inputFile, input)) {

        string direction;
        int distance;
        deconstruct(input, direction, distance);

        if (direction == "R") {
            dialPosition = (dialPosition + distance) % 100;
        } else {
            dialPosition = (dialPosition - distance + 100) % 100;
        }

        if (dialPosition == 0) {
            pointsToZero++;
        }
    }

    cout << pointsToZero << endl;
    return 0;
}
