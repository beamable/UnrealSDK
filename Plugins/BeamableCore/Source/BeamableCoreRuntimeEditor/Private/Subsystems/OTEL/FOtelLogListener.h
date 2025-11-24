#pragma once
#include "BeamOTELManagerEditor.h"


class FOtelLogListener : public FOutputDevice
{
public:

	virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category) override
	{
		FString Message(V);
       
		FString VerbosityString = GetOtelLogVerbosityString(Verbosity);
		FString CategoryString = Category.ToString();

#if WITH_EDITOR
		
		if ((Message.Contains("beamable") || Message.Contains("beam")) && Verbosity <= ELogVerbosity::Warning)
		{
			ANSICHAR StackTrace[65536];
			FPlatformStackWalk::StackWalkAndDump(StackTrace, UE_ARRAY_COUNT(StackTrace), 0);

			GEditor->GetEditorSubsystem<UBeamOTELManagerEditor>()->OtelAddLog(Message, ANSI_TO_TCHAR(StackTrace), VerbosityString);
		}
#endif
	}

private:
	FString GetOtelLogVerbosityString(ELogVerbosity::Type Verbosity)
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
