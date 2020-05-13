#include <iostream>
using namespace std;

// the following implementation is for strings containing a..z

typedef struct trie {
	trie* children[26] = {};
	bool isleaf = false;
} trie;

trie root;

void trie_add(string s) {
	trie* cur = &root;
	for (char c : s) {
		if (cur->children[c-'a'] == NULL)
			cur->children[c-'a'] = new trie;
		cur = cur->children[c-'a'];
	}
	cur->isleaf = true;
}

void trie_clear(trie* cur) {
    for (int i = 0; i < 26; i++)
        if (cur->children[i] != NULL) {
            trie_clear(cur->children[i]);
            delete cur->children[i];
            cur->children[i] = NULL;
        }
}

bool trie_contains(string s) {
	trie* cur = &root;
	for (char c : s) {
		if (cur->children[c-'a'] == NULL)
			return false;
		cur = cur->children[c-'a'];
	}
	return cur->isleaf;
}