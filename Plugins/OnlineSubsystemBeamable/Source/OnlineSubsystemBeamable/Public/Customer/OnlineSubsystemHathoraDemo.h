#pragma once

#ifdef BEAM_ENABLE_BEAMABLE_OSS

#include "HathoraSDK.h"
#include "Beamable/OnlineIdentityBeamable.h"
#include "Beamable/OnlineSessionInterfaceBeamable.h"
#include "Beamable/OnlineSubsystemBeamable.h"
#include "Interfaces/OnlineStatsInterface.h"
#include "Subsystems/Stats/BeamStatsSubsystem.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamMSPlaygroundApi.h"

class FOnlineSubsystemHathoraDemo final : public FOnlineSubsystemBeamable
{
public:
	FOnlineSubsystemHathoraDemo() = delete;

	explicit FOnlineSubsystemHathoraDemo(const FName& InInstanceName)
		: FOnlineSubsystemBeamable(InInstanceName)
	{
	}

	FString ConvertHathoraRegionPingsToJson(const FHathoraRegionPings& RegionPings);

	FBeamOperationHandle HathoraPingsOperation(FUserSlot UserSlot);

	virtual bool Init() override
	{
		const bool bDidRunCorrectly = FOnlineSubsystemBeamable::Init();

		const auto Sessios = static_cast<FOnlineSessionBeamable*>(GetSessionInterface().Get());
		Sessios->StartMatchmakingHooks.Add(FPreStartMatchmakingHook::CreateLambda([this](const TArray<FUniqueNetIdRef>& LocalPlayers, FName SessionName, const FOnlineSessionSettings& NewSessionSettings, TSharedRef<FOnlineSessionSearch>& SearchSettings)
		{
			// log hook started
			UE_LOG(LogTemp, Display, TEXT("StartMatchmakingHook started"));

			auto PlayerAccount = GetAccountForId(*LocalPlayers[0]);
			auto UserSlot = PlayerAccount->CurrentSlot;

			bool IsHathoraSDKLoaded = FModuleManager::Get().IsModuleLoaded("HathoraSDK");
			if (IsHathoraSDKLoaded) return HathoraPingsOperation(UserSlot);

			return GetRequestTracker()->CPP_BeginSuccessfulOperation({UserSlot}, this->GetInstanceName().ToString(), FString(""), {});
		}));

		Sessios->PreCreateSessionHooks.Add(FPreCreatedSessionHook::CreateLambda([this](const FUniqueNetId& LocalPlayerId, FName SessionName, const FOnlineSessionSettings& SelectedSession)
		{
			// log hook started
			UE_LOG(LogTemp, Display, TEXT("Pre Create Session Hooks started"));

			auto PlayerAccount = GetAccountForId(LocalPlayerId);
			auto UserSlot = PlayerAccount->CurrentSlot;

			// If hathora is being used, we ping their servers before we create a session.
			bool IsHathoraSDKLoaded = FModuleManager::Get().IsModuleLoaded("HathoraSDK");
			if (IsHathoraSDKLoaded) return HathoraPingsOperation(UserSlot);

			// Otherwise, we don't do anything in the hook.
			return GetRequestTracker()->CPP_BeginSuccessfulOperation({UserSlot}, this->GetInstanceName().ToString(), FString(""), {});
		}));

		Sessios->PreJoinSessionHooks.Add(FPreJoinedSessionHook::CreateLambda([this](const FUniqueNetId& LocalPlayerId, FName SessionName, const FOnlineSessionSearchResult& Settings)
		{
			// log hook started
			UE_LOG(LogTemp, Display, TEXT("Pre Create Session Hooks started"));

			auto PlayerAccount = GetAccountForId(LocalPlayerId);
			auto UserSlot = PlayerAccount->CurrentSlot;

			// If hathora is being used, we ping their servers before we create a session.
			bool IsHathoraSDKLoaded = FModuleManager::Get().IsModuleLoaded("HathoraSDK");
			if (IsHathoraSDKLoaded) return HathoraPingsOperation(UserSlot);

			// Otherwise, we don't do anything in the hook.
			return GetRequestTracker()->CPP_BeginSuccessfulOperation({UserSlot}, this->GetInstanceName().ToString(), FString(""), {});
		}));

		// Add ping search hooks.
		Sessios->PingSearchHooks.Add(FPingSearchHook::CreateLambda([this](const FOnlineSessionSearchResult& Results)
		{
			// log hook started
			UE_LOG(LogTemp, Display, TEXT("Ping Search Hooks started"));
			
			// If there's no Hathora SDK, we fail this operation.
			if (!FModuleManager::Get().IsModuleLoaded("HathoraSDK"))
				return GetRequestTracker()->CPP_BeginErrorOperation({}, this->GetInstanceName().ToString(), FString("NO_PINGS_FOUND"), {});

			const auto Op = GetRequestTracker()->CPP_BeginOperation({}, TEXT("Timeless Ping Search Hook"), {});
			FHathoraSDK::Instance()->GetRegionalPings(FHathoraOnGetRegionalPings::CreateLambda([this, Op](const FHathoraRegionPings& Result)
			{
				if (Result.Pings.Num() > 0)
				{
					FOnlineSessionSearchResult Results;					
					GetRequestTracker()->TriggerOperationSuccess(Op, FString(""));
				}
				else
				{
					GetRequestTracker()->TriggerOperationError(Op, FString("NO_PINGS_FOUND"));
				}
			}));

			return Op;
		}));

		// const auto Identity = static_cast<FOnlineIdentityBeamable*>(GetIdentityInterface().Get());
		// Identity->OnBeamableUserReadyHook.Add(FOnBeamableReadyIdentityHook::CreateLambda([this](FUserSlot UserSlot, TSharedPtr<FUserOnlineAccountBeamable> Account)
		// {
		// 	// ensure player has all the things a new player should have
		//
		// 	const auto Op = GetRequestTracker()->CPP_BeginOperation({UserSlot}, this->GetInstanceName().ToString(), {});
		// 	const auto TimelessMsApi = GEngine->GetEngineSubsystem<UBeamTimelessMsApi>();
		// 	UTimelessMsOnPostLoginRequest* Req = UTimelessMsOnPostLoginRequest::Make(GetTransientPackage(), {});
		// 	const auto Handler = FOnTimelessMsOnPostLoginFullResponse::CreateLambda([this, Op](FTimelessMsOnPostLoginFullResponse Resp)
		// 	{
		// 		// If we are invoking this before retrying, we just don't do anything 
		// 		if (Resp.State == RS_Retrying) return;
		//
		// 		if (Resp.State != RS_Success)
		// 		{
		// 			GetRequestTracker()->TriggerOperationError(Op, Resp.ErrorData.message);
		// 			return;
		// 		}
		//
		// 		if (!Resp.SuccessData->bSuccess)
		// 		{
		// 			// log error messge
		// 			UE_LOG(LogTemp, Error, TEXT("POST_LOGIN failed: %s"), *Resp.SuccessData->ErrorMessage);
		// 		}
		// 		else
		// 		{
		// 			UE_LOG(LogTemp, Warning, TEXT("POST_LOGIN success: %s"), *Resp.SuccessData->ErrorMessage);
		// 		}
		//
		// 		GetRequestTracker()->TriggerOperationSuccess(Op, FString("POST_LOGIN"));
		// 	});
		// 	FBeamRequestContext Ctx;
		// 	TimelessMsApi->CPP_OnPostLogin(UserSlot, Req, Handler, Ctx, Op, GetGameInstance());
		// 	return Op;
		// }));
		//
		// Identity->OnBeamableUserReadyHook.Add(FOnBeamableReadyIdentityHook::CreateLambda([this](FUserSlot UserSlot, TSharedPtr<FUserOnlineAccountBeamable> Account)
		// {
		// 	return GetRequestTracker()->CPP_BeginSuccessfulOperation({}, this->GetInstanceName().ToString(), FString(""), {});
		// }));

		return true;
	}
};

#endif