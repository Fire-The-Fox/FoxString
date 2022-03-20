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

int
main()
{
    FoxString string = *new FoxString((char*)"I am going to be mutable FoxString");

    // string.New((char*)"I am going to be mutable FoxString");

    printf("\n%s\n", string.data);

    string.ReCreate((char*)"I am better version of C++ string");

    printf("New string: %s\nSize is: %d\n", string.data, string.size);

    printf("\nTaking input: ");
    printf("Your input is: %s\n", FoxStringInput().data);

    string.Replace(*new FoxString((char*)" "), *new FoxString((char*)"                    "), NO_LIMIT);

    printf("\nAfter .Replace\n%s\nSize is: %d", string.data, string.size);

    FoxString copy = string.Copy();

    string.Clean();

    printf("\n\nNew freshly copied FoxString:\n%s", copy.data);

    return 0;
}
