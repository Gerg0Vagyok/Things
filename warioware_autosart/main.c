// UNTESTED - Probably works tho.
// For Windows:
//   x86_64-w64-mingw32-gcc -static main.c -o warioware.exe
// For Linux:
//   gcc -static main.c -o warioware
// I dont own a Mac nor have skd for Mac compiling so RIP Mac users.
// It also has everything in it so using it is a piece of cake, no dependencies i think.

#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#else
#include <stdlib.h>
#include <stdio.h>
#endif

#define PAGE "https://en.wikipedia.org/wiki/Wario"

int main() {
	#ifdef _WIN32
		HKEY hKey;

		const char *valueName = "WarioWare";
		const char *command = "cmd /c start " PAGE;
		if (RegOpenKeyExA(	HKEY_LOCAL_MACHINE,
							"Software\\Microsoft\\Windows\\CurrentVersion\\Run",
							0, KEY_WRITE, &hKey) != ERROR_SUCCESS) {
			printf("Failed to open registry key\n");
			return 1;
		}

		if (RegSetValueExA(	hKey, valueName, 0, REG_SZ, (const BYTE*)command,
							(DWORD)(strlen(command) + 1)) != ERROR_SUCCESS) {
			printf("Failed to set registry value\n");
			RegCloseKey(hKey);
			return 1;
		}

		RegCloseKey(hKey);
	#else
		FILE *file = fopen("/etc/xdg/autostart/warioware.desktop", "w");
		if (!file) {
			perror("GuessNot\n");
		} else {
			fprintf(file, "[Desktop Entry]\nType=Application\nExec=xdg-open " PAGE "\nHidden=false\nNoDisplay=false\nX-GNOME-Autostart-enabled=true\nName=WarioWare");
		}
		system("xdg-open " PAGE);
	#endif
	return 0;
}

