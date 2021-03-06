/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                           www.segger.com                           *
**********************************************************************
*                                                                    *
* C-file generated by                                                *
*                                                                    *
*        Font converter for emWin version 5.22                       *
*        Compiled Jul  4 2013, 12:18:44                              *
*        (C) 1998 - 2013 Segger Microcontroller GmbH & Co. KG
*                                                                    *
**********************************************************************
*                                                                    *
* Source file: Calibri_11_Bold.c                                     *
* Font:        Calibri                                               *
* Height:      11                                                    *
*                                                                    *
**********************************************************************
*                                                                    *
* Initial font height:  22                                           *
* Edit/Delete/Top       at character 0x50 (80)                       *
* Edit/Delete/Top       at character 0x50 (80)                       *
* Edit/Delete/Top       at character 0x50 (80)                       *
* Edit/Delete/Top       at character 0x50 (80)                       *
* Edit/Delete/Top       at character 0x50 (80)                       *
* Edit/Delete/Top       at character 0x50 (80)                       *
* Edit/Delete/Bottom    at character 0x50 (80)                       *
* Edit/Delete/Bottom    at character 0x50 (80)                       *
* Edit/Delete/Bottom    at character 0x50 (80)                       *
* Edit/Delete/Bottom    at character 0x50 (80)                       *
* Edit/Delete/Bottom    at character 0x50 (80)                       *
* Range disabled:       0000 - FFFF                                  *
* Character enabled:   0x4D (77)                                     *
* Character enabled:   0x50 (80)                                     *
*                                                                    *
**********************************************************************
*/

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

/* The following line needs to be included in any file selecting the
   font.
*/
extern GUI_CONST_STORAGE GUI_FONT GUI_FontCalibri_11_Bold;

/* Start of unicode area <Basic Latin> */
GUI_CONST_STORAGE unsigned char acGUI_FontCalibri_11_Bold_004D[ 22] = { /* code 004D, LATIN CAPITAL LETTER M */
  _XXXX___,__XXXX__,
  _XXXX___,__XXXX__,
  _XXXX___,__XXXX__,
  _XX_XX__,_XX_XX__,
  _XX_XX__,_XX_XX__,
  _XX_XXX_,XXX_XX__,
  _XX__XX_,XX__XX__,
  _XX__XX_,XX__XX__,
  _XX__XXX,X___XX__,
  _XX___XX,X___XX__,
  _XX___XX,X___XX__};

GUI_CONST_STORAGE unsigned char acGUI_FontCalibri_11_Bold_0050[ 22] = { /* code 0050, LATIN CAPITAL LETTER P */
  _XXXXXX_,________,
  _XXXXXXX,X_______,
  _XX____X,X_______,
  _XX____X,X_______,
  _XX___XX,X_______,
  _XXXXXXX,________,
  _XXXXXX_,________,
  _XX_____,________,
  _XX_____,________,
  _XX_____,________,
  _XX_____,________};

GUI_CONST_STORAGE GUI_CHARINFO GUI_FontCalibri_11_Bold_CharInfo[2] = {
   {  16,  16,  2, acGUI_FontCalibri_11_Bold_004D } /* code 004D */
  ,{  10,  10,  2, acGUI_FontCalibri_11_Bold_0050 } /* code 0050 */
};

GUI_CONST_STORAGE GUI_FONT_PROP GUI_FontCalibri_11_Bold_Prop2 = {
   0x0050 /* first character */
  ,0x0050 /* last character  */
  ,&GUI_FontCalibri_11_Bold_CharInfo[  1] /* address of first character */
  ,(GUI_CONST_STORAGE GUI_FONT_PROP *)0 /* pointer to next GUI_FONT_PROP */
};

GUI_CONST_STORAGE GUI_FONT_PROP GUI_FontCalibri_11_Bold_Prop1 = {
   0x004D /* first character */
  ,0x004D /* last character  */
  ,&GUI_FontCalibri_11_Bold_CharInfo[  0] /* address of first character */
  ,&GUI_FontCalibri_11_Bold_Prop2 /* pointer to next GUI_FONT_PROP */
};

GUI_CONST_STORAGE GUI_FONT GUI_FontCalibri_11_Bold = {
   GUI_FONTTYPE_PROP /* type of font    */
  ,11 /* height of font  */
  ,11 /* space of font y */
  ,1 /* magnification x */
  ,1 /* magnification y */
  ,{&GUI_FontCalibri_11_Bold_Prop1}
  ,11 /* Baseline */
  ,8 /* Height of lowercase characters */
  ,11 /* Height of capital characters */
};

