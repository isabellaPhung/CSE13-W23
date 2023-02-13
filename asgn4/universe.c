//Written by Isabella Phung for CSE13S
//with struct code provided by CSE13S instructors.
#include "universe.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Universe {
    uint32_t rows;
    uint32_t cols;
    bool **grid;
    bool toroidal;
};

//creates and allocates a new empty universe.
//accepts # of rows and cols and if it's a toroidal universe
Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal) {
    Universe *universe = (Universe *) malloc(sizeof(universe));
    universe->grid = (bool **) calloc(rows, sizeof(bool *));
    assert(universe->grid); //check if allocated.
    universe->rows = rows;
    universe->cols = cols;

    for (uint32_t i = 0; i < rows; i++) {
        universe->grid[i] = (bool *) calloc(cols, sizeof(bool));
        assert(universe->grid[i] != NULL);
    }
    universe->toroidal = toroidal;
    return universe;
}

//deletes universe and deallocates memory
//accepts universe struct as parameter.
void uv_delete(Universe *u) {
    for (uint32_t i = 0; i < (uv_rows(u)); i++) {
        free(u->grid[i]);
        u->grid[i] = NULL;
    }
    free(u->grid);
    u->grid = NULL;
    free(u);
    u = NULL;
}

//returns universe rows, accepts universe parameter
uint32_t uv_rows(Universe *u) {
    return u->rows;
}

//returns universe columns, accepts universe parameter
uint32_t uv_cols(Universe *u) {
    return u->cols;
}

//sets cell in universe as alive
//accepts universe, then row and column of target cell
void uv_live_cell(Universe *u, uint32_t r, uint32_t c) {
    u->grid[r][c] = true;
}

//sets cell in universe as dead
//accepts universe, then row and column of target cell
void uv_dead_cell(Universe *u, uint32_t r, uint32_t c) {
    u->grid[r][c] = false;
}

//returns cell, accepts universe parameter, then row and column of target.
bool uv_get_cell(Universe *u, uint32_t r, uint32_t c) {
    return u->grid[r][c];
}

//accepts universe and a file stream from a document or stdin
//populates given universe using indicated coordinates in document
// with live cells.
bool uv_populate(Universe *u, FILE *infile) {
    //parse value with fscanf
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t index = 0;
    uint32_t totalCells = (u->rows) * (u->cols);
    int argNum = 0;

     while ((argNum = fscanf(infile, "%" SCNd32, &x) != EOF)) {
        //if value exceeds universe or more cells inputted than can fit in universe, return false
        if ((x > (u->rows) - 1) || (y > (u->cols) - 1) || index > totalCells
            || argNum == 0) {
                   return false;
        }
        fscanf(infile, "%" SCNd32, &y);
        uv_live_cell(u, x, y);
        index++;
    }
    return true;
}

//evaluates neighboring cells for live cells and returns number of live neighbors
//accepts universe, row, and column of specified cell
uint32_t uv_census(Universe *u, uint32_t r, uint32_t c) {
    //creates list of neighbor coordinates regardless of location first
    //order of list is: top, top right, right, bottom right, bottom
    //bottom left, left, top left

    //signed int used since neighbors may dip below 0
    int32_t **neighbors = (int32_t **) calloc(8, sizeof(int32_t *));
    for (int i = 0; i < 8; i++) {
        neighbors[i] = (int32_t *) calloc(2, sizeof(int32_t));
    }

    neighbors[1][1] = c + 1;
    neighbors[2][1] = c + 1;
    neighbors[3][1] = c + 1;

    neighbors[5][1] = c - 1;
    neighbors[6][1] = c - 1;
    neighbors[7][1] = c - 1;

    neighbors[0][1] = c;
    neighbors[4][1] = c;

    neighbors[3][0] = r + 1;
    neighbors[4][0] = r + 1;
    neighbors[5][0] = r + 1;

    neighbors[7][0] = r - 1;
    neighbors[0][0] = r - 1;
    neighbors[1][0] = r - 1;

    neighbors[2][0] = r;
    neighbors[6][0] = r;

    int32_t width = uv_cols(u);
    int32_t height = uv_rows(u);
    if (!u->toroidal) {
        if (c == width - 1) { //if on right edge of universe
            //no right neighbors
            free(neighbors[1]);
            neighbors[1] = NULL;
            free(neighbors[2]);
            neighbors[2] = NULL;
            free(neighbors[3]);
            neighbors[3] = NULL;
        }
        if (c == 0) { // if on left edge of universe
            //no left neighbors
            free(neighbors[5]);
            neighbors[5] = NULL;
            free(neighbors[6]);
            neighbors[6] = NULL;
            free(neighbors[7]);
            neighbors[7] = NULL;
        }
        if (r == height - 1) { //if on bottom edge of universe
            //no bottom neighbors
            free(neighbors[3]);
            neighbors[3] = NULL;
            free(neighbors[4]);
            neighbors[4] = NULL;
            free(neighbors[5]);
            neighbors[5] = NULL;
        }
        if (r == 0) { // if on top edge of universe
            //no top neighbors
            free(neighbors[7]);
            neighbors[7] = NULL;
            free(neighbors[0]);
            neighbors[0] = NULL;
            free(neighbors[1]);
            neighbors[1] = NULL;
        }
    } else { //if toroidal
        for (uint32_t i = 0; i < 8; i++) {
            //% gets funky with signed ints when going to unsigned ints.
            neighbors[i][1] = ((neighbors[i][1] % width) + width) % width;
            neighbors[i][0] = ((neighbors[i][0] % height) + height) % height;
        }
    }
    //after adjusting neighbors, add up live neighbors.
    uint32_t total = 0;
    uint32_t x = 0;
    uint32_t y = 0;
    for (int i = 0; i < 8; i++) {
        if (neighbors[i] != NULL) {
            x = neighbors[i][0];
            y = neighbors[i][1];
            if (u->grid[x][y]) {
                total++;
            }
        }
    }

    //once done, free list of neighbors
    for (int i = 0; i < 8; i++) {
        free(neighbors[i]);
        neighbors[i] = NULL;
    }
    free(neighbors);
    neighbors = NULL;
    return total;
}

//prints universe with o representing live and . representing dead cells
//accepts a universe u and a file which can be stdout.
void uv_print(Universe *u, FILE *outfile) {
    for (uint32_t i = 0; i < uv_rows(u); i++) {
        for (uint32_t j = 0; j < uv_cols(u); j++) {
            if (uv_get_cell(u, i, j)) {
                fprintf(outfile, "o");
            } else {
                fprintf(outfile, ".");
            }
        }
        fprintf(outfile, "\n");
    }
    fprintf(outfile, "\n");
}
