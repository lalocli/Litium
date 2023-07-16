cl /c /O2 /MT litium/addresses.c litium/hooks.c litium/litium.c subhook/subhook.c -DSUBHOOK_STATIC
cl /c /std:c++20 /MT litium/api/*.cpp
link /DLL /SUBSYSTEM:WINDOWS /DEBUG:NONE /OUT:litium.dll *.obj Kernel32.lib User32.lib
@del *.obj

cl /MT launcher/main.c /link /OUT:LitiumLauncher.exe /SUBSYSTEM:WINDOWS Kernel32.lib User32.lib
@del *.obj
