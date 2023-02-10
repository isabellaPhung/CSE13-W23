//Written by Isabella Phung for CSE13S
//with struct code provided by CSE13S instructors.
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "universe.h"
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>

static bool toroidalFlag = false;

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
    fscanf(infile, "%"SCNd32, &x); //skip height and width
    fscanf(infile, "%"SCNd32, &y);
    
    int index = 0;
    while (fscanf(infile, "%"SCNd32, &x)!=EOF){ 
        fscanf(infile, "%"SCNd32, &y);
        if(!u -> toroidal && (x > u -> rows || y > u -> cols)){
            return false;
        }
        u -> grid[index][0] = x;
        u -> grid[index][1] = y;
        return true;
        
        index++;
    } 
    return false;
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
    uint32_t neighbors[8][2] = {{r-1, c},{r-1, c+1}, {r, c+1}, {r+1, c+1}, {r+1, c}, {r+1, c-1}, {r, c-1}, {r-1, c-1}};
    uint32_t width = uv_rows(u);
    uint32_t height = uv_cols(u);
    if(u -> toroidal){ //if toroidal, 
        if(c >= width - 1){ //if past right edge of universe
            //col adjusted for right neighbors
            //right neighbors: neighbors[1], neighbors[2], neighbors[3]
            //actual col value is (col+1)%width
            neighbors[1][1]=(c%width);
            neighbors[2][1]=(c%width);
            neighbors[3][1]=(c%width);
       }else if (r == 0){ // if against left edge of universe
            //col adjusted for left neighbors
            //left neighbors: neighbors[5], neighbors[6], neighbors[7]
            neighbors[5][1]=(c%width);
            neighbors[6][1]=(c%width);
            neighbors[7][1]=(c%width);
       }
       if(r >= height - 1){ //if past bottom edge of universe
            //row adjusted for bottom neighbors
            //bottom neighbors: neighbors[3], neighbors[4], neighbors[5]
            neighbors[3][0]=(r%height);
            neighbors[4][0]=(r%height);
            neighbors[5][0]=(r%height);

       }else if (c == 0){ // if against top edge of universe
            //row adjusted for top neighbors
            //top neighbors: neighbors[7], neighbors[0], neighbors[1]
            neighbors[3][0]=(r%height);
            neighbors[4][0]=(r%height);
            neighbors[5][0]=(r%height);

       }
    }else{ //if flat world
       if(r == width - 1){ //if on right edge of universe
            //no right neighbors
            neighbors[1], neighbors[2], neighbors[3] = NULL;

       }else if (r == 0){ // if on left edge of universe
            //no left neighbors
            neighbors[5], neighbors[6], neighbors[7] = NULL;
       }
       if(c == height - 1){ //if on bottom edge of universe
            //no bottom neighbors
            neighbors[3], neighbors[4], neighbors[5] = NULL;
       }else if (c == 0){ // if on top edge of universe
            //no top neighbors
            neighbors[7], neighbors[0], neighbors[1] = NULL;

       }

    }

       //after checking all neighbors, perform census
        uint32_t total = 0;
        uint32_t x = 0;
        uint32_t y = 0;
        for(int i = 0; i<8; i++){
            if(neighbors[index] != NULL){
                x = neighbors[i][0];
                y = neighbors[i][1];
                if(u -> grid[x][y]){
                    total++;
                }               
            }
        }
    return total;
}

void uv_print(Universe *u, FILE *outfile){
    //figure out how to use fscanf with outfile.
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
}
