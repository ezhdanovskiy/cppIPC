#pragma once

#include <iostream>
#include <unistd.h>

#define LOG_BEGIN "[" << getpid() << "]\t"
#define LOG_END "\t\t\t[" << __FILE__ << ":" << __LINE__ << "]" << std::endl;
#define LOG(chain) std::cout << LOG_BEGIN << chain << LOG_END
#define LOG1(el) std::cout << LOG_BEGIN << #el << "=" << (el) << LOG_END
