#include "headers.h"
#include <initguid.h>
#include <KnownFolders.h>
#include <ShlObj.h>
//#define ENABLE_DEBUG_PRINTS

DWORD WINAPI initialize(LPVOID lpParam) {
	// if injected too early patterns will fail so we must wait to prevent failures
	while (!FindWindowA("grcWindow", NULL)) {
		Sleep(50);
	}

	// create console, if not enabled, does nothing
	createConsoleAndRedirectIo();
	
	logMsgColor(consoleBrightWhiteOnBlack,
		"____________________________________________________________\n"
		"                                                            \n"
		"             Welcome to Universal GTAO_Booster!             \n"
		"  Massive thanks to tostercx for the original GTAO_Booster  \n"
		"        Universal GTAO_Booster created by QuickNET          \n"
		"____________________________________________________________\n"
	);
	logMsg("Allocated console");
	
	uint64_t startTime = GetTickCount64();
	
	if(findSigs()) {
		logMsg("Finished finding pointers in %llums", GetTickCount64() - startTime);

		applyLegalAndLogoPatches();
		
		initHooks();

		logMsgColor(consoleBrightGreenOnBlack, "Load online when you're ready\nUniversal GTAO_Booster will unload and this window will disappear automatically, this is normal!");
	} else {
		logMsg("One or more errors occurred while finding pointers");
	}
	return 0;
}

BOOL WINAPI dllMain(HINSTANCE hinstDll, DWORD fdwReason, LPVOID lpvReversed) {
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, initialize, hinstDll, 0, NULL);
		break;
	case DLL_PROCESS_DETACH:
		MH_DisableHook((LPVOID)netCatalogueInsertUniquePtr);
		MH_Uninitialize();
		break;
	default:
		break;
	}

	return TRUE;
}
