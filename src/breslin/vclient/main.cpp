
//log
#include "../clientside/tdreamsock/dreamSockLog.h"

//app
#include "../clientside/application/applicationBreslin.h"


/******************** MAIN ***********************/
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
       
	StartLogConsole();
        
	ApplicationBreslin* applicationBreslin = new ApplicationBreslin(strCmdLine,30004);
#else
        ApplicationBreslin* applicationBreslin = new ApplicationBreslin(argv[1],30004);
#endif
        try
	{
		while (true)
		{
       	    		applicationBreslin->processUpdate();
		}
        }
		catch( Ogre::Exception& e )
		{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }
        return 0;
    }

#ifdef __cplusplus
}
#endif

