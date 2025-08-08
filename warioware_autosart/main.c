// UNTESTED - Probably works tho.

#ifdef _WIN32
#include <windows/windows.h>
#include <windows/stdio.h>
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

