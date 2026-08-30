/* See LICENSE file for copyright and license details. */

/* Helper macros for spawning commands */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define CMD(...)   { .v = (const char*[]){ __VA_ARGS__, NULL } }

/* appearance */
static const unsigned int borderpx       = 1;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const unsigned int gappih         = 5;  /* horiz inner gap between windows */
static const unsigned int gappiv         = 5;  /* vert inner gap between windows */
static const unsigned int gappoh         = 5;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 5;  /* vert outer gap between windows and screen edge */
static const int smartgaps_fact          = 1;   /* gap factor when there is only one client; 0 = no gaps, 3 = 3x outer gaps */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
#define ICONSIZE 20    /* icon size */
#define ICONSPACING 5  /* space between icon and title */
/* Status is to be shown on: -1 (all monitors), 0 (a specific monitor by index), 'A' (active monitor) */
static const int statusmon               = 'A';
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int showsystray             = 1;   /* 0 means no systray */

/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype              = INDICATOR_TOP_LEFT_SQUARE;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_TOP_LEFT_SQUARE;
static const char *fonts[]               = { "MesloLGS Nerd Font Mono:size=16", "NotoColorEmoji:pixelsize=16:antialias=true:autohint=true" };
static const char dmenufont[]            = "MesloLGS Nerd Font Mono:size=16";

static char c000000[]                    = "#000000"; // placeholder value

static char normfgcolor[]                = "#bbbbbb";
static char normbgcolor[]                = "#222222";
static char normbordercolor[]            = "#444444";
static char normfloatcolor[]             = "#db8fd9";

static char selfgcolor[]                 = "#eeeeee";
static char selbgcolor[]                 = "#005577";
static char selbordercolor[]             = "#005577";
static char selfloatcolor[]              = "#005577";

static char titlenormfgcolor[]           = "#bbbbbb";
static char titlenormbgcolor[]           = "#222222";
static char titlenormbordercolor[]       = "#444444";
static char titlenormfloatcolor[]        = "#db8fd9";

static char titleselfgcolor[]            = "#eeeeee";
static char titleselbgcolor[]            = "#005577";
static char titleselbordercolor[]        = "#005577";
static char titleselfloatcolor[]         = "#005577";

static char tagsnormfgcolor[]            = "#bbbbbb";
static char tagsnormbgcolor[]            = "#222222";
static char tagsnormbordercolor[]        = "#444444";
static char tagsnormfloatcolor[]         = "#db8fd9";

static char tagsselfgcolor[]             = "#eeeeee";
static char tagsselbgcolor[]             = "#005577";
static char tagsselbordercolor[]         = "#005577";
static char tagsselfloatcolor[]          = "#005577";

static char hidnormfgcolor[]             = "#005577";
static char hidselfgcolor[]              = "#227799";
static char hidnormbgcolor[]             = "#222222";
static char hidselbgcolor[]              = "#222222";

static char urgfgcolor[]                 = "#bbbbbb";
static char urgbgcolor[]                 = "#222222";
static char urgbordercolor[]             = "#ff0000";
static char urgfloatcolor[]              = "#db8fd9";

static char *colors[][ColCount] = {
	/*                       fg                bg                border                float */
	[SchemeNorm]         = { normfgcolor,      normbgcolor,      normbordercolor,      normfloatcolor },
	[SchemeSel]          = { selfgcolor,       selbgcolor,       selbordercolor,       selfloatcolor },
	[SchemeTitleNorm]    = { titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor },
	[SchemeTitleSel]     = { titleselfgcolor,  titleselbgcolor,  titleselbordercolor,  titleselfloatcolor },
	[SchemeTagsNorm]     = { tagsnormfgcolor,  tagsnormbgcolor,  tagsnormbordercolor,  tagsnormfloatcolor },
	[SchemeTagsSel]      = { tagsselfgcolor,   tagsselbgcolor,   tagsselbordercolor,   tagsselfloatcolor },
	[SchemeHidNorm]      = { hidnormfgcolor,   hidnormbgcolor,   c000000,              c000000 },
	[SchemeHidSel]       = { hidselfgcolor,    hidselbgcolor,    c000000,              c000000 },
	[SchemeUrg]          = { urgfgcolor,       urgbgcolor,       urgbordercolor,       urgfloatcolor },
};

