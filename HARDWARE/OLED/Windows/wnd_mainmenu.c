#include "wnd_mainmenu.h"

//test window functions
static UG_OBJECT obj_buff_wnd_1[10];
static UG_WINDOW window_1;
static UG_TEXTBOX textbox[PAGE_SIZE];
static u8 textboxIds[]={TXB_ID_0,TXB_ID_1,TXB_ID_2,TXB_ID_3,TXB_ID_4,TXB_ID_5};
static void ProcessInputData( UG_WINDOW* wnd );
static void window_1_callback(UG_MESSAGE *msg);

static void DisplayCurrentPage(UG_WINDOW* wnd);
static u8 itemCount,focusPos=0;//当前页面下项目数，被选中的项目位置

UG_WINDOW* CreateWindow_MainMenu()
{
		UG_WindowCreate(&window_1, obj_buff_wnd_1, 10, window_1_callback);
    // Window Title
//    UG_WindowSetTitleText(&window_1, "Test Window - \xe6GUI v0.31   \x02");      //  \xhh : Special CHR the ASCII value is given by hh interpreted as a hexadecimal number (Check FONT Table)
    UG_WindowSetTitleText(&window_1, "Main Menu");      //  \xhh : Special CHR the ASCII value is given by hh interpreted as a hexadecimal number (Check FONT Table)
    UG_WindowSetTitleTextFont(&window_1, &FONT_4X6);
		UG_WindowSetTitleTextColor(&window_1,0);
    UG_WindowSetXStart(&window_1, 0);
    UG_WindowSetYStart(&window_1, 0);
    UG_WindowSetXEnd(&window_1, 127);       // Window 128x64
    UG_WindowSetYEnd(&window_1, 63);

		
//		UG_ButtonCreate(&window_1, &button_1, BTN_ID_0, 25, 25, 40, 40);
//		UG_ButtonSetFont(&window_1,BTN_ID_0,&FONT_5X8);
//		UG_ButtonSetForeColor(&window_1,BTN_ID_0, C_WHITE);
//		UG_ButtonSetText(&window_1,BTN_ID_0,"B");
		

// Create Textboxes
	u8 x=H_SPACE,y=0;
	for(int i=0;i<PAGE_SIZE;i++){
		y+=V_SPACE;
		UG_TextboxCreate(&window_1, &textbox[i], textboxIds[i], x, y, x+ROW_WIDTH-1, y+ROW_HEIGHT-1);
//    UG_TextboxSetFont(&window_1, TXB_ID_0, &FONT_4X6);//5列8行，每个字宽5列，高8行
    //UG_TextboxSetText(&window_1, TXB_ID_0, "00");
		UG_TextboxSetText(&window_1, textboxIds[i], "XX");
    UG_TextboxSetForeColor(&window_1, textboxIds[i], C_WHITE);
		UG_TextboxSetBackColor(&window_1, textboxIds[i], C_BLACK);
    UG_TextboxSetAlignment(&window_1, textboxIds[i], ALIGN_CENTER);
		y+=ROW_HEIGHT;
	}
	
	MC_Init(&window_1);

	DisplayCurrentPage(&window_1);
			

		UG_WindowShow(&window_1);
//		CX_DrawBattery(0,0,10);
		window_1.inputCb=ProcessInputData;
		return &window_1;
}
void DisplayCurrentPage(UG_WINDOW* wnd)
{
	u8 pos=mc.menu[mc.pos].pos,spos=0;
	spos=pos-pos%PAGE_SIZE;//当前项目位置对应的页首项目位置
	itemCount=0;
	focusPos=pos-spos;//当前选中项在当前页面是第几项
	for(u8 i=spos,j=0;i<mc.menu[mc.pos].len || j<PAGE_SIZE;i++,j++)
	{
		if(i-spos+1>PAGE_SIZE) break;//要显示的内容超过页面容量
		if(i>=mc.menu[mc.pos].len) { //页面容量超出要显示的内容，隐藏剩余占位文本框控件
			UG_TextboxHide(wnd,textboxIds[j]);
		}
		else { //页面有容量，菜单有内容
			itemCount++;
			u8 index=mc.menu[mc.pos].item[i].id;
			UG_TextboxSetText(wnd,textboxIds[j],menus[index]);
			UG_TextboxShow(wnd,textboxIds[j]);
		}

	}
	CX_FocusObj(wnd,focusPos);
}
//deal with keypad and timer input, it's window specific! Each window deals with input differently!!
void ProcessInputData( UG_WINDOW* wnd )
{
	if(gui->input&INPUT_TIMER){
		UG_TEXTBOX* txt=(UG_TEXTBOX*)(wnd->objlst[wnd->actobj].data);
		CX_TextboxToggleColor(wnd,wnd->objlst[wnd->actobj].id);
	}
	if(gui->input&INPUT_KEY_RIGHT){
		//CX_FocusNextObj(wnd);
		if(mc.menu[mc.pos].item[mc.menu[mc.pos].pos].subpos!=0) {//没有子项
			MC_MoveToSubMenu();
			DisplayCurrentPage(wnd);
		}
	}
	if(gui->input&INPUT_KEY_LEFT){
		if(mc.pos!=0) {//没有父项
			MC_MoveToParentMenu();
			DisplayCurrentPage(wnd);
		}
	}
	if(gui->input&INPUT_KEY_UP){
		if(mc.menu[mc.pos].pos!=0) {//没有上一项
			MC_MoveToPrevItem();
			DisplayCurrentPage(wnd);
		}
	}
	if(gui->input&INPUT_KEY_DOWN){
		if(mc.menu[mc.pos].pos!=mc.menu[mc.pos].len-1) {//没有下一项
			MC_MoveToNextItem();
			DisplayCurrentPage(wnd);
		}
	}
	if(gui->input&INPUT_KEY_OK){
		UG_WindowShow(CreateWindow_SetTime());
	}	
	gui->input=INPUT_NONE;
}

void window_1_callback(UG_MESSAGE *msg)
{
    if(msg->type == MSG_TYPE_OBJECT)
    {
        if(msg->id == OBJ_TYPE_BUTTON)
        {
            if(msg->event == OBJ_EVENT_PRESSED)
            {
//                switch(msg->sub_id)
//                {
//                    case BTN_ID_0:
//                    {
//                        LED4_Write(0);
//                        UG_ButtonHide(&window_1,BTN_ID_1);
//                        break;
//                    }
//                    case BTN_ID_1:
//                    {
//                        UG_TextboxSetText(&window_1, TXB_ID_0, "Button B \nPressed!");
//                        break;
//                    }
//                    case BTN_ID_2:
//                    {
//                        LED4_Write(1);
//                        UG_ButtonShow(&window_1,BTN_ID_1);
//                        break;
//                    }
//                    case BTN_ID_3:
//                    {
//                        UG_TextboxSetText(&window_1, TXB_ID_0, "Image \nPressed!");
//                        LED4_Write(!LED4_Read());
//                        break;
//                    }
//                }
            }
            if(msg->event == OBJ_EVENT_RELEASED)
            {
//                if(msg->sub_id == BTN_ID_1)
//                {
//                        UG_TextboxSetText(&window_1, TXB_ID_0, "This is a \n test sample window!");
//                }
//                if(msg->sub_id == BTN_ID_3)
//                {
//                        UG_TextboxSetText(&window_1, TXB_ID_0, "This is a \n test sample window!");
//                }
            }
        }
        //CyDelay(5);
    }
    
}