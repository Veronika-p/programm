#include <stdio.h>
 
int main(void)
{
    FILE *fIn = NULL;
    fIn = fopen("input.txt", "r");
 
    int iCountStart = 0, iCountEnd = 0;
    char ch;
 
    if (fIn == NULL) return 1;
 
    while ((ch = fgetc(fIn))!=EOF)
    {
        if (ch == '(') iCountStart++;
        if (ch == '(') iCountEnd++;
    }
 
    if (iCountStart == iCountEnd)
        printf("Числа открывающихся и закрывающихся скобок равны");
    else
 
    printf("\nЧисла открывающихся и закрывающихся скобок %s", iCountStart == iCountEnd? "равны": "не равны");
 
 
    return 0;
}
