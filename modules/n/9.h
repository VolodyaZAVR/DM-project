// Nikolaenko
natural *N9(natural *A, natural *B, int c) {
    natural *C, *D;
	
    C = init_natural(A -> length);
    D = init_natural(B -> length);
    
    C -> length = A -> length;
    D -> length = B -> length;
    
    for(int i = 0; i < (C -> length); i++) 
	    C -> digits[i] = (A -> digits[i]);
    for(int i = 0; i < (D -> length); i++) 
	    D -> digits[i] = (B -> digits[i]);
          // compare
        int q = N1(A, B);
          // multiplication and subtraction      
        if((q == 2) || (q == 0)) 
        {
            D = N6(D, c);
            C = N5(C, D);
            return C;
        }
        else if(q == 1) 
        {    
            C = N6(C, c);
            D = N5(D, C);
            return D;
        }    
}
