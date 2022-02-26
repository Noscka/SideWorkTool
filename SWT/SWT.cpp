#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <WinUser.h>

int main()
{
	enum { ONE_KEYID = 1 };
	RegisterHotKey(0, ONE_KEYID, MOD_SHIFT | MOD_CONTROL | MOD_ALT, 'K'); // register 1 key as hotkey
	MSG msg;
	while(GetMessage(&msg, 0, 0, 0))
	{
		PeekMessage(&msg, 0, 0, 0, 0x0001);
		switch(msg.message)
		{
		case WM_HOTKEY:
			if(msg.wParam == ONE_KEYID)
			{
				printf("1 Pressed\n");
			}
		}
	}
	return 0;
}
