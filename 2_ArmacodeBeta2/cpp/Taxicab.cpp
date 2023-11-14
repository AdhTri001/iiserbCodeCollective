#include <cmath>
#include <iostream>
using namespace std;

bool isRamaNo(long n) {
    if ((n % 7) == 3 || (n % 7) == 4) {
        return false;
    }
    int j = std::floor(std::cbrt(n));
    int j_cube = std::pow(j, 3);
    int i = std::floor(std::cbrt(n - j_cube));
    int count = 0;
    while (i <= j) {
        long val = (long)std::pow(i, 3) + j_cube;
        if (val == n) {
            count += 1;
        } else if (val > n) {
            j -= 1;
            j_cube = std::pow(j, 3);
            i = std::floor(std::cbrt(n - j_cube));
            continue;
        }
        i += 1;
    }
    if (count >= 2) {
        return true;
    }
    return false;
}

int main() {
    int T;
    cin >> T;
    long numberToCheck;
    while (T--) {
        cin >> numberToCheck;
        if (isRamaNo(numberToCheck))
            cout << 1;
        else
            cout << 0;
        cout << '\n';
    }
    return 0;
}