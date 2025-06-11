#include "OnlineSessionInterfaceBeamable.h"
#include "Misc/Guid.h"
#include "OnlineSubsystem.h"
#include "Beamable/OnlineSubsystemBeamable.h"
#include "OnlineSubsystemBeamableTypes.h"
#include "Online/OnlineBase.h"

#if WITH_ENGINE
#include "OnlineSubsystemUtils.h"
#endif //WITH_ENGINE

#include "FInternetAddressBeamable.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineAsyncTaskManager.h"
#include "OnlineIdentityBeamable.h"
#include "OnlineSessionSettings.h"
#include "Beamable/OnlineSubsystemBeamableSettings.h"
#include "AutoGen/CreateLobbyLibrary.h"
#include "AutoGen/LobbyLibrary.h"
#include "AutoGen/LobbyPlayerLibrary.h"
#include "AutoGen/Optionals/OptionalGamerTag.h"
#include "AutoGen/SubSystems/BeamMatchmakingApi.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineStatsInterface.h"
#include "Online/OnlineSessionNames.h"
#include "Subsystems/Lobby/BeamLobbySubsystem.h"
#include "Subsystems/Matchmaking/BeamMatchmakingSubsystem.h"
#include "UObject/CoreNet.h"


FOnlineSessionInfoBeamable::FOnlineSessionInfoBeamable() :
	HostAddr(nullptr),
	SessionId(FUniqueNetIdBeamable::EmptyId())
{
}

FOnlineSessionInfoBeamable::FOnlineSessionInfoBeamable(FString LobbyId) : SessionId(FUniqueNetIdBeamable::Create(LobbyId))
{
}

void FOnlineSessionInfoBeamable::Init(const FOnlineSubsystemBeamable& Subsystem)
{
}

void FNamedOnlineLobbySessionBeamable::SetLobby(ULobby* InLobby)
{
	SetLobby(InLobby, LocalOwnerId);
}

void FNamedOnlineLobbySessionBeamable::SetLobby(ULobby* InLobby, FUniqueNetIdPtr LocalOwnerIdPtr)
{
	Lobby = InLobby;
	LocalOwnerId = LocalOwnerIdPtr;
	FOnlineSessionBeamable::MapLobbyToSessionSettings(InLobby, SessionSettings);
	FOnlineSessionBeamable::MapLobbyToOnlineSession(InLobby, this);

	this->RegisteredPlayers.Empty();

	// Add players to the register players
	if (Lobby->Players.IsSet)
	{
		for (auto Player : Lobby->Players.Val)
		{
			auto UniqueId = FUniqueNetIdBeamable::Create(Player->PlayerId.Val.AsString);
			this->RegisteredPlayers.Add(UniqueId);
			UE_LOG_ONLINE_SESSION(Log, TEXT("FOnlineSessionBeamable::OnLobbyUpdated: Mapping player in Beamable Lobby to UE Session.LOBBY_ID=%s GAMERTAG=%s"), *InLobby->LobbyId.Val,
			                      *Player->PlayerId.Val.AsString);
		}
	}
}


/**
 *	Async task for ending a Beamable online session
 */
class FOnlineAsyncTaskBeamableEndSession : public FOnlineAsyncTaskBasic<FOnlineSubsystemBeamable>
{
private:
	/** Name of session ending */
	FName SessionName;

public:
	FOnlineAsyncTaskBeamableEndSession(class FOnlineSubsystemBeamable* InSubsystem, FName InSessionName) :
		FOnlineAsyncTaskBasic(InSubsystem),
		SessionName(InSessionName)
	{
	}

	~FOnlineAsyncTaskBeamableEndSession()
	{
	}

	/**
	 *	Get a human readable description of task
	 */
	virtual FString ToString() const override
	{
		return FString::Printf(TEXT("FOnlineAsyncTaskBeamableEndSession bWasSuccessful: %d SessionName: %s"), WasSuccessful(), *SessionName.ToString());
	}

	/**
	 * Give the async task time to do its work
	 * Can only be called on the async task manager thread
	 */
	virtual void Tick() override
	{
		bIsComplete = true;
		bWasSuccessful = true;
	}

	/**
	 * Give the async task a chance to marshal its data back to the game thread
	 * Can only be called on the game thread by the async task manager
	 */
	virtual void Finalize() override
	{
		IOnlineSessionPtr SessionInt = Subsystem->GetSessionInterface();
		FNamedOnlineSession* Session = SessionInt->GetNamedSession(SessionName);
		if (Session)
		{
			Session->SessionState = EOnlineSessionState::Ended;
		}
	}

	/**
	 *	Async task is given a chance to trigger it's delegates
	 */
	virtual void TriggerDelegates() override
	{
		IOnlineSessionPtr SessionInt = Subsystem->GetSessionInterface();
		if (SessionInt.IsValid())
		{
			SessionInt->TriggerOnEndSessionCompleteDelegates(SessionName, bWasSuccessful);
		}
	}
};

/**
 *	Async task for destroying a Beamable online session
 */
class FOnlineAsyncTaskBeamableDestroySession : public FOnlineAsyncTaskBasic<FOnlineSubsystemBeamable>
{
private:
	/** Name of session ending */
	FName SessionName;

public:
	FOnlineAsyncTaskBeamableDestroySession(class FOnlineSubsystemBeamable* InSubsystem, FName InSessionName) :
		FOnlineAsyncTaskBasic(InSubsystem),
		SessionName(InSessionName)
	{
	}

	~FOnlineAsyncTaskBeamableDestroySession()
	{
	}

	/**
	 *	Get a human readable description of task
	 */
	virtual FString ToString() const override
	{
		return FString::Printf(TEXT("FOnlineAsyncTaskBeamableDestroySession bWasSuccessful: %d SessionName: %s"), WasSuccessful(), *SessionName.ToString());
	}

	/**
	 * Give the async task time to do its work
	 * Can only be called on the async task manager thread
	 */
	virtual void Tick() override
	{
		bIsComplete = true;
		bWasSuccessful = true;
	}

	/**
	 * Give the async task a chance to marshal its data back to the game thread
	 * Can only be called on the game thread by the async task manager
	 */
	virtual void Finalize() override
	{
		IOnlineSessionPtr SessionInt = Subsystem->GetSessionInterface();
		if (SessionInt.IsValid())
		{
			FNamedOnlineSession* Session = SessionInt->GetNamedSession(SessionName);
			if (Session)
			{
				SessionInt->RemoveNamedSession(SessionName);
			}
		}
	}

	/**
	 *	Async task is given a chance to trigger it's delegates
	 */
	virtual void TriggerDelegates() override
	{
		IOnlineSessionPtr SessionInt = Subsystem->GetSessionInterface();
		if (SessionInt.IsValid())
		{
			SessionInt->TriggerOnDestroySessionCompleteDelegates(SessionName, bWasSuccessful);
		}
	}
};


void FOnlineSessionBeamable::Tick(float DeltaTime)
{
	SCOPE_CYCLE_COUNTER(STAT_Session_Interface);
}

FUniqueNetIdPtr FOnlineSessionBeamable::CreateSessionIdFromString(const FString& SessionIdStr)
{
	FUniqueNetIdPtr SessionId;
	if (!SessionIdStr.IsEmpty())
	{
		SessionId = FUniqueNetIdBeamable::Create(SessionIdStr);
	}
	return SessionId;
}

// Local Session Querying 	
FNamedOnlineSession* FOnlineSessionBeamable::GetNamedSession(FName SessionName)
{
	FScopeLock ScopeLock(&SessionLock);
	for (int32 SearchIndex = 0; SearchIndex < Sessions.Num(); SearchIndex++)
	{
		if (Sessions[SearchIndex].SessionName == SessionName)
		{
			return &Sessions[SearchIndex];
		}
	}
	return nullptr;
}

void FOnlineSessionBeamable::RemoveNamedSession(FName SessionName)
{
	FScopeLock ScopeLock(&SessionLock);
	for (int32 SearchIndex = 0; SearchIndex < Sessions.Num(); SearchIndex++)
	{
		if (Sessions[SearchIndex].SessionName == SessionName)
		{
			Sessions.RemoveAtSwap(SearchIndex);
			return;
		}
	}
}

EOnlineSessionState::Type FOnlineSessionBeamable::GetSessionState(FName SessionName) const
{
	FScopeLock ScopeLock(&SessionLock);
	for (int32 SearchIndex = 0; SearchIndex < Sessions.Num(); SearchIndex++)
	{
		if (Sessions[SearchIndex].SessionName == SessionName)
		{
			return Sessions[SearchIndex].SessionState;
		}
	}

	return EOnlineSessionState::NoSession;
}

bool FOnlineSessionBeamable::HasPresenceSession()
{
	FScopeLock ScopeLock(&SessionLock);
	for (int32 SearchIndex = 0; SearchIndex < Sessions.Num(); SearchIndex++)
	{
		if (Sessions[SearchIndex].SessionSettings.bUsesPresence)
		{
			return true;
		}
	}

	return false;
}

FNamedOnlineLobbySessionBeamable* FOnlineSessionBeamable::GetNamedLobbySessionBeamable(FName SessionName)
{
	return static_cast<FNamedOnlineLobbySessionBeamable*>(GetNamedSession(SessionName));
}

FNamedOnlineSessionBeamable* FOnlineSessionBeamable::GetNamedSessionBeamable(FName SessionName)
{
	return static_cast<FNamedOnlineSessionBeamable*>(GetNamedSession(SessionName));
}

FNamedOnlineLobbySessionBeamable* FOnlineSessionBeamable::AddNamedSession(FName InSessionName, ULobby* InLobby, const FOnlineSessionSettings& SessionSettings)
{
	FScopeLock ScopeLock(&SessionLock);
	return new(Sessions) FNamedOnlineLobbySessionBeamable(InSessionName, InLobby, SessionSettings);
}

