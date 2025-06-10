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

	UFUNCTION()
	void OnMatchmakingAccessRefreshed(FMatchmakingAccessRefreshNotificationMessage evt)
	{
		UE_LOG(LogTemp, Display, TEXT("BeamDiscord HandleMatchmakingAccessRefreshNotificationMessage: %hhd"), evt.matchmaking_discord_whitelisted);
		CanPerformMatchmaking = evt.matchmaking_discord_whitelisted;

		const auto IsAuthenticated = Runtime->GetOwnerSlotConnectivity()->IsAuthenticated();
		this->OnStatusUpdated.Broadcast(IsAuthenticated, this->CanPerformMatchmaking);
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
	void OnBeamableSDKReady()
	{
		FUserStateChangedHandler UserReadyHandler;
		FRuntimeError SDKInitializationErrorHandler;
		UserReadyHandler.BindDynamic(this, &UDiscordDemoMainMenu::OnBeamableUserReady);

		Runtime->RegisterOnUserReady(UserReadyHandler);

		const auto OwnerSlot = Runtime->GetOwnerSlotConnectivity()->UserSlot;
		Runtime->CPP_LoginFrictionlessOperation(OwnerSlot, {}, {});
	}

	UFUNCTION()
	void OnBeamableSDKFail(FString ErrorMessage)
	{
	}

	UFUNCTION(BlueprintCallable)
	void InitBeam()
	{
		UE_LOG(LogTemp, Display, TEXT("BeamDiscord Demo Main Menu BEAM"));
		auto GameInstance = GetWorld()->GetGameInstance();
		Runtime = GameInstance->GetSubsystem<UBeamRuntime>();

		FBeamRuntimeHandler OnStartedHandler;
		OnStartedHandler.BindDynamic(this, &UDiscordDemoMainMenu::OnBeamableSDKReady);
		FRuntimeError OnStarterFailHandler;
		OnStarterFailHandler.BindDynamic(this, &UDiscordDemoMainMenu::OnBeamableSDKFail);

		Runtime->InitSDK(OnStartedHandler, OnStarterFailHandler);
	}

	UFUNCTION()
	void OnBeamableUserReady(const FUserSlot& UserSlotAuthenticated)
	{
		UE_LOG(LogTemp, Display, TEXT("BeamDiscord Demo Main Menu BEAM"));
		OnInitialized.Broadcast();

		this->Runtime->SubscribeToCustomNotification<FOnMatchmakingAccessRefreshMessageCode, FMatchmakingAccessRefreshNotificationMessage>(UserSlotAuthenticated, CTX_KEY_Matchmaking_Refresh,
		                                                                                                                                   FOnMatchmakingAccessRefreshMessageCode::CreateUObject(
			                                                                                                                                   this, &UDiscordDemoMainMenu::OnMatchmakingAccessRefreshed));
	}

	UFUNCTION(BlueprintCallable)
	void InitializeDiscordDemo()
	{
		const auto DiscordGameSystem = GetWorld()->GetGameInstance()->GetSubsystem<UDiscordSubsystem>();
		DiscordGameSystem->OnDiscordInitialized.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(UDiscordDemoMainMenu, HandleDiscordInitialized));
		DiscordGameSystem->ManualInitialize();
	}

	UFUNCTION()
	void HandleDiscordInitialized(bool success, FDiscordUserData DiscordUserData, FString Error)
	{
		if (!success)
		{
			UE_LOG(LogTemp, Display, TEXT("Initialized BeamDiscord Demo Main Menu: Discord failed to initialize: %s"), *Error);
			return;
		}

		UE_LOG(LogTemp, Display, TEXT("Initialized BeamDiscord Demo Main Menu: Discord Initialized"));

		const auto OwnerSlot = Runtime->GetOwnerSlotConnectivity()->UserSlot;

		if (!UserSlots->IsUserSlotAuthenticated(OwnerSlot, this))
		{
			UE_LOG(LogTemp, Error, TEXT("DiscordDemo Main Menu, NO USER!"))
			return;
		}

		const auto AccountID = DiscordUserData.UserId;
		const auto Namespace = TEXT("discord");
		const auto ServiceName = TEXT("DiscordSampleMs");

		const auto LoginHandler = FBeamOperationEventHandlerCode::CreateLambda([this](const FBeamOperationEvent& Evt)
		{
			if (Evt.EventType == OET_SUCCESS)
			{
				UE_LOG(LogTemp, Warning, TEXT( "[Federated Identity] Successfully SignedUp using federated identity!" ));
				this->HandleLoggedIn(true, TEXT(""));
				return;
			}
			UE_LOG(LogTemp, Error, TEXT("[Federated Identity] FAILED TO LOGIN: %s"), *Evt.EventCode);
			this->HandleLoggedIn(false, *Evt.EventCode);
		});
		const auto OnSignUpWithDiscord = FBeamOperationEventHandlerCode::CreateLambda([this, Namespace, ServiceName, DiscordUserData, LoginHandler, OwnerSlot](const FBeamOperationEvent& Evt)
		{
			// Handle successful login
			if (Evt.EventType == OET_SUCCESS)
			{
				UE_LOG(LogTemp, Warning, TEXT( "[Federated Identity] Successfully SignedUp using federated identity!" ));
				this->HandleLoggedIn(true, TEXT(""));
			}
			// Handle error for when the discord id is already in use by logging into the account with that discord id
			else if (Evt.EventCode.Contains("EXTERNAL_IDENTITY_IN_USE"))
			{
				UE_LOG(LogTemp, Warning, TEXT( "[Federated Identity] User already associated with beamable account. Login in started on the account with third party identity." ));
				Runtime->CPP_LoginFederatedOperation(OwnerSlot, ServiceName, Namespace, DiscordUserData.OAuthToken, LoginHandler);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("[Federated Identity] Failed To Sign Up. Reason=%s"), *Evt.EventCode);
				this->HandleLoggedIn(false, *Evt.EventCode);
			}
		});
		Runtime->CPP_AttachFederatedOperation(OwnerSlot, ServiceName, Namespace, AccountID, DiscordUserData.OAuthToken, OnSignUpWithDiscord);
	}

	void HandleLoggedIn(bool bSuccess, const FString& Error)
	{
		const auto IsAuthenticated = Runtime->GetOwnerSlotConnectivity()->IsAuthenticated();

		this->OnLoginCompleted.Broadcast(bSuccess, Error);
		this->OnStatusUpdated.Broadcast(IsAuthenticated, this->CanPerformMatchmaking);
		if (bSuccess)
		{
			auto Request = UDiscordSampleMsUpdateUserWhitelistedStatusRequest::Make(this, {});
			const auto Handler = FOnDiscordSampleMsUpdateUserWhitelistedStatusFullResponse::CreateLambda([this](FDiscordSampleMsUpdateUserWhitelistedStatusFullResponse Resp)
			{
				// If the request failed, or we are retrying, we do nothing  
				if (Resp.State != RS_Success)
				{
					UE_LOG(LogTemp, Display, TEXT(" BeamDiscord FDiscordSampleMsUpdateUserWhitelistedStatusFullResponse: REQUEST FAILED: %s"), *Resp.ErrorData.message);
					return;
				}

				auto NewMessage = FMatchmakingAccessRefreshNotificationMessage{};
				NewMessage.matchmaking_discord_whitelisted = Resp.SuccessData->bMatchmakingDiscordWhitelisted;
				// Otherwise, print the value 
				UE_LOG(LogTemp, Display, TEXT(" BeamDiscord FDiscordSampleMsUpdateUserWhitelistedStatusFullResponse: %dhh"), Resp.SuccessData->bMatchmakingDiscordWhitelisted);
				OnMatchmakingAccessRefreshed(NewMessage);
			});

			FBeamRequestContext Ctx;
			UE_LOG(LogTemp, Display, TEXT("BeamDiscord SENDING UpdateUserWhitelistedStatus request"))
			DiscordSampleMsApi->CPP_UpdateUserWhitelistedStatus(Runtime->GetOwnerSlotConnectivity()->UserSlot, Request, Handler, Ctx, {}, this);
		}
	}
};
