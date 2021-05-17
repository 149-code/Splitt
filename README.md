# Splitt

MAC OS Window Manager'

Discalmer: Only works for MacOS
Just a project I made for productivity, lets you reposition windows across multiple screens with keyboard shortcuts

# Usage
For the fully fledged MacOS app check out the xcode_app branch

Trigger-key \[Screen Number\] Keybind-Letter

The trigger key is Cntl-S
The screen number is just the screen you want to send the window to (If no number is given, the window is moved to the screens it currently on)
The Keybind letter is just a letter that you delcare in the keybinds file which represents a window position (see below for more info)

This programm uses a keybinds file to declare custom keybinds, its located in the data folder
The format is "key": x1,y1,x2,y2, where key is the key you hit after Cntl-S and the numbers (x1, x2, y1, y2) are the positions of the windows scaled between 0 to 1.
i.e. is (x1, y1) = (0.5, 0) - This means the top corner of the window is halfway across the window horizontally and at the top vartically

You can also swap your cursor between different windows by binding a letter to cursor (i.e.) "c": cursor. If a window number is given, this will move your cursor to that window
otherwise, it will just move your cursor to the next window.

# Compiling
    git clone https://github.com/149-code/Splitt
    cd Splitt
    make
    
    ./main

# Contributing

Bug reports are always helpful, and if you have feature ideas just file a issue on github and I'll look over it.
