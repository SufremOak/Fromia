#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_TEXT 1024

int main() {
    Display *dpy;
    Window win;
    int screen;
    GC gc;
    char text_buffer[MAX_TEXT] = "";
    int text_length = 0;
    
    dpy = XOpenDisplay(NULL);
    if (!dpy) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }
    screen = DefaultScreen(dpy);
    win = XCreateSimpleWindow(dpy, RootWindow(dpy, screen), 50, 50, WIDTH, HEIGHT, 1,
                              BlackPixel(dpy, screen), WhitePixel(dpy, screen));
    
    XSelectInput(dpy, win, ExposureMask | KeyPressMask);
    XMapWindow(dpy, win);
    
    gc = XCreateGC(dpy, win, 0, NULL);
    XSetForeground(dpy, gc, BlackPixel(dpy, screen));
    
    XEvent event;
    while (1) {
        XNextEvent(dpy, &event);
        
        if (event.type == Expose) {
            /* Redraw the text content */
            XClearWindow(dpy, win);
            XDrawString(dpy, win, gc, 10, 50, text_buffer, strlen(text_buffer));
        }
        
        if (event.type == KeyPress) {
            KeySym keysym = XLookupKeysym(&event.xkey, 0);
            if (keysym == XK_Escape)
                break;
            if (keysym == XK_BackSpace) {
                if (text_length > 0)
                    text_buffer[--text_length] = '\0';
            } else {
                char buf[32];
                int len = XLookupString(&event.xkey, buf, sizeof(buf) - 1, &keysym, NULL);
                if (len > 0 && (text_length + len) < MAX_TEXT) {
                    buf[len] = '\0';
                    strcat(text_buffer, buf);
                    text_length += len;
                }
            }
            /* Update display */
            XClearWindow(dpy, win);
            XDrawString(dpy, win, gc, 10, 50, text_buffer, strlen(text_buffer));
        }
    }
    
    XFreeGC(dpy, gc);
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
    return 0;
}