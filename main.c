/*
 * FoxString - Easy to use string implementation in C/C++
 * Copyright (C) 20022 Fire-The-Fox
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>

#include "library.h"

void
output(FoxStringArray array)
{
    for (int i = 0; i < array.size; i++) {
        printf("%s ", FoxStringArray_Get(array, i).data);
    }
}

int
main()
{
    FoxString string = FoxString_New("I am immutable string, but with FoxString i will be mutable"), string2;
    FoxStringArray array = FoxString_Split(string, ' ');

    printf("\nValue of string is: %s\nSize of string is: %d\n", string.data, string.size);

    printf("\nFound ' ' in string %d times\n", FoxString_Count(string, ' '));

    printf("'x' is located in string at %d\n", FoxString_Find(string, 'x'));

    FoxString_Add(&string, 'x');
    printf("\nValue of string is: %s\nSize of string is: %d\n", string.data, string.size);

    string2 = FoxString_Replace(string, ' ', '\0', NO_LIMIT);
    printf("\nValue of string is: %s\nSize of string is: %d\n", string2.data, string2.size);

    for (int i = 0; i < array.size; i++) {
        FoxString tmp = FoxStringArray_Get(array, i);
        printf("\nValue of string is: %s\nSize of string is: %d\n", tmp.data, tmp.size);
    }

    printf("\nInput testing: ");
    printf("Your input: %s\n", FoxStringInput().data);

    FoxStringArray_Insert(&array, 2, FoxString_New("char pointer"));
    printf("\nInserted \"char pointer\" into array\nThis is final sentence\n");

    output(array);

    printf("\n\nRemoving inserted element\n");
    FoxStringArray_Remove(&array, 2);

    output(array);

    printf("\n\nIndex of \"mutable\" is %d", FoxStringArray_Index(array, FoxString_New("mutable")));

    printf("\n\nreplacing immutable with \"char pointer\"\n");
    FoxStringArray_Replace(&array, 2, FoxString_New("char pointer"));

    output(array);

    printf("\n\nI -> You, am -> are, i -> you");
    FoxString tmp = FoxStringArray_Get(array, 0);
    FoxString_ReCreate(&tmp, "You");

    tmp = FoxStringArray_Get(array, 1);
    FoxString_ReCreate(&tmp, "are");

    tmp = FoxStringArray_Get(array, FoxStringArray_Index(array, FoxString_New("i")));
    FoxString_ReCreate(&tmp, "you");

    printf("\n");
    output(array);

    FoxString_Pop(&string);
    printf("\n\nAdding \"string\" to the end of our first string\n");
    FoxString_Connect(&string, FoxString_New(" string"));

    printf("%s", string.data);

    printf("\n\nDoes \"I am immutable string,\" exist in our first string\nAnswer: %d",
           FoxString_Contains(string, FoxString_New("I am immutable string,")));

    printf("\n\nDoes \"I am immutable string.\" exist in our first string\nAnswer: %d",
           FoxString_Contains(string, FoxString_New("I am immutable string.")));

    printf("\n\n\"abc\" in \"xxx a\": %d", FoxString_Contains(FoxString_New("xxx a"), FoxString_New("abc")));

    FoxString_Clean(&string);
    FoxString_Clean(&string2);

    FoxString_Clean(&tmp);

    FoxStringArray_Clean(&array);

    return 0;
}
