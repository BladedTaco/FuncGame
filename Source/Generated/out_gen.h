#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
#pragma once

#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/FDecl.h"
#pragma once







include "Templates/SharedPointer.h"

#line 12 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/FDecl.h"




class VStar;


template <class T> class Number;
template <class T> class Maybe;
class Bool;
class Char;
template <class L, class R> class Either;
class Float;
class Int;
template <class T> class List;
class Ordering;
template <class... Ts> class Tuple;

template <class From, class To> class Func;


template <> class Number<VStar>;
template <> class Maybe<VStar>;

template <> class Either<VStar, VStar>;
template <> class List<VStar>;
template <> class Tuple<VStar, VStar>;

template <typename To> class Func<To, VStar>;



typedef  Number<VStar>  NumberV;
typedef  Maybe<VStar>  MaybeV;

typedef  Either<VStar, VStar> EitherV;
typedef  List<VStar> ListV;
typedef  Tuple<VStar, VStar> TupleV;

typedef Func<VStar, VStar> ArrV;
typedef Func<Func<VStar, VStar>, VStar> ArrVV;
typedef Func<Func<Func<VStar, VStar>, VStar>, VStar> ArrVVV;



template <typename From, typename To>
using Arr = Func<To, From>;



class IOrdinal;
class IFunctor;
class IShow;
class IAlternative;
class IApplicative;
class IBounded;
class IEnum;
class IEq;
class IFoldable;
class IMonad;
class IMonoid;
class INum;
class IRead;
class ISemigroup;
class ITraversable;



struct Typeclass {
	const IOrdinal* Ordinal;
	const IFunctor* Functor;
	const IShow* Show;
	const IAlternative* Alternative;
	const IApplicative* Applicative;
	const IBounded* Bounded;
	const IEnum* Enum;
	const IEq* Eq;
	const IFoldable* Foldable;
	const IMonad* Monad;
	const IMonoid* Monoid;
	const INum* Num;
	const IRead* Read;
	const ISemigroup* Semigroup;
	const ITraversable* Traversable;
};



class ITypeclass {
private:
	virtual TSharedPtr<const Typeclass> _GetTypeclass() const = 0;
public:
	TSharedPtr<const Typeclass> GetTypeclass() const;
};

TSharedPtr<const Typeclass> NoopPtr(const Typeclass* InTypeclass);
#line 4 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"

 






include "Misc/Optional.h"

#line 15 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"

#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Functor.h"
#pragma once
























#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\Types\\Typeclass\\Functor_gen.h"





#pragma once
#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\MacroUtils.h"


#pragma once
#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\LoopMacros.h"


#pragma once














































































































































































































#line 5 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\MacroUtils.h"
















































































































































































   









#line 8 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\Types\\Typeclass\\Functor_gen.h"
#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Functional\\Prelude.h"


#pragma once






include <functional>
include "Functional/curry_gen.h"
#line 13 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Functional\\Prelude.h"
























































































































namespace Prelude {
	
	template <typename A, typename B>
	inline auto constant = curry([](A a, B b) -> A {
		return a;
	});

	
	template <typename A, typename B, typename C>
	inline auto compose = curry([](Arr<B, C> f, Arr<A, B> g, A x) -> C {
		return f(g(x));
	});

	template <typename A>
	inline auto id = curry([](A a) -> A { return a; });

	template <typename A, typename B>
	inline auto swap = curry([](TTuple<A, B> tup) -> TTuple<B, A> {
		return MakeTuple(tup.template Get<1>(), tup.template Get<0>());
	});
};


namespace PreludeV {
	
	inline auto constant = curry([](VStar a, VStar b) -> VStar {
		return a;
	});

	
	inline auto compose = curry([](VStar f, VStar g, VStar x) -> VStar {
		ArrV _f = f.ResolveToUnsafe<ArrV>();
		ArrV _g = g.ResolveToUnsafe<ArrV>();

		return _f(_g(x));
	});

	inline auto id = curry([](VStar a) -> VStar { return a; });

};
#line 9 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\Types\\Typeclass\\Functor_gen.h"
#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Functional\\Typeclass.h"
#pragma once

#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Preprocess/Include.h"
#pragma once














#line 17 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Preprocess/Include.h"






#line 4 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Functional\\Typeclass.h"




































































































































































































#pragma warning(disable: 4250)


#line 10 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\Types\\Typeclass\\Functor_gen.h"
#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types\\Unpack.h"
#pragma once















include <memory>
include <type_traits>

