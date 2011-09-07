mkdir lib
mkdir build
mkdir build\art
echo jmonkey
copy "C:\Program Files\jmonkeyplatform\jmonkeyplatform\libs" lib\
copy "C:\Program Files\jmonkeyplatform\jmonkeyplatform\libs" lib\
copy "C:\Program Files\jmonkeyplatform\jmonkeyplatform\libs" lib\
echo art
//xcopy art\*.* build\art /s
xcopy "C:\sandbox\jmonkeyengine-read-only\engine\src\test-data\Models\Sinbad\*.*" build\art /s 
