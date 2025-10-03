/* See LICENSE file for copyright and license details. */

/* Внешний вид */
static const unsigned int borderpx  = 2;        /* толщина рамки вокруг окна */
static const unsigned int snap      = 32;       /* на каком расстоянии окно прилипает к краю экрана, другому окну... */
static const int showbar            = 1;        /* 0 не показывать панель, можно все равно показать по mod+b */
static const int topbar             = 1;        /* 0 панель внизу */
static const char *fonts[]          = { "JetBrainsMono:style=Bold:size=10", "Symbols Nerd Font:size=10" };        /* шрифт бара*/
static const char dmenufont[]       = "JetBrainsMono-Bold:size=8";            /* шрифт dmenu*/

/* Для патча dwm-barpadding */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 12;       /* horizontal padding of bar */

/* Для патча dwm-fullgaps-6.4 */
static const unsigned int gappx     = 12;       /* gap p1ixel between windows */

/* Для патча dwm-bar-height-spacing, который у меня не заработал */
static const int user_bh            = 10;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */

static const char col_gray1[]       = "#32302f";        /* цвет col_gray1 */ 
static const char col_gray2[]       = "#83a598";        /* цвет col_gray2 */
static const char col_gray3[]       = "#83a598";        /* цвет col_gray3 */
static const char col_gray4[]       = "#32302f";        /* цвет col_gray4 */
static const char col_cyan[]        = "#afaf2c";        /* цвет col_cyan */
static const char *colors[][3]      = {
	/*               fg         bg         border   */ /* где будет применяться цвет, передний план, задний, рамка */
	[SchemeNorm] = { col_gray2, col_gray1, col_gray2 },
	[SchemeSel]  = { col_cyan, col_gray1,  col_cyan  },
};

// #3f3128
/* tagging */
static const char *tags[] = { "○", "○", "○", "○", "○", "○", "○", "○", "○" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[ ]",      tile },    /* first entry is default */
	{ "< >",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *pcmanfm[]  = { "pcmanfm", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          SHCMD("exec rofi -show drun -I") },
	{ MODKEY,             			XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_x,      spawn,      SHCMD("~/.script/color-picker.sh") },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_r,      spawn,      SHCMD("~/.script/record-xorg.sh") },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_e,      spawn,      {.v = pcmanfm } },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_m,      quit,           {1} },
	{ MODKEY|ShiftMask,                       XK_Print,  spawn,          SHCMD("~/.script/screenshot-xorg.sh") },
	{ MODKEY,             XK_Print,  spawn,          SHCMD("~/.script/screenshot-xorg-full.sh") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

