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

// FString::Printf(TEXT("%s [Index: %d, Starting Map: %s, IsServer: %d, NetMode: %d] -"), *Header, FBeamPIE_Utilities::GetPIEInstance(WorldContext), *CurrMapName,
// 								   FBeamPIE_Utilities::IsRunningOnServer(WorldContext->World()), WorldContext->World()->GetNetMode());

#define UE_BEAM_LOG(Ctx, CategoryName, Verbosity, Format, ...) \
{ \
	UE_LOG(CategoryName, Verbosity, TEXT("[PIE Index: %d, Server Type: ] %s"), \
		FBeamPIE_Utilities::GetPIEInstance(Ctx), *FString::Printf(Format, ##__VA_ARGS__)); \
}

// #define UE_LOG_ONLINE_ACHIEVEMENTS(Verbosity, Format, ...) \
// { \
// UE_LOG(LogOnlineAchievements, Verbosity, TEXT("%s%s"), ONLINE_LOG_PREFIX, *FString::Printf(Format, ##__VA_ARGS__)); \
// }