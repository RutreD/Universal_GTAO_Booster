#include "../headers.h"

static char logBuf[0xFFF];

void logMsg(char const* fmt, ...) {
	ZeroMemory(logBuf, sizeof(logBuf));

	va_list valist;
	va_start(valist, fmt);
	vsprintf_s(logBuf, sizeof(logBuf), fmt, valist);
	va_end(valist);

	printf("%s\n", logBuf);
}

void logMsgColor(uint16_t color, char const* fmt, ...) {
	ZeroMemory(logBuf, sizeof(logBuf));

	va_list valist;
	va_start(valist, fmt);
	vsprintf_s(logBuf, sizeof(logBuf), fmt, valist);
	va_end(valist);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	printf("%s\n", logBuf);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), consoleWhiteOnBlack);
}

void createConsoleAndRedirectIo(void) {
	AllocConsole();

	EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

	SetConsoleTitleA("Grand Theft Auto V : Universal GTAO_Booster v1.0.3 by QuickNET / RTD edition");

	FILE* file = NULL;

	freopen_s(&file, "CONIN$", "r", stdin);
	freopen_s(&file, "CONOUT$", "w", stdout);
	freopen_s(&file, "CONOUT$", "w", stderr);
}