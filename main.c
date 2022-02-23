//
// Created by jani on 19. 2. 2022.
//
#include <stdio.h>

#include "library.h"

void
output(FStringArray array)
{
    for (int i = 0; i < array.size; i++) {
        printf("%s ", FStringArray_Get(array, i).data);
    }
}

int
main()
{
    FString string = FString_New("I am immutable string, but with FString i will be mutable"), string2;
    FStringArray array = FString_Split(string, ' ');

    printf("\nValue of string is: %s\nSize of string is: %d\n", string.data, string.size);

    printf("\nFound ' ' in string %d times\n", FString_Count(string, ' '));

    printf("'x' is located in string at %d\n", FString_Find(string, 'x'));

    FString_Add(&string, 'x');
    printf("\nValue of string is: %s\nSize of string is: %d\n", string.data, string.size);

    string2 = FString_Replace(string, ' ', '\0', NO_LIMIT);
    printf("\nValue of string is: %s\nSize of string is: %d\n", string2.data, string2.size);

    for (int i = 0; i < array.size; i++) {
        FString tmp = FStringArray_Get(array, i);
        printf("\nValue of string is: %s\nSize of string is: %d\n", tmp.data, tmp.size);
    }

    printf("\nInput testing: ");
    printf("Your input: %s\n", FStringInput().data);

    FStringArray_Insert(&array, 2, FString_New("char pointer"));
    printf("\nInserted \"char pointer\" into array\nThis is final sentence\n");

    output(array);

    printf("\n\nRemoving inserted element\n");
    FStringArray_Remove(&array, 2);

    output(array);

    printf("\n\nIndex of \"mutable\" is %d", FStringArray_Index(array, FString_New("mutable")));

    printf("\n\nreplacing immutable with \"char pointer\"\n");
    FStringArray_Replace(&array, 2, FString_New("char pointer"));

    output(array);

    printf("\n\nI -> You, am -> are, i -> you");
    FString tmp = FStringArray_Get(array, 0);
    FString_ReCreate(&tmp, "You");

    tmp = FStringArray_Get(array, 1);
    FString_ReCreate(&tmp, "are");

    tmp = FStringArray_Get(array, FStringArray_Index(array, FString_New("i")));
    FString_ReCreate(&tmp, "you");

    printf("\n");
    output(array);

    FString_Pop(&string);
    printf("\n\nAdding \"string\" to the end of our first string\n");
    FString_Connect(&string, FString_New(" string"));

    printf("%s", string.data);

    printf("\n\nDoes \"I am immutable string,\" exist in our first string\nAnswer: %d",
           FString_Contains(string, FString_New("I am immutable string,")));

    printf("\n\nDoes \"I am immutable string.\" exist in our first string\nAnswer: %d",
           FString_Contains(string, FString_New("I am immutable string.")));

    printf("\n\n\"abc\" in \"xxx a\": %d", FString_Contains(FString_New("xxx a"), FString_New("abc")));

    FString_Clean(&string);
    FString_Clean(&string2);

    FString_Clean(&tmp);

    FStringArray_Clean(&array);

    return 0;
}
