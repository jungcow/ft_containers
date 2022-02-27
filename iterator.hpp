#ifndef _ITERATOR_H__
#define _ITERATOR_H__

#include <cstddef> // ptrdiff_t
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


	

	/*
	**	여기의 Iterator 템플릿 인수는 해당 컨테이너에서 쓰이는 iterator를 템플릿 인자로 받아야 한다. -> 이 Iterator가 base가 되므로
	**	-> base를 이용한 operator 오버로딩을 하므로
	*/
	template <class Iterator>
	class reverse_iterator : public ft::iterator<typename ft::iterator_traits<Iterator>::Category,
												typename ft::iterator_traits<Iterator>::value_type,
												typename ft::iterator_traits<Iterator>::difference_type,
												typename ft::iterator_traits<Iterator>::pointer,
												typename ft::iterator_traits<Iterator>::reference>
	{
	protected:
		Iterator __base;
	public:
		reverse_iterator() : __base() {};
		virtual ~reverse_iterator() : __base() {};

		template <class OtherIter>
		reverse_iterator(const reverse_iterator<OtherIter>& other) : __base(other.base()) {};

		template <class OtherIter>
		reverse_iterator &operator=(const reverse_iterator<OtherIter>& other) {
			if (this != other)
				__base = other.base();
			return *this;
		}


		//TODO: 왜 reference를 반환하지 않지? reverse_iterator&로 반환하는게 더 낫지 않나?
		//TODO: 왜 const를 붙여주지 않는거지?? 결과값이 상숫값이 안되는 이유는?
		const reverse_iterator operator+(reverse_iterator::difference_type n) const {
			return (__base - n);
		}

		const reverse_iterator operator-(reverse_iterator::difference_type n) const {
			return (__base + n);
		}
		
		// const reverse_iterator& operator*

		Iterator &base(void) const {
			return __base;
		}
	};
	
	/*
	** Non-member overload of reverse_iterator;
	*/
	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
										const reverse_iterator<Iterator>& rfs) {
		return (rfs + n);
	}
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type
	operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rfs) {
		return (lhs - rfs);
	}

	/**
	 * vector 컨테이너가 사용하는 iterator wrapper 클래스 템플릿 이다.
	 * 뭘 위해 있나? => 이는 클래스의 중복되는 정의를 줄이고자 wrapper로 감싼 것 같다.
	 * const와 그냥 iterator가 있으므로, const형 그리고 그냥을 따로 정의해야 할텐데,
	 * 이를 wrapper의 템플릿 인자에 const_pointer 또는 pointer를 넘겨 정의하는 것으로
	 * 해결하였다. Container를 템플릿 인자로 바는 이유는 Copy Constructor를 보면 알 수 있다.
	 */
	template <class Iter, class Container>
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
		explicit __wrap_iter(iterator_type &other) : __iter(other) {};

		/**
		 * Copy Constructor
		 * ft::is_same의 두번째 템플릿 인자는 복사 생성에 이용하는 iterator의 type을 의미한다.
		 * i) const_iterator = iterator (O)
		 * ii) iterator = const_iterator (X)
		 * 위와 같은 상황을 고려하여 is_same 두번째 인자에 const가 올 때에는 허용을 하도록 해야 한다(위 첫번째 경우에 해당한다.)
		 * _Up는 무조건 비상수 iterator, Container::pointer는 상수든 아니든 Container의 pointer를 가져오기 때문에 비상수.
		 * 때문에 is_same의 value가 1이 되면서 enable_if의 type이 Container로 정의되어 진다.
		 */
		template <class _Up>
		__wrap_iter(const __wrap_iter<_Up, typename ft::enable_if<
				ft::is_same<_Up, typename Container::pointer>::value, Container
			>::type> &other) : __iter(other.base()) {
				std::cout << "[ copy constructor of iterator ]" << std::endl;
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

		/**
		 * 반환값이 상수가 아닌 이유 -> iterator에 iter + n의 반환값을 대입할 수 있어야 하기 때문
		 */
		__wrap_iter operator+(difference_type n) const{
			std::cout << "operator+" << std::endl;
			__wrap_iter tmp = *this;
			tmp += n;
			return tmp;
		}
		__wrap_iter operator-(difference_type n) const{
			std::cout << "operator-" << std::endl;
			__wrap_iter tmp = *this;
			tmp -= n;
			return tmp;
		}

		/**
		 * non-member function으로 해도 될 것 같은데 일단 member function으로 오버로딩 해보자.
		 */
		template <class OtherIter, class Cont>
		typename __wrap_iter<OtherIter, Cont>::difference_type 
		operator-(const __wrap_iter<OtherIter, Cont>& rfs) const{
			std::cout << "iter1 - iter2" << std::endl;
			return this->base() - rfs.base();
		}

		__wrap_iter operator+=(difference_type n) {
			std::cout << "operator+=" << std::endl;
			this->__iter += n;
			return *this;
		}
		__wrap_iter operator-=(difference_type n) {
			std::cout << "operator-=" << std::endl;
			this->__iter -= n;
			return *this;
		}

		const iterator_type& base(void) const {
			return __iter;
		}

		template <class Iter1, class Cont>
		friend __wrap_iter<Iter1, Cont> operator+(typename __wrap_iter<Iter1, Cont>::difference_type n, const __wrap_iter<Iter1, Cont>& iter);

	private:
		/**
		 * 아래의 friend 선언은 __wrap_iter 템플릿으로 만들어질 수 있는 모든 __wrap_iter 클래스들의 private에
		 * 접근하기 위함이다.
		 * 왜 접근하려 하나? -> 아래의 non-member function 때문에
		 * non-member에선 private에 접근할 수 없으므로
		 */
		template <class _Up, class Cont> friend class __wrap_iter;
		
		template <class Iter1, class Iter2, class Cont>
		friend bool operator>(const __wrap_iter<Iter1, Cont>& lhs, const __wrap_iter<Iter2, Cont>& rhs);	
		template <class Iter1, class Iter2, class Cont>
		friend bool operator>=(const __wrap_iter<Iter1, Cont>& lhs, const __wrap_iter<Iter2, Cont>& rhs);	
		template <class Iter1, class Iter2, class Cont>
		friend bool operator==(const __wrap_iter<Iter1, Cont>& lhs, const __wrap_iter<Iter2, Cont>& rhs);	
		template <class Iter1, class Iter2, class Cont>
		friend bool operator<(const __wrap_iter<Iter1, Cont>& lhs, const __wrap_iter<Iter2, Cont>& rhs);	
		template <class Iter1, class Iter2, class Cont>
		friend bool operator<=(const __wrap_iter<Iter1, Cont>& lhs, const __wrap_iter<Iter2, Cont>& rhs);	
		template <class Iter1, class Iter2, class Cont>
		friend bool operator!=(const __wrap_iter<Iter1, Cont>& lhs, const __wrap_iter<Iter2, Cont>& rhs);

		template <class Iter1, class Cont>
		friend __wrap_iter<Iter1, Cont> operator+(typename __wrap_iter<Iter1, Cont>::difference_type n, const __wrap_iter<Iter1, Cont>& iter);
		// template <class Iter, class Cont>
		// friend const __wrap_iter operator+(const int & n, const __wrap_iter<Iter, Cont>& rfs);
	};

	/**
	 * inline specifier는 함수를 호출하는 오버헤드를 절약한다.
	 * inline을 통해 해당 코드에 바로 아래 정의된 함수 코드가 들어가게 된다.(compile-time에)
	 */
	template <class Iter1, class Iter2, class Cont>
	inline bool operator>(const __wrap_iter<Iter1, Cont>& lhs, const __wrap_iter<Iter2, Cont>& rhs) {
		std::cout << "operator >" << std::endl;
		return (lhs.base() > rhs.base());
	}
	template <class Iter1, class Iter2, class Cont>
	inline bool operator>=(const __wrap_iter<Iter1, Cont>& lhs, const __wrap_iter<Iter2, Cont>& rhs) {
		std::cout << "operator >=" << std::endl;

		return (lhs.base() >= rhs.base());
	}
	template <class Iter1, class Iter2, class Cont>
	inline bool operator==(const __wrap_iter<Iter1, Cont>& lhs, const __wrap_iter<Iter2, Cont>& rhs) {
		std::cout << "operator ==" << std::endl;
		return (lhs.base() == rhs.base());
	}
	template <class Iter1, class Iter2, class Cont>
	inline bool operator<(const __wrap_iter<Iter1, Cont>& lhs, const __wrap_iter<Iter2, Cont>& rhs) {
		std::cout << "operator <" << std::endl;
		return (rhs > lhs);
	}
	template <class Iter1, class Iter2, class Cont>
	inline bool operator<=(const __wrap_iter<Iter1, Cont>& lhs, const __wrap_iter<Iter2, Cont>& rhs) {
		std::cout << "operator <=" << std::endl;
		return (rhs >= lhs);
	}
	template <class Iter1, class Iter2, class Cont>
	inline bool operator!=(const __wrap_iter<Iter1, Cont>& lhs, const __wrap_iter<Iter2, Cont>& rhs) {
		std::cout << "operator !=" << std::endl;
		return !(lhs == rhs);
	}

	template <class Iter, class Cont>
	inline __wrap_iter<Iter, Cont> operator+(typename __wrap_iter<Iter, Cont>::difference_type n, const __wrap_iter<Iter, Cont>& iter) {
		std::cout << "non-member operator+" << std::endl;
		return iter + n;
	}
};

#endif