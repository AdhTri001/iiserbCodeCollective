#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

typedef long long intLL;
typedef tuple<intLL, intLL, intLL> tuple_ll3;

bool compVals(const tuple_ll3 & a, const tuple_ll3 & b) {
    return get<1>(a) < get<1>(b);
}

int main() {
    long N;
    cin >> N;
    vector<tuple_ll3> vals(N);
    intLL i_start, i_end, i_oxygen;
    for (long i = 0; i < N; ++i) {
        cin >> i_start >> i_end >> i_oxygen;
        vals[i] = {i_start, i_end, i_oxygen};
    }
    sort(
        vals.begin(), vals.end(), compVals
    );

    map<intLL, intLL> oxygenSoFar;
    oxygenSoFar[0] = 0;
    intLL maxOxygen = 0;

    for(long i = 0; i < N; ++i) {
        intLL start = get<0>(vals[i]);
        intLL end   = get<1>(vals[i]);
        intLL oxy   = get<2>(vals[i]);
        auto lowerBound = -- oxygenSoFar.lower_bound(start);

        oxy += lowerBound->second;
        maxOxygen = max(oxy, maxOxygen);
        oxygenSoFar[end] = maxOxygen;
    }

    cout << maxOxygen;
    return 0;
}