FNamedOnlineLobbySessionBeamable* FOnlineSessionBeamable::AddNamedSession(FName InSessionName, ULobby* InLobby, const FOnlineSession& Session)
{
	FScopeLock ScopeLock(&SessionLock);
	return new(Sessions) FNamedOnlineLobbySessionBeamable(InSessionName, InLobby, Session);
}

FNamedOnlineSessionBeamable* FOnlineSessionBeamable::AddNamedSession(FName& InSessionName, UTicket* InToken, const FOnlineSessionSettings& SessionSettings)
{
	FScopeLock ScopeLock(&SessionLock);
	return new(Sessions) FNamedOnlineSessionBeamable(InSessionName, InToken, SessionSettings);
}

FNamedOnlineSessionBeamable* FOnlineSessionBeamable::AddNamedSession(FName& InSessionName, UTicket* InToken, const FOnlineSession& Session)
{
	FScopeLock ScopeLock(&SessionLock);
	return new(Sessions) FNamedOnlineSessionBeamable(InSessionName, InToken, Session);
}

// Matchmaking
bool FOnlineSessionBeamable::StartMatchmaking(const TArray<FUniqueNetIdRef>& LocalPlayers, FName SessionName, const FOnlineSessionSettings& NewSessionSettings,
                                              TSharedRef<FOnlineSessionSearch>& SearchSettings)
{
	// Make sure we are only joining as a single player.
	if (LocalPlayers.Num() > 1)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("Beamable does not support more than one player for matchmaking"));
		return false;
	}

	// Make sure we have a settings that describe which UBeamGameTypeContent we are meant to join the queue for.
	FString QueueName;
	if (!ensure(SearchSettings->QuerySettings.Get<FString>(SETTING_BEAMABLE_QUEUE, QueueName)))
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("Cannot find search setting QueueName for matchmaking"));
		TriggerOnMatchmakingCompleteDelegates(SessionName, false);
		return false;
	}

	// Kill the reference to any previous search parameters
	if (InProgressMatchmakingSearch.IsValid()) InProgressMatchmakingSearch.Reset();

	// Initialize the search parameters
	SearchSettings->SearchState = EOnlineAsyncTaskState::InProgress;
	InProgressMatchmakingSearch = SearchSettings;
	InProgressMatchmakingSearchName = SessionName;

	// We allow arbitrary user code to run before joining the queue; this enables users to update stats for matchmaking at the last mile if they wish to do so.
	const auto GameTypeQueue = FBeamContentId(FName(QueueName));
	const auto PlayerAccount = BeamableSubsystem->GetAccountForId(*LocalPlayers[0]);
	const auto MatchmakingSubsystem = BeamableSubsystem->GetGameInstance()->GetSubsystem<UBeamMatchmakingSubsystem>();
	const auto HookDoneHandler = FOnWaitCompleteCode::CreateLambda([this, MatchmakingSubsystem, NewSessionSettings, GameTypeQueue, SessionName, PlayerAccount](FBeamWaitCompleteEvent Evt)
	{
		TArray<FString> HookErrors;
		if (BeamableSubsystem->GetRequestTracker()->IsWaitFailed(Evt, HookErrors))
		{
			UE_LOG_ONLINE_SESSION(Warning, TEXT("Customer Hook Failed: %s"), *FString::Join(HookErrors, TEXT("\n")));
			TriggerOnMatchmakingCompleteDelegates(SessionName, false);
			return;
		}

		// Initialize the search settings
		InProgressMatchmakingSessionSettings = MakeShared<FOnlineSessionSettings>(NewSessionSettings);

		// Setup the matchmaking delegates
		FBeamOperationEventHandlerCode Handler;
		Handler.BindLambda([this, SessionName, MatchmakingSubsystem](FBeamOperationEvent Evt)
		{
			if (Evt.EventType == OET_ERROR)
			{
				UE_LOG_ONLINE_SESSION(Error, TEXT("[FOnlineSessionBeamable::StartMatchmaking] Failed to join queue: %s"), *Evt.EventCode);
				TriggerOnMatchmakingCompleteDelegates(SessionName, false);
				return;
			}

			UE_LOG_ONLINE_SESSION(Verbose, TEXT("[FOnlineSessionBeamable::StartMatchmaking] Matchmaking Queue Joined. Binding delegates to hooks."));

			FGuid TicketId;
			FGuid::Parse(Evt.EventCode, TicketId);

			FOnMatchmakingTicketUpdatedCode CanceledHandler;
			CanceledHandler.BindRaw(this, &FOnlineSessionBeamable::OnMatchmakingCanceled);
			MatchmakingSubsystem->OnMatchCancelledCode.Add(TicketId, CanceledHandler);

			FOnMatchmakingTicketUpdatedCode TimedOutHandler;
			TimedOutHandler.BindRaw(this, &FOnlineSessionBeamable::OnMatchmakingTimedOut);
			MatchmakingSubsystem->OnMatchTimedOutCode.Add(TicketId, TimedOutHandler);

			FOnMatchmakingTicketUpdatedCode ReadyHandler;
			ReadyHandler.BindRaw(this, &FOnlineSessionBeamable::OnMatchmakingReady);
			MatchmakingSubsystem->OnMatchReadyCode.Add(TicketId, ReadyHandler);
		});

		UE_LOG_ONLINE_SESSION(Log, TEXT("[FOnlineSessionBeamable::StartMatchmaking]  Trying to join queue: %s"), *GameTypeQueue.AsString);
		MatchmakingSubsystem->CPP_TryJoinQueueOperation(PlayerAccount->CurrentSlot, GameTypeQueue, {}, Handler);
	});

	FBeamWaitHandle _;
	if (!BeamableSubsystem->GetRequestTracker()->InvokeAndWaitForHooks(_, StartMatchmakingHooks, HookDoneHandler, LocalPlayers, SessionName, NewSessionSettings, SearchSettings))
	{
		UE_LOG_ONLINE_SESSION(Error, TEXT("Unbound customer Hook detected: %s."), ANSI_TO_TCHAR(__FUNCTION__));
		TriggerOnMatchmakingCompleteDelegates(SessionName, false);
	}

	return true;
}

bool FOnlineSessionBeamable::CancelMatchmaking(int32 SearchingPlayerNum, FName SessionName)
{
	const FUniqueNetIdPtr UserId = BeamableSubsystem->GetIdentityInterface()->GetUniquePlayerId(SearchingPlayerNum);
	if (!UserId.IsValid())
	{
		TriggerOnCancelMatchmakingCompleteDelegates(SessionName, false);
		return false;
	}

	return CancelMatchmaking(*UserId, SessionName);
}

bool FOnlineSessionBeamable::CancelMatchmaking(const FUniqueNetId& SearchingPlayerId, FName SessionName)
{
	UBeamMatchmakingSubsystem* MatchmakingSubsystem = BeamableSubsystem->GetGameInstance()->GetSubsystem<UBeamMatchmakingSubsystem>();
	MatchmakingSubsystem->CPP_TryLeaveQueueOperation(GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot(), FBeamOperationEventHandlerCode::CreateLambda([this, SessionName](FBeamOperationEvent Evt)
	{
		if (Evt.EventType == OET_ERROR)
		{
			UE_LOG_ONLINE_SESSION(Error, TEXT("[FOnlineSessionBeamable::StartMatchmaking] Failed to cancel matchmaking queue. SESSION_NAME=%s, ERROR=%s"), *SessionName.ToString(), *Evt.EventCode);
			TriggerOnCancelMatchmakingCompleteDelegates(SessionName, false);
			return;
		}

		UE_LOG_ONLINE_SESSION(Verbose, TEXT("[FOnlineSessionBeamable::StartMatchmaking] Failed to cancel matchmaking queue. SESSION_NAME=%s"), *SessionName.ToString());
		TriggerOnCancelMatchmakingCompleteDelegates(SessionName, true);
	}));

	return false;
}


// Lobby - Creation/Destruction
bool FOnlineSessionBeamable::CreateSession(int32 HostingPlayerNum, FName SessionName, const FOnlineSessionSettings& NewSessionSettings)
{
	IOnlineIdentityPtr IdentityInterface = BeamableSubsystem->GetIdentityInterface();
	FUniqueNetIdPtr NetId = IdentityInterface->GetUniquePlayerId(HostingPlayerNum);

	return CreateSession(*NetId.Get(), SessionName, NewSessionSettings);
}

