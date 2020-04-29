//Кашин Андрей 9305
//Частное от деления многочлена на многочлен при делении с остатком
polynomial *P9(polynomial *A, polynomial *B) 
{
    size_t degree, i = 0;

    polynomial *res = NULL, *temp = NULL, *temp2 = NULL, *divider = NULL, *dividend = NULL;
    
	if (P6(A) >= P6(B)) 
	{
        dividend = copy_polynomial(A);
        divider = copy_polynomial(B);
        
		degree = dividend -> degree - divider -> degree; // старшая степень результата
        
		res = init_polynomial(degree);
        
		while ((P6(dividend) >= P6(divider)) && i <= res -> degree) {
            res -> factors[degree] = Q8(dividend -> factors[dividend -> degree],
            
			divider -> factors[divider -> degree]);   // текущий коэф перед степенью
            
			temp = dividend;
            
			temp2 = P8(divider, res); // полином полученный умножением делителя и текущего результата
            
			dividend = P2(dividend, temp2);// делимое тепер =делимое - результат умножения
            
			free_polynomial(temp);
            free_polynomial(temp2);
            
			degree = dividend -> degree - divider -> degree; // степень следующего коэф результата
            
			i++;// счетчик проходов
        }
 
        free_polynomial(dividend);
        free_polynomial(divider);

    } 
	else 
	{    // если делитель больше делимого , частное =0
        res = init_polynomial(1);
        
		res->factors[0]->numerator->length = 1;
        res->factors[0]->numerator->digits[0] = 0;
        
		res->factors[0]->denominator->length = 1;
        res->factors[0]->denominator->digits[0] = 1;
        
		res->degree = 0;

    }
    
    return (res);

}
