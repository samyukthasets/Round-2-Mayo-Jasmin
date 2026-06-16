#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "print.h"
#include "api.h"

extern uint64_t mayo2_crypto_sign_keypair(unsigned char *pk, unsigned char *sk);
extern int
mayo2_crypto_sign(unsigned char *sm,
            const unsigned char *m, unsigned long long mlen,
            const unsigned char *sk);
extern int
mayo2_crypto_sign_open(unsigned char *sm,
            const unsigned char *m, unsigned long long mlen,
            const unsigned char *pk);

int main(void) {
    
    unsigned char *pk  = calloc(CRYPTO_PUBLICKEYBYTES, 1);
    unsigned char *sk  = calloc(CRYPTO_SECRETKEYBYTES, 1);
    int param_sig_bytes = 186;

    unsigned char seed[48];
    
    uint64_t ret_val;

     int r;
    

    clock_t start, end;
    double cpu_time_used;

   
    start = clock();
    
    ret_val = mayo2_crypto_sign_keypair(pk, sk);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time taken to generate the key: %f seconds\n", cpu_time_used);
    if(ret_val == 0){
        printf("\n[1]. Mayo2 public key and secret key generated\n");
    }
    else{
        printf("\n[FATAL]: Mayo2 public key and secret key generation failed\n");
    }

    printf("\nSecret Key starts:\n");

    for(int i = 0; i < CRYPTO_SECRETKEYBYTES; i++){
        printf("%02x",sk[i]);
    }
   
   
    printf("\nPublic Key starts:\n");

    for(int i = 0; i < CRYPTO_PUBLICKEYBYTES; i++){
        printf("%02x",pk[i]);
    }
    
  
    unsigned long long mlen = 33;
    unsigned char m[33] = { 
         0xd8, 0x1c, 0x4d, 0x8d, 0x73, 0x4f, 0xcb, 0xfb, 0xea, 0xde, 0x3d, 0x3f, 0x8a, 0x03, 0x9f, 0xaa, 0x2a, 0x2c, 0x99, 0x57, 0xe8, 0x35, 0xad, 0x55, 0xb2, 0x2e, 0x75, 0xbf, 0x57, 0xbb, 0x55, 0x6a, 0xc8
        
        };

 
    unsigned long long smlen = param_sig_bytes;
 
    unsigned char *sma;
    sma = (unsigned char *)calloc(mlen + CRYPTO_BYTES, sizeof(unsigned char));
    start = clock();
    r = mayo2_crypto_sign(sma, m, mlen, sk);
    end = clock();
      cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\n\nTime taken to sign: %f seconds\n", cpu_time_used);

    if(r == 0){
        printf("\n[2]. Mayo2 Signature Generated\n");
    }
    else{
        printf("\n[FATAL]: Mayo2 Signature Generation failed\n");
    }

    
    printf("\nsignature:\n");

    for(int i = 0; i < param_sig_bytes; i++){
        printf("%02x",sma[i]);
    }
 
    
    start = clock();
   
   r = mayo2_crypto_sign_open(sma, m, mlen, pk);
   
    end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Print the result
    printf("\n\nTime taken to verify: %f seconds\n", cpu_time_used);

    if(r == 0){
        printf("\n[3]. Mayo2 Signature Verified\n");
    }
    else{
        printf("\n[FATAL]: Mayo2 Verification failed\n");
    }

}
