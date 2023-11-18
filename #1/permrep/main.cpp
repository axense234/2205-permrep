#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>

/*
aamm

copies
 1 2
[a,m]
[2,2]

aamm
1122

a aa aam aamm -> aamm
1 11 112 1122

when validating we check if the number of current copies of x char is lesser than max amount of copies

aamm -> amam -> amma -> maam -> mama -> mmaa
1122   1212     1221    2112    2121    2211


*/

#define MAX_LENGTH 10

using namespace std;

ifstream inputFile("permrep.in");
ofstream runtimeDurationsFile("runtimeDurations.out", ios::app);
ofstream outputFile("permrep.out");

char charListInput[MAX_LENGTH];

char uniqueChars[MAX_LENGTH];
short int uniqueCharsLength = 0;
short int maxCopiesOfUniqueChars[MAX_LENGTH];
short int currentCharIndice = 0;

void sortCharListInput()
{
    // Sort the list of chars
    for (int i = 0; i < strlen(charListInput) - 1; i++)
    {
        for (int j = i; j < strlen(charListInput); j++)
        {
            if (charListInput[i] > charListInput[j])
            {
                swap(charListInput[i], charListInput[j]);
            }
        }
    }
    cout << charListInput << endl;
}

bool canBeAddedToUniqueChars(char currentChar)
{
    for (int i = 1; i <= uniqueCharsLength; i++)
    {
        if (uniqueChars[i] == currentChar)
        {
            return false;
        }
    }
    return true;
}

void constructCopiesMax()
{
    int currentCharNumber = 0;
    for (int i = 0; i < strlen(charListInput); i++)
    {
        char currentChar = charListInput[i];
        if (currentChar != charListInput[i - 1] && canBeAddedToUniqueChars(currentChar))
        {
            currentCharNumber += 1;
            uniqueChars[currentCharNumber] = currentChar;
            uniqueCharsLength++;

            for (int j = 0; j < strlen(charListInput); j++)
            {
                if (currentChar == charListInput[j])
                {
                    maxCopiesOfUniqueChars[currentCharNumber]++;
                }
            }
        }
    }
}

void readInputFile()
{

    inputFile.getline(charListInput, MAX_LENGTH);
    if (strlen(charListInput) == 0)
    {
        cout << "empty file boy" << endl;
        return;
    }
    sortCharListInput();
    constructCopiesMax();
    for (int i = 1; i <= uniqueCharsLength; i++)
    {
        cout << uniqueChars[i] << ' ';
    }
    cout << endl;
    for (int i = 1; i <= uniqueCharsLength; i++)
    {
        cout << maxCopiesOfUniqueChars[i] << ' ';
    }
    cout << endl;
}

void printOutputFile(char C[MAX_LENGTH])
{
    cout << C << endl;
    outputFile << C << endl;
}

void init(char C[MAX_LENGTH], int k)
{
    C[k] = ' ';
}

bool succesor(char C[MAX_LENGTH], int k)
{
    if (currentCharIndice < uniqueCharsLength)
    {
        C[k] = uniqueChars[currentCharIndice + 1];
        currentCharIndice += 1;
        return true;
    }
    return false;
}

bool valid(char C[MAX_LENGTH], int k)
{
    int copiesMaxNumber = 1;
    int copiesCurrentNumber = 0;
    // Find the max amount of copies for current char
    copiesMaxNumber = maxCopiesOfUniqueChars[currentCharIndice];
    // Find copies of current char in C
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        if (C[k] == C[i])
        {
            copiesCurrentNumber++;
        }
    }
    return (copiesCurrentNumber <= copiesMaxNumber);
}

bool solution(char C[MAX_LENGTH], int k)
{
    return k == strlen(charListInput) - 1;
}

void bt(char C[MAX_LENGTH])
{
    int k = 0;
    init(C, k);
    bool s = false, v = false;
    while (k > -1)
    {
        do
        {
            s = succesor(C, k);
            if (s)
            {
                v = valid(C, k);
            }
        } while (s && !v);
        if (s)
        {
            if (solution(C, k))
            {
                printOutputFile(C);
            }
            else
            {
                init(C, ++k);
                currentCharIndice = 0;
            }
        }
        else
        {
            init(C, k);
            k--;
            for (int i = 1; i <= uniqueCharsLength; i++)
            {
                if (uniqueChars[i] == C[k])
                {
                    currentCharIndice = i;
                    break;
                }
            }
        }
    }
}

int main()
{
    auto start = chrono::high_resolution_clock::now();
    char C[MAX_LENGTH] = "";
    readInputFile();
    bt(C);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Runtime: " << duration.count() << " seconds" << endl;
    runtimeDurationsFile << strlen(charListInput) << ' ' << duration.count() << " seconds" << endl;
    runtimeDurationsFile.close();

    return 0;
}