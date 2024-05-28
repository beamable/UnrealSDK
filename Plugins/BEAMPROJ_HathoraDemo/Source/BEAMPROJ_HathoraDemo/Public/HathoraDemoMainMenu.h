// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DelayAction.h"
#include "OnlineError.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Beamable/OnlineSubsystemBeamableDefines.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineStatsInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Online/OnlineSessionNames.h"
#include "OnlineSubsystemUtils.h"

#include "Runtime/BeamLevelSubsystem.h"
#include "Runtime/BeamRuntime.h"
#include "Runtime/CoreOnline/Private/Online/CoreOnlinePrivate.h"

#include "HathoraDemoMainMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDelegate_LoginComplete, bool, Success, const FString&, Error);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegate_Simple);


/**
 * 
 */
UCLASS()
class BEAMPROJ_HATHORADEMO_API UHathoraDemoMainMenu : public UBeamLevelSubsystem
{
	GENERATED_BODY()

	IOnlineSubsystem* OnlineSubsystem;
	IOnlineIdentityPtr IdentityInterface;
	IOnlineSessionPtr SessionInterface;
	IOnlineStatsPtr StatsInterface;

	FDelegateHandle OnBeamableStarted;

	TSharedPtr<FOnlineSessionSearch> CurrentSearch;
	FTimerHandle MatchmakingTimeoutHandle;


	/**
	 * Whether or not we started to travel to the server connection map.
	 */
	bool bStartedTravel;

	/**
	 * Current pending online session.
	 */
	FNamedOnlineSession* PendingSession;

	/**
	 * Whether we are awaiting a session or not.
	 */
	bool bWaitingForSession;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DelayToGameStart = 30.0f;

	UPROPERTY(BlueprintAssignable)
	FDelegate_LoginComplete OnLoginCompleteDelegate;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnMatchmakingCompleteDelegate;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnMatchmakingFailureDelegate;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnInitialized;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnTravelStartedDelegate;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
	}

	virtual FString GetSpecificLevelName() const override { return FString(TEXT("HathoraDemo")); }

	UFUNCTION(BlueprintCallable)
	void InitializeHathoraDemo()
	{
		UE_LOG(LogTemp, Warning, TEXT("Starting Hathora Demo Main Menu"));

		const auto GI = GetWorld()->GetGameInstance();
		if (GI->IsDedicatedServerInstance())
			return;

		UE_LOG(LogTemp, Warning, TEXT("Setting OnBeamStarted"));
		UBeamRuntime* Runtime = GI->GetSubsystem<UBeamRuntime>();
		OnBeamableStarted = Runtime->CPP_RegisterOnStarted(FRuntimeStateChangedHandlerCode::CreateLambda([this, GI, Runtime]
		{
			UE_LOG(LogTemp, Warning, TEXT("Initializing after beamable started"));

			// Initialize Beamable's OnlineSubsystem
			OnlineSubsystem = Online::GetSubsystem(GetWorld(),"BEAMABLE");			
			BeamOSS::InitializeOnlineSubsystemBeamable(OnlineSubsystem, GI);

			IdentityInterface = OnlineSubsystem->GetIdentityInterface();
			SessionInterface = OnlineSubsystem->GetSessionInterface();
			StatsInterface = OnlineSubsystem->GetStatsInterface();

			// Notify UI that we are ready for logging in.
			if (OnInitialized.IsBound())
				OnInitialized.Broadcast();

			// Unregister this after execution so that when we reload this scene we don't have multiple callbacks bound to this.
			Runtime->CPP_UnregisterOnStarted(OnBeamableStarted);
		}));
	}

