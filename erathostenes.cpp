#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <cstring>
#include <vector>
using namespace std;

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

void print_bitarr(bitarray &prt){//call this function if you want to see the sieve as numbers of 0 or 1
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
    printf("enter in wich number you want the algorithm to stop");
    scanf("%lu", &stop);
    clock_t t=clock();
    eratosthenes(stop, erat);
    printf("the time of erath is: %f\n\n", (double)(clock()-t)/((double)CLOCKS_PER_SEC));
    printf("last prime: %lu\n", erat[erat.size()-1]);
    printf("vector size is: %lu\n", erat.size());
    
    //quit the comments if you want to see all the numbers
    /*
    uint32_t i=0;
    for(; i<erat.size(); i++){
        printf("%lu ", erat[i]);
    }
    */
    return 0;
}