bool FOnlineSessionBeamable::CreateSession(const FUniqueNetId& HostingPlayerId, FName SessionName, const FOnlineSessionSettings& NewSessionSettings)
{
	FString QueueName;
	if (!ensure(NewSessionSettings.Get<FString>(SETTING_BEAMABLE_QUEUE, QueueName)))
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("Cannot find search setting QueueName for matchmaking"));
		TriggerOnCreateSessionCompleteDelegates(SessionName, false);
		return false;
	}

	// Check for an existing session
	FNamedOnlineSession* Session = GetNamedSession(SessionName);

	// If a session exists, we don't allow creating 
	if (Session != nullptr)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("Already in a session."));
		TriggerOnCreateSessionCompleteDelegates(SessionName, false);
		return false;
	}

	if (!NewSessionSettings.bUseLobbiesIfAvailable)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("Lobbies is the only API Beamable supports for creating a session through this OSS API. Please make sure this is set in your settings."));
		TriggerOnCreateSessionCompleteDelegates(SessionName, false);
		return false;
	}
	auto PlayerAccount = BeamableSubsystem->GetAccountForId(HostingPlayerId);

	// create a dummy lobby for the session until it's created
	ULobby* DummyLobby = CreateDummyLobby(PlayerAccount->BeamUser.GamerTag);
	TSharedRef<FOnlineSession> NewSession = CreateSessionFromLobby(DummyLobby);

	auto NamedSession = AddNamedSession(SessionName, DummyLobby, NewSession.Get());
	NamedSession->SessionState = EOnlineSessionState::Pending;
	NamedSession->LocalOwnerId = PlayerAccount->GetUserId();

	// Our create session implementation allows customer code to run before we actually go and create the lobby.
	// Most people use this to update stats with ping information against potential regions.
	const auto GameTypeQueue = FBeamContentId(FName(QueueName));
	const auto HookDoneHandler = FOnWaitCompleteCode::CreateLambda([this, PlayerAccount, NamedSession, SessionName, GameTypeQueue, NewSessionSettings](FBeamWaitCompleteEvent Evt)
	{
		TArray<FString> Errs;
		if (BeamableSubsystem->GetRequestTracker()->IsWaitFailed(Evt, Errs))
		{
			UE_LOG_ONLINE_SESSION(Error, TEXT("Customer Hook Failed: %s."), *FString::Join(Errs, TEXT("\n")));
			TriggerOnCreateSessionCompleteDelegates(SessionName, false);
			return;
		}

		// If the customer hook worked as intended, we run our session creating logic.
		FUserSlot Slot;
		UGameInstance* GameInstance = BeamableSubsystem->GetGameInstance();
		UBeamLobbySubsystem* LobbySubsystem = GameInstance->GetSubsystem<UBeamLobbySubsystem>();
		const auto BeamOssSettings = GetDefault<UOnlineSubsystemBeamableSettings>();

		// Map the global Settings to our Lobby's Global Data (ULobby::Data)
		TMap<FString, FString> GlobalProperties;
		for (auto Setting : NewSessionSettings.Settings)
		{
			GlobalProperties.Add(Setting.Key.ToString(), Setting.Value.Data.ToString());
		}

		// Maps the MemberSettings to ULobbyPlayer::Tags
		TArray<FBeamTag> PlayerTags;
		for (auto Setting : NewSessionSettings.MemberSettings)
		{
			auto Id = Setting.Key;
			auto S = Setting.Value;
			for (auto KVP : S)
			{
				FBeamTag Tag;
				Tag.Name = FOptionalString(KVP.Key.ToString());
				Tag.Value = FOptionalString(KVP.Value.Data.ToString());
				PlayerTags.Add(Tag);
			}
		}
		auto PlayerId = PlayerAccount->GetUserId();
		PlayerTags.Add(FBeamTag{BeamOssSettings->LobbyPlayerTagDisplayNameKey, BeamableSubsystem->GetIdentityInterface()->GetPlayerNickname(*PlayerId)});

		TMap<FString, FString> LobbyData;
		for (auto Setting : NewSessionSettings.Settings)
		{
			LobbyData.Add(Setting.Key.ToString(), Setting.Value.Data.ToString());
		}


		FBeamOperationEventHandlerCode CreateLobbyHandler;
		CreateLobbyHandler.BindLambda([this, LobbySubsystem, NamedSession, SessionName, PlayerAccount, CreateLobbyHandler](FBeamOperationEvent Evt)
		{
			UE_LOG_ONLINE_SESSION(Verbose, TEXT("[FOnlineSessionBeamable::CreateSession] callback"));

			FGuid LobbyId;
			FGuid::Parse(Evt.EventCode, LobbyId);
			ULobby* Lobby = nullptr;
			if (!LobbySubsystem->TryGetLobbyById(LobbyId, Lobby))
			{
				// log lobby not found
				UE_LOG_ONLINE_SESSION(Error, TEXT("[FOnlineSessionBeamable::CreateSession] Error: Lobby not found {lobby}"), *Evt.EventCode);
				TriggerOnCreateSessionCompleteDelegates(NamedSession->SessionName, false);
				return;
			}

			// log updating lobby data
			UE_LOG_ONLINE_SESSION(Log, TEXT("[FOnlineSessionBeamable::CreateSession] Success with Passcode={passcode}. Updating Lobby Data"), *Lobby->Passcode.Val);
			NamedSession->SetLobby(Lobby);
			UE_LOG_ONLINE_SESSION(Log, TEXT("[FOnlineSessionBeamable::CreateSession] CreateLobby Success setting state to Starting"));
			NamedSession->SessionState = EOnlineSessionState::Starting;

			UE_LOG_ONLINE_SESSION(Display, TEXT("Beamable CreateLobby Success with Passcode={passcode}. Subscribing to Lobby Updates"), *Lobby->Passcode.Val);

			const auto Slot = PlayerAccount->CurrentSlot;
			const auto LobbyState = LobbySubsystem->GetCurrentSlotLobbyState(Slot);

			const auto PlayerId = PlayerAccount->GetUserId();
			// Setup and store the delegate handle for this user and lobby.
			const auto OnUpdatedDelegate = LobbyState->OnLobbyUpdatedCode.AddRaw(this, &FOnlineSessionBeamable::OnLobbyUpdated, SessionName);;
			const auto OnDisbandedDelegate = LobbyState->OnLobbyDisbandedCode.AddRaw(this, &FOnlineSessionBeamable::OnLobbyUpdated, SessionName);

			if (!OnLobbyUpdatedDelegates.Contains(PlayerId))
				OnLobbyUpdatedDelegates.Add(PlayerId, OnUpdatedDelegate);
			else
				OnLobbyUpdatedDelegates[PlayerId] = OnUpdatedDelegate;

			if (!OnLobbyDisbandedDelegates.Contains(PlayerId))
				OnLobbyDisbandedDelegates.Add(PlayerId, OnDisbandedDelegate);
			else
				OnLobbyDisbandedDelegates[PlayerId] = OnDisbandedDelegate;
		});

		UE_LOG_ONLINE_SESSION(Display, TEXT("FOnlineSessionBeamable::CreateSession: Beamable CreateLobby"));
		LobbySubsystem->CPP_CreateClosedLobbyOperation(PlayerAccount->CurrentSlot, CreateLobbyHandler, "", "", GameTypeQueue, 3, LobbyData, PlayerTags);
	});

	FBeamWaitHandle _;
	if (!BeamableSubsystem->GetRequestTracker()->InvokeAndWaitForHooks(_, PreCreateSessionHooks, HookDoneHandler, HostingPlayerId, SessionName, NewSessionSettings))
	{
		UE_LOG_ONLINE_SESSION(Error, TEXT("Unbound customer Hook detected: %s."), ANSI_TO_TCHAR(__FUNCTION__));
		TriggerOnCreateSessionCompleteDelegates(SessionName, false);
	}

	return true;
}

bool FOnlineSessionBeamable::StartSession(FName SessionName)
{
	uint32 Result = ONLINE_FAIL;

	if (FNamedOnlineLobbySessionBeamable* Session = GetNamedLobbySessionBeamable(SessionName))
	{
		// get the subsystem
		FUserSlot Slot;
		auto GameInstance = BeamableSubsystem->GetGameInstance();
		UBeamLobbySubsystem* LobbySubsystem = GameInstance->GetSubsystem<UBeamLobbySubsystem>();

		FBeamGamerTag LocalPlayerGamerTag(Session->LocalOwnerId->ToString());
		FBeamRealmUser RealmUser;
		FString NamespacedSlot;
		FString QueueName;
		if (!Session->SessionSettings.Get(SETTING_GAMEMODE, QueueName))
		{
			UE_LOG_ONLINE_SESSION(Error, TEXT("Could not get matchType (SETTING_GAMEMODE) for lobby. HOST=%s, LOCAL_OWNER=%s"), *Session->Lobby->Host.Val.AsString, *LocalPlayerGamerTag.AsString);
			TriggerOnStartSessionCompleteDelegates(SessionName, false);
			return false;
		}

		if (BeamableSubsystem->GetUserSlots()->GetUserDataWithGamerTag(LocalPlayerGamerTag, RealmUser, Slot, NamespacedSlot))
		{
			LobbySubsystem->CPP_ProvisionGameServerForLobbyOperation(Slot, FOptionalBeamContentId(QueueName), FBeamOperationEventHandlerCode::CreateLambda(
				                                                         [this, SessionName, Session](FBeamOperationEvent Evt)
				                                                         {
					                                                         if (Evt.EventType != OET_SUCCESS)
					                                                         {
						                                                         // log the error
						                                                         UE_LOG_ONLINE_SESSION(Error, TEXT("Beamable Error while Provisioning Game Server=%s"), *Evt.EventCode);
						                                                         TriggerOnStartSessionCompleteDelegates(SessionName, false);
						                                                         return;
					                                                         }

					                                                         // TODO : Brent - CommonSession seems to want to join on session create
					                                                         // TriggerOnCreateSessionCompleteDelegates(SessionName, true);
					                                                         // TriggerOnStartSessionCompleteDelegates(SessionName, true);
					                                                         UE_LOG_ONLINE_SESSION(Display, TEXT("Beamable Successfully Provisioned Game Server.HOST=%s"),
					                                                                               *Session->Lobby->Host.Val.AsString);
				                                                         }));
		}
		else
		{
			UE_LOG_ONLINE_SESSION(Error, TEXT("Local user not found! You should never see this message. HOST=%s, LOCAL_OWNER=%s"), *Session->Lobby->Host.Val.AsString, *LocalPlayerGamerTag.AsString);
			TriggerOnStartSessionCompleteDelegates(SessionName, false);
		}
	}
	else
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("No game present to update for session (%s)"), *SessionName.ToString());
		TriggerOnStartSessionCompleteDelegates(SessionName, false);
	}
	return Result == ONLINE_SUCCESS || Result == ONLINE_IO_PENDING;
}

