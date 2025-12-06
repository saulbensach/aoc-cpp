#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

const std::string PATH = "/home/saul/Work/aoc-cpp/input/";

namespace aoc {
    struct Range {
        long long lower;
        long long upper;

        Range(long long a, long long b) : lower(a), upper(b) {}
    };

    int char_to_int(char c) {
        return c - '0';
    }
}