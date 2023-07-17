cl /c /MT subhook/subhook.c -DSUBHOOK_STATIC
cl /c /Ob1 /std:c++20 /EHsc /MT litium/api/*.cpp -DSUBHOOK_STATIC
cl /c /O2 /MT litium/addresses.c litium/hooks.c litium/patches.c litium/litium.c -DSUBHOOK_STATIC
link /DLL /SUBSYSTEM:WINDOWS /DEBUG:NONE /OUT:litium.dll *.obj Kernel32.lib User32.lib
@del *.obj

cl /MT launcher/main.c /link /OUT:LitiumLauncher.exe /SUBSYSTEM:WINDOWS Kernel32.lib User32.lib
@del *.obj
