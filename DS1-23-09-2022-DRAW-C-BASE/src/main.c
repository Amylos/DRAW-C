/*
 ============================================================================
 Name        : main.c
 Author      : <author>
 Version     : <version>
 Copyright   : <Your copyright notice>
 Description : MinDRAW in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include "../App/app.h"

int main(int argc, char**argv) {
	puts("========ENTER DRAW APP=========");
	t_app*pTheApp=AppNew(
		APP_WINDOW_WIDTH,
		APP_WINDOW_HEIGHT,
		APP_COLORBKGND,
		APP_WINDOW_TITLE);
	int res=AppRun(pTheApp);
	pTheApp=AppDel(pTheApp);
	puts("========EXIT  DRAW APP=========");
	return res;
}
