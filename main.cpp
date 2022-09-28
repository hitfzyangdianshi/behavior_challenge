#include<cstdio>
#include <ctime>

extern "C" {
#include "miracl.h"
}


using namespace std;



// Goldbach's conjecture using MIRACL

int main() {


    miracl* mip = mirsys(5000, 10);  /* initialise system to base 10, 5000 digits per "big" */

    big number1, number2, composite_number;

    number1 = mirvar(2);
    number2=mirvar(2);
    composite_number=mirvar(0);

    big bigzero;
    bigzero=mirvar(0);

    irand((unsigned)time(NULL));

    bigbits(1500, composite_number);

    multiply(composite_number, mirvar(2),composite_number);

    cotnum(composite_number,stdout);
    printf(" =\n");

    int result_count=0;

    while(true){
        bool nextprime_success;
        nextprime_success = nxprime(number1, number1);
        if(nextprime_success==false){
            printf("break3 nextprime_success==false");
            break;
        }

        if(mr_compare(number1,composite_number)>=0 || mr_compare(number2,composite_number)>=0 ){
            printf("break1");
            break;
        }

        subtract(composite_number,number1,  number2);

        if(mr_compare(number2,bigzero)<=0){
            printf("break2");
            break;
        }

        bool isprime_result;
        isprime_result= isprime(number2);

        if(isprime_result==true){
            cotnum(number1,stdout);
            printf(" + ");
            cotnum(number2,stdout);
            result_count++;
            if(result_count==10)break;
        }
        else{
            continue;
        }
    }
    return 0;
}
