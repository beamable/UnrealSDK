// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DiscordSubsystem.h"
#include "AutoGen/SubSystems/BeamNotificationApi.h"
#include "Runtime/BeamLevelSubsystem.h"
#include "Runtime/BeamRuntime.h"
#include "Subsystems/Stats/BeamStatsSubsystem.h"
#include "DiscordDemoMainMenu.generated.h"

USTRUCT()
struct FMatchmakingAccessRefreshNotificationMessage : public FBeamBaseNotificationMessage
{
	GENERATED_BODY()

	UPROPERTY()
	bool matchmaking_discord_whitelisted;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue("matchmaking_discord_whitelisted", matchmaking_discord_whitelisted);
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue("matchmaking_discord_whitelisted", matchmaking_discord_whitelisted);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		matchmaking_discord_whitelisted = Bag->GetBoolField("matchmaking_discord_whitelisted");
	}
};

DECLARE_DELEGATE_OneParam(FOnMatchmakingAccessRefreshMessageCode, FMatchmakingAccessRefreshNotificationMessage);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMatchmakingAccessRefreshMessage, FMatchmakingAccessRefreshNotificationMessage,
                                  Evt);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegate_Simple);

UCLASS()
class BEAMPROJ_DISCORDDEMO_API UDiscordDemoMainMenu : public UBeamLevelSubsystem
{
	GENERATED_BODY()

	static const inline FString CTX_KEY_Matchmaking_Refresh = TEXT("matchmaking_refresh");

	UPROPERTY()
	UBeamUserSlots* UserSlots;

	UPROPERTY()
	UBeamNotifications* Notifications;

	FDelegateHandle OnBeamableReady;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnInitialized;

	UPROPERTY()
	bool CanPerformMatchmaking = false;

	UFUNCTION()
	void HandleMatchmakingAccessRefreshNotificationMessage(FMatchmakingAccessRefreshNotificationMessage evt)
	{
		UE_LOG(LogTemp, Display, TEXT("BeamDiscord HandleMatchmakingAccessRefreshNotificationMessage: %hhd"),
		       evt.matchmaking_discord_whitelisted);
		CanPerformMatchmaking = evt.matchmaking_discord_whitelisted;
	}

protected:
	FDelegateHandle StatsUpdatedHandle;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		Notifications = GEngine->GetEngineSubsystem<UBeamNotifications>();
		UserSlots = GEngine->GetEngineSubsystem<UBeamUserSlots>();
		UE_LOG(LogTemp, Display, TEXT("Initialize BeamDiscord Demo Main Menu"));
	}

	virtual FString GetSpecificLevelName() const override { return FString(TEXT("DiscordDemo")); }

	UFUNCTION()
	void HandleDiscordInitialized(bool success, FDiscordUserData UserData, FString Error)
	{
		UE_LOG(LogTemp, Display, TEXT("Initialized BeamDiscord Demo Main Menu: %hhd"), success);
		if (!success)
		{
			return;
		}
		UGameInstance* GameInstance = GetWorld()->GetGameInstance();
		UBeamRuntime* Runtime = GameInstance->GetSubsystem<UBeamRuntime>();
		FUserSlot TargetSlot = FUserSlot(TEXT("Player0"));
		FBeamRealmUser User;
		const bool userGrabbed = UserSlots->GetUserDataAtSlot(TargetSlot, User, this);
		if (!userGrabbed)
		{
			UE_LOG(LogTemp, Error, TEXT("DiscordDemo Main Menu, NO USER!"))
			return;
		}
		const auto AccountID = User.AccountId.AsString;
		const auto Namespace = TEXT("discord");
		const auto ServiceName = TEXT("DiscordSampleMs");

		const FBeamOperationEventHandlerCode LoginHandler = FBeamOperationEventHandlerCode::CreateLambda(
			[this](const FBeamOperationEvent& Evt)
			{
				if (Evt.EventType == OET_SUCCESS)
				{
					UE_LOG(LogTemp,
					       Warning,
					       TEXT(
						       "SteamDemoLogs [Federated Identity] Successfully SignedUp using federated identity!"
					       ));
					return;
				}
				UE_LOG(LogTemp, Error, TEXT("SteamDemoLogs, FAILED TO LOGIN: %s"), *Evt.EventData);
			});
		const auto OnSignUpWithDiscord = FBeamOperationEventHandlerCode::CreateLambda(
			[this, TargetSlot,Namespace,ServiceName,UserData,Runtime,LoginHandler](const FBeamOperationEvent& Evt)
			{
				if (Evt.EventType == OET_SUCCESS)
				{
					UE_LOG(LogTemp,
					       Warning,
					       TEXT(
						       "[Federated Identity] Successfully SignedUp using federated identity!"
					       ));
					return;
				}
				// Error Handling
				if (Evt.EventData.Contains("EXTERNAL_IDENTITY_IN_USE"))
				{
					UE_LOG(LogTemp,
					       Warning,
					       TEXT(
						       "[Federated Identity] %s User already associated with beamable account. Logging in instead."
					       ));
					Runtime->CPP_LoginExternalIdentityOperation(TargetSlot, ServiceName, Namespace,
					                                            UserData.OAuthToken, LoginHandler);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("[Federated Identity] Failed To Sign Up. Reason=%s."),
					       *Evt.EventData);
				}
			});
		Runtime->CPP_AttachExternalIdentityOperation(TargetSlot, ServiceName, Namespace,
		                                             AccountID, UserData.OAuthToken,
		                                             OnSignUpWithDiscord);
	}

	UFUNCTION(BlueprintCallable)
	void InitBeam()
	{
		UE_LOG(LogTemp, Display, TEXT("BeamDiscord Demo Main Menu BEAM"));
		UGameInstance* GameInstance = GetWorld()->GetGameInstance();
		UBeamRuntime* Runtime = GameInstance->GetSubsystem<UBeamRuntime>();

		OnBeamableReady = Runtime->CPP_RegisterOnReady(FRuntimeStateChangedHandlerCode::CreateLambda(
			[this,Runtime]
			{
				UE_LOG(LogTemp, Display, TEXT("BeamDiscord Demo Main Menu BEAM"));
				OnInitialized.Broadcast();
				Runtime->CPP_UnregisterOnReady(OnBeamableReady);
				const auto UserSlot = FUserSlot(TEXT("Player0"));
				FDelegateHandle Handle;
				if (!this->Notifications->TrySubscribeForMessage<
					FOnMatchmakingAccessRefreshMessageCode, FMatchmakingAccessRefreshNotificationMessage>(UserSlot,
					Runtime->DefaultNotificationChannel, CTX_KEY_Matchmaking_Refresh,
					FOnMatchmakingAccessRefreshMessageCode::CreateUObject(
						this, &UDiscordDemoMainMenu::HandleMatchmakingAccessRefreshNotificationMessage),
					Handle, this))
				{
					UE_LOG(LogBeamNotifications, Warning,
					       TEXT("BeamDiscord Trying to subscribe to a non-existent socket."));
				}
			}));
	}


	UFUNCTION(BlueprintCallable)
	void InitializeDiscordDemo()
	{
		UGameInstance* GameInstance = GetWorld()->GetGameInstance();
		UDiscordSubsystem* discordGameSystem = GameInstance->GetSubsystem<UDiscordSubsystem>();
		discordGameSystem->OnDiscordInitialized.BindUFunction(
			this, GET_FUNCTION_NAME_CHECKED(UDiscordDemoMainMenu, HandleDiscordInitialized));
		discordGameSystem->ManualInitialize();
	}
};
