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
#include <string.h>        // Definition of NULL
#include <stdlib.h>        // malloc() and free()
#include "GUI.h"
#include "WM.h"            // MemoryDevices

#include "WIDGET_BitMapMovie.h"
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
*       BitMapMovie widget data (global)
*
**********************************************************************
*/
/*********************************************************************
*
*       Typedef
*/
typedef struct _gui_bitmap_movie_userdata {
    GUI_BITMAP_MOVIE* pMoive;
    int Frameindex;
    int Notification;
    int FramePeriod;
    WM_HTIMER hTimer;
    GUI_BITMAP_MOVIE_FUNC *pfNotify;
    int x0;
    int y0;
} GUI_BitMap_Movie_UserData;


/*********************************************************************
*
*       BitMapMovie widget function prototypes (global)
*
**********************************************************************
*/

/*********************************************************************
*
*       BitMapMovie widget functions (global)
*
**********************************************************************
*/
/*********************************************************************
*
*       MYWIDGET_Callback
*/
static void GUI_BITMAP_MOVIE_Callback(WM_MESSAGE * pMsg) {
    GUI_BITMAP_MOVIE_Handle   hWin;
    GUI_BitMap_Movie_UserData MovieUserData;
    GUI_MEMDEV_Handle handle;

    hWin = pMsg->hWin;

    WM_GetUserData(hWin, &MovieUserData, sizeof(GUI_BitMap_Movie_UserData));

    switch (pMsg->MsgId) {
    case WM_TIMER:
        if (MovieUserData.hTimer == pMsg->Data.v) {
            if (GUI_BITMMAP_MOVIE_NOTIFICATION_START != MovieUserData.Notification) {
                break;
            }
            WM_RestartTimer(MovieUserData.hTimer, MovieUserData.pMoive->FramePeriod);
            MovieUserData.Frameindex++;
            WM_SetUserData(pMsg->hWin, &MovieUserData, sizeof(GUI_BitMap_Movie_UserData));
            WM_Invalidate(pMsg->hWin);
        }
    break;

    case WM_PAINT:
        handle = GUI_MEMDEV_Create(MovieUserData.x0, MovieUserData.y0, MovieUserData.pMoive->xSize, MovieUserData.pMoive->ySize);
        GUI_MEASDEV_Select(handle);
        GUI_DrawBitmap(((MovieUserData.pMoive->pBitmapTable)[MovieUserData.Frameindex]), 0, 0);
        GUI_MEASDEV_Select(0);
        GUI_MEMDEV_CopyToLCD(handle);
        GUI_MEMDEV_Delete(handle);


        if (MovieUserData.Frameindex == MovieUserData.pMoive->FrameNum - 1) {
            MovieUserData.Notification = GUI_BITMMAP_MOVIE_NOTIFICATION_END;
            WM_SetUserData(pMsg->hWin, &MovieUserData, sizeof(GUI_BitMap_Movie_UserData));
            if (MovieUserData.pfNotify) {
                MovieUserData.pfNotify(hWin, MovieUserData.Notification, MovieUserData.Frameindex);
            }
        }
    break;

    default:
        WM_DefaultProc(pMsg);
        break;
    }
}

