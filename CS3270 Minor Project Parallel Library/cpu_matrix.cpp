#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <vector>
#include <chrono>

using std::cout;
using std::generate;
using std::vector;

void matrixMul(const vector<int>& a, const vector<int>& b, vector<int>& c, vector<unsigned int>& timer, int N) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            auto start_time = std::chrono::system_clock::now();
            c[row * N + col] = 0;
            for (int k = 0; k < N; k++) {
                c[row * N + col] += a[row * N + k] * b[k * N + col];
            }
            auto stop_time = std::chrono::system_clock::now();
            timer[row * N + col] = std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time).count();
        }
    }
}

void verify_result(const vector<int>& a, const vector<int>& b, const vector<int>& c, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int temp = 0;
            for (int k = 0; k < N; k++) {
                temp += a[i * N + k] * b[k * N + j];
            }
            assert(temp == c[i * N + j]);
        }
    }
}

int main() {
    int N = 1 << 10;

    vector<int> h_a(N * N);
    vector<int> h_b(N * N);
    vector<int> h_c(N * N);
    vector<unsigned int> timer(N * N);

    generate(h_a.begin(), h_a.end(), []() { return rand() % 100; });
    generate(h_b.begin(), h_b.end(), []() { return rand() % 100; });

    matrixMul(h_a, h_b, h_c, timer, N);

    for (long unsigned int i = 0; i < timer.size(); i++) {
        for (int j = 0; j < N; j++) {
            cout << timer[i] << " ";
        }
        cout << "\n";
    }

    cout << "COMPLETED SUCCESSFULLY\n";

    return 0;
}
