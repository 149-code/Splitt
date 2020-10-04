#ifndef LISTENER_H
#define LISTENER_H

#include <stdio.h>
#include <stdbool.h>

#include <CoreGraphics/CoreGraphics.h>
#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h>

char keycode_to_char(CGKeyCode keycode);
int start_listener();

#endif
