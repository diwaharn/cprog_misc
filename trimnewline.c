#include <stdio.h>
#include <string.h>


void removeNewlineSpace(char *input, int length)
{
    int count = 0;
    char *src, *dst;
    src = input;
    dst = input;

    //trim initial spaces
    while (isspace(*src)){
        src++;
    }
    *dst++ = *src++;

    while ((*src != '\0') && (count++ < length))
    {
        if (isspace(*src)) {
            while (isspace(*(++src)));  
            if ((*src != '\n') && (*src != '\0'))
                *dst++ = ' '; 
        }

        if ((*src == '\n') || (*src == '\0')) {
            break;
        }
        else {
            *dst++ = *src++;
        }
        //src++;
    }

    *dst = '\0';
}


int main()
{
    char str[6][64];

    strcpy (str[0], " first ");
    strcpy (str[1], "    second  ");
    strcpy (str[2], "third third               ");
    strcpy (str[3], "   fourth   fourth   ");
    strcpy (str[4], "   fifth");
    strcpy (str[5], "six");

    printf ("|%s|\n|%s|\n|%s|\n|%s|\n|%s|\n|%s|\n", 
            str[0], str[1], str[2], str[3], str[4], str[5]);

    removeNewlineSpace(str[0], 64);
    removeNewlineSpace(str[1], 64);
    removeNewlineSpace(str[2], 64);
    removeNewlineSpace(str[3], 64);
    removeNewlineSpace(str[4], 64);

    printf ("--------------\n|%s|\n|%s|\n|%s|\n|%s|\n|%s|\n|%s|\n", 
            str[0], str[1], str[2], str[3], str[4], str[5]);
    return 1;
}