include "Type.h"
include "Types_gen.h"

include "Templates/EnableIf.h"
include "Templates/Tuple.h"

#line 27 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types\\Unpack.h"






template <class, class...>
struct X;



template <typename A, typename>
using to_first = A;


template <typename... Ts>
struct TyTuple {
	template <int idx>
	using get = typename std::tuple_element<idx, std::tuple<Ts..., std::false_type, std::false_type, std::false_type>>::type;

	template <template <typename...> typename T>
	using rewrap = T<Ts...>;

	inline static constexpr int size = sizeof...(Ts);
};


template <>
struct TyTuple<std::false_type> {
	template <int idx>
	using get = std::false_type;

	template <template <typename...> typename T>
	using rewrap = std::false_type;

	inline static constexpr int size = 0;
};

template <typename With, typename... Replace>
using replace = TyTuple<to_first<With, Replace>...>;




template <int Num, template <int> typename F>
struct Recurse {
	template <typename... Rest>
	using R = TyTuple<F<Num>, Rest...>;

	using result = typename Recurse<Num - 1, F>::result::template rewrap<R>;
};

template <template <int> typename F>
struct Recurse<0, F> {
	using result = TyTuple<F<0>>;
};

template <template <int> typename F>
struct Recurse<-1, F> {
	using result = TyTuple<>;
};


template <typename T>
struct FlipTuple_t {
	using type = typename Recurse<T::size - 1, T::template get>::result;
};

 

template <>
struct FlipTuple_t<std::false_type> {
	using type = TyTuple<>;
};


template <typename T>
using FlipTuple = typename FlipTuple_t<T>::type;



template <int N, typename T>
using take_n = FlipTuple<typename Recurse<N - 1, T::template get>::result>;



template <typename T>
struct unwrap_impl : std::false_type {
	using wrapper = std::false_type;
	using wrapper_fill = std::false_type;

	using types = TyTuple<std::false_type>;
	template <typename A>
	using is_only = std::false_type;
};



template<template<typename...> class E, typename... Ts>
struct unwrap_impl<E<Ts...>> : std::true_type {

	template <typename... Rewrap>
	using wrapper = E<Rewrap...>;

	template <typename Rewrap>
	using wrapper_fill = typename replace<Rewrap, Ts...>::template rewrap<E>;


	using types = TyTuple<Ts...>;
	template <typename A>
	using is_only = typename std::is_same< types, replace<A, Ts...> >;
};


template<template<typename> class E, typename T>
struct unwrap_impl<E<T>> : std::true_type {
	template <typename Rewrap>
	using wrapper = E<Rewrap>;
	template <typename Rewrap>
	using wrapper_fill = E<Rewrap>;
	using types = TyTuple<T>;
	template <typename A>
	using is_only = typename std::is_same< types, replace<A, T> >;
};

template<typename T>
using unwrap = typename unwrap_impl<T>::types;

template<typename T, int idx>
using extract = typename unwrap_impl<T>::types::template get<idx>;

template<typename T, template <typename...> typename Wrapper>
using rewrap = typename unwrap_impl<T>::types::template rewrap<Wrapper>;

template<int N, typename T, template <typename...> typename Wrapper>
using rewrap_cut = typename take_n<N, typename unwrap_impl<T>::types>::template rewrap<Wrapper>;

template<typename T, typename... NewInner>
using repack = typename unwrap_impl<T>::template wrapper<NewInner...>;



template<typename T, typename NewInner>
using repack_fill = typename unwrap_impl<T>::template wrapper_fill<NewInner>;

static_assert(std::is_same_v<  repack_fill<X<int, float>, char>, X<char, char> >, "");


template <typename T, typename Inner>
using contains_only = typename unwrap_impl<T>::template is_only<Inner>;


static_assert(contains_only<X<VStar, VStar>, VStar>::value, "");
static_assert(!contains_only<X<VStar, int>, VStar>::value, "");

template <typename T>
struct is_template_t : std::is_base_of< std::true_type, unwrap_impl<T> > {};

template <typename T>
struct not_template_t : std::is_base_of< std::false_type, unwrap_impl<T> > {};




template<typename T>
using is_template = typename is_template_t<T>::value;

template<typename T>
using not_template = typename not_template_t<T>::value;






static_assert(std::is_same_v< int, TyTuple<int, int>::get<0> >, "");
static_assert(std::is_same_v< unwrap<X<int, float>>::get<1>, float >, "");

static_assert(std::is_same_v< repack<X<int, float>, int, float>, X<int, float> >, "");


