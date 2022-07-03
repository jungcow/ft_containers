#ifndef __ASSERT_BASE_H__
#define __ASSERT_BASE_H__

#include <string>
#include <type_traits>  // enable_if

#include "assert_util.hpp"

namespace ContainerAssured
{
	template <class This>
	class AssertBase
	{
	protected:
		This then;
		AssertInfoBase& assertInfo;

	public:
		AssertBase(This t, AssertInfoBase& info) : then(t), assertInfo(info) {}
		This nextAssert(void) { return then; }
	};

	/**
	 * param1: this
	 * param2: assertInfo
	 * param3: container
	 */
	template <class This, class Cont>
	class AssertContainer : public AssertBase<This>
	{
	private:
		const Cont& container;

	public:
		AssertContainer(This t, ContainerAssertInfo& CAI, const Cont& c) : AssertBase<This>(t, CAI), container(c) {}

		template <class C = Cont>
		AssertContainer& sizeIs(typename C::size_type size)
		{
			this->assertInfo.assertions.push_back(Assertion("Size", "", container.size() == size));
			std::cout << "is size " << size << "?" << '\n';
			if (container.size() == size)
				std::cout << "Yes!\n";
			else
				std::cout << "NOOO!\n";
			return (*this);
		}
		template <class UniPred>
		AssertContainer& sizeIs(typename std::enable_if<!std::is_integral<UniPred>::value, UniPred>::type F)
		{
			this->assertInfo.assertions.push_back(Assertion("Size Test", "", F(container.size())));
			return (*this);
		}

		template <class C = Cont>
		AssertContainer& capacityIs(typename C::size_type capacity)
		{
			this->assertInfo.assertions.push_back(Assertion("Capacity", "", container.capacity() == capacity));
			return (*this);
		}
		template <class UniPred>
		AssertContainer& capacityIs(typename std::enable_if<!std::is_integral<UniPred>::value, UniPred>::type F)
		{
			this->assertInfo.assertions.push_back(Assertion("Capacity", "", F(container.capacity())));
			return (*this);
		}

		template <class OtherCont>
		AssertContainer& equalWith(OtherCont input)
		{
			this->assertInfo.assertions.push_back(Assertion("Equal Container", "", container == input));
		}
	};
	template <class This>
	class AssertReturnValue : public AssertBase<This>
	{
	public:
		AssertReturnValue(This t, ReturnValueAssertInfo& RVAI) : AssertBase<This>(t, RVAI) {}
		/**
		 * pointedValueIs(Value): this
		 * valueIs(size_t): this
		 * addressIs(Container): this
		 */
	};
}

#endif
