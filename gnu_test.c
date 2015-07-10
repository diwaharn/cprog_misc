#include <stdio.h>
#include <stdlib.h>


int label_as_value()
{
    int a;
    void *addr_s;
    void *addr_e;
    void *test;

start1:
start:
    printf ("inside function %s\n",__FUNCTION__);

    /* error statement, not defined */
    //test = &start;

    addr_s = &&start;
    addr_e = &&end;
    printf ("address of start1 %u, start %u, end %u\n", &&start1, addr_s, addr_e);
end:
    return 1;
}

int main()
{
    int a;
    label_as_value();
}
