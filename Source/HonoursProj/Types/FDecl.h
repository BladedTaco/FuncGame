#pragma once

// Forward Declarations

// VStar
class VStar;

// Dataclass Instances
template <class T> class Number;
template <class T> class Maybe;

template <> class Number<VStar>;
template <> class Maybe<VStar>;


// Dataclass Shorthands
typedef  Number<VStar>  NumberV;
typedef  Maybe<VStar>  MaybeV;



// Typeclass Interfaces
class IOrdinal;
class IFunctor;

// Aggregate Interface
struct Typeclass {
	const IOrdinal* Ordinal;
	const IFunctor* Functor;
	//IFunctor* Functor;
};

