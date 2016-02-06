#include <d3dapp.h>

#include "BoxDemo.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
    PSTR cmdLine, int showCmd)
{
    // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    BoxApp theApp(hInstance);

    if(!theApp.Init())
    {
        return EXIT_FAILURE;
    }

    return theApp.Run();
}
