mkdir lib
mkdir build
mkdir build\art
echo jmonkey
copy ..\jme3\dist\jMonkeyEngine3.jar lib\
copy ..\jme3\lib\lwjgl\lwjgl.jar lib\
copy ..\jme3\lib\lwjgl\jME3-lwjgl-natives.jar lib\
echo art
xcopy art\*.* build\art /s

