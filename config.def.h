/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */

static const int bbbpx=1;   // width of bar bottom border in px
/* 2 and 3 are customised, M-b cycles through 0, 2 and 3 */
static const int showbar            = 3;        /* 0 means no bar */
#define topdmenu 1  // 0 is bottom
#if topdmenu
static const int topbar             = 1;        /* 0 means bottom bar */
#else
static const int topbar=0;
#endif
static const int tlpx=6;    // client top and left margin in px


//static const char *fonts[]          = { "monospace:size=10" };
//static const char dmenufont[]       = "monospace:size=10";
static const char *fonts[]          = { "dejavusansmono:size=12" };
static const char dmenufont[]       = "dejavusansmono:size=12";

//static const char col_gray1[]       = "#222222";
//static const char col_gray2[]       = "#444444";
//static const char col_gray3[]       = "#bbbbbb";
//static const char col_gray4[]       = "#eeeeee";
//static const char col_cyan[]        = "#005577";
static const char col_r[]="red";
static const char col_g[]="green";
static const char col_b[]="blue";
static const char col_y[]="yellow";
static const char col_o[]="orange";
static const char col_black[]="black";
static const char col_grey5[]="#5d8aa8";
static const unsigned int abg=0xbb;
static const unsigned int afg=0xff;

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	//[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	//[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeNorm] = { col_grey5, col_black, col_grey5},
	[SchemeSel]  = { col_black, col_grey5, col_r},
    [SchemeRgb]={ col_r,col_g,col_b},
    [SchemeR]={ col_r,col_black,col_b},
    [SchemeG]={ col_g,col_black,col_b},
    [SchemeY]={ col_y,col_black,col_b},
    [SchemeO]={ col_o,col_black,col_b},

};
static const unsigned int sch_a[][3]={
    /*              fg      bg      border */
    [SchemeNorm]={  afg,    abg,    afg},
    [SchemeSel] ={  afg,    abg,    afg},
    [SchemeR]   ={  afg,    abg,    afg},
    [SchemeG]   ={  afg,    abg,    afg},
    [SchemeY]   ={  afg,    abg,    afg},
    [SchemeO]   ={  afg,    abg,    afg},
};


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	//{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_black, "-nf", col_grey5, "-sb", col_grey5, "-sf", col_black
#if !topdmenu
    ,"-b"
#endif
    , NULL };
static const char *termcmd[]  = { "urxvt", NULL };
static const char *termcmd2[]={"runtabbed","--urxvtc","-w",NULL};

static const char *amixer1[]={"amixer","-q","set","Master","10%-",NULL};
static const char *amixer2[]={"amixer","-q","set","Master","toggle",NULL};
static const char *amixer3[]={"amixer","-q","set","Master","10%+",NULL};


static Key keys[] = {
    /* modifier             key             function            argument */
    { MODKEY,               XK_p,           spawn,              {.v = dmenucmd } },
    { MODKEY|ShiftMask,     XK_Return,      spawn,              {.v = termcmd } },
    { MODKEY,               XK_b,           togglebar,          {0} },
    { MODKEY,               XK_j,           focusstack,         {.i = +1 } },
    { MODKEY,               XK_k,           focusstack,         {.i = -1 } },
    { MODKEY,               XK_i,           incnmaster,         {.i = +1 } },
    { MODKEY,               XK_d,           incnmaster,         {.i = -1 } },
    { MODKEY,               XK_h,           setmfact,           {.f = -0.05} },
    { MODKEY,               XK_l,           setmfact,           {.f = +0.05} },
    { MODKEY,               XK_Return,      zoom,               {0} },
    { MODKEY,               XK_Tab,         view,               {0} },
    { MODKEY|ShiftMask,     XK_c,           killclient,         {0} },
    { MODKEY,               XK_t,           setlayout,          {.v = &layouts[0]} },
    { MODKEY,               XK_f,           setlayout,          {.v = &layouts[1]} },
    { MODKEY,               XK_m,           setlayout,          {.v = &layouts[2]} },
    { MODKEY,               XK_space,       setlayout,          {0} },
    { MODKEY|ShiftMask,     XK_space,       togglefloating,     {0} },
    { MODKEY,               XK_0,           view,               {.ui = ~0 } },
    { MODKEY|ShiftMask,     XK_0,           tag,                {.ui = ~0 } },
    { MODKEY,               XK_comma,       focusmon,           {.i = -1 } },
    { MODKEY,               XK_period,      focusmon,           {.i = +1 } },
    { MODKEY|ShiftMask,     XK_comma,       tagmon,             {.i = -1 } },
    { MODKEY|ShiftMask,     XK_period,      tagmon,             {.i = +1 } },
    TAGKEYS(                XK_1,                               0)
    TAGKEYS(                XK_2,                               1)
    TAGKEYS(                XK_3,                               2)
    TAGKEYS(                XK_4,                               3)
    TAGKEYS(                XK_5,                               4)
    TAGKEYS(                XK_6,                               5)
    TAGKEYS(                XK_7,                               6)
    TAGKEYS(                XK_8,                               7)
    TAGKEYS(                XK_9,                               8)
    { MODKEY|ShiftMask,     XK_q,           quit,               {0} },
    { 0,                    0x1008ff11,     spawn,              {.v=amixer1}},
    { 0,                    0x1008ff12,     spawn,              {.v=amixer2}},
    { 0,                    0x1008ff13,     spawn,              {.v=amixer3}},
    { MODKEY|ShiftMask,     XK_Down,        spawn,              {.v = termcmd2}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

