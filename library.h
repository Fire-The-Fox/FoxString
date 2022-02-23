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
} FString;

typedef struct {
    FString *array;
    int size;
    char created; // using as much little memory as possible
} FStringArray;

FString
FString_New(char *init);

void
FString_Clean(FString *string);

FString
FString_ReCreate(FString *string, char *init);

FString
FStringInput();

int
FString_Count(FString string, char detect);

int
FString_Find(FString string, char detect);

int
FString_Contains(FString str1, FString str2);

int
FString_Add(FString* string, char character);

int
FString_Pop(FString* string);

int
FString_Connect(FString* mainString, FString sideString);

FString
FString_Replace(FString string, char oldChar, char newChar, int count);

int
FString_Compare(FString str1, FString str2);

FStringArray
FString_Split(FString string, char splitChar);

FStringArray
FStringArray_Create();

int
FStringArray_Append(FStringArray *array, FString string);

FString
FStringArray_Get(FStringArray array, int index);

int
FStringArray_Insert(FStringArray *array, int index, FString string);

int
FStringArray_Replace(FStringArray *array, int index, FString string);

int
FStringArray_Remove(FStringArray *array, int index);

int
FStringArray_Index(FStringArray array, FString string);

int
FStringArray_Clean(FStringArray *array);

FStringArray
FStringArray_ReCreate(FStringArray *array);

#else

class FString {
    public:
        char *data;
        unsigned int size;

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
        Contains(FString string) const;

        int
        Connect(FString string);

        int
        Pop();

        int
        Replace(char* oldString, char* newString, int count);

        int
        Compare(FString string);
};

FString
FStringInput();
#endif

#endif //FOXSTRING_LIBRARY_H
