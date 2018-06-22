#ifndef COMMON_H
#define COMMON_H

namespace LEFTWIDGET{
#define LEFTWIDGETWIDTH 800    //左边窗口宽度
#define LEFTWIDGETHEIGHT 600  //左边窗口高度

#define	MENU_X	0  //菜单X
#define MENU_Y 0    //菜单Y
#define MENUWIDTH 80    //菜单宽度
#define	MENUHEIGHT	50  //菜单高度

#define	IMAGEFORCOORD_X	80  //坐标状态X
#define IMAGEFORCOORD_Y 0    //坐标状态Y
#define IMAGEFORCOORDWIDTH 70    //坐标状态宽度
#define	IMAGEFORCOORDHEIGHT	50  //坐标状态高度

#define	IMAGEFORORDER_X	150  //命令状态X
#define IMAGEFORORDER_Y 0    //命令状态Y
#define IMAGEFORORDERWIDTH 70    //命令状态宽度
#define	IMAGEFORORDERHEIGHT	50  //命令状态高度

#define	IMAGEFORSTATE_X	220  //报警按钮X
#define IMAGEFORSTATE_Y 0    //报警按钮Y
#define IMAGEFORSTATEWIDTH 70    //报警按钮宽度
#define	IMAGEFORSTATEHEIGHT	50  //报警按钮高度

#define	IMAGEFORSPEED_X	290  //速度状态X
#define IMAGEFORSPEED_Y 0    //速度状态Y
#define IMAGEFORSPEEDWIDTH 70    //速度状态宽度
#define	IMAGEFORSPEEDHEIGHT	50  //速度状态高度

#define	STATEBYSYS_X	360  //报警按钮X
#define STATEBYSYS_Y 0    //报警按钮Y
#define STATEBYSYSWIDTH 390    //报警按钮宽度
#define	STATEBYSYSHEIGHT	50  //报警按钮高度

#define	CLOSEBTN_X	750  //关闭按钮X
#define CLOSEBTN_Y 0    //关闭按钮Y
#define CLOSEBTNWIDTH 50    //关闭按钮宽度
#define	CLOSEBTNHEIGHT	50  //关闭按钮高度

#define	PAGEOPTION_X	0  //界面选择X
#define PAGEOPTION_Y 50    //界面选择Y
#define PAGEOPTIONWIDTH 800    //界面选择宽度
#define	PAGEOPTIONHEIGHT    500  //界面选择高度

#define	STATEBAR_X	0  //底部状态栏X
#define STATEBAR_Y 550    //底部状态栏Y
#define STATEBARWIDTH 800    //底部状态栏宽度
#define	STATEBARHEIGHT	50  //底部状态栏高度
}

#define RIGHTWIDGETWIDTH 200    //右边窗口宽度
#define RIGHTWIDGETHEIGHT 600  //右边窗口高度

#define WIDGETWIDTH LEFTWIDGETWIDTH+RIGHTWIDGETWIDTH    //界面宽度
#define WIDGETHEIGHT 600    //界面高度

namespace ViewData{

}

typedef enum Digit{
    ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN
}Digit;

namespace SetData{
    typedef enum{
        ZH_CN,
        EN
    }LANGUAGE;
}
#endif	//COMMONVAR_H
