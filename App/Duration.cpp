#include "Duration.h"

#include <iostream>

Duration::Duration(const std::string &prefix)
    : m_start{std::chrono::system_clock::now().time_since_epoch()}
    , m_prefix{prefix}
{
}

Duration::~Duration()
{
	const auto currentTime = std::chrono::system_clock::now().time_since_epoch();

	std::cout << m_prefix << (currentTime - m_start).count() << std::endl;
}
