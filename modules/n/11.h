// 9305_Nikolaenko

natural *N11(natural *A, natural *B)
{
    natural *C, *D, *N, *R;
    size_t i, c = 0;
    signed char t = 0;
    size_t u;

    N = init_natural((B -> length) + 1);
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
        
        for(b = (N -> length) - 1; b >= 1; b--)
            N -> digits[b] = (N -> digits[b - 1]);
        
        N -> digits[0] = (C -> digits[--u]);
        
        C -> length -= 1;
    }

    i = (C -> length);

    t = N10(N, D);
    R -> digits[c++] = t;
    R -> length = 1;

    N = N9(N, D, t);
    if((N -> length == 1) && (N -> digits[0] == 0))
        N -> length = 0;

    while(i--)
    {
    	if((N -> length != 1) || (N -> digits[0] != 0))
		    N -> length += 1;
        resize_natural(N, N -> length);
        
        for(b = (N -> length); b >= 2; b--)
            N -> digits[b - 1] = (N -> digits[b - 2]);

        N -> digits[0] = (C -> digits[u - 1]);
        if(u != 0)
            u--;

        t = N10(N, D);
        R -> digits[c++] = t;

        N = N9(N, D, t);

        C -> length -= 1;
    }
    
    free_natural(C);
    free_natural(D);
    free_natural(N);
    
	R -> length = c;

    for(b = 0; b < c/2; b++)
    {
        t = R -> digits[b];
        R -> digits[b] = R -> digits[c - b - 1];
        R -> digits[c - b - 1] = t;
    }

    return R;
}