static_assert(std::is_same_v< repack<X<int, float>, int, float>, unwrap<X<int, float>>::rewrap<X> >, "");


template <typename T, typename U>
inline constexpr bool is_similar = std::is_same<std::remove_const_t<std::remove_reference_t<T>>, U>::value;


static_assert(is_similar<const int&, int>, "");
static_assert(!is_similar<const float&, int>, "");



































template <class T, template <class, class...> class U>
using is_instance_t = typename std::is_same<T, rewrap<T, U> >;





template <class T, template <class, class...> class U>
inline constexpr bool is_instance = is_similar<T, rewrap<T, U> >;





template <int N, class T, template <class, class...> class U>
inline constexpr bool is_instance_n = []() {
	if constexpr (unwrap<T>::size == N) {
		return is_similar<T, rewrap_cut<N, T, U> >;
	}
	return false;
}();








static_assert(!is_instance_n<2, X<int>, X>, "");
static_assert(is_instance_n<2, X<int, int>, X>, "");
static_assert(!is_instance_n<2, X<int, int, int>, X>, "");

static_assert(!is_instance<int, Number>, "");
static_assert(is_instance<Number<int>, Number>, "");
static_assert(is_instance<Number<X<int>>, Number>, "");


static_assert(is_instance<Number<int>, Number>, "");

static_assert(is_template_t<X<int, float>>::value, "");




















class VStar;


template <class T>
typename std::enable_if_t< is_similar<T, VStar>, UTypeConst*>
FromType() {
	return UTypeConst::New(ETypeBase::NONE);
};

template <class T>
typename std::enable_if_t< is_similar<T, void>, UTypeConst*>
FromType() {
	return UTypeConst::New(ETypeBase::NONE);
};


template <class T>
typename std::enable_if_t< is_similar<T, Bool>, UTypeConst*>
FromType() {
	return UTypeConst::New(ETypeBase::BOOL);
};

template <class T>
typename std::enable_if_t< is_similar<T, Int>, UTypeConst*>
FromType() {
	return UTypeConst::New(ETypeBase::INT);
};


template <class T>
typename std::enable_if_t< is_similar<T, float>, UTypeConst*>
FromType() {
	return UTypeConst::New(ETypeBase::FLOAT);
};









template <class T>
typename std::enable_if_t< is_instance_n<1, T, Maybe>, UTypeConst*>
FromType() {
	using T_0 = extract<T, 0>;
	return UTypeConst::New(ETypeData::MAYBE, { FromType<T_0>() });
};

template <class T>
typename std::enable_if_t< is_instance_n<2, T, Func>, UTypeConst*>
FromType() {
	using From = extract<T, 1>;
	using To = extract<T, 0>;
	return UTypeConst::New(ETypeData::FUNC, { FromType<From>(), FromType<To>() });
};

template <class T>
typename std::enable_if_t< is_instance_n<1, T, List>, UTypeConst*>
FromType() {
	using T_0 = extract<T, 0>;
	return UTypeConst::New(ETypeData::LIST, { FromType<T_0>() });
};

template <class T>
typename std::enable_if_t< is_instance_n<2, T, Either>, UTypeConst*>
FromType() {
	using Left = extract<T, 0>;
	using Right = extract<T, 1>;
	return UTypeConst::New(ETypeData::EITHER, { FromType<Left>(), FromType<Right>() });
};


#line 11 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\Types\\Typeclass\\Functor_gen.h"
class IFunctor {
	public: const Arr<const VStar&, Arr<const VStar&, VStar > > fmap() const { return curry([this]( const VStar& f , const VStar& f_a ) -> VStar { return this->_fmap ( f, f_a ); }); }; private: virtual VStar _fmap ( const VStar& f , const VStar& f_a ) const = 0;
	public: const Arr<const VStar&, Arr<const VStar&, VStar > > map_replace_by() const { return curry([this]( const VStar& a , const VStar& f_b ) -> VStar { return this->_map_replace_by ( a, f_b ); }); }; private: virtual VStar _map_replace_by ( const VStar& a , const VStar& f_b ) const { 
		Arr<VStar, VStar> f = { PreludeV::constant(a) };
		return _fmap(f, f_b);
	};
};
#line 27 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Functor.h"
#line 17 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Applicative.h"
#pragma once















#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\Types\\Typeclass\\Applicative_gen.h"





#pragma once





