#include<iostream>
//#include<gmp.h>
#include<gmpxx.h>

using namespace std;

int main (int argc, char **argv) {

    mpz_class a,b,c;
    
    a= 1234;
    b= "-5673";
    
    
    //mpz_inits(a,b,c,NULL);

    //mpz_set_str(a, "1234", 10);
    //mpz_set_str(b,"-5678", 10); //Decimal base

    c = a+b;
    //mpz_add(c,a,b);

    cout<<"\nThe exact result is:" << c;
    //mpz_out_str(stdout, 10, c); //Stream, numerical base, var
    cout<<endl;

    //mpz_abs(c, c);
    cout<<"The absolute value result is:" << abs(c);

    //mpz_out_str(stdout, 10, c);
    cout<<endl;

    cin.get();

    return 0;
}