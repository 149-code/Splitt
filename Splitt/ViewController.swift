//
//  ViewController.swift
//  Splitt
//
//  Created by Adi Mehrotra on 11/10/20.
//

import Cocoa

class ViewController: NSViewController {
        @IBOutlet weak var quitButton: NSButton!
        
        override func viewDidLoad() {
                super.viewDidLoad()

                // Do any additional setup after loading the view.
        }

        override var representedObject: Any? {
                didSet {
                // Update the view, if already loaded.
                }
        }


        @IBAction func quitButtonPressed(_ sender: Any) {
                NSApplication.shared.terminate(self)
        }
}

