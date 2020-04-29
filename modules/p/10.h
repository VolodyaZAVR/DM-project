//Кашин Андрей 9305
//Остаток от деления многочлена на многочлен при делении с остатком
polynomial *P10(polynomial *A, polynomial *B)
{
    polynomial *res = NULL, *res1 = NULL, *res2 = NULL;

    if(A -> degree > B -> degree)
    {
        res1 = P9(A, B);
        
		res2 = P8(res1, B);
        
		res = P2(A, res2);

        free_polynomial(res1);
        free_polynomial(res2);
    }
    else res = copy_polynomial(A);	
    
    return res;
}
