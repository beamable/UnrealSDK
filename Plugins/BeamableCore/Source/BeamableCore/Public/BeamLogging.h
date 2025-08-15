#pragma once

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamBackend, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamNotifications, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamUserSlots, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamRequestTracker, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamEditor, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamRuntime, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamContent, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamMicroservices, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamStats, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamLobby, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamMatchmaking, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamStore, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamParty, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamFriend, Log, All);

BEAMABLECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogBeamCli, Log, All);

#define UE_BEAM_LOG(Ctx, CategoryName, Verbosity, Format, ...) \
{ \
	UE_LOG(CategoryName, Verbosity, TEXT("%s - %s"), \
		*FString::Printf(TEXT("[Index: %d, IsServer: %d, NetMode: %d]"), FBeamPIE_Utilities::GetPIEInstance(Ctx), \
		FBeamPIE_Utilities::IsRunningOnServer(Ctx->World()), Ctx->World()->GetNetMode()), *FString::Printf(Format, ##__VA_ARGS__)); \
}
