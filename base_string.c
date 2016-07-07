#include "base_string.h"
PSTRING append(PSTRING _Dest, LPCTSTR _Source, const UINT _SrcPos, UINT _SrcCnt) {
	TCHAR _C;
	UINT i;
	if (_SrcPos >= _tcslen(_Source) || _SrcCnt <= 0) {
		return _Dest;
	}
	if (_SrcPos + _SrcCnt > _tcslen(_Source)) {
		_SrcCnt = _tcslen(_Source) - _SrcPos;
	}
	for (i = 0; i < _SrcCnt; ++i) {
		_C = _Source[_SrcPos + i];
		push_back(_Dest, _C);
	}
	return _Dest;
}
PSTRING assign(PSTRING _Dest, LPCTSTR _Source, const UINT _SrcPos, UINT _SrcCnt) {
	TCHAR _C;
	if (_SrcPos >= _tcslen(_Source) || _SrcCnt <= 0) {
		return _Dest;
	}
	_Dest->size = 0;
	if (_SrcPos + _SrcCnt > _tcslen(_Source)) {
		_SrcCnt = _tcslen(_Source) - _SrcPos;
	}
	while (size(_Dest) < _SrcCnt) {
		_C = _Source[_SrcPos + size(_Dest)];
		push_back(_Dest, _C);
	}
	return _Dest;
}
LPTSTR at(const PSTRING _Str, const UINT _Index) {
	return &_Str->str[_Index];
}
TCHAR back(const PSTRING _Str) {
	return *at(_Str, size(_Str) - 1);
}
LPTSTR begin(const PSTRING _Str) {
	return _Str->str;
}
size_t capacity(const PSTRING _Str) {
	return _Str->capacity;
}
LPCTSTR cbegin(const PSTRING _Str) {
	return _Str->str;
}
LPCTSTR cend(const PSTRING _Str) {
	return begin(_Str) + size(_Str);
}
TCHAR cin(PSTRING _Str, FILE *_File) {
	TCHAR _C;
	clear(_Str);
	while (1) {
		_C = _gettc(_File);
		if (_C == EOF || _C == TEXT('\0') || _C == TEXT('\t') || _C == TEXT('\n') || _C == TEXT(' ')) {
			break;
		}
		push_back(_Str, _C);
	}
	return _C;
}
PSTRING clear(PSTRING _Str) {
	resize(_Str, 0, TEXT('\0'));
	return _Str;
}
int compare(const PSTRING _Str1, const PSTRING _Str2) {
	return _tcscmp(_Str1->str, _Str2->str);
}
int constructor(PSTRING _Str) {
	UINT i;
	_Str->str = (LPTSTR)malloc(sizeof(TCHAR) * 2);
	if (_Str->str == NULL) {
		return EXIT_FAILURE;
	}
	_Str->capacity = 2;
	clear(_Str);
	for (i = 0; i < 2; ++i) {
		*at(_Str, i) = TEXT('\0');
	}
	return EXIT_SUCCESS;
}
UINT copy(LPTSTR _Dest, PSTRING _Source, const UINT _SrcPos, UINT _SrcCnt) {
	UINT i;
	if (_SrcPos >= size(_Source) || _SrcCnt <= 0) {
		return 0;
	}
	if (_SrcPos + _SrcCnt > size(_Source)) {
		_SrcCnt = size(_Source) - _SrcPos;
	}
	for (i = 0; i < _SrcCnt; ++i) {
		_Dest[i] = *at(_Source, _SrcPos + i);
	}
	return _SrcCnt;
}
size_t count(const PSTRING _Str, const UINT _First, const UINT _Last, const TCHAR _C) {
	TCHAR str[2] = TEXT("");
	size_t retval = 0;
	int pos = _Last;
	if (_First > size(_Str) || _First > _Last) {
		return 0;
	}
	if (_Last > size(_Str)) {
		pos = size(_Str);
	}
	str[0] = _C;
	while (1) {
		size_t index;
		if ((index = find_last_of(_Str, str, _First - 1 + pos)) == UINT_MAX) {
			break;
		}
		pos = index - 1;
		if (pos >= 0) {
			++retval;
		}
		else {
			break;
		}
	}
	return retval;
}
LPCTSTR c_str(PSTRING _Str) {
	if (*at(_Str, size(_Str) < capacity(_Str) ? size(_Str) : size(_Str) - 1) != TEXT('\0')) {
		push_back(_Str, TEXT('\0'));
		--_Str->size;
	}
	return _Str->str;
}
LPCTSTR data(const PSTRING _Str) {
	return _Str->str;
}
int destructor(PSTRING _Str) {
	clear(_Str);
	_Str->capacity = 0;
	free(_Str->str);
	return EXIT_SUCCESS;
}
size_t distance(LPCTSTR _First, LPCTSTR _Last) {
	return (_Last - _First) / sizeof(TCHAR);
}
BOOL empty(const PSTRING _Str) {
	return size(_Str) > 0 ? TRUE : FALSE;
}
LPTSTR end(const PSTRING _Str) {
	return begin(_Str) + size(_Str);
}
BOOL ends_with(const PSTRING _Str, LPCTSTR _SubStr) {
	size_t i;
	for (i = 0; i < _tcslen(_SubStr); ++i) {
		if (*at(_Str, size(_Str) - _tcslen(_SubStr) + i) != _SubStr[i]) {
			return FALSE;
		}
	}
	return TRUE;
}
LPTSTR erase(PSTRING _Str, const UINT _First, const UINT _Last) {
	int pos = _Last;
	if (_First > size(_Str) || _First > _Last) {
		return NULL;
	}
	if (_Last > size(_Str)) {
		pos = size(_Str);
	}
	do {
		UINT i;
		for (i = _First; i < size(_Str) - 1; ++i) {
			*at(_Str, i) = *at(_Str, i + 1);
		}
		--_Str->size;
	} while ((int)_First < --pos);
	return at(_Str, pos + 1);
}
size_t find(const PSTRING _Str, LPCTSTR _SubStr, const UINT _Pos) {
	size_t i;
	for (i = _Pos; i <= size(_Str) - _tcslen(_SubStr); ++i) {
		UINT j = 0;
		while (*at(_Str, i + j) == _SubStr[j]) {
			if (_SubStr[j++] == TEXT('\0')) {
				break;
			}
		}
		if (j >= _tcslen(_SubStr)) {
			return i;
		}
	}
	return UINT_MAX;
}
size_t find_first_not_of(const PSTRING _Str, LPCTSTR _SubStr, const UINT _Pos) {
	size_t i;
	for (i = _Pos; i <= size(_Str) - _tcslen(_SubStr); ++i) {
		UINT j = 0;
		while (_SubStr[j] != TEXT('\0')) {
			if (*at(_Str, i) != _SubStr[j++]) {
				return i;
			}
		}
	}
	return UINT_MAX;
}
size_t find_first_of(const PSTRING _Str, LPCTSTR _SubStr, const UINT _Pos) {
	size_t i;
	for (i = _Pos; i <= size(_Str) - _tcslen(_SubStr); ++i) {
		UINT j = 0;
		while (_SubStr[j] != TEXT('\0')) {
			if (*at(_Str, i) == _SubStr[j++]) {
				return i;
			}
		}
	}
	return UINT_MAX;
}
size_t find_last_not_of(const PSTRING _Str, LPCTSTR _SubStr, UINT _Pos) {
	size_t i;
	if (_Pos >= size(_Str)) {
		_Pos = size(_Str) - _tcslen(_SubStr);
	}
	for (i = _Pos; i >= 0; --i) {
		UINT j = 0;
		while (_SubStr[j] != TEXT('\0')) {
			if (*at(_Str, i) != _SubStr[j++]) {
				return i;
			}
		}
	}
	return UINT_MAX;
}
size_t find_last_of(const PSTRING _Str, LPCTSTR _SubStr, UINT _Pos) {
	size_t i;
	if (_Pos >= size(_Str)) {
		_Pos = size(_Str) - _tcslen(_SubStr);
	}
	for (i = _Pos; i >= 0; --i) {
		UINT j = 0;
		while (_SubStr[j] != TEXT('\0')) {
			if (*at(_Str, i) == _SubStr[j++]) {
				return i;
			}
		}
	}
	return UINT_MAX;
}
TCHAR front(const PSTRING _Str) {
	return *at(_Str, 0);
}
TCHAR getline(PSTRING _Str, FILE *_File) {
	TCHAR _C;
	clear(_Str);
	while (1) {
		_C = _gettc(_File);
		if (_C == EOF || _C == TEXT('\0') || _C == TEXT('\n')) {
			break;
		}
		push_back(_Str, _C);
	}
	return _C;
}
BOOL iends_with(const PSTRING _Str, LPCTSTR _SubStr) {
	size_t i;
	for (i = 0; i < _tcslen(_SubStr); ++i) {
		if (_totupper(*at(_Str, size(_Str) - _tcslen(_SubStr) + i)) != _totupper(_SubStr[i])) {
			return FALSE;
		}
	}
	return TRUE;
}
LPTSTR insert(PSTRING _Dest, UINT _DstPos, LPCTSTR _Source, const UINT _SrcPos, UINT _SrcCnt) {
	if (_SrcPos >= size(_Dest) || _SrcCnt <= 0) {
		return at(_Dest, size(_Dest) - 1);
	}
	if (_DstPos >= size(_Dest)) {
		_DstPos = size(_Dest) - 1;
	}
	if (_SrcPos + _SrcCnt > _tcslen(_Source)) {
		_SrcCnt = _tcslen(_Source) - _SrcPos;
	}
	while (_SrcCnt > 0) {
		UINT i;
		push_back(_Dest, *at(_Dest, size(_Dest) - 1));
		for (i = size(_Dest) - 2; i > _DstPos; --i) {
			*at(_Dest, i) = *at(_Dest, i - 1);
		}
		*at(_Dest, _DstPos) = _Source[_SrcPos + _SrcCnt - 1];
		--_SrcCnt;
	}
	return at(_Dest, _DstPos);
}
BOOL istarts_with(const PSTRING _Str, LPCTSTR _SubStr) {
	size_t i;
	for (i = 0; i < _tcslen(_SubStr); ++i) {
		if (_totupper(*at(_Str, size(_Str) + i)) != _totupper(_SubStr[i])) {
			return FALSE;
		}
	}
	return TRUE;
}
size_t length(const PSTRING _Str) {
	return size(_Str);
}
PSTRING pop_back(PSTRING _Str) {
	_Str->size -= size(_Str) > 0 ? 1 : 0;
	return _Str;
}
PSTRING pop_front(PSTRING _Str) {
	erase(_Str, 0, 0);
	return _Str;
}
PSTRING push_back(PSTRING _Str, const TCHAR _C) {
	if (size(_Str) >= capacity(_Str)) {
		reserve(_Str, capacity(_Str) * 2);
	}
	*at(_Str, size(_Str)) = _C;
	++_Str->size;
	return _Str;
}
PSTRING push_front(PSTRING _Str, const TCHAR _C) {
	TCHAR str[2] = TEXT("");
	str[0] = _C;
	insert(_Str, 0, str, 0, _tcslen(str));
	return _Str;
}
PSTRING replace(PSTRING _Dest, UINT _DstPos, UINT _DstCnt, LPCTSTR _Source, const UINT _SrcPos, UINT _SrcCnt) {
	if (_SrcPos >= size(_Dest) || _SrcCnt <= 0) {
		return _Dest;
	}
	if (_DstPos >= size(_Dest)) {
		_DstPos = size(_Dest) - 1;
	}
	if (_DstPos + _DstCnt >= size(_Dest)) {
		_DstCnt = size(_Dest) - _DstPos;
	}
	if (_SrcPos + _SrcCnt > _tcslen(_Source)) {
		_SrcCnt = _tcslen(_Source) - _SrcPos;
	}
	erase(_Dest, _DstPos, _DstCnt + 1);
	insert(_Dest, _DstPos, _Source, _SrcPos, _SrcCnt);
	return _Dest;
}
PSTRING replace_all(PSTRING _Dest, LPCTSTR _SubStr, LPCTSTR _Source) {
	size_t i;
	while ((i = find(_Dest, _SubStr, 0)) < UINT_MAX) {
		replace(_Dest, i, _tcslen(_SubStr), _Source, 0, _tcslen(_Source));
	}
	return _Dest;
}
PSTRING reserve(PSTRING _Str, const size_t _Size) {
	if (_Size > capacity(_Str)) {
		LPTSTR temp;
		UINT i;
		temp = (LPTSTR)realloc(_Str->str, sizeof(TCHAR) * _Size);
		if (temp == NULL) {
			return NULL;
		}
		_Str->str = temp;
		_Str->capacity = _Size;
		for (i = size(_Str); i < _Size; ++i) {
			*at(_Str, i) = TEXT('\0');
		}
	}
	return _Str;
}
PSTRING resize(PSTRING _Str, const size_t _Size, const TCHAR _C) {
	UINT i;
	if (_Size > capacity(_Str)) {
		reserve(_Str, _Size);
	}
	for (i = size(_Str); i < _Size; ++i) {
		*at(_Str, i) = _C;
	}
	_Str->size = _Size;
	return _Str;
}
PSTRING reverse(PSTRING _Dest, UINT _DstPos, UINT _DstCnt) {
	STRING _Str;
	UINT i;
	if (_DstPos >= size(_Dest)) {
		_DstPos = size(_Dest) - 1;
	}
	if (_DstPos + _DstCnt >= size(_Dest)) {
		_DstCnt = size(_Dest) - _DstPos;
	}
	constructor(&_Str);
	assign(&_Str, c_str(_Dest), 0, size(_Dest));
	for (i = _DstPos; i < _DstCnt; ++i) {
		*at(_Dest, i) = *at(&_Str, _DstCnt - 1 - i);
	}
	destructor(&_Str);
	return _Dest;
}
size_t rfind(const PSTRING _Str, LPCTSTR _SubStr, UINT _Pos) {
	size_t i;
	if (_Pos >= size(_Str)) {
		_Pos = size(_Str) - _tcslen(_SubStr);
	}
	for (i = _Pos; i >= 0; --i) {
		UINT j = 0;
		while (*at(_Str, i + j) == _SubStr[j]) {
			if (_SubStr[j++] == TEXT('\0')) {
				break;
			}
		}
		if (j >= _tcslen(_SubStr)) {
			return i;
		}
	}
	return UINT_MAX;
}
PSTRING shrink_to_fit(PSTRING _Str, size_t _Size) {
	if (_Size < capacity(_Str)) {
		LPTSTR temp;
		temp = (LPTSTR)realloc(_Str->str, sizeof(TCHAR) * _Size);
		if (temp == NULL) {
			return NULL;
		}
		else {
			_Str->str = temp;
			_Str->capacity = _Size;
		}
	}
	return _Str;
}
size_t size(const PSTRING _Str) {
	return _Str->size;
}
PSTRING sort(PSTRING _Dest, UINT _DstPos, UINT _DstCnt) {
	UINT i, h = 1;
	if (_DstPos >= size(_Dest)) {
		_DstPos = size(_Dest) - 1;
	}
	if (_DstPos + _DstCnt >= size(_Dest)) {
		_DstCnt = size(_Dest) - _DstPos;
	}
	for (i = 0; 3 * i + 1 < _DstCnt / 9; ++i) {
		h = 3 * i + 1;
	}
	while (h > 0) {
		for (i = _DstPos; i < _DstCnt; ++i) {
			TCHAR temp = *at(_Dest, i);
			UINT j = i;
			while (j >= _DstPos + h && *at(_Dest, j - h) > temp) {
				*at(_Dest, j) = *at(_Dest, j - h);
				j -= h;
			}
			*at(_Dest, j) = temp;
		}
		h = (h - 1) / 3;
	}
	return _Dest;
}
BOOL starts_with(const PSTRING _Str, LPCTSTR _SubStr) {
	size_t i;
	for (i = 0; i < _tcslen(_SubStr); ++i) {
		if (*at(_Str, size(_Str) + i) != _SubStr[i]) {
			return FALSE;
		}
	}
	return TRUE;
}
int stoi(PSTRING _Str) {
	return _ttoi(c_str(_Str));
}
PSTRING substr(PSTRING _Dest, const PSTRING _Source, const UINT _SrcPos, UINT _SrcCnt) {
	TCHAR _C;
	if (_Dest == _Source || _SrcPos >= size(_Source)) {
		return _Dest;
	}
	_Dest->size = 0;
	if (_SrcPos + _SrcCnt > size(_Source)) {
		_SrcCnt = size(_Source) - _SrcPos;
	}
	while (size(_Dest) < _SrcCnt) {
		_C = *at(_Source, _SrcPos + size(_Dest));
		push_back(_Dest, _C);
	}
	return _Dest;
}
PSTRING swap(PSTRING _Str1, PSTRING _Str2) {
	STRING temp;
	constructor(&temp);
	substr(&temp, _Str1, 0, size(_Str1));
	substr(_Str1, _Str2, 0, size(_Str2));
	substr(_Str2, &temp, 0, size(&temp));
	destructor(&temp);
	return _Str1;
}
PSTRING to_string(PSTRING _Str, const int _Value) {
	UINT i = _Value < 0 ? 1 : 0;
	int temp;
	for (temp = _Value; temp != 0; temp /= 10) {
		++i;
	}
	reserve(_Str, i + 1);
	resize(_Str, i, TEXT('\0'));
	_itot_s(_Value, _Str->str, capacity(_Str), 10);
	return _Str;
}
PSTRING trim(PSTRING _Str) {
	UINT i;
	for (i = 0; i < size(_Str) && front(_Str) == TEXT(' '); ++i) {
		pop_front(_Str);
	}
	for (i = size(_Str) - 1; i >= 0 && back(_Str) == TEXT(' '); --i) {
		pop_back(_Str);
	}
	return _Str;
}
PSTRING trim_left(PSTRING _Str) {
	UINT i = 0;
	while (i < size(_Str) && *at(_Str, i) == TEXT(' ')) {
		++i;
	}
	erase(_Str, 0, i);
	return _Str;
}
PSTRING trim_right(PSTRING _Str) {
	UINT i = size(_Str) - 1;
	while (i >= 0 && *at(_Str, i) == TEXT(' ')) {
		--i;
	}
	erase(_Str, i + 1, size(_Str));
	return _Str;
}