#ifndef __BASE_STRING_H__
#define __BASE_STRING_H__
#ifdef _DEBUG
#define EXT_STR "_d.lib"
#else
#define EXT_STR ".lib"
#endif
#pragma comment(lib, "base_string" EXT_STR)
#include <limits.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
typedef struct _STRING {
	LPTSTR str;
	size_t capacity, size;
} STRING, *PSTRING;
PSTRING append(PSTRING, LPCTSTR, const UINT, UINT);
PSTRING assign(PSTRING, LPCTSTR, const UINT, UINT);
LPTSTR at(const PSTRING, const UINT);
TCHAR back(const PSTRING);
LPTSTR begin(const PSTRING);
size_t capacity(const PSTRING);
LPCTSTR cbegin(const PSTRING);
LPCTSTR cend(const PSTRING);
TCHAR cin(PSTRING, FILE *);
PSTRING clear(PSTRING);
int compare(const PSTRING, const PSTRING);
int constructor(PSTRING);
UINT copy(LPTSTR, PSTRING, const UINT, UINT);
size_t count(const PSTRING, const UINT, const UINT, const TCHAR);
LPCTSTR c_str(PSTRING);
LPCTSTR data(const PSTRING);
int destructor(PSTRING);
size_t distance(LPCTSTR, LPCTSTR);
BOOL empty(const PSTRING);
LPTSTR end(const PSTRING);
BOOL ends_with(const PSTRING, LPCTSTR);;
LPTSTR erase(PSTRING, const UINT, const UINT);
size_t find(const PSTRING, LPCTSTR, const UINT);
size_t find_first_not_of(const PSTRING, LPCTSTR, const UINT);
size_t find_first_of(const PSTRING, LPCTSTR, const UINT);
size_t find_last_not_of(const PSTRING, LPCTSTR, UINT);
size_t find_last_of(const PSTRING, LPCTSTR, UINT);
TCHAR front(const PSTRING);
TCHAR getline(PSTRING, FILE *);
BOOL iends_with(const PSTRING, LPCTSTR);
LPTSTR insert(PSTRING, UINT, LPCTSTR, const UINT, UINT);
BOOL istarts_with(const PSTRING, LPCTSTR);
size_t length(const PSTRING);
PSTRING pop_back(PSTRING);
PSTRING pop_front(PSTRING);
PSTRING push_back(PSTRING, const TCHAR);
PSTRING push_front(PSTRING, const TCHAR);
PSTRING replace(PSTRING, UINT, UINT, LPCTSTR, const UINT, UINT);
PSTRING replace_all(PSTRING, LPCTSTR, LPCTSTR);
PSTRING reserve(PSTRING, const size_t);
PSTRING resize(PSTRING, const size_t, const TCHAR);
PSTRING reverse(PSTRING, UINT, UINT);
size_t rfind(const PSTRING, LPCTSTR, UINT);
PSTRING shrink_to_fit(PSTRING, size_t);
size_t size(const PSTRING);
PSTRING sort(PSTRING, UINT, UINT);
BOOL starts_with(const PSTRING, LPCTSTR);
int stoi(PSTRING _Str);
PSTRING substr(PSTRING, const PSTRING, const UINT, UINT);
PSTRING swap(PSTRING, PSTRING);
PSTRING to_string(PSTRING, const int);
PSTRING trim(PSTRING);
PSTRING trim_left(PSTRING);
PSTRING trim_right(PSTRING);
#endif