;
class IApplicative : public virtual IFunctor {
	public: const Arr<const VStar&, VStar > pure() const { return curry([this]( const VStar& value ) -> VStar { return this->_pure ( value ); }); }; private: virtual VStar _pure ( const VStar& value ) const = 0;
	public: const Arr<const VStar&, Arr<const VStar&, VStar > > apply() const { return curry([this]( const VStar& boxedFunc , const VStar& app ) -> VStar { return this->_apply ( boxedFunc, app ); }); }; private: virtual VStar _apply ( const VStar& boxedFunc , const VStar& app ) const = 0; 
	public: const Arr<const VStar&, Arr<const VStar&, Arr<const VStar&, VStar > > > liftA2() const { return curry([this]( const VStar& ternary , const VStar& boxA , const VStar& boxB ) -> VStar { return this->_liftA2 ( ternary, boxA, boxB ); }); }; private: virtual VStar _liftA2 ( const VStar& ternary , const VStar& boxA , const VStar& boxB ) const {
		VStar f_b = fmap()(ternary)(boxA);
		return apply()(f_b)(boxB);
	};
	public: const Arr<const VStar&, Arr<const VStar&, VStar > > leftApply() const { return curry([this]( const VStar& discard , const VStar& keep ) -> VStar { return this->_leftApply ( discard, keep ); }); }; private: virtual VStar _leftApply ( const VStar& discard , const VStar& keep ) const {
		return liftA2()(PreludeV::constant)(discard)(keep);
	};
	public: const Arr<const VStar&, Arr<const VStar&, VStar > > rightApply() const { return curry([this]( const VStar& keep , const VStar& discard ) -> VStar { return this->_rightApply ( keep, discard ); }); }; private: virtual VStar _rightApply ( const VStar& keep , const VStar& discard ) const {
		VStar f_a = map_replace_by()(PreludeV::id)(discard);
		return apply()(f_a)(keep);
	}
}
#line 18 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Applicative.h"
#line 18 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Monad.h"
#pragma once

















#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\Types\\Typeclass\\Monad_gen.h"





#pragma once





;
class IMonad : public virtual IApplicative {
	public: const Arr<const VStar&, Arr<const VStar&, VStar > > bind() const { return curry([this]( const VStar& m_a , const VStar& a_to_mb ) -> VStar { return this->_bind ( m_a, a_to_mb ); }); }; private: virtual VStar _bind ( const VStar& m_a , const VStar& a_to_mb ) const = 0;
	public: const Arr<const VStar&, Arr<const VStar&, VStar > > then() const { return curry([this]( const VStar& m_a , const VStar& m_b ) -> VStar { return this->_then ( m_a, m_b ); }); }; private: virtual VStar _then ( const VStar& m_a , const VStar& m_b ) const {
		return bind()(m_a)(PreludeV::constant(m_b));
	}
	public: const Arr<const VStar&, VStar > mpure() const { return curry([this]( const VStar& value ) -> VStar { return this->_mpure ( value ); }); }; private: virtual VStar _mpure ( const VStar& value ) const {
		return pure()(value);
	}
};
#line 20 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Monad.h"
#line 19 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Semigroup.h"
#pragma once

















#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\Types\\Typeclass\\Semigroup_gen.h"





#pragma once




class ISemigroup {
	public: const Arr<const VStar&, Arr<const VStar&, VStar > > mappend() const { return curry([this]( const VStar& left , const VStar& right ) -> VStar { return this->_mappend ( left, right ); }); }; private: virtual VStar _mappend ( const VStar& left , const VStar& right ) const = 0;
	public: const Arr<const VStar&, Arr<const VStar&, VStar > > stimes() const; private: virtual VStar _stimes ( const VStar& times , const VStar& group ) const ;
};
#line 20 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Semigroup.h"
#line 20 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Monoid.h"
#pragma once
















#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\Types\\Typeclass\\Monoid_gen.h"





#pragma once





;
class IMonoid : public virtual ISemigroup {
	public: const Arr<void, VStar > mempty() const { return curry([this]( ) -> VStar { return this->_mempty ( ); }); }; private: virtual VStar _mempty ( ) const = 0;
	public: const Arr<const VStar&, VStar > memptyV() const { return curry([this]( const VStar& monoid ) -> VStar { return this->_memptyV ( monoid ); }); }; private: virtual VStar _memptyV ( const VStar& monoid ) const { return monoid.getTypeclass()->Monoid->mempty(); }
};
#line 19 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Monoid.h"
#line 21 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Foldable.h"
#pragma once
















#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\Types\\Typeclass\\Foldable_gen.h"





