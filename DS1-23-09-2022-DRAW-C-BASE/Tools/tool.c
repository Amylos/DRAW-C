/**
 * @file tool.c
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
#include <stdarg.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../Utils/utils.h"
#include "tool.h"

struct s_tool {
	t_toolType      m_toolType;		/* enumerate tool type, identifying the specific tool 					 */
	size_t          m_szSize;		/* tool frame size: square icon for all, except for the color-chart tool */
	SDL_Point       m_location;		/* tool location in the tool-box, window relative 						 */
	SDL_Point*      m_pVextexes;	/* for tool vertexes         											 */
	SDL_Texture*    m_pTexture;		/* only for the color-chart tool 										 */
	SDL_Surface*	m_pSurface;
	SDL_Color       m_colorAt;		/* only use with the color-chart tool 									 */
};

t_tool*ToolNew(t_toolType toolType, size_t szToolSize, int iLocX, int iLocY, ...){

    t_tool*pTool=(t_tool*)malloc(sizeof(t_tool));
    assert(pTool);
    /**
     * @todo: initializing the new pTool structure with parameters
     * 
     */

    *pTool = (t_tool){
    	.m_toolType = toolType,
    	.m_szSize 	= szToolSize,
		.m_location = (SDL_Point){iLocX,iLocY},
    };

    switch(pTool->m_toolType){
    case TOOL_SQUARE:
    case TOOL_TRIANGLE:
    case TOOL_CIRCLE:
    case TOOL_POLYGON:

    	pTool->m_pVextexes = (SDL_Point*)malloc(sizeof(SDL_Point)*pTool->m_toolType);
    	assert(pTool->m_pVextexes);

        break;
    case TOOL_COLORCHART:
        /* do nothing */
        break;
    case TOOL_UNDEFINED:
    default:
        /* do nothing */
        break;
    }

    switch(pTool->m_toolType){
    case TOOL_SQUARE:

    	pTool->m_pVextexes[0].x = pTool->m_location.x;
    	pTool->m_pVextexes[0].y = pTool->m_location.y;

    	pTool->m_pVextexes[1].x = pTool->m_location.x + pTool->m_szSize;
    	pTool->m_pVextexes[1].y = pTool->m_location.y;

    	pTool->m_pVextexes[2].x = pTool->m_location.x + pTool->m_szSize;
    	pTool->m_pVextexes[2].y = pTool->m_location.y + pTool->m_szSize;

    	pTool->m_pVextexes[3].x = pTool->m_location.x;
    	pTool->m_pVextexes[3].y = pTool->m_location.y + pTool->m_szSize;

    	pTool->m_pVextexes[4] = pTool->m_pVextexes[0];

        break;
    case TOOL_TRIANGLE:

    	pTool->m_pVextexes[0].x = pTool->m_location.x + pTool->m_szSize/2 ;
		pTool->m_pVextexes[0].y = pTool->m_location.y;

		pTool->m_pVextexes[1].x = pTool->m_location.x + pTool->m_szSize;
		pTool->m_pVextexes[1].y = pTool->m_location.y + pTool->m_szSize;

		pTool->m_pVextexes[2].x = pTool->m_location.x;
		pTool->m_pVextexes[2].y = pTool->m_location.y + pTool->m_szSize;

		pTool->m_pVextexes[3] = pTool->m_pVextexes[0];

        break;
    case TOOL_POLYGON:
        /**
         * @todo: defining the vertexes for TOOL_POLYGON tool
         * 
         */
    	pTool->m_pVextexes[0].x = pTool->m_location.x;
		pTool->m_pVextexes[0].y = pTool->m_location.y + pTool->m_szSize*1/2;

    	pTool->m_pVextexes[1].x = pTool->m_location.x + pTool->m_szSize*1/5;
		pTool->m_pVextexes[1].y = pTool->m_location.y + pTool->m_szSize;

    	pTool->m_pVextexes[2].x = pTool->m_location.x + pTool->m_szSize;
		pTool->m_pVextexes[2].y = pTool->m_location.y + pTool->m_szSize*4/5;

    	pTool->m_pVextexes[3].x = pTool->m_location.x + pTool->m_szSize*4/5;
		pTool->m_pVextexes[3].y = pTool->m_location.y;

    	pTool->m_pVextexes[4].x = pTool->m_location.x + pTool->m_szSize/2;
		pTool->m_pVextexes[4].y = pTool->m_location.y + pTool->m_szSize/2;

    	pTool->m_pVextexes[5].x = pTool->m_location.x + pTool->m_szSize*4/5;
		pTool->m_pVextexes[5].y = pTool->m_location.y + pTool->m_szSize*7/10;

    	pTool->m_pVextexes[6] = pTool->m_pVextexes[0];

        break;
    case TOOL_CIRCLE:

    	pTool->m_pVextexes[0].x = pTool->m_location.x + pTool->m_szSize/2;
    	pTool->m_pVextexes[0].y = pTool->m_location.y+ pTool->m_szSize/2;

        break;
    case TOOL_COLORCHART:
    {   /* nothing to do! It's already done for you! ;-)) */

    	/* only for use of TOOL_COLORCHART: DO NOT MODIFY */
    	va_list optList;
    	va_start(optList, iLocY);
        /**************************************************/

    	SDL_Renderer*pRenderer=va_arg(optList, SDL_Renderer*);
        const char*colorChartFileStr=va_arg(optList, const char*);

        pTool->m_pSurface = IMG_Load(colorChartFileStr);
        if(pTool->m_pSurface == NULL)	SDL_Log("Failed to load surface : %s \n", SDL_GetError());

        pTool->m_pTexture=IMG_LoadTexture(pRenderer, colorChartFileStr);
        if(pTool->m_pTexture==NULL)	SDL_Log("Failed to load the color chart png: %s\n", SDL_GetError());

        /* only for use of TOOL_COLORCHART: DO NOT MODIFY */
        va_end(optList);
        /**************************************************/
    }
        break;
    case TOOL_UNDEFINED:
    default:
        /* do nothing */
        break;
    }

    return pTool;
}

