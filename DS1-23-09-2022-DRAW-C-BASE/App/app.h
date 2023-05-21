/**
 * @file app.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//#define APP_DONT_PROCESS_POLYGON_TOOL
//#define APP_USE_SDLSETWINDOWMOUSERECT

#define APP_WINDOW_WIDTH    (900)
#define APP_WINDOW_HEIGHT   (600)
#define APP_COLORBKGND      (0xFF404040)
#define APP_WINDOW_TITLE    ("A simple Draw App with SDL2")
#define APP_TIMER_INTERVAL  (30)

#define APP_TOOLBOX_WIDTH           (80)
#define APP_TOOLBOX_TOOL_SIZE       (APP_TOOLBOX_WIDTH*.75)
#define APP_TOOLBOX_TOOL_SPACING    (APP_TOOLBOX_WIDTH*.125)

#define APP_TOOLBOX_COLORCHART_FILE	("./Resources/Images/colorchart.png")


typedef struct s_app t_app;

t_app*AppNew(int iWidth, int iHeight, int iColorBkgnd, const char*pAppTitleStr);
t_app*AppDel(t_app*pApp);
int   AppRun(t_app*pApp);



