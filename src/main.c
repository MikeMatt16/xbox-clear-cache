#include <hal/debug.h>
#include <hal/fileio.h>
#include <hal/xbox.h>
#include <hal/video.h>
#include <windows.h>

int main(void)
{
    XVideoSetMode(640, 480, 32, REFRESH_DEFAULT);

    // TODO: Mount cache partitions and delete all the files?

    // Sleep and reboot
    debugPrint("Rebooting in 5 seconds...\n");
    Sleep(5000);
    XReboot();
}
