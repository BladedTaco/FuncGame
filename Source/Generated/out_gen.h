#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
#pragma once








include "Types/VStar.h"

#line 13 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"

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



typedef  Maybe<VStar>  MaybeV;
typedef  List<VStar> ListV;

typedef  Either<VStar, VStar> EitherV;
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
static_assert(is_instance_n<2, ArrVV, Func>, "");

static_assert(!is_instance<int, Number>, "");
static_assert(is_instance<Number<int>, Number>, "");
static_assert(is_instance<Number<X<int>>, Number>, "");
static_assert(is_instance<ArrVV, Func>, "");
static_assert(is_instance<ArrV, Func>, "");
static_assert(is_instance<Arr<VStar, ListV>, Func>, "");
static_assert(is_instance<extract<Arr<VStar, ArrV>, 0>, Func>, "");


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
#line 21 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
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
#line 22 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
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
#line 23 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Semigroup.h"
#pragma once

















#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\Types\\Typeclass\\Semigroup_gen.h"





#pragma once




class ISemigroup {
	public: const Arr<const VStar&, Arr<const VStar&, VStar > > mappend() const { return curry([this]( const VStar& left , const VStar& right ) -> VStar { return this->_mappend ( left, right ); }); }; private: virtual VStar _mappend ( const VStar& left , const VStar& right ) const = 0;
	public: const Arr<const VStar&, Arr<const VStar&, VStar > > stimes() const; private: virtual VStar _stimes ( const VStar& times , const VStar& group ) const ;
};
#line 20 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Semigroup.h"
#line 24 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Foldable.h"
#pragma once
















#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\Types\\Typeclass\\Foldable_gen.h"





#pragma once




#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Monoid_gen.h"





#pragma once





;
class IMonoid : public virtual ISemigroup {
	public: const Arr<void, VStar > mempty() const { return curry([this]( ) -> VStar { return this->_mempty ( ); }); }; private: virtual VStar _mempty ( ) const = 0;
	public: const Arr<const VStar&, VStar > memptyV() const { return curry([this]( const VStar& monoid ) -> VStar { return this->_memptyV ( monoid ); }); }; private: virtual VStar _memptyV ( const VStar& monoid ) const { return monoid.getTypeclass()->Monoid->mempty(); }
};
#line 12 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\Types\\Typeclass\\Foldable_gen.h"
class IFoldable {
	public: const Arr<const VStar&, Arr<const VStar&, Arr<const VStar&, VStar > > > foldr() const { return curry([this]( const VStar& f , const VStar& initial , const VStar& foldable ) -> VStar { return this->_foldr ( f, initial, foldable ); }); }; private: virtual VStar _foldr ( const VStar& f , const VStar& initial , const VStar& foldable ) const = 0;
};
#line 19 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Foldable.h"
#line 25 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
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
#line 26 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
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
#line 27 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
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
#line 28 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Show.h"
#pragma once

















#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\Types\\Typeclass\\Show_gen.h"





#pragma once




class IShow {
	public: const Arr<const VStar&, FString > show() const { return curry([this]( const VStar& a ) -> FString { return this->_show ( a ); }); }; private: virtual FString _show ( const VStar& a ) const = 0;
};
#line 20 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Show.h"
#line 29 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"
#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Read.h"
#pragma once







#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\HonoursProj\\Types\\Typeclass\\Read_gen.h"





#pragma once




class IRead {
};
#line 10 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Typeclass/Read.h"
#line 30 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"

#line 1 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Dataclass/BaseTypes.h"
#pragma once












include "Types/Dataclass/Int_gen.h"
include "Types/Dataclass/Bool_gen.h"
include "Types/Dataclass/Char_gen.h"
include "Types/Dataclass/Float_gen.h"
include "Types/Dataclass/Func_gen.h"

#line 21 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27/Source/HonoursProj\\Types/Dataclass/BaseTypes.h"
#line 32 "S:\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj 4.27\\Source\\Generated\\out_pre.h"

