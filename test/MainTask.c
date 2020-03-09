/*********************************************************************
----------------------------- MIT License ----------------------------
*  MIT License
*
*  Copyright (c) 2020 damonzhang
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
File        : MainTask.c
Purpose     : a simple test code for BitMapMovie WIDGET.
Requirements: WIDGET_BitMapMovie - (x)

---------------------------END-OF-HEADER------------------------------
*/
#include <string.h>        // Definition of NULL
#include <stdlib.h>        // malloc() and free()
#include "GUI.h"
#include "WM.h"            // MemoryDevices

#include "WIDGET_BitMapMovie.h"
/*********************************************************************
*
*       Defines
*
*********************************************************************/

static int        _Play;
/*********************************************************************
*
*       _cbNotifyOnce
*
* Function description
*   Uses multiple buffering (if available) to avoid tearing effects.
*/
static void _cbNotifyOnce(GUI_BITMAP_MOVIE_Handle hMovie, int Notification, uint32_t CurrentFrame) {
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


/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
  GUI_BITMAP_MOVIE_Handle hMyWidget;
  GUI_Init();
  GUI_DrawBitmap(&bmStandbyBK,0,0);
  int time = 0;
  while (1) {
      hMyWidget = GUI_BITMAP_MOVIE_Create(&test_movie, 0, _cbNotifyOnce);
      GUI_BITMAP_MOVIE_Show(hMyWidget, 121,158);
      time = GUI_GetTime();
      do {
          GUI_Exec();
          GUI_X_Delay(1);
      } while (_Play);
      time = GUI_GetTime() - time;
      GUI_DispDecAt(time/35, 0, 0, 5);
      GUI_BITMAP_MOVIE_Delete(hMyWidget);
      GUI_Delay(50);
    
  }
}

/*************************** End of file ****************************/
