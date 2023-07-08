#pragma once

// Forward Declarations

// VStar
class VStar;

// Dataclass Instances

template <class T> class Number;
template <class T> class Maybe;

// Dataclass Aliases
using NumberV = Number<VStar>;
using MaybeV = Number<VStar>;

// Typeclass Interfaces
class IOrdinal;
class IFunctor;

// Aggregate Interface
struct Typeclass {
	const IOrdinal* Ordinal;
	const IFunctor* Functor;
	//IFunctor* Functor;
};

