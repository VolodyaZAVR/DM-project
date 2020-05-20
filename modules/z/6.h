// Когутенко Андрей 9305
// Сложение целых чисел

#include <stdbool.h>

integer *Z6(integer *A, integer *B)
{
    integer *C;
    
    natural *A_natural = Z1(A);
    natural *B_natural = Z1(B);
    natural *C_natural;
    
    bool sign;
    
    if(A -> sign == B -> sign) {
        
        // Суммируем абсолютные величины
        
        C_natural = N4(A_natural, B_natural);
        sign = A -> sign;
        
    } else {
        
        if(A -> sign == true) {
            
            // +-
            
            if(N1(A_natural, B_natural) == 1) {
                
                // |a| < |b|
                
                C_natural = N5(B_natural, A_natural);
                sign = false;
                
            } else {
                
                // |a| >= |b|
                
                C_natural = N5(A_natural, B_natural);
                sign = true;
            }
            
        } else {
            
            // -+
            
            if(N1(A_natural, B_natural) == 2) {
                
                // |a| > |b|
                
                C_natural = N5(A_natural, B_natural);
                sign = false;
                
            } else {
                
                // |a| <= |b|
                
                C_natural = N5(B_natural, A_natural);
                sign = true;
            }
        }
    }
        
    C = Z4(C_natural);
    C -> sign = sign;
    
    free_natural(A_natural);
    free_natural(B_natural);
    free_natural(C_natural);
    
    return C;
}