t_tool*ToolDel(t_tool*pTool){
    assert(pTool);
    if(pTool->m_pVextexes)  free(pTool->m_pVextexes);
    if(pTool->m_pSurface)	SDL_FreeSurface(pTool->m_pSurface);
    if(pTool->m_pTexture)   SDL_DestroyTexture(pTool->m_pTexture);
    free(pTool);
    return NULL;
}

t_tool*ToolDraw(const t_tool*pTool, SDL_Renderer*pRenderer){
    assert(pTool);

    SDL_SetRenderDrawColor(pRenderer, 200, 200, 200, 255);

    switch(pTool->m_toolType){
    case TOOL_SQUARE:
    case TOOL_TRIANGLE:
    case TOOL_POLYGON:
        SDL_RenderDrawLines(pRenderer, pTool->m_pVextexes, pTool->m_toolType);    
        break;
    case TOOL_CIRCLE:
        SDL_RenderDrawCircle(pRenderer, pTool->m_pVextexes[0].x, pTool->m_pVextexes[0].y, pTool->m_szSize/2);
        break;
    case TOOL_COLORCHART:
        if(pTool->m_pTexture){
            SDL_RenderCopy(
                pRenderer,
                pTool->m_pTexture,
                NULL, 
                &(SDL_Rect){
                    pTool->m_location.x, 
                    pTool->m_location.y, 
                    pTool->m_szSize, 
                    pTool->m_szSize*TOOL_COLORCHART_HEIGHT_RATIO});
        }
        else{
            SDL_SetRenderDrawColor(pRenderer, 100, 100, 100, 255);
            SDL_RenderFillRect(
                pRenderer
                ,&(SDL_Rect){
                    pTool->m_location.x,
                    pTool->m_location.y,
                    pTool->m_szSize,
                    pTool->m_szSize*TOOL_COLORCHART_HEIGHT_RATIO});
        }
        break;
    case TOOL_UNDEFINED:
    default:
        break;
    }
    return NULL;
}

t_tool*ToolAt(t_tool*pTool, SDL_Point*pAt){
    assert(pTool);

    int h = pTool->m_szSize * (pTool->m_toolType==TOOL_COLORCHART?TOOL_COLORCHART_HEIGHT_RATIO:1);
    SDL_bool isAt = SDL_PointInRect(pAt, &(SDL_Rect){pTool->m_location.x, pTool->m_location.y, pTool->m_szSize, h});

    if(isAt && pTool->m_toolType == TOOL_COLORCHART){
    	pAt->x -= pTool->m_location.x;
    	pAt->y -= pTool->m_location.y;

    	pAt->x *= (double)pTool->m_pSurface->w/pTool->m_szSize;
    	pAt->y *= (double)pTool->m_pSurface->h/(TOOL_COLORCHART_HEIGHT_RATIO*pTool->m_szSize);

    	pTool->m_colorAt = *(SDL_Color*){
    		pTool->m_pSurface->pixels +
			pAt->y *pTool->m_pSurface->pitch +
			pAt->x * pTool->m_pSurface->format->BytesPerPixel};
    }
    return (t_tool*)isAt;
}

t_toolType ToolGetType(const t_tool*pTool){
    assert(pTool);
    return pTool->m_toolType;
}


SDL_Color ToolGetColor(const t_tool*pTool){
	assert(pTool);
	return pTool->m_colorAt;
}
