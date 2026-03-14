#pragma once
#include"matrix.hpp"
#include"qr.hpp"
#include<vector>
#include<functional>


pp::vector lsfit(const std::vector<std::function<double(double)>>& fs, const pp::vector& x, const pp::vector& y, const pp::vector& dy);