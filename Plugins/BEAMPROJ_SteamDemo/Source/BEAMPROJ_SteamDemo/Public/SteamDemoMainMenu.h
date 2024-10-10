// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Online/OnlineSessionNames.h"
#include "OnlineSubsystemUtils.h"
#include "AutoGen/SubSystems/BeamStatsApi.h"
#include "steam/steam_api.h"

#include "Runtime/BeamLevelSubsystem.h"
#include "Runtime/BeamRuntime.h"
#include "Subsystems/Stats/BeamStatsSubsystem.h"
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

		UGameInstance* GameInstance = GetWorld()->GetGameInstance();
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
				FBeamRealmUser User;
				const bool userGrabbed = UserSlots->GetUserDataAtSlot(TargetSlot, User, this);
				if (!userGrabbed)
				{
					UE_LOG(LogTemp, Error, TEXT("SteamDemoLogs, NO USER!"))
					return;
				}
				const auto AccountID = User.AccountId.AsString;
				if (!SteamAccount)
				{
					UE_LOG(LogTemp, Error, TEXT("SteamDemoLogs, NOT A STEAM USER"))
					this->OnLoginCompleteDelegate.Broadcast(false,TEXT("NOT A STEAM USER"));
					return;
				}

				uint32 TicketSize = 0;
				uint8 TicketBuffer[1024];
				HAuthTicket AuthTicket = SteamAccount->GetAuthSessionTicket(
					TicketBuffer, sizeof(TicketBuffer), &TicketSize, nullptr);

				if (AuthTicket == k_HAuthTicketInvalid || TicketSize <= 0)
				{
					// Handle the error case
					UE_LOG(LogTemp, Error, TEXT("SteamDemoLogs, Failed to get Steam auth session ticket"));
				}
				const auto Namespace = TEXT("federated_steam");
				const auto ServiceName = TEXT("SteamDemo");
				// Successfully obtained the session ticket
				FString ExternalToken;
				for (uint32 i = 0; i < TicketSize; i++)
				{
					ExternalToken += FString::Printf(TEXT("%02x"), TicketBuffer[i]);
				}
				UE_LOG(LogTemp, Warning, TEXT("SteamDemoLogs User HEX Auth ticket: %s"), *ExternalToken);
				if (IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
				{
					IOnlineIdentityPtr IdentityInterface = OnlineSubsystem->GetIdentityInterface();
					if (IdentityInterface.IsValid())
					{
						ExternalToken = IdentityInterface->GetAuthToken(0);
						FString UserName = IdentityInterface->GetPlayerNickname(0);	
						UE_LOG(LogTemp, Warning, TEXT("SteamDemoLogs IOnlineSubsystem Auth ticket: %s"), *ExternalToken);
						UE_LOG(LogTemp, Warning, TEXT("SteamDemoLogs IOnlineSubsystem Username: %s"), *UserName);
						UBeamStatsSubsystem* Stats = GameInstance->GetSubsystem<UBeamStatsSubsystem>();
						Stats->CPP_SetStatOperation(TargetSlot, TEXT("SteamUserName"),UserName, FBeamOperationEventHandlerCode::CreateLambda([](FBeamOperationEvent Evt)
						{
						if (Evt.EventType == OET_SUCCESS)
						{
							UE_LOG(LogTemp, Log, TEXT("Steam username saved to stats"));
						}else{
							UE_LOG(LogTemp, Error, TEXT("Failed to save Steam username to stats"));
						}
						}));
					}
				}
				const FBeamOperationEventHandlerCode LoginHandler = FBeamOperationEventHandlerCode::CreateLambda(
					[this](const FBeamOperationEvent& Evt)
					{
						if (Evt.EventType == OET_SUCCESS)
						{
							this->LoggedIn = true;
							UE_LOG_ONLINE_IDENTITY(
								Warning,
								TEXT(
									"SteamDemoLogs [Federated Identity] Successfully SignedUp using federated identity!"
								));
							this->OnLoginCompleteDelegate.Broadcast(true,*Evt.EventCode);
							return;
						}
						UE_LOG(LogTemp, Error, TEXT("SteamDemoLogs, FAILED TO LOGIN: %s"), *Evt.EventCode);
						this->OnLoginCompleteDelegate.Broadcast(false,*Evt.EventCode);
					});

				const auto OnSignUpWithSteam = FBeamOperationEventHandlerCode::CreateLambda(
					[this, GameInstance,TargetSlot,Namespace,ServiceName,ExternalToken,LoginHandler,Runtime](
					const FBeamOperationEvent& Evt)
					{
						if (Evt.EventType == OET_SUCCESS)
						{
							this->LoggedIn = true;
							UE_LOG_ONLINE_IDENTITY(
								Warning, TEXT("[Federated Identity] Successfully SignedUp using federated identity!"));
							this->OnLoginCompleteDelegate.Broadcast(true,*Evt.EventCode);
							return;
						}

						// Error Handling
						if (Evt.EventCode.Contains("EXTERNAL_IDENTITY_IN_USE"))
						{
							UE_LOG_ONLINE_IDENTITY(
								Warning,
								TEXT(
									"[Federated Identity] User already associated with beamable account. Logging in instead."
								));
							Runtime->CPP_LoginExternalIdentityOperation(TargetSlot, ServiceName, Namespace,
							                                            ExternalToken, LoginHandler);
							
						}
						else
						{
							UE_LOG_ONLINE_IDENTITY(Warning, TEXT("[Federated Identity] Failed To Sign Up. Reason=%s."), *Evt.EventCode);
							this->OnLoginCompleteDelegate.Broadcast(false,*Evt.EventCode);
						}
					});
				Runtime->CPP_AttachExternalIdentityOperation(TargetSlot, ServiceName, Namespace, 
				                                             AccountID, ExternalToken, OnSignUpWithSteam);
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
