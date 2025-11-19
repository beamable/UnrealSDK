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
		if (Message.Contains("beamable") || CategoryString.Contains("beam"))
		{
			GEditor->GetEditorSubsystem<UBeamOTELManagerEditor>()->OtelAddLog(Message, "", VerbosityString);
			// UE_LOG(LogTemp, Warning, TEXT("Intercepted log: [%s] %s - %s"), TEXT(""), *CategoryString, *Message);
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
