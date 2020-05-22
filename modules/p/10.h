// Кашин Андрей 9305
// Остаток от деления многочлена на многочлен при делении с остатком

polynomial *P10(polynomial *A, polynomial *B)
{
    polynomial *quotient;
    polynomial *multiply;
    polynomial *remainder;
    
    if(A -> degree >= B -> degree)
    {
        quotient = P9(A, B);
		multiply = P8(quotient, B);
		remainder = P2(A, multiply);
        
        free_polynomial(quotient);
        free_polynomial(multiply);
        
    } else remainder = copy_polynomial(A);
    
    return remainder;
}
