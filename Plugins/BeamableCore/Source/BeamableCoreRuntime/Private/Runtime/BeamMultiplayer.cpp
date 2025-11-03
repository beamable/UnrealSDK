#include "Runtime/BeamMultiplayer.h"

#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerState.h"
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

			return LobbySubsystem->GetLobbyIdFromCLArgs();
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
			return Lobby->PrepareLoginOptionsByLocalPlayer(This, Options);
		}

		void Logout(const AController* Controller)
		{
			
			const auto LobbySubsystem = Controller->GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();

			if (!IsValid(LobbySubsystem))
			{
				UE_LOG(LogBeamRuntime, Verbose, TEXT("The lobby system is invalid, you probably stop the game server with the client at same time."))
				return;
			}
			auto UserSlot = LobbySubsystem->GetUserSlotByPlayerController(Controller);
			
			LobbySubsystem->TryRemoveLocalPlayerState(Controller);

			const auto UserSlots = GEngine->GetEngineSubsystem<UBeamUserSlots>();
			UserSlots->ClearServerUserAtSlotSilent(UserSlot, Controller);
		}
	}

	void Authentication::PreLoginAsync(const AGameModeBase* GameMode, const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, const FBeamOperationEventHandlerCode& OperationHandler)
	{
		const auto LobbySubsystem = GameMode->GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();
		const auto ServerSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();

		const auto WorldContext = GEngine->GetWorldContextFromWorld(GameMode->GetWorld());
		if (!ensureAlwaysMsgf(
			UniqueId.IsValid(),
			TEXT("Failed to received a valid UniqueId --- please ensure that you have UBeamRuntimeSettings::bUseBeamableGamerTagsAsUniqueNetIds set to 'true' OR have another UniqueId set up correctly.")))
		{
			UE_BEAM_LOG(WorldContext, LogBeamLobby, Error,
			            TEXT("Failed to binding UniqueId for user. OPTIONS=%s, Address=%s"), *Options, *Address);
		}
		const FString& ConnectingToLobby = UGameplayStatics::ParseOption(Options, UBeamLobbySubsystem::Reserved_LoginOpt_LobbyId_Optional);

		FGuid LobbyGuid;
		if (!FGuid::Parse(ConnectingToLobby, LobbyGuid))
		{
			UE_BEAM_LOG(WorldContext, LogBeamLobby, Error, TEXT("Wasn't able to parse the Lobby Id from the Options."));
		}

		FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([=](const float)
		{
			if (!FBeamPIE_Utilities::IsValidContext(WorldContext)) return false;

			ULobby* Lobby;
			if(LobbySubsystem->TryGetLobbyById(LobbyGuid, Lobby))
			{
				LobbySubsystem->CPP_AcceptUserIntoGameServerOperation(ServerSlot, Options, Address, UniqueId, OperationHandler);
				return false;
			}
			
			return true;
		}), 0.2f);
	
	
	}
}
