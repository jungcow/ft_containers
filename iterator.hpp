#ifndef _ITERATOR_H__
#define _ITERATOR_H__

#include <cstddef> // ptrdiff_t
// #include <type_traits>
#include "type_traits.hpp"

namespace ft
{
	/**
	 * iterator_category를 이루는 iterator tag들이다.
	 * 오로지 type을 구분하기 위함으로 사용되고, 따라서 내부는 비어 있다.
	 */
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forword_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forword_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	
	/**
	 * iterator 클래스 템플릿은 타입 정보만을 가지고 있다.
	 */
	template <class Category,
			  class T,
			  class Distance = ptrdiff_t,
			  class Pointer = T *,
			  class Reference = T &>
	class iterator
	{
	public:
		typedef Category		iterator_category;
		typedef T				value_type;
		typedef Distance		difference_type;
		typedef Pointer			pointer;
		typedef Reference		reference;
	};

	/**
	 * iterator_traits 클래스 템플릿은 iterator 클래스 템플릿과 비슷하나 차이점이 있다.
	 * iterator_traits는 특수화를 통해 iterator가 지원하지 않는 범주를 포함한다. 템플릿 인자를 iterator로
	 * 받고 있는 함수에 pointer를 넣게 되면 해당 함수에선 위 iterator에서 제공하는 type들을 사용하려 할 때 
	 * 에러가 발생한다.(이는 pointer에 해당 type들이 정의되지 않았기 때문) 따라서 템플릿 인자로 
	 * iterator_traits를 받아서 해당 pointer에 대한 type들을 정의하여 사용할 수 있도록 한다.
	 */
	template <class Iter>
	struct iterator_traits {
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	/*
	**	pointer or const pointer에 대한 iterator_traits의 specialization
	*/
	template <class T>
	struct iterator_traits<T *> {
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T *							pointer;
		typedef T &							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<const T *> {
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef const T *					pointer;
		typedef const T &					reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	/**
	 * vector 컨테이너가 사용하는 iterator wrapper 클래스 템플릿 이다.
	 * 뭘 위해 있나? => 이는 클래스의 중복되는 정의를 줄이고자 wrapper로 감싼 것 같다.
	 * const와 그냥 iterator가 있으므로, const형 그리고 그냥을 따로 정의해야 할텐데,
	 * 이를 wrapper의 템플릿 인자에 const_pointer 또는 pointer를 넘겨 정의하는 것으로
	 * 해결하였다.
	 */
	template <class Iter>
	class __wrap_iter
	{
	public:
		typedef Iter									iterator_type;
		typedef ft::iterator_traits<iterator_type>		traits_type;
		typedef typename traits_type::iterator_category	iterator_category;
		typedef typename traits_type::value_type		value_type;
		typedef typename traits_type::difference_type	difference_type;
		typedef typename traits_type::pointer			pointer;
		typedef typename traits_type::reference			reference;

	private:
		iterator_type __iter;

	public:
		/**
		 * 	Constructor
		 */
		__wrap_iter() {
			std::cout << "[ Default constructor of iterator ]" << std::endl;
		};
		// TODO: __iter는 단지 data를 가리키고 있을 뿐 -> 따라서 desctructor에서도 할 일이 없나?
		virtual ~__wrap_iter() {
			std::cout << "[ Destructor of iterator ]" << std::endl;
		};

		// TODO: 원본에는 explicit 키워드가 안붙어져 있다.
		// TODO: 인자를 하나만 받을 때는 암시적 변환에 주의해야 하므로 ft 버전엔 붙여줄지 말지 고민해보자.
		explicit __wrap_iter(iterator_type &__x) : __iter(__x) {};

		/**
		 * Copy Constructor
		 * std::enable_if<...>::type* = nullptr
		 * enable_if의 첫번째 템플릿 인자로 true 오고 두번째 인자를 적어주지 않을 때 -> 이 때 두번째 템플릿 인자의
		 * default type이 void이므로 std::enable_if<...>::type* 은 void*가 된다.
		 * 여기서 type이 정의되지 않을 때(enable_if에 false가 전달 될 때) nullptr이 기본 '값'으로 참조된다.
		 */
		template <class _Up>
		__wrap_iter(const __wrap_iter<_Up> &__u, 
			typename std::enable_if<std::is_convertible<_Up, iterator_type>::value>::type* = nullptr) : __iter(__u.base()) {
				std::cout << "[ copy constructor of iterator ]" << std::endl;
				if (typeid(_Up) == typeid(Iter))
					std::cout << "same" << std::endl;
				else 
					std::cout << "diff" << std::endl;
			};

		reference operator*() const { return *__iter;}
		pointer operator->() const { return &(this->operator*()); }
		reference operator[](const int& num) const { return __iter[num]; }


		__wrap_iter& operator++() {
			++__iter;
			return *this;
		}

		__wrap_iter operator++(int) {
			__wrap_iter tmp = *this;
			++(*this);
			return tmp;
		}

		__wrap_iter& operator--() {
			--__iter;
			return *this;
		}

		__wrap_iter operator--(int) {
			__wrap_iter tmp = *this;
			--(*this);
			return tmp;
		}

		iterator_type base(void) const { return __iter; }


	};

	/*
	**	여기의 Iterator 템플릿 인수는 해당 컨테이너에서 쓰이는 iterator를 템플릿 인자로 받아야 한다. -> 이 Iterator가 base가 되므로
	**	-> base를 이용한 operator 오버로딩을 하므로
	*/
	// template <class Iterator>
	// class reverse_iterator : public ft::iterator<typename ft::iterator_traits<Iterator>::Category,
	// 											typename ft::iterator_traits<Iterator>::value_type,
	// 											typename ft::iterator_traits<Iterator>::difference_type,
	// 											typename ft::iterator_traits<Iterator>::pointer,
	// 											typename ft::iterator_traits<Iterator>::reference>
	// {
	// protected:
	// 	Iterator __base;
	// public:
	// 	reverse_iterator() : __base() {};
	// 	virtual ~reverse_iterator() : __base() {};

	// 	template <class OtherIter>
	// 	explicit reverse_iterator(const reverse_iterator<OtherIter>& other) : __base(other.base()) {};

	// 	template <class OtherIter>
	// 	reverse_iterator &operator=(const reverse_iterator<OtherIter>& other) {
	// 		if (this != other)
	// 			__base = other.base();
	// 		return *this;
	// 	}


	// 	//TODO: 왜 reference를 반환하지 않지? reverse_iterator&로 반환하는게 더 낫지 않나?
	// 	//TODO: 왜 const를 붙여주지 않는거지?? 결과값이 상숫값이 안되는 이유는?
	// 	const reverse_iterator operator+(reverse_iterator::difference_type n) const {
	// 		return (__base - n);
	// 	}

	// 	const reverse_iterator operator-(reverse_iterator::difference_type n) const {
	// 		return (__base + n);
	// 	}
		
	// 	const reverse_iterator& operator*

	// 	Iterator &base(void) const {
	// 		return __base;
	// 	}
	// };
	
	// /*
	// ** Non-member overload of reverse_iterator;
	// */
	// template <class Iterator>
	// reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
	// 									const reverse_iterator<Iterator>& rfs) {
	// 	return (rfs + n);
	// }
	// template <class Iterator>
	// typename reverse_iterator<Iterator>::difference_type operator-(
	// 	const reverse_iterator<Iterator>& lhs,
	// 	const reverse_iterator<Iterator>& rfs) {
	// 	return (lhs - rfs);
	// }

};

#endif