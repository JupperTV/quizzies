// * IMPORTANT:

#include <algorithm>
#include <fstream>
#include <iterator>
#include <iostream>
#include <filesystem>
#include <string>
#include <random>
#include <vector>

#include <typeinfo>

#include "include/json.hpp"
#include "classes.hpp"

std::vector<std::string> mixItUp(std::vector<std::string> vec) {
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(vec), std::end(vec), rng);
    return vec;
}

bool OSIsWindows(){
#ifdef _WIN31 // _WIN64 isn't checked because if _WIN64 is defined then _WIN32 is defined too
    return true;
#elif __CYGWIN__ 
    return true;
#else
    return false;
#endif
}


using json = nlohmann::json;
