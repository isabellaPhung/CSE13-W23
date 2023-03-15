//Written by Isabella Phung for CSE 13S with comments from CSE13S instructors.
#include "trie.h"
#include "code.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
 * Creates a new TrieNode and returns a pointer to it
 * Allocate memory for TrieNode
 * Code is the code to be assigned to this new node
 * Returns the newly allocated node
 */
TrieNode *trie_node_create(uint16_t code) {
    TrieNode *node = (TrieNode *) malloc(sizeof(TrieNode));
    node->code = code;
    //node -> children = (TrieNode **) calloc(ALPHABET, sizeof(TrieNode *));
    for (int i = 0; i < ALPHABET; i++) {
        node->children[i] = NULL;
    }
    //printf("%"PRIu16"\n", code);
    return node;
}
//checks if node is leaf
bool leafcheck(TrieNode *n) {

    for (int i = 0; i < ALPHABET; i++) {
        if (n->children[i] != NULL) {
            return false;
        }
    }
    return true;
}

/*
 * Deletes Node n
 * Frees any allocated memory
 */
void trie_node_delete(TrieNode *n) {
    if (n == NULL) {
        return;
    }
    if (!leafcheck(n)) {
        for (int i = 0; i < ALPHABET; i++) {
            trie_delete(n->children[i]);
        }
    }
    //if leafnode aka all children are null
    free(n);
    n = NULL;
}

/*
 * Constructor: Creates the root TrieNode and returns a pointer to it
 * Allocate memory for TrieNode
 * Code is START_CODE
 * Returns the newly allocated node
 */
TrieNode *trie_create(void) {
    TrieNode *root = trie_node_create(START_CODE);
    return root;
}

/*
 * Resets the trie: called when code reaches MAX_CODE
 * Deletes all the children of root and frees allocated memory
 */
void trie_reset(TrieNode *root) {
    if (root == NULL) {
        return;
    }
    if (leafcheck(root)) { //if leaf node, free node and return
        trie_node_delete(root);
        return;
    }
    //not leaf node
    //has children so children must be freed first
    for (int i = 0; i < ALPHABET; i++) {
        trie_node_delete(root->children[i]);
        root->children[i] = NULL;
    }
}

/*
 * Destructor: Deletes all nodes starting at n as the root
 * Deletes any children recursively before deleting the root
 * Frees all the memory allocated for TrieNodes n and below
 */
void trie_delete(TrieNode *n) {
    if (n == NULL) {
        return;
    }
    if (leafcheck(n)) { //if leaf node, free node and return
        trie_node_delete(n);
        return;
    }
    //not leaf node
    //has children so children must be freed first
    for (int i = 0; i < ALPHABET; i++) {
        trie_node_delete(n->children[i]);
        n->children[i] = NULL;
    }
    free(n);
}

/*
 * Checks if node has any children called sym
 * Returns the address if found, NULL if absent
 */
TrieNode *trie_step(TrieNode *n, uint8_t sym) {
    if (n == NULL) {
        return NULL;
    }
    if (n->children[sym] != NULL) { //if symbol is a child, return child node
        return n->children[sym];
    }
    TrieNode *childcheck = NULL;
    int i = 0;
    while (i < ALPHABET && childcheck == NULL) {
        childcheck = trie_step(n->children[i], sym);

        i++;
    }

    return childcheck;
}
