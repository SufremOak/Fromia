#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/types.h>

int main() {
    Display *display = XOpenDisplay(nullptr);
    if (!display) {
        return EXIT_FAILURE;
    }

    int screen = DefaultScreen(display);
    Window root = RootWindow(display, screen);

    // Create the main window.
    Window win = XCreateSimpleWindow(display, root, 100, 100, 640, 480,
                                     2, BlackPixel(display, screen), WhitePixel(display, screen));
    XStoreName(display, win, "Fromia Application Opener");

    // Setup WM_DELETE_WINDOW.
    Atom WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, win, &WM_DELETE_WINDOW, 1);

    // Listen for events.
    XSelectInput(display, win, ExposureMask | ButtonPressMask | KeyPressMask);
    XMapWindow(display, win);

    // Create a graphics context.
    GC gc = XCreateGC(display, win, 0, nullptr);
    XSetForeground(display, gc, BlackPixel(display, screen));

    // Text input data.
    std::string binaryPath;
    bool textBoxActive = false;
    // Define text box and button geometry.
    const int textBoxX = 20, textBoxY = 90, textBoxW = 400, textBoxH = 30;
    const int buttonX = 430, buttonY = 90, buttonW = 80, buttonH = 30;

    bool running = true;
    while (running) {
        XEvent event;
        XNextEvent(display, &event);

        switch (event.type) {
            case Expose:
                if (event.xexpose.count == 0) {
                    // Clear and redraw main window.
                    XClearWindow(display, win);

                    // Draw a title and instructions.
                    const char* title = "Fromia - Application Opener";
                    XDrawString(display, win, gc, 20, 40, title, std::strlen(title));
                    const char* instruction = "Type binary path in the box and click [Open].";
                    XDrawString(display, win, gc, 20, 70, instruction, std::strlen(instruction));

                    // Draw the text box.
                    XDrawRectangle(display, win, gc, textBoxX, textBoxY, textBoxW, textBoxH);
                    // Draw the current text inside the text box.
                    XDrawString(display, win, gc, textBoxX + 5, textBoxY + textBoxH/2 + 5,
                                binaryPath.c_str(), binaryPath.size());

                    // Draw the "Open" button.
                    XDrawRectangle(display, win, gc, buttonX, buttonY, buttonW, buttonH);
                    const char* btnText = "Open";
                    XDrawString(display, win, gc, buttonX + 15, buttonY + buttonH/2 + 5,
                                btnText, std::strlen(btnText));
                }
                break;

            case ButtonPress: {
                int x = event.xbutton.x;
                int y = event.xbutton.y;
                // If click is in the text box area, activate text input.
                if (x >= textBoxX && x <= textBoxX + textBoxW &&
                    y >= textBoxY && y <= textBoxY + textBoxH) {
                    textBoxActive = true;
                }
                // If click is in the button area, try to launch the application.
                else if (x >= buttonX && x <= buttonX + buttonW &&
                         y >= buttonY && y <= buttonY + buttonH) {
                    if (!binaryPath.empty()) {
                        pid_t pid = fork();
                        if (pid == 0) {
                            // Child process: execute the binary.
                            execl(binaryPath.c_str(), binaryPath.c_str(), (char*)nullptr);
                            // If execl fails, exit child.
                            _exit(EXIT_FAILURE);
                        }
                        // Optionally you might wait for the child or handle errors.
                    }
                }
                else {
                    // Click outside text box: cancel text input.
                    textBoxActive = false;
                }
                break;
            }

            case KeyPress:
                if (textBoxActive) {
                    char buffer[128];
                    KeySym keysym;
                    int len = XLookupString(&event.xkey, buffer, sizeof(buffer) - 1, &keysym, nullptr);
                    if (keysym == XK_BackSpace) {
                        if (!binaryPath.empty()) {
                            binaryPath.pop_back();
                        }
                    } else if (keysym == XK_Return) {
                        // Do nothing on Enter; the button click handles execution.
                    } else if (len > 0) {
                        buffer[len] = '\0';
                        binaryPath += buffer;
                    }
                    // Refresh just the text box area.
                    XClearArea(display, win, textBoxX, textBoxY, textBoxW, textBoxH, True);
                } else {
                    // If not in text input mode, you can decide to exit.
                    running = false;
                }
                break;

            case ClientMessage:
                if (static_cast<Atom>(event.xclient.data.l[0]) == WM_DELETE_WINDOW) {
                    running = false;
                }
                break;

            default:
                break;
        }
    }

    XFreeGC(display, gc);
    XDestroyWindow(display, win);
    XCloseDisplay(display);
    return EXIT_SUCCESS;
}