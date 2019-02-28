#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "trie.h"

#include <iostream>
using std::cout;
using std::endl;

int main()
{
    TrieTree trieTree;
    cout << "insert `hello` into trie-tree.\n";
    trieTree.addString("hello");

    cout << "insert `hello` into trie-tree again.\n";
    trieTree.addString("hello");

    cout << "insert `hellk` into trie-tree.\n";
    trieTree.addString("hellk");

    // ----------------------------------------------------------------------
    cout << "\ncontains(`hello`): ";
    cout << trieTree.findString("hello") << endl;
    cout << "contains(`hellk`): ";
    cout << trieTree.findString("hellk") << endl;
    cout << "contains(`abc`): ";
    cout << trieTree.findString("abc") << endl;
    cout << "contains(`hellok`): ";
    cout << trieTree.findString("hellok") << endl;
    cout << "contains(`he`): ";
    cout << trieTree.findString("he") << endl;
    cout << "contains(``): ";
    cout << trieTree.findString("") << endl;

    // ----------------------------------------------------------------------
    cout << "\nafter delete `hello`\n";
    trieTree.delString("hello");

    cout << "contains(`hello`): ";
    cout << trieTree.findString("hello") << endl;
    cout << "contains(`hellk`): ";
    cout << trieTree.findString("hellk") << endl;

    // ----------------------------------------------------------------------
    cout << "\ninsert `hello` again\n";
    trieTree.addString("hello");

    cout << "contains(`hello`): ";
    cout << trieTree.findString("hello") << endl;
    cout << "contains(`hellk`): ";
    cout << trieTree.findString("hellk") << endl;

    // ----------------------------------------------------------------------
    {
        char buf[64];
        TrieTree *ttree = new TrieTree;
        for (int i = 0; i < 100; ++i) {
            sprintf(buf, "%d\0", i);
            ttree->addString(buf);
        }
        delete ttree;
    }

    getchar();
    return 0;
}