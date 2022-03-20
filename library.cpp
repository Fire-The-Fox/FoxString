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

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>

FoxString::FoxString(char *init) {
    if (init == nullptr || init == NULL | strcmp(init, "\0") == 0) {
        this->data = (char*) malloc(1);
        *(this->data+0) = '\0';
        this->size = 0;
    } else {
        this->data = (char*) malloc(strlen(init));
        strcpy(this->data, init);
        this->size = strlen(this->data);
    }
}


[[deprecated("Use new FoxString(''); instead")]]
int
FoxString::New(char *init)
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
FoxString::Clean()
{
    free(this->data);
    this->size = 0;
    return NO_ISSUE;
}

int
FoxString::ReCreate(char *init)
{
    this->Clean();

    FoxString temp = *new FoxString(init);

    if (temp.data == NULL) {
        return OUT_OF_MEMORY;
    }

    strcpy(this->data, temp.data);
    this->size = temp.size;

    return NO_ISSUE;
}

int
FoxString::Add(char character)
{
    this->data = (char*) realloc(this->data, this->size + 2);

    if (this->data == NULL) return OUT_OF_MEMORY;

    this->data[this->size] = character;
    this->data[this->size + 1] = '\0';
    this->size = strlen(this->data);

    return NO_ISSUE;
}

int
FoxString::Count(char detect) const
{
    int found = 0;

    for (int i = 0; i < this->size; i++) {
        if (this->data[i] == detect) found++;
    }

    return found;
}

int
FoxString::Find(char detect) const
{
    int index;

    for (index; index < this->size; index++) {
        if (this->data[index] == detect) break;
    }

    if (index < this->size) return index;
    else return NOT_FOUND;
}

int
FoxString::Contains(FoxString string) const
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
FoxString::Connect(FoxString string)
{
    this->data = (char*) realloc(this->data, this->size + string.size + 1);

    if (this->data == NULL) return OUT_OF_MEMORY;

    for (int i = 0; i < string.size; i++) this->data[this->size + i] = string.data[i];

    this->data[this->size + string.size + 1] = '\0';
    this->size = strlen(this->data);

    return NO_ISSUE;
}

char
FoxString::Pop()
{
	char removed = this->data[this->size - 1];
	
    this->data[this->size - 1] = '\0';
    this->size--;
    this->data = (char*) realloc(this->data, this->size);

    if (this->data == NULL) return OUT_OF_MEMORY;

    return removed;
}

int
FoxString::Replace(FoxString oldString, FoxString newString, int count)
{
    FoxString tmp = *new FoxString(NULL);
    int replacements = 0;

    if (count == NO_LIMIT) count = (int) this->size;
    for (int i = 0; i < this->size; i++) {
        if (this->data[i] == oldString.data[0]) {
            char mistake = false;

            if (i + strlen(oldString.data) > this->size) mistake = true;

            for (int j = 0; j < strlen(oldString.data) && !mistake; j++) {
                if (this->data[i+j] != oldString.data[j]) {
                    mistake = true;
                    break;
                }
            }

            if (!mistake && replacements < count) {
                for (int j = 0; j < strlen(newString.data); j++) tmp.Add(newString.data[j]);
                replacements++;
                i += (int) strlen(oldString.data) - 1;

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

    oldString.Clean();
    newString.Clean();
    tmp.Clean();

    return NO_ISSUE;
}

int
FoxString::Compare(FoxString string)
{
    if (strcmp(this->data, string.data) == 0) return EQUAL;
    return NOT_EQUAL;
}

void
FoxString::Upper()
{
	for (int i = 0; i < this->size; i++) this->data[i] = toupper(this->data[i]);
}

void
FoxString::Lower()
{
	for (int i = 0; i < this->size; i++) this->data[i] = tolower(this->data[i]);
}

void
FoxString::Capitalize()
{
	for (int i = 0; i < this->size; i++) {
		if (i == 0) this->data[0] = toupper(this->data[0]);
		else this->data[i] = tolower(this->data[i]);
	}
}

FoxString
FoxString::Copy()
{
    FoxString fresh = *new FoxString(this->data);

    return fresh;
}

FoxString
FoxStringInput()
{
    unsigned char bufferChar;
    FoxString string = *new FoxString(NULL);

    while(true) {
        bufferChar = getchar();
        if (bufferChar == '\n') break;
        string.Add((char) bufferChar);
    }

    return string;
}