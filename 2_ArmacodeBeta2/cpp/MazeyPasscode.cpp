#include <string>
#include <iostream>

using namespace std;

bool isPalindrome(string s) {
    for(unsigned int i = 0; i<s.size()/2; i++) {
        if(s[i] != s[s.size()-i-1]) {
            return false;
        }
    } return true;
}

int main() {
    unsigned int palindromeLen = 0, len = 0;
    cin >> palindromeLen;
    cin >> len;
    string s;
    cin >> s;
    for(unsigned int i = 0; i<s.size()-palindromeLen+1; i++) {
        string substrToCheck = s.substr(i, palindromeLen);
        if(isPalindrome(substrToCheck)) {
            cout << substrToCheck << endl;
            break;
        }
    }
    return 0;
}