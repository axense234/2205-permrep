#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>

#define MAX_LENGTH 10

using namespace std;

ifstream inputFile("permrep.in");
ofstream outputFile("permrep.out");
ofstream runningTimesFile("runningTimes.out", ios::app);

char charList[MAX_LENGTH];
short int charListLength = 0;

char setOfPermutations[10000000][MAX_LENGTH];
int numberOfSetPermutations = 0;

void sortCharList()
{
    for (int i = 0; i < charListLength - 1; i++)
    {
        for (int j = i; j < charListLength; j++)
        {
            if (charList[i] > charList[j])
            {
                swap(charList[i], charList[j]);
            }
        }
    }
    cout << charList << endl;
}

void inputCharList()
{
    inputFile.getline(charList, MAX_LENGTH);
    charListLength = strlen(charList);
    if (charListLength == 0)
    {
        cout << "file is empty" << endl;
        return;
    }
    sortCharList();
}

void outputCharList(int A[MAX_LENGTH])
{
    char result[MAX_LENGTH] = "";
    for (int i = 1; i <= charListLength; i++)
    {
        char charInCharList = charList[A[i] - 1];
        result[i - 1] = charInCharList;
    }
    for (int i = 1; i <= numberOfSetPermutations; i++)
    {
        if (strcmp(setOfPermutations[i], result) == 0)
        {
            return;
        }
    }
    numberOfSetPermutations++;
    strcpy(setOfPermutations[numberOfSetPermutations], result);
    outputFile << result << endl;
    cout << result << endl;
}

bool succesor(int A[MAX_LENGTH], int k)
{
    if (A[k] < charListLength)
    {
        A[k]++;
        return true;
    }
    return false;
}

bool valid(int A[MAX_LENGTH], int k)
{
    for (int i = 1; i < k; i++)
    {
        if (A[i] == A[k])
        {
            return false;
        }
    }
    return true;
}

bool solution(int k)
{
    return k == charListLength;
}

void init(int A[MAX_LENGTH], int k)
{
    A[k] = 0;
}

void bt(int A[MAX_LENGTH])
{
    int k = 1;
    init(A, k);
    bool s = false, v = false;
    while (k > 0)
    {
        do
        {
            s = succesor(A, k);
            if (s)
            {
                v = valid(A, k);
            }
        } while (s && !v);
        if (s)
        {
            if (solution(k))
            {
                outputCharList(A);
            }
            else
            {
                init(A, ++k);
            }
        }
        else
        {
            k--;
        }
    }
}

int main()
{
    auto start = chrono::high_resolution_clock::now();
    int A[MAX_LENGTH];
    inputCharList();
    bt(A);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Running time is: " << duration.count() << " seconds" << endl;
    runningTimesFile << charListLength << ' ' << duration.count() << " seconds" << endl;
    runningTimesFile.close();

    return 0;
}