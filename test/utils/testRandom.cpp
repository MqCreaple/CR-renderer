#include "TestInclude.h"
#include "utils/Random.h"
using namespace std;

int main() {
    int obj[4] {0, 1, 2, 3};
    float weight[4] {0.5, 0, 0.25, 0.25};
    int stat[4] {0, 0, 0, 0};
    int N = 100000;
    for(int i = 0; i < N; i++) {
        int index;
        int result = Random::randSelect(4, obj, weight, index);
        stat[result]++;
    }
    CHECK(stat[1] == 0);
    cout << stat[0] * 1.0 / N << endl;
    cout << stat[1] * 1.0 / N << endl;
    cout << stat[2] * 1.0 / N << endl;
    cout << stat[3] * 1.0 / N << endl;
}