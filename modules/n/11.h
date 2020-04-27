// 9305_Nikolaenko

natural *N11(natural *A, natural *B)
{
    natural *C, *D, *N, *R, *G;
    size_t i, c = 0;
    signed char t = 0;
    size_t u = 0;
    
    N = init_natural(B -> length);
    R = init_natural(A -> length);
    C = copy_natural(A);
    D = copy_natural(B);

    size_t j, b;
    u = C -> length;

    for(j = (D -> length); j >= 1; j--)
        N -> digits[j - 1] = (C -> digits[--u]);

    N -> length = D -> length;
    C -> length -= (D -> length);

    if(N1(N, D) == 1)
    {
        N -> length += 1;
        resize_natural(N, N -> length);
        
        for(b = (N -> length) - 1; b >= 1; b--)
            N -> digits[b] = (N -> digits[b - 1]);
        
        N -> digits[0] = (C -> digits[--u]);
        
        C -> length -= 1;
    }

    i = (C -> length);
    
    t = N10(N, D);
    R -> digits[c++] = t;
    R -> length = 1;
    
    G = init_natural(N -> length);
    G = N9(N, D, t);
    free_natural(N);
    
    if((G -> length == 1) && (G -> digits[0] == 0)){
    	G -> length = 0;
    	resize_natural(G, 1);
	}

    while(i--)
    {
    	if((G -> length != 1) || (G -> digits[0] != 0))
		    {
		    	G -> length += 1;
                resize_natural(G, G -> length);
			}
        
        for(b = (G -> length); b >= 2; b--)
            G -> digits[b - 1] = (G -> digits[b - 2]);

        G -> digits[0] = (C -> digits[u - 1]);
        N = copy_natural(G);
        
		if(u != 0)
            u--;

        t = N10(N, D);
        R -> digits[c++] = t;

        G = N9(N, D, t);
        free_natural(N);
        
        C -> length -= 1;
    }
    
    free_natural(C);
    free_natural(D);
    free_natural(G);
    
	R -> length = c;
	resize_natural(R, c);

    for(b = 0; b < c/2; b++)
    {
        t = R -> digits[b];
        R -> digits[b] = R -> digits[c - b - 1];
        R -> digits[c - b - 1] = t;
    }

    return R;
}
