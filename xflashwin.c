#include <X11/Xlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    Display *dpy;
    Window focused=0;
    Window rr;
    int revert_to=0;
    GC gc;
    XGCValues gcv;
    int xr, yr;
    unsigned int wr, hr, bwr, dr;

    struct timespec tp1;
    struct timespec tp2;

    dpy = XOpenDisplay(":0.0");
    XGetInputFocus(dpy, &focused, &revert_to);
    XGetGeometry(dpy, focused, &rr, &xr, &yr, &wr, &hr, &bwr, &dr);

    gc = XCreateGC(dpy, focused, 0, NULL);
    XSetSubwindowMode(dpy, gc, IncludeInferiors);

    gcv.function = GXcopyInverted;
    XChangeGC(dpy, gc, GCFunction, &gcv);
    XFlushGC(dpy, gc);
    XCopyArea(dpy, focused, focused, gc, xr, yr, wr, hr, 0, 0);

    clock_gettime(CLOCK_REALTIME, &tp1);

    for(;;) {
      XEvent e;
      while (XPending(dpy)) XNextEvent(dpy, &e);

      usleep(5000);

      clock_gettime(CLOCK_REALTIME, &tp2);
      if (((tp2.tv_nsec - tp1.tv_nsec)/1000000 + 1000 * (tp2.tv_sec - tp1.tv_sec)) > 30)
        break;

//      if (e.type == NoExpose)
//        break;
    }

    exit(0);
}
