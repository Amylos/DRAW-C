/**
 * @file tool.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define TOOL_COLORCHART_HEIGHT_RATIO		(3)



typedef enum e_toolType{	/* Tool type enumerate definition 	 	 */
	TOOL_UNDEFINED  = 0,	/* undefined tool: no tool			 	 */
	TOOL_CIRCLE     = 1,	/* for drawing circles				 	 */
	TOOL_TRIANGLE   = 4,	/* for drawing triangles			 	 */
	TOOL_SQUARE     = 5,	/* for drawing squares or rectangles 	 */
	TOOL_POLYGON    = 7,	/* for drawing free polygons		 	 */
	TOOL_COLORCHART,		/* for placing a color-chart in tool-box,
								in purpose to peek a color			 */
}t_toolType;

typedef struct s_tool t_tool;

t_tool*ToolNew(t_toolType toolType, size_t szToolSize, int iLocX, int iLocY, ...);
t_tool*ToolDel(t_tool*pTool);
t_tool*ToolDraw(const t_tool*pTool, SDL_Renderer*pRenderer);
t_tool*ToolAt(t_tool*pTool, SDL_Point*pAt);
t_toolType ToolGetType(const t_tool*pTool);
SDL_Color ToolGetColor(const t_tool*pTool);

