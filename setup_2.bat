mkdir lib
mkdir build
mkdir build\art
echo jmonkey
copy "C:\Program Files\jmonkeyplatform\jmonkeyplatform\libs\jMonkeyEngine3.jar" lib\
copy "C:\Program Files\jmonkeyplatform\jmonkeyplatform\libs\lwjgl.jar" lib\
copy "C:\Program Files\jmonkeyplatform\jmonkeyplatform\libs\jME3-lwjgl-natives.jar" lib\

echo art
echo copy_sinbad_files
xcopy "C:\sandbox\jmonkeyengine-read-only\engine\src\test-data\Models\Sinbad\*.*" build\art\models\sinbad /s 
