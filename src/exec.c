#include "exec.h"

int get_frontmost_application()
{
	CFArrayRef window_list = CGWindowListCopyWindowInfo(
		kCGWindowListExcludeDesktopElements | kCGWindowListOptionOnScreenOnly, 
		kCGNullWindowID);

	int num_windows = CFArrayGetCount(window_list);

	for (int i = 0; i < num_windows; i++) {
		CFDictionaryRef dict = CFArrayGetValueAtIndex(window_list, i);
		CFNumberRef objc_window_layer = CFDictionaryGetValue(dict, kCGWindowLayer);

		int window_layer;
		CFNumberGetValue(objc_window_layer, kCFNumberIntType, &window_layer);

		if (window_layer == 0) {
			CFNumberRef objc_window_pid = CFDictionaryGetValue(dict, kCGWindowOwnerPID);

			int window_pid = 0;
			CFNumberGetValue(objc_window_pid, kCFNumberIntType, &window_pid);

			return window_pid;
		}
	}

	return -1;
}

void resize_current_window(int x, int y, int dx, int dy)
{
	int pid = get_frontmost_application();
	if (pid == -1)
		return;

	AXUIElementRef app = AXUIElementCreateApplication(pid);
	AXUIElementRef win;

	AXUIElementCopyAttributeValue(app, kAXMainWindowAttribute, (CFTypeRef*) &win);

	CGPoint point = {x, y};
	CGSize size = {dx, dy};

	CFTypeRef objc_point = (CFTypeRef) (AXValueCreate(kAXValueCGPointType, (void *) &point));
	CFTypeRef objc_size = (CFTypeRef) (AXValueCreate(kAXValueCGSizeType, (void*) &size));

	AXUIElementSetAttributeValue(win, kAXPositionAttribute, objc_point);
	AXUIElementSetAttributeValue(win, kAXSizeAttribute, objc_size);
}

struct screen_size get_window_size()
{
	int pid = get_frontmost_application();
	if (pid == -1)
		return (struct screen_size) {0, 0, 0, 0,};

	AXUIElementRef app = AXUIElementCreateApplication(pid);
	AXUIElementRef win;

	AXError error = AXUIElementCopyAttributeValue(app, kAXMainWindowAttribute, (CFTypeRef*) &win);

	CGPoint point;
	CFTypeRef objc_point;

	CGSize size;
	CFTypeRef objc_size;

	AXUIElementCopyAttributeValue(win, kAXPositionAttribute, &objc_point);
	AXValueGetValue(objc_point, kAXValueCGPointType, &point);

	AXUIElementCopyAttributeValue(win, kAXSizeAttribute, &objc_size);
	AXValueGetValue(objc_size, kAXValueCGSizeType, &size);

	struct screen_size ret = {
		.x = point.x,
		.y = point.y,
		.dx = size.width,
		.dy = size.height,
	};

	return ret;
}

struct screen_sizes get_desktop_sizes()
{
	CGDirectDisplayID display_buffer[9];
	unsigned int num_displays;

	CGGetActiveDisplayList(9, display_buffer, &num_displays);

	struct screen_sizes ret = {
		.len = num_displays,
		.arr = malloc(sizeof(struct screen_size) * num_displays),
	};

	for (int i = 0; i < num_displays; i++) {
		CGRect display_bounds = CGDisplayBounds(display_buffer[i]);
		ret.arr[i] = (struct screen_size) {
			.x = display_bounds.origin.x,
			.y = display_bounds.origin.y,
			.dx = display_bounds.size.width,
			.dy = display_bounds.size.height,
		};
	}

	return ret;
}
