#include <iostream>
#include <sstream>
#include <set>

using namespace std;

struct comparator {
    inline bool operator()(const int& x, const int& y) const noexcept {
        if (x == -y) {
            return true;
        }
        if (y == -x) {
            return false;
        }
        return less<int>()(abs(x), abs(y));
    }
};

/**
 Write a program that prints the temperature closest to 0 among input data.
 If two numbers are equally close to zero, positive integer has to be considered
 closest to zero (for instance, if the temperatures are -5 and 5, then display 5).
**/
int main() {
    int n; // the number of temperatures to analyse
    cin >> n; 
    cin.ignore();

    if (n == 0) {
        cout << "0" << endl;
        return 0;
    }
    
    string temps; // the n temperatures expressed as integers ranging from -273 to 5526
    getline(cin, temps);
    
    stringstream ss(temps);

    set<int, comparator> numbers;

    while (ss) {
        int a;
        ss >> a;
        numbers.insert(a);
    }

    cout << *numbers.begin() << endl;
    return 0;
}