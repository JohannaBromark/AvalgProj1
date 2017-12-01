//
// Created by Isabelle Hallman on 2017-11-22.
//

#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include <string>
//#include <set>
#include <iterator>
#include <gmpxx.h>

//Ladda ned bibliotek och kompilera GMP. Kompilera med specinställningar från Christian c++.
//Öka poängen genom att kolla efter specialfall. p^exp, innan den tar en massa tid.
//Använd pekare även för ints så ska det gå snabbare

mpz_class gFunction(mpz_class& x, const mpz_class& number) {
    //Computes (x*x)+1 mod number (which factor we seek)
    return (x * x + 1) % number;
}

mpz_class pollardsRho(const mpz_class &number, int& startValue) {
    //Finds non trivial factor for number. 
    //factor: the non trivial factor for number
    //number: the number to find factor for
    //startValue: the start value for x and y
    
    mpz_class factor = 1, x = startValue, y = startValue, cycle_size = 2;
    mpz_t ansGCD;
    mpz_init(ansGCD);
    while (factor == 1) {
        for (int count = 0; count < cycle_size && factor <= 1; count++) {
            x = gFunction(x, number);
            mpz_class xyDiff = x-y; 
            mpz_gcd(ansGCD, xyDiff.get_mpz_t(), number.get_mpz_t());            
            factor = mpz_class(ansGCD);
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
    mpz_clear(ansGCD);
}

bool findFactors(const mpz_class &number, std::vector<mpz_class>& factors) {
    //Recursive function for printing all factors of a number

    mpz_class numberLimit;
    numberLimit = "18446744073709551000000000";

    if (number > numberLimit) { //Sets a limit to pass the time limit
        return false;
    }
    else if (number == 0 || number == 1 || mpz_probab_prime_p(number.get_mpz_t(), 1000) > 0) {
        factors.push_back(number);
        return true;
    }

    int startValue = 2;
    mpz_class factor = pollardsRho(number, startValue);
    
    int tryFor = 0;
    while (factor == 0 && tryFor < 10 && startValue < number) {
        startValue++;
        factor = pollardsRho(number, startValue);
        tryFor++;
    }
    if (factor == 0) {
        return false;
    }
    else if (mpz_probab_prime_p(factor.get_mpz_t(), 1000) > 0) {
        factors.push_back(factor);
        //Factor is a divisor of number, no rounding occurs. 
        return findFactors(number / factor, factors);
    }
    else {
        findFactors(factor, factors);
        return findFactors(number / factor, factors);
    }
}

int main() {
    std::string input;
    mpz_class number;
    std::vector<mpz_class> factors;
    std::vector<std::string> inputs;
    
    while ( std::cin >> input) {
        inputs.push_back(input);
    }

    for (int i = 0; i < inputs.size(); i++) {
        factors.clear();
        number = inputs[i];

        if (findFactors(number, factors)) {
            for (mpz_class factor: factors) {
                std::cout << factor << "\n";
            }
        }
        else {
            std::cout << "fail" << "\n";
        }
        std::cout << "\n";
    }

    return 0;
}
