// 9305_Nikolaenko
fraction *Q8(fraction *A, fraction *B) {
    integer *C, *D;
    size_t i;
 
    C = init_integer(A -> numerator -> length);
    C -> sign = (A -> numerator -> sign);
    for(i = 0; i < (C -> length); i++) 
        C -> digits[i] = (A -> numerator ->digits[i]);

    D = init_integer(B -> denominator -> length); 
    D -> sign = true;
    for(i = 0; i < (D -> length); i++) 
        D -> digits[i] = (B -> denominator ->digits[i]);
    
    C = Z8(C, D);
    
        integer *N, *P;
    
        N = init_integer(B -> numerator -> length);
        N -> sign = (B -> numerator -> sign);
        for(i = 0; i < (N -> length); i++) 
            N -> digits[i] = (B -> numerator ->digits[i]);

        P = init_integer(A -> denominator -> length);  
        P -> sign = true;
        for(i = 0; i < (P -> length); i++) 
            P -> digits[i] = (A -> denominator ->digits[i]);
    
        P = Z8(N, P);
    
        if((P -> sign) == false) C = Z3(C);
    
        natural *G = init_natural(P -> length);
        for(i = 0; i < (G -> length); i++)
            G -> digits[i] = (P -> digits[i]);
	
	natural *K = init_natural(C -> length);
	for(size_t j = 0; j < (C -> length); j++) K -> digits[j] = C -> digits[j]; 
	
	natural *F = N13(K, G);
	
	K = N11(K, F);
	G = N11(G, F);
	
	C -> length =  K -> length;
	for(size_t j = 0; j < (K -> length); j++) C -> digits[j] = K -> digits[j]; 
	
	fraction *R = init_fraction(C, G);
       
    return R;
}