#pragma once





class IFoldable {
	public: const Arr<const VStar&, Arr<const VStar&, Arr<const VStar&, VStar > > > foldr() const { return curry([this]( const VStar& f , const VStar& initial , const VStar& foldable ) -> VStar { return this->_foldr ( f, initial, foldable ); }); }; private: virtual VStar _foldr ( const VStar& f , const VStar& initial , const VStar& foldable ) const = 0;
};
#line 19 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Foldable.h"
#line 22 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Traversable.h"
#pragma once















#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\Types\\Typeclass\\Traversable_gen.h"





#pragma once






;
class ITraversable : public virtual IFoldable, public virtual IFunctor {
	public: const Arr<const VStar&, Arr<const VStar&, Arr<const VStar&, VStar > > > traverse() const { return curry([this]( const VStar& applic , const VStar& f , const VStar& foldable ) -> VStar { return this->_traverse ( applic, f, foldable ); }); }; private: virtual VStar _traverse ( const VStar& applic , const VStar& f , const VStar& foldable ) const = 0;
	public: const Arr<const VStar&, Arr<const VStar&, VStar > > sequenceA() const { return curry([this]( const VStar& applic , const VStar& foldable ) -> VStar { return this->_sequenceA ( applic, foldable ); }); }; private: virtual VStar _sequenceA ( const VStar& applic , const VStar& foldable ) const {
		return traverse()(PreludeV::id)(foldable);
	};
};
#line 18 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Traversable.h"
#line 23 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Alternative.h"
#pragma once





#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\Types\\Typeclass\\Alternative_gen.h"





#pragma once





;
class IAlternative : public virtual IApplicative {
};
#line 8 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Alternative.h"
#line 24 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Eq.h"
#pragma once















#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\Types\\Typeclass\\Eq_gen.h"





#pragma once




;
class IEq {
	public: const Arr<const VStar&, Arr<const VStar&, Bool > > eq() const; private: virtual Bool _eq ( const VStar& a , const VStar& b ) const = 0;
	public: const Arr<const VStar&, Arr<const VStar&, Bool > > neq() const; private: virtual Bool _neq ( const VStar& a , const VStar& b ) const ;
};
#line 18 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Eq.h"
#line 25 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Ordinal.h"
#pragma once















#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\Types\\Typeclass\\Ordinal_gen.h"





#pragma once




enum class ORD : int {
	LT = -1,
	EQ = 0,
	GT = 1
};
class IOrdinal : public virtual IEq {
	public: const Arr<const VStar&, Arr<const VStar&, ORD > > ord() const; private: virtual ORD _ord ( const VStar& a , const VStar& b ) const = 0;
	public: const Arr<const VStar&, Arr<const VStar&, Bool > > lt() const; private: virtual Bool _lt ( const VStar& a , const VStar& b ) const ;
	public: const Arr<const VStar&, Arr<const VStar&, Bool > > lte() const; private: virtual Bool _lte ( const VStar& a , const VStar& b ) const ;
	public: const Arr<const VStar&, Arr<const VStar&, Bool > > gt() const; private: virtual Bool _gt ( const VStar& a , const VStar& b ) const ;
	public: const Arr<const VStar&, Arr<const VStar&, Bool > > gte() const; private: virtual Bool _gte ( const VStar& a , const VStar& b ) const ;
	public: const Arr<const VStar&, Arr<const VStar&, VStar > > min() const; private: virtual VStar _min ( const VStar& a , const VStar& b ) const ;
	public: const Arr<const VStar&, Arr<const VStar&, VStar > > max() const; private: virtual VStar _max ( const VStar& a , const VStar& b ) const ;
	private: virtual Bool _eq ( const VStar& a , const VStar& b ) const override ;
	private: virtual Bool _neq ( const VStar& a , const VStar& b ) const override ;
};
#line 18 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Ordinal.h"
#line 26 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Show.h"
#pragma once

















#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\Types\\Typeclass\\Show_gen.h"





#pragma once




class IShow {
	public: const Arr<const VStar&, FString > show() const { return curry([this]( const VStar& a ) -> FString { return this->_show ( a ); }); }; private: virtual FString _show ( const VStar& a ) const = 0;
};
#line 20 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Show.h"
#line 27 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Read.h"
#pragma once







#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\Types\\Typeclass\\Read_gen.h"





#pragma once




class IRead {
};
#line 10 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Read.h"
#line 28 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"

