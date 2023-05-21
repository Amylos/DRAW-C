/**
 * @file container.c
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
#include "container.h"

typedef struct s_node{
    struct s_node*m_pPrev;
    struct s_node*m_pNext;
             void*m_pItem;
}t_node;

t_node*NodeNew(t_node*pPrev, t_node*pNext, void*pItem){
    /**
     * @todo
     *
     */

	t_node*pNode = (t_node*)malloc(sizeof(t_node));
	assert(pNode);

	*pNode = (t_node){
		.m_pPrev = pPrev,
		.m_pNext = pNext,
		.m_pItem = pItem,
	};

	if(pPrev)	pPrev->m_pNext = pNode;
	if(pNext)	pNext->m_pPrev = pNode;

    return pNode; /* TAKE CARE OF THIS!*/ /*THIS LOL!*/
}

t_node*NodeDelReturnNext(t_node*pNode, t_ptfV pDeleteFunc){
    assert(pNode);
    /**
     * @todo
     *
     */

    if(pDeleteFunc){
    	pDeleteFunc(pNode->m_pItem);
    }
    else{
    	free(pNode->m_pItem);
    }

    t_node*pNodeNext = pNode->m_pNext;

    if(pNode->m_pNext)	pNode->m_pNext->m_pPrev = pNode->m_pPrev;
    if(pNode->m_pPrev)	pNode->m_pPrev->m_pNext = pNode->m_pNext;

    free(pNode);

    return pNodeNext; /* SAME WARNING! */
}

struct s_container {
    t_node*m_pHead;
    t_node*m_pTail;
    t_ptfV m_pDeleteFunc;
    size_t m_szCard;
};

t_container*ContainerNew(t_ptfV pDeleteFunc){
    /**
     * @todo
     *
     */
	t_container*pContainer = (t_container*)malloc(sizeof(t_container));
	assert(pContainer);


	*pContainer = (t_container){
		.m_pDeleteFunc = pDeleteFunc,
	};


    return pContainer; /* TAKE CARE OF THIS!*/ /*THIS LOL!*/
}

t_container*ContainerDel(t_container*pContainer){

    free(ContainerFlush(pContainer));
    return NULL; 
}   



/************************************************************************************************************************/
/*  For the code below, all commented 'asserts' and 'returns' should be re-actived after complete function implementing */
/************************************************************************************************************************/

t_container*ContainerFlush(t_container*pContainer){
    assert(pContainer);

    while(pContainer->m_pHead){
    	pContainer->m_pHead = NodeDelReturnNext(pContainer->m_pHead, pContainer->m_pDeleteFunc);
    	pContainer->m_szCard--;
    }
    assert(pContainer->m_szCard == 0);
    pContainer->m_pTail = pContainer->m_pHead;

    return pContainer;
}

size_t ContainerCard(const t_container*pContainer){
    assert(pContainer);

    return pContainer->m_szCard;
}

void*ContainerPushback(t_container*pContainer, void*pItem){
    assert(pContainer);

    if(pContainer->m_szCard == 0){
    	assert(pContainer->m_pHead == NULL);
    	assert(pContainer->m_pTail == NULL);
    	pContainer->m_pTail = NodeNew(NULL, NULL, pItem);
    	pContainer->m_pHead = pContainer->m_pTail;
    }
    else{
    	pContainer->m_pTail = NodeNew(pContainer->m_pTail, NULL, pItem);
    }
    pContainer->m_szCard++;
    assert(pContainer->m_pTail->m_pItem == pItem);

	return pContainer->m_pTail->m_pItem;    /* TO TAKE CARE! */
}


void*ContainerGetback(const t_container*pContainer){
    assert(pContainer);

    return pContainer->m_pTail->m_pItem;
}

void*ContainerParse(const t_container*pContainer, t_ptfVV pParseFunc, void*pParam){
    assert(pContainer);
    assert(pParseFunc);
    t_node*pParse =pContainer->m_pHead;

    while(pParse){
    	if(pParseFunc(pParse->m_pItem,pParam))	return pParse->m_pItem;
    	pParse = pParse->m_pNext;
    }

    return NULL;
}

void*ContainerParseDelIf(t_container*pContainer, t_ptfVV pParseFunc, void*pParam){

	assert(pContainer);

	t_node*pParse =pContainer->m_pHead;
	t_node*pNext;

	while(pParse){

		if(pParseFunc(pParse->m_pItem,pParam)) {
			pNext = NodeDelReturnNext(pParse, pContainer->m_pDeleteFunc);
			if(pContainer->m_pHead == pParse) pContainer->m_pHead = pNext;
			if(pContainer->m_pTail == pParse) pContainer->m_pTail=pParse->m_pPrev;
			pContainer->m_szCard--;
		}
		else{
			pParse = pParse->m_pNext;
		}
	}
	return NULL;
}
