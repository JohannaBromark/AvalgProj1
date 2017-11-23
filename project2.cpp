//
// Created by Isabelle Hallman on 2017-11-22.
//

#include <iostream>
#include <random>
#include <algorithm>

unsigned long long gcd(unsigned long long x, unsigned long long y) {
    //Finds greatest common divisor
    if (x < y) {
        return gcd(y, x);
    }
    while (y > 0){
        unsigned long long z = x % y;
        x = y;
        y = z;
    }
    return x;
}

unsigned long long gFunction(unsigned long long x, unsigned long long number) {
    return (x * x + 1) % number;
}

unsigned long long myExp(unsigned long long x, int y) {
    if (y == 0) {
        return 1;
    }
    else if (y == 1) {
        return x;
    }
    return x * myExp(x, y - 1);
}

unsigned long long pollardsRho(unsigned long long number, int startValue) {
    unsigned long long factor = 1, x = startValue, y = startValue, cycle_size = 2;
    while (factor == 1) {
        for (int count = 0; count < cycle_size && factor <= 1; count++) {
            x = gFunction(x, number);
            //y = gFunction(gFunction(y, number), number);
            factor = gcd(x - y, number);
        }
        cycle_size *= 2;
        y = x;
    }
    if (factor == number) {
        return 0;
    }
    else {
        return factor;
    }
}

bool mrInnerLoop(unsigned long long x, int s, unsigned long long number) {
    for (int j = 0; j < s - 1; j++) {
        x = (x * x) % number;
        if (x == 1){
            return false;
        }
        if (x == number - 1) {
            return true;
        }
    }
    return false;
}

bool isProbablyPrime(unsigned long long number, int certainty) {
    //Miller-Rabins function for estimating if prime
    //funkar inte för 103
    if (number == 2 || number == 3 || number == 5 || number == 7) {
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
    //std::random_device rd;

    unsigned long long x;
    for (int i = 0; i < certainty; i++) { //WitnessLoop
        std::mt19937_64 rng(time(0));
        std::uniform_int_distribution<int> uni(2, number-1);
        auto randInt = uni(rng);
        x = myExp(randInt, d) % number;
        if (x == 1 || x == (number - 1)) {
            continue;
        }
        if (! mrInnerLoop(x, s, number)) {
            return false;
        }
    }
    return true;
}

std::vector<int> firstPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79};

unsigned long long modPow(unsigned long long base, unsigned long long pow, unsigned long long mod) {
    base %= mod;
    unsigned long long result = 1;
    while (pow > 0) {
        if (pow & 1) { //if odd
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        pow >>= 1; //division by two
    }
    return result;
}

bool isPrime(unsigned long long number) {
    if (number == 2 || number == 3 || number == 5 || number == 7) {
        return true;
    }
    else if ((!(number & 1)) || number < 2) { //if number not odd
        return false;
    }

    unsigned long long d = number - 1;
    int s = 0;
    while (! (d & 1)) { //while not odd
        s += 1;
        d >>= 1; //division by two
    }
    unsigned long long limit = std::min(number - 1, (unsigned long long) (2 * std::pow(std::log(number), 2)));
    bool composite;
    for (int a = 2; a <= limit; a++) {
        if (modPow(a, d, number) != 1) {
            for (int r = 0; r < s; r++) {
                composite = true;
                if (modPow(a, myExp(2, r) * d, number) == -1) {
                    composite = false;
                }
            }
            if (composite) {
                return false;
            }
        }
    }
    return true;
}

bool findFactors(unsigned long long number, std::vector<unsigned long long>& factors) {
    //Recursive function for printing all factors of a number
    if (isPrime(number)) {
        factors.push_back(number);
        return true;
    }

    int startValue = 2;
    unsigned long long factor = pollardsRho(number, startValue);
    int tryFor = 0;
    while (factor == 0 && tryFor < 10 && startValue < number) {
        factor = pollardsRho(number, startValue++);
        tryFor++;
    }
    if (factor == 0) {
        //std::cout << "fail" << std::endl;
        return false;
    }
    else if (isPrime(factor)) {
        factors.push_back(factor);
        return findFactors(number / factor, factors);
        //std::cout << factor << std::endl;
    }
    else {
        findFactors(factor, factors);
        return findFactors(number / factor, factors);
    }

}

int main() {
    std::cout << isPrime(103) << std::endl;

    unsigned long long number;
    std::cin >> number;

    std::vector<unsigned long long> factors;
    if (findFactors(number, factors)) {
        for (unsigned long long factor: factors) {
            std::cout << factor << std::endl;
        }
    }
    else {
        std::cout << "fail" << std::endl;
    }

    while (std::cin >> number) {
        factors.clear();
        std::cout << "\n";
        if (findFactors(number, factors)) {
            for (unsigned long long factor: factors) {
                std::cout << factor << std::endl;
            }
        }
        else {
            std::cout << "fail" << std::endl;
        }
    }
}