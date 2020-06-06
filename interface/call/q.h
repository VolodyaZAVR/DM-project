/* Wrappers for Q block modules */

#pragma once

#include "../io.h"
#include "../numbers.h"
#include "../locale.h"
#include "../include.h"


/* FUNCTIONS */

unsigned char call_Q(unsigned char n);      /* Block N wrappers */



/* FUNCTIONS IMPLEMENTATIONS */


unsigned char call_Q(unsigned char n) {
        
    switch(n) {
        
        #ifdef Q_1
            case 1:
            {
                fraction *A = read_fraction(FIRST_FRACT);
                fraction *result = Q1(A);
                
                print("\n" RESULT);
                write_fraction(result);
                printf("\n");
                
                free_fraction(A);
                free_fraction(result);
                
                break;
            }
        #endif
        
        #ifdef Q_2
            case 2:
            {
                fraction *A = read_fraction(FIRST_FRACT);
                bool result = Q2(A);
                
                print("\n" RESULT);
                write_bool(result);
                
                free_fraction(A);
                
                break;
            }
        #endif
        
        #ifdef Q_3
            case 3:
            {
                integer *A = read_integer(FIRST_ARG_LI);
                fraction *result = Q3(A);
                
                print("\n" RESULT);
                write_fraction(result);
                printf("\n");
                
                free_integer(A);
                free_fraction(result);
                
                break;
            }
        #endif
        
        #ifdef Q_4
            case 4:
            {
                fraction *A = read_fraction(FIRST_FRACT);
                integer *result = Q4(A);
                
                print("\n" RESULT);
                write_integer(result);
                
                free_fraction(A);
                free_integer(result);
                
                break;
            }
        #endif
        
        #ifdef Q_5
            case 5:
            {
                fraction *A = read_fraction(FIRST_FRACT);
                fraction *B = read_fraction(SECOND_FRACT);
                fraction *result = Q5(A, B);
                
                print("\n" RESULT);
                write_fraction(result);
                printf("\n");
                
                free_fraction(A);
                free_fraction(B);
                free_fraction(result);
                
                break;
            }
        #endif
        
        #ifdef Q_6
            case 6:
            {
                fraction *A = read_fraction(FIRST_FRACT);
                fraction *B = read_fraction(SECOND_FRACT);
                fraction *result = Q6(A, B);
                
                print("\n" RESULT);
                write_fraction(result);
                printf("\n");
                
                free_fraction(A);
                free_fraction(B);
                free_fraction(result);
                
                break;
            }
        #endif
        
        #ifdef Q_7
            case 7:
            {
                fraction *A = read_fraction(FIRST_FRACT);
                fraction *B = read_fraction(SECOND_FRACT);
                fraction *result = Q7(A, B);
                
                print("\n" RESULT);
                write_fraction(result);
                printf("\n");
                
                free_fraction(A);
                free_fraction(B);
                free_fraction(result);
                
                break;
            }
        #endif
        
        #ifdef Q_8
            case 8:
            {
                fraction *A = read_fraction(FIRST_FRACT);
                fraction *B = read_fraction(SECOND_FRACT);
                fraction *result = Q8(A, B);
                
                print("\n" RESULT);
                write_fraction(result);
                printf("\n");
                
                free_fraction(A);
                free_fraction(B);
                free_fraction(result);
                
                break;
            }
        #endif
        
        default: return RCODE_NF;
    }
    
    print("\n");
    
    return RCODE_OK;
}
