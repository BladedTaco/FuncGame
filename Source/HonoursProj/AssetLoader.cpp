
#include "AssetLoader_gen.h"

#include "Types/TypeRepr.h"

FAssets* Assets() {
	static FAssets singleton = {};
	return &singleton;
}

