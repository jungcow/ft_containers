#ifndef __THEN_BASE_H__
#define __THEN_BASE_H__

namespace ContainerAssured
{

	template <class Args>
	class ThenBase : public TesterInfo
	{
	private:
		const Args args;  // ParameterPack class
		std::chrono::duration<double> sec;

	protected:
		AssertInfo assertInfo;
		const char* methodname;

	protected:
		ThenBase(const Args& inputArgs, std::chrono::duration<double> timespan, const char* mn)
			: args(inputArgs), sec(timespan), methodname(mn) {}

	protected:
		template <class T = Args>
		typename T::Arg1Type firstParam(typename std::enable_if<!is_lt_one<T>::value>::type* = nullptr)
		{
			return args.firstParam();
		}

		template <class T = Args>
		typename T::Arg2Type secondParam(typename std::enable_if<!is_lt_two<T>::value>::type* = nullptr)
		{
			return args.secondParam();
		}

		template <class T = Args>
		typename T::Arg3Type thridParam(typename std::enable_if<!is_lt_three<T>::value>::type* = nullptr)
		{
			return args.thridParam();
		}

		template <class T = Args>
		typename T::Arg4Type fourthParam(typename std::enable_if<!is_lt_four<T>::value>::type* = nullptr)
		{
			return args.fourthParam();
		}

	public:
		template <class timeunit = std::chrono::duration<double> >
		std::string info()
		{
			std::cout << "[ " << methodname << " ]" << std::endl;
			for (int i = 0; i < assertInfo.assertions.size(); i++)
			{
				std::cout << assertInfo.assertions[i].assertType << " | ";
				std::cout << assertInfo.assertions[i].testname << " | ";
				std::cout << assertInfo.assertions[i].description << " | ";
				if (assertInfo.assertions[i].result == true)
					std::cout << "✅" << std::endl;
				else
					std::cout << "❌" << std::endl;
			}
			if (sec.count() < 0)
				return (std::string("This test doesn't check time duration"));
			return (TesterInfo::info(std::chrono::duration_cast<timeunit>(sec)));
		}
	};
}

#endif