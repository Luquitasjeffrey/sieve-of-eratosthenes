#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

void createsieve(uint64_t * arr, uint32_t arrlen){//this is not the sieve of eratosthenes
    arr[0]=3;
    uint64_t start=5;
    uint32_t arrpos=1;
    for(; arrpos<arrlen; arrpos++){
        uint32_t i=0;
        while(arr[i]*arr[i]<=start){
            if(start%arr[i]==0){
                i=0;
                start+=2;
                continue;
            }
            i++;
        }
        arr[arrpos]=start;
        start+=2;
    }
}

void trivialp(uint64_t * arr, uint32_t arrlen){
    arr[0]=3;
    uint64_t start=5;
    for(int pos=1; pos<arrlen; pos++){
        uint32_t i=3;
        while(i*i<=start){
            if(start%i==0){
                start+=2;
                i=3;
                continue;
            }
            i+=2;
        }
        arr[pos]=start;
        start+=2;
    }
}

struct bitarray{
    uint8_t * arr;
    uint64_t arrsize;
    bitarray(uint64_t len){
        arr=(uint8_t*)malloc(1+len/8+(len%8==0));
        arrsize=len;
    }

    inline bool operator [](uint64_t bitpos){
        uint8_t compare=(1u<<(bitpos%8));
        uint8_t cpy=compare;
        compare&=arr[bitpos/8];
        return cpy==compare;
    }

    inline void setelement(uint64_t pos, bool bit){
        uint8_t cadd=(1u<<(pos%8));
        arr[pos/8]&=(0xff-cadd);
        arr[pos/8]^=(bit*cadd);
    }

    void _bitarray_memset(bool val){
        if(val){
            memset(arr, 255,(1+arrsize/8+(arrsize%8==1)));
            return;
        }
        memset(arr, 0,(1+arrsize/8+(arrsize%8==1)));
    }

    void cls(){
        free(arr);
    }
};

void print_bitarr(bitarray &prt){
    int i=0;
    for(; i<prt.arrsize; i++){
        printf("%i", (int)prt[i]);
    }
}

inline void removeprod(uint64_t n, bitarray &output){

    int i=2;
    for(; i*n<output.arrsize; i++){
        output.setelement(i*n, 0);
    }

}

void eratosthenes(uint64_t until, vector<uint64_t> &out){
    bitarray output(until);
    uint32_t stop=(uint32_t)sqrt(output.arrsize);
    output._bitarray_memset(1);
    output.setelement(1, 0);
    output.setelement(0, 0);
    uint64_t i=2;
    while(i<stop){
        removeprod(i, output);
        i++;
        while(!output[i]){
            i++;
        }
    }

    printf("done\n");
    for(i=2; i<output.arrsize; i++){
        if(output[i]){
            out.push_back(i);
        }
    }
    output.cls();
}

int main(){
    vector<uint64_t> erat;
    uint64_t stop;
    scanf("%lu", &stop);
    clock_t t=clock();
    eratosthenes(stop, erat);
    printf("the time of erath is: %f\n\n", (double)(clock()-t)/((double)CLOCKS_PER_SEC));
    printf("last prime: %lu\n", erat[erat.size()-1]);
    printf("vector size is: %lu\n", erat.size());

    /*
    uint32_t i=0;
    for(; i<erat.size(); i++){
        printf("%lu ", erat[i]);
    }
    */
    return 0;
}

#if 0
int main(){

    uint32_t len;
    cin>>len;
    uint64_t * arr=(uint64_t*)malloc(len*sizeof(uint64_t));
    clock_t start;

    start=clock();
    createsieve(arr, len);
    printf("timer of my sieve is: %f\n\n", (double)(clock()-start)/((double)CLOCKS_PER_SEC));

    vector<uint64_t> justforfun;
    start=clock();
    eratosthenes(arr[len-1], justforfun);
    printf("timer of erath is: %f\n\n", (double)(clock()-start)/((double)CLOCKS_PER_SEC));

    start=clock();
    trivialp(arr, len);
    printf("timer of trivial div is: %f\n\n", (double)(clock()-start)/((double)CLOCKS_PER_SEC));
    return 0;
}
#endif
