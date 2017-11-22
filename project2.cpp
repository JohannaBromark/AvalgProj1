//
// Created by Isabelle Hallman on 2017-11-22.
//

#include <iostream>
#include <random>

unsigned long long gcd(unsigned long long x, unsigned long long y) {
    //Finds greatest common divisor
    if (x < y) {
        return gcd(y, x);
    }
    return (y == 0 ? x : gcd(y, x % y));
}

unsigned long long gFunction(unsigned long long x, unsigned long long number) {
    return (x*x + 1) % number;
}

unsigned long long myExp(unsigned long long x, int y) {
    if ( y == 0 ) {
        return 1;
    }
    else if ( y == 1 ) {
        return x;
    }
    return x * myExp(x, y-1);
}

unsigned long long pollardsRho(unsigned long long number) {
    unsigned long long factor = 1, x = 2, y = 2;
    while (factor == 1) {
        x = gFunction(x, number);
        y = gFunction(gFunction(y, number), number);
        factor = gcd((unsigned long long) std::abs( (long long) (x - y) ), number);
    }
    if (factor == number) {
        return 0;
    }
    else {
        return factor;
    }
}

bool isProbablyPrime(unsigned long long number, int certainty) {
    //Miller-Rabin
    if (number == 2 || number == 3) {
        return true;
    }
    else if (number % 2 == 0 || number < 2) {
        return false;
    }
    unsigned long long d = number - 1;
    int s = 0;
    while (d % 2 == 0) {
        s += 1;
        d /= 2;
    }
    std::random_device rd;
    std::mt19937 rng(rd);
    std::uniform_int_distribution<int> uni(2, number-1);
    unsigned long long x;
    for (int i = 0; i < certainty; i++) { //WitnessLoop
        auto randInt = uni(rng);
        x = myExp(randInt, d) % number;
        if (x == 1 || x == number -1 ) {
            continue;
        }
        for (int j = 0; j < s - 1; j++) {
            x = (x * x) % number;
            if (x == 1){
                return false;
            }
            if (x == number - 1) {
                break; //Vill gå till början på WitnessLoop, hur? goto bra?
            }
        }
        return false;
    }
    return true;
}

void printFactors(unsigned long long number) {
    if (isProbablyPrime(number, 10)) {
        std::cout << number << std::endl;
    }
    else {
        unsigned long long factor = pollardsRho(number);
        if (isProbablyPrime(factor, 10)) {
            std::cout << factor << std::endl;
            printFactors(number / factor);
        }
        else {
            printFactors(factor);
            printFactors(number / factor);
        }
    }
}

int main() {
    unsigned long long number;
    std::cin >> number;
    printFactors(number);

}