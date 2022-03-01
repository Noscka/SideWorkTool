/*
Program: ASCII ART Generator (Modified by Ruski1)
Description: Design text with ascii art. Modification: Made function return string instead of printing it straight to console
Author: Lord Hypersonic
Email: lordhypersonic.522@gmail.com
Website: www.lordhypersonic.blogspot.com
*/

#include <iostream>
#include <string>
#include <conio.h>
#include "AsciiTextGenerator.h"

std::string AsciiTextGenerator::AsciiWrite(std::string input)
{
	std::string output;

	//loop will print first layer
	for(int i = 0; i < input.size(); i++)
	{
		if(input[i] == 'A' || input[i] == 'a')
			output += "  ___   ";
		if(input[i] == 'B' || input[i] == 'b')
			output += " _____  ";
		if(input[i] == 'C' || input[i] == 'c')
			output += " _____  ";
		if(input[i] == 'D' || input[i] == 'd')
			output += " _____  ";
		if(input[i] == 'E' || input[i] == 'e')
			output += " _____  ";
		if(input[i] == 'F' || input[i] == 'f')
			output += " _____  ";
		if(input[i] == 'G' || input[i] == 'g')
			output += " _____  ";
		if(input[i] == 'H' || input[i] == 'h')
			output += " _   _  ";
		if(input[i] == 'I' || input[i] == 'i')
			output += " _____  ";
		if(input[i] == 'J' || input[i] == 'j')
			output += "   ___  ";
		if(input[i] == 'K' || input[i] == 'k')
			output += " _   __ ";
		if(input[i] == 'L' || input[i] == 'l')
			output += " _      ";
		if(input[i] == 'M' || input[i] == 'm')
			output += " __  __  ";
		if(input[i] == 'N' || input[i] == 'n')
			output += " _   _  ";
		if(input[i] == 'O' || input[i] == 'o')
			output += " _____  ";
		if(input[i] == 'P' || input[i] == 'p')
			output += " _____  ";
		if(input[i] == 'Q' || input[i] == 'q')
			output += " _____  ";
		if(input[i] == 'R' || input[i] == 'r')
			output += " _____  ";
		if(input[i] == 'S' || input[i] == 's')
			output += " _____  ";
		if(input[i] == 'T' || input[i] == 't')
			output += " _____  ";
		if(input[i] == 'U' || input[i] == 'u')
			output += " _   _  ";
		if(input[i] == 'V' || input[i] == 'v')
			output += " _   _  ";
		if(input[i] == 'W' || input[i] == 'w')
			output += " _    _  ";
		if(input[i] == 'X' || input[i] == 'x')
			output += "__   __ ";
		if(input[i] == 'Y' || input[i] == 'y')
			output += "__   __ ";
		if(input[i] == 'Z' || input[i] == 'z')
			output += " ______ ";
		if(input[i] == ' ')
			output += "  ";
		if(input[i] == '`')
			output += " _  ";
		if(input[i] == '~')
			output += "      ";
		if(input[i] == '1')
			output += " __   ";
		if(input[i] == '2')
			output += " _____  ";
		if(input[i] == '3')
			output += " _____  ";
		if(input[i] == '4')
			output += "   ___  ";
		if(input[i] == '5')
			output += " _____  ";
		if(input[i] == '6')
			output += "  ____  ";
		if(input[i] == '7')
			output += " ______ ";
		if(input[i] == '.')
			output += "    ";
		if(input[i] == '8')
			output += " _____  ";
		if(input[i] == '9')
			output += " _____  ";
		if(input[i] == '0')
			output += " _____  ";
		if(input[i] == '!')
			output += " _  ";
		if(input[i] == '@')
			output += "   ____   ";
		if(input[i] == '#')
			output += "   _  _    ";
		if(input[i] == '$')
			output += "  _   ";
		if(input[i] == '%')
			output += " _   __ ";
		if(input[i] == '^')
			output += " /\\  ";
		if(input[i] == '&')
			output += "         ";
		if(input[i] == '*')
			output += "    _     ";
		if(input[i] == '(')
			output += "  __ ";
		if(input[i] == ')')
			output += "__   ";
		if(input[i] == '-')
			output += "         ";
		if(input[i] == '_')
			output += "         ";
		if(input[i] == '=')
			output += "         ";
		if(input[i] == '+')
			output += "        ";
		if(input[i] == '[')
			output += " ___  ";
		if(input[i] == '{')
			output += "   __ ";
		if(input[i] == ']')
			output += " ___  ";
		if(input[i] == '}')
			output += "__    ";
		if(input[i] == '|')
			output += " _  ";
		if(input[i] == '\\')
			output += "__      ";
		if(input[i] == ';')
			output += " _  ";
		if(input[i] == ':')
			output += "    ";
		if(input[i] == '\'')
			output += " _  ";
		if(input[i] == '"')
			output += " _ _  ";
		if(input[i] == '<')
			output += "   __ ";
		if(input[i] == ',')
			output += "    ";
		if(input[i] == '>')
			output += "__    ";
		if(input[i] == '/')
			output += "     __ ";
		if(input[i] == '?')
			output += " ___   ";
	}
	output += "\n";
	//loop will print second layer
	for(int i = 0; i < input.size(); i++)
	{
		if(input[i] == 'A' || input[i] == 'a')
			output += " / _ \\  ";
		if(input[i] == 'B' || input[i] == 'b')
			output += "| ___ \\ ";
		if(input[i] == 'C' || input[i] == 'c')
			output += "/  __ \\ ";
		if(input[i] == 'D' || input[i] == 'd')
			output += "|  _  \\ ";
		if(input[i] == 'E' || input[i] == 'e')
			output += "|  ___| ";
		if(input[i] == 'F' || input[i] == 'f')
			output += "|  ___| ";
		if(input[i] == 'G' || input[i] == 'g')
			output += "|  __ \\ ";
		if(input[i] == 'H' || input[i] == 'h')
			output += "| | | | ";
		if(input[i] == 'I' || input[i] == 'i')
			output += "|_   _| ";
		if(input[i] == 'J' || input[i] == 'j')
			output += "  |_  | ";
		if(input[i] == 'K' || input[i] == 'k')
			output += "| | / / ";
		if(input[i] == 'L' || input[i] == 'l')
			output += "| |     ";
		if(input[i] == 'M' || input[i] == 'm')
			output += "|  \\/  | ";
		if(input[i] == 'N' || input[i] == 'n')
			output += "| \\ | | ";
		if(input[i] == 'O' || input[i] == 'o')
			output += "|  _  | ";
		if(input[i] == 'P' || input[i] == 'p')
			output += "| ___ \\ ";
		if(input[i] == 'Q' || input[i] == 'q')
			output += "|  _  | ";
		if(input[i] == 'R' || input[i] == 'r')
			output += "| ___ \\ ";
		if(input[i] == 'S' || input[i] == 's')
			output += "/  ___| ";
		if(input[i] == 'T' || input[i] == 't')
			output += "|_   _| ";
		if(input[i] == 'U' || input[i] == 'u')
			output += "| | | | ";
		if(input[i] == 'V' || input[i] == 'v')
			output += "| | | | ";
		if(input[i] == 'W' || input[i] == 'w')
			output += "| |  | | ";
		if(input[i] == 'X' || input[i] == 'x')
			output += "\\ \\ / / ";
		if(input[i] == 'Y' || input[i] == 'y')
			output += "\\ \\ / / ";
		if(input[i] == 'Z' || input[i] == 'z')
			output += "|___  / ";
		if(input[i] == ' ')
			output += "  ";
		if(input[i] == '`')
			output += "( ) ";
		if(input[i] == '~')
			output += "      ";
		if(input[i] == '1')
			output += "/  |  ";
		if(input[i] == '2')
			output += "/ __  \\ ";
		if(input[i] == '3')
			output += "|____ | ";
		if(input[i] == '4')
			output += "  /   | ";
		if(input[i] == '5')
			output += "|  ___| ";
		if(input[i] == '6')
			output += " / ___| ";
		if(input[i] == '7')
			output += "|___  / ";
		if(input[i] == '.')
			output += "    ";
		if(input[i] == '8')
			output += "|  _  | ";
		if(input[i] == '9')
			output += "|  _  | ";
		if(input[i] == '0')
			output += "|  _  | ";
		if(input[i] == '!')
			output += "| | ";
		if(input[i] == '@')
			output += "  / __ \\  ";
		if(input[i] == '#')
			output += " _| || |_  ";
		if(input[i] == '$')
			output += " | |  ";
		if(input[i] == '%')
			output += "(_) / / ";
		if(input[i] == '^')
			output += "|/\\| ";
		if(input[i] == '&')
			output += "  ___    ";
		if(input[i] == '*')
			output += " /\\| |/\\  ";
		if(input[i] == '(')
			output += " / / ";
		if(input[i] == ')')
			output += "\\ \\  ";
		if(input[i] == '-')
			output += "         ";
		if(input[i] == '_')
			output += "         ";
		if(input[i] == '=')
			output += " ______  ";
		if(input[i] == '+')
			output += "   _    ";
		if(input[i] == '[')
			output += "|  _| ";
		if(input[i] == '{')
			output += "  / / ";
		if(input[i] == ']')
			output += "|_  | ";
		if(input[i] == '}')
			output += "\\ \\   ";
		if(input[i] == '|')
			output += "| | ";
		if(input[i] == '\\')
			output += "\\ \\     ";
		if(input[i] == ';')
			output += "(_) ";
		if(input[i] == ':')
			output += " _  ";
		if(input[i] == '\'')
			output += "( ) ";
		if(input[i] == '"')
			output += "( | ) ";
		if(input[i] == '<')
			output += "  / / ";
		if(input[i] == ',')
			output += "    ";
		if(input[i] == '>')
			output += "\\ \\   ";
		if(input[i] == '/')
			output += "    / / ";
		if(input[i] == '?')
			output += "|__ \\  ";
	}
	output += "\n";
	//loop will print third layer
	for(int i = 0; i < input.size(); i++)
	{
		if(input[i] == 'A' || input[i] == 'a')
			output += "/ /_\\ \\ ";
		if(input[i] == 'B' || input[i] == 'b')
			output += "| |_/ / ";
		if(input[i] == 'C' || input[i] == 'c')
			output += "| /  \\/ ";
		if(input[i] == 'D' || input[i] == 'd')
			output += "| | | | ";
		if(input[i] == 'E' || input[i] == 'e')
			output += "| |__   ";
		if(input[i] == 'F' || input[i] == 'f')
			output += "| |_    ";
		if(input[i] == 'G' || input[i] == 'g')
			output += "| |  \\/ ";
		if(input[i] == 'H' || input[i] == 'h')
			output += "| |_| | ";
		if(input[i] == 'I' || input[i] == 'i')
			output += "  | |   ";
		if(input[i] == 'J' || input[i] == 'j')
			output += "    | | ";
		if(input[i] == 'K' || input[i] == 'k')
			output += "| |/ /  ";
		if(input[i] == 'L' || input[i] == 'l')
			output += "| |     ";
		if(input[i] == 'M' || input[i] == 'm')
			output += "| .  . | ";
		if(input[i] == 'N' || input[i] == 'n')
			output += "|  \\| | ";
		if(input[i] == 'O' || input[i] == 'o')
			output += "| | | | ";
		if(input[i] == 'P' || input[i] == 'p')
			output += "| |_/ / ";
		if(input[i] == 'Q' || input[i] == 'q')
			output += "| | | | ";
		if(input[i] == 'R' || input[i] == 'r')
			output += "| |_/ / ";
		if(input[i] == 'S' || input[i] == 's')
			output += "\\ `--.  ";
		if(input[i] == 'T' || input[i] == 't')
			output += "  | |   ";
		if(input[i] == 'U' || input[i] == 'u')
			output += "| | | | ";
		if(input[i] == 'V' || input[i] == 'v')
			output += "| | | | ";
		if(input[i] == 'W' || input[i] == 'w')
			output += "| |  | | ";
		if(input[i] == 'X' || input[i] == 'x')
			output += " \\ V /  ";
		if(input[i] == 'Y' || input[i] == 'y')
			output += " \\ V /  ";
		if(input[i] == 'Z' || input[i] == 'z')
			output += "   / /  ";
		if(input[i] == ' ')
			output += "  ";
		if(input[i] == '`')
			output += " \\| ";
		if(input[i] == '~')
			output += " /\\/| ";
		if(input[i] == '1')
			output += "`| |  ";
		if(input[i] == '2')
			output += "`' / /' ";
		if(input[i] == '3')
			output += "    / / ";
		if(input[i] == '4')
			output += " / /| | ";
		if(input[i] == '5')
			output += "|___ \\  ";
		if(input[i] == '6')
			output += "/ /___  ";
		if(input[i] == '7')
			output += "   / /  ";
		if(input[i] == '.')
			output += "    ";
		if(input[i] == '8')
			output += " \\ V /  ";
		if(input[i] == '9')
			output += "| |_| | ";
		if(input[i] == '0')
			output += "| |/' | ";
		if(input[i] == '!')
			output += "| | ";
		if(input[i] == '@')
			output += " / / _` | ";
		if(input[i] == '#')
			output += "|_  __  _| ";
		if(input[i] == '$')
			output += "/ __) ";
		if(input[i] == '%')
			output += "   / /  ";
		if(input[i] == '^')
			output += "     ";
		if(input[i] == '&')
			output += " ( _ )   ";
		if(input[i] == '*')
			output += " \\ ` ' /  ";
		if(input[i] == '(')
			output += "| |  ";
		if(input[i] == ')')
			output += " | | ";
		if(input[i] == '-')
			output += " ______  ";
		if(input[i] == '_')
			output += "         ";
		if(input[i] == '=')
			output += "|______| ";
		if(input[i] == '+')
			output += " _| |_  ";
		if(input[i] == '[')
			output += "| |   ";
		if(input[i] == '{')
			output += " | |  ";
		if(input[i] == ']')
			output += "  | | ";
		if(input[i] == '}')
			output += " | |  ";
		if(input[i] == '|')
			output += "| | ";
		if(input[i] == '\\')
			output += " \\ \\    ";
		if(input[i] == ';')
			output += "    ";
		if(input[i] == ':')
			output += "(_) ";
		if(input[i] == '\'')
			output += "|/  ";
		if(input[i] == '"')
			output += " V V  ";
		if(input[i] == '<')
			output += " / /  ";
		if(input[i] == ',')
			output += "    ";
		if(input[i] == '>')
			output += " \\ \\  ";
		if(input[i] == '/')
			output += "   / /  ";
		if(input[i] == '?')
			output += "   ) | ";
	}
	output += "\n";
	//loop will print fourth layer
	for(int i = 0; i < input.size(); i++)
	{
		if(input[i] == 'A' || input[i] == 'a')
			output += "|  _  | ";
		if(input[i] == 'B' || input[i] == 'b')
			output += "| ___ \\ ";
		if(input[i] == 'C' || input[i] == 'c')
			output += "| |     ";
		if(input[i] == 'D' || input[i] == 'd')
			output += "| | | | ";
		if(input[i] == 'E' || input[i] == 'e')
			output += "|  __|  ";
		if(input[i] == 'F' || input[i] == 'f')
			output += "|  _|   ";
		if(input[i] == 'G' || input[i] == 'g')
			output += "| | __  ";
		if(input[i] == 'H' || input[i] == 'h')
			output += "|  _  | ";
		if(input[i] == 'I' || input[i] == 'i')
			output += "  | |   ";
		if(input[i] == 'J' || input[i] == 'j')
			output += "    | | ";
		if(input[i] == 'K' || input[i] == 'k')
			output += "|    \\  ";
		if(input[i] == 'L' || input[i] == 'l')
			output += "| |     ";
		if(input[i] == 'M' || input[i] == 'm')
			output += "| |\\/| | ";
		if(input[i] == 'N' || input[i] == 'n')
			output += "| . ` | ";
		if(input[i] == 'O' || input[i] == 'o')
			output += "| | | | ";
		if(input[i] == 'P' || input[i] == 'p')
			output += "|  __/  ";
		if(input[i] == 'Q' || input[i] == 'q')
			output += "| | | | ";
		if(input[i] == 'R' || input[i] == 'r')
			output += "|    /  ";
		if(input[i] == 'S' || input[i] == 's')
			output += " `--. \\ ";
		if(input[i] == 'T' || input[i] == 't')
			output += "  | |   ";
		if(input[i] == 'U' || input[i] == 'u')
			output += "| | | | ";
		if(input[i] == 'V' || input[i] == 'v')
			output += "| | | | ";
		if(input[i] == 'W' || input[i] == 'w')
			output += "| |/\\| | ";
		if(input[i] == 'X' || input[i] == 'x')
			output += " / ^ \\  ";
		if(input[i] == 'Y' || input[i] == 'y')
			output += "  \\ /   ";
		if(input[i] == 'Z' || input[i] == 'z')
			output += "  / /   ";
		if(input[i] == ' ')
			output += "  ";
		if(input[i] == '`')
			output += "    ";
		if(input[i] == '~')
			output += "|/\\/  ";
		if(input[i] == '1')
			output += " | |  ";
		if(input[i] == '2')
			output += "  / /   ";
		if(input[i] == '3')
			output += "    \\ \\ ";
		if(input[i] == '4')
			output += "/ /_| | ";
		if(input[i] == '5')
			output += "    \\ \\ ";
		if(input[i] == '6')
			output += "| ___ \\ ";
		if(input[i] == '7')
			output += "  / /   ";
		if(input[i] == '.')
			output += "    ";
		if(input[i] == '8')
			output += " / _ \\  ";
		if(input[i] == '9')
			output += "\\____ | ";
		if(input[i] == '0')
			output += "|  /| | ";
		if(input[i] == '!')
			output += "| | ";
		if(input[i] == '@')
			output += "| | (_| | ";
		if(input[i] == '#')
			output += " _| || |_  ";
		if(input[i] == '$')
			output += "\\__ \\ ";
		if(input[i] == '%')
			output += "  / /   ";
		if(input[i] == '^')
			output += "     ";
		if(input[i] == '&')
			output += " / _ \\/\\ ";
		if(input[i] == '*')
			output += "|_     _| ";
		if(input[i] == '(')
			output += "| |  ";
		if(input[i] == ')')
			output += " | | ";
		if(input[i] == '-')
			output += "|______| ";
		if(input[i] == '_')
			output += "         ";
		if(input[i] == '=')
			output += " ______  ";
		if(input[i] == '+')
			output += "|_   _| ";
		if(input[i] == '[')
			output += "| |   ";
		if(input[i] == '{')
			output += "< <   ";
		if(input[i] == ']')
			output += "  | | ";
		if(input[i] == '}')
			output += "  > > ";
		if(input[i] == '|')
			output += "| | ";
		if(input[i] == '\\')
			output += "  \\ \\   ";
		if(input[i] == ';')
			output += " _  ";
		if(input[i] == ':')
			output += "    ";
		if(input[i] == '\'')
			output += "    ";
		if(input[i] == '"')
			output += "      ";
		if(input[i] == '<')
			output += "< <   ";
		if(input[i] == ',')
			output += " _  ";
		if(input[i] == '>')
			output += "  > > ";
		if(input[i] == '/')
			output += "  / /   ";
		if(input[i] == '?')
			output += "  / /  ";
	}
	output += "\n";
	//loop will print fifth layer
	for(int i = 0; i < input.size(); i++)
	{
		if(input[i] == 'A' || input[i] == 'a')
			output += "| | | | ";
		if(input[i] == 'B' || input[i] == 'b')
			output += "| |_/ / ";
		if(input[i] == 'C' || input[i] == 'c')
			output += "| \\__/\\ ";
		if(input[i] == 'D' || input[i] == 'd')
			output += "| |/ /  ";
		if(input[i] == 'E' || input[i] == 'e')
			output += "| |___  ";
		if(input[i] == 'F' || input[i] == 'f')
			output += "| |     ";
		if(input[i] == 'G' || input[i] == 'g')
			output += "| |_\\ \\ ";
		if(input[i] == 'H' || input[i] == 'h')
			output += "| | | | ";
		if(input[i] == 'I' || input[i] == 'i')
			output += " _| |_  ";
		if(input[i] == 'J' || input[i] == 'j')
			output += "/\\__/ / ";
		if(input[i] == 'K' || input[i] == 'k')
			output += "| |\\  \\ ";
		if(input[i] == 'L' || input[i] == 'l')
			output += "| |____ ";
		if(input[i] == 'M' || input[i] == 'm')
			output += "| |  | | ";
		if(input[i] == 'N' || input[i] == 'n')
			output += "| |\\  | ";
		if(input[i] == 'O' || input[i] == 'o')
			output += "\\ \\_/ / ";
		if(input[i] == 'P' || input[i] == 'p')
			output += "| |     ";
		if(input[i] == 'Q' || input[i] == 'q')
			output += "\\ \\/' / ";
		if(input[i] == 'R' || input[i] == 'r')
			output += "| |\\ \\  ";
		if(input[i] == 'S' || input[i] == 's')
			output += "/\\__/ / ";
		if(input[i] == 'T' || input[i] == 't')
			output += "  | |   ";
		if(input[i] == 'U' || input[i] == 'u')
			output += "| |_| | ";
		if(input[i] == 'V' || input[i] == 'v')
			output += "\\ \\_/ / ";
		if(input[i] == 'W' || input[i] == 'w')
			output += "\\  /\\  / ";
		if(input[i] == 'X' || input[i] == 'x')
			output += "/ / \\ \\ ";
		if(input[i] == 'Y' || input[i] == 'y')
			output += "  | |   ";
		if(input[i] == 'Z' || input[i] == 'z')
			output += "./ /___ ";
		if(input[i] == ' ')
			output += "  ";
		if(input[i] == '`')
			output += "    ";
		if(input[i] == '~')
			output += "      ";
		if(input[i] == '1')
			output += "_| |_ ";
		if(input[i] == '2')
			output += "./ /___ ";
		if(input[i] == '3')
			output += ".___/ / ";
		if(input[i] == '4')
			output += "\\___  | ";
		if(input[i] == '5')
			output += "/\\__/ / ";
		if(input[i] == '6')
			output += "| \\_/ | ";
		if(input[i] == '7')
			output += "./ /    ";
		if(input[i] == '.')
			output += " _  ";
		if(input[i] == '8')
			output += "| |_| | ";
		if(input[i] == '9')
			output += ".___/ / ";
		if(input[i] == '0')
			output += "\\ |_/ / ";
		if(input[i] == '!')
			output += "|_| ";
		if(input[i] == '@')
			output += " \\ \\__,_| ";
		if(input[i] == '#')
			output += "|_  __  _| ";
		if(input[i] == '$')
			output += "(   / ";
		if(input[i] == '%')
			output += " / / _  ";
		if(input[i] == '^')
			output += "     ";
		if(input[i] == '&')
			output += "| (_>  < ";
		if(input[i] == '*')
			output += " / , . \\  ";
		if(input[i] == '(')
			output += "| |  ";
		if(input[i] == ')')
			output += " | | ";
		if(input[i] == '-')
			output += "         ";
		if(input[i] == '_')
			output += " ______  ";
		if(input[i] == '=')
			output += "|______| ";
		if(input[i] == '+')
			output += "  |_|   ";
		if(input[i] == '[')
			output += "| |_  ";
		if(input[i] == '{')
			output += " | |  ";
		if(input[i] == ']')
			output += " _| | ";
		if(input[i] == '}')
			output += " | |  ";
		if(input[i] == '|')
			output += "| | ";
		if(input[i] == '\\')
			output += "   \\ \\  ";
		if(input[i] == ';')
			output += "( ) ";
		if(input[i] == ':')
			output += " _  ";
		if(input[i] == '\'')
			output += "    ";
		if(input[i] == '"')
			output += "      ";
		if(input[i] == '<')
			output += " \\ \\  ";
		if(input[i] == ',')
			output += "( ) ";
		if(input[i] == '>')
			output += " / /  ";
		if(input[i] == '/')
			output += " / /    ";
		if(input[i] == '?')
			output += " |_|   ";
	}
	output += "\n";
	//loop will print sixth layer
	for(int i = 0; i < input.size(); i++)
	{
		if(input[i] == 'A' || input[i] == 'a')
			output += "\\_| |_/ ";
		if(input[i] == 'B' || input[i] == 'b')
			output += "\\____/  ";
		if(input[i] == 'C' || input[i] == 'c')
			output += " \\____/ ";
		if(input[i] == 'D' || input[i] == 'd')
			output += "|___/   ";
		if(input[i] == 'E' || input[i] == 'e')
			output += "\\____/  ";
		if(input[i] == 'F' || input[i] == 'f')
			output += "\\_|     ";
		if(input[i] == 'G' || input[i] == 'g')
			output += " \\____/ ";
		if(input[i] == 'H' || input[i] == 'h')
			output += "\\_| |_/ ";
		if(input[i] == 'I' || input[i] == 'i')
			output += " \\___/  ";
		if(input[i] == 'J' || input[i] == 'j')
			output += "\\____/  ";
		if(input[i] == 'K' || input[i] == 'k')
			output += "\\_| \\_/ ";
		if(input[i] == 'L' || input[i] == 'l')
			output += "\\_____/ ";
		if(input[i] == 'M' || input[i] == 'm')
			output += "\\_|  |_/ ";
		if(input[i] == 'N' || input[i] == 'n')
			output += "\\_| \\_/ ";
		if(input[i] == 'O' || input[i] == 'o')
			output += " \\___/  ";
		if(input[i] == 'P' || input[i] == 'p')
			output += "\\_|     ";
		if(input[i] == 'Q' || input[i] == 'q')
			output += " \\_/\\_\\ ";
		if(input[i] == 'R' || input[i] == 'r')
			output += "\\_| \\_| ";
		if(input[i] == 'S' || input[i] == 's')
			output += "\\____/  ";
		if(input[i] == 'T' || input[i] == 't')
			output += "  \\_/   ";
		if(input[i] == 'U' || input[i] == 'u')
			output += " \\___/  ";
		if(input[i] == 'V' || input[i] == 'v')
			output += " \\___/  ";
		if(input[i] == 'W' || input[i] == 'w')
			output += " \\/  \\/  ";
		if(input[i] == 'X' || input[i] == 'x')
			output += "\\/   \\/ ";
		if(input[i] == 'Y' || input[i] == 'y')
			output += "  \\_/   ";
		if(input[i] == 'Z' || input[i] == 'z')
			output += "\\_____/ ";
		if(input[i] == ' ')
			output += "  ";
		if(input[i] == '`')
			output += "    ";
		if(input[i] == '~')
			output += "      ";
		if(input[i] == '1')
			output += "\\___/ ";
		if(input[i] == '2')
			output += "\\_____/ ";
		if(input[i] == '3')
			output += "\\____/  ";
		if(input[i] == '4')
			output += "    |_/ ";
		if(input[i] == '5')
			output += "\\____/  ";
		if(input[i] == '6')
			output += "\\_____/ ";
		if(input[i] == '7')
			output += "\\_/     ";
		if(input[i] == '.')
			output += "(_) ";
		if(input[i] == '8')
			output += "\\_____/ ";
		if(input[i] == '9')
			output += "\\____/  ";
		if(input[i] == '0')
			output += " \\___/  ";
		if(input[i] == '!')
			output += "(_) ";
		if(input[i] == '@')
			output += "  \\____/  ";
		if(input[i] == '#')
			output += "  |_||_|   ";
		if(input[i] == '$')
			output += " |_|  ";
		if(input[i] == '%')
			output += "/_/ (_) ";
		if(input[i] == '^')
			output += "     ";
		if(input[i] == '&')
			output += " \\___/\\/ ";
		if(input[i] == '*')
			output += " \\/|_|\\/  ";
		if(input[i] == '(')
			output += " \\_\\ ";
		if(input[i] == ')')
			output += "/_/  ";
		if(input[i] == '-')
			output += "         ";
		if(input[i] == '_')
			output += "|______| ";
		if(input[i] == '=')
			output += "         ";
		if(input[i] == '+')
			output += "        ";
		if(input[i] == '[')
			output += "|___| ";
		if(input[i] == '{')
			output += "  \\_\\ ";
		if(input[i] == ']')
			output += "|___| ";
		if(input[i] == '}')
			output += "/_/   ";
		if(input[i] == '|')
			output += "|_| ";
		if(input[i] == '\\')
			output += "    \\_\\ ";
		if(input[i] == ';')
			output += "|/  ";
		if(input[i] == ':')
			output += "(_) ";
		if(input[i] == '\'')
			output += "    ";
		if(input[i] == '"')
			output += "      ";
		if(input[i] == '<')
			output += "  \\_\\ ";
		if(input[i] == ',')
			output += "|/  ";
		if(input[i] == '>')
			output += "/_/   ";
		if(input[i] == '/')
			output += "/_/     ";
		if(input[i] == '?')
			output += " (_)   ";
	}
	output += "\n";

	return output;
}