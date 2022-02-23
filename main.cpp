//
// Created by jani on 22. 2. 2022.
//
#include "library.h"
#include <cstdio>

int
main()
{
    FString string;

    string.New((char*)"I am going to be mutable FoxString");

    printf("\n%s\n", string.data);

    string.ReCreate((char*)"I am better version of C++ string");

    printf("New string: %s\nSize is: %d\n", string.data, string.size);

    printf("\nTaking input: ");
    printf("Your input is: %s\n", FStringInput().data);

    string.Replace((char*) " ",(char*) "                    ", NO_LIMIT);

    printf("\nAfter .Replace\n%s\nSize is: %d", string.data, string.size);

    return 0;
}
