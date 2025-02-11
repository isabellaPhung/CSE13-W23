#include "io.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

uint64_t total_syms = 0;
uint64_t total_bits = 0;
//
// Read up to to_read bytes from infile and store them in buf. Return the number of bytes actually
// read.
//
// Since read() may not read in as many bytes as you asked for, this function should continuously
// call read() and attempt to read as many bytes as it has not yet read. For instance, if to_read is
// 100 and the first read() call only reads 20 bytes, it should attempt to read 80 bytes the next
// time it calls read().
//
int read_bytes(int infile, uint8_t *buf, int to_read) {
    int bytes_read = 0;
    int bytes = read(infile, buf, to_read);
    while (to_read != 0) {
        //printf("%d\n", bytes);
        if (bytes <= 0) {
            break;
        }
        bytes_read += bytes;
        to_read -= bytes;
        bytes = read(infile, buf, to_read);
    }
    return bytes_read;
}

//
// Write up to to_write bytes from buf into outfile. Return the number of bytes actually written.
//
// Similarly to read_bytes, this function will need to call write() in a loop to ensure that it
// writes as many bytes as possible.
//
int write_bytes(int outfile, uint8_t *buf, int to_write) {
    int bytes_written = 0;
    //for
    while (to_write != 0) {
        //printf("%"PRIu8"\n", buf[0]);
        int bytes = write(outfile, buf, to_write);
        if (bytes <= 0) {
            break;
        }
        bytes_written += bytes;
        to_write -= bytes;
    }
    return bytes_written;
}

//
// Read a file header from infile into *header.
//
// This function need not create any additional buffer to store the contents of the file header.
// File headers, like any struct or any value in C, are just represented by bytes in memory which
// means you can use read_bytes to read however many bytes the header consumes (use sizeof!) into
// *header.
//
// Since we decided that the canonical byte order for our headers is little-endian, this function
// will need to swap the byte order of both the header fields if it is run on a big-endian system.
// For example, here is how the 4 bytes of the magic number will look when written to the file:
//
// +------+------+------+------+
// | 0xAC | 0xBA | 0xAD | 0xBA |
// +------+------+------+------+
//
// A big-endian computer would interpret those bytes as the 4-byte number 0xACBAADBA, which is
// not what we want, so you would have to change the order of those bytes in memory. A little-endian
// computer will interpret that as 0xBAADBAAC.
//
// This function should also make sure the magic number is correct. Since it has no return value you
// may call assert() to do that, or print out an error message and exit the program, or use some
// other way to report the error.
//

//assuming little endianness for now.
void read_header(int infile, FileHeader *header) {
    read_bytes(infile, (uint8_t *) header, sizeof(FileHeader));
}

//
// Write a file header from *header to outfile. Like above, this function should swap the byte order
// of the header's two fields if necessary.
//

void write_header(int outfile, FileHeader *header) {
    write_bytes(outfile, (uint8_t *) header, sizeof(FileHeader));
}

uint8_t static *symbols;

void createBlock(void) {
    symbols = (uint8_t *) calloc(BLOCK, sizeof(uint8_t));
    return;
}

void clearBlock(void) {
    free(symbols);
    return;
}

//
// Read one symbol from infile into *sym. Return true if a symbol was successfully read, false
// otherwise.
//
// Reading one symbol at a time is slow, so this function will need to maintain a global buffer
// (an array) of BLOCK bytes. Most calls will only need to read a symbol out of that buffer, and
// then update some counter so that the function knows what position in the buffer it is at. If
// there are no more bytes in the buffer for it to return, it will have to call read_bytes to refill
// the buffer with fresh data. If this call fails then you cannot read a symbol and should return
// false.
//
bool read_sym(int infile, uint8_t *sym) {
    createBlock();
    uint64_t symcursor = 0;
    uint32_t read = 0;
    read = read_bytes(infile, symbols, BLOCK);
    if (read == 0) {
        return false;
    }
    while (read != 0) {
        total_syms += read;
        for (int i = 0; i < BLOCK; i++) {
            sym[symcursor] = symbols[i];
        }
        symcursor++;
        read = read_bytes(infile, symbols, BLOCK);
    }
    clearBlock();
    return true;
}

