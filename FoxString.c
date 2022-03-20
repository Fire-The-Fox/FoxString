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

#include "FoxString.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


FoxString
FoxString_New(char *init)
{
    FoxString new;

    if (init == NULL || strcmp(init, "\0") == 0) {

        new.data = (char*) malloc(1);
        *(new.data+0) = '\0';
        new.size = 0;

    } else {

        new.data = (char*) malloc(strlen(init));
        strcpy(new.data, init);
        new.size = strlen(new.data);
    }
    return new;
}


void
FoxString_Clean(FoxString *string)
{
    free(string->data);
    string->size = 0;
}

FoxString
FoxString_ReCreate(FoxString *string, char *init)
{
    FoxString_Clean(string);

    FoxString fresh = FoxString_New(init);

    return fresh;
}

FoxString
FoxStringInput()
{
    unsigned char bufferChar;
    FoxString string = FoxString_New(NULL);

    while(true) {
        bufferChar = getchar();
        if (bufferChar == '\n') break;
        FoxString_Add(&string, (char) bufferChar);
    }

    return string;
}

int
FoxString_Count(FoxString string, char detect)
{
    int found = 0;

    for (int i = 0; i < strlen(string.data); i++) {
        if (string.data[i] == detect) found++;
    }

    return found;
}

int
FoxString_Find(FoxString string, char detect)
{
    int i;

    for (i = 0; i < strlen(string.data); i++) {
        if (string.data[i] == detect) break;
    }

    if (i < strlen(string.data)) return i;
    else return NOT_FOUND;
}

int
FoxString_Contains(FoxString str1, FoxString str2)
{
    char found = false;

    for (int i = 0; i < str1.size; i++) {
        if (str1.data[i] == str2.data[0]) {
            char mistake = false;
            if (i + str2.size - 1 >= str1.size) mistake = true;
            for (int j = 0; j < str2.size && !mistake; j++) {
                if (str1.data[i+j] != str2.data[j]) {
                    mistake = true;
                    break;
                }
            }
            if (!mistake) {
                found = true;
                break;
            }
        }
    }

    if (!found) {
        return NOT_FOUND;
    }

    return found;
}

int
FoxString_Add(FoxString* string, char character)
{
    string->data = realloc(string->data, string->size + 2);

    if (string->data == NULL) return OUT_OF_MEMORY;

    string->data[string->size] = character;
    string->data[string->size + 1] = '\0';
    string->size = strlen(string->data);

    return NO_ISSUE;
}

int
FoxString_Connect(FoxString* mainString, FoxString sideString)
{
    mainString->data = realloc(mainString->data, mainString->size + sideString.size);

    if (mainString->data == NULL) return OUT_OF_MEMORY;

    for (int i = 0; i < sideString.size; i++) mainString->data[mainString->size + i] = sideString.data[i];

    mainString->data[mainString->size + sideString.size + 1] = '\0';
    mainString->size = strlen(mainString->data);

    return NO_ISSUE;
}

int
FoxString_Pop(FoxString* string)
{
    string->data[string->size-1] = '\0';
    string->size--;
    string->data = realloc(string->data, string->size);

    if (string->data == NULL) return OUT_OF_MEMORY;

    return NO_ISSUE;
}


FoxString
FoxString_Replace(FoxString string, char oldChar, char newChar, int count)
{
    FoxString fresh = FoxString_New(NULL);
    int replacements = 0;

    if (count == NO_LIMIT) count = (int) strlen(string.data);

    for (int i = 0; i < strlen(string.data); i++) {
        if (string.data[i] == oldChar && newChar != '\0' && replacements < count) {
            replacements++;
            FoxString_Add(&fresh, newChar);
        } else if (string.data[i] == oldChar && newChar == '\0' && replacements < count) {
            i++;
            replacements++;
            FoxString_Add(&fresh, string.data[i]);
        } else FoxString_Add(&fresh, string.data[i]);
    }

    return fresh;
}

int
FoxString_Compare(FoxString str1, FoxString str2)
{
    if (strcmp(str1.data, str2.data) == 0) return EQUAL;
    return NOT_EQUAL;
}

FoxStringArray
FoxString_Split(FoxString string, char splitChar)
{
    FoxStringArray array = FoxStringArray_Create();
    FoxString tmpString = FoxString_New(NULL);

    for (int i = 0; i < strlen(string.data); i++) {
        if (string.data[i] == splitChar) {
            FoxStringArray_Append(&array, tmpString);
            tmpString = FoxString_New(NULL);
        } else FoxString_Add(&tmpString, string.data[i]);
    }
    FoxStringArray_Append(&array, tmpString);
    return array;
}

FoxStringArray
FoxStringArray_Create()
{
    FoxStringArray fresh;
    fresh.array = (FoxString*) malloc(1 * sizeof(FoxString));
    fresh.size = 0;
    fresh.created = true;

    return fresh;
}

int
FoxStringArray_Append(FoxStringArray *array, FoxString string)
{
    if (array->created) {

        array->size++;
        array->array = realloc(array->array, array->size * sizeof(FoxString));

        if (array->array == NULL) return OUT_OF_MEMORY;

        array->array[array->size-1] = string;

    } else return NOT_CREATED;
    return NO_ISSUE;
}

FoxString
FoxStringArray_Get(FoxStringArray array, int index)
{
    if (array.created) return array.array[index];
    else return FoxString_New(NULL);
}

int
FoxStringArray_Insert(FoxStringArray *array, int index, FoxString string)
{
    if (array->created) {

        if (array->size > index) {

            array->size++;
            array->array = realloc(array->array, array->size * sizeof(FoxString));

            if (array->array == NULL) return OUT_OF_MEMORY;

            for (int i = array->size; i > index; i--) array->array[i-1] = array->array[i-2];

            array->array[index] = string;
        }
    } else return NOT_CREATED;
    return NO_ISSUE;
}

int
FoxStringArray_Replace(FoxStringArray *array, int index, FoxString string)
{
    if (array->created) array->array[index] = string;
    else return NOT_CREATED;
    return NO_ISSUE;
}

int
FoxStringArray_Remove(FoxStringArray *array, int index)
{
    if (array->created) {

        for (int i = index; i < array->size; i++) array->array[i] = array->array[i+1];

        array->array = realloc(array->array, (array->size-1) * sizeof(FoxString));

        if (array->array == NULL) return OUT_OF_MEMORY;

        array->size--;
    } else return NOT_CREATED;
    return NO_ISSUE;
}

int
FoxStringArray_Index(FoxStringArray array, FoxString string)
{
    int index, found = false;

    if (array.created) {
        for (index = 0; index < array.size; index++) {
            if (FoxString_Compare(string, array.array[index]) == EQUAL) {
                found = true;
                break;
            }
        }
    } else return NOT_CREATED;

    if (found) return index;
    else return NOT_FOUND;
}

int
FoxStringArray_Clean(FoxStringArray *array)
{
    if (array->created) {

        array->created = false;
        array->size = 0;
        free(array->array);

    } else NOT_CREATED;
    return NO_ISSUE;
}

FoxStringArray
FoxStringArray_ReCreate(FoxStringArray *array)
{
    FoxStringArray_Clean(array);

    FoxStringArray fresh = FoxStringArray_Create();

    return fresh;
}
