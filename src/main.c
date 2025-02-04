#include <hal/debug.h>
#include <hal/fileio.h>
#include <hal/xbox.h>
#include <hal/video.h>
#include <nxdk/mount.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#define GAME_CACHE_X "\\Device\\Harddisk0\\Partition3\\"
#define GAME_CACHE_Y "\\Device\\Harddisk0\\Partition4\\"
#define GAME_CACHE_Z "\\Device\\Harddisk0\\Partition5\\"


static void find_and_clear(char *dirname);
static void reboot_five_sec(void);

int main(void)
{
    BOOL ret;

    XVideoSetMode(640, 480, 32, REFRESH_DEFAULT);

    // Mount drives
    if (!(ret = nxMountDrive('X', GAME_CACHE_X)))
    {
        debugPrint("Failed to mount X cache partition.\n");
        debugPrint("nxMountDrive returned %d.\n", ret);
        reboot_five_sec();
    }

    if (!(ret = nxMountDrive('Y', GAME_CACHE_Y)))
    {
        debugPrint("Failed to mount Y cache partition.\n");
        debugPrint("nxMountDrive returned %d.\n", ret);
        reboot_five_sec();
    }

    if (!(ret = nxMountDrive('Z', GAME_CACHE_Z)))
    {
        debugPrint("Failed to mount Z cache partition.\n");
        debugPrint("nxMountDrive returned %d.\n", ret);
        reboot_five_sec();
    }

    // Clear cache directories (X, Y, and Z)
    find_and_clear("X:");
    find_and_clear("Y:");
    find_and_clear("Z:");

    // Unmount drives
    if (!(ret = nxUnmountDrive('X')))
    {
        debugPrint("Failed to unmount X cache partition.\n");
        debugPrint("nxUnmountDrive returned %d.\n", ret);
        reboot_five_sec();
    }

    if (!(ret = nxUnmountDrive('Y')))
    {
        debugPrint("Failed to unmount Y cache partition.\n");
        debugPrint("nxUnmountDrive returned %d.\n", ret);
        reboot_five_sec();
    }

    if (!(ret = nxUnmountDrive('Z')))
    {
        debugPrint("Failed to unmount Z cache partition.\n");
        debugPrint("nxUnmountDrive returned %d.\n", ret);
        reboot_five_sec();
    }

    // Complete
    debugPrint("Complete.\n");
    reboot_five_sec();
}

void reboot_five_sec(void)
{
    debugPrint("Rebooting in 5 seconds...\n");
    Sleep(5000);
    XReboot();
}

void find_and_clear(char *dirname)
{
    const char filename[MAX_PATH];
    const char directoryname[MAX_PATH];

    WIN32_FIND_DATA fileFd, dirFd;
    HANDLE hFileFind, hDirFind;

    if (dirname == NULL) return;

    sprintf(filename, "%s\\*", dirname);
    hFileFind = FindFirstFile(filename, &fileFd);
    if (hFileFind == INVALID_HANDLE_VALUE)
    {
        debugPrint("No files found for \'%s\'.\n", filename);
        return;
    }

    do
    {
        ZeroMemory(filename, MAX_PATH);
        ZeroMemory(directoryname, MAX_PATH);
        sprintf(filename, "%s\\%s", dirname, fileFd.cFileName);
        sprintf(directoryname, "%s\\*", filename, fileFd.cFileName);

        if ((fileFd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            hDirFind = FindFirstFile(directoryname, &dirFd);
            if (hDirFind != INVALID_HANDLE_VALUE)
            {
                FindClose(hDirFind);
                find_and_clear(filename);
            }

            if (RemoveDirectory(filename))
                debugPrint("Removed directory \'%s\'.\n", filename);
            else debugPrint("Unable to remove directory \'%s\'. (0x%lx)\n", filename, HRESULT_FROM_WIN32(GetLastError()));
        }
        else
        {
            if (DeleteFile(filename))
                debugPrint("Deleted file \'%s\'.\n", filename);
            else debugPrint("Unable to delete file \'%s\'. (0x%lx)\n", filename, HRESULT_FROM_WIN32(GetLastError()));
        }
    }
    while (FindNextFile(hFileFind, &fileFd) != 0);

    FindClose(hFileFind);
}