public:
	UFUNCTION(BlueprintCallable)
	void LogIn(const FString& Username, const FString& Password)
	{
		DoLogIn(Username, Password, BeamOSS::GetIdentityTypeEmail());
	}

	UFUNCTION(BlueprintCallable)
	void Register(const FString& Username, const FString& Password)
	{
		DoLogIn(Username, Password, BeamOSS::GetIdentityTypeSignUpEmail());
	}

	UFUNCTION(BlueprintCallable)
	bool IsLoggedIn()
	{
		if (!IdentityInterface) return false;

		ELoginStatus::Type LoginStatus = IdentityInterface->GetLoginStatus(0);
		return LoginStatus == ELoginStatus::Type::LoggedIn;
	}

	UFUNCTION(BlueprintCallable)
	void EnterMatchmaking(FString QueueId)
	{
		DoEnterMatchmaking(QueueId, 120);
	}

	UFUNCTION(BlueprintCallable)
	void GetOwnerUserProfileData(FString& Id, FString& Email, FString& Alias, FString& DisplayName)
	{
		if (!OnlineSubsystem)
			return;

		const auto LoggedInUser = IdentityInterface->GetUniquePlayerId(0);
		if (LoggedInUser)
		{
			const auto Ref = LoggedInUser.ToSharedRef();
			const auto Stats = StatsInterface->GetStats(Ref);
			Id = LoggedInUser->ToString();

			if (const auto EmailStat = Stats->Stats.Find(USER_ATTR_EMAIL)) EmailStat->GetValue(Email);
			else Email = TEXT("");

			if (const auto AliasStat = Stats->Stats.Find(USER_ATTR_ALIAS)) AliasStat->GetValue(Alias);
			else Alias = TEXT("");

			if (const auto DisplayNameStat = Stats->Stats.Find(USER_ATTR_DISPLAYNAME)) DisplayNameStat->GetValue(DisplayName);
			else DisplayName = TEXT("");
		}
	}

