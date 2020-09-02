/* /ee LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 1;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static const unsigned gappx   = 10;
static const char *fonts[]          = { "iosevka-term:size=18" , "FontAwesome:size=18"};
static const char dmenufont[]       = "iosevka-term:size=18"; /* "monospace:size=14"; */
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       /* [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  }, */
      [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };  */

static const char *tags[] = { " ", " ", " ", " ", " ", " " }; 

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask                 isfloating   monitor */
	{ "Chromium",  "chromium",   "WorkSpace*",   1 << 5,       0,           -1 },
	{ "Chromium",  NULL,         NULL,                          2,       0,           -1 },
	{ "Wfica",    "Wfica",       NULL,                     1 << 5,       0,           -1 },
	{ "St",        NULL,     "ranger",                     1 << 4,       0,           -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};

#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_w,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

    /* apps shortcut */
    { MODKEY,                       XK_b,      spawn,           SHCMD("chromium") },
    { MODKEY,                       XK_c,      spawn,           SHCMD("chromium --new-window 'myworkspace.jpmchase.com' &") },
    { MODKEY|ShiftMask,             XK_r,      spawn,           SHCMD("reboot")},
    { MODKEY,                       XK_r,      spawn,           SHCMD("st -e ranger ~")},

    { 0, XF86XK_AudioMute,          spawn,        SHCMD("amixer set Master toggle && kill -44 $(pidof dwmblocks)") },
    { 0, XF86XK_AudioRaiseVolume,   spawn,        SHCMD("amixer set Master 5%+ && kill -44 $(pidof dwmblocks)") },
    { 0, XF86XK_AudioLowerVolume,   spawn,        SHCMD("amixer set Master 5%- && kill -44 $(pidof dwmblocks)") },
    { 0, XF86XK_AudioPrev,          spawn,        SHCMD("mpc prev") },
    { 0, XF86XK_AudioNext,          spawn,        SHCMD("mpc next") },
    { 0, XF86XK_AudioPause,         spawn,        SHCMD("mpc pause") },
    { 0, XF86XK_AudioPlay,          spawn,        SHCMD("mpc play") },
    { 0, XF86XK_AudioStop,          spawn,        SHCMD("mpc stop") },
    { 0, XF86XK_AudioRewind,        spawn,        SHCMD("mpc seek -10") },
    { 0, XF86XK_AudioForward,       spawn,        SHCMD("mpc seek +10") },
    { 0, XF86XK_AudioMedia,         spawn,        SHCMD("st -e ncmpcpp") },
    { 0, XF86XK_PowerOff,           spawn,        SHCMD("sysact") },
    { 0, XF86XK_Calculator,         spawn,        SHCMD("st -e bc -l") },
    { 0, XF86XK_Display,            spawn,        SHCMD("changeDisplay") },
    { 0, XF86XK_Sleep,              spawn,        SHCMD("sudo -A zzz") },
    { 0, XF86XK_WWW,                spawn,        SHCMD("$BROWSER") },
    { 0, XF86XK_DOS,                spawn,        SHCMD("st") },
    { 0, XF86XK_ScreenSaver,        spawn,        SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
    { 0, XF86XK_TaskPane,           spawn,        SHCMD("st -e htop") },
    { 0, XF86XK_Mail,               spawn,        SHCMD("st -e neomutt ; pkill -RTMIN+12 dwmblocks") },
    { 0, XF86XK_MyComputer,         spawn,        SHCMD("st -e lf /") },
/* { 0, XF86XK_Battery,        spawn,        SHCMD("") }, */
    { 0, XF86XK_Launch1,           spawn,        SHCMD("xset dpms force off") },
    { 0, XF86XK_TouchpadToggle,    spawn,        SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
    { 0, XF86XK_TouchpadOff,       spawn,        SHCMD("synclient TouchpadOff=1") },
    { 0, XF86XK_TouchpadOn,        spawn,        SHCMD("synclient TouchpadOff=0") },
    { 0, XF86XK_MonBrightnessUp,    spawn,        SHCMD("xbacklight -inc 2") },
    { 0, XF86XK_MonBrightnessDown,    spawn,        SHCMD("xbacklight -dec 2") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

