#pragma once

#ifndef CODE_REVIEW_CORE_EXPORT
#    pragma comment(lib, "Core.lib")
#    define CODE_REVIEW_CORE_API __declspec(dllimport)
#else 
#    define CODE_REVIEW_CORE_API __declspec(dllexport)
#endif 
