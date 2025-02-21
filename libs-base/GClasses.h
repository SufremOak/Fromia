#ifndef GCLASSES_H
#define GCLASSES_H

#include "fromia.h"
#include <iostream>
#include <vector>

namespace Fromia {

    // Basic window structure
    struct GWindow {
        int width, height;
        const char* title;

        GWindow(const char* t, int w, int h) : title(t), width(w), height(h) {}
        void show() {
            std::cout << "Window: " << title << " (" << width << "x" << height << ")\n";
        }
    };

    // Basic button structure
    struct GButton {
        const char* label;
        void (*onClick)();

        GButton(const char* l, void (*cb)()) : label(l), onClick(cb) {}
        void press() {
            if (onClick) onClick();
        }
    };
}

#endif // GCLASSES_H
