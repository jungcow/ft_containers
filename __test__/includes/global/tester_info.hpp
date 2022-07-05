#ifndef __TESTER_INFO_H__
#define __TESTER_INFO_H__

#include <chrono>
#include <string>
#include <type_traits>

namespace ContainerAssured
{
	typedef std::chrono::milliseconds MILLISECONDS;
	typedef std::chrono::microseconds MICROSECONDS;
	typedef std::chrono::nanoseconds NANOSECONDS;

	class TesterInfo
	{
	private:
		std::string takes;

	public:
		TesterInfo() : takes() {}

	protected:
		std::string info(std::chrono::duration<double> sec)
		{
			std::string info("takes ");

			takes += std::to_string(sec.count());
			takes += "s";
			return takes;
		}

		std::string info(std::chrono::milliseconds ms)
		{
			takes += std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(ms).count());
			takes += "ms";
			return takes;
		}

		std::string info(std::chrono::microseconds us)
		{
			takes += std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(us).count());
			takes += "us";
			return takes;
		}

		std::string info(std::chrono::nanoseconds ns)
		{
			takes += std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(ns).count());
			takes += "ns";
			return takes;
		}
	};
}

#endif
