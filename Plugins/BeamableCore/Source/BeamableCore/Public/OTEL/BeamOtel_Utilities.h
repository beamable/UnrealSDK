#pragma once
#include "BeamLogging.h"

class FBeamOtel_Utilities
{
public:
	static void BeamOtelLog(const FString& Message, const ELogVerbosity::Type& VerbosityLevel)
	{
		ANSICHAR StackTrace[65536];
		FPlatformStackWalk::StackWalkAndDump(StackTrace, UE_ARRAY_COUNT(StackTrace), 0);
		
		BeamLoggingMessageHook.ExecuteIfBound(Message, StackTrace, GetOtelLogVerbosityString(VerbosityLevel));
	}

	static FString GetOtelLogVerbosityString(ELogVerbosity::Type Verbosity)
	{
		switch (Verbosity)
		{
		case ELogVerbosity::NoLogging: return TEXT("None");
		case ELogVerbosity::Fatal: return TEXT("Critical");
		case ELogVerbosity::Error: return TEXT("Error");
		case ELogVerbosity::Warning: return TEXT("Warning");
		case ELogVerbosity::Display: return TEXT("Information");
		case ELogVerbosity::Log: return TEXT("Debug");
		case ELogVerbosity::Verbose: return TEXT("Information");
		case ELogVerbosity::VeryVerbose: return TEXT("Information");
		default: return TEXT("None");
		}
	}
};