PP__NEWLINE PP__DIRECTIVE(Typeclass, Functor, List) PP__NEWLINE ;
PP__NEWLINE PP__DIRECTIVE(Typeclass, Applicative, List) PP__NEWLINE ;
PP__NEWLINE PP__DIRECTIVE(Typeclass, Monad, List) PP__NEWLINE ;

PP__NEWLINE PP__DIRECTIVE(Typeclass, Semigroup, List) PP__NEWLINE ;
PP__NEWLINE PP__DIRECTIVE(Typeclass, Monoid, List) PP__NEWLINE ;

PP__NEWLINE PP__DIRECTIVE(Typeclass, Foldable, List) PP__NEWLINE ;
PP__NEWLINE PP__DIRECTIVE(Typeclass, Traversable, List) PP__NEWLINE ;

PP__NEWLINE PP__DIRECTIVE(Typeclass, Alternative, List) PP__NEWLINE ;


PP__NEWLINE PP__DIRECTIVE(Typeclass, Eq, List) PP__NEWLINE ;
PP__NEWLINE PP__DIRECTIVE(Typeclass, Ordinal, List) PP__NEWLINE ;
PP__NEWLINE PP__DIRECTIVE(Typeclass, Show, List) PP__NEWLINE ;
PP__NEWLINE PP__DIRECTIVE(Typeclass, Read, List) PP__NEWLINE ;



class IList : public virtual ITypeclass {
private:
	virtual TSharedPtr<const Typeclass> _GetTypeclass() const override {
		return NoopPtr(&Instances);
	}
public:
	PP__NEWLINE class Functor : public virtual IFunctor { PP__NEWLINE private: PP__NEWLINE virtual VStar _fmap(const VStar& f, const VStar& f_a) const override; PP__NEWLINE public: PP__NEWLINE Functor() = default; PP__NEWLINE }; PP__NEWLINE inline static const Functor FunctorInst = {}; ;
    PP__NEWLINE class Applicative : public virtual IApplicative, public virtual Functor { PP__NEWLINE private: PP__NEWLINE virtual VStar _pure(const VStar& value) const override; PP__NEWLINE virtual VStar _apply(const VStar& boxedFunc, const VStar& app) const override; PP__NEWLINE public: PP__NEWLINE Applicative() = default; PP__NEWLINE }; PP__NEWLINE inline static const Applicative ApplicativeInst = {}; ;
    PP__NEWLINE class Monad : public virtual IMonad, public virtual Applicative { PP__NEWLINE private: PP__NEWLINE virtual VStar _bind(const VStar& m_a, const VStar& a_to_mb) const override; PP__NEWLINE public: PP__NEWLINE Monad() = default; PP__NEWLINE }; PP__NEWLINE inline static const Monad MonadInst = {}; ;

    PP__NEWLINE class Semigroup : public virtual ISemigroup { PP__NEWLINE private: PP__NEWLINE virtual VStar _mappend( const VStar& left, const VStar& right) const override; PP__NEWLINE public: PP__NEWLINE Semigroup() = default; PP__NEWLINE }; PP__NEWLINE inline static const Semigroup SemigroupInst = {}; ;
    PP__NEWLINE class Monoid : public virtual IMonoid, public virtual Semigroup { PP__NEWLINE private: PP__NEWLINE virtual VStar _mempty() const override; PP__NEWLINE public: PP__NEWLINE Monoid() = default; PP__NEWLINE }; PP__NEWLINE inline static const Monoid MonoidInst = {}; ;

    PP__NEWLINE class Foldable : public virtual IFoldable { PP__NEWLINE private: PP__NEWLINE virtual VStar _foldr(const VStar& f, const VStar& initial, const VStar& foldable) const override; PP__NEWLINE public: PP__NEWLINE Foldable() = default; PP__NEWLINE }; PP__NEWLINE inline static const Foldable FoldableInst = {}; ;
    PP__NEWLINE class Traversable : public virtual ITraversable, public virtual Foldable, public virtual Functor { PP__NEWLINE private: PP__NEWLINE virtual VStar _traverse(const VStar& applic, const VStar& f, const VStar& foldable) const override; PP__NEWLINE public: PP__NEWLINE Traversable() = default; PP__NEWLINE }; PP__NEWLINE inline static const Traversable TraversableInst = {}; ;

    

    
    
