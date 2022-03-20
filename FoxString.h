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

#ifndef FOXSTRING_LIBRARY_H
#define FOXSTRING_LIBRARY_H

#define NOT_FOUND (-1)
#define NO_ISSUE 0
#define OUT_OF_MEMORY 2
#define NO_LIMIT 0
#define EQUAL 1
#define NOT_EQUAL 0
#define NOT_CREATED 3

#ifndef __cplusplus
typedef struct {
    char *data;
    unsigned int size;
} FoxString;

typedef struct {
    FoxString *array;
    int size;
    char created; // using as much little memory as possible
} FoxStringArray;

FoxString
FoxString_New(char *init);

void
FoxString_Clean(FoxString *string);

FoxString
FoxString_ReCreate(FoxString *string, char *init);

FoxString
FoxStringInput();

int
FoxString_Count(FoxString string, char detect);

int
FoxString_Find(FoxString string, char detect);

int
FoxString_Contains(FoxString str1, FoxString str2);

int
FoxString_Add(FoxString* string, char character);

int
FoxString_Pop(FoxString* string);

int
FoxString_Connect(FoxString* mainString, FoxString sideString);

FoxString
FoxString_Replace(FoxString string, char oldChar, char newChar, int count);

int
FoxString_Compare(FoxString str1, FoxString str2);

FoxStringArray
FoxString_Split(FoxString string, char splitChar);

FoxStringArray
FoxStringArray_Create();

int
FoxStringArray_Append(FoxStringArray *array, FoxString string);

FoxString
FoxStringArray_Get(FoxStringArray array, int index);

int
FoxStringArray_Insert(FoxStringArray *array, int index, FoxString string);

int
FoxStringArray_Replace(FoxStringArray *array, int index, FoxString string);

int
FoxStringArray_Remove(FoxStringArray *array, int index);

int
FoxStringArray_Index(FoxStringArray array, FoxString string);

int
FoxStringArray_Clean(FoxStringArray *array);

FoxStringArray
FoxStringArray_ReCreate(FoxStringArray *array);

#else

class FoxString {
    public:
        char *data;
        unsigned int size;

        explicit FoxString(char *init);

        [[deprecated("Use `new FoxString();` instead")]]
        int
        New(char *init);

        int
        Clean();

        int
        ReCreate(char *init);

        int
        Add(char character);

        int
        Count(char detect) const;

        int
        Find(char detect) const;

        int
        Contains(FoxString string) const;

        int
        Connect(FoxString string);

        char
        Pop();

        int
        Replace(FoxString oldString, FoxString newString, int count);

        int
        Compare(FoxString string);
        
        void
        Capitalize();
        
        void
        Upper();
        
        void
        Lower();

        FoxString
        Copy();
};

FoxString
FoxStringInput();
#endif

#endif //FOXSTRING_LIBRARY_H
