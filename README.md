# Arkanoid
Old game callled Arkanoid. Everyone knows arkanoid. (Perhaps)

That's remake of arkanoid made in SDL2. Made with C++ language. 


## How to setup? ( Windows 10; Visual Studio 2019 )
1. Donwload VS 2019 and install extra tool in setup: Programming classic apps in language C++
2. Clone repository
3. Open `arkanoid.vcxproj` file in VS 2019
4. Unpack `sdl_libs` with ready package of dlls.
5. Go to VS 2019 and open "arkanoid Debug Properties" on green button to debug project.
6. Set Configuration to: All Configurations and Platform to: All Platforms.
7. Open tab **C/C++** and edit field `Additional Include Directories`. Change or add paths to your every "include" folder from `C++ Libs`. For example: `C:\Users\Abnormal\Documents\C++ Libs\SDL2_mixer-devel-2.6.1-VC\include`
8. Then open tab **Linker** and edit same field, add same librares like in 7.
9. Click apply and run Local debugger. Everything should work now.
