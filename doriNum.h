#pragma once
#include <bits/stdc++.h>

struct Narray{
    double** values;
    unsigned int row, colunm;

    Narray(unsigned int _row, unsigned int _colunm);

    Narray operator+ (const double &a);

    Narray operator- ();

    Narray operator* (const double &a);

    Narray operator/ (const double &a);

    Narray operator+ (const Narray &a);

    Narray operator- (const Narray &a);

    Narray operator* (const Narray &a);

    Narray operator() (auto func);

    void randomValues();
};