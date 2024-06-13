// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineStatsInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Online/OnlineSessionNames.h"
#include "OnlineSubsystemUtils.h"
#include "steam/steam_api.h"

#include "Runtime/BeamLevelSubsystem.h"
#include "Runtime/BeamRuntime.h"
#include "SteamDemoMainMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDelegate_LoginComplete, bool, Success, const FString&, Error);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegate_Simple);

/**
 * 
 */
UCLASS()
class BEAMPROJ_STEAMDEMO_API USteamDemoMainMenu : public UBeamLevelSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	UBeamUserSlots* UserSlots;
	/** Cached pointer to owning subsystem */
	IOnlineSubsystem* OnlineSubsystem;
	IOnlineSessionPtr SessionInterface;
	IOnlineStatsPtr StatsInterface;
	bool LoggedIn;

	FDelegateHandle OnBeamableReady;

public:
	UPROPERTY(BlueprintAssignable)
	FDelegate_LoginComplete OnLoginCompleteDelegate;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnInitialized;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		UE_LOG(LogTemp, Warning, TEXT("Hello"));
		UserSlots = GEngine->GetEngineSubsystem<UBeamUserSlots>();
		LoggedIn = false;
	}

	virtual FString GetSpecificLevelName() const override { return FString(TEXT("SteamDemo")); }

	UFUNCTION(BlueprintCallable)
	void InitializeSteamDemo()
	{
		if (APlayerController* PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()))
		{
			PC->bShowMouseCursor = true;
			PC->bEnableClickEvents = true;
			PC->bEnableMouseOverEvents = true;
		}

		UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
		UE_LOG(LogTemp, Warning, TEXT("SteamDemo Init Start"));
		UBeamRuntime* Runtime = GameInstance->GetSubsystem<UBeamRuntime>();

		const TSharedPtr<const FUniqueNetId> netID = UGameplayStatics::GetGameInstance(GetWorld())->GetFirstGamePlayer()
			->GetPreferredUniqueNetId().GetUniqueNetId();
		const FString UniqueNetId = netID->ToString();
		UE_LOG(LogTemp, Warning, TEXT("SteamDemoLogs, GetUniqueNetId: %s"), *UniqueNetId);
		ISteamUser* SteamAccount = SteamUser();

		OnBeamableReady = Runtime->CPP_RegisterOnReady(FRuntimeStateChangedHandlerCode::CreateLambda(
			[this, GameInstance, Runtime,SteamAccount]
			{
				UE_LOG(LogTemp, Warning, TEXT("SteamDemoLogs Initializing after beamable Ready"));
				FUserSlot TargetSlot = FUserSlot(TEXT("Player0"));
				FBeamRealmUser user;
				const bool userGrabbed = UserSlots->GetUserDataAtSlot(TargetSlot, user, this);
				if (!userGrabbed) 
				{
					UE_LOG(LogTemp, Error, TEXT("SteamDemoLogs, NO USER!"))
					return;
				}
				const auto AccountID = user.AccountId.AsString;
				if (!SteamAccount)
				{
					UE_LOG(LogTemp, Error, TEXT("SteamDemoLogs, NOT A STEAM USER"))
					return;
				}

				uint32 TicketSize = 0;
				uint8 TicketBuffer[1024];

				HAuthTicket AuthTicket = SteamAccount->GetAuthSessionTicket(
					TicketBuffer, sizeof(TicketBuffer), &TicketSize);

				if (AuthTicket == k_HAuthTicketInvalid || TicketSize <= 0)
				{
					// Handle the error case
					UE_LOG(LogTemp, Error, TEXT("SteamDemoLogs, Failed to get Steam auth session ticket"));
				}
				const auto Namespace = TEXT("steam_federated");
				const auto ServiceName = TEXT("SteamDemo");
				// Successfully obtained the session ticket
				FString ExternalToken;
				for (uint32 i = 0; i < TicketSize; i++)
				{
					ExternalToken += FString::Printf(TEXT("%02x"), TicketBuffer[i]);
				}
				UE_LOG(LogTemp, Warning, TEXT("SteamDemoLogs User HEX Auth ticket: %s"), *ExternalToken);
				const FBeamOperationEventHandlerCode LoginHandler = FBeamOperationEventHandlerCode::CreateLambda(
					[this](FBeamOperationEvent Evt)
					{
						if (Evt.EventType == OET_SUCCESS)
						{
							UE_LOG_ONLINE_IDENTITY(
								Warning,
								TEXT(
									"SteamDemoLogs [Federated Identity] Successfully SignedUp using federated identity!"
								));
							return;
						}
						UE_LOG(LogTemp, Error, TEXT("SteamDemoLogs, FAILED TO LOGIN: %s"), *Evt.EventData);
					});

				const auto OnSignUpWithSteam = FBeamOperationEventHandlerCode::CreateLambda(
					[this, GameInstance,TargetSlot,Namespace,ServiceName,ExternalToken,LoginHandler,Runtime](
					FBeamOperationEvent Evt)
					{
						if (Evt.EventType == OET_SUCCESS)
						{
							UE_LOG_ONLINE_IDENTITY(
								Warning, TEXT("[Federated Identity] Successfully SignedUp using federated identity!"));
							return;
						}

						// Error Handling
						if (Evt.EventData.Contains("EXTERNAL_IDENTITY_IN_USE"))
						{
							UE_LOG_ONLINE_IDENTITY(
								Warning,
								TEXT(
									"[Federated Identity] %s User already associated with beamable account. Logging in instead."
								));
							Runtime->CPP_LoginExternalIdentityOperation(TargetSlot, ServiceName, Namespace,
							                                            ExternalToken, LoginHandler);
						}
						else
						{
							UE_LOG_ONLINE_IDENTITY(Warning, TEXT("[Federated Identity] Failed To Sign Up. Reason=%s."),
							                       *Evt.EventData);
							// TriggerOnLoginCompleteDelegates(LocalUserNum, false, *FUniqueNetIdBeamable::EmptyId(), Evt.EventData);
						}
					});
				Runtime->CPP_AttachExternalIdentityOperation(TargetSlot, ServiceName, Namespace, *ExternalToken,
				                                             AccountID, OnSignUpWithSteam);
				// Unregister this after execution so that when we reload this scene we don't have multiple callbacks bound to this.
				Runtime->CPP_UnregisterOnReady(OnBeamableReady);
			}));
	}

	UFUNCTION(BlueprintCallable)
	bool IsLoggedIn()
	{
		return LoggedIn;
	}
};
