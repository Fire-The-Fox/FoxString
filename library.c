#include "library.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

FString
FString_New(char *init)
{
    FString new;

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
FString_Clean(FString *string)
{
    free(string->data);
    string->size = 0;
}

FString
FString_ReCreate(FString *string, char *init)
{
    FString_Clean(string);

    FString fresh = FString_New(init);

    return fresh;
}

FString
FStringInput()
{
    unsigned char bufferChar;
    FString string = FString_New(NULL);

    while(true) {
        bufferChar = getchar();
        if (bufferChar == '\n') break;
        FString_Add(&string, (char) bufferChar);
    }

    return string;
}

int
FString_Count(FString string, char detect)
{
    int found = 0;

    for (int i = 0; i < strlen(string.data); i++) {
        if (string.data[i] == detect) found++;
    }

    return found;
}

int
FString_Find(FString string, char detect)
{
    int i;

    for (i = 0; i < strlen(string.data); i++) {
        if (string.data[i] == detect) break;
    }

    if (i < strlen(string.data)) return i;
    else return NOT_FOUND;
}

int
FString_Contains(FString str1, FString str2)
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
FString_Add(FString* string, char character)
{
    string->data = realloc(string->data, string->size + 2);

    if (string->data == NULL) return OUT_OF_MEMORY;

    string->data[string->size] = character;
    string->data[string->size + 1] = '\0';
    string->size = strlen(string->data);

    return NO_ISSUE;
}

int
FString_Connect(FString* mainString, FString sideString)
{
    mainString->data = realloc(mainString->data, mainString->size + sideString.size);

    if (mainString->data == NULL) return OUT_OF_MEMORY;

    for (int i = 0; i < sideString.size; i++) mainString->data[mainString->size + i] = sideString.data[i];

    mainString->data[mainString->size + sideString.size + 1] = '\0';
    mainString->size = strlen(mainString->data);

    return NO_ISSUE;
}

int
FString_Pop(FString* string)
{
    string->data[string->size-1] = '\0';
    string->size--;
    string->data = realloc(string->data, string->size);

    if (string->data == NULL) return OUT_OF_MEMORY;

    return NO_ISSUE;
}

FString
FString_Replace(FString string, char oldChar, char newChar, int count)
{
    FString fresh = FString_New(NULL);
    int replacements = 0;

    if (count == NO_LIMIT) count = (int) strlen(string.data);

    for (int i = 0; i < strlen(string.data); i++) {
        if (string.data[i] == oldChar && newChar != '\0' && replacements < count) {
            replacements++;
            FString_Add(&fresh, newChar);
        } else if (string.data[i] == oldChar && newChar == '\0' && replacements < count) {
            i++;
            replacements++;
            FString_Add(&fresh, string.data[i]);
        } else FString_Add(&fresh, string.data[i]);
    }

    return fresh;
}

int
FString_Compare(FString str1, FString str2)
{
    if (strcmp(str1.data, str2.data) == 0) return EQUAL;
    return NOT_EQUAL;
}

FStringArray
FString_Split(FString string, char splitChar)
{
    FStringArray array = FStringArray_Create();
    FString tmpString = FString_New(NULL);

    for (int i = 0; i < strlen(string.data); i++) {
        if (string.data[i] == splitChar) {
            FStringArray_Append(&array, tmpString);
            tmpString = FString_New(NULL);
        } else FString_Add(&tmpString, string.data[i]);
    }
    FStringArray_Append(&array, tmpString);
    return array;
}

FStringArray
FStringArray_Create()
{
    FStringArray fresh;
    fresh.array = (FString*) malloc(1 * sizeof(FString));
    fresh.size = 0;
    fresh.created = true;

    return fresh;
}

int
FStringArray_Append(FStringArray *array, FString string)
{
    if (array->created) {

        array->size++;
        array->array = realloc(array->array, array->size * sizeof(FString));

        if (array->array == NULL) return OUT_OF_MEMORY;

        array->array[array->size-1] = string;

    } else return NOT_CREATED;
    return NO_ISSUE;
}

FString
FStringArray_Get(FStringArray array, int index)
{
    if (array.created) return array.array[index];
    else return FString_New(NULL);
}

int
FStringArray_Insert(FStringArray *array, int index, FString string)
{
    if (array->created) {

        if (array->size > index) {

            array->size++;
            array->array = realloc(array->array, array->size * sizeof(FString));

            if (array->array == NULL) return OUT_OF_MEMORY;

            for (int i = array->size; i > index; i--) array->array[i-1] = array->array[i-2];

            array->array[index] = string;
        }
    } else return NOT_CREATED;
    return NO_ISSUE;
}

int
FStringArray_Replace(FStringArray *array, int index, FString string)
{
    if (array->created) array->array[index] = string;
    else return NOT_CREATED;
    return NO_ISSUE;
}

int
FStringArray_Remove(FStringArray *array, int index)
{
    if (array->created) {

        for (int i = index; i < array->size; i++) array->array[i] = array->array[i+1];

        array->array = realloc(array->array, (array->size-1) * sizeof(FString));

        if (array->array == NULL) return OUT_OF_MEMORY;

        array->size--;
    } else return NOT_CREATED;
    return NO_ISSUE;
}

int
FStringArray_Index(FStringArray array, FString string)
{
    int index = 0, found = false;

    if (array.created) {
        for (index = 0; index < array.size; index++) {
            if (FString_Compare(string, array.array[index]) == EQUAL) {
                found = true;
                break;
            }
        }
    } else return NOT_CREATED;

    if (found) return index;
    else return NOT_FOUND;
}

int
FStringArray_Clean(FStringArray *array)
{
    if (array->created) {

        array->created = false;
        array->size = 0;
        free(array->array);

    } else NOT_CREATED;
    return NO_ISSUE;
}

FStringArray
FStringArray_ReCreate(FStringArray *array)
{
    FStringArray_Clean(array);

    FStringArray fresh = FStringArray_Create();

    return fresh;
}
