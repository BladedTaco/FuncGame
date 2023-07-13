#pragma once

// Forward Declarations

// VStar
class VStar;

// Dataclass Instances
template <class T> class Number;
template <class T> class Maybe;
class Bool;

template <class From, class To> class Func;


template <> class Number<VStar>;
template <> class Maybe<VStar>;

template <typename To> class Func<To, VStar>;


// Dataclass Shorthands
typedef  Number<VStar>  NumberV;
typedef  Maybe<VStar>  MaybeV;

typedef Func<VStar, VStar> ArrV;


// Curried Function Shorthand as Arrow From -> To
template <typename From, typename To>
using Arr = Func<To, From>;


// Typeclass Interfaces
class IOrdinal;
class IFunctor;
class IShow;


// Aggregate Interface
struct Typeclass {
	const IOrdinal* Ordinal;
	const IFunctor* Functor;
	const IShow* Show;
};

// ITypeclass Interface
class ITypeclass {
private:
	virtual const Typeclass* _GetTypeclass() const = 0;
public:
	const Typeclass* GetTypeclass() const { return _GetTypeclass(); };
};
