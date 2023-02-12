//Written by Isabella Phung for CSE13S
//with struct code provided by CSE13S instructors.
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "universe.h"
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>

struct Universe{
    uint32_t rows;
    uint32_t cols;
    bool **grid;
    bool toroidal;
}; 

Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal){ 
    Universe *universe = (Universe *) malloc(sizeof(universe));
    universe -> grid = (bool **)calloc(rows, sizeof(bool *));
    assert(universe -> grid);
    universe -> rows = rows;
    universe -> cols = cols;

    for(uint32_t i = 0; i < rows; i++){
        universe -> grid[i] = (bool *) calloc(cols, sizeof(bool));
        assert(universe -> grid[i] != NULL);
    }
    universe -> toroidal = toroidal;
    return universe;
}

void uv_delete(Universe *u){
    for(uint32_t i = 0; i < (uv_rows(u)); i++){
        free(u -> grid[i]);
        u -> grid[i] = NULL;
    }
    free(u -> grid);
    u -> grid = NULL;
    free(u);
    u = NULL;
}

uint32_t uv_rows(Universe *u){
    return u -> rows;
}

uint32_t uv_cols(Universe *u){
    return u -> cols;
}

void uv_live_cell(Universe *u, uint32_t r, uint32_t c){
    u -> grid[r][c] = true;
}

void uv_dead_cell(Universe *u, uint32_t r, uint32_t c){
    u -> grid[r][c] = false;
}

bool uv_get_cell(Universe *u, uint32_t r, uint32_t c){
    return u -> grid[r][c];

}

bool uv_populate(Universe *u, FILE *infile){
    //parse value with fscanf 
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t index = 0;
    uint32_t totalCells = (u -> rows)*(u -> cols);
    int argNum = 0; 
    while ((argNum = fscanf(infile, "%"SCNd32, &x) != EOF)){
        if((x > (u -> rows) - 1) || (y > (u -> cols) - 1) || index > totalCells || argNum == 0){ //if value exceeds universe or more cells inputted than can fit in universe, return false
            return false;
        }
        fscanf(infile, "%"SCNd32, &y);
        uv_live_cell(u, x, y);
        index++;
    } 
    return true;
    //value isn't int, return false
    //if universe is flat and
    //value exceeds universe's rows-1 and columns-1, return false.
    //if universe is toroidal, perform mod on values that exceed flat version
    //to find corresponding value
}

uint32_t uv_census(Universe *u, uint32_t r, uint32_t c){
    //creates list of neighbor coordinates regardless of location first
    //order is: top, top right, right, bottom right, bottom
    //bottom left, left, top left
    int32_t **neighbors = (int32_t **)calloc(8, sizeof(int32_t *));
    for(int i = 0; i < 8; i++){
        neighbors[i] = (int32_t *)calloc(2, sizeof(int32_t));
    }
    
    neighbors[1][1] = c+1;
    neighbors[2][1] = c+1;
    neighbors[3][1] = c+1;

    neighbors[5][1] = c-1;
    neighbors[6][1] = c-1;
    neighbors[7][1] = c-1; 

    neighbors[0][1]  = c;
    neighbors[4][1]  = c;

    neighbors[3][0] = r+1;
    neighbors[4][0] = r+1;
    neighbors[5][0] = r+1;

    neighbors[7][0] = r-1;
    neighbors[0][0] = r-1;
    neighbors[1][0] = r-1;

    neighbors[2][0] = r;
    neighbors[6][0] = r;

    int32_t width = uv_cols(u);
    int32_t height = uv_rows(u);
   if(!u -> toroidal){
         if(c == width - 1){ //if on right edge of universe
            //no right neighbors
            neighbors[1] = NULL;
            neighbors[2] = NULL;
            neighbors[3] = NULL;

       }else if (c == 0){ // if on left edge of universe
            //no left neighbors
            neighbors[5] = NULL;
            neighbors[6] = NULL;
            neighbors[7] = NULL;
       }
       if(r == height - 1){ //if on bottom edge of universe
            //no bottom neighbors
            neighbors[3] = NULL;
            neighbors[4] = NULL;
            neighbors[5] = NULL;
       }else if (r == 0){ // if on top edge of universe
            //no top neighbors
            neighbors[7] = NULL;
            neighbors[0] = NULL;
            neighbors[1] = NULL;
       }
   }else{//if toroidal
        for(uint32_t i = 0; i < 8; i++){
            //% gets funky with signed ints
            neighbors[i][1] = ((neighbors[i][1] % width) + width) % width;
            neighbors[i][0] = ((neighbors[i][0] % height) + height) % height;
//            if(neighbors[i][0]==r || neighbors[i][1]==c){
//                neighbors[i] = NULL;
//            }
         }
   }
//after checking all neighbors, perform census
    uint32_t total = 0;
    uint32_t x = 0;
    uint32_t y = 0;
    for(int i = 0; i<8; i++){
        if(neighbors[i] != NULL){
            x = neighbors[i][0];
            y = neighbors[i][1];
            if(u -> grid[x][y]){
                total++;
            }               
        }
    }
    for(int i = 0; i < 8; i++){
        free(neighbors[i]);
        neighbors[i] = NULL;
    }
    free(neighbors);
    neighbors = NULL;
    return total;
}

void uv_print(Universe *u, FILE *outfile){
    for(uint32_t i = 0; i < uv_rows(u); i++){
        for(uint32_t j = 0; j < uv_cols(u); j++){
            if(uv_get_cell(u, i, j)){
                fprintf(outfile, "o");
            }else{
                fprintf(outfile, ".");
            }
        }
        fprintf(outfile, "\n");
    }
    fprintf(outfile, "\n");
}
