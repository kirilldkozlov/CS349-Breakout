#ifndef XLIB
#define XLIB
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
#endif

#ifndef CORE
#define CORE
	#include <cstdlib>
	#include <iostream>
	#include <unistd.h>
	#include <list>
	#include <sys/time.h>
#endif

struct XInfo {
  Display*  display;
  Window   window;
  GC       gc;
  Pixmap   pixmap;
};

class Displayable {
  public:
		bool active = true;
    virtual void paint(XInfo &xinfo) = 0;
};
