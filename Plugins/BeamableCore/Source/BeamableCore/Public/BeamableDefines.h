#pragma once

#if defined(_MSC_VER) && !defined(__clang__)
	#ifndef BEAM_FUNC_SIG
		#define BEAM_FUNC_SIG __FUNCSIG__
		#define BEAM_FUNC_SIG_STARTCHAR '<'
		#define BEAM_FUNC_SIG_ENDCHAR '>'

		#pragma warning(push)
		#pragma warning(disable : 4503) // "identifier" : decorated name length exceeded, name was truncated
	#endif
#else
	#ifndef BEAM_FUNC_SIG
		#define BEAM_FUNC_SIG __PRETTY_FUNCTION__
		#define BEAM_FUNC_SIG_STARTCHAR '='
		#define BEAM_FUNC_SIG_ENDCHAR ']'
	#endif
#endif
