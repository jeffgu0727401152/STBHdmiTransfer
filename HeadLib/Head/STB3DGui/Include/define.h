
// touch message
#define WNDMSG_MIN         	0x00000000
#define WNDMSG_MAX          0xFFFFFFFF

#define WNDMSG_NULL        	0x00000000

#define WNDMSG_QUIT        	0x00000001
#define WNDMSG_DESTROY     	0x00000002

#define WNDMSG_TOUCHDOWN	0x00000010
#define WNDMSG_TOUCHUP		0x00000011
#define WNDMSG_TOUCHMOVE	0x00000012
#define WNDMSG_KEYEVENT		0x00000013

#define WNDMSG_TIMER			0x00000020

// broadcast message
// wParam: mouse point position(screen)
// lParam: continue count
#define WNDBCMSG_CONTINUE_CLICK		0x00000030

// broadcast message
// wParam: CBaseWnd
// lParam: visible
#define WNDBCMSG_POPUPWNDVISIBLE	0X00000031

// broadcast message
// wParam: unused
// lParam: is_over
#define WNDBCMSG_LIMITTIMEOVER		0X00000032

// wParam: null
// lParam: null
#define LISTVIEWMSG_REFRESH		0X00000050
// wParam: null
// lParam: null
#define LISTVIEWMSG_PREVPAGE	0X00000051
// wParam: null
// lParam: null
#define LISTVIEWMSG_NEXTPAGE	0X00000052


// 系统控件的timer id，定义到SYSCTRL_TIMERID_BASE之后，
 // 以免和用户定义的 timer id冲突，用户总喜欢从0开始定义的
#define SYSCTRL_TIMERID_BASE 	0x00007FFF

#define WNDMSG_USERBASE			0x00008000

#define PEEKMESSAGE_DEFAULT		0x00000000
#define PEEKMESSAGE_REMOVE		0x00000001

#define CLASSNAME_MAXLEN		32

#define WINDOWFLAG_DEFAULT		0x00000000
#define WINDOWFLAG_POPUP		0x00000001

#define WINDOWSTATE_DEFAULT		0x00000000
#define WINDOWSTATE_DISABLED	0x00000001
#define WINDOWSTATE_INVISIBLE	0x00000002
#define WINDOWSTATE_NOCLIP		0x00000004
#define WINDOWSTATE_NOFOCUS		0x00000008

#define BUTTONSTATE_NORMAL		0x00000000
#define BUTTONSTATE_PRESSING	0x00000001
#define BUTTONSTATE_PRESSED		0x00000002

#define BUTTONTYPE_NORMAL		0x00000000
#define BUTTONTYPE_RADIO		0x00000001


#define E3D_ZORDER_NUMBER_MIN    500.0
#define E3D_ZORDER_NUMBER_MAX    3000.0

// 1. 窗口z序必须在 E3D_ZORDER_NUMBER_MIN/E3D_ZORDER_NUMBER_MAX之间
// 2. list view的效果范围大约在 z-listview +/- 700 左右
#define EMBEDDED_WINDOW_ZORDER_START	2995.0
#define EMBEDDED_WINDOW_ZORDER_END		2101.0
#define E3D_LISTVIEW_ZORDER 			2100.00
#define POPUP_WINDOW_ZORDER_START		2000.0
#define POPUP_WINDOW_ZORDER_END			560.0

// focus
#define E3D_ZORDER_FOCUSTEXTURE  		555.0
// 特殊控件Z序, 效果,overlay,鼠标，FPS
#define E3D_ZORDER_MASKTEXTURE 550.0
#define E3D_ZORDER_OVERLAYTEXTURE 548.0
#define E3D_ZORDER_LIMITTEXTURE 546.0
#define E3D_ZORDER_FPSTEXTURE 544.0

// 飞入，淡入淡出,等特殊窗口效果
#define E3D_ZORDER_EFFECT_START	 		540.0
#define E3D_ZORDER_EFFECT_END  			510.0

#define E3D_ZORDER_FLOATINGBUBBLE_START 504.0
#define E3D_ZORDER_FLOATINGBUBBLE_END 503.0

#define E3D_ZORDER_MOUSETEXTURE 502.0
#define E3D_ZORDER_MOUSECURSORTEXTURE 501.0

#ifdef ANDROID
#define DEFAULT_FONTSIZE	18
#else
#define DEFAULT_FONTSIZE	20
#endif

#define ZORDER_SCALE(fZorder)   ((fZorder) / E3D_ZORDER_NUMBER_MIN)

#define LISTCTRL_ITEMTEXT_MAXLEN 32

#define CLICK_MAX_DISTANCE		30
