#ifndef FDK_WINDOWS_HEADERS_H
#define FDK_WINDOWS_HEADERS_H

#ifdef FDK_OS_WIN

#pragma warning(push,0)

	#define _WINSOCK_H
	#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers

	//#include <tchar.h>
	//#include <strsafe.h>
	//#include <iostream>
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <mswsock.h>
	#include <Windows.h>

#pragma warning(pop)

#endif

#endif