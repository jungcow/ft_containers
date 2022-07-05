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
		AssertInfo& assertInfo;
		std::string assertType;
		std::string testname;
		std::string description;

	public:
		AssertBase(This t, AssertInfo& info, const std::string& at) : then(t), assertInfo(info), assertType(at) {}
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
		AssertContainer(This t, AssertInfo& CAI, const Cont& c) : AssertBase<This>(t, CAI, "Container"), container(c) {}

		template <class C = Cont>
		AssertContainer& sizeIs(size_t size)
		{
			this->testname = "Size";
			this->description = std::to_string(container.size()) + " == " + std::to_string(size) + "?";
			this->assertInfo.assertions.push_back(Assertion(this->assertType, this->testname, this->description, container.size() == size));
			return (*this);
		}
		template <class UniPred>
		AssertContainer& sizeIs(typename std::enable_if<!std::is_integral<UniPred>::value, UniPred>::type F)
		{
			this->testname = "Size";
			this->assertInfo.assertions.push_back(Assertion(this->assertType, this->testname, "", F(container.size())));
			return (*this);
		}

		template <class C = Cont>
		AssertContainer& capacityIs(typename C::size_type capacity)
		{
			this->testname = "Capacity";
			this->description = std::to_string(container.capacity()) + " == " + std::to_string(capacity) + "?";
			this->assertInfo.assertions.push_back(Assertion(this->assertType, this->testname, this->description, container.capacity() == capacity));
			return (*this);
		}
		template <class UniPred>
		AssertContainer& capacityIs(typename std::enable_if<!std::is_integral<UniPred>::value, UniPred>::type F)
		{
			this->testname = "Capacity";
			this->assertInfo.assertions.push_back(Assertion(this->assertType, this->testname, "", F(container.capacity())));
			return (*this);
		}

		template <class OtherCont = Cont>
		AssertContainer& equalWith(typename std::enable_if<
								   std::is_same<Cont, OtherCont>::value,
								   OtherCont>::type input)
		{
			this->testname = "Equivalence";
			// this->description = type(container) + " == " + type(input) + "?";
			this->assertInfo.assertions.push_back(Assertion(this->assertType, this->testname, "", container == input));
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
		AssertReturnValue(This t, AssertInfo& RVAI, const Ret& rv, const Cont& c)
			: AssertBase<This>(t, RVAI, "ReturnValue"), returnValue(rv), container(c) {}

		AssertReturnValue& pointedValue(typename Container::value_type a)
		{
			this->testname = "Pointed Value";
			this->description = std::to_string(*returnValue) + " == " + std::to_string(a) + "?";
			this->assertInfo.assertions.push_back(Assertion(this->assertType, this->testname, this->description, *returnValue == a));
			return (*this);
		}

		template <class T>
		AssertReturnValue& pointedValue(T a, typename std::enable_if<
												 std::is_same<typename std::iterator_traits<T>::iterator_category, std::random_access_iterator_tag>::value ||
												 std::is_same<typename std::iterator_traits<T>::iterator_category, std::bidirectional_iterator_tag>::value ||
												 std::is_same<typename std::iterator_traits<T>::iterator_category, std::forward_iterator_tag>::value ||
												 std::is_same<typename std::iterator_traits<T>::iterator_category, std::input_iterator_tag>::value>::type* = nullptr)
		{
			this->testname = "Pointed Value";
			this->description = std::to_string(*returnValue) + " == " + std::to_string(*a) + "?";
			this->assertInfo.assertions.push_back(Assertion(this->assertType, this->testname, this->description, *returnValue == *a));
			return (*this);
		}

		AssertReturnValue& valueIs(Ret a)
		{
			this->testname = "Value";
			this->description = std::to_string(returnValue) + " == " + std::to_string(a) + "?";
			this->assertInfo.assertions.push_back(Assertion(this->assertType, this->testname, this->description, returnValue == a));
			return (*this);
		}
		/**
		 * addressIs(Container): this -> 미정
		 */
	};
}

#endif
