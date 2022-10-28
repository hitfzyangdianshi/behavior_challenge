#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#define DEFINE_ON_ARM (defined (__arm__) || defined(__arm64__) || defined(__aarch64__) || defined(RPI) || defined(__Raspberry_PI__) || defined(__ARM_ARCH))

#include<cstdio>
#include <ctime>
#include <cstdlib>
#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

#include "miracl.h"

#if !DEFINE_ON_ARM
#include "interposition/jfree.h"
#include "interposition/jmalloc.h"
#endif


#ifdef __cplusplus
}
#endif


#include <unistd.h>
#include <dlfcn.h>



using namespace std;

/*
 * using g++ -ldl on arm
 * */

#if DEFINE_ON_ARM
void* myfree(void *pt)
{
    static void* (*real_free)(void*) = NULL;
    if (!real_free) {
        real_free= reinterpret_cast<void*(*)(void*)>( dlsym(RTLD_NEXT, "free"));
    }

    void *p = real_free(pt);
    // fprintf(stderr, "free(%p) = %p\n", pt, p);
    return p;
}


void* mymalloc(size_t size)
{
    static void* (*real_malloc)(size_t) = NULL;
    if (!real_malloc) {
        real_malloc = reinterpret_cast<void*(*)(size_t)>( dlsym(RTLD_NEXT, "malloc") );
    }

    void *p = real_malloc(size);
    // fprintf(stderr, "malloc(%d) = %p\n", size, p);
    return p;
}
#endif



// Goldbach's conjecture using MIRACL

int main(int argc, char** argv) {

    FILE *output_txt=fopen("result_output.txt","w");
    fprintf(output_txt,"*** START CHALLENGE ***\n");
    fprintf(output_txt,"argv[1] = %s\n",argv[1]);
    fflush(output_txt);

    if(argv[1]==NULL){
        fprintf(stderr, "[ERROR] no argv for composite number\n " );
        exit(EXIT_FAILURE);
    }

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
    //777850139815515823432937985104439249598190573151700075968989406179695960875331150269514998940399022488467916090825849114465503642910133770861457271969532878537031815230446931840061684995416357349745183381771279860684246236778849474628625674942902795509939309916363937745442241024561396926537841449463846747213991413648112534401838116568615587203457359448034002605339982599140780190821876471767613

    cinstr(composite_number,argv[1]);

    multiply(composite_number, mirvar(2),composite_number);

    //cotnum(composite_number,stdout);
    //printf(" =\n");

    int result_count=0;

    fprintf(output_txt,"*** START while loop ***\n");
    fflush(output_txt);
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
            cotnum(number1,output_txt);
            cotnum(number1,stdout);
            //printf(" + ");
            cotnum(number2,output_txt);
            cotnum(number2,stdout);
            result_count++;
            fflush(output_txt);
            if(result_count==10)break;
        }
        else{
            continue;
        }
    }

    myfree(number1);
    myfree(number2);
    myfree(composite_number);

    fprintf(output_txt, "***CHALLENGE ENDS\n");

    fclose(output_txt);

    return 0;
}