/*********************************************************************
*
*       GUI_BITMAP_MOVIE_Show
*/
void GUI_BITMAP_MOVIE_Show (GUI_BITMAP_MOVIE_Handle hWin, int x0, int y0)
{
    GUI_BitMap_Movie_UserData MovieUserData;

    if (hWin == GUI_HMEM_NULL) {
        return;
    }
    WM_GetUserData(hWin, &MovieUserData, sizeof(GUI_BitMap_Movie_UserData));
    if(GUI_BITMMAP_MOVIE_NOTIFICATION_START == MovieUserData.Notification){
        return 0;
    }
    MovieUserData.Notification = GUI_BITMMAP_MOVIE_NOTIFICATION_START;
    MovieUserData.Frameindex = 0;
    MovieUserData.x0 = x0;
    MovieUserData.y0 = y0;
    WM_SetUserData(hWin, &MovieUserData, sizeof(GUI_BitMap_Movie_UserData));

    if (MovieUserData.pfNotify) {
        MovieUserData.pfNotify(hWin, MovieUserData.Notification, MovieUserData.Frameindex);
    }
        
    WM_MoveTo(hWin, x0, y0);
    WM_ShowWindow(hWin);
    WM_RestartTimer(MovieUserData.hTimer, MovieUserData.FramePeriod);
    WM_Paint(hWin);
}
/*********************************************************************
*
*       GUI_BITMAP_MOVIE_Pause
*/
int GUI_BITMAP_MOVIE_Pause(GUI_BITMAP_MOVIE_Handle hMovie)
{
    int ret = 0;
    GUI_BitMap_Movie_UserData MovieUserData;

    if (hMovie == WM_HMEM_NULL) {
        return -1;
    }

    ret = WM_GetUserData(hMovie, &MovieUserData, sizeof(GUI_BitMap_Movie_UserData));
    if (ret == 0) {
        return -1;
    }
    if(GUI_BITMMAP_MOVIE_NOTIFICATION_STOP == MovieUserData.Notification){
        return 0;
    }
    MovieUserData.Notification = GUI_BITMMAP_MOVIE_NOTIFICATION_STOP;

    WM_SetUserData(hMovie, &MovieUserData, sizeof(GUI_BitMap_Movie_UserData));

    return 0;
}
/*********************************************************************
*
*       GUI_BITMAP_MOVIE_Play
*/
int GUI_BITMAP_MOVIE_Play(GUI_BITMAP_MOVIE_Handle hMovie)
{
    int ret = 0;
    GUI_BitMap_Movie_UserData MovieUserData;

    if (hMovie == WM_HMEM_NULL) {
        return -1;
    }

    ret = WM_GetUserData(hMovie, &MovieUserData, sizeof(GUI_BitMap_Movie_UserData));
    if (ret == 0) {
        return -1;
    }
    if(GUI_BITMMAP_MOVIE_NOTIFICATION_START == MovieUserData.Notification){
        return 0;
    }
    MovieUserData.Notification = GUI_BITMMAP_MOVIE_NOTIFICATION_START;
    WM_RestartTimer(MovieUserData.hTimer, MovieUserData.FramePeriod);

    WM_SetUserData(hMovie, &MovieUserData, sizeof(GUI_BitMap_Movie_UserData));

    return 0;
}

/*********************************************************************
*
*       GUI_BITMAP_MOVIE_GetFrameIndex
*/
U32 GUI_BITMAP_MOVIE_GetFrameIndex(GUI_BITMAP_MOVIE_Handle hMovie)
{
    int ret = 0;
    GUI_BitMap_Movie_UserData MovieUserData;

    if (hMovie == WM_HMEM_NULL) {
        return 0;
    }

    WM_GetUserData(hMovie, &MovieUserData, sizeof(GUI_BitMap_Movie_UserData));

    return (U32)MovieUserData.Frameindex;
}
/*********************************************************************
*
*       MYWIDGET_Create
*/
GUI_BITMAP_MOVIE_Handle GUI_BITMAP_MOVIE_Create(const void* pFileData, WM_HWIN hWinParent, GUI_BITMAP_MOVIE_FUNC* pfNotify)
{
    GUI_BITMAP_MOVIE* pBitmapMovie = (GUI_BITMAP_MOVIE*)pFileData;
    GUI_BITMAP_MOVIE_Handle   hWin;
    GUI_BitMap_Movie_UserData BitMapMovieUserData;

    if (pFileData == NULL) {
        return GUI_HMEM_NULL;
    }
    if (pBitmapMovie->pBitmapTable == NULL || pBitmapMovie->FrameNum == 0) {
        return GUI_HMEM_NULL;
    }

    if (hWinParent == GUI_HMEM_NULL) {
        hWinParent = WM_HBKWIN;
    }

    BitMapMovieUserData.pMoive = pBitmapMovie;
    BitMapMovieUserData.Frameindex = 0;
    BitMapMovieUserData.Notification = GUI_BITMMAP_MOVIE_NOTIFICATION_NULL;
    BitMapMovieUserData.pfNotify = pfNotify;

    hWin = WM_CreateWindowAsChild(0, 0, pBitmapMovie->xSize, pBitmapMovie->ySize, hWinParent, WM_CF_HIDE, GUI_BITMAP_MOVIE_Callback, sizeof(GUI_BitMap_Movie_UserData));
    BitMapMovieUserData.hTimer = WM_CreateTimer(hWin, 0, pBitmapMovie->FramePeriod, 0);
    BitMapMovieUserData.FramePeriod = pBitmapMovie->FramePeriod;
    WM_SetUserData(hWin, &BitMapMovieUserData, sizeof(GUI_BitMap_Movie_UserData));
    return hWin;
}

/*********************************************************************
*
*       GUI_BITMAP_MOVIE_Delete
*/
void GUI_BITMAP_MOVIE_Delete(GUI_BITMAP_MOVIE_Handle hWin)
{
    GUI_BitMap_Movie_UserData MovieUserData;
    WM_GetUserData(hWin, &MovieUserData, sizeof(GUI_BitMap_Movie_UserData));
    WM_DeleteTimer(MovieUserData.hTimer);
    WM_DeleteWindow(hWin);
}


/*************************** End of file ****************************/

