/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>
#include <chrono>
#include <random>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <functional>

using namespace std;

// sequential implementation using separate chaining technique
class hashtable
{
    int numBuckets, listLen;
    list<int> *myTable;

public:
    hashtable(int numBuckets, int listLen)
    {
        this->numBuckets = numBuckets;
        this->listLen = listLen;
        myTable = new list<int>[numBuckets];
    }

    // destructor
    ~hashtable()
    {
        printf("hastable object destroyed");
    }

    int hashFunction(int value)
    {
        int retVal = (value * 31) % this->numBuckets;
        return retVal;
    }

    // for some reason, I couldn't find the built-in size method that
    // every list in C++ should have, so I went on ahead and created my own
    int getSize(int hashedIndex)
    {
        int acc = 0;

        for (auto val : myTable[hashedIndex])
        {
            ++acc;
        }

        return acc;
    }

    void insert(int value)
    {
        int hashedIndex = hashFunction(value);

        //            cout << "inserted " << value << endl;
        int hashedListSize = getSize(hashedIndex);

        // checks if we need to expand the hash table before inserting
        if (hashedListSize >= listLen)
        {
            // cout << "hashedListSize: " << hashedListSize << endl; // DEBUG PRINT STATEMENT
            // cout << "listLen: " << listLen << endl; // DEBUG PRINT STATEMENT

            expand();
        }

        myTable[hashedIndex].push_back(value);

        // we always sort the list located at the given hashedIndex
        // so that the numbers are in order [O(n log n) runtime]
        myTable[hashedIndex].sort();
    }

    // doubles the table size and
    // increases the max allowed size per list by 1
    void expand()
    {
        ++this->listLen;
        int tmp = this->numBuckets;
        this->numBuckets *= 2;

        cout << "made it with " << tmp << " and " << this->numBuckets << endl; // DEBUG
        rehash(tmp);
    }

    void rehash(int prevListLen)
    {
        vector<int> tmp;

        // takes everything that I have out of the list at specified index i
        // and stores them in a vector
        for (int i = 0; i < prevListLen; i++)
        {
            copy(myTable[i].begin(), myTable[i].end(), back_inserter(tmp));

            // clear list so we can safely re-insert values
            myTable[i].clear();

            // just for debugging purposes
            // cout << "vector contents: " << endl;
            // for (int val : tmp) {
            //     cout << val << endl;
            // }
        }

        // the list pointer now points to more buckets
        myTable = new list<int>[numBuckets];

        for (int val : tmp)
        {
            // and re-insert
            int hashedIndex = hashFunction(val);
            // cout << "hashedIndex for " << val << ": " << hashedIndex << endl;
            myTable[hashedIndex].push_back(val);
            // cout << "re-inserted " << val << endl;
        }

        // clean up after yourself
        tmp.clear();
    }

    void delete_elem(int value)
    {
        // in order to delete, we must find it first to avoid
        // any weird errors or behaviors

        list<int>::iterator itr;
        int hashedIndex = hashFunction(value);

        // find the value we're looking for using itr
        for (itr = myTable[hashedIndex].begin();
             itr != myTable[hashedIndex].end(); itr++)
        {
            if (*itr == value)
            {
                break;
            }
        }

        // if we haven't iterated thru the whole list,
        // then we're guaranteed to stopped somewhere
        // on the value we're searching for
        if (itr != myTable[hashedIndex].end())
        {
            myTable[hashedIndex].erase(itr);
        }
        else
        {
            cout << value << " couldn't be deleted because it doesn't exist in the list" << endl;
        }
    }

    void printContents()
    {
        cout << "final contents" << endl;
        for (int i = 0; i < numBuckets; i++)
        {
            cout << '[' << i << ']';
            for (auto val : myTable[i])
            {
                cout << " --> " << val;
            }
            cout << endl;
        }
        cout << endl;
    }

    bool search(int value)
    {
        // search the linked list at 'hashedIndex'
        int hashedIndex = hashFunction(value);

        for (list<int>::iterator itr = myTable[hashedIndex].begin();
             itr != myTable[hashedIndex].end(); ++itr)
        {
            if (*itr == value)
            {
                std ::cout << value << " found" << std ::endl;
                return true;
            }
        }

        std ::cout << value << " not found" << std ::endl;
        return false;
    }

    // insert, delete, search
    // token for the type of operation to perform on hashtable and randomValue for the value apply
    // in that operation
    void random_ops(int randomToken, int randomValue)
    {
        if (randomToken == 0)
        {
            printf("inserted\n");
            insert(randomValue);
        }
        else if (randomToken == 1 || randomToken == 2)
        {
            printf("deleted\n");
            delete_elem(randomValue);
        }
        else if (randomToken == 3)
        {
            printf("searched\n");
            search(randomValue);
        }
    }
};

int main(int argc, char const *argv[])
{
    // listLen is set an initial max length allowed per list in the
    // array of lists, which is 2 in this case
    int numValuesToInsert = 100, numBuckets = 1, listLen = 2;

    srand(time(nullptr));
    hashtable ht(numBuckets, listLen);

    // Begin time.
    long duration;

    auto start = std::chrono::steady_clock::now();
    for (int i = 1; i <= numValuesToInsert; i++)
    {
        ht.random_ops(rand() % 4, rand() % 101);
    }
    auto end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    ht.printContents();

    std ::cout << "total runtime in ms: " << duration << std ::endl;

    return 0;
}
