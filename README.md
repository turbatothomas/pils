# Operating Systems
Windows 10, GNU/Linux
OS X never tried

# Linux Dependencies
- g++ version or newer than 8.0
- SDL2
- SDL2_image
You'll need the sdl development versions if you want to build the program.

# Windows Dependencies
- ninja (It can be installed with chocolatey package manager)
- meson (pip install meson) obviously you need python
- visual studio 2017 (maybe older version works)

# Build
You can run these commands:

meson build_directory
cd build_directory
ninja

# Install
when you are into the build directory run this:

ninja install

Then you will find all that you need in the release directory

# Run
Put some images into the girl directories, you can add how many girls you want

