#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
    // Create the main window
    NSWindow *window = [[NSWindow alloc] initWithContentRect:NSMakeRect(100, 100, 400, 200)
                                                 styleMask:(NSWindowStyleMaskTitled |
                                                             NSWindowStyleMaskClosable |
                                                             NSWindowStyleMaskResizable)
                                                   backing:NSBackingStoreBuffered
                                                     defer:NO];
    [window setTitle:@"GNUstep GUI App"];
    [window makeKeyAndOrderFront:nil];

    // Create a button
    NSButton *button = [[NSButton alloc] initWithFrame:NSMakeRect(150, 50, 100, 40)];
    [button setTitle:@"Click Me"];
    [button setTarget:self];
    [button setAction:@selector(buttonClicked:)];
    [[window contentView] addSubview:button];
}

- (void)buttonClicked:(id)sender {
    NSLog(@"Hello, World!");
}

@end

int main(int argc, const char *argv[]) {
    @autoreleasepool {
        // Create an instance of the application
        NSApplication *app = [NSApplication sharedApplication];

        // Set the app delegate
        AppDelegate *delegate = [[AppDelegate alloc] init];
        [app setDelegate:delegate];

        // Start the application
        [app run];
    }
    return 0;
}
