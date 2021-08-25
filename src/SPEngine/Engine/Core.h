#pragma once

#ifdef DLL_EXPORT
#	define SP_API __declspec(dllexport)
#else
#	define SP_API __declspec(dllimport)
#endif