bool FOnlineSessionBeamable::UpdateSession(FName SessionName, FOnlineSessionSettings& UpdatedSessionSettings, bool bShouldRefreshOnlineData)
{
	bool bWasSuccessful = true;

	if (FNamedOnlineLobbySessionBeamable* Session = GetNamedLobbySessionBeamable(SessionName))
	{
		// get the subsystem
		FUserSlot Slot;
		auto GameInstance = BeamableSubsystem->GetGameInstance();
		UBeamLobbySubsystem* LobbySubsystem = GameInstance->GetSubsystem<UBeamLobbySubsystem>();

		FBeamGamerTag LocalPlayerGamerTag(Session->LocalOwnerId->ToString());
		FBeamRealmUser RealmUser;
		FString NamespacedSlot;

		FUniqueNetIdRef MemberId = FUniqueNetIdBeamable::Create(LocalPlayerGamerTag.AsString);

		if (BeamableSubsystem->GetUserSlots()->GetUserDataWithGamerTag(LocalPlayerGamerTag, RealmUser, Slot, NamespacedSlot))
		{
			TArray<FBeamTag> PlayerTags;

			if (UpdatedSessionSettings.MemberSettings.Contains(MemberId))
			{
				for (auto Setting : UpdatedSessionSettings.MemberSettings[MemberId])
				{
					FBeamTag Tag;
					Tag.Name = FOptionalString(Setting.Key.ToString());
					Tag.Value = FOptionalString(Setting.Value.Data.ToString());
					PlayerTags.Add(Tag);
				}
			}

			LobbySubsystem->CPP_UpdatePlayerDataOperation(Slot, LocalPlayerGamerTag, PlayerTags, FBeamOperationEventHandlerCode::CreateLambda(
				                                              [this, SessionName, LocalPlayerGamerTag, LobbySubsystem, Session, Slot](FBeamOperationEvent Evt)
				                                              {
					                                              if (Evt.EventType != OET_SUCCESS)
					                                              {
						                                              if (Evt.EventId == TEXT("CANNOT_MODIFY_OTHER_PLAYER_TAGS_IF_NOT_HOST"))
						                                              {
							                                              // log the error
							                                              UE_LOG_ONLINE_SESSION(
								                                              Error,
								                                              TEXT("Attempted to modify player data for someone other than yourself without being the host. HOST=%s, LOCAL_PLAYER=%s"),
								                                              *Session->Lobby->Host.Val.AsString, *LocalPlayerGamerTag.AsString);
						                                              }
						                                              else
						                                              {
							                                              // log the error
							                                              UE_LOG_ONLINE_SESSION(Error, TEXT("Beamable PutLobby Error with Code=%s"), *Evt.EventCode);
						                                              }

						                                              TriggerOnUpdateSessionCompleteDelegates(SessionName, false);
						                                              return;
					                                              }

					                                              Session->Lobby = LobbySubsystem->GetCurrentLobby(Slot);
					                                              UE_LOG_ONLINE_SESSION(Display, TEXT("Beamable PutLobby Success with Passcode=%s"), *Session->Lobby->Passcode.Val);
					                                              TriggerOnUpdateSessionCompleteDelegates(SessionName, true);
				                                              }));
		}
		else
		{
			UE_LOG_ONLINE_SESSION(Error, TEXT("Local user not found! You should never see this message. HOST=%s, LOCAL_OWNER=%s"), *Session->Lobby->Host.Val.AsString, *LocalPlayerGamerTag.AsString);
			TriggerOnUpdateSessionCompleteDelegates(SessionName, false);
		}
	}
	else
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("No game present to update for session (%s)"), *SessionName.ToString());
		TriggerOnUpdateSessionCompleteDelegates(SessionName, false);
	}
	return bWasSuccessful;
}

bool FOnlineSessionBeamable::EndSession(FName SessionName)
{
	uint32 Result = ONLINE_FAIL;
	auto Session = GetNamedLobbySessionBeamable(SessionName);

	if (!Session)
	{
		// log named session not found
		UE_LOG_ONLINE_SESSION(Error, TEXT("[FOnlineSessionBeamable::EndSession] Beamable EndSession Error: Session not found {session}"), *SessionName.ToString());
		return false;
	}

	FBeamGamerTag GamerTag(Session->OwningUserId->ToString());
	FBeamRealmUser RealmUser;
	FUserSlot Slot;
	FString NamespacedSlot;
	if (BeamableSubsystem->GetUserSlots()->GetUserDataWithGamerTag(GamerTag, RealmUser, Slot, NamespacedSlot))
	{
		UBeamLobbySubsystem* LobbySubsystem = BeamableSubsystem->GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();
		LobbySubsystem->CPP_LeaveLobbyOperation(Slot, FBeamOperationEventHandlerCode::CreateLambda([this, SessionName](FBeamOperationEvent Evt)
		{
			if (Evt.EventType != OET_SUCCESS)
			{
				TriggerOnEndSessionCompleteDelegates(SessionName, false);
				UE_LOG_ONLINE_SESSION(Error, TEXT("[FOnlineSessionBeamable::EndSession] Beamable EndSession Error: Failed to leave lobby {session}"), *SessionName.ToString());
				return;
			}

			RemoveNamedSession(SessionName);
			TriggerOnEndSessionCompleteDelegates(SessionName, true);
		}));

		return Result == ONLINE_SUCCESS || Result == ONLINE_IO_PENDING;
	}

	// log named session not found
	UE_LOG_ONLINE_SESSION(Error, TEXT("[FOnlineSessionBeamable::EndSession] Beamable EndSession Error: Local user not found %s"), *SessionName.ToString());
	return false;
}

bool FOnlineSessionBeamable::DestroySession(FName SessionName, const FOnDestroySessionCompleteDelegate& CompletionDelegate)
{
	uint32 Result = ONLINE_FAIL;
	if (FNamedOnlineLobbySessionBeamable* Session = GetNamedLobbySessionBeamable(SessionName))
	{
		UBeamLobbySubsystem* LobbySubsystem = BeamableSubsystem->GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();

		// log found the session
		UE_LOG_ONLINE_SESSION(Display, TEXT("[FOnlineSessionBeamable::DestroySession] Beamable DestroySession Success: Session found {session}"), *SessionName.ToString());

		// get identity sub system
		const IOnlineIdentityPtr IdentityInterface = BeamableSubsystem->GetIdentityInterface();

		FUniqueNetIdPtr UserId = IdentityInterface->GetUniquePlayerId(0);

		FGuid LobbyId = FGuid(Session->Lobby->LobbyId.Val);

		// TODO : Brent -- how?
		FBeamOperationEventHandlerCode Handler;
		Handler.BindLambda([this, CompletionDelegate, SessionName](FBeamOperationEvent Evt)
		{
			if (Evt.EventType == OET_SUCCESS)
			{
				UE_LOG_ONLINE_SESSION(Verbose, TEXT("[FOnlineSessionBeamable::DestroySession] callback"));
				CompletionDelegate.ExecuteIfBound(SessionName, true);
				TriggerOnDestroySessionCompleteDelegates(SessionName, true);
			}

			if (Evt.EventType == OET_ERROR)
			{
				UE_LOG_ONLINE_SESSION(Verbose, TEXT("[FOnlineSessionBeamable::DestroySession] failed callback"));
				CompletionDelegate.ExecuteIfBound(SessionName, false);
				TriggerOnDestroySessionCompleteDelegates(SessionName, false);
			}
		});

		ULobby* Lobby = nullptr;

		if (LobbySubsystem->TryGetLobbyById(LobbyId, Lobby))
		{
			LobbySubsystem->CPP_LeaveLobbyOperation(GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot(), Handler);
		}
		else
		{
			// log lobby not found
			UE_LOG_ONLINE_SESSION(Error, TEXT("[FOnlineSessionBeamable::DestroySession] Error: Lobby not found {lobby}"), *LobbyId.ToString());
		}

		RemoveNamedSession(SessionName);
	}
	return Result == ONLINE_SUCCESS || Result == ONLINE_IO_PENDING;
}

bool FOnlineSessionBeamable::IsPlayerInSession(FName SessionName, const FUniqueNetId& UniqueId)
{
	return IsPlayerInSessionImpl(this, SessionName, UniqueId);
}


// Lobby - Querying/Joining
bool FOnlineSessionBeamable::FindSessions(int32 SearchingPlayerNum, const TSharedRef<FOnlineSessionSearch>& SearchSettings)
{
	uint32 Return = ONLINE_FAIL;
	const FUniqueNetId* UniqueId = BeamableSubsystem->GetIdentityInterface()->GetUniquePlayerId(SearchingPlayerNum).Get();
	return FindSessions(*UniqueId, SearchSettings);
}

bool FOnlineSessionBeamable::FindSessions(const FUniqueNetId& SearchingPlayerId, const TSharedRef<FOnlineSessionSearch>& SearchSettings)
{
	return true;
}

bool FOnlineSessionBeamable::FindSessionById(const FUniqueNetId& SearchingUserId, const FUniqueNetId& SessionId, const FUniqueNetId& FriendId,
                                             const FOnSingleSessionResultCompleteDelegate& CompletionDelegates)
{
	FOnlineSessionSearchResult EmptyResult;
	CompletionDelegates.ExecuteIfBound(0, false, EmptyResult);
	return true;
}

bool FOnlineSessionBeamable::CancelFindSessions()
{
	uint32 Return = ONLINE_FAIL;
	return Return == ONLINE_SUCCESS || Return == ONLINE_IO_PENDING;
}

bool FOnlineSessionBeamable::JoinSession(int32 PlayerNum, FName SessionName, const FOnlineSessionSearchResult& DesiredSession)
{
	auto UniqueId = BeamableSubsystem->GetIdentityInterface()->GetUniquePlayerId(PlayerNum);
	return JoinSession(*UniqueId, SessionName, DesiredSession);
}

