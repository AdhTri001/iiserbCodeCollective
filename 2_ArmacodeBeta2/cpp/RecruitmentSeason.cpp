#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int nPeople;
    std::cin >> nPeople;

    std::vector<int> receivers(nPeople);
    for (int i = 0; i < nPeople; ++i) {
        std::cin >> receivers[i];
    }
    std::sort(receivers.begin(), receivers.end());

    const int CEO_INDEX = 0;

    for (int personID = CEO_INDEX; personID <= nPeople; ++personID) {
        if (! std::binary_search(receivers.begin(), receivers.end(), personID)) {
            std::cout << personID << " ";
        }
    }

    return 0;
}