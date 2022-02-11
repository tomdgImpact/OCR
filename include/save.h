#ifndef SAVE_H_
#define SAVE_H_
#include <stdlib.h>

void save(double (*data)[][10], size_t rows, size_t cols, char *filename);

void loadNet(Network *network);

void savearray(double *data, size_t rows, char *filename);

void loaddarray(double *data, char *filename);

void saveNet(Network *network);

void savearrayNet(Network *network);

void put_in_file(char c, char *filename);
#endif