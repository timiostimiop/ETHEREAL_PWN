

#include "pch.h"

#include <iostream>
#include <string>

#include <MinHook.h>

typedef bool (WINAPI* pAllocConsole)(void);
pAllocConsole oAllocConsole = NULL;


DWORD64 hMod = NULL;
bool cancontinue = false;

void pMemcpy(void* dest, void* src, size_t size)
{
    DWORD oProtect = NULL;
    VirtualProtect(dest, size, PAGE_EXECUTE_READWRITE, &oProtect);
    memcpy(dest, src, size);
    VirtualProtect(dest, size, oProtect, NULL);
}

bool canpatch = false;
bool WINAPI hkAllocConsole()
{
    canpatch = true;
    

    printf("Removing hooks...\n");
    HMODULE ntDll = GetModuleHandleA("ntdll.dll");
    if (ntDll != 0)
    {
        auto vpAddy = (DWORD64)GetProcAddress(ntDll, "NtProtectVirtualMemory");

        BYTE restoreVirtualProtect[] =
        {
        0x4C, 0x8B, 0xD1, 0xB8, 0x50, 0x00, 0x00, 0x00, 0xF6, 0x04, 0x25, 0x08, 0x03, 0xFE, 0x7F, 0x01,
        0x75, 0x03, 0x0F, 0x05 
        };


        if (WriteProcessMemory(GetCurrentProcess(), (LPVOID)vpAddy, &restoreVirtualProtect, sizeof(restoreVirtualProtect), NULL))
            printf("Hooks restored.\n");
        else printf("failed to restore hooks\n");

    }
    else printf("failed to get ntdll\n");


   return oAllocConsole();

}


DWORD WINAPI px()
{
    
    if (MH_Initialize() != MH_OK) { printf(("failed to init mh\n")); return false; }


    
  
   // 45B80
    DWORD64 mod{ 0 };
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

  
    printf("waiting for ethereal...\n");
    HMODULE kernelnigga = GetModuleHandleA("kernelbase.dll");

     auto neger_loch = (DWORD64)GetProcAddress(kernelnigga, "AllocConsole");
     if (neger_loch)
     {
         MH_CreateHook((DWORD_PTR*)neger_loch, &hkAllocConsole, reinterpret_cast<void**>(&oAllocConsole));
         MH_EnableHook(MH_ALL_HOOKS);
     }
  
     DWORD64 addr1 = NULL;

     while (addr1 == 0)
     {
         addr1 = (DWORD64)GetModuleHandleA("ethereal.dll");
         hMod = (DWORD64)GetModuleHandleA("ethereal.dll") ;
         Sleep(1);
     }

     printf("waiting for continue bool...\n");

     while (!canpatch)
     {
         Sleep(1);
     }

     printf("patching...\n");
     if (addr1)
     {
         BYTE patch1[5] = { 0xB0, 0x01, 0xC3, 0x90, 0x90 };

         DWORD64 Patch1 = (DWORD64)hMod + 0x4A980;
         HMODULE ntDll = GetModuleHandleA("ntdll.dll");
         auto memcpyAddy = (DWORD64)GetProcAddress(ntDll, "RtlCopyMemory");

         BYTE p[1];
         ReadProcessMemory(GetCurrentProcess(), (LPVOID)memcpyAddy, &p[1], sizeof(p), NULL);
         if (p[1] == 0x48)
         {

             DWORD oProtect = NULL;

            pMemcpy((void*)Patch1, patch1, sizeof(patch1));
         
             Sleep(5000); 
             printf("patched. greetz - \ntimiostimio#0629\n"); // go change this to paste ur own p100 crack :)
         
         }
       
     }

    return TRUE;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&px, 0, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

