#include "Runtime/BeamMultiplayer.h"

#include "GameFramework/GameModeBase.h"
#include "PIE/BeamPIE_Utilities.h"
#include "Subsystems/Lobby/BeamLobbySubsystem.h"
#include "Subsystems/PIE/BeamPIE.h"

namespace BeamMultiplayer
{
	namespace Orchestrator
	{
		FGuid GetLobbyIdFromCLArgs(UObject* CallingContext)
		{
			if (!CallingContext) return FGuid{};
			if (!CallingContext->GetWorld()) return FGuid{};

			const auto GI = CallingContext->GetWorld()->GetGameInstance();
			if (!GI) return FGuid{};

			auto LobbySubsystem = GI->GetSubsystem<UBeamLobbySubsystem>();
			if (!LobbySubsystem) return FGuid{};


			//... that expects to run a single lobby's match (we expect either a CLArg or a EnvVar to exist)
			FString LobbyIdStr;
			if (!FParse::Value(FCommandLine::Get(), TEXT("BeamableDedicatedServerInstanceLobbyId="), LobbyIdStr))
			{
				LobbyIdStr = FPlatformMisc::GetEnvironmentVariable(TEXT("BEAMABLE_DEDICATED_SERVER_INSTANCE_LOBBY_ID"));
			}

			// If no CLArg or EnvVar are provided, we assume the user will run multiple matches per server and will make the calls to RefreshLobbyDataOperation from their integration with their game server orchestrator
			// (Hathora, GameLift, etc...)
			if (LobbyIdStr.IsEmpty())
			{
				UE_LOG(LogBeamLobby, Warning, TEXT("No LobbyId was provided via CLArgs/EnvVars. "
					       "Take a look at our Multiplayer docs to understand when/how to use this."))

				return FGuid{};
			}

			return FGuid(LobbyIdStr);
		}

		FBeamOperationHandle RegisterLobbyWithServer(const UObject* CallingContext, const FGuid LobbyId, const FBeamOperationEventHandlerCode& Handler)
		{
			if (!CallingContext) return FBeamOperationHandle{};
			if (!CallingContext->GetWorld()) return FBeamOperationHandle{};

			const auto GI = CallingContext->GetWorld()->GetGameInstance();
			if (!GI) return FBeamOperationHandle{};

			auto LobbySubsystem = GI->GetSubsystem<UBeamLobbySubsystem>();
			if (!LobbySubsystem) return FBeamOperationHandle{};

			return LobbySubsystem->CPP_RegisterLobbyWithServerOperation(GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot(), LobbyId, Handler);
		}

		FBeamOperationHandle NotifyLobbyReady(const UObject* CallingContext, FGuid LobbyId, const FBeamOperationEventHandlerCode& Handler)
		{
			if (!CallingContext) return FBeamOperationHandle{};
			if (!CallingContext->GetWorld()) return FBeamOperationHandle{};

			const auto GI = CallingContext->GetWorld()->GetGameInstance();
			if (!GI) return FBeamOperationHandle{};

			auto LobbySubsystem = GI->GetSubsystem<UBeamLobbySubsystem>();
			if (!LobbySubsystem) return FBeamOperationHandle{};

			return LobbySubsystem->CPP_NotifyLobbyReadyForClientsOperation(GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot(), LobbyId, Handler);
		}
	}


	namespace LocalPlayer
	{
		FString GetGameLoginOptions(const ULocalPlayer* This, FString BaseOptions)
		{
			FString Options = BaseOptions;
			const auto Lobby = This->GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();
			return Lobby->PrepareLoginOptions(This, Options);
		}
	}

	void Authentication::PreLoginAsync(const AGameModeBase* GameMode, const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, const FBeamOperationEventHandlerCode& OperationHandler)
	{
		const auto Lobby = GameMode->GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();
		const auto ServerSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();

		if (UniqueId.IsValid())
		{
			UE_BEAM_LOG(GEngine->GetWorldContextFromWorld(GameMode->GetWorld()), LogBeamEditor, Warning, TEXT("GetPreferredUniqueNetId %s"), *UniqueId.GetUniqueNetId().Get()->ToString())
		}
		
		Lobby->CPP_AcceptUserIntoGameServerOperation(ServerSlot, Options, Address, UniqueId, OperationHandler);
	}
}
