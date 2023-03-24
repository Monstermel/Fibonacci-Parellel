#include <benchmark/benchmark.h>

#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

unsigned long long fibos = 100000;

// Para calcular fibos
double binpow_dbl(double a, int n) {
    double res = 1.0;
    while (n > 0) {
        if (n & 1) {
            res *= a;
        }
        a = a * a;
        n >>= 1;
    }
    return res;
}

// Para probar la funcion y evitar overflow
double binpow_int(int a, int n) {
    a %= 1000000;
    int res = 1;
    while (n > 0) {
        if (n & 1) {
            res = res * a % 1000000;
        }
        a = a * a % 1000000;
        n >>= 1;
    }
    return res;
}

auto expo = binpow_int;

double fibo_binet_parallel(unsigned long long n) {
    double a = (1.0 + sqrt(5.0)) / 2.0;
    double b = (1.0 - sqrt(5.0)) / 2.0;
    std::thread myThread([&a, n]() { a = expo(a, n); });
    b = expo(b, n);
    myThread.join();
    return (a - b) / sqrt(5.0);
}

double fibo_binet_sequential(unsigned long long n) {
    double a = (1.0 + sqrt(5.0)) / 2.0;
    double b = (1.0 - sqrt(5.0)) / 2.0;
    a = expo(a, n);
    b = expo(b, n);
    return (a - b) / sqrt(5.0);
}

// int main(void) {
//     using std::cout;
//     using namespace std::chrono;

//     auto start_1 = high_resolution_clock::now();
//     for (size_t i = 0; i < fibos; i++) fibo_binet_parallel(i);
//     auto end_1 = high_resolution_clock::now();
//     auto duration_1 = duration_cast<nanoseconds>(end_1 - start_1).count();
//     cout << "Paralelo  : " << duration_1 << " ns" << '\n';

//     auto start_2 = high_resolution_clock::now();
//     for (size_t i = 0; i < fibos; i++) fibo_binet_sequential(i);
//     auto end_2 = high_resolution_clock::now();
//     auto duration_2 = duration_cast<nanoseconds>(end_2 - start_2).count();
//     cout << "Secuencial: " << duration_2 << " ns" << '\n';

//     return EXIT_SUCCESS;
// }

static void BM_fibo_sequential(benchmark::State& state) {
    for (auto _ : state) fibo_binet_sequential(fibos);
}

static void BM_fibo_parallel(benchmark::State& state) {
    for (auto _ : state) fibo_binet_parallel(fibos);
}

// Register the function as a benchmark
BENCHMARK(BM_fibo_sequential);
BENCHMARK(BM_fibo_parallel);

BENCHMARK_MAIN();