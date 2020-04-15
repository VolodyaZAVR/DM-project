/* Wrappers for N block modules */

#pragma once

#include "../io.h"
#include "../numbers.h"
#include "../locale.h"
#include "../include.h"


/* FUNCTIONS */

unsigned char call_N(unsigned char n);      /* Block N wrappers */



/* FUNCTIONS IMPLEMENTATIONS */


unsigned char call_Z(unsigned char n) {
    
    if(n > 10 || n == 0) return RCODE_NF;
        
    switch(n) {
        
        #ifdef Z_1
            case 1:
            {
                integer *A = read_integer(FIRST_ARG_LI);
                natural *result = Z1(A);
                
                print("\n" RESULT);
                write_natural(result);
                
                free_integer(A);
                free_natural(result);
                
                break;
            }
        #endif
        
        #ifdef Z_2
            case 2:
            {
                integer *A = read_integer(FIRST_ARG_LI);
                int result = Z2(A);
                
                print("\n" RESULT);
                write_int(result);
                
                free_integer(A);
                
                break;
            }
        #endif
        
        #ifdef Z_3
            case 3:
            {
                integer *A = read_integer(FIRST_ARG_LI);
                integer *result = Z3(A);
                
                print("\n" RESULT);
                write_integer(result);
                
                free_integer(A);
                free_integer(result);
                
                break;
            }
        #endif
        
        #ifdef Z_4
            case 4:
            {
                natural *A = read_natural(FIRST_ARG_LN);
                integer *result = Z4(A);
                
                print("\n" RESULT);
                write_integer(result);
                
                free_natural(A);
                free_integer(result);
                
                break;
            }
        #endif
        
        #ifdef Z_5
            case 5:
            {
                integer *A = read_integer(FIRST_ARG_LI);
                natural *result = Z1(A);
                
                print("\n" RESULT);
                write_natural(result);
                
                free_integer(A);
                free_natural(result);
                
                break;
            }
        #endif
        
        #ifdef Z_6
            case 6:
            {
                integer *A = read_integer(FIRST_ARG_LI);
                integer *B = read_integer(SECOND_ARG_LI);
                integer *result = Z6(A);
                
                print("\n" RESULT);
                write_integer(result);
                
                free_integer(A);
                free_integer(B);
                free_integer(result);
                
                break;
            }
        #endif
        
        #ifdef Z_7
            case 7:
            {
                integer *A = read_integer(FIRST_ARG_LI);
                integer *B = read_integer(SECOND_ARG_LI);
                integer *result = Z7(A, B);
                
                print("\n" RESULT);
                write_integer(result);
                
                free_integer(A);
                free_integer(B);
                free_integer(result);
                
                break;
            }
        #endif
        
        #ifdef Z_8
            case 8:
            {
                integer *A = read_integer(FIRST_ARG_LI);
                integer *B = read_integer(SECOND_ARG_LI);
                integer *result = Z8(A, B);
                
                print("\n" RESULT);
                write_integer(result);
                
                free_integer(A);
                free_integer(B);
                free_integer(result);
                
                break;
            }
        #endif
        
        #ifdef Z_9
            case 9:
            {
                integer *A = read_integer(FIRST_ARG_LI);
                integer *B = read_integer(SECOND_ARG_LI);
                integer *result = Z9(A);
                
                print("\n" RESULT);
                write_integer(result);
                
                free_integer(A);
                free_integer(B);
                free_integer(result);
                
                break;
            }
        #endif
        
        #ifdef Z_10
            case 10:
            {
                integer *A = read_integer(FIRST_ARG_LI);
                integer *B = read_integer(SECOND_ARG_LI);
                integer *result = Z10(A);
                
                print("\n" RESULT);
                write_integer(result);
                
                free_integer(A);
                free_integer(B);
                free_integer(result);
                
                break;
            }
        #endif
        
        default: return RCODE_NF;
    }
    
    print("\n");
    
    return RCODE_OK;
}
