#pragma once

#include <iostream>
#include <unistd.h>
#include <thread>

#if defined(__linux__)
    #define LOG_BEGIN "[" << getpid() << std::hex << ":0x" << std::this_thread::get_id() << std::dec << "]\t"
#else
    #define LOG_BEGIN "[" << getpid() << ":" << std::this_thread::get_id() << "]\t"
#endif

#define LOG_END "\t\t\t[" << __FILE__ << ":" << __LINE__ << "]" << std::endl;
#define LOG(chain) std::cout << LOG_BEGIN << chain << LOG_END
#define LOG1(el) std::cout << LOG_BEGIN << #el << "=" << (el) << LOG_END
