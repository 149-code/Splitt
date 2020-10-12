# Splitt

This is the XCode App Branch
It's basiclly just the software in the master branch integrated in an XCode Agent Application

# Usage
Just double click to start the app
The app with check ~/.splitt_keybinds for all the user keybinds

If you get an "Insuuficient Permissions Error", navigate to System Prefences > Security & Privacy > Privacy and grant Splitt.app full Disk Acsess and Acessibility Privalegs

# Compiling
Note: XCode Developer Tools need to installed to build from source
    git clone https://github.com/149-code/Splitt
    cd Splitt
    git checkout xcode_app
    xcodebuild
