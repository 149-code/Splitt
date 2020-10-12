//
//  alert.swift
//  Splitt
//
//  Created by Adi Mehrotra on 12/10/20.
//

import Foundation
import AppKit

@_cdecl("alert_permission_error")
func alert_permission_error() {
        let alert = NSAlert()
        alert.messageText = """
                ERROR: Inccorect Permissions
                Please give Splitt full disk access and acessibility permisions
                System Preferences > Security & Privacy > Privacy
                """
        alert.addButton(withTitle: "OK")
        alert.runModal()
}
