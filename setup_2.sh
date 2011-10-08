mkdir lib
mkdir build
cd build
mkdir art
cd art
mkdir models
cd models
mkdir sinbad
cd ../../../

cp ../../jmonkeyplatform/jmonkeyplatform/libs/jMonkeyEngine3.jar lib
cp ../../jmonkeyplatform/jmonkeyplatform/libs/lwjgl.jar lib
cp ../../jmonkeyplatform/jmonkeyplatform/libs/jME3-lwjgl-natives.jar lib

cp ../jmonkeyengine-read-only/engine/src/test-data/Models/Sinbad/*.* build/art/models/sinbad
