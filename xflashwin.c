#include <X11/Xlib.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    Display *dpy;
    Window focused=0;
    Window rr;
    int revert_to=0;
    GC gc;
    XGCValues gcv;
    int xr, yr;
    unsigned int wr, hr, bwr, dr;

    dpy = XOpenDisplay(":0.0");
    XGetInputFocus(dpy, &focused, &revert_to);
    XGetGeometry(dpy, focused, &rr, &xr, &yr, &wr, &hr, &bwr, &dr);

    gc = XCreateGC(dpy, focused, 0, NULL);
    XSetSubwindowMode(dpy, gc, IncludeInferiors);

    gcv.function = GXcopyInverted;
    XChangeGC(dpy, gc, GCFunction, &gcv);
    XFlushGC(dpy, gc);
    XCopyArea(dpy, focused, focused, gc, xr, yr, wr, hr, 0, 0);

    for(;;) {
      XEvent e;
      XNextEvent(dpy, &e);
      if (e.type == NoExpose)
        break;
    }

    exit(0);
}
