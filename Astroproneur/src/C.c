#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main()
{
    char str1[105], str2[105];

    scanf("%s", &str1);
    scanf("%s", &str2);

    for (int i = 0; i < 105; i++)
    {
        if (str1[i] == '\0')
            break;

        if (str1[i] < 'a')
            str1[i] = 'a' + (str1[i] - 'A');
    }

    for (int i = 0; i < 105; i++)
    {
        if (str2[i] == '\0')
            break;

        if (str2[i] < 'a')
            str2[i] = 'a' + (str2[i] - 'A');
    }

    int comp = strcmp(str1, str2);

    printf("%d", comp);

    return 0;
}