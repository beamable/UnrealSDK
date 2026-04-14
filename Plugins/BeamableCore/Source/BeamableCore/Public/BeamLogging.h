#pragma once

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamBackend, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamNotifications, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamUserSlots, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamRequestTracker, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamEditor, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamRuntime, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamContent, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamEditorMs, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamMs, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamStats, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamLobby, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamMatchmaking, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamStore, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamParty, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamFriend, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamCli, Log, All);

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnBeamLogging, FString, FString, FString);

class BEAMABLECORE_API FBeamLogging
{
public:
	static FOnBeamLogging BeamLoggingMessageHook;

	
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

	static void BeamOtelLog(FName Category, const FString& Message, ELogVerbosity::Type VerbosityLevel)
	{
		ANSICHAR StackTrace[65536];
		FPlatformStackWalk::StackWalkAndDump(StackTrace, UE_ARRAY_COUNT(StackTrace), 0);
		FLogCategoryName CategoryName = Category;
		if ((CategoryName.ToString().Contains("beam") || Message.Contains("beamable")) && VerbosityLevel <= ELogVerbosity::Type::Warning)
		{
			BeamLoggingMessageHook.Broadcast(Message, StackTrace, GetOtelLogVerbosityString(VerbosityLevel));
		}
	}
};

#define UE_BEAM_LOG_PIE(Context, CategoryName, Verbosity, Format, ...) \
{ \
	UE_LOG(CategoryName, Verbosity, TEXT("%s - %s"), \
		*FBeamPIE_Utilities::BeamLogFormat(Context), *FString::Printf(Format, ##__VA_ARGS__)); \
	FBeamLogging::BeamOtelLog(FName(TEXT(#CategoryName)), FString::Printf(TEXT("%s - %s"), *FBeamPIE_Utilities::BeamLogFormat(Context), *FString::Printf(Format, ##__VA_ARGS__)), ELogVerbosity::Verbosity); \
}


#define UE_BEAM_LOG(CategoryName, Verbosity, Format, ...) \
{ \
	UE_LOG(CategoryName, Verbosity, Format, ##__VA_ARGS__); \
	FBeamLogging::BeamOtelLog(FName(TEXT(#CategoryName)), FString::Printf(TEXT("%s"), *FString::Printf(Format, ##__VA_ARGS__)), ELogVerbosity::Verbosity); \
}