    PP__NEWLINE class Ordinal : public virtual IOrdinal { PP__NEWLINE private: PP__NEWLINE virtual ORD _ord( const VStar& a, const VStar& b) const override; PP__NEWLINE public: PP__NEWLINE Ordinal() = default; PP__NEWLINE }; PP__NEWLINE inline static const Ordinal OrdinalInst = {}; ;
    PP__NEWLINE class Show : public virtual IShow { PP__NEWLINE private: PP__NEWLINE virtual FString _show( const VStar& me) const override; PP__NEWLINE public: PP__NEWLINE Show() = default; PP__NEWLINE }; PP__NEWLINE inline static const Show ShowInst = {}; ;
    

public:
	static const inline Typeclass Instances = []{ Typeclass ${}; $.Functor = &IList::FunctorInst; $.Applicative = &IList::ApplicativeInst; $.Monad = &IList::MonadInst; $.Semigroup = &IList::SemigroupInst; $.Monoid = &IList::MonoidInst; $.Foldable = &IList::FoldableInst; $.Traversable = &IList::TraversableInst; $.Eq = &IList::OrdinalInst; $.Ordinal = &IList::OrdinalInst; $.Show = &IList::ShowInst;; return $; }()













;
};





template <typename A>
class List : public virtual IList {
private:
    VStar _head;
    VStar _rest;
    VStar _next;

	friend IList::Ordinal;
	friend IList::Show;
	friend IList::Functor;
	friend IList::Applicative;
	friend IList::Monad;
	friend IList::Monoid;
	friend IList::Semigroup;
	friend IList::Foldable;
	friend IList::Traversable;
	friend ListV;

	virtual TSharedPtr<const Typeclass> _GetTypeclass() const override {
        
        if (isEmpty().get()) return NoopPtr(&IList::Instances); 

        
        TSharedPtr<Typeclass> out = MakeShareable(new Typeclass());
        *out = IList::Instances;
         
        
        auto inner = _head.getTypeclass();
        if (!inner->Ordinal) out->Ordinal = NULL;
        if (!inner->Eq) out->Eq = NULL;
        if (!inner->Show) out->Show = NULL;

        return out;
	}
public:
	virtual ~List() = default;

    List(){};
    List(A InHead, List<A> InRest)
        : _head(InHead)
        , _rest(InRest)
    {};
    List(A seed, Arr<A, A> InNext)
        : _head(seed)
        , _next(InNext)
    {};

public:
    Bool isEmpty() const { return !_head.Valid(); }
    Bool isInfinite() const { return _next.Valid(); }
    A head(A fallback) {
        return isEmpty().get() ? fallback : _head.ResolveToUnsafe<A>();
	}
    List<A> rest() {
        
        if (_rest.Valid()) return _rest.ResolveToUnsafe<List<A>>();
        
        if (!_next.Valid()) return List();
        
        ArrV nex = _next.ResolveToUnsafe<ArrV>();
        return List(nex(_head), nex);
    }

	
	List(const ListV* other);
};



template <>
class List<VStar> : public virtual IList {
private:
    VStar _head;
    VStar _rest;
    VStar _next;

	friend IList::Ordinal;
	friend IList::Show;
	friend IList::Functor;
	friend IList::Applicative;
	friend IList::Monad;
	friend IList::Semigroup;
	friend IList::Foldable;
	friend IList::Traversable;
	friend ListV;

	template <typename A>
	friend List<A>::List(const ListV* other);
public:
	virtual ~List() = default;

    List(){};
    List(VStar InHead, ListV InRest)
        : _head(InHead)
        , _rest(InRest)
    {};
    List(VStar seed, ArrV InNext)
        : _head(seed)
        , _next(InNext)
    {};

public:
    Bool isEmpty() const { return !_head.Valid(); }
    Bool isInfinite() const { return _next.Valid(); }
    template <typename A>
    A head(A fallback) {
        return isEmpty().get() ? fallback : _head.ResolveToUnsafe<A>();
	}  
    template <>
    VStar head(VStar fallback) {
        return isEmpty().get()  ? fallback : _head;
	}
    template <typename A = VStar>
    List<A> rest() {
        
        if (_rest.Valid()) return _rest.ResolveToUnsafe<List<A>>();
        
        if (!_next.Valid()) return List();
        
        ArrV nex = _next.ResolveToUnsafe<ArrV>();
        return List(nex(_head), nex);
    }

	
	List(const ListV* other);
};

template <typename A>
List<A>::List(const ListV* other) {
    _head = other->_head;
    _rest = other->_rest;
    _next = other->_next;
}

template <typename A>
auto isEmpty = curry([](List<A> l_a) -> Bool {
    return l_a.isEmpty();
});

