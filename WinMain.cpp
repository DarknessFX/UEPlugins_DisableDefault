///
/// Created by DarknessFX - https://dfx.lv - @DrkFX
/// Source Code at https://github.com/DarknessFX/UEPlugins_DisableDefault
///

#include <windows.h>
#include "AppForm.h"

using namespace UEPluginsDisableDefault;
[STAThreadAttribute]
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, INT nCmdShow)
{
    AppForm appForm;
    appForm.ShowDialog();
    return 0;
}
