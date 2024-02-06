#pragma once

#include <chrono>
#include <string>

class Duration
{
public:
	Duration(const std::string &prefix = {});
	~Duration();

private:
	const std::chrono::nanoseconds m_start;
	const std::string m_prefix;
};

// struct Duration
// {
// 	const std::chrono::nanoseconds m_start;
// 	const std::string m_prefix;
// };

// struct Duration
// {
// 	int m_start;
// 	char* m_prefix;
// };
