﻿#include "../FA2Expand.h"
#include "../resource.h"
#include <INI.h>

int MinPlayer = 2;

DEFINE_HOOK(4D57D2, SaveMapOption_OnInitDialog, 5)
{
	GET(const CDialog*, pThis, ESI);

	auto& mapFile = INIClass::CurrentMapSetting();

	auto const MinPlayer = mapFile.GetInteger("Basic", "MinPlayer", 2);
	auto const hwnd = GetDlgItem(pThis->m_hWnd, WND_SaveOption::Edit_MinPlayer);
	char szMinPlayer[4]{};
	_itoa_s(MinPlayer, szMinPlayer, 10);
	SendMessageA(hwnd, WM_SETTEXT, sizeof(szMinPlayer), (LPARAM)szMinPlayer);

	//logger::g_logger.Warn(__FUNCTION__" minPlayer:" + std::string(szMinPlayer));
	return 0;
}

DEFINE_HOOK(4D56E0, SaveMapOption_DoDataExchange, 8)
{
	GET(const CDialog*, pThis, ECX);

	auto const hwnd = GetDlgItem(pThis->m_hWnd, WND_SaveOption::Edit_MinPlayer);
	char szMinPlayer[4]{};
	SendMessageA(hwnd, WM_GETTEXT, 4, (LPARAM)szMinPlayer);
	//logger::g_logger.Warn(__FUNCTION__" " + std::string(szMinPlayer));
	MinPlayer = atoi(szMinPlayer);
	MinPlayer > 0 ? MinPlayer : 2;

	return 0;
}

DEFINE_HOOK(428229, SaveMap_MinPlayer, 8)
{
	GET(INIEntry* const, pEntry, ESI);

	auto const minPlayerStr = std::to_string(MinPlayer);
	pEntry->Value = minPlayerStr.c_str();

	//logger::g_logger.Warn(__FUNCTION__" " + std::string(pEntry->Value.c_str()));

	return 0x428236;
}