PP__NEWLINE PP__DIRECTIVE(Typeclass, Functor, Either) PP__NEWLINE ;
PP__NEWLINE PP__DIRECTIVE(Typeclass, Applicative, Either) PP__NEWLINE ;
PP__NEWLINE PP__DIRECTIVE(Typeclass, Monad, Either) PP__NEWLINE ;
PP__NEWLINE PP__DIRECTIVE(Typeclass, Semigroup, Either) PP__NEWLINE ;
PP__NEWLINE PP__DIRECTIVE(Typeclass, Foldable, Either) PP__NEWLINE ;
PP__NEWLINE PP__DIRECTIVE(Typeclass, Traversable, Either) PP__NEWLINE ;


PP__NEWLINE PP__DIRECTIVE(Typeclass, Eq, Either) PP__NEWLINE ;
PP__NEWLINE PP__DIRECTIVE(Typeclass, Ordinal, Either) PP__NEWLINE ;
PP__NEWLINE PP__DIRECTIVE(Typeclass, Show, Either) PP__NEWLINE ;
PP__NEWLINE PP__DIRECTIVE(Typeclass, Read, Either) PP__NEWLINE ;


class IEither : public virtual ITypeclass {
private:
	virtual TSharedPtr<const Typeclass> _GetTypeclass() const override {
		return NoopPtr(&Instances);
	}
public:
    PP__NEWLINE class Functor : public virtual IFunctor { PP__NEWLINE private: PP__NEWLINE virtual VStar _fmap(const VStar& f, const VStar& f_a) const override; PP__NEWLINE public: PP__NEWLINE Functor() = default; PP__NEWLINE }; PP__NEWLINE inline static const Functor FunctorInst = {}; ;
    PP__NEWLINE class Applicative : public virtual IApplicative, public virtual Functor { PP__NEWLINE private: PP__NEWLINE virtual VStar _pure(const VStar& value) const override; PP__NEWLINE virtual VStar _apply(const VStar& boxedFunc, const VStar& app) const override; PP__NEWLINE public: PP__NEWLINE Applicative() = default; PP__NEWLINE }; PP__NEWLINE inline static const Applicative ApplicativeInst = {}; ;
    PP__NEWLINE class Monad : public virtual IMonad, public virtual Applicative { PP__NEWLINE private: PP__NEWLINE virtual VStar _bind(const VStar& m_a, const VStar& a_to_mb) const override; PP__NEWLINE public: PP__NEWLINE Monad() = default; PP__NEWLINE }; PP__NEWLINE inline static const Monad MonadInst = {}; ;
    PP__NEWLINE class Semigroup : public virtual ISemigroup { PP__NEWLINE private: PP__NEWLINE virtual VStar _mappend( const VStar& left, const VStar& right) const override; PP__NEWLINE public: PP__NEWLINE Semigroup() = default; PP__NEWLINE }; PP__NEWLINE inline static const Semigroup SemigroupInst = {}; ;
    PP__NEWLINE class Foldable : public virtual IFoldable { PP__NEWLINE private: PP__NEWLINE virtual VStar _foldr(const VStar& f, const VStar& initial, const VStar& foldable) const override; PP__NEWLINE public: PP__NEWLINE Foldable() = default; PP__NEWLINE }; PP__NEWLINE inline static const Foldable FoldableInst = {}; ;
    PP__NEWLINE class Traversable : public virtual ITraversable, public virtual Foldable, public virtual Functor { PP__NEWLINE private: PP__NEWLINE virtual VStar _traverse(const VStar& applic, const VStar& f, const VStar& foldable) const override; PP__NEWLINE public: PP__NEWLINE Traversable() = default; PP__NEWLINE }; PP__NEWLINE inline static const Traversable TraversableInst = {}; ;

    
    
    PP__NEWLINE class Ordinal : public virtual IOrdinal { PP__NEWLINE private: PP__NEWLINE virtual ORD _ord( const VStar& a, const VStar& b) const override; PP__NEWLINE public: PP__NEWLINE Ordinal() = default; PP__NEWLINE }; PP__NEWLINE inline static const Ordinal OrdinalInst = {}; ;
    PP__NEWLINE class Show : public virtual IShow { PP__NEWLINE private: PP__NEWLINE virtual FString _show( const VStar& me) const override; PP__NEWLINE public: PP__NEWLINE Show() = default; PP__NEWLINE }; PP__NEWLINE inline static const Show ShowInst = {}; ;
    

public:
	static const inline Typeclass Instances = []{ Typeclass ${}; $.Functor = &IEither::FunctorInst; $.Applicative = &IEither::ApplicativeInst; $.Monad = &IEither::MonadInst; $.Semigroup = &IEither::SemigroupInst; $.Foldable = &IEither::FoldableInst; $.Traversable = &IEither::TraversableInst; $.Eq = &IEither::OrdinalInst; $.Ordinal = &IEither::OrdinalInst; $.Show = &IEither::ShowInst;; return $; }()











;
};




