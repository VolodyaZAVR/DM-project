polynomial *P11(polynomial *A, polynomial *B)
{
    polynomial *r1 = NULL,*r2 = NULL,*ri = NULL;

    size_t sizeA,sizeB;
    sizeA = P6(A);
    sizeB = P6(B);

    if (sizeA >= sizeB) {
        r1 = P10(A,B);
        r2 =P10(B,r1);
    } else if (sizeA < sizeB) {
        r1 = P10(B,A);
        r2 = P10(A,r1);
    }
    while (ri -> factors != 0) {
        ri = P10(r1,r2);
        r1 = r2;
        r2 = ri;
    }

    return r2;
}
