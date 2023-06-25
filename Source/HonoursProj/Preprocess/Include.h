#pragma once

#ifndef PP__PREPROCESSING

#define PP__NEWLINE
#define PP__DIRECTIVE(...)
#define PP__PRE_DIRECTIVE(...)

#else

#define PP__NEWLINE PP__NEWLINE
#define PP__DIRECTIVE(...) PP_DIRECTIVE(__VA_ARGS__)
#define PP__PRE_DIRECTIVE(...) PP__PRE_DIRECTIVE(__VA_ARGS__)

#endif


#define _UENUM(...) UENUM(__VA_ARGS__)