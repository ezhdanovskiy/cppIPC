#pragma once

#include <iostream>
#include <unistd.h>
#include <thread>

#define BEFORE_LOG
#define AFTER_LOG

#if defined(__linux__)
#define LOG_THREAD_ID std::hex << ":0x" << std::this_thread::get_id() << std::dec
#else
#define LOG_THREAD_ID ":" << std::this_thread::get_id()
#endif

#define LOG_BEGIN BEFORE_LOG std::cout << "[" << getpid() << LOG_THREAD_ID << "]\t"
#define LOG_END "\t\t\t[" << __FILE__ << ":" << __LINE__ << "]" << std::endl; AFTER_LOG

#define LOG(chain) LOG_BEGIN << chain << LOG_END
#define LOG1(el) LOG_BEGIN << #el << "=" << (el) << LOG_END
