#pragma once

#ifndef CODE_REVIEW_APPLICATION_EXPORT
#    pragma comment(lib, "Application.lib")
#    define CODE_REVIEW_APPLICATION_API __declspec(dllimport)
#else 
#    define CODE_REVIEW_APPLICATION_API __declspec(dllexport)
#endif 