template <typename A>
auto isInfinite = curry([](List<A> l_a) -> Bool {
    return l_a.isInfinite();
});

template <typename A>
auto head = curry([](List<A> l_a, A a) -> A {
    return l_a.head(a);
});

template <typename A>
auto rest = curry([](List<A> l_a, A a) -> A {
    return l_a.rest(a);
});

template <typename A = VStar>
auto cons = curry([](A value, List<A> list) {
    return List<A>(value, list);
});
auto consV = curry([](VStar headV, VStar listV) {
    return ListV(headV, listV.ResolveToUnsafe<ListV>());
}); 
 
inline FString IList::Show::_show(const VStar& a) const {
	
	ListV m_a = a.ResolveToUnsafe<ListV>();

	
	return m_a.isEmpty().get()
		? FString(TEXT("[]"))
        : FString::Format(TEXT("[{0}, ...]"), { m_a._head.getTypeclass()->Show->show()(m_a._head) });
}





inline ORD IList::Ordinal::_ord( const VStar& a, const VStar& b) const {
	ListV _a = a.ResolveToUnsafe<ListV>();
	ListV _b = b.ResolveToUnsafe<ListV>();

    
    int _ae = _a.isEmpty().get();
    int _be = _b.isEmpty().get();
    if (_ae || _be) return ORD(_be - _ae);

    
    ORD order = _a.head(VStar()).getTypeclass()->Ordinal->ord()(_a.head(VStar()))(_b.head(VStar()));
    return order != ORD::EQ ? order : ord()(VStar(_a.rest()))(VStar(_b.rest()));
}



inline VStar IList::Functor::_fmap(const VStar& f, const VStar& f_a) const {
	
	ListV l_a = f_a.ResolveToUnsafe<ListV>();

    
    if (l_a.isEmpty().get()) return ListV();

    
	ArrV g = f.ResolveToUnsafe<ArrV>();
    return VStar(ListV(g(l_a._head), fmap()(f)(l_a.rest()).ResolveToUnsafe<ListV>()));
}


inline VStar IList::Applicative::_pure(const VStar& value) const {
    return ListV(value, ListV());
}	

inline VStar IList::Applicative::_apply(const VStar& boxedFunc, const VStar& app) const {
	ListV m_a = boxedFunc.ResolveToUnsafe<ListV>();
	ListV _app = app.ResolveToUnsafe<ListV>();

    
	if (m_a.isEmpty().get() || _app.isEmpty().get()) return m_a;

    
    return boxedFunc.getTypeclass()->Semigroup->mappend()
        (fmap()(m_a._head)(app))    
        (apply()(m_a.rest())(app)); 
}

inline  VStar IList::Monad::_bind(const VStar& m_a, const VStar& a_to_mb) const {
	ListV _ma = m_a.ResolveToUnsafe<ListV>();

	if (_ma.isEmpty().get()) return _ma;

	ArrV arr = a_to_mb.ResolveToUnsafe<ArrV>();

    
    return m_a.getTypeclass()->Semigroup->mappend()
        (arr(_ma._head))    
        (bind()(_ma.rest())(a_to_mb)); 
}

inline VStar IList::Foldable::_foldr(const VStar& f, const VStar& initial, const VStar& foldable) const {
    ListV _ma = foldable.ResolveToUnsafe<ListV>();

    
    if (_ma.isEmpty().get()) return initial;

    
	ArrV g = f.ResolveToUnsafe<ArrV>();

    
    return g(_ma._head).ResolveToUnsafe<ArrV>()(foldr()(f)(initial)(_ma.rest()));
}

inline VStar IList::Traversable::_traverse( const VStar& applic, const VStar& f, const VStar& foldable) const {
    ListV _ma = foldable.ResolveToUnsafe<ListV>();
	ArrV g = f.ResolveToUnsafe<ArrV>();

    ArrVV t = curry([](VStar _a, VStar _b) -> VStar { return VStar();});

    

    
    
    

    ArrV cons_f2 = t.ToArrV();

    return foldr()
        (cons_f2)
        (applic.getTypeclass()->Applicative->pure()(ListV()))
        (_ma);
}


inline VStar IList::Semigroup::_mappend( const VStar& left, const VStar& right) const {
    ListV _ma = left.ResolveToUnsafe<ListV>();

    
    if (_ma.isEmpty().get()) return right;

    
    return cons<VStar>(_ma._head)(mappend()(_ma.rest())(right));
}

inline VStar IList::Monoid::_mempty() const {
    return ListV();
}
