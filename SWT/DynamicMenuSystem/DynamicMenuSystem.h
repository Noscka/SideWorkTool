#pragma once

#include <list>
#include <string>
#include <functional>
#include <Windows.h>
#include <iostream>
#include <list>

#define ARROW_UP    72
#define ARROW_DOWN  80
#define ENTER       13

class MenuEntry
{
public:
	std::string Name;
	std::function<void()> Function;

	MenuEntry(std::string name, std::function<void()> function)
	{
		Name = name;
		Function = function;
	}
};

static class DynamicMenuSystem
{
private:
	static CONSOLE_SCREEN_BUFFER_INFO csbi;
	static int columns, rows;
	static std::list<MenuEntry> MenuEntryList;
	static bool SetUpEntries, ContinueMenu;

public:
	
	/// <summary>
	/// Create Menu once everything was set up
	/// </summary>
	/// <param name="Title">Title to be displayed</param>
	/// <param name="AddExitEntry">if there should be "exit menu" entry at the bottom</param>
	static void CreateMenu(std::string Title, bool AddExitEntry);

	/// <summary>
	/// Add Entries to Menu
	/// </summary>
	/// <param name="size">Amount of entries being added</param>
	/// <param name="...">Entry Variable</param>
	static void AddMenuEntries(int size, MenuEntry ...);

	/// <summary>
	/// Simple Quit Menu, does this by setting menu while loop to false
	/// </summary>
	inline static void QuitMenu();
};