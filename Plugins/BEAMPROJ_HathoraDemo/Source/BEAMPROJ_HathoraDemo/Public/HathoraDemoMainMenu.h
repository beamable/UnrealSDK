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
#include "HAL/PlatformApplicationMisc.h"
#include "AutoGen/SubSystems/BeamHathoraDemoApi.h"


#include "Runtime/BeamLevelSubsystem.h"
#include "Runtime/BeamRuntime.h"
#include "Runtime/CoreOnline/Private/Online/CoreOnlinePrivate.h"
#include "Subsystems/Party/BeamPartySubsystem.h"


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

	UBeamPartySubsystem* PartySubsystem;

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
	FDelegate_Simple OnEnterInTheMatchMaking;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnMatchmakingCompleteDelegate;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnMatchmakingFailureDelegate;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnInitialized;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnTravelStartedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnReceivedPartyInviteEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnReceivedPartyInviteExpiredEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnReceivedPartyInviteCancelEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnReceivedPartyJoinEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnReceivedPartyKickEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnReceivedPartyPromoteEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnReceivedPartyLeftEventDelegate;

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
		{
			return;
		}

		UE_LOG(LogTemp, Warning, TEXT("Setting OnBeamStarted"));
		UBeamRuntime* Runtime = GI->GetSubsystem<UBeamRuntime>();
		OnBeamableStarted = Runtime->CPP_RegisterOnStarted(FBeamRuntimeHandlerCode::CreateLambda([this, GI, Runtime]
		{
			UE_LOG(LogTemp, Warning, TEXT("Initializing after beamable started"));

			// Initialize Beamable's OnlineSubsystem
			OnlineSubsystem = Online::GetSubsystem(GetWorld(), "BEAMABLE");


			BeamOSS::InitializeOnlineSubsystemBeamable(OnlineSubsystem, GI);

			IdentityInterface = OnlineSubsystem->GetIdentityInterface();
			SessionInterface = OnlineSubsystem->GetSessionInterface();
			StatsInterface = OnlineSubsystem->GetStatsInterface();

			InitializePartySubsystem();


			// Notify UI that we are ready for logging in.
			if (OnInitialized.IsBound())
			{
				OnInitialized.Broadcast();
			}

			// Unregister this after execution so that when we reload this scene we don't have multiple callbacks bound to this.
			Runtime->CPP_UnregisterOnStarted(OnBeamableStarted);
		}));
		FBeamRuntimeHandler RuntimeChangedHandler;
		FRuntimeError SDKInitializationErrorHandler;
		Runtime->InitSDK(RuntimeChangedHandler, SDKInitializationErrorHandler);
	}

	void InitializePartySubsystem()
	{
		PartySubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UBeamPartySubsystem>();


		PartySubsystem->OnPlayerInvitedCode.AddLambda([this](FGuid PartyId, FUserSlot UserSlot)
		{
			// Forwarding message to blueprint under the Hathora demo subsystem
			OnReceivedPartyInviteEventDelegate.Broadcast(PartyId, UserSlot);
		});

		PartySubsystem->OnPlayerInviteCanceledCode.AddLambda([this](FGuid PartyId, FUserSlot UserSlot)
		{
			// Forwarding message to blueprint under the Hathora demo subsystem
			OnReceivedPartyInviteCancelEventDelegate.Broadcast(PartyId, UserSlot);
		});

		PartySubsystem->OnPlayerInviteExpiredCode.AddLambda([this](FGuid PartyId, FUserSlot UserSlot)
		{
			// Forwarding message to blueprint under the Hathora demo subsystem
			OnReceivedPartyInviteExpiredEventDelegate.Broadcast(PartyId, UserSlot);
		});

		PartySubsystem->OnPlayerJoinedCode.AddLambda([this](FGuid PartyId, FUserSlot UserSlot)
		{
			// Forwarding message to blueprint under the Hathora demo subsystem
			OnReceivedPartyJoinEventDelegate.Broadcast(PartyId, UserSlot);
		});

		PartySubsystem->OnPlayerKickedCode.AddLambda([this](FGuid PartyId, FUserSlot UserSlot)
		{
			// Forwarding message to blueprint under the Hathora demo subsystem
			OnReceivedPartyKickEventDelegate.Broadcast(PartyId, UserSlot);
		});

		PartySubsystem->OnPlayerLeftCode.AddLambda([this](FGuid PartyId, FUserSlot UserSlot)
		{
			// Forwarding message to blueprint under the Hathora demo subsystem
			OnReceivedPartyLeftEventDelegate.Broadcast(PartyId, UserSlot);
		});

		PartySubsystem->OnPlayerPromotedToLeaderCode.AddLambda([this](FGuid PartyId, FUserSlot UserSlot)
		{
			// Forwarding message to blueprint under the Hathora demo subsystem
			OnReceivedPartyPromoteEventDelegate.Broadcast(PartyId, UserSlot);
		});
	}

