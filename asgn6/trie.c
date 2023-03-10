//Written by Isabella Phung for CSE 13S with comments from CSE13S instructors.
#include "trie.h"
#include "code.h"

/*
 * Creates a new TrieNode and returns a pointer to it
 * Allocate memory for TrieNode
 * Code is the code to be assigned to this new node
 * Returns the newly allocated node
 */
TrieNode *trie_node_create(uint16_t code){
    TrieNode *node = (node *)calloc(sizeof(TrieNode));
    node -> code = code;
    node -> children = NULL;
    return node;
}

/*
 * Deletes Node n
 * Frees any allocated memory
 */
void trie_node_delete(TrieNode *n){
    free(n);
}

/*
 * Constructor: Creates the root TrieNode and returns a pointer to it
 * Allocate memory for TrieNode
 * Code is START_CODE
 * Returns the newly allocated node
 */
TrieNode *trie_create(void){
    TrieNode *root = trie_node_create(START_CODE); 
    return root;
}

/*
 * Resets the trie: called when code reaches MAX_CODE
 * Deletes all the children of root and frees allocated memory
 */
void trie_reset(TrieNode *root){
    if(root -> children == NULL){
        trie_node_delete(root);
        return;
    }
    for(int i = 0; i<ALPHABET; i++){
        trie_node_delete(root -> children[i]);
    }
    
}

/*
 * Destructor: Deletes all nodes starting at n as the root
 * Deletes any children recursively before deleting the root
 * Frees all the memory allocated for TrieNodes n and below
 */
void trie_delete(TrieNode *n){
    trie_reset(n);
    free(n);
    n = NULL;
}

/*
 * Checks if node has any children called sym
 * Returns the address if found, NULL if absent
 */
TrieNode *trie_step(TrieNode *n, uint8_t sym){
    if(n->children == NULL){
        return NULL;
    }else if(root -> code == sym){
        return root;
    }else{
        trie_step(n);
    }
}


