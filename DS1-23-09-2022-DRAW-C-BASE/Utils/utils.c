/**
 * @file utils.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */




#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <SDL2/SDL.h>

#include "utils.h"


int SDL_RenderDrawCircle(SDL_Renderer*renderer, int32_t xCenter, int32_t yCenter, int32_t radius){

    const int32_t diameter = radius*2;
    int32_t x = radius-1,
            y = 0,
            tx = 1,
            ty = 1,
            error = tx-diameter;

    while(x>=y){
        SDL_RenderDrawPoint(renderer, xCenter + x, yCenter - y);
        SDL_RenderDrawPoint(renderer, xCenter + x, yCenter + y);
        SDL_RenderDrawPoint(renderer, xCenter - x, yCenter - y);
        SDL_RenderDrawPoint(renderer, xCenter - x, yCenter + y);
        SDL_RenderDrawPoint(renderer, xCenter + y, yCenter - x);
        SDL_RenderDrawPoint(renderer, xCenter + y, yCenter + x);
        SDL_RenderDrawPoint(renderer, xCenter - y, yCenter - x);
        SDL_RenderDrawPoint(renderer, xCenter - y, yCenter + x);

        if(error<=0){
            ++y;
            error += ty;
            ty += 2;
        }

        if(error>0){
            --x;
            tx += 2;
            error += (tx-diameter);
        }
    }
    return EXIT_SUCCESS;
}
