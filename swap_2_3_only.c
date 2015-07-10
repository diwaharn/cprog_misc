#include <stdio.h>

int swap23 (int x)
{
    int y, z;
    int a, b;

    a = (y&3);
    b = (y&3) ^ 1;
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    
    return a;
}

char* print_binary_8(unsigned int n)
{
    enum { MAX_BITS = 8 };
    static char bin_str[64];
    int len = 0;
    int idx;

    for (idx = MAX_BITS; idx > 0; idx--){
        if (((idx%4) == 0) && (idx != MAX_BITS)) {
            bin_str[len++] = ' ';
        }

        if (n & (1 << (idx-1))){
            bin_str[len++] = '1';
        }
        else {
            bin_str[len++] = '0';
        }
    }

    bin_str[len] = '\0';

    return bin_str;
}

char* print_binary_16(unsigned int n)
{
    enum { MAX_BITS = 16 };
    static char bin_str[64];
    int len = 0;
    int idx;

    for (idx = MAX_BITS; idx > 0; idx--){
        if (((idx%4) == 0) && (idx != MAX_BITS)) {
            bin_str[len++] = ' ';
        }

        if (n & (1 << (idx-1))){
            bin_str[len++] = '1';
        }
        else {
            bin_str[len++] = '0';
        }
    }

    bin_str[len] = '\0';

    return bin_str;
}

int naveen_check(int x)
{
    printf ("x                   :%04x:%s\n", x, print_binary_8((unsigned int)x));
    printf ("x^2                 :%04x:%s\n", (x^2), print_binary_8(x^2));
    printf ("x^3                 :%04x:%s\n", (x^3), print_binary_8(x^3));
    printf ("x^2 | x^3           :%04x:%s\n", (x^2) | (x^3), print_binary_8((x^2) | (x^3)));
    printf ("x^2 | x^3 ^ 1       :%04x:%s\n", ((x^2) | (x^3)) ^ 1, print_binary_8(((x^2) | (x^3))^1));

    return ((1 >> (((x^2) | (x^3)) ^ 1)) ^ x);
}

int main()
{
    int x;
    int y;

    printf ("%d,%d\n", 'A', ~'A');
    for (x = 1; x < 25; x++) {
        y = x;
        (!(x>>1) || (x >> 2) || (y=x^1));
        printf ("%d, %d\n", y, naveen_check(x)); 
    }
    return 1;
}

