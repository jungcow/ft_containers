#ifndef __ASSERT_BASE_H__
#define __ASSERT_BASE_H__

#include "assert_util.hpp"

namespace ContainerAssured
{
	template <class This>
	class AssertBase
	{
	protected:
		This then;
		AssertInfoBase& assertInfo;
		std::string testname;
		std::string description;

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
		AssertContainer& sizeIs(size_t size)
		{
			this->testname = "Size";
			this->description = std::to_string(container.size()) + "==" + std::to_string(size) + "?";
			this->assertInfo.assertions.push_back(Assertion(this->testname, this->description, container.size() == size));
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
			this->testname = "Capacity";
			this->description = std::to_string(container.capacity()) + "==" + std::to_string(capacity) + "?";

			this->assertInfo.assertions.push_back(Assertion(this->testname, this->description, container.capacity() == capacity));
			return (*this);
		}
		template <class UniPred>
		AssertContainer& capacityIs(typename std::enable_if<!std::is_integral<UniPred>::value, UniPred>::type F)
		{
			this->testname = "Capacity";
			this->assertInfo.assertions.push_back(Assertion(this->testname, "", F(container.capacity())));
			return (*this);
		}

		template <class OtherCont>
		AssertContainer& equalWith(OtherCont input)
		{
			this->testname = "Equivalence";
			this->assertInfo.assertions.push_back(Assertion(this->testname, "", container == input));
			return (*this);
		}
	};

	template <class This, class Ret, class Cont>
	class AssertReturnValue : public AssertBase<This>
	{
	private:
		typedef typename std::remove_reference<Cont>::type Container;

		const Ret& returnValue;
		Container container;

	public:
		AssertReturnValue(This t, ReturnValueAssertInfo& RVAI, const Ret& rv, const Cont& c)
			: AssertBase<This>(t, RVAI), returnValue(rv), container(c) {}

		AssertReturnValue& pointedValue(typename Container::value_type a)
		{
			this->testname = "Pointed Value";
			this->description = std::to_string(*returnValue) + "==" + std::to_string(a) + "?";
			this->assertInfo.assertions.push_back(Assertion(this->testname, this->description, *returnValue == a));
			return (*this);
		}

		template <class T>
		AssertReturnValue& pointedValue(T a, typename std::enable_if<
												 std::is_same<typename std::iterator_traits<T>::iterator_category, std::random_access_iterator_tag>::value ||
												 std::is_same<typename std::iterator_traits<T>::iterator_category, std::bidirectional_iterator_tag>::value ||
												 std::is_same<typename std::iterator_traits<T>::iterator_category, std::forward_iterator_tag>::value ||
												 std::is_same<typename std::iterator_traits<T>::iterator_category, std::input_iterator_tag>::value>::type* = nullptr)
		{
			std::cout << "what is? " << *a << std::endl;
			this->testname = "Iterator pointedValue assertion";
			this->description = std::to_string(*returnValue) + "==" + std::to_string(*a) + "?";
			this->assertInfo.assertions.push_back(Assertion(this->testname, this->description, *returnValue == *a));
			return (*this);
		}

		template <class T, class U = Ret>
		AssertReturnValue& valueIs()
		{
			std::cout << "value assertion" << std::endl;
			return (*this);
		}
		/**
		 * pointedValueIs(Value): this
		 * valueIs(size_t): this
		 * addressIs(Container): this
		 */
	};
}

#endif
