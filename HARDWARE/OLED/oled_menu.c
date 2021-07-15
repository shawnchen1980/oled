#include "oled_menu.h"
#include "oled.h"
#include "stdio.h"
MenuConfig mc;

const u8 *menus[]={
	"根节点",//0,不显示
	"菜单1",//1
	"菜单2",//2
	"菜单3",//3
	"菜单1-1",//4
	"菜单1-2",//5
	"菜单2-1",//6
	"菜单2-2",//7
	"菜单3-1"//8
	
};
void MC_Init(UG_WINDOW* wnd)
{
	mc.len=0;
	mc.pos=0;
	mc.currWnd=wnd;
	MC_AddItem(0,1);
	MC_AddItem(0,2);
	MC_AddItem(0,3);
	MC_AddItem(1,4);
	MC_AddItem(1,5);
	MC_AddItem(2,6);
	MC_AddItem(2,7);
	MC_AddItem(3,8);
}

//pid-parent item's id
//id-current item's id
//return-index of menu in the mc for the newly added
//0xff for error
u8 MC_AddItem(u8 pid, u8 id)
{
	if(pid==0)
	{
		if(mc.len==0) mc.len=1;
		if(mc.menu[0].len==MAX_ITEMS_IN_A_SERIES) return 0xff;
		MenuItem* temp=&mc.menu[0].item[(mc.menu[0].len++)];
		mc.menu[0].pos=0;
		mc.menu[0].ppos=0;
		temp->id=id;
		temp->subpos=0;//it means no sub menu items, this one is now the leaf node
		temp->val=0;
		return 0;
	}
	else
	{
		MenuItem* temp=NULL;
		u8 pmenuInd,pitemInd,menuInd,itemInd;
		for(u8 i=0;i<mc.len;i++)
		{
			for(u8 j=0;j<mc.menu[i].len;j++)
			{
				if(mc.menu[i].item[j].id==pid)
				{
					temp=&mc.menu[i].item[j];
					pmenuInd=i;
					pitemInd=j;
					break;
				}
			}
			if(temp!=NULL) break;
		}
		if(temp==NULL) return 0xff;
		if(temp->subpos==0)//the current added menu item is the first item of its menu.
		{
			if(mc.len==MAX_ITEM_SERIES) return 0xff;
			MenuSeries* pm=&mc.menu[mc.len++];
			pm->len=1;
			pm->pos=0;
			pm->ppos=pmenuInd;
			pm->item[0].id=id;
			pm->item[0].subpos=0;
			pm->item[0].val=0;
			temp->subpos=mc.len-1;
			return temp->subpos;
		}
		else
		{
			if(mc.menu[temp->subpos].len==MAX_ITEMS_IN_A_SERIES) return 0xff;
			MenuSeries* pm=&mc.menu[temp->subpos];
			MenuItem* pi=&pm->item[pm->len++];
			pi->id=id;
			pi->subpos=0;
			pi->val=0;
			return temp->subpos;
			
		}
		
	}
}

void MC_PrintConfig()
{
	printf("the number of menus is %d\n",mc.len);
	for(u8 i=0;i<mc.len;i++)
	{
		printf("the length of menu %d is %d,its parant node is %d, it has the following menu items\n",i,mc.menu[i].len,mc.menu[i].ppos);
		for(u8 j=0;j<mc.menu[i].len;j++)
		{
			printf("node %d, ",mc.menu[i].item[j].id);
		}
		printf("\n");
	}
	
}

void MC_DisplayCurrentMenu()
{
	/*
	printf("the current menu has nodes: ");
	for(u8 i=0;i<mc.menu[mc.pos].len;i++)
	{
		printf("%d ",mc.menu[mc.pos].item[i].id);
	}
	printf("\n, the current selected is %d\n",mc.menu[mc.pos].item[mc.menu[mc.pos].pos].id);
	*/
	OLED_Clear();
	u8 x,y;
	x=HMARGIN;
	y=VMARGIN;
	for(u8 i=mc.menu[mc.pos].pos;i<mc.menu[mc.pos].len;i++)
	{
		u8 index=mc.menu[mc.pos].item[i].id;
		OLED_ShowString(x,y,menus[index],WORD_SIZE,1);
		y+=VMARGIN+ROW_HEIGHT;
		if(y>MAX_HEIGHT-ROW_HEIGHT) break;
	}
	x=0;
	y=VMARGIN;
	OLED_ShowChar(x,y,'>',16,1);
	OLED_Refresh();
}

void MC_MoveToPrevItem()
{
	printf("I am moving up.\n");
	u8 pos=mc.menu[mc.pos].pos;
	if(pos==0)
	{
		printf("But I'm already at the top\n");
	}
	else
	{
		mc.menu[mc.pos].pos=--pos;
		printf("And the current node is %d\n",mc.menu[mc.pos].item[pos].id);
	}
	
}

void MC_MoveToNextItem()
{
	printf("I am moving down.\n");
	u8 pos=mc.menu[mc.pos].pos;
	if(pos==mc.menu[mc.pos].len-1)
	{
		printf("But I'm already at the bottom\n");
	}
	else
	{
		mc.menu[mc.pos].pos=++pos;
		printf("And the current node is %d\n",mc.menu[mc.pos].item[pos].id);
	}
	
}

void MC_MoveToSubMenu()
{
	printf("I am moving to the sub-menu.\n");
	u8 pos=mc.menu[mc.pos].pos;
	if(mc.menu[mc.pos].item[pos].subpos==0)
	{
		printf("But the current item has no sub-menu\n");
	}
	else
	{
		mc.pos=mc.menu[mc.pos].item[pos].subpos;
		mc.menu[mc.pos].pos=0;
		//MC_DisplayCurrentMenu();
	}
}

void MC_MoveToParentMenu()
{
	printf("I am moving to the parent-menu.\n");
	u8 pos=mc.menu[mc.pos].pos;
	if(mc.pos==0)
	{
		printf("But I'm already at the root.\n");
	}
	else
	{
		mc.pos=mc.menu[mc.pos].ppos;
		//mc.menu[mc.pos].pos=0;
		//MC_DisplayCurrentMenu();
	}
}