#ifndef __ASSERT_UTIL_H__
#define __ASSERT_UTIL_H__

#include <string>

namespace ContainerAssured
{
	/**
	 * param1: test name
	 * param2: description
	 * param3: true or false
	 */
	struct Assertion
	{
		std::string testname;
		std::string description;
		bool result;

		Assertion(const std::string& name, const std::string& desc, bool rs)
			: testname(name), description(desc), result(rs) {}
	};

	struct AssertInfoBase
	{
		const std::string AssertName;

		std::vector<Assertion> assertions;
		AssertInfoBase(const std::string assertname) : AssertName(assertname) {}
	};

	struct ContainerAssertInfo : AssertInfoBase
	{
		ContainerAssertInfo() : AssertInfoBase("Container Assertion") {}
	};
	struct ReturnValueAssertInfo : AssertInfoBase
	{
		ReturnValueAssertInfo() : AssertInfoBase("Return Value Assertion") {}
	};
	struct ParameterAssertInfo : AssertInfoBase
	{
		ParameterAssertInfo() : AssertInfoBase("Parameter Assertion") {}
	};
}

#endif