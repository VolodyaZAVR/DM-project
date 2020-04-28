polynomial *P12(polynomial *input)
{
    polynomial *res = NULL;
    size_t temp;

    temp = input -> degree;
    res -> degree = temp - 1;

    while (temp != 0) {
        res -> factors[temp - 1] = input -> factors[temp] * temp--;
    }

    return res;
}
