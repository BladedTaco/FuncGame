#pragma once

#ifndef PP__PREPROCESSING

#define PP__NEWLINE
#define PP__DIRECTIVE(...)
#define PP__PRE_DIRECTIVE(...)
#define PP__VA_ARGS__ PP__VA_ARGS__
#else

#define PP__NEWLINE PP__NEWLINE
#define PP__DIRECTIVE(...) PP__NEWLINE PP__DIRECTIVE(__VA_ARGS__) PP__NEWLINE
#define PP__PRE_DIRECTIVE(...) PP__PRE_DIRECTIVE(__VA_ARGS__)
#define PP__VA_ARGS__ PP__VA_ARGS__

#endif


#define _UENUM(...) UENUM(__VA_ARGS__)
#define _USTRUCT(...) USTRUCT(__VA_ARGS__)
#define _UPROPERTY(...) UPROPERTY(__VA_ARGS__)
#define _GENERATED_BODY() GENERATED_BODY()