static const char *const autostart[] = {
    "xset", "s", "off", NULL,
    "xset", "s", "noblank", NULL,
    "xset", "-dpms", NULL,
    "dbus-update-activation-environment", "--systemd", "--all", NULL,
    "/usr/lib/mate-polkit/polkit-mate-authentication-agent-1", NULL,
    "dunst", NULL,
    "picom", "-b", NULL,
    //"sh", "-c", "feh --bg-fill ~/Pictures/GL3OJDYX0AA77uh.jpg", NULL,
    "sh", "-c", "feh --randomize --bg-fill ~/Pictures/backgrounds/*", NULL,    
    "slstatus", NULL,
    "xrandr", "--output", "DisplayPort-0", "--mode", "1920x1080", "--rate", "180", NULL,
    "conky", NULL,
	NULL /* terminate */
};

static char *tagicons[][NUMTAGS] =
{
	[DEFAULT_TAGS]        = { "1", "2", "3", "4", "5", "6", "7", "8", "9" },
	[ALTERNATIVE_TAGS]    = { "A", "B", "C", "D", "E", "F", "G", "H", "I" },
	[ALT_TAGS_DECORATION] = { "<1>", "<2>", "<3>", "<4>", "<5>", "<6>", "<7>", "<8>", "<9>" },
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *	WM_WINDOW_ROLE(STRING) = role
	 *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
	 */
	RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
	RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
	RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
	RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
	RULE(.class = "Gimp", .tags = 1 << 4)
	RULE(.class = "Firefox", .tags = 1 << 7)
};

static const BarRule barrules[] = {
	/* monitor   bar    alignment         widthfunc                 drawfunc                clickfunc                hoverfunc                name */
	{ -1,        0,     BAR_ALIGN_LEFT,   width_tags,               draw_tags,              click_tags,              hover_tags,              "tags" },
	{  0,        0,     BAR_ALIGN_RIGHT,  width_systray,            draw_systray,           click_systray,           NULL,                    "systray" },
	{ -1,        0,     BAR_ALIGN_LEFT,   width_ltsymbol,           draw_ltsymbol,          click_ltsymbol,          NULL,                    "layout" },
	{ statusmon, 0,     BAR_ALIGN_RIGHT,  width_status,             draw_status,            click_status,            NULL,                    "status" },
	{ -1,        0,     BAR_ALIGN_NONE,   width_wintitle,           draw_wintitle,          click_wintitle,          NULL,                    "wintitle" },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 180;  /* refresh rate (per second) for client move/resize */
static const int refreshrate_placemouse = 180; /* refresh rate (per second) for placemouse */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
	"dmenu_run",
	"-m", dmenumon,
	"-fn", dmenufont,
	"-nb", normbgcolor,
	"-nf", normfgcolor,
	"-sb", selbgcolor,
	"-sf", selfgcolor,
	NULL
};
//static const char *termcmd[]  = { "st", NULL };
static const char *termcmd[]  = { "ghostty", NULL };
static const char *browser[]  = { "brave", NULL };
static const char *filesbrowser[]  = { "thunar", NULL };
static const char *chat[]  = { "vesktop", NULL };
static const char *editor[]  = { "geany", NULL };

/* Web app commands using xdg-open */
static const char *chatgptcmd[]   = { "webapp-launch", "https://chatgpt.com", NULL };