bool FOnlineSessionBeamable::JoinSession(const FUniqueNetId& PlayerId, FName SessionName, const FOnlineSessionSearchResult& DesiredSession)
{
	uint32 Return = ONLINE_FAIL;
	FNamedOnlineSession* Session = GetNamedSession(SessionName);

	// Don't join a session if already in one or hosting one
	if (Session != NULL)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("Session (%s) already exists, can't join twice"), *SessionName.ToString());
		return false;
	}

	// Create a named session from the search result data
	auto PlayerAccount = BeamableSubsystem->GetAccountForId(PlayerId);
	auto DummyLobby = CreateDummyLobby(FBeamGamerTag{TEXT("")});
	auto NewSession = AddNamedSession(SessionName, DummyLobby, DesiredSession.Session);
	NewSession->SessionState = EOnlineSessionState::Pending;
	NewSession->LocalOwnerId = PlayerAccount->GetUserId();

	// We allow customer code to run before joining the lobby/session. 
	const auto HookDoneHandler = FOnWaitCompleteCode::CreateLambda([this, PlayerAccount, NewSession, SessionName, DesiredSession](FBeamWaitCompleteEvent Evt)
	{
		// If customer hook failed, we error out.
		TArray<FString> Errs;
		if (BeamableSubsystem->GetRequestTracker()->IsWaitFailed(Evt, Errs))
		{
			UE_LOG_ONLINE_SESSION(Error, TEXT("Customer Hook Failed. ERRORS=%s."), *FString::Join(Errs, TEXT("\n")));
			TriggerOnJoinSessionCompleteDelegates(SessionName, EOnJoinSessionCompleteResult::UnknownError);
			return;
		}

		// Gets the player account for the player joining the Lobby.
		const auto PlayerId = PlayerAccount->GetUserId();

		// Build the Player Tags for the player that's trying to join the lobby.
		TArray<FBeamTag> PlayerTags;
		if (const auto MemberSettings = DesiredSession.Session.SessionSettings.MemberSettings.Find(PlayerId))
		{
			for (FSessionSettings::TConstIterator It(*MemberSettings); It; ++It)
			{
				const FName KeyName = It.Key();
				const FOnlineSessionSetting& Setting = It.Value();
				FBeamTag Tag;
				Tag.Name = FOptionalString(KeyName.ToString());
				Tag.Value = FOptionalString(Setting.Data.ToString());
				PlayerTags.Add(Tag);
			}
		}

		// Gets the Lobby Subsystem
		auto LobbySubsystem = BeamableSubsystem->GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();

		// If its a closed lobby, we join via Passcode; if not, we join via LobbyId.
		const auto BeamOssSettings = GetDefault<UOnlineSubsystemBeamableSettings>();
		if (DesiredSession.Session.SessionSettings.Settings.Contains(FName(BeamOssSettings->LobbyPasscodeSettingsKey)))
		{
			// Gets the passcode if its there
			const auto Passcode = DesiredSession.Session.SessionSettings.Settings.FindRef(FName(BeamOssSettings->LobbyPasscodeSettingsKey)).Data.ToString();
			const auto JoinSessionHandler = FBeamOperationEventHandlerCode::CreateLambda([this, LobbySubsystem, SessionName, NewSession, PlayerAccount](FBeamOperationEvent Evt)
			{
				UE_LOG_ONLINE_SESSION(Log, TEXT("[FOnlineSessionBeamable::JoinSession] Join Session Result %s"), *Evt.EventId.ToString());

				if (Evt.EventType == OET_ERROR)
				{
					// TODO: Get list of errors (lobby full, etc...) from Justin and map this to the various EOnJoinSessionCompleteResults.
					UE_LOG_ONLINE_SESSION(Error, TEXT("[FOnlineSessionBeamable::JoinSession] Failed to join Lobby. ERROR=%s"), *Evt.EventCode);
					TriggerOnJoinSessionCompleteDelegates(SessionName, EOnJoinSessionCompleteResult::UnknownError);
					return;
				}

				// Get the Lobby Id.
				FGuid LobbyId;
				FGuid::Parse(Evt.EventCode, LobbyId);

				// We should be able to get this lobby from our LobbySubsystem.
				ULobby* Lobby = nullptr;
				if (!LobbySubsystem->TryGetLobbyById(LobbyId, Lobby))
				{
					// log lobby not found
					UE_LOG_ONLINE_SESSION(Error, TEXT("[FOnlineSessionBeamable::JoinSession] Lobby not found. LOBBY_ID=%s"), *Evt.EventCode);
					TriggerOnJoinSessionCompleteDelegates(SessionName, EOnJoinSessionCompleteResult::UnknownError);
					return;
				}

				UE_LOG_ONLINE_SESSION(Verbose, TEXT("[FOnlineSessionBeamable::JoinSession] Joined Lobby with Id. LOBBY_ID=%s"), *Lobby->LobbyId.Val);

				NewSession->SetLobby(Lobby);
				NewSession->SessionState = EOnlineSessionState::Starting;

				const auto Slot = PlayerAccount->CurrentSlot;
				const auto LobbyState = LobbySubsystem->GetCurrentSlotLobbyState(Slot);

				const auto PlayerId = PlayerAccount->GetUserId();
				// Setup and store the delegate handle for this user and lobby.
				const auto OnUpdatedDelegate = LobbyState->OnLobbyUpdatedCode.AddRaw(this, &FOnlineSessionBeamable::OnLobbyUpdated, SessionName);;
				const auto OnDisbandedDelegate = LobbyState->OnLobbyDisbandedCode.AddRaw(this, &FOnlineSessionBeamable::OnLobbyUpdated, SessionName);

				if (!OnLobbyUpdatedDelegates.Contains(PlayerId))
					OnLobbyUpdatedDelegates.Add(PlayerId, OnUpdatedDelegate);
				else
					OnLobbyUpdatedDelegates[PlayerId] = OnUpdatedDelegate;

				if (!OnLobbyDisbandedDelegates.Contains(PlayerId))
					OnLobbyDisbandedDelegates.Add(PlayerId, OnDisbandedDelegate);
				else
					OnLobbyDisbandedDelegates[PlayerId] = OnDisbandedDelegate;

				UE_LOG_ONLINE_SESSION(Verbose, TEXT("[FOnlineSessionBeamable::JoinSession] Joined Lobby By Passcode. PASSCODE=%s"), *Lobby->Passcode.Val);

				// this joins the session - actually connects to the gameserver
				// TriggerOnJoinSessionCompleteDelegates(SessionName, EOnJoinSessionCompleteResult::Success);
			});
			UE_LOG_ONLINE_SESSION(Verbose, TEXT("[FOnlineSessionBeamable::JoinSession] Trying to JoinLobby By Passcode: %s"), *Passcode);
			LobbySubsystem->CPP_JoinLobbyByPasscodeOperation(GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot(), JoinSessionHandler, Passcode, PlayerTags);
		}
		else
		{
			// Get the lobby id.
			const auto LobbyIdStr = static_cast<const FOnlineSessionInfoBeamable*>(DesiredSession.Session.SessionInfo.Get())->GetSessionId().ToString();
			FGuid LobbyId;
			if (!FGuid::Parse(LobbyIdStr, LobbyId))
			{
				// log lobby not found
				UE_LOG_ONLINE_SESSION(Error, TEXT("[FOnlineSessionBeamable::JoinSession] Lobby Id failed to parse. LOBBY_ID_STR=%s"), *LobbyIdStr);
				TriggerOnJoinSessionCompleteDelegates(SessionName, EOnJoinSessionCompleteResult::SessionDoesNotExist);
				return;
			}

			// Gets the passcode if its there			
			const auto JoinSessionHandler = FBeamOperationEventHandlerCode::CreateLambda([this, LobbySubsystem, LobbyId, SessionName, NewSession, PlayerAccount](FBeamOperationEvent Evt)
			{
				UE_LOG_ONLINE_SESSION(Log, TEXT("[FOnlineSessionBeamable::JoinSession] Join Session Result %s"), *Evt.EventId.ToString());

				if (Evt.EventType == OET_ERROR)
				{
					// TODO: Get list of errors (lobby full, etc...) from Justin and map this to the various EOnJoinSessionCompleteResults.
					UE_LOG_ONLINE_SESSION(Error, TEXT("[FOnlineSessionBeamable::JoinSession] Failed to join Lobby. ERROR=%s"), *Evt.EventCode);
					TriggerOnJoinSessionCompleteDelegates(SessionName, EOnJoinSessionCompleteResult::UnknownError);
					return;
				}

				// We should be able to get this lobby from our LobbySubsystem.
				ULobby* Lobby = nullptr;
				if (!LobbySubsystem->TryGetLobbyById(LobbyId, Lobby))
				{
					// log lobby not found
					UE_LOG_ONLINE_SESSION(Error, TEXT("[FOnlineSessionBeamable::JoinSession] Lobby not found {lobby}"), *Evt.EventCode);
					TriggerOnJoinSessionCompleteDelegates(SessionName, EOnJoinSessionCompleteResult::SessionDoesNotExist);
					return;
				}

				UE_LOG_ONLINE_SESSION(Log, TEXT("[FOnlineSessionBeamable::JoinSession] Joined Session: %s"), *Lobby->LobbyId.Val);
				NewSession->SetLobby(Lobby);
				NewSession->SessionState = EOnlineSessionState::Starting;

				// Configure the Beamable SDK to listen for updates on this lobby for this user slot.
				const auto Slot = PlayerAccount->CurrentSlot;
				const auto LobbyState = LobbySubsystem->GetCurrentSlotLobbyState(Slot);

				auto PlayerId = PlayerAccount->GetUserId();
				// Setup and store the delegate handle for this user and lobby.
				const auto OnUpdatedDelegate = LobbyState->OnLobbyUpdatedCode.AddRaw(this, &FOnlineSessionBeamable::OnLobbyUpdated, SessionName);;
				const auto OnDisbandedDelegate = LobbyState->OnLobbyDisbandedCode.AddRaw(this, &FOnlineSessionBeamable::OnLobbyUpdated, SessionName);

				if (!OnLobbyUpdatedDelegates.Contains(PlayerId))
					OnLobbyUpdatedDelegates.Add(PlayerId, OnUpdatedDelegate);
				else
					OnLobbyUpdatedDelegates[PlayerId] = OnUpdatedDelegate;

				if (!OnLobbyDisbandedDelegates.Contains(PlayerId))
					OnLobbyDisbandedDelegates.Add(PlayerId, OnDisbandedDelegate);
				else
					OnLobbyDisbandedDelegates[PlayerId] = OnDisbandedDelegate;

				UE_LOG_ONLINE_SESSION(Display, TEXT("Beamable JoinLobbyByPasscode. PASSCODE=%s"), *Lobby->Passcode.Val);

				// this joins the session - actually connects to the gameserver
				// TriggerOnJoinSessionCompleteDelegates(SessionName, EOnJoinSessionCompleteResult::Success);
			});

			UE_LOG_ONLINE_SESSION(Log, TEXT("[FOnlineSessionBeamable::JoinSession]  Beamable JoinLobby By Id: %s"), *LobbyIdStr);
			LobbySubsystem->CPP_JoinLobbyOperation(PlayerAccount->CurrentSlot, JoinSessionHandler, LobbyId, PlayerTags);
		}
	});

	FBeamWaitHandle _;
	if (!BeamableSubsystem->GetRequestTracker()->InvokeAndWaitForHooks(_, PreJoinSessionHooks, HookDoneHandler, PlayerId, SessionName, DesiredSession))
	{
		UE_LOG_ONLINE_SESSION(Error, TEXT("Unbound customer Hook detected: %s."), ANSI_TO_TCHAR(__FUNCTION__));
		TriggerOnJoinSessionCompleteDelegates(SessionName, EOnJoinSessionCompleteResult::UnknownError);
	}

	return false;
}