template <typename Left, typename Right>
class Either : public virtual IEither {
private:
    VStar left;
    VStar right;

    friend IEither;

	friend IEither::Ordinal;
	friend IEither::Show;
	friend IEither::Functor;
	friend IEither::Applicative;
	friend IEither::Monad;
	friend IEither::Semigroup;
	friend IEither::Foldable;
	friend IEither::Traversable;

    Either(Left InLeft, bool ignored) : left(InLeft) {};
    Either(bool ignored, Right InRight) : right(InRight) {};

	virtual TSharedPtr<const Typeclass> _GetTypeclass() const override {
        TSharedPtr<const Typeclass> inner = get().getTypeclass();
        TSharedPtr<Typeclass> out = MakeShareable(new Typeclass());
        *out = IEither::Instances;
        
        if (!inner->Ordinal) out->Ordinal = NULL;
        if (!inner->Eq) out->Eq = NULL;
        if (!inner->Show) out->Show = NULL;

        return out;
	}
public:
	virtual ~Either() = default;

public:
    static Either<Left, Right> AsLeft(Left InLeft) {
        return Either<Left, Right>(InLeft, false);
    }
    static Either<Left, Right> AsRight(Right InRight) {
        return Either<Left, Right>(false, InRight);
    }


public:
    Bool isLeft() const {
        return left.Valid();
    }
    Bool isRight() const {
        return right.Valid();
    };

    Left fromLeft(Left fallback) const {
        return isLeft().get() ? left.ResolveToUnsafe<Left>() : fallback;
    }
    Right fromRight(Right fallback) const {
        return isRight().get() ? right.ResolveToUnsafe<Right>() : fallback;
    }

    VStar get() const {
        return isLeft().get() ? left : right;
    }

	
	Either(const EitherV* other);
};

template <>
class Either<VStar, VStar> : public virtual IEither {
private:
    VStar left;
    VStar right;

    friend IEither;

	friend IEither::Ordinal;
	friend IEither::Show;
	friend IEither::Functor;
	friend IEither::Applicative;
	friend IEither::Monad;
	friend IEither::Semigroup;
	friend IEither::Foldable;
	friend IEither::Traversable;

	template <typename Left, typename Right>
	friend Either<Left, Right>::Either(const EitherV* other);

    Either(VStar InLeft, bool ignored) : left(InLeft) {};
    Either(bool ignored, VStar InRight) : right(InRight) {};
public:
	virtual ~Either() = default;

public:
    template <typename L>
    static EitherV AsLeft(L InLeft) {
        return EitherV(VStar(InLeft), false);
    }
    template <>
    static EitherV AsLeft(VStar InLeft) {
        return EitherV(InLeft, false);
    }

    template <typename R>
    static EitherV AsRight(R InRight) {
        return EitherV(false, VStar(InRight));
    }
    template <>
    static EitherV AsRight(VStar InRight) {
        return EitherV(false, InRight);
    }

public:
    Bool isLeft() const {
        return left.Valid();
    }
    Bool isRight() const {
        return right.Valid();
    };

    template <typename Left>
    Left fromLeft(Left fallback) const {
        return isLeft().get() ? left.ResolveToUnsafe<Left>() : fallback;
    }
    template <>
    VStar fromLeft(VStar fallback) const {
        return isLeft().get() ? left : fallback;
    }

    template <typename Right>
    Right fromRight(Right fallback) const {
        return isRight().get() ? right.ResolveToUnsafe<Right>() : fallback;
    }
    template <>
    VStar fromRight(VStar fallback) const {
        return isRight().get() ? right : fallback;
    }