//
// Write a pair -- bitlen bits of code, followed by all 8 bits of sym -- to outfile.
//
// This function should also use a buffer. It writes into individual bits in the buffer, starting
// with the least significant bit of the first byte, until the most significant bit of the first
// byte, and then the least significant bit of the second byte, and so on. You will need bitwise
// arithmetic to manipulate individual bits within your buffer -- consult asgn3/set.c if you don't
// remember how to do this.
//
// The first bit of code to be written is the least significant bit, and the same holds for sym.
//
// This function will need to track which *bit* in the buffer will be written to next. If it ever
// reaches the end of the buffer it needs to write out the contents of the buffer to outfile; you
// may use flush_pairs to do this.
//

//calculates 2^(exponent)
uint32_t twoexponent(int exponent) {
    uint32_t total = 1;
    for (int i = 0; i < exponent; i++) {
        total *= 2;
    }
    return total;
}

static uint8_t *writepairbuffer;
static int writepaircursor;

void makewritepair(void) {
    writepairbuffer = (uint8_t *) calloc(BLOCK, sizeof(uint8_t));
}

void write_pair(int outfile, uint16_t code, uint8_t sym, int bitlen) {
    //uint32_t vectorlen = bitlen + 8;
    //just put char in first, shift left by bitlen, then insert code in right most bits
    uint32_t vector = sym;
    //printf("%"PRIu32"\n", vector);
    vector = vector << bitlen;
    vector = vector | code;
    //vector now written

    //vector may be 12 bits for example, how to write as a byte to a buffer limited by uint8?
    //or a vector of 8 bits with the 32 bit vector, right shift 32 bit vector by 8 until byteVector == 0

    if (writepaircursor == 0) {
        makewritepair();
    }
    int totalbits = bitlen + 8;
    int pairindex = writepaircursor / 8;
    //bitindex = writepaircursor %8;
    int byteVector = 0;
    printf("writepaircursor: %d\n", writepaircursor);
    if (writepaircursor % 8 != 0) { //if doesn't start at byte alignment
        int index = (((pairindex + 1) * 8) - writepaircursor);
        int downshift = 8 - index;
        byteVector = twoexponent(index);
        byteVector = byteVector & vector;
        writepairbuffer[pairindex] = writepairbuffer[pairindex] | (byteVector << downshift);
        writepaircursor += index;
        vector = vector >> index;
        totalbits -= index;
    }

    byteVector = 255;
    byteVector = byteVector & vector;
    pairindex = writepaircursor / 8;
    //int bitindex = totalbits %8; //any remaining bits at the end
    //byteVector now hold 8 bits of the pieced together pair
    printf("byteVector: %" PRIu8 "\n", byteVector);
    uint32_t count = 0;
    while (byteVector != 0) {
        writepairbuffer[count] = byteVector;
        count++;
        vector = vector >> 8;
        byteVector = 255; //reset byteVector;
        byteVector = byteVector & vector;
        printf("byteVector2: %" PRIu8 "\n", byteVector);
    }
    writepaircursor += totalbits;
    // we now have a buffer with the bits of the pair written, write buffer to output.
    //    for(uint32_t i = 0; i < count; i++){
    //       printf("%"PRIu8 ", ", pairbuffer[i]);
    //  }
    // printf("\n");

    write_bytes(outfile, writepairbuffer, count);
    if (writepaircursor >= 4096 * 8) {
        free(writepairbuffer);
        writepaircursor = 0;
    }
}

//
// Write any pairs that are in write_pair's buffer but haven't been written yet to outfile.
//
// This function will need to be called at the end of encode since otherwise those pairs would never
// be written. You don't have to, but it would be easy to make this function also work when called
// by write_pair, since otherwise you would write essentially the same code in two places.
//
// If not all bits of the last byte in your buffer have been written to, make sure that the
// unwritten bits are set to zero. An easy way to do this is by zeroing the entire buffer after
// flushing it every time.
//

void flush_pairs(int outfile) {
    read(outfile, NULL, 0);
    return;
}

//
// Read bitlen bits of a code into *code, and then a full 8-bit symbol into *sym, from infile.
// Return true if the complete pair was read and false otherwise.
//
// Like write_pair, this function must read the least significant bit of each input byte first, and
// will store those bits into the LSB of *code and of *sym first.
//
// It may be useful to write a helper function that reads a single bit from a file using a buffer.
//

static uint8_t *readpairbuffer;
static int readpaircursor = 0;
static uint32_t bufferVector = 0;

