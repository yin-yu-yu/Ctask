#include<stdio.h>
int main()
{
    char input[256];

    printf("请输入内容: ");
    scanf("%255s", input);
    printf("你输入的是: %s\n", input);

    return 0;
}