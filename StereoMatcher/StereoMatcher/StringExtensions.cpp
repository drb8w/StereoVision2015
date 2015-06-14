#include "StringExtensions.h"

#include "stdafx.h"
#include <string>
#include <sstream>

// ==============================================
// string stuff
// ==============================================

char *replace(char *st, char *orig, char *repl) 
{
  static char buffer[4096];
  char *ch;
  if (!(ch = strstr(st, orig)))
   return st;
  strncpy(buffer, st, ch-st);  
  buffer[ch-st] = 0;
  sprintf(buffer+(ch-st), "%s%s", repl, ch+strlen(orig));
  return buffer;
}

std::string ImgPath(int argc, char *argv[], int argNo, std::string &imgPath)
{
	if (argc >argNo)
		imgPath = argv[argNo];

	for (int i=0; i<100; i++)
		imgPath = replace((char *)(imgPath.c_str()), "\\", "/");

	return imgPath;
}

std::string intToString(int number)
{
	
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

std::string doubleToString(double number)
{
	
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}