protected:
	void DoLogIn(const FString& Username, const FString& Password, const FString& Type)
	{
		if (IsLoggedIn())
		{
			IdentityInterface->Logout(0);
			PendingSession = nullptr;
			bWaitingForSession = false;
			OnlineSubsystem->GetSessionInterface()->RemoveNamedSession(NAME_GameSession);
		}

		IdentityInterface->OnLoginCompleteDelegates->RemoveAll(this);
		IdentityInterface->OnLoginCompleteDelegates->AddUObject(this, &UHathoraDemoMainMenu::HandleUserLoginCompleted);

		FOnlineAccountCredentials Credentials;
		Credentials.Id = Username;
		Credentials.Token = Password;
		Credentials.Type = Type;

		IdentityInterface->Login(0, Credentials);
	}


	void HandleUserLoginCompleted(int32 PlatformUserIndex, bool bWasSuccessful, const FUniqueNetId& NetId, const FString& ErrorString)
	{
		if (!bWasSuccessful)
		{
			OnLoginCompleteDelegate.Broadcast(false, ErrorString);
			return;
		}

		if (OnLoginCompleteDelegate.IsBound())
		{
			OnLoginCompleteDelegate.Broadcast(bWasSuccessful, ErrorString);
		}
	}


	void DoEnterMatchmaking(FString QueueName, float Timeout)
	{
		TSharedPtr<const FUniqueNetId> UniqueId = IdentityInterface->GetUniquePlayerId(0);
		if (!UniqueId.IsValid())
		{
			// log error
			UE_LOG(LogTemp, Error, TEXT("Enter matchmaking -- UniqueId is invalid"));
			return;
		}


		FString PlayerType = "Player";

		TArray<FSessionMatchmakingUser> LocalPlayers;
		FSessionMatchmakingUser User{IdentityInterface->GetUniquePlayerId(0).ToSharedRef()};
		LocalPlayers.Add(User);

		FName SessionName = NAME_GameSession;

		FOnlineSessionSettings NewSessionSettings;
		NewSessionSettings.bIsDedicated = true;
		NewSessionSettings.bIsLANMatch = false;

		FSessionSettings MemberSettings;
		NewSessionSettings.MemberSettings.Add(UniqueId.ToSharedRef(), MemberSettings);
		if (!CurrentSearch || CurrentSearch->SearchState != EOnlineAsyncTaskState::InProgress)
		{
			CurrentSearch = MakeShared<FOnlineSessionSearch>();
			CurrentSearch->bIsLanQuery = false;
			CurrentSearch->QuerySettings.SearchParams.Empty();
		}
		CurrentSearch->QuerySettings.Set<FString>(SETTING_GAMEMODE, QueueName, EOnlineComparisonOp::Equals);

		FOnStartMatchmakingComplete Callback;
		Callback.BindUObject(this, &UHathoraDemoMainMenu::OnMatchmakingComplete);

		auto RefToSearch = CurrentSearch.ToSharedRef();
		SessionInterface->StartMatchmaking(LocalPlayers, SessionName, NewSessionSettings, RefToSearch, Callback);

		GetWorld()->GetTimerManager().SetTimer(MatchmakingTimeoutHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			if (OnlineSubsystem->GetSessionInterface()->CancelMatchmaking(0, NAME_GameSession))
			{
				SessionInterface->RemoveNamedSession(NAME_GameSession);
				UE_LOG(LogTemp, Display, TEXT("CancelMatchMaking -- CancelMatchMaking."));
			}

			PendingSession = nullptr;
			CurrentSearch = nullptr;

			// fire the failure delegate
			if (OnMatchmakingFailureDelegate.IsBound())
			{
				OnMatchmakingFailureDelegate.Broadcast();
			}
		}), Timeout, false);
	}

	void OnMatchmakingComplete(FName SessionName, const FOnlineError& Error, const FSessionMatchmakingResults& Results)
	{
		if (MatchmakingTimeoutHandle.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(MatchmakingTimeoutHandle);
		}

		if (Error.WasSuccessful())
		{			
			UE_LOG(LogTemp, Display, TEXT("OnMatchmakingComplete -- SessionName: %s"), *SessionName.ToString());
			SessionInterface->GetNamedSession(SessionName);

			if (CurrentSearch->SearchResults.Num() == 0)
			{
				UE_LOG(LogTemp, Error, TEXT("OnMatchmakingComplete -- SearchResults is empty"));
				OnMatchmakingFailureDelegate.Broadcast();				
				return;
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("OnMatchmakingComplete -- SearchResults: %s"), *CurrentSearch->SearchResults[0].GetSessionIdStr());
			}

			FString URL = "";
			if (!SessionInterface->GetResolvedConnectString(CurrentSearch->SearchResults[0], NAME_GamePort, URL))
			{
				UE_LOG(LogTemp, Error, TEXT("OnMatchmakingComplete -- Error resolving connection string"));
				OnMatchmakingFailureDelegate.Broadcast();				
				return;
			}

			UE_LOG(LogTemp, Display, TEXT("OnMatchmakingComplete -- URL: %s"), *URL);

			FOnlineSession Session = CurrentSearch->SearchResults[0].Session;
			UE_LOG(LogTemp, Display, TEXT("OnMatchmakingComplete -- SessionId: %s"), *Session.GetSessionIdStr());
			OnMatchmakingCompleteDelegate.Broadcast();
			StartTravelToGameServer(*URL);
		}
		else
		{
			if (OnMatchmakingFailureDelegate.IsBound())
			{
				OnMatchmakingFailureDelegate.Broadcast();
			}
		}
	}


	void StartTravelToGameServer(const FString& ServerAddress)
	{
		FTimerHandle TravelDelayHandle;
		GetWorld()->GetTimerManager().SetTimer(TravelDelayHandle, FTimerDelegate::CreateWeakLambda(this, [this, ServerAddress]
		{
			TravelToGameServer(ServerAddress);
		}), DelayToGameStart, false);
	}

	void TravelToGameServer(const FString& ServerAddress)
	{		
		if (bStartedTravel)
			return;

		OnTravelStartedDelegate.Broadcast();
		bStartedTravel = true;

		TArray<FString> Options;
		auto localPlayer = GetWorld()->GetFirstLocalPlayerFromController();
		if (localPlayer)
		{
			Options.Add("Name=" + localPlayer->GetNickname());
		}

		const auto OptionsStr = FString::Join(Options, TEXT("?"));
		UGameplayStatics::OpenLevel(this, FName(ServerAddress), true, OptionsStr);
	}
};
