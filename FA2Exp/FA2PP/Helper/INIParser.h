﻿#pragma once

#include "Parser.h"

#include "../INI.h"
#include <algorithm>

using byte = unsigned char;

class INI_EX {
	INIClass* IniFile;

public:
	explicit INI_EX(INIClass* pIniFile)
		: IniFile(pIniFile)
	{ }

	char* value() const {
		return INI_EX::readBuffer;
	}

	size_t max_size() const {
		return INI_EX::readLength;
	}

	bool empty() const {
		return !INI_EX::readBuffer[0];
	}

	// basic string reader
	size_t ReadString(const char* pSection, const char* pKey) {
		auto const pEntries = IniFile->GetEntries(pSection);
		if (!pEntries) return 0;
		auto const pItem = pEntries->Items.GetItem(pKey);
		if (!pItem) return 0;
		CString* pValue = reinterpret_cast<CString*>(&pItem->Value);
		if (!pValue || pValue->IsEmpty()) return 0;
		auto const res = pValue->GetLength();
		if (!res) return 0;
		auto const size = std::min(res + 1, (int)this->max_size());
		memcpy_s(this->value(), size, pValue, size);
		return static_cast<size_t>(res);
	}

	// parser template
	template <typename T, size_t Count>
	bool Read(const char* pSection, const char* pKey, T* pBuffer) {
		if (this->ReadString(pSection, pKey)) {
			return Parser<T, Count>::Parse(this->value(), pBuffer) == Count;
		}
		return false;
	}

	// helpers

	bool ReadBool(const char* pSection, const char* pKey, bool* bBuffer) {
		return Read<bool, 1>(pSection, pKey, bBuffer);
	}

	bool ReadInteger(const char* pSection, const char* pKey, int* nBuffer) {
		return Read<int, 1>(pSection, pKey, nBuffer);
	}

	bool Read2Integers(const char* pSection, const char* pKey, int* nBuffer) {
		return Read<int, 2>(pSection, pKey, nBuffer);
	}

	bool Read3Integers(const char* pSection, const char* pKey, int* nBuffer) {
		return Read<int, 3>(pSection, pKey, nBuffer);
	}

	bool Read4Integers(const char* pSection, const char* pKey, int* nBuffer) {
		return Read<int, 4>(pSection, pKey, nBuffer);
	}

	bool Read3Bytes(const char* pSection, const char* pKey, byte* nBuffer) {
		return Read<byte, 3>(pSection, pKey, nBuffer);
	}

	bool ReadDouble(const char* pSection, const char* pKey, double* nBuffer) {
		return Read<double, 1>(pSection, pKey, nBuffer);
	}


public:
	static const size_t readLength = 2048;
	static char readBuffer[readLength];

};
