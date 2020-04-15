integer *Z7(integer *A, integer *B)
{
    int k;
    integer *R;
    natural *A1, *B1, *L;
    R = NULL;

    if (Z2(A) == 0)
    {
        if (Z2(B) == 2)
            B -> sign = false;
        else if (Z2(B) == 1)
            B -> sign = true;
		R = init_integer(B -> length);
        R = B;
    }

	if (Z2(B) == 0)
	{
		R = init_integer(A -> length);
		R = A;
	}

    if (Z2(A) == 1 && Z2(B) == 1)
    {
 
        A1 = Z1(A);
        B1 = Z1(B);
		k = N1(A1, B1);
		if (k == 2)
		{
			L = N5(A1, B1);
			R = init_integer(L -> length);
			R = Z4(L);
			R -> sign = false;
		}
		else if (k == 0)
		{
			L = N5(A1, B1);
			R = init_integer(L->length);
			R = Z4(L);
		}
		else
		{
			L = N5(B1, A1);
			R = init_integer(L -> length);
			R = Z4(L);
		}
    }

    if (Z2(A) == 2 && Z2(B) == 1)
    {
        A1 = Z1(A);
        B1 = Z1(B);
        L = N4(A1, B1);
		R = init_integer(L -> length);
        R = Z4(L);
    }

    if (Z2(A) == 2 && Z2(B) == 2)
    {
        A1 = Z1(A);
        B1 = Z1(B);
        k = N1(A1, B1);
        if (k == 2 || k == 0)
        {
            L = N5(A1, B1);
			R = init_integer(L -> length);
            R = Z4(L);
        }
        else
        {
            L = N5(B1, A1);
			R = init_integer(L -> length);
            R = Z4(L);
            R -> sign = false;
        }
    }

    if (Z2(A) == 1 && Z2(B) == 2)
    {
        B1 = Z1(B);
        A1 = Z1(A);
        L = N4(A1, B1);
		R = init_integer(L -> length);
        R = Z4(L);
        R -> sign = false;
    }
    
    return(R);
}
