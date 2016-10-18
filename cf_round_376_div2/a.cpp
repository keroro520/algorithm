#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

string exhibits;

int main() {
    int ans = 0;
    char prev = 'a';
    cin >> exhibits;
    for(string::iterator c = exhibits.begin(); c != exhibits.end(); c ++) {
        int step = min(abs(prev - *c), 26 - abs(prev - *c));
        ans += step;
        prev = *c;
    }

    printf("%d", ans);

    return 0;
}
