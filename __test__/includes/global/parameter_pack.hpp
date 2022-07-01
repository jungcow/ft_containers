#ifndef __PARAMETER_PACK_H__
#define __PARAMETER_PACK_H__

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
		ParameterPackBase(Arg1 arg1) : __arg1(arg1) {}
		ParameterPackBase(Arg1 arg1, Arg2 arg2) : __arg1(arg1), __arg2(arg2) {}
		ParameterPackBase(Arg1 arg1, Arg2 arg2, Arg3 arg3) : __arg1(arg1), __arg2(arg2), __arg3(arg3) {}
		ParameterPackBase(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4) : __arg1(arg1), __arg2(arg2), __arg3(arg3), __arg4(arg4) {}

	protected:
		Arg1 getFirstParam(void) const
		{
			return __arg1;
		}
		Arg2 getSecondParam(void) const
		{
			return __arg2;
		}
		Arg3 getThridParam(void) const
		{
			return __arg3;
		}
		Arg4 getFourthParam(void) const
		{
			return __arg4;
		}
	};

	template <typename Arg1, typename Arg2, typename Arg3, typename Arg4>
	class ParameterPack : private ParameterPackBase<Arg1, Arg2, Arg3, Arg4>
	{
		ParameterPack(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
			: ParameterPackBase<Arg1, Arg2, Arg3, Arg4>(arg1, arg2, arg3, arg4) {}
		Arg1 firstParam(void) const
		{
			return this->getFirstParam();
		}
		Arg2 secondParam(void) const
		{
			return this->getSecondParam();
		}
		Arg3 thirdParam(void) const
		{
			return this->getThirdParam();
		}
		Arg4 fourthParam(void) const
		{
			return this->getFourthParam();
		}
	};

	template <typename Arg1, typename Arg2, typename Arg3>
	class ParameterPack<Arg1, Arg2, Arg3, void> : private ParameterPackBase<Arg1, Arg2, Arg3, int>
	{
	public:
		ParameterPack(Arg1 arg1, Arg2 arg2, Arg3 arg3)
			: ParameterPackBase<Arg1, Arg2, Arg3, int>(arg1, arg2, arg3) {}
		Arg1 firstParam(void) const
		{
			return this->getFirstParam();
		}
		Arg2 secondParam(void) const
		{
			return this->getSecondParam();
		}
		Arg3 thirdParam(void) const
		{
			return this->getThirdParam();
		}
	};

	template <typename Arg1, typename Arg2>
	class ParameterPack<Arg1, Arg2, void, void> : private ParameterPackBase<Arg1, Arg2, int, int>
	{
	public:
		ParameterPack(Arg1 arg1, Arg2 arg2)
			: ParameterPackBase<Arg1, Arg2, int, int>(arg1, arg2) {}
		Arg1 firstParam(void) const
		{
			return this->getFirstParam();
		}
		Arg2 secondParam(void) const
		{
			return this->getSecondParam();
		}
	};

	template <typename Arg1>
	class ParameterPack<Arg1, void, void, void> : private ParameterPackBase<Arg1, int, int, int>
	{
	public:
		ParameterPack(Arg1 arg1)
			: ParameterPackBase<Arg1, int, int, int>(arg1) {}
		Arg1 firstParam(void) const
		{
			return this->getFirstParam();
		}
	};

	template <>
	class ParameterPack<void, void, void, void> : private ParameterPackBase<int, int, int, int>
	{
	};

	typedef ParameterPack<void, void, void, void> voidParameterPack;

	template <class Arg1>
	struct oneParameterPack
	{
		typedef ParameterPack<Arg1, void, void, void> type;
	};

	template <class Arg1, class Arg2>
	struct twoParameterPack
	{
		typedef ParameterPack<Arg1, Arg2, void, void> type;
	};

	template <class Arg1, class Arg2, class Arg3>
	struct threeParameterPack
	{
		typedef ParameterPack<Arg1, Arg2, Arg3, void> type;
	};

}

#endif