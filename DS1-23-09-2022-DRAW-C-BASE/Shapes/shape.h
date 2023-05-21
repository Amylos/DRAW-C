/**
 * @file shape.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

typedef enum e_shapeType{	/* Shape type enumerate definition 	 	 */
	SHAPE_UNDEFINED  = 0,	/* undefined shape: no shape		 	 */
	SHAPE_CIRCLE     = 1,	/* for circle shapes				 	 */
	SHAPE_TRIANGLE   = 4,	/* for triangle shapes				 	 */
	SHAPE_SQUARE     = 5,	/* for square or rectangle shapes	 	 */
	SHAPE_POLYGON    = 7,	/* for free polygon shapes			 	 */
}t_shapeType;

typedef struct s_shape t_shape;

t_shape*ShapeNew(t_shapeType shapeType, int iLocX, int iLocY, int iWidth, int iHeight, SDL_Color color,...);
t_shape*ShapeDel(t_shape*pShape);
t_shape*ShapeDraw(t_shape*pShape, SDL_Renderer*pRenderer);
t_shape*ShapeDrag(t_shape*pShape, int iDx, int iDy);

t_shape*ShapeIsAt(t_shape*pShape, SDL_Point*piAt);
t_shape*ShapeSerialize(t_shape*pShape,FILE*fd);
t_shape*ShapeNewFromFile(FILE*fd);