    VStar get() const {
        return isLeft().get() ? left : right;
    }
}; 

template <typename Left, typename Right>
Either<Left, Right>::Either(const EitherV* other) {
    if (other->isLeft().get()) {
        left = other->get().ResolveToUnsafe<Left>();
    } else {
        right = other->get().ResolveToUnsafe<Right>();
    }
}



template <typename L, typename R>
auto isLeft = curry([](Either<L,R> l_a) -> Bool {
    return l_a.isLeft();
});

template <typename L, typename R>
auto isRight = curry([](Either<L,R> l_a) -> Bool {
    return l_a.isRight();
});

template <typename L, typename R>
auto fromLeft = curry([](Either<L,R> l_a, L a) -> L {
    return l_a.fromLeft(a);
});

template <typename L, typename R>
auto fromRight = curry([](Either<L,R> l_a, R a) -> R {
    return l_a.fromRight(a);
});


inline FString IEither::Show::_show(const VStar& me) const {
	
	EitherV a = me.ResolveToUnsafe<EitherV>();

    return FString(a.isLeft().get() ? "L:" : "R:") + a.get().getTypeclass()->Show->show()(a.get());
}




inline ORD IEither::Ordinal::_ord( const VStar& a, const VStar& b) const {
	EitherV _a = a.ResolveToUnsafe<EitherV>();
	EitherV _b = b.ResolveToUnsafe<EitherV>();

    
    if (_a.isLeft().get() && _b.isRight().get()) return ORD::LT;
    if (_a.isRight().get() && _b.isLeft().get()) return ORD::GT;
    
    
    return _a.get().getTypeclass()->Ordinal->ord()(_a.get())(_b.get());
}


inline VStar IEither::Functor::_fmap(const VStar& f, const VStar& f_a) const {
	
	EitherV m_a = f_a.ResolveToUnsafe<EitherV>();

    
    if (m_a.isLeft().get()) return m_a;

    
	ArrV g = f.ResolveToUnsafe<ArrV>();
    return EitherV::AsRight(g(m_a.get()));
}

inline VStar IEither::Applicative::_pure(const VStar& value) const {
    return EitherV::AsRight(value);
}	

inline VStar IEither::Applicative::_apply(const VStar& boxedFunc, const VStar& app) const {
	EitherV m_a = boxedFunc.ResolveToUnsafe<EitherV>();

    
	if (m_a.isLeft().get()) return m_a;

    
    return app.getTypeclass()->Functor->fmap()(m_a.get())(app);
}

inline  VStar IEither::Monad::_bind(const VStar& m_a, const VStar& a_to_mb) const {
	EitherV _ma = m_a.ResolveToUnsafe<EitherV>();

	if (_ma.isLeft().get()) return _ma;

	ArrV arr = a_to_mb.ResolveToUnsafe<ArrV>();
	return arr(_ma.get());
}

inline VStar IEither::Foldable::_foldr(const VStar& f, const VStar& initial, const VStar& foldable) const {
    EitherV _ma = foldable.ResolveToUnsafe<EitherV>();

    
    if (_ma.isLeft().get()) return initial;

    
	ArrV g = f.ResolveToUnsafe<ArrV>();

    return g(_ma.get()).ResolveToUnsafe<ArrV>()(initial);
}

inline VStar IEither::Traversable::_traverse(const VStar& applic, const VStar& f, const VStar& foldable) const {
    EitherV _ma = foldable.ResolveToUnsafe<EitherV>();

    

    
    if (_ma.isLeft().get()) {
        return applic.getTypeclass()->Applicative->pure()(EitherV::AsLeft(_ma.get()));
    }

    ArrV right = curry([](VStar a) -> VStar { return VStar(EitherV::AsRight(a));});

    
	ArrV g = f.ResolveToUnsafe<ArrV>();
    return _ma.get().getTypeclass()->Functor->fmap()(right)(g(_ma.get()));
}
 
inline VStar IEither::Semigroup::_mappend( const VStar& left, const VStar& right) const {
    EitherV _ma = left.ResolveToUnsafe<EitherV>();

    
    if (_ma.isLeft().get()) return right;
    
    return _ma;
}
