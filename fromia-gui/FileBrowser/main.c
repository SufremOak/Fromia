/*
 * Fromia File Browser - NexTStep-like file explorer using libX11
 *
 * To compile:
 *     gcc -o filebrowser main.c -lX11
 *
 * This simple file explorer lists files in the current directory. Use the UP and DOWN arrow keys
 * to move the selection.
 */

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX_FILES 1024
#define FILE_HEIGHT 20
#define PADDING 5

typedef struct {
    char **names;
    int count;
} FileList;

FileList get_file_list(const char *path) {
    FileList fl;
    fl.names = malloc(sizeof(char*) * MAX_FILES);
    fl.count = 0;

    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir");
        exit(1);
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL && fl.count < MAX_FILES) {
        // Skip current directory entries if desired.
        if (strcmp(entry->d_name, ".") == 0)
            continue;
        // Copy the file name.
        fl.names[fl.count] = strdup(entry->d_name);
        fl.count++;
    }
    closedir(dir);
    return fl;
}

void free_file_list(FileList fl) {
    for (int i = 0; i < fl.count; i++) {
        free(fl.names[i]);
    }
    free(fl.names);
}

int main() {
    Display *display;
    Window window;
    int screen;
    GC gc, gcHighlight;
    XEvent event;
    unsigned long white, black, highlight_bg;

    const int win_width = 400;
    const int win_height = 300;

    /* Open connection to X server */
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    screen = DefaultScreen(display);
    white = WhitePixel(display, screen);
    black = BlackPixel(display, screen);
    highlight_bg = 0x336699;  // A blue-like color for selection highlight

    /* Create window */
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 100, 100, win_width, win_height, 1, black, white);
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    /* Create graphics contexts */
    gc = XCreateGC(display, window, 0, 0);
    XSetForeground(display, gc, black);

    gcHighlight = XCreateGC(display, window, 0, 0);
    XSetForeground(display, gcHighlight, highlight_bg);

    /* Get file list from current directory */
    FileList fl = get_file_list(".");

    int selected = 0;
    if (fl.count == 0) {
        fprintf(stderr, "No files found in the directory.\n");
    }

    int scroll_offset = 0;
    int lines_per_page = (win_height - PADDING*2) / FILE_HEIGHT;

    while (1) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            /* Clear the window */
            XClearWindow(display, window);

            for (int i = 0; i < lines_per_page && (i + scroll_offset) < fl.count; i++) {
                int file_index = i + scroll_offset;
                int y = PADDING + (i + 1) * FILE_HEIGHT;

                /* Highlight the selected file */
                if (file_index == selected) {
                    XFillRectangle(display, window, gcHighlight, PADDING, y - FILE_HEIGHT + 5, win_width - PADDING*2, FILE_HEIGHT);
                    /* Draw text in white on highlight */
                    XSetForeground(display, gc, white);
                    XDrawString(display, window, gc, PADDING + 5, y - 5, fl.names[file_index], strlen(fl.names[file_index]));
                    XSetForeground(display, gc, black);
                } else {
                    XDrawString(display, window, gc, PADDING + 5, y - 5, fl.names[file_index], strlen(fl.names[file_index]));
                }
            }
        } else if (event.type == KeyPress) {
            KeySym key = XLookupKeysym(&event.xkey, 0);
            if (key == XK_Down) {
                if (selected < fl.count - 1) {
                    selected++;
                    if (selected >= scroll_offset + lines_per_page)
                        scroll_offset++;
                }
            } else if (key == XK_Up) {
                if (selected > 0) {
                    selected--;
                    if (selected < scroll_offset)
                        scroll_offset--;
                }
            } else if (key == XK_Escape) {
                break;
            }
            /* Redraw after key event */
            XClearWindow(display, window);
        }
    }

    /* Cleanup */
    free_file_list(fl);
    XFreeGC(display, gc);
    XFreeGC(display, gcHighlight);
    XCloseDisplay(display);
    return 0;
}