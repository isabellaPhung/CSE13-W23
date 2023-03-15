#include "word.h"
#include <stdlib.h>
#include "code.h"

/*
 * Creates a new Word with symbols syms and length len
 * Allocates new array and copies the symbols over
 */
Word *word_create(uint8_t *syms, uint32_t len) {
    Word *newWord = (Word *) calloc(len, sizeof(Word));
    newWord->len = len;
    uint8_t *symbols = (uint8_t *) calloc(len, sizeof(uint8_t));
    for (uint32_t i = 0; i < len; i++) {
        symbols[i] = syms[i];
    }
    newWord->syms = symbols;
    return newWord;
}

/*
 * Creates a new word by appending symbol sym to word w
 * Updates the length of the new word and copies symbols over
 * Returns a pointer to the newly allocated word
 */
Word *word_append_sym(Word *w, uint8_t sym) {
    uint32_t newLen = w->len + 1;
    uint8_t *newSyms = (uint8_t *) calloc(newLen, sizeof(uint8_t));
    for (uint32_t i = 0; i < w->len; i++) {
        newSyms[i] = w->syms[i];
    }
    newSyms[w->len] = sym;
    Word *newWord = word_create(newSyms, newLen);
    return newWord;
}

/*
 * Deletes the word w
 * Frees up associated space
 */
void word_delete(Word *w) {
    free(w->syms);
    free(w);
    w = NULL;
}

/*
 * Constructor:
 * Creates a new table big enough to fit MAX_CODE
 * Creates the first element at EMPTY_CODE and returns it
 */
WordTable *wt_create(void) {
    WordTable *wt = (WordTable *) calloc(MAX_CODE, sizeof(WordTable));

    uint8_t emptystring[1] = "\0";
    Word *empty = word_create(emptystring, 0);
    wt[EMPTY_CODE] = empty;
    return wt;
}

/*
 * Deletes all words except EMPTY_CODE
 * Frees associated memory
 */
void wt_reset(WordTable *wt) {
    for (uint32_t i = START_CODE; i < MAX_CODE; i++) {
        free(wt[i]);
        wt[i] = NULL;
    }
}

/*
 * Destructor: Deletes all words and tables
 * Frees up associated memory
 */
void wt_delete(WordTable *wt) {
    wt_reset(wt);
    free(wt[EMPTY_CODE]);
    free(wt);
    wt = NULL;
}