void makereadpair(void) {
    readpairbuffer = (uint8_t *) calloc(BLOCK, sizeof(uint8_t));
}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, int bitlen) {
    if (readpaircursor == 0) {
        makereadpair();

        read_bytes(infile, readpairbuffer, BLOCK);
        bufferVector = readpairbuffer[readpaircursor / 8 + 3] << 24
                       | readpairbuffer[readpaircursor / 8 + 2] << 16
                       | readpairbuffer[readpaircursor / 8 + 1] << 8
                       | readpairbuffer[readpaircursor / 8];
        printf("%" PRIu8 "\n", readpairbuffer[readpaircursor / 8 + 2]);
        readpaircursor += 32;
    }

    //printf("readpaircursor:%d\n",readpaircursor);
    //extract code and sym
    //printf("bufferVector: %"PRIu32"\n",bufferVector);
    uint32_t codeVector = (twoexponent(bitlen) - 1);
    //printf("codeVector: %"PRIu32"\n", codeVector);
    codeVector = codeVector & bufferVector;
    *code = codeVector;
    bufferVector = bufferVector >> bitlen;
    uint32_t symbolVector = 255;
    symbolVector = symbolVector & bufferVector;
    *sym = symbolVector;
    bufferVector = bufferVector >> 8;

    //sym and code acquired now to add more values to bufferVector
    int totalbits = 8 + bitlen;
    int pairindex = readpaircursor / 8;
    //printf("pairindex: %d\n", pairindex);
    int bitindex = bitlen % 8;
    //printf("bitindex: %d\n",bitindex);
    uint32_t byteVector = 0;
    int downshift = 0;
    //int remaining = bitlen;

    if (readpaircursor % 8 != 0) { //if cursor is not at start of bit
        int index = (((pairindex + 1) * 8) - readpaircursor);
        downshift = 8 - index;
        byteVector = 0;
        byteVector = 255 - (twoexponent(downshift) - 1);
        byteVector = byteVector & readpairbuffer[pairindex];
        byteVector = byteVector >> downshift;
        byteVector = byteVector << (32 - totalbits);
        bufferVector = bufferVector | byteVector;
        readpaircursor += index;
        //remaining -=
    }

    pairindex = readpaircursor / 8;
    //printf("pairindex: %d\n", pairindex);
    //for(int i = 0; i < 20; i++){
    //    printf("%"PRIu8"\n", readpairbuffer[i]);
    // }
    //remainder of bits that align with the bytes
    for (int i = 0; i < totalbits / 8; i++) {
        //printf("i: %d\n", i);
        byteVector = 0;
        byteVector = byteVector | readpairbuffer[pairindex + i];
        //printf("byte: %"PRIu8 "\n", readpairbuffer[pairindex + i]);
        //printf("byteVector: %"PRIu32"\n", byteVector);
        byteVector = byteVector << ((32 - totalbits) + (8 * i) - downshift);
        bufferVector = bufferVector | byteVector;
    }
    readpaircursor += pairindex * 8;
    //printf("pairindex: %d\n", pairindex);

    pairindex = bitlen / 8;

    //any remaining bits at end
    byteVector = 0;
    byteVector = twoexponent(bitindex) - 1;
    byteVector = byteVector & readpairbuffer[pairindex + 1];
    byteVector = byteVector << 24;
    bufferVector = bufferVector | byteVector;
    readpaircursor += bitindex;

    if (readpaircursor >= 4096 * 8) {
        free(readpairbuffer);
        readpaircursor = 0;
        bufferVector = 0;
        return false;
    }
    return true;
}

//
// Write every symbol from w into outfile.
//
// These symbols should also be buffered and the buffer flushed whenever necessary (note you will
// likely sometimes fill up your buffer in the middle of writing a word, so you cannot only check
// that the buffer is full at the end of this function).
//
static uint8_t *buffer;

void write_word(int outfile, Word *w) {
    buffer = (uint8_t *) calloc(BLOCK, sizeof(uint8_t));
    uint32_t cursor = 0;
    for (uint32_t i = 0; i < w->len; i++) {
        if (cursor == BLOCK - 1) {
            write_bytes(outfile, buffer, w->len);
            //reset buffer to 0s
            for (int i = 0; i < BLOCK; i++) {
                buffer[i] = 0;
            }
            cursor = 0;
        }
        buffer[cursor] = *(w->syms);
        cursor++;
    }
}

//
// Write any unwritten word symbols from the buffer used by write_word to outfile.
//
// Similarly to flush_pairs, this function must be called at the end of decode since otherwise you
// would have symbols remaining in the buffer that were never written.
//
void flush_words(int outfile) {
    write_bytes(outfile, buffer, BLOCK);
    free(buffer);
}
