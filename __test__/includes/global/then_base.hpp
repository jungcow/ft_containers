#ifndef __THEN_BASE_H__
#define __THEN_BASE_H__

#include <unistd.h>

#include <iomanip>

#include "color.hpp"

using namespace std;

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

	private:
		void printInfoHeader(void)
		{
			cout << '\n'
				 << BLUE;
			cout << left << setw(15) << setfill(' ') << "FUNCTIONS";
			cout << left << setw(15) << setfill(' ') << "ASSERTYPE";
			cout << left << setw(15) << setfill(' ') << "ASSERTION";
			cout << left << setw(15) << setfill(' ') << "RESULT";
			cout << left << setw(15) << setfill(' ') << "TIME";
			cout << "DESCRIPTION";
			cout << RESET << endl;
		}

	public:
		template <class timeunit = std::chrono::duration<double> >
		std::string info()
		{
			string time = (TesterInfo::info(std::chrono::duration_cast<timeunit>(sec)));

			printInfoHeader();
			for (int i = 0; i < assertInfo.assertions.size(); i++)
			{
				cout << left << setw(15) << setfill(' ') << methodname;
				cout << left << setw(15) << setfill(' ') << assertInfo.assertions[i].assertType;
				cout << left << setw(15) << setfill(' ') << assertInfo.assertions[i].testname;
				if (assertInfo.assertions[i].result == true)
				{
					cout << GREEN << "  ";
					cout << left << setw(15) << setfill(' ') << "✔";
					cout << RESET;
				}
				else
				{
					cout << RED << "  ";
					cout << left << setw(15) << setfill(' ') << "✘";
					cout << RESET;
				}
				cout << left << setw(15) << setfill(' ') << time;
				cout << assertInfo.assertions[i].description << endl;
				usleep(100000);
			}
			return time;
		}
	};
}

#endif