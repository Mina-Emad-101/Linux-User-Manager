#include <X11/X.h>
#include <X11/Xlib.h>
#include <err.h>

static Display* dp;
static int screen;
static Window root;

#define POSX 683
#define POSY 384
#define WIDTH 500
#define HEIGHT 500
#define BORDER_WIDTH 20

int main()
{
	Window win;
	XEvent ev;

	dp = XOpenDisplay("Display");

	if(dp == NULL)
		errx(1, "Can't Open Display!");

	screen = DefaultScreen(dp);
	root = RootWindow(dp, screen);

	win = XCreateSimpleWindow(dp, root, POSX, POSY, WIDTH, HEIGHT, BORDER_WIDTH, BlackPixel(dp, screen), WhitePixel(dp, screen));

	XMapWindow(dp, win);

	while(XNextEvent(dp, &ev) == 0)
	{
		
	}

	XUnmapWindow(dp, win);

	XDestroyWindow(dp, win);

	XCloseDisplay(dp);

	return 0;
}
