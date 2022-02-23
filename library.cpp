//
// Created by jani on 22. 2. 2022.
//
#include "library.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

int
FString::New(char *init)
{
    if (init == nullptr || init == NULL | strcmp(init, "\0") == 0) {
        this->data = (char*) malloc(1);
        *(this->data+0) = '\0';
        this->size = 0;
    } else {
        this->data = (char*) malloc(strlen(init));
        strcpy(this->data, init);
        this->size = strlen(this->data);
    }
    if (this->data == NULL) {
        return OUT_OF_MEMORY;
    }
    return NO_ISSUE;
}

int
FString::Clean()
{
    free(this->data);
    this->size = 0;
    return NO_ISSUE;
}

int
FString::ReCreate(char *init)
{
    this->Clean();

    if (this->New(init) == OUT_OF_MEMORY) {
        return OUT_OF_MEMORY;
    }

    return NO_ISSUE;
}

int
FString::Add(char character)
{
    this->data = (char*) realloc(this->data, this->size + 2);

    if (this->data == NULL) return OUT_OF_MEMORY;

    this->data[this->size] = character;
    this->data[this->size + 1] = '\0';
    this->size = strlen(this->data);

    return NO_ISSUE;
}

int
FString::Count(char detect) const
{
    int found = 0;

    for (int i = 0; i < this->size; i++) {
        if (this->data[i] == detect) found++;
    }

    return found;
}

int
FString::Find(char detect) const
{
    int index;

    for (index; index < this->size; index++) {
        if (this->data[index] == detect) break;
    }

    if (index < this->size) return index;
    else return NOT_FOUND;
}

int
FString::Contains(FString string) const
{
    char found = false; // saving memory
    for (int i = 0; i < this->size; i++) {
        if (this->data[i] == string.data[0]) {
            char mistake = false;

            if (i + string.size > this->size) mistake = true;

            for (int j = 0; j < string.size && !mistake; j++) {
                if (this->data[i+j] != string.data[j]) {
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
FString::Connect(FString string)
{
    this->data = (char*) realloc(this->data, this->size + string.size + 1);

    if (this->data == NULL) return OUT_OF_MEMORY;

    for (int i = 0; i < string.size; i++) this->data[this->size + i] = string.data[i];

    this->data[this->size + string.size + 1] = '\0';
    this->size = strlen(this->data);

    return NO_ISSUE;
}

int
FString::Pop()
{
    this->data[this->size - 1] = '\0';
    this->size--;
    this->data = (char*) realloc(this->data, this->size);

    if (this->data == NULL) return OUT_OF_MEMORY;

    return NO_ISSUE;
}

int
FString::Replace(char* oldString, char* newString, int count)
{
    FString tmp;
    tmp.New(NULL);
    int replacements = 0;

    if (count == NO_LIMIT) count = (int) this->size;
    for (int i = 0; i < this->size; i++) {
        if (this->data[i] == oldString[0]) {
            char mistake = false;

            if (i + strlen(oldString) > this->size) mistake = true;

            for (int j = 0; j < strlen(oldString) && !mistake; j++) {
                if (this->data[i+j] != oldString[j]) {
                    mistake = true;
                    break;
                }
            }

            if (!mistake && replacements < count) {
                for (int j = 0; j < strlen(newString); j++) tmp.Add(newString[j]);
                replacements++;
                i += (int) strlen(oldString) - 1;

            } else if (replacements >= count) {
                tmp.Add(this->data[i]);
            }
        } else {
            tmp.Add(this->data[i]);
        }
    }

    this->size = tmp.size;

    this->data = (char*) realloc(this->data, this->size);

    if (this->data == NULL) return OUT_OF_MEMORY;

    strcpy(this->data, tmp.data);

    return NO_ISSUE;
}

int
FString::Compare(FString string)
{
    if (strcmp(this->data, string.data) == 0) return EQUAL;
    return NOT_EQUAL;
}

FString
FStringInput()
{
    unsigned char bufferChar;
    FString string;

    string.New(nullptr);

    while(true) {
        bufferChar = getchar();
        if (bufferChar == '\n') break;
        string.Add((char) bufferChar);
    }

    return string;
}