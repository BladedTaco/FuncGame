#pragma once

#ifndef PP__PREPROCESSING

#include "Templates/SharedPointer.h"

#else

include "Templates/SharedPointer.h"

#endif

// Forward Declarations

// VStar
class VStar;

// Dataclass Instances
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


// Dataclass Shorthands
typedef  Maybe<VStar>  MaybeV;
typedef  List<VStar> ListV;

typedef  Either<VStar, VStar> EitherV;
typedef  Tuple<VStar, VStar> TupleV;

typedef Func<VStar, VStar> ArrV;
typedef Func<Func<VStar, VStar>, VStar> ArrVV;
typedef Func<Func<Func<VStar, VStar>, VStar>, VStar> ArrVVV;


// Curried Function Shorthand as Arrow From -> To
template <typename From, typename To>
using Arr = Func<To, From>;


// Typeclass Interfaces
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


// Aggregate Interface
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


// ITypeclass Interface
class ITypeclass {
private:
	virtual TSharedPtr<const Typeclass> _GetTypeclass() const = 0;
public:
	TSharedPtr<const Typeclass> GetTypeclass() const;
};

TSharedPtr<const Typeclass> NoopPtr(const Typeclass* InTypeclass);