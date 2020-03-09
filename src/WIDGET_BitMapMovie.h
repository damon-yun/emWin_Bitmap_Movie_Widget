/*********************************************************************
*  Author : Damon Zhang
*  E-mail : damonzhang92@gmail.com
----------------------------- MIT License ----------------------------
*  MIT License
*
*  Copyright (c) 2020 Damon Zhang
*  All rights reserved.
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in all
*  copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*  SOFTWARE.
----------------------------------------------------------------------
File        : WIDGET_BitMapMovie.c
Purpose     : A Custom emWin Widget Type to achieve Bitmap format picture movie play.
Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              Bitmap        - ( )
---------------------------END-OF-HEADER------------------------------
*/

#ifndef _WIDGET_BITMAP_MOVIE_H_
#define _WIDGET_BITMAP_MOVIE_H_

#include <string.h>        // Definition of NULL
#include <stdlib.h>        // malloc() and free()
#include <stdint.h>        // int32_t uint32_t
#include "GUI.h"
#include "WM.h"            // MemoryDevices

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define GUI_BITMMAP_MOVIE_NOTIFICATION_NULL         -1
#define GUI_BITMMAP_MOVIE_NOTIFICATION_PREDRAW       0
#define GUI_BITMMAP_MOVIE_NOTIFICATION_POSTDRAW      1
#define GUI_BITMMAP_MOVIE_NOTIFICATION_START         2
#define GUI_BITMMAP_MOVIE_NOTIFICATION_STOP          3
#define GUI_BITMMAP_MOVIE_NOTIFICATION_END           4
#define GUI_BITMMAP_MOVIE_NOTIFICATION_DELETE        5

/*********************************************************************
*
*       Custom widget data (global)
*
**********************************************************************
*/
/*********************************************************************
*
*       Typedef
*/
typedef struct _gui_bitmap_movie {
    char* pFileName;
    const GUI_BITMAP** pBitmapTable;
    int FrameNum;
    int FramePeriod;
    int xSize;
    int ySize;
} GUI_BITMAP_MOVIE;

typedef WM_HWIN GUI_BITMAP_MOVIE_Handle;

typedef void GUI_BITMAP_MOVIE_FUNC(GUI_BITMAP_MOVIE_Handle hMovie, int Notification, uint32_t CurrentFrame);

/*********************************************************************
*
*       API
*/
#if defined(__cplusplus)
extern "C" {
#endif

/*********************************************************************
*
*       MYWIDGET_Create
*/
 extern GUI_BITMAP_MOVIE_Handle GUI_BITMAP_MOVIE_Create(const void* pFileData, WM_HWIN hWinParent, GUI_BITMAP_MOVIE_FUNC* pfNotify);

/*********************************************************************
*
*       GUI_BITMAP_MOVIE_Show
*/
 extern void GUI_BITMAP_MOVIE_Show(GUI_BITMAP_MOVIE_Handle hWin, int x0, int y0);

 /*********************************************************************
*
*       GUI_BITMAP_MOVIE_Delete
*/
 extern void GUI_BITMAP_MOVIE_Delete(GUI_BITMAP_MOVIE_Handle hWin);

/*  example

static int        _Play;

static void _cbNotifyOnce(GUI_HMEM hMovie, int Notification, U32 CurrentFrame) {
    GUI_USE_PARA(hMovie);
    GUI_USE_PARA(CurrentFrame);
    switch (Notification) {
    case GUI_MOVIE_NOTIFICATION_PREDRAW:
        GUI_MULTIBUF_Begin();
        break;
    case GUI_MOVIE_NOTIFICATION_POSTDRAW:
        GUI_MULTIBUF_End();
        break;
    case GUI_BITMMAP_MOVIE_NOTIFICATION_START:
        _Play = 1;
        break;
    case GUI_BITMMAP_MOVIE_NOTIFICATION_END:
        _Play = 0;
        break;
    }
}


extern GUI_CONST_STORAGE GUI_BITMAP bmStandby01;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby02;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby03;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby04;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby05;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby06;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby07;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby08;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby09;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby10;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby11;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby12;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby13;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby14;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby15;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby16;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby17;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby18;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby19;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby20;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby21;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby22;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby23;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby24;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby25;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby26;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby27;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby28;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby29;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby30;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby31;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby32;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby33;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby34;
extern GUI_CONST_STORAGE GUI_BITMAP bmStandby35;

const GUI_BITMAP* movie_table[] = { &bmStandby01, &bmStandby02, &bmStandby03, &bmStandby04, &bmStandby05,
                              &bmStandby06, &bmStandby07, &bmStandby08, &bmStandby09, &bmStandby10,
                              &bmStandby11, &bmStandby12, &bmStandby13, &bmStandby14, &bmStandby15,
                              &bmStandby16, &bmStandby17, &bmStandby18, &bmStandby19, &bmStandby20,
                              &bmStandby21, &bmStandby22, &bmStandby23, &bmStandby24, &bmStandby25,
                              &bmStandby26, &bmStandby27, &bmStandby28, &bmStandby29, &bmStandby30,
                              &bmStandby31, &bmStandby32, &bmStandby33, &bmStandby34, &bmStandby35,
};

GUI_BITMAP_MOVIE test_movie = {
    .pFileName = "test",
    .pBitmapTable = movie_table,
    .FrameNum = 35,
    .FramePeriod = 40,
    .xSize = 29,
    .ySize = 107
};

extern GUI_CONST_STORAGE GUI_BITMAP bmStandbyBK;

void MainTask(void) {
    GUI_BITMAP_MOVIE_Handle hMyWidget;
    GUI_Init();
    GUI_DrawBitmap(&bmStandbyBK, 0, 0);
    int time = 0;
    while (1) {
        hMyWidget = GUI_BITMAP_MOVIE_Create(&test_movie, 0, _cbNotifyOnce);
        time = GUI_GetTime();

        GUI_BITMAP_MOVIE_Show(hMyWidget, 121, 158);
        do {
            GUI_Exec();
            GUI_X_Delay(1);
        } while (_Play);
        time = GUI_GetTime() - time;
        GUI_DispDecAt(time / 35, 0, 0, 5);
        GUI_BITMAP_MOVIE_Delete(hMyWidget);
        GUI_Delay(50);

    }
}

*/

#if defined(__cplusplus)
}
#endif

#endif /* _WIDGET_BITMAP_MOVIE_H_ */

/*************************** End of file ****************************/