static const Key keys[] = {
	/* modifier                     key            function                argument */
	{ MODKEY,                       XK_space,      spawn,                  {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,     spawn,                  {.v = termcmd } },
    { MODKEY,                       XK_b,          spawn,                  {.v = browser } },
    { MODKEY,                       XK_e,          spawn,                  {.v = filesbrowser } },
    { MODKEY,                       XK_d,          spawn,                  {.v = chat } },
    { MODKEY,                       XK_c,          spawn,                  {.v = editor } },
    { MODKEY,                       XK_a,          spawn,                  {.v = chatgptcmd } },
    { MODKEY,                       XK_g,          spawn,                  SHCMD ("github-desktop")},         
	{ MODKEY|ShiftMask,             XK_b,          togglebar,              {0} },
	//{ MODKEY,                       XK_j,          focusstack,             {.i = +1 } },
	//{ MODKEY,                       XK_k,          focusstack,             {.i = -1 } },
	//{ MODKEY,                       XK_i,          incnmaster,             {.i = +1 } },
	//{ MODKEY,                       XK_d,          incnmaster,             {.i = -1 } },
	//{ MODKEY,                       XK_h,          setmfact,               {.f = -0.05} },
	//{ MODKEY,                       XK_l,          setmfact,               {.f = +0.05} },
	//{ MODKEY|ShiftMask,             XK_Return,     zoom,                   {0} },
	//{ MODKEY|Mod4Mask,              XK_u,          incrgaps,               {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_u,          incrgaps,               {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_i,          incrigaps,              {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_i,          incrigaps,              {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_o,          incrogaps,              {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_o,          incrogaps,              {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_6,          incrihgaps,             {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_6,          incrihgaps,             {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_7,          incrivgaps,             {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_7,          incrivgaps,             {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_8,          incrohgaps,             {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_8,          incrohgaps,             {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_9,          incrovgaps,             {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_9,          incrovgaps,             {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_0,          togglegaps,             {0} },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_0,          defaultgaps,            {0} },
	//{ MODKEY,                       XK_Tab,        view,                   {0} },
	{ MODKEY,                       XK_q,          killclient,             {0} },
	{ MODKEY|ShiftMask,             XK_q,          quit,                   {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,          quit,                   {1} },
	//{ MODKEY,                       XK_t,          setlayout,              {.v = &layouts[0]} },
	//{ MODKEY|ShiftMask,             XK_f,          setlayout,              {.v = &layouts[1]} },
	//{ MODKEY,                       XK_m,          setlayout,              {.v = &layouts[2]} },
	//{ MODKEY|ShiftMask,             XK_space,      setlayout,              {0} },
	{ MODKEY,                       XK_v,          togglefloating,         {0} },
	{ MODKEY,                       XK_f,          togglefullscreen,       {0} },
	//{ MODKEY,                       XK_0,          view,                   {.ui = ~0 } },
	//{ MODKEY|ShiftMask,             XK_0,          tag,                    {.ui = ~0 } },
	//{ MODKEY,                       XK_comma,      focusmon,               {.i = -1 } },
	//{ MODKEY,                       XK_period,     focusmon,               {.i = +1 } },
	//{ MODKEY|ShiftMask,             XK_comma,      tagmon,                 {.i = -1 } },
	//{ MODKEY|ShiftMask,             XK_period,     tagmon,                 {.i = +1 } },
	TAGKEYS(                        XK_1,                                  0)
	TAGKEYS(                        XK_2,                                  1)
	TAGKEYS(                        XK_3,                                  2)
	TAGKEYS(                        XK_4,                                  3)
	TAGKEYS(                        XK_5,                                  4)
	TAGKEYS(                        XK_6,                                  5)
	TAGKEYS(                        XK_7,                                  6)
	TAGKEYS(                        XK_8,                                  7)
	TAGKEYS(                        XK_9,                                  8)
    { MODKEY|ControlMask|ShiftMask, XK_r,          spawn,                  SHCMD("systemctl reboot")},
    { MODKEY|ControlMask|ShiftMask, XK_s,          spawn,                  SHCMD("shutdown now")},	
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask           button          function        argument */
	{ ClkLtSymbol,          0,                   Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                   Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button2,        spawn,          {.v = termcmd } },
	/* placemouse options, choose which feels more natural:
	 *    0 - tiled position is relative to mouse cursor
	 *    1 - tiled postiion is relative to window center
	 *    2 - mouse pointer warps to window center
	 *
	 * The moveorplace uses movemouse or placemouse depending on the floating state
	 * of the selected client. Set up individual keybindings for the two if you want
	 * to control these separately (i.e. to retain the feature to move a tiled window
	 * into a floating position).
	 */
	{ ClkClientWin,         MODKEY,              Button1,        moveorplace,    {.i = 1} },
	{ ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
};

