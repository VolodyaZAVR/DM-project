// Кашин Андрей 9305
// Частное от деления многочлена на многочлен при делении с остатком

#include <stdint.h>

polynomial *P9(polynomial *A, polynomial *B) 
{
    polynomial *dividend = copy_polynomial(A);
    polynomial *C = init_polynomial(A -> degree - B -> degree);
    
    size_t dividend_deg = A -> degree;
    
    for(size_t i = C -> degree; i != SIZE_MAX; ++i) {
        
        // Вычисляем частное от деления старшего коэффициента делимого
        // на старший коэффициент делителя
        
        fraction *quotient = Q8(dividend -> factors[dividend_deg], B -> factors[B -> degree]);
        
        // Домножаем делитель на полученное число
        
        polynomial *temp = P3(B, quotient);
        
        // Вычитаем из делимого
        
        write_polynomial(temp);
        
        polynomial *old = dividend;
        dividend = P2(dividend, temp);
        free_polynomial(old);
        free_polynomial(temp);
        
        C -> factors[i] = quotient;
        
        --dividend_deg;
    }
    
    return C;
}
