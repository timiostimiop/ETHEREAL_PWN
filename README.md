# ETHEREAL_PWN

Simple ethereal hax.
Ethereal made heavy use of VMP's virtualization & mutation but in the end the developer failed to implement it properly.

Add minhook from nuget , Compile in Release x64 , Inject that dll & afterwards inject ethereal.dll.

The code is trash and could be improved alot but in the end I don't care - deal with it, it's a goddamn "bypass" ;-)


define DUMP_BYTES to print out first 20 bytes of NtProtectVirtualMemory and adjust it ( restoreVirtualProtect ).

On W11 you may need to edit VirtualProtect og bytes.
Unzip Ethereal.rar to C:\


![Alt text](/pic/NEGERSS.png?raw=true "Screenshotboi")


Installing Minhook via nuget:




![Alt text](/pic/PIC1.png?raw=true "Screenshotboi2")
![Alt text](/pic/pic2.png?raw=true "Screenshotboi3")
