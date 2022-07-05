#ifndef __ASSERT_UTIL_H__
#define __ASSERT_UTIL_H__

#include <string>

namespace ContainerAssured
{
	/**
	 * param1: assert type
	 * param2: test name
	 * param3: description
	 * param4: true or false
	 */
	struct Assertion
	{
		std::string assertType;
		std::string testname;
		std::string description;
		bool result;

		Assertion(const std::string& at, const std::string& name, const std::string& desc, bool rs)
			: assertType(at), testname(name), description(desc), result(rs) {}
	};

	struct AssertInfo
	{
		std::vector<Assertion> assertions;
	};

	// struct ContainerAssertInfo : AssertInfoBase
	// {
	// 	std::vector<Assertion> assertions;
	// };
	// struct ReturnValueAssertInfo : AssertInfoBase
	// {
	// 	std::vector<Assertion> assertions;
	// };
	// struct ParameterAssertInfo : AssertInfoBase
	// {
	// 	std::vector<Assertion> assertions;
	// };
}

#endif