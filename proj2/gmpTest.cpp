#include <iostream>
//#include <gmp.h>
#include <gmpxx.h>
#include <string>
//#include <cstring>
#include <vector>

void gFunction(mpz_t& x, const mpz_t& number) {
    
    mpz_t sum, mult;
    mpz_inits(sum, mult, NULL);
    mpz_mul(mult,x,x);
    mpz_add_ui(sum, mult, 1);
    mpz_mod(x, sum, number);
    mpz_clear(sum);
    mpz_clear(mult);
}

int main(){

    /*
    mpz_t a, b, c, d;
    mpz_init(a);
    mpz_inits(b,c,d,NULL);
    std::vector<mpz_t> aVector;

    std::string aString = "12345678901234567892345678"; 
    const char * input = aString.c_str();
    mpz_set_str(a, input, 10);
    aVector.push_back(a);
    mpz_set_str(b, "-4", 10);
    mpz_add(c,a,b);
    mpz_out_str(stdout, 10, c);
    mpz_mul(b, b, b);
    mpz_mod(c, a, b);
    gFunction(c, b);
    std::cout << "efter funktionen"<<std::endl;
    mpz_out_str(stdout, 10, c);
    std::cout << std::endl;
    mpz_probab_prime_p(a, 1000);
    int e =  mpz_probab_prime_p(a, 1000);
    std::cout << mpz_probab_prime_p(a, 1000) << std::endl;
    std::cout << e << std::endl;

    mpz_pow_ui(d, b, 2);
    mpz_out_str(stdout, 10, d);
    */
    
    mpz_class a, b, c, d;
    
    a = 2;
    b = "-3";
    c = a+b;
    d = a/b;


    int e =  mpz_probab_prime_p(a.get_mpz_t(), 1000);
    std::cout << "summa: " << c << std::endl;
    std::cout << "division: " << d << std::endl;
    //std::cout << "Is prime? " << e << endl;
    
    return 0;
}