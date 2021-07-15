#include "wnd_settime.h"

//test window functions
UG_OBJECT obj_buff_wnd_1[10];
UG_WINDOW window_1;
UG_BUTTON button_1;
UG_TEXTBOX textbox_1;
UG_TEXTBOX textbox_2;
UG_TEXTBOX textbox_3;
void ProcessInputData( UG_WINDOW* wnd );
void window_1_callback(UG_MESSAGE *msg);
UG_U8 hour=0,minute=0,second=0;
UG_U8 hstr[3],mstr[3],sstr[3];

UG_WINDOW* CreateWindow_SetTime()
{
		    UG_WindowCreate(&window_1, obj_buff_wnd_1, 10, window_1_callback);
    // Window Title
//    UG_WindowSetTitleText(&window_1, "Test Window - \xe6GUI v0.31   \x02");      //  \xhh : Special CHR the ASCII value is given by hh interpreted as a hexadecimal number (Check FONT Table)
    UG_WindowSetTitleText(&window_1, "Time Setting");      //  \xhh : Special CHR the ASCII value is given by hh interpreted as a hexadecimal number (Check FONT Table)
    UG_WindowSetTitleTextFont(&window_1, &FONT_4X6);
		UG_WindowSetTitleTextColor(&window_1,0);
    UG_WindowSetXStart(&window_1, 0);
    UG_WindowSetYStart(&window_1, 0);
    UG_WindowSetXEnd(&window_1, 128);       // Window 450x250
    UG_WindowSetYEnd(&window_1, 64);

		
//		UG_ButtonCreate(&window_1, &button_1, BTN_ID_0, 25, 25, 40, 40);
//		UG_ButtonSetFont(&window_1,BTN_ID_0,&FONT_5X8);
//		UG_ButtonSetForeColor(&window_1,BTN_ID_0, C_WHITE);
//		UG_ButtonSetText(&window_1,BTN_ID_0,"B");
		

// Create Textbox
    UG_TextboxCreate(&window_1, &textbox_1, TXB_ID_0, 45, 25, 55, 33);
    UG_TextboxSetFont(&window_1, TXB_ID_0, &FONT_4X6);//5列8行，每个字宽5列，高8行
    //UG_TextboxSetText(&window_1, TXB_ID_0, "00");
		sprintf(hstr,"%02d",hour);
		UG_TextboxSetText(&window_1, TXB_ID_0, hstr);
    UG_TextboxSetForeColor(&window_1, TXB_ID_0, C_WHITE);
		UG_TextboxSetBackColor(&window_1, TXB_ID_0, C_BLACK);
    UG_TextboxSetAlignment(&window_1, TXB_ID_0, ALIGN_CENTER);
			

		
		UG_TextboxCreate(&window_1, &textbox_2, TXB_ID_1, 59, 25, 69, 33);
    UG_TextboxSetFont(&window_1, TXB_ID_1, &FONT_4X6);//5列8行，每个字宽5列，高8行
//    UG_TextboxSetText(&window_1, TXB_ID_1, "00");
		sprintf(mstr,"%02d",minute);
		UG_TextboxSetText(&window_1, TXB_ID_1, mstr);		
    UG_TextboxSetForeColor(&window_1, TXB_ID_1, C_WHITE);
		UG_TextboxSetBackColor(&window_1, TXB_ID_1, C_BLACK);
    UG_TextboxSetAlignment(&window_1, TXB_ID_1, ALIGN_CENTER);
		
		UG_TextboxCreate(&window_1, &textbox_3, TXB_ID_2, 73, 25, 83, 33);
    UG_TextboxSetFont(&window_1, TXB_ID_2, &FONT_4X6);//5列8行，每个字宽5列，高8行
 //   UG_TextboxSetText(&window_1, TXB_ID_2, "00");
		sprintf(sstr,"%02d",second);
		UG_TextboxSetText(&window_1, TXB_ID_2, sstr);	
    UG_TextboxSetForeColor(&window_1, TXB_ID_2, C_WHITE);
		UG_TextboxSetBackColor(&window_1, TXB_ID_2, C_BLACK);
    UG_TextboxSetAlignment(&window_1, TXB_ID_2, ALIGN_CENTER);
		
		UG_WindowShow(&window_1);
		window_1.inputCb=ProcessInputData;
		return &window_1;
}
//deal with keypad and timer input, it's window specific! Each window deals with input differently!!
void ProcessInputData( UG_WINDOW* wnd )
{
	if(gui->input&INPUT_TIMER){
		UG_TEXTBOX* txt=(UG_TEXTBOX*)(wnd->objlst[wnd->actobj].data);
		CX_TextboxToggleColor(wnd,wnd->objlst[wnd->actobj].id);
	}
	if(gui->input&INPUT_KEY_RIGHT){
		CX_FocusNextObj(wnd);
	}
	if(gui->input&INPUT_KEY_LEFT){
		CX_FocusPrevObj(wnd);
	}
	if(gui->input&INPUT_KEY_UP){
		UG_OBJECT* obj=CX_GetActiveObj(wnd);
		if(obj->id==TXB_ID_0){
			hour=(hour+1)%24;
			sprintf(hstr,"%02d",hour);
			UG_TextboxSetText(&window_1, TXB_ID_0, hstr);			
		}
		else if(obj->id==TXB_ID_1) {
			minute=(minute+1)%60;
			sprintf(mstr,"%02d",minute);
			UG_TextboxSetText(&window_1, TXB_ID_1, mstr);				
		}
		else if(obj->id==TXB_ID_2) {
			second=(second+1)%60;
			sprintf(sstr,"%02d",second);
			UG_TextboxSetText(&window_1, TXB_ID_2, sstr);					
		}
	}
	if(gui->input&INPUT_KEY_DOWN){
		UG_OBJECT* obj=CX_GetActiveObj(wnd);
		if(obj->id==TXB_ID_0){
			hour=(hour+23)%24;
			sprintf(hstr,"%02d",hour);
			UG_TextboxSetText(&window_1, TXB_ID_0, hstr);			
		}
		else if(obj->id==TXB_ID_1) {
			minute=(minute+59)%60;
			sprintf(mstr,"%02d",minute);
			UG_TextboxSetText(&window_1, TXB_ID_1, mstr);				
		}
		else if(obj->id==TXB_ID_2) {
			second=(second+59)%60;
			sprintf(sstr,"%02d",second);
			UG_TextboxSetText(&window_1, TXB_ID_2, sstr);					
		}
	}
	if(gui->input&INPUT_KEY_CANCEL){
		UG_WindowHide(wnd);
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