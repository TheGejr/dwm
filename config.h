/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */
// static const char *fonts[]          = { "monospace:size=10", "JoyPixels:pixelsize=10:antialias=true:autohint=true"  };
static const char *fonts[]          = { "monospace:size=10", "Noto Color Emoji:pixelsize=10:antialias=true:autohint=true" };
static char dmenufont[]       = "monospace:size=10";

static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";

static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       1 << 8,            0,           -1 },
	/* { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 }, */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
 	// { "[@]",      spiral },
 	// { "[\\]",      dwindle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_q,     ACTION##stack, {.i = 0 } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY|ShiftMask,		XK_Escape,	spawn,	SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Close Xorg?\")\" = Yes ] && killall Xorg") },
	{ MODKEY|ShiftMask,		XK_BackSpace, spawn, SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Reboot computer?\")\" = Yes ] && sudo -A reboot") },
	{ MODKEY,			XK_grave,	spawn,	SHCMD("dmenuunicode") },
	/* { MODKEY|ShiftMask,		XK_grave,	togglescratch,	SHCMD("") }, */
	TAGKEYS(			XK_1,		0)
	TAGKEYS(			XK_2,		1)
	TAGKEYS(			XK_3,		2)
	TAGKEYS(			XK_4,		3)
	TAGKEYS(			XK_5,		4)
	TAGKEYS(			XK_6,		5)
	TAGKEYS(			XK_7,		6)
	TAGKEYS(			XK_8,		7)
	TAGKEYS(			XK_9,		8)

	/**  Common keybindings  **/
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,		          XK_Return, togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY,                       XK_w,      spawn,          SHCMD("$BROWSER") },
  	{ MODKEY,                       XK_r,      spawn,          SHCMD("$FILE") },

  	/**  Movement keybindings  **/
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
  	{ MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_Right,  setmfact,       {.f = +0.05} },

  	/**  Layout keybindings  **/
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
  	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

  	/**  Misc. keybindings  **/
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

  	/**  Media control keybindings  **/
  	{ MODKEY,			                  XK_a,      spawn,		       SHCMD("st -e gmc control") },
  	{ MODKEY,                       XK_p,      spawn,          SHCMD("mpc toggle") },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("mpc pause ; pauseallmpv") },
	{ MODKEY,                       XK_minus,  spawn,          SHCMD("gmc down") },
	{ MODKEY|ShiftMask,             XK_minus,	 spawn,		       SHCMD("gmc down 15") },
	{ MODKEY,                       XK_plus,	 spawn,		       SHCMD("gmc up") },
	{ MODKEY|ShiftMask,		          XK_plus,	 spawn,		       SHCMD("gmc up 15") },

  	/**  Mediakeys keybindings  **/
  	{ 0,                            XF86XK_AudioMute,        spawn,   SHCMD("gmc toggle") },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn,		SHCMD("gmc up") },
	{ 0,                            XF86XK_AudioLowerVolume, spawn,		SHCMD("gmc down") },
	{ 0,                            XF86XK_AudioPrev,        spawn,		SHCMD("mpc prev") },
	{ 0,                            XF86XK_AudioNext,        spawn,		SHCMD("mpc next") },
	{ 0,                            XF86XK_AudioPause,       spawn,		SHCMD("mpc pause") },
	{ 0,                            XF86XK_AudioPlay,        spawn,		SHCMD("mpc play") },
	{ 0,                            XF86XK_AudioStop,	       spawn,		SHCMD("mpc stop") },
	{ 0,                            XF86XK_AudioRewind,      spawn,		SHCMD("mpc seek -10") },
	{ 0,                            XF86XK_AudioForward,     spawn,		SHCMD("mpc seek +10") },
	{ 0,                            XF86XK_AudioMedia,       spawn,		SHCMD("st -e ncmpcpp") },
	{ 0,                            XF86XK_PowerOff,         spawn,		SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Shutdown computer?\")\" = Yes ] && sudo -A shutdown -h now") },
	{ 0,                            XF86XK_Calculator,       spawn,		SHCMD("st -e bc -l") },
	{ 0,                            XF86XK_Sleep,            spawn,		SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Hibernate computer?\")\" = Yes ] && sudo -A zzz") },
	{ 0,                            XF86XK_WWW,              spawn,		SHCMD("$BROWSER") },
	{ 0,                            XF86XK_DOS,	             spawn,		SHCMD("st") },
	{ 0,                            XF86XK_ScreenSaver,	     spawn,		SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0,                            XF86XK_TaskPane,         spawn,		SHCMD("st -e htop") },
	/* { 0,                            XF86XK_Mail,             spawn,		SHCMD("st -e neomutt ; pkill -RTMIN+12 dwmblocks") }, */
  	/* { 0,                            XF86XK_MyComputer,       spawn,		SHCMD("st -e lf /") }, */
	/* { 0,                            XF86XK_Battery,          spawn,		SHCMD("") }, */
	{ 0,                            XF86XK_Launch1,          spawn,		SHCMD("xset dpms force off") },
	{ 0,                            XF86XK_TouchpadToggle,   spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0,                            XF86XK_TouchpadOff,      spawn,		SHCMD("synclient TouchpadOff=1") },
	{ 0,                            XF86XK_TouchpadOn,       spawn,		SHCMD("synclient TouchpadOff=0") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          SHCMD("st -e statusbarinfo") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
	{ "incnmaster",     incnmaster },
	{ "togglefloating", togglefloating },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
	{ "xrdb",		xrdb },
};
