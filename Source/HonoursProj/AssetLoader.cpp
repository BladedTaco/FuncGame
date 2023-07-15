
#include "AssetLoader_gen.h"

FAssets* Assets() {
	static FAssets singleton = {};
	return &singleton;
}

