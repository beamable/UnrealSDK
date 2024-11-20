// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DiscordSubsystem.h"
#include "AutoGen/SubSystems/BeamDiscordSampleMsApi.h"
#include "AutoGen/SubSystems/BeamNotificationApi.h"
#include "Runtime/BeamLevelSubsystem.h"
#include "Runtime/BeamRuntime.h"
#include "DiscordDemoMainMenu.generated.h"

struct FBeamOperationEvent;

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
		Bag->TryGetBoolField(TEXT("matchmaking_discord_whitelisted"), matchmaking_discord_whitelisted);
	}
};

DECLARE_DELEGATE_OneParam(FOnMatchmakingAccessRefreshMessageCode, FMatchmakingAccessRefreshNotificationMessage);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMatchmakingAccessRefreshMessage, FMatchmakingAccessRefreshNotificationMessage,
                                  Evt);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDelegate_LoginComplete, bool, Success, const FString&, Error);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDelegate_StatusUpdate, bool, loggedIn, bool, MatchmakingEnabled);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegate_Simple);

UCLASS()
class BEAMPROJ_DISCORDDEMO_API UDiscordDemoMainMenu : public UBeamLevelSubsystem
{
	GENERATED_BODY()

	static const inline FString CTX_KEY_Matchmaking_Refresh = TEXT("matchmaking_refresh");

	UPROPERTY()
	UBeamUserSlots* UserSlots;

	UPROPERTY()
	UBeamRuntime* Runtime;
	
	UPROPERTY()
	UBeamNotifications* Notifications;

	UPROPERTY()
	UBeamDiscordSampleMsApi* DiscordSampleMsApi;

	FDelegateHandle OnBeamableReady;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnInitialized;
	UPROPERTY(BlueprintAssignable)
	FDelegate_LoginComplete OnLoginCompleted;
	UPROPERTY(BlueprintAssignable)
	FDelegate_StatusUpdate OnStatusUpdated;

	UPROPERTY()
	bool CanPerformMatchmaking = false;
	UPROPERTY()
	bool LoggedIn = false;

	FUserSlot UserSlot = FUserSlot(TEXT("Player0"));

