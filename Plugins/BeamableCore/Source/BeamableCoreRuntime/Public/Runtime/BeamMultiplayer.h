#pragma once
#include "RequestTracker/BeamOperation.h"


namespace BeamMultiplayer
{
	namespace Orchestrator
	{
		BEAMABLECORERUNTIME_API FGuid GetLobbyIdFromCLArgs(UObject* CallingContext);
		BEAMABLECORERUNTIME_API FBeamOperationHandle RegisterLobbyWithServer(const UObject* CallingContext, const FGuid LobbyId, const FBeamOperationEventHandlerCode& Handler);
		BEAMABLECORERUNTIME_API FBeamOperationHandle NotifyLobbyReady(const UObject* CallingContext, const FGuid LobbyId, const FBeamOperationEventHandlerCode& Handler);
	}

	namespace Authentication
	{
		BEAMABLECORERUNTIME_API void PreLoginAsync(const AGameModeBase* GameMode, const FString& String, const FString& Address, const FUniqueNetIdRepl& UniqueId, const FBeamOperationEventHandlerCode& OperationHandler);
	}

	namespace LocalPlayer
	{
		BEAMABLECORERUNTIME_API FString GetGameLoginOptions(const ULocalPlayer* This, FString BaseOptions);
		BEAMABLECORERUNTIME_API void Logout(const AController* Controller);
	}
}
