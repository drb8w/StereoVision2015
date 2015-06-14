#ifndef STRINGEXTENSIONS
#define STRINGEXTENSIONS

char *replace(char *st, char *orig, char *repl);

std::string ImgPath(int argc, char *argv[], int argNo, std::string &imgPath);

std::string intToString(int number);
std::string doubleToString(double number);

#endif