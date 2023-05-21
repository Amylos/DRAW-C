/**
 * @file container.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

typedef void*(*t_ptfV)(void*);
typedef void*(*t_ptfVV)(void*,void*);

typedef struct s_container t_container;

t_container*ContainerNew(t_ptfV pDeleteFunc);
t_container*ContainerDel(t_container*pContainer);
t_container*ContainerFlush(t_container*pContainer);
size_t ContainerCard(const t_container*pContainer);
void*ContainerPushback(t_container*pContainer, void*pItem);
void*ContainerParse(const t_container*pContainer, t_ptfVV pParseFunc, void*pParam);


