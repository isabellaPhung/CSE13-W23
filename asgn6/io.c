#include "io.h"

int read_bytes(int infile, uint8_t *buf, int to_read){

}

int write_bytes(int outfile, uint8_t *buf, int to_write){

}

void read_header(int infile, FileHeader *header){

}

void write_header(int outfile, FileHeader *header){

}

bool read_sym(int infile, uint8_t *sym){

}

void write_pair(int outfile, uint16_t code, uint8_t sym, int bitlen){

}

void flush_pairs(int outfile){

}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, int bitlen){

}

void write_word(int outfile, Word *w){

}

void flush_words(int outfile){

}

