#pragma once

#ifdef SP_PLATFORM_WIN
	#ifdef SP_EXPORT_DLL
		#define SP_API __declspec(dllexport)
	#else 
		#define SP_API __declspec(dllimport)
	#endif
#elif SP_PLATFORM_DARWIN
	#ifdef SP_EXPORT_DLL
		#define SP_API __declspec(dllexport)
	#else 
		#define SP_API __declspec(dllimport)
	#endif
#endif // SP_PLATFORM_DARWIN
