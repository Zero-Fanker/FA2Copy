#pragma once
#include <FA2PPCore.h>
#include <ctype.h>
#include <string.h>

namespace utilities {
	size_t parse_list(const char* pValue, const char** outValue, size_t Count = 1) {
		char buffer[0x80];
		for (size_t i = 0; i < Count; ++i) {
			// skip the leading spaces
			while (isspace(static_cast<unsigned char>(*pValue))) {
				++pValue;
			}

			// read the next part
			int n = 0;
			if (sscanf_s(pValue, "%[^,]%n", buffer, sizeof(buffer), &n) != 1) {
				return i;
			}

			// skip all read chars and the comma
			pValue += n;
			if (*pValue) {
				++pValue;
			}

			// trim the trailing spaces
			while (n && isspace(static_cast<unsigned char>(buffer[n - 1]))) {
				buffer[n-- - 1] = '\0';
			}

			outValue[i] = _strdup(buffer);
		}

		return Count;
	}

	static bool parse_bool(const char* pValue) {
		switch (toupper(static_cast<unsigned char>(*pValue))) {
		case '1':
		case 'T':
		case 'Y':
			return true;
		case '0':
		case 'F':
		case 'N':
		default:
			return false;
		}
	}
}