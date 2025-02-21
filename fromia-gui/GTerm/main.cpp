#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;

int main() {
    Display* display = XOpenDisplay(nullptr);
    if (!display) {
        fprintf(stderr, "Cannot open display!\n");
        exit(1);
    }

    int screen = DefaultScreen(display);
    Window root = RootWindow(display, screen);
    Window win = XCreateSimpleWindow(display, root, 100, 100, WIN_WIDTH, WIN_HEIGHT, 1,
                                     BlackPixel(display, screen), WhitePixel(display, screen));
    XSelectInput(display, win, ExposureMask | KeyPressMask);
    XMapWindow(display, win);

    GC gc = XCreateGC(display, win, 0, nullptr);
    XSetForeground(display, gc, BlackPixel(display, screen));

    char text[1024] = "Type keys: ";
    size_t textLen = strlen(text);

    bool running = true;
    while (running) {
        XEvent event;
        XNextEvent(display, &event);

        if (event.type == Expose) {
            // Draw the current text string
            XClearWindow(display, win);
            XDrawString(display, win, gc, 10, 50, text, textLen);
        }
        else if (event.type == KeyPress) {
            char buffer[32] = {0};
            KeySym keysym;
            int len = XLookupString(&event.xkey, buffer, sizeof(buffer) - 1, &keysym, nullptr);

            // Exit if Return (Enter) is pressed
            if (keysym == XK_Return) {
                running = false;
                continue;
            }

            // Append typed characters to the text (ignore non-printable keys)
            if (len > 0) {
                // Check for available space in the buffer.
                if (textLen + len < sizeof(text) - 1) {
                    strcat(text, buffer);
                    textLen += len;
                }
            }
            // Force a redraw
            XClearWindow(display, win);
            XDrawString(display, win, gc, 10, 50, text, textLen);
        }
    }

    XFreeGC(display, gc);
    XCloseDisplay(display);
    return 0;
}