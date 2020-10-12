//
//  AppDelegate.swift
//  myApp
//
//  Created by Adi Mehrotra on 8/10/20.
//

import Cocoa

@NSApplicationMain
class AppDelegate: NSObject, NSApplicationDelegate {
        let statusItem = NSStatusBar.system.statusItem(withLength: NSStatusItem.variableLength)

        func applicationDidFinishLaunching(_ aNotification: Notification) {
                statusItem.button?.title = "✁"
                statusItem.button?.target = self
                statusItem.button?.action = #selector(showSettings)
                
                print("Test")
                start_splitt_deamon()
        }

        func applicationWillTerminate(_ aNotification: Notification) {
                stop_splitt_deamon();
                // Insert code here to tear down your application
        }

        @objc func showSettings() {
                let storyboard = NSStoryboard(name: "Main", bundle: nil)
                guard let vc = storyboard.instantiateController(withIdentifier: "ViewController") as?
                        ViewController else {
                        fatalError("Unable to find ViewController")
                }
                
                let popoverView = NSPopover()
                popoverView.contentViewController = vc
                popoverView.behavior = .transient
                popoverView.show(relativeTo: statusItem.button!.bounds,
                                 of: statusItem.button!, preferredEdge: .maxY)
        }
}