public:
	UFUNCTION(BlueprintCallable)
	void CopyText(FString Text)
	{
		FPlatformApplicationMisc::ClipboardCopy(*Text);
	}

	UFUNCTION(BlueprintCallable)
	FString PastText()
	{
		FString Text;
		FPlatformApplicationMisc::ClipboardPaste(Text);
		return Text;
	}

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
		if (!IdentityInterface)
		{
			return false;
		}

		const ELoginStatus::Type LoginStatus = IdentityInterface->GetLoginStatus(0);
		return LoginStatus == ELoginStatus::Type::LoggedIn;
	}

	UFUNCTION(BlueprintCallable)
	void EnterMatchmaking(FString QueueId)
	{
		DoEnterMatchmaking(QueueId, 120);
	}

	/**
	 * Invites player to a party if the player isn't in any party create it before invite
	 */
	UFUNCTION(BlueprintCallable)
	void InvitePlayerToParty(FBeamGamerTag Player)
	{
		DoInvitePlayerToParty(Player);
	}

	/**
	* Accept Party Invite
	*/
	UFUNCTION(BlueprintCallable)
	void AcceptPartyInvite(FGuid PartyId)
	{
		DoAcceptPartyInvite(PartyId);
	}

	/**
	* Decline Party Invite
	*/
	UFUNCTION(BlueprintCallable)
	void DeclinePartyInvite(FGuid PartyId)
	{
		DoDeclinePartyInvite(PartyId);
	}

	/**
	* Leave the player party using the PartyId
	*/
	UFUNCTION(BlueprintCallable)
	void LeaveParty(FGuid PartyId)
	{
		DoLeaveParty(PartyId);
	}

	/**
	* Kick player from party
	*/
	UFUNCTION(BlueprintCallable)
	void KickPlayerFromParty(FBeamGamerTag Player)
	{
		DoKickPlayerFromParty(Player);
	}

	/**
	* Promote player to be party leader
	*/
	UFUNCTION(BlueprintCallable)
	void PromotePlayerToPartyLeader(FBeamGamerTag Player)
	{
		DoPromotePlayerToPartyLeader(Player);
	}


	/**
	 * Get all the invites for the local user slot
	 */
	UFUNCTION(BlueprintCallable)
	TArray<FBeamPartyInviteState> GetInvitesState()
	{
		return DoGetInvitesState();
	}

	/**
	 * Get the current party for the local user slot
	 */
	UFUNCTION(BlueprintCallable)
	FBeamPartyState GetPartyState()
	{
		return DoGetPartyState();
	}

	/**
	 * Get local user beam gamer tag
	 */
	UFUNCTION(BlueprintCallable)
	FBeamGamerTag GetLocalGamerTag()
	{
		FUserSlot UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();
		const UBeamRuntimeSubsystem* RuntimeSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<
			UBeamRuntimeSubsystem>();
		FBeamRealmUser RealmUser;
		if (RuntimeSubsystem->Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
		{
			return RealmUser.GamerTag;
		}
		return FBeamGamerTag();
	}

	UFUNCTION(BlueprintCallable)
	void GetOwnerUserProfileData(FString& Id, FString& Email, FString& Alias, FString& DisplayName)
	{
		if (!OnlineSubsystem)
		{
			return;
		}

		const auto LoggedInUser = IdentityInterface->GetUniquePlayerId(0);
		if (LoggedInUser)
		{
			const auto Ref = LoggedInUser.ToSharedRef();
			const auto Stats = StatsInterface->GetStats(Ref);
			Id = LoggedInUser->ToString();

			if (const auto EmailStat = Stats->Stats.Find(USER_ATTR_EMAIL))
			{
				EmailStat->GetValue(Email);
			}
			else
			{
				Email = TEXT("");
			}

			if (const auto AliasStat = Stats->Stats.Find(USER_ATTR_ALIAS))
			{
				AliasStat->GetValue(Alias);
			}
			else
			{
				Alias = TEXT("");
			}

			if (const auto DisplayNameStat = Stats->Stats.Find(USER_ATTR_DISPLAYNAME))
			{
				DisplayNameStat->GetValue(DisplayName);
			}
			else
			{
				DisplayName = TEXT("");
			}
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


	void HandleUserLoginCompleted(int32 PlatformUserIndex, bool bWasSuccessful, const FUniqueNetId& NetId,
	                              const FString& ErrorString)
	{
		if (!bWasSuccessful)
		{
			OnLoginCompleteDelegate.Broadcast(false, ErrorString);
			return;
		}

		const auto HathoraMicroservice = GEngine->GetEngineSubsystem<UBeamHathoraDemoApi>();
		const auto Req = UHathoraDemoInitializePlayerRequest::Make(GetTransientPackage(), {});
		FBeamRequestContext Ctx;
		HathoraMicroservice->CPP_InitializePlayer(GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot(), Req,
		                                          FOnHathoraDemoInitializePlayerFullResponse::CreateLambda(
			                                          [this, bWasSuccessful, ErrorString](
			                                          FHathoraDemoInitializePlayerFullResponse Resp)
			                                          {
				                                          UE_LOG(LogTemp, Display, TEXT("Ran Initialize Player %s"),
				                                                 *StaticEnum<EBeamFullResponseState>()->GetValueAsString
				                                                 (Resp.State));
				                                          if (Resp.State == RS_Success)
				                                          {
					                                          if (OnLoginCompleteDelegate.IsBound())
					                                          {
						                                          OnLoginCompleteDelegate.Broadcast(
							                                          bWasSuccessful, ErrorString);
					                                          }
				                                          }
			                                          }), Ctx, {}, this);
	}

	TArray<FBeamPartyInviteState> DoGetInvitesState()
	{
		UBeamPartySubsystem* BeamPartySubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UBeamPartySubsystem>();
		FUserSlot UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();

		TArray<FBeamPartyInviteState> Invites;
		if (BeamPartySubsystem->TryGetUserInvitesState(UserSlot, Invites))
		{
			return Invites;
		}
		return TArray<FBeamPartyInviteState>();
	}

	FBeamPartyState DoGetPartyState()
	{
		UBeamPartySubsystem* BeamPartySubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UBeamPartySubsystem>();
		FUserSlot UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();

		FBeamPartyState PartyState;
		if (BeamPartySubsystem->TryGetUserPartyState(UserSlot, PartyState))
		{
			return PartyState;
		}

		return FBeamPartyState();
	}

	void DoAcceptPartyInvite(FGuid PartyId)
	{
		UBeamPartySubsystem* BeamPartySubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UBeamPartySubsystem>();
		FUserSlot UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();

		BeamPartySubsystem->CPP_JoinPartyOperation(UserSlot, PartyId, FBeamOperationEventHandlerCode::CreateLambda(
			                                           [](FBeamOperationEvent Evt)
			                                           {
			                                           }));
	}

	void DoDeclinePartyInvite(FGuid PartyId)
	{
		UBeamPartySubsystem* BeamPartySubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UBeamPartySubsystem>();
		FUserSlot UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();

		BeamPartySubsystem->CPP_DeclinePlayerPartyInviteOperation(UserSlot, PartyId,
		                                                          FBeamOperationEventHandlerCode::CreateLambda(
			                                                          [](FBeamOperationEvent Evt)
			                                                          {
			                                                          }));
	}

	void DoInvitePlayerToParty(FBeamGamerTag Player)
	{
		UBeamPartySubsystem* BeamPartySubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UBeamPartySubsystem>();
		FUserSlot UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();

		if (!BeamPartySubsystem->IsInAParty(UserSlot))
		{
			BeamPartySubsystem->CPP_CreatePartyOperation(UserSlot, EBeamPartyRestriction::BEAM_Unrestricted, 10,
			                                             FBeamOperationEventHandlerCode::CreateLambda(
				                                             [BeamPartySubsystem, UserSlot, Player](
				                                             FBeamOperationEvent Evt)
				                                             {
					                                             if (Evt.EventType == OET_SUCCESS)
					                                             {
						                                             FBeamPartyState PartyState;
						                                             if (BeamPartySubsystem->TryGetUserPartyState(
							                                             UserSlot, PartyState))
						                                             {
							                                             BeamPartySubsystem->
								                                             CPP_InvitePlayerToPartyOperation(
									                                             UserSlot, PartyState.PartyId, Player,
									                                             FBeamOperationEventHandlerCode::CreateLambda(
										                                             [](FBeamOperationEvent Evt)
										                                             {
										                                             }));
						                                             }
					                                             }
				                                             }));
		}
		else
		{
			FBeamPartyState PartyState;
			if (BeamPartySubsystem->TryGetUserPartyState(UserSlot, PartyState))
			{
				BeamPartySubsystem->CPP_InvitePlayerToPartyOperation(UserSlot, PartyState.PartyId, Player,
				                                                     FBeamOperationEventHandlerCode::CreateLambda(
					                                                     [](FBeamOperationEvent Evt)
					                                                     {
					                                                     }));
			}
		}
	}

	void DoLeaveParty(FGuid PartyId)
	{
		UBeamPartySubsystem* BeamPartySubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UBeamPartySubsystem>();
		FUserSlot UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();

		BeamPartySubsystem->CPP_LeavePartyOperation(UserSlot, PartyId, FBeamOperationEventHandlerCode::CreateLambda(
			                                            [](FBeamOperationEvent Evt)
			                                            {
			                                            }));
	}

	void DoKickPlayerFromParty(FBeamGamerTag Player)
	{
		UBeamPartySubsystem* BeamPartySubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UBeamPartySubsystem>();
		FUserSlot UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();
		FBeamPartyState PartyState;

		if (BeamPartySubsystem->TryGetUserPartyState(UserSlot, PartyState))
		{
			BeamPartySubsystem->CPP_KickPlayerOperation(UserSlot, PartyState.PartyId, Player,
			                                            FBeamOperationEventHandlerCode::CreateLambda(
				                                            [](FBeamOperationEvent Evt)
				                                            {
				                                            }));
		}
	}

	void DoPromotePlayerToPartyLeader(FBeamGamerTag Player)
	{
		UBeamPartySubsystem* BeamPartySubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UBeamPartySubsystem>();
		FUserSlot UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();
		FBeamPartyState PartyState;
		if (BeamPartySubsystem->TryGetUserPartyState(UserSlot, PartyState))
		{
			BeamPartySubsystem->CPP_PromotePlayerToLeaderOperation(UserSlot, PartyState.PartyId, Player,
			                                                       FBeamOperationEventHandlerCode::CreateLambda(
				                                                       [](FBeamOperationEvent Evt)
				                                                       {
				                                                       }));
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
			UE_LOG(LogTemp, Display, TEXT("OnMatchmakingComplete -- SearchResults: %s"),
			       *CurrentSearch->SearchResults[0].GetSessionIdStr());

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
		GetWorld()->GetTimerManager().SetTimer(TravelDelayHandle, FTimerDelegate::CreateWeakLambda(
			                                       this, [this, ServerAddress]
			                                       {
				                                       TravelToGameServer(ServerAddress);
			                                       }), DelayToGameStart, false);
	}

	void TravelToGameServer(const FString& ServerAddress)
	{
		if (bStartedTravel)
		{
			return;
		}

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
