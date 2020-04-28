/* Wrappers for Q block modules */

#pragma once

#include "../io.h"
#include "../numbers.h"
#include "../locale.h"
#include "../include.h"


/* FUNCTIONS */

unsigned char call_P(unsigned char n);      /* Block N wrappers */



/* FUNCTIONS IMPLEMENTATIONS */


unsigned char call_P(unsigned char n) {
        
    switch(n) {
        #ifdef P_1
            case 1:
            {
                
                polynomial *A = read_polynomial(FIRST_POLY);
                polynomial *B = read_polynomial(SECOND_POLY);
                polynomial *result = P1(A, B);
                
                print("\n" RESULT);
                write_polynomial(result);
                
                free_polynomial(A);
                free_polynomial(B);
                free_polynomial(result);
                
                break;
            }
        #endif
        
        #ifdef P_2
            case 2:
            {
                
                polynomial *A = read_polynomial(FIRST_POLY);
                polynomial *B = read_polynomial(SECOND_POLY);
                polynomial *result = P2(A, B);
                
                print("\n" RESULT);
                write_polynomial(result);
                
                free_polynomial(A);
                free_polynomial(B);
                free_polynomial(result);
                
                break;
            }
        #endif
        
        #ifdef P_3
            case 3:
            {
                
                polynomial *A = read_polynomial(FIRST_POLY);
                fraction *B = read_fraction(SECOND_FRACT);
                polynomial *result = P3(A, B);
                
                print("\n" RESULT);
                write_polynomial(result);
                
                free_polynomial(A);
                free_fraction(B);
                free_polynomial(result);
                
                break;
            }
        #endif
        
        #ifdef P_4
            case 4:
            {
                
                polynomial *A = read_polynomial(FIRST_POLY);
                int b = read_int(SECOND_ARG_INT);
                polynomial *result = P4(A, (size_t)b);
                
                print("\n" RESULT);
                write_polynomial(result);
                
                free_polynomial(A);
                free_polynomial(result);
                
                break;
            }
        #endif
        
        #ifdef P_5
            case 5:
            {
                
                polynomial *A = read_polynomial(FIRST_POLY);
                fraction *result = P5(A);
                
                print("\n" RESULT);
                write_fraction(result);
                
                free_polynomial(A);
                free_fraction(result);
                
                break;
            }
        #endif
        
        #ifdef P_6
            case 6:
            {
                polynomial *A = read_polynomial(FIRST_POLY);
                size_t result = P6(A);
                
                print("\n" RESULT);
                write_int((int)result);
                
                free_polynomial(A);
                
                break;
            }
        #endif
        
        #ifdef P_11
            case 11:
            {
                
                polynomial *A = read_polynomial(FIRST_POLY);
                polynomial *B = read_polynomial(SECOND_POLY);
                polynomial *result = P11(A, B);
                
                print("\n" RESULT);
                write_polynomial(result);
                
                free_polynomial(A);
                free_polynomial(B);
                free_polynomial(result);
                
                break;
            }
        #endif
        
        #ifdef P_12
            case 12:
            {
                
                polynomial *A = read_polynomial(FIRST_POLY);
                polynomial *result = P12(A);
                
                print("\n" RESULT);
                write_polynomial(result);
                
                free_polynomial(A);
                free_polynomial(result);
                
                break;
            }
        #endif
        
        default: return RCODE_NF;
    }
    
    print("\n");
    
    return RCODE_OK;
}
