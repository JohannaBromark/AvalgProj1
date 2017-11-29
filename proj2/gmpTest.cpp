#include <iostream>
#include <gmpxx.h>
#include <string>
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
    
    mpz_t p, answ;
    mpz_inits(p, answ, NULL);
    mpz_set_str(p, "13", 10);
    mpz_class a, b, c, d, j, gcd, h;
    std::vector<mpz_class> testV;
    
    a = 4;
    j = 18;
    b = "-3";
    c = a+b;
    d = a/b;
    testV.push_back(a);
    testV.push_back(j);
    h = "123456789012345678900000";



    int e =  mpz_probab_prime_p(a.get_mpz_t(), 1000);
    int f = mpz_probab_prime_p(p, 1000);
    mpz_class mod = (4 * 4 + 1) % 7;
    
    mpz_gcd(answ, a.get_mpz_t(), j.get_mpz_t());
    gcd = mpz_class(answ);

    std::cout << "summa: " << c << std::endl;
    std::cout << "division: " << d << std::endl;
    std::cout << "Is prime? " << e << std::endl;
    std::cout << "Is prime? " << mpz_probab_prime_p(p, 1000) << std::endl;
    std::cout << "mod: " << mod << std::endl;
    std::cout << "gcd: " << gcd << std::endl;
    std::cout << "längd på lista: " << testV.size()<< std::endl;
    std::cout << "Jämförelse: " << (a > 1) << std::endl;

    mpz_clear(p);
    mpz_clear(answ);
    return 0;
}