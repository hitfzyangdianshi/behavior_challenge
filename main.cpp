#include<cstdio>
#include <ctime>

#ifdef __cplusplus
extern "C" {
#endif


#include "miracl.h"

#include "interposition/jmalloc.h"

#include "interposition/jfree.h"


#ifdef __cplusplus
}
#endif


#include <unistd.h>


using namespace std;



// Goldbach's conjecture using MIRACL

int main(int argc, char** argv) {

    sleep(3);

    miracl* mip = mirsys(5000, 10);  /* initialise system to base 10, 5000 digits per "big" */

    big number1, number2, composite_number;


    number1 =(big) mymalloc(sizeof(big));
    number2=(big) mymalloc(sizeof(big));

    composite_number=(big) mymalloc(sizeof(big));


    number1 = mirvar(2);
    number2=mirvar(2);
    composite_number=mirvar(0);

    big bigzero;
    bigzero=mirvar(0);

    //irand((unsigned)time(NULL));

    //bigbits(1800, composite_number);
    //77785013981551582343293798510443924959819057315170007596898940617969596087533115026951499894039902248846791609082584911446550364291013377086145727196953287853703181523044693184006168499541635734974518338177127986068424623677884947462862567494290279550993930991636393774544224102456139692653784144946384674721399141364811253440183811656861558720345735944803400260533998259914078019082187647176761313535767485202646237839574347186337095641076426343761905828352269566830703817878713983333711383742746209161506947321366421127198006811720502000160

    cinstr(composite_number,argv[1]);

    multiply(composite_number, mirvar(2),composite_number);

    //cotnum(composite_number,stdout);
    //printf(" =\n");

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
            //printf(" + ");
            cotnum(number2,stdout);
            result_count++;
            if(result_count==10)break;
        }
        else{
            continue;
        }
    }

    myfree(number1);
    myfree(number2);
    myfree(composite_number);

    return 0;
}