	UFUNCTION()
	void HandleMatchmakingAccessRefreshNotificationMessage(FMatchmakingAccessRefreshNotificationMessage evt)
	{
		UE_LOG(LogTemp, Display, TEXT("BeamDiscord HandleMatchmakingAccessRefreshNotificationMessage: %hhd"),
		       evt.matchmaking_discord_whitelisted);
		CanPerformMatchmaking = evt.matchmaking_discord_whitelisted;
		this->OnStatusUpdated.Broadcast(this->LoggedIn, this->CanPerformMatchmaking);
	}

protected:
	FDelegateHandle StatsUpdatedHandle;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		Notifications = GEngine->GetEngineSubsystem<UBeamNotifications>();
		UserSlots = GEngine->GetEngineSubsystem<UBeamUserSlots>();
		DiscordSampleMsApi = GEngine->GetEngineSubsystem<UBeamDiscordSampleMsApi>();
		UE_LOG(LogTemp, Display, TEXT("Initialize BeamDiscord Demo Main Menu"));
	}

	virtual FString GetSpecificLevelName() const override { return FString(TEXT("DiscordDemo")); }

	UFUNCTION()
	void HandleDiscordInitialized(bool success, FDiscordUserData UserData, FString Error)
	{
		if (!success)
		{
			UE_LOG(LogTemp, Display, TEXT("Initialized BeamDiscord Demo Main Menu: Discord failed to initialize: %s"), *Error);
			return;
		}
		UE_LOG(LogTemp, Display, TEXT("Initialized BeamDiscord Demo Main Menu: Discord Initialized"));
		UGameInstance* GameInstance = GetWorld()->GetGameInstance();
		Runtime = GameInstance->GetSubsystem<UBeamRuntime>();
		FBeamRealmUser User;
		const bool userGrabbed = UserSlots->GetUserDataAtSlot(UserSlot, User, this);
		if (!userGrabbed)
		{
			UE_LOG(LogTemp, Error, TEXT("DiscordDemo Main Menu, NO USER!"))
			return;
		}
		const auto AccountID = UserData.UserId;
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
						       "[Federated Identity] Successfully SignedUp using federated identity!"
					       ));
					LoggedIn = true;
					this->HandleLoggedIn(true, TEXT(""));
					return;
				}
				UE_LOG(LogTemp, Error, TEXT("[Federated Identity] FAILED TO LOGIN: %s"), *Evt.EventCode);
				this->HandleLoggedIn(false, *Evt.EventCode);
			});
		const auto OnSignUpWithDiscord = FBeamOperationEventHandlerCode::CreateLambda(
			[this,Namespace,ServiceName,UserData,LoginHandler](const FBeamOperationEvent& Evt)
			{
				if (Evt.EventType == OET_SUCCESS)
				{
					UE_LOG(LogTemp,
					       Warning,
					       TEXT(
						       "[Federated Identity] Successfully SignedUp using federated identity!"
					       ));
					LoggedIn = true;
					this->HandleLoggedIn(true, TEXT(""));
					return;
				}
				// Error Handling
				if (Evt.EventCode.Contains("EXTERNAL_IDENTITY_IN_USE"))
				{
					UE_LOG(LogTemp,
					       Warning,
					       TEXT(
						       "[Federated Identity] User already associated with beamable account. Lo ging in instead."
					       ));
					Runtime->CPP_LoginExternalIdentityOperation(UserSlot, ServiceName, Namespace,
					                                            UserData.OAuthToken, LoginHandler);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("[Federated Identity] Failed To Sign Up. Reason=%s"), *Evt.EventCode);
					this->HandleLoggedIn(false, *Evt.EventCode);
				}
			});
		Runtime->CPP_AttachExternalIdentityOperation(UserSlot, ServiceName, Namespace,
		                                             AccountID, UserData.OAuthToken,
		                                             OnSignUpWithDiscord);
	}

	void HandleLoggedIn(bool success, const FString& Error)
	{
		this->OnLoginCompleted.Broadcast(success, Error);
		this->OnStatusUpdated.Broadcast(this->LoggedIn, this->CanPerformMatchmaking);
		if (success)
		{
			TMap<FString, FString> empty;
			UDiscordSampleMsUpdateUserWhitelistedStatusRequest* request =
				UDiscordSampleMsUpdateUserWhitelistedStatusRequest::Make(this, empty);
			const auto Handler = FOnDiscordSampleMsUpdateUserWhitelistedStatusFullResponse::CreateLambda(
				[this](FDiscordSampleMsUpdateUserWhitelistedStatusFullResponse Resp)
				{
					// If the request failed, or we are retrying, we do nothing  
					if (Resp.State != RS_Success)
					{
						
						UE_LOG(LogTemp, Display, TEXT(" BeamDiscord FDiscordSampleMsUpdateUserWhitelistedStatusFullResponse: REQUEST FAILED: %s"),
							   *Resp.ErrorData.message);
						return;
					}

					FMatchmakingAccessRefreshNotificationMessage newMessage;
					newMessage.matchmaking_discord_whitelisted = Resp.SuccessData->bMatchmakingDiscordWhitelisted;
					// Otherwise, print the value 
					UE_LOG(LogTemp, Display, TEXT(" BeamDiscord FDiscordSampleMsUpdateUserWhitelistedStatusFullResponse: %dhh"),
					       Resp.SuccessData->bMatchmakingDiscordWhitelisted);
					HandleMatchmakingAccessRefreshNotificationMessage(newMessage);
					
				});
			FBeamRequestContext Ctx;
			UE_LOG(LogTemp, Display, TEXT("BeamDiscord SENDING UpdateUserWhitelistedStatus request"))
			DiscordSampleMsApi->CPP_UpdateUserWhitelistedStatus(UserSlot, request, Handler, Ctx, {}, this);
		}
	}

	UFUNCTION(BlueprintCallable)
	void InitBeam()
	{
		UE_LOG(LogTemp, Display, TEXT("BeamDiscord Demo Main Menu BEAM"));
		UGameInstance* GameInstance = GetWorld()->GetGameInstance();
		Runtime = GameInstance->GetSubsystem<UBeamRuntime>();

		FUserStateChangedHandler UserReadyHandler;
        FRuntimeError SDKInitializationErrorHandler;
        UserReadyHandler.BindDynamic(this, &UDiscordDemoMainMenu::OnBeamableUserReady);
        
        Runtime->InitSDKWithFrictionlessLogin(UserReadyHandler,SDKInitializationErrorHandler,SDKInitializationErrorHandler);
	}

	UFUNCTION()
	void OnBeamableUserReady(const FUserSlot& UserSlotAuthenticated)
	{
		UE_LOG(LogTemp, Display, TEXT("BeamDiscord Demo Main Menu BEAM"));
		OnInitialized.Broadcast();
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
