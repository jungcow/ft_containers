#ifndef __VECTOR_INSERT_H__
#define __VECTOR_INSERT_H__

#include "base/method_base.hpp"
#include "base/vector_given_base.hpp"
#include "global/tester_result.hpp"
#include "global/tester_util.hpp"

namespace Test
{
	namespace VectorMethod
	{
		class Insert;
	}

	namespace VectorUtil
	{
		template <class Cont>
		class InsertGiven;
	}
}

template <class Cont>
class Test::VectorUtil::InsertGiven : public Test::Base::VectorGivenBase<Cont>
{
private:
	typedef Test::Base::VectorGivenBase<Cont> __base;

public:
	InsertGiven(Cont& input) : Test::Base::VectorGivenBase<Cont>(input) {}

	Test::TesterResult<typename __base::iterator> when(typename __base::iterator position,
													   typename __base::const_reference val)
	{
		return (Test::TesterUtil<typename __base::iterator>()
					.template impl<Cont,
								   typename __base::const_iterator,
								   typename __base::const_reference>(this->c, &Cont::insert, position, val));
	}

	Test::TesterResult<typename __base::iterator> when(typename __base::iterator position,
													   typename __base::size_type n,
													   typename __base::const_reference val)
	{
		return (Test::TesterUtil<typename __base::iterator>()
					.template impl<Cont,
								   typename __base::const_iterator,
								   typename __base::size_type,
								   typename __base::const_reference>(this->c, &Cont::insert, position, n, val));
	}

	// TODO: exception 관리
	template <class InputIterator>
	Test::TesterResult<typename __base::iterator> when(typename __base::iterator position,
													   typename std::enable_if<
														   !std::is_integral<InputIterator>::value,
														   InputIterator>::type first,
													   InputIterator last)
	{
		std::cout << type(position) << std::endl;
		std::cout << type(first) << std::endl;
		std::cout << type(last) << std::endl;
		return (Test::TesterUtil<typename __base::iterator>()
					.template impl<Cont,
								   typename __base::const_iterator,
								   InputIterator,
								   InputIterator>(this->c, &Cont::insert, position, first, last));
	}
};

class Test::VectorMethod::Insert : public MethodBase
{
public:
	template <class Cont>
	VectorUtil::InsertGiven<Cont> given(Cont& container)
	{
		return (VectorUtil::InsertGiven<Cont>(container));
	}
};

#endif
