#ifndef __PARAMETER_PACK_H__
#define __PARAMETER_PACK_H__

#include "type.hpp"
namespace ContainerAssured
{
	template <class Arg1, class Arg2, class Arg3, class Arg4>
	class ParameterPackBase
	{
	private:
		Arg1 __arg1;
		Arg2 __arg2;
		Arg3 __arg3;
		Arg4 __arg4;

	protected:
		ParameterPackBase() {}
		ParameterPackBase(const Arg1& arg1) : __arg1(arg1) {}
		ParameterPackBase(const Arg1& arg1, const Arg2& arg2) : __arg1(arg1), __arg2(arg2) {}
		ParameterPackBase(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3) : __arg1(arg1), __arg2(arg2), __arg3(arg3) {}
		ParameterPackBase(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3, const Arg4& arg4) : __arg1(arg1), __arg2(arg2), __arg3(arg3), __arg4(arg4) {}

		ParameterPackBase(const ParameterPackBase& other)
			: __arg1(other.__arg1), __arg2(other.__arg2), __arg3(other.__arg3), __arg4(other.__arg4) {}

	protected:
		const Arg1 getFirstParam(void) const
		{
			return __arg1;
		}
		const Arg2 getSecondParam(void) const
		{
			return __arg2;
		}
		const Arg3 getThridParam(void) const
		{
			return __arg3;
		}
		const Arg4 getFourthParam(void) const
		{
			return __arg4;
		}
	};

	template <typename Arg1, typename Arg2, typename Arg3, typename Arg4>
	class ParameterPack : private ParameterPackBase<Arg1, Arg2, Arg3, Arg4>
	{
	public:
		static const int num = 4;

		ParameterPack(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3, const Arg4& arg4)
			: ParameterPackBase<Arg1, Arg2, Arg3, Arg4>(arg1, arg2, arg3, arg4) {}

		ParameterPack(const ParameterPack& other)
			: ParameterPackBase<Arg1, Arg2, Arg3, Arg4>(other) {}

		const Arg1 firstParam(void) const
		{
			return this->getFirstParam();
		}
		const Arg2 secondParam(void) const
		{
			return this->getSecondParam();
		}
		const Arg3 thirdParam(void) const
		{
			return this->getThirdParam();
		}
		const Arg4 fourthParam(void) const
		{
			return this->getFourthParam();
		}
	};

	template <typename Arg1, typename Arg2, typename Arg3>
	class ParameterPack<Arg1, Arg2, Arg3, void> : private ParameterPackBase<Arg1, Arg2, Arg3, int>
	{
	public:
		static const int num = 3;

		ParameterPack(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3)
			: ParameterPackBase<Arg1, Arg2, Arg3, int>(arg1, arg2, arg3) {}

		ParameterPack(const ParameterPack& other)
			: ParameterPackBase<Arg1, Arg2, Arg3, int>(other) {}
		const Arg1 firstParam(void) const
		{
			return this->getFirstParam();
		}
		const Arg2 secondParam(void) const
		{
			return this->getSecondParam();
		}
		const Arg3 thirdParam(void) const
		{
			return this->getThirdParam();
		}
	};

	template <typename Arg1, typename Arg2>
	class ParameterPack<Arg1, Arg2, void, void> : private ParameterPackBase<Arg1, Arg2, int, int>
	{
	public:
		static const int num = 2;

		ParameterPack(const Arg1& arg1, const Arg2& arg2)
			: ParameterPackBase<Arg1, Arg2, int, int>(arg1, arg2, 0, 0) {}

		ParameterPack(const ParameterPack& other)
			: ParameterPackBase<Arg1, Arg2, int, int>(other) {}

		const Arg1 firstParam(void) const
		{
			return this->getFirstParam();
		}
		const Arg2 secondParam(void) const
		{
			return this->getSecondParam();
		}
	};

	template <typename Arg1>
	class ParameterPack<Arg1, void, void, void> : private ParameterPackBase<Arg1, int, int, int>
	{
	public:
		static const int num = 1;

		ParameterPack(const Arg1& arg1)
			: ParameterPackBase<Arg1, int, int, int>(arg1, 0, 0, 0) {}
		ParameterPack(const ParameterPack& other)
			: ParameterPackBase<Arg1, int, int, int>(other) {}

		const Arg1 firstParam() const
		{
			return this->getFirstParam();
		}
	};

	template <>
	class ParameterPack<void, void, void, void> : private ParameterPackBase<int, int, int, int>
	{
	public:
		static const int num = 0;
	};

	typedef ParameterPack<void, void, void, void> voidParameterPack;

	template <class Arg1>
	struct OneParameterPack
	{
		typedef ParameterPack<Arg1, void, void, void> type;
	};

	template <class Arg1, class Arg2>
	struct TwoParameterPack
	{
		typedef ParameterPack<Arg1, Arg2, void, void> type;
	};

	template <class Arg1, class Arg2, class Arg3>
	struct ThreeParameterPack
	{
		typedef ParameterPack<Arg1, Arg2, Arg3, void> type;
	};
}

#endif