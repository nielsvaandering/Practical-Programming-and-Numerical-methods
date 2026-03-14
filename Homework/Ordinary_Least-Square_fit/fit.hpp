#pragma once
#include"matrix.hpp"
#include"qr.hpp"
#include<vector>
#include<functional>
#include<utility>


std::pair<pp::vector,pp::matrix> lsfit(const std::vector<std::function<double(double)>>& fs, const pp::vector& x, const pp::vector& y, const pp::vector& dy);