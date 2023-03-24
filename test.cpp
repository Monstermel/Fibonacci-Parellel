#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

unsigned long long fibos = 40;

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

auto expo = binpow_dbl;

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

int main(void) {
    std::cout << "Paralelo \n";
    for (size_t i = 0; i < fibos; i++) {
        std::cout << i << ":" << fibo_binet_parallel(i) << '\n';
    }
    std::cout << '\n';

    std::cout << "Secuencial \n";
    for (size_t i = 0; i < fibos; i++) {
        std::cout << i << ":" << fibo_binet_sequential(i) << '\n';
    }
    std::cout << '\n';

    return EXIT_SUCCESS;
}