bool FOnlineSessionBeamable::PingSearchResults(const FOnlineSessionSearchResult& SearchResult)
{
	const auto HookDoneHandler = FOnWaitCompleteCode::CreateLambda([this](FBeamWaitCompleteEvent Evt)
	{
		// If customer hook failed, we error out.
		TArray<FString> Errs;
		if (BeamableSubsystem->GetRequestTracker()->IsWaitFailed(Evt, Errs))
		{
			UE_LOG_ONLINE_SESSION(Error, TEXT("Customer Hook Failed. ERRORS=%s."), *FString::Join(Errs, TEXT("\n")));
			TriggerOnPingSearchResultsCompleteDelegates(false);
			return;
		}

		TriggerOnPingSearchResultsCompleteDelegates(true);
	});

	FBeamWaitHandle _;
	if (!BeamableSubsystem->GetRequestTracker()->InvokeAndWaitForHooks(_, PingSearchHooks, HookDoneHandler, SearchResult))
	{
		UE_LOG_ONLINE_SESSION(Error, TEXT("Unbound customer Hook detected: %s."), ANSI_TO_TCHAR(__FUNCTION__));
		TriggerOnPingSearchResultsCompleteDelegates(false);
	}
	return true;
}

bool FOnlineSessionBeamable::FindFriendSession(int32 LocalUserNum, const FUniqueNetId& Friend)
{
	// this function has to exist due to interface definition, but it does not have a meaningful implementation in Beamable subsystem
	TArray<FOnlineSessionSearchResult> EmptySearchResult;
	TriggerOnFindFriendSessionCompleteDelegates(LocalUserNum, false, EmptySearchResult);
	return false;
};

bool FOnlineSessionBeamable::FindFriendSession(const FUniqueNetId& LocalUserId, const FUniqueNetId& Friend)
{
	// this function has to exist due to interface definition, but it does not have a meaningful implementation in Beamable subsystem
	TArray<FOnlineSessionSearchResult> EmptySearchResult;
	TriggerOnFindFriendSessionCompleteDelegates(0, false, EmptySearchResult);
	return false;
}

bool FOnlineSessionBeamable::FindFriendSession(const FUniqueNetId& LocalUserId, const TArray<FUniqueNetIdRef>& FriendList)
{
	// this function has to exist due to interface definition, but it does not have a meaningful implementation in Beamable subsystem
	TArray<FOnlineSessionSearchResult> EmptySearchResult;
	TriggerOnFindFriendSessionCompleteDelegates(0, false, EmptySearchResult);
	return false;
}

bool FOnlineSessionBeamable::SendSessionInviteToFriend(int32 LocalUserNum, FName SessionName, const FUniqueNetId& Friend)
{
	// this function has to exist due to interface definition, but it does not have a meaningful implementation in Beamable subsystem
	return false;
};

bool FOnlineSessionBeamable::SendSessionInviteToFriend(const FUniqueNetId& LocalUserId, FName SessionName, const FUniqueNetId& Friend)
{
	// this function has to exist due to interface definition, but it does not have a meaningful implementation in Beamable subsystem
	return false;
}

bool FOnlineSessionBeamable::SendSessionInviteToFriends(int32 LocalUserNum, FName SessionName, const TArray<FUniqueNetIdRef>& Friends)
{
	// this function has to exist due to interface definition, but it does not have a meaningful implementation in Beamable subsystem
	return false;
};

bool FOnlineSessionBeamable::SendSessionInviteToFriends(const FUniqueNetId& LocalUserId, FName SessionName, const TArray<FUniqueNetIdRef>& Friends)
{
	// this function has to exist due to interface definition, but it does not have a meaningful implementation in Beamable subsystem
	return false;
}

// Lobby - Connection
bool FOnlineSessionBeamable::GetResolvedConnectString(FName SessionName, FString& ConnectInfo, FName PortType)
{
	bool bSuccess = false;
	// Find the session
	FNamedOnlineSession* Session = GetNamedSession(SessionName);
	if (Session != NULL)
	{
		TSharedPtr<FOnlineSessionInfoBeamable> SessionInfo = StaticCastSharedPtr<FOnlineSessionInfoBeamable>(Session->SessionInfo);
		if (PortType == NAME_BeaconPort)
		{
			int32 BeaconListenPort = GetBeaconPortFromSessionSettings(Session->SessionSettings);
			bSuccess = GetConnectStringFromSessionInfo(SessionInfo, ConnectInfo, BeaconListenPort);
		}
		else if (PortType == NAME_GamePort)
		{
			bSuccess = GetConnectStringFromSessionInfo(SessionInfo, ConnectInfo, 0);
		}

		if (!bSuccess)
		{
			UE_LOG_ONLINE_SESSION(Warning, TEXT("Invalid session info for session %s in GetResolvedConnectString()"), *SessionName.ToString());
		}
	}
	else
	{
		UE_LOG_ONLINE_SESSION(Warning,
		                      TEXT("Unknown session name (%s) specified to GetResolvedConnectString()"),
		                      *SessionName.ToString());
	}

	return bSuccess;
}

bool FOnlineSessionBeamable::GetResolvedConnectString(const FOnlineSessionSearchResult& SearchResult, FName PortType, FString& ConnectInfo)
{
	bool bSuccess = false;
	if (SearchResult.Session.SessionInfo.IsValid())
	{
		TSharedPtr<FOnlineSessionInfoBeamable> SessionInfo = StaticCastSharedPtr<FOnlineSessionInfoBeamable>(SearchResult.Session.SessionInfo);

		if (PortType == NAME_BeaconPort)
		{
			int32 BeaconListenPort = GetBeaconPortFromSessionSettings(SearchResult.Session.SessionSettings);
			bSuccess = GetConnectStringFromSessionInfo(SessionInfo, ConnectInfo, BeaconListenPort);
		}
		else if (PortType == NAME_GamePort)
		{
			bSuccess = GetConnectStringFromSessionInfo(SessionInfo, ConnectInfo, 0);
		}
	}

	if (!bSuccess || ConnectInfo.IsEmpty())
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("Invalid session info in search result to GetResolvedConnectString()"));
	}

	return bSuccess;
}


// Lobby - Tracking Players in Session
bool FOnlineSessionBeamable::RegisterPlayer(FName SessionName, const FUniqueNetId& PlayerId, bool bWasInvited)
{
	TArray<FUniqueNetIdRef> Players;
	Players.Add(PlayerId.AsShared());
	return RegisterPlayers(SessionName, Players, bWasInvited);
}

bool FOnlineSessionBeamable::RegisterPlayers(FName SessionName, const TArray<FUniqueNetIdRef>& Players, bool bWasInvited)
{
	// TODO: If beamable is not started, we should reject connections from players
	// BeamableSubsystem->GetGameInstance()->GetSubsystem<UBeamRuntime>()->bIsBeamableStarted

	// ULobby* DedicatedServerLobby;
	// BeamableSubsystem->GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>()->TryGetDedicatedServerLobby(DedicatedServerLobby);
	// TODO -> Get the Lobby's player's gamertags, create UniqueNetIds from them and compare with the players coming in.

	bool bSuccess = false;
	FNamedOnlineSession* Session = GetNamedSession(SessionName);
	if (Session)
	{
		bSuccess = true;

		for (int32 PlayerIdx = 0; PlayerIdx < Players.Num(); PlayerIdx++)
		{
			const FUniqueNetIdRef& PlayerId = Players[PlayerIdx];

			FUniqueNetIdMatcher PlayerMatch(*PlayerId);
			if (Session->RegisteredPlayers.IndexOfByPredicate(PlayerMatch) == INDEX_NONE)
			{
				Session->RegisteredPlayers.Add(PlayerId);

				// update number of open connections
				if (Session->NumOpenPublicConnections > 0)
				{
					Session->NumOpenPublicConnections--;
				}
				else if (Session->NumOpenPrivateConnections > 0)
				{
					Session->NumOpenPrivateConnections--;
				}
			}
			else
			{
				UE_LOG_ONLINE_SESSION(Log, TEXT("Player %s already registered in session %s"), *PlayerId->ToDebugString(), *SessionName.ToString());
			}
		}
	}
	else
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("No game present to join for session (%s)"), *SessionName.ToString());
	}

	TriggerOnRegisterPlayersCompleteDelegates(SessionName, Players, bSuccess);
	return bSuccess;
}

