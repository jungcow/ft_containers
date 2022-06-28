#ifndef __TESTER_INFO_H__
#define __TESTER_INFO_H__

#include <chrono>
#include <type_traits>

typedef std::chrono::milliseconds	MILLISECONDS;
typedef std::chrono::microseconds	MICROSECONDS;
typedef std::chrono::nanoseconds	NANOSECONDS;

class TesterInfo
{
protected:
	std::string info(std::chrono::duration<double> sec)
	{
		std::string info("takes ");

		info += std::to_string(sec.count());
		info += " sec";
		return info;
	}

	std::string info(std::chrono::milliseconds ms)
	{
		std::string info("takes ");

		info += std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(ms).count());
		info += " ms";
		return info;
	}

	std::string info(std::chrono::microseconds us)
	{
		std::string info("takes ");

		info += std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(us).count());
		info += " us";
		return info;
	}

	std::string info(std::chrono::nanoseconds ns)
	{
		std::string info("takes ");

		info += std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(ns).count());
		info += " ns";
		return info;
	}
};

#endif