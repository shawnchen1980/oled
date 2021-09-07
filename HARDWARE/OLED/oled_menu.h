#ifndef __OLED_MENU_H
#define __OLED_MENU_H

#include "oled.h"
#include "ugui.h"

#define MAX_ITEMS_IN_A_SERIES 5 //THE MAX NUMBER OF ITEMS IN A MENU SERIES
#define MAX_ITEM_SERIES 12 //THE MAX NUMBER OF MENU SERIES
#define VMARGIN 5 //上边界宽度
#define HMARGIN 10 //左边界宽度
#define ROW_HEIGHT 13
#define MAX_HEIGHT 64
#define WORD_SIZE 16



typedef struct {
	u8 id;//unique id for each node
	u8 subpos;//pos of the sub-menu series in the menu series array
	u8 val;//value that this menu item carries
} MenuItem;//for submit command from a certain menu item or navigate to a sub-menu

typedef struct {
	MenuItem item[MAX_ITEMS_IN_A_SERIES];
	u8 pos;//index of current selected item, it determines which item should be highlighted as the current selected one
	u8 ppos;//index of the parent menu in menu config
	u8 len;//length of the current menu
	
} MenuSeries;

typedef struct {
	MenuSeries menu[MAX_ITEM_SERIES];
	u8 pos;//index of current menu series, it determines which menu items should be displayed
	u8 len;//length of the menu array
	UG_WINDOW  *currWnd;

} MenuConfig;

extern MenuConfig mc;
extern const u8 *menus[];
//draw a menu item at a certain position specified by (x,y)
//pos1-index of the menu series
//pos2-index of the menu item inside a menu series
//return-position of the next menu item on the oled
u16 OLED_DrawMenuItem(u8 x,u8 y,u8 pos1,u8 pos2);
//pid-parent item's id
//id-current item's id
//return-index of menu in the mc for the newly added
u8 MC_AddItem(u8 pid, u8 id);
void MC_Init(UG_WINDOW* wnd);
void MC_PrintConfig();
void MC_DisplayCurrentMenu();
void MC_MoveToPrevItem();
void MC_MoveToNextItem();
void MC_MoveToSubMenu();
void MC_MoveToParentMenu();

#endif