bool FOnlineSessionBeamable::UnregisterPlayer(FName SessionName, const FUniqueNetId& PlayerId)
{
	TArray<FUniqueNetIdRef> Players;
	Players.Add(PlayerId.AsShared());
	return UnregisterPlayers(SessionName, Players);
}

bool FOnlineSessionBeamable::UnregisterPlayers(FName SessionName, const TArray<FUniqueNetIdRef>& Players)
{
	bool bSuccess = true;

	FNamedOnlineSession* Session = GetNamedSession(SessionName);
	if (Session)
	{
		for (int32 PlayerIdx = 0; PlayerIdx < Players.Num(); PlayerIdx++)
		{
			const FUniqueNetIdRef& PlayerId = Players[PlayerIdx];

			FUniqueNetIdMatcher PlayerMatch(*PlayerId);
			int32 RegistrantIndex = Session->RegisteredPlayers.IndexOfByPredicate(PlayerMatch);
			if (RegistrantIndex != INDEX_NONE)
			{
				Session->RegisteredPlayers.RemoveAtSwap(RegistrantIndex);

				// update number of open connections
				if (Session->NumOpenPublicConnections < Session->SessionSettings.NumPublicConnections)
				{
					Session->NumOpenPublicConnections++;
				}
				else if (Session->NumOpenPrivateConnections < Session->SessionSettings.NumPrivateConnections)
				{
					Session->NumOpenPrivateConnections++;
				}
			}
			else
			{
				UE_LOG_ONLINE_SESSION(Warning, TEXT("Player %s is not part of session (%s)"), *PlayerId->ToDebugString(), *SessionName.ToString());
			}
		}
	}
	else
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("No game present to leave for session (%s)"), *SessionName.ToString());
		bSuccess = false;
	}

	TriggerOnUnregisterPlayersCompleteDelegates(SessionName, Players, bSuccess);
	return bSuccess;
}

void FOnlineSessionBeamable::RegisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnRegisterLocalPlayerCompleteDelegate& Delegate)
{
	Delegate.ExecuteIfBound(PlayerId, EOnJoinSessionCompleteResult::Success);
}

void FOnlineSessionBeamable::UnregisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnUnregisterLocalPlayerCompleteDelegate& Delegate)
{
	Delegate.ExecuteIfBound(PlayerId, true);
}

void FOnlineSessionBeamable::RegisterLocalPlayers(FNamedOnlineSession* Session) const
{
#if WITH_ENGINE
	if (!BeamableSubsystem->IsDedicated())
	{
		IOnlineVoicePtr VoiceInt = BeamableSubsystem->GetVoiceInterface();
		if (VoiceInt.IsValid())
		{
			for (int32 Index = 0; Index < MAX_LOCAL_PLAYERS; Index++)
			{
				// Register the local player as a local talker
				VoiceInt->RegisterLocalTalker(Index);
			}
		}
	}
#endif //WITH_ENGINE
}

// Utilities
int32 FOnlineSessionBeamable::GetNumSessions()
{
	FScopeLock ScopeLock(&SessionLock);
	return Sessions.Num();
}

void FOnlineSessionBeamable::DumpSessionState()
{
	FScopeLock ScopeLock(&SessionLock);

	for (int32 SessionIdx = 0; SessionIdx < Sessions.Num(); SessionIdx++)
	{
		DumpNamedSession(&Sessions[SessionIdx]);
	}
}

FOnlineSessionSettings* FOnlineSessionBeamable::GetSessionSettings(FName SessionName)
{
	FNamedOnlineSession* Session = GetNamedSession(SessionName);
	if (Session)
	{
		return &Session->SessionSettings;
	}
	return NULL;
}

// Hooks into Beamable SDK
void FOnlineSessionBeamable::OnMatchmakingReady(const FBeamMatchmakingTicket& Ticket)
{
	// log
	UE_LOG_ONLINE_SESSION(Display, TEXT("Beamable Matchmaking Ready with TicketId=%s"), *Ticket.TicketId.ToString());

	auto* LobbySubsystem = BeamableSubsystem->GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();

	ULobby* Lobby;
	if (!LobbySubsystem->TryGetLobbyById(Ticket.FoundMatchLobbyId, Lobby))
	{
		UE_LOG_ONLINE_SESSION(Error, TEXT("Beamable Matchmaking Ready Error: No lobby Found {lobby}"), *Ticket.FoundMatchLobbyId.ToString());
		TriggerOnMatchmakingCompleteDelegates(InProgressMatchmakingSearchName, false);
		return;
	}

	TSharedRef<FOnlineSession> Session = CreateSessionFromLobby(Lobby);
	FOnlineSessionSearchResult SearchResult;
	SearchResult.Session = Session.Get();

	InProgressMatchmakingSearch->SearchResults.Add(SearchResult);
	InProgressMatchmakingSearch->SearchState = EOnlineAsyncTaskState::Done;

	TriggerOnMatchmakingCompleteDelegates(InProgressMatchmakingSearchName, true);

	InProgressMatchmakingSearch = nullptr;
}

void FOnlineSessionBeamable::OnMatchmakingCanceled(const FBeamMatchmakingTicket& Ticket)
{
	UE_LOG_ONLINE_SESSION(Display, TEXT("Beamable Matchmaking Canceled with TicketId={ticketId}"), *Ticket.TicketId.ToString());

	if (InProgressMatchmakingSearch.IsValid())
	{
		InProgressMatchmakingSearch->SearchState = EOnlineAsyncTaskState::Failed;
		InProgressMatchmakingSearch = nullptr;
	}
	TriggerOnCancelMatchmakingCompleteDelegates(InProgressMatchmakingSearchName, true);
}

void FOnlineSessionBeamable::OnMatchmakingSearching(const FBeamMatchmakingTicket& Ticket)
{
	// log
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("Beamable Matchmaking Searching with TicketId={ticketId}"), *Ticket.TicketId.ToString());
}

void FOnlineSessionBeamable::OnMatchmakingTimedOut(const FBeamMatchmakingTicket& Ticket)
{
	// log
	UE_LOG_ONLINE_SESSION(Display, TEXT("Beamable Matchmaking TimedOut with TicketId={ticketId}"), *Ticket.TicketId.ToString());
	TriggerOnMatchmakingCompleteDelegates(InProgressMatchmakingSearchName, false);
}

void FOnlineSessionBeamable::OnLobbyUpdated(const FUserSlot& UserSlot, ULobby* Lobby, FLobbyUpdateNotificationMessage Evt, FName SessionName)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionBeamable::OnLobbyUpdated LobbyUpdateNotification"));

	auto NamedSession = GetNamedLobbySessionBeamable(SessionName);
	if (!NamedSession)
	{
		UE_LOG_ONLINE_SESSION(Error, TEXT("FOnlineSessionBeamable::OnLobbyUpdated: Error: Session not found GameSession"));
		return;
	}

	const auto OldLobby = NamedSession->Lobby;

	switch (Evt.Type)
	{
	case EBeamLobbyEvent::BEAM_PlayerJoined:
		{
			const auto OldPlayers = OldLobby->Players.Val;
			const auto NewPlayers = Lobby->Players.Val;

			auto Joined = TArray<ULobbyPlayer*>{};
			for (ULobbyPlayer* NewPlayer : NewPlayers)
			{
				if (!OldPlayers.FindByPredicate([NewPlayer](ULobbyPlayer*& Lp) { return Lp->PlayerId.Val == NewPlayer->PlayerId.Val; }))
				{
					Joined.Add(NewPlayer);
				}
			}

			NamedSession->SetLobby(Lobby);
			for (ULobbyPlayer* JoinedPlayer : Joined)
			{
				UE_LOG_ONLINE_SESSION(Log, TEXT("FOnlineSessionBeamable::OnLobbyUpdated: Refreshing lobby... BEAM_PlayerJoined %s"), *JoinedPlayer->PlayerId.Val.AsString);
				TriggerOnSessionParticipantJoinedDelegates(SessionName, FUniqueNetIdBeamable::Create(JoinedPlayer->PlayerId.Val.AsString).Get());
			}
			break;
		}
	case EBeamLobbyEvent::BEAM_PlayerLeft:
		{
			const auto OldPlayers = OldLobby->Players.Val;
			const auto NewPlayers = Lobby->Players.Val;

			auto Left = TArray<ULobbyPlayer*>{};
			for (ULobbyPlayer* OldPlayer : OldPlayers)
			{
				if (!NewPlayers.FindByPredicate([OldPlayer](ULobbyPlayer*& Lp) { return Lp->PlayerId.Val == OldPlayer->PlayerId.Val; }))
				{
					Left.Add(OldPlayer);
				}
			}

			NamedSession->SetLobby(Lobby);
			for (ULobbyPlayer* LeftPlayer : Left)
			{
				UE_LOG_ONLINE_SESSION(Log, TEXT("FOnlineSessionBeamable::OnLobbyUpdated: Refreshing lobby... BEAM_PlayerLeft"));
				TriggerOnSessionParticipantLeftDelegates(SessionName, FUniqueNetIdBeamable::Create(LeftPlayer->PlayerId.Val.AsString).Get(), EOnSessionParticipantLeftReason::Left);
			}
			break;
		}
	case EBeamLobbyEvent::BEAM_DataChanged:
		{
			UE_LOG_ONLINE_SESSION(Log, TEXT("FOnlineSessionBeamable::OnLobbyUpdated: Refreshing lobby... BEAM_DataChanged"));
			NamedSession->SetLobby(Lobby);

			if (Lobby->Data.IsSet && Lobby->Data.Val.Contains(TEXT("host")))
			{
				NamedSession->SessionState = EOnlineSessionState::InProgress;
			}
			else
			{
				TriggerOnSessionSettingsUpdatedDelegates(SessionName, NamedSession->SessionSettings);
				// TODO : Brent - don;t we need another event for this?
				// TODO : Pedro - Set lobby call need to differentiate  between session settings and member settings
				TriggerOnSessionParticipantSettingsUpdatedDelegates(SessionName, FUniqueNetIdBeamable::Create("").Get(), NamedSession->SessionSettings);
			}
			break;
		}
	case EBeamLobbyEvent::BEAM_LobbyDisbanded:
		{
			UE_LOG_ONLINE_SESSION(Log, TEXT("FOnlineSessionBeamable::OnLobbyUpdated: BEAM_LobbyDisbanded"));
			RemoveNamedSession(SessionName);
			TriggerOnDestroySessionCompleteDelegates(SessionName, true);
			break;
		}
	case EBeamLobbyEvent::BEAM_PlayerKicked:
		{
			const auto OldPlayers = OldLobby->Players.Val;
			const auto NewPlayers = Lobby->Players.Val;

			auto Kicked = TArray<ULobbyPlayer*>{};
			for (ULobbyPlayer* OldPlayer : OldPlayers)
			{
				if (!NewPlayers.FindByPredicate([OldPlayer](ULobbyPlayer*& Lp) { return Lp->PlayerId.Val == OldPlayer->PlayerId.Val; }))
				{
					Kicked.Add(OldPlayer);
				}
			}

			NamedSession->SetLobby(Lobby);
			for (ULobbyPlayer* KickedPlayer : Kicked)
			{
				UE_LOG_ONLINE_SESSION(Log, TEXT("FOnlineSessionBeamable::OnLobbyUpdated: Refreshing lobby... BEAM_PlayerKicked"));
				TriggerOnSessionParticipantLeftDelegates(SessionName, FUniqueNetIdBeamable::Create(KickedPlayer->PlayerId.Val.AsString).Get(), EOnSessionParticipantLeftReason::Kicked);
			}
			break;
		}
	default:
		break;;
	}
}

// Utility Functions into Beamable SDK
ULobby* FOnlineSessionBeamable::CreateDummyLobby(FBeamGamerTag HostGamerTag)
{
	TArray<ULobbyPlayer*> Players;

	auto Player = ULobbyPlayerLibrary::Make(FOptionalBeamGamerTag(HostGamerTag), FOptionalDateTime(), FOptionalArrayOfBeamTag(), GetTransientPackage());
	Players.Add(Player);

	ULobby* DummyLobby = ULobbyLibrary::Make(FOptionalString(), FOptionalMatchType(), FOptionalDateTime(), FOptionalString(),
	                                         FOptionalString(), FOptionalBeamGamerTag(HostGamerTag), FOptionalString(), FOptionalLobbyRestriction(),
	                                         FOptionalInt32(2), FOptionalArrayOfLobbyPlayer(Players), FOptionalMapOfString(), GetTransientPackage());

	return DummyLobby;
}

TSharedRef<FOnlineSession> FOnlineSessionBeamable::CreateSessionFromLobby(ULobby* Lobby)
{
	// Get the OSS Settings so we know how to pre-map some things 
	const auto BeamOssSettings = GetDefault<UOnlineSubsystemBeamableSettings>();

	auto SessionSettings = FOnlineSessionSettings();
	MapLobbyToSessionSettings(Lobby, SessionSettings);

	// Create a session with the correct properties and Owner Information
	auto Session = new FOnlineSession(SessionSettings);
	MapLobbyToOnlineSession(Lobby, Session);

	return MakeShareable(Session);
}

void FOnlineSessionBeamable::MapLobbyToSessionSettings(ULobby* Lobby, FOnlineSessionSettings& SessionSettings)
{
	const auto BeamOssSettings = GetDefault<UOnlineSubsystemBeamableSettings>();
	if (Lobby->Restriction.Val == EBeamLobbyRestriction::BEAM_Open)
	{
		SessionSettings.NumPublicConnections = Lobby->MaxPlayers.Val;
		SessionSettings.NumPrivateConnections = 0;
	}
	else
	{
		SessionSettings.NumPublicConnections = 0;
		SessionSettings.NumPrivateConnections = Lobby->MaxPlayers.Val;
	}

	// Map ULobby::Data to SessionSettings
	for (auto KVP : Lobby->Data.Val)
	{
		SessionSettings.Set(FName(KVP.Key), KVP.Value);
	}

	// Map the passcode if its there
	if (Lobby->Restriction.Val == EBeamLobbyRestriction::BEAM_Closed)
	{
		SessionSettings.Set(FName(BeamOssSettings->LobbyPasscodeSettingsKey), Lobby->Passcode.Val);
	}

	SessionSettings.MemberSettings.Reset();

	// Map ULobby::Players to Member settings
	for (ULobbyPlayer* LobbyPlayer : Lobby->Players.Val)
	{
		// Map each player's tags to MemberSettings
		FUniqueNetIdRef MemberId = FUniqueNetIdBeamable::Create(LobbyPlayer->PlayerId.Val.AsString);
		if (!SessionSettings.MemberSettings.Contains(MemberId))
			SessionSettings.MemberSettings.Add(MemberId, {});

		UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionBeamable::MapLobbyToSessionSettings: Mapping Player %s"), *MemberId->ToDebugString());

		FSessionSettings& Settings = SessionSettings.MemberSettings[MemberId];
		if (LobbyPlayer->Tags.IsSet)
		{
			for (FBeamTag BeamTag : LobbyPlayer->Tags.Val)
			{
				Settings.Add(FName(BeamTag.Name.Val), BeamTag.Value.Val);
				UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionBeamable::MapLobbyToSessionSettings: Setting %s=%s"), *BeamTag.Name.Val, *BeamTag.Value.Val);
			}
		}
	}
}

void FOnlineSessionBeamable::MapLobbyToOnlineSession(ULobby* Lobby, FOnlineSession* Session)
{
	const auto BeamOssSettings = GetDefault<UOnlineSubsystemBeamableSettings>();
	Session->OwningUserId = FUniqueNetIdBeamable::Create(Lobby->Host.Val.AsString);
	if (Lobby->Restriction.Val == EBeamLobbyRestriction::BEAM_Open)
	{
		Session->NumOpenPublicConnections = Lobby->MaxPlayers.Val - Lobby->Players.Val.Num();
		Session->NumOpenPrivateConnections = 0;
	}
	else
	{
		Session->NumOpenPublicConnections = 0;
		Session->NumOpenPrivateConnections = Lobby->MaxPlayers.Val - Lobby->Players.Val.Num();
	}

	// Map the Display name of the owner user to the lobby player
	for (ULobbyPlayer* Val : Lobby->Players.Val)
	{
		if (Val->PlayerId.Val == Lobby->Host.Val)
		{
			if (Val->Tags.IsSet)
			{
				for (FBeamTag BeamTag : Val->Tags.Val)
				{
					if (BeamTag.Name.Val == BeamOssSettings->UOnlineSubsystemBeamableSettings::LobbyPlayerTagDisplayNameKey)
					{
						Session->OwningUserName = BeamTag.Value.Val;
					}
				}
			}
		}
	}

	auto Info = new FOnlineSessionInfoBeamable(Lobby->LobbyId.Val);
	auto IP = new FInternetAddressBeamable();
	// Map the InternetAddress stuff we need to connect if its there.
	if (Lobby->Data.IsSet)
	{
		bool bIsValid;
		if (Lobby->Data.Val.Contains(BeamOssSettings->LobbyDataHostKey)) IP->SetIp(*Lobby->Data.Val[BeamOssSettings->LobbyDataHostKey], bIsValid);
		if (Lobby->Data.Val.Contains(BeamOssSettings->LobbyDataPortKey)) IP->SetPort(FCString::Atoi(*Lobby->Data.Val[BeamOssSettings->LobbyDataPortKey]));
	}

	Info->HostAddr = MakeShareable(IP);
	Session->SessionInfo = MakeShareable(Info);
}

bool FOnlineSessionBeamable::IsSessionJoinable(const FNamedOnlineSession& Session)
{
	const FOnlineSessionSettings& Settings = Session.SessionSettings;

	// LAN beacons are implicitly advertised.
	const bool bIsAdvertised = Settings.bShouldAdvertise || Settings.bIsLANMatch;
	const bool bIsMatchInProgress = Session.SessionState == EOnlineSessionState::InProgress;
	const bool bIsMatchedning = Session.SessionState == EOnlineSessionState::Pending;

	const bool bJoinableFromProgress = (!bIsMatchInProgress || Settings.bAllowJoinInProgress);

	const bool bAreSpacesAvailable = Session.NumOpenPublicConnections > 0;

	// LAN matches don't care about private connections / invites.
	// LAN matches don't care about presence information.
	// return bIsAdvertised && bJoinableFromProgress && bAreSpacesAvailable;
	return true;
}

bool FOnlineSessionBeamable::GetConnectStringFromSessionInfo(TSharedPtr<FOnlineSessionInfoBeamable>& SessionInfo, FString& ConnectInfo, int32 PortOverride)
{
	bool bSuccess = false;
	if (SessionInfo.IsValid())
	{
		if (SessionInfo->HostAddr.IsValid() && SessionInfo->HostAddr->IsValid())
		{
			if (PortOverride != 0)
			{
				ConnectInfo = FString::Printf(TEXT("%s:%d"), *SessionInfo->HostAddr->ToString(false), PortOverride);
			}
			else
			{
				ConnectInfo = FString::Printf(TEXT("%s"), *SessionInfo->HostAddr->ToString(true));
			}

			bSuccess = true;
		}
	}
	else
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("Invalid session info object in GetConnectStringFromSessionInfo()"));
	}

	return bSuccess;
}
