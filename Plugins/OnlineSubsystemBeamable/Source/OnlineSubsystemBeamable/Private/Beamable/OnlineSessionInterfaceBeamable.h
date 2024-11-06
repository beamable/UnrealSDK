#pragma once

#include "CoreMinimal.h"
#include "Beamable/FInternetAddressBeamable.h"
#include "Online/CoreOnline.h"
#include "Misc/ScopeLock.h"
#include "OnlineSessionSettings.h"
#include "Beamable/OnlineSubsystemBeamableSettings.h"
#include "Beamable/OnlineSubsystemBeamableTypes.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Online/LANBeacon.h"
#include "Subsystems/Matchmaking/BeamMatchmakingSubsystem.h"
#include "AutoGen/SubSystems/BeamLobbyApi.h"

#define SETTING_BEAMABLE_QUEUE FName(TEXT("GAMEMODE"))

struct FLobbyUpdateNotificationMessage;
class FOnlineSubsystemBeamable;

class FNamedOnlineSessionBeamable : public FNamedOnlineSession
{
public:
	UTicket* Ticket;

	FNamedOnlineSessionBeamable(const FName& InSessionName, UTicket* InTicket, const FOnlineSessionSettings& InSessionSettings) :
		FNamedOnlineSession(InSessionName, InSessionSettings)
	{
		Ticket = InTicket;
	}

	FNamedOnlineSessionBeamable(const FName& InSessionName, UTicket* InTicket, const FOnlineSession& Session) :
		FNamedOnlineSession(InSessionName, Session)
	{
		Ticket = InTicket;
	}

	virtual ~FNamedOnlineSessionBeamable()
	{
		Ticket = nullptr;
	}
};

class FNamedOnlineLobbySessionBeamable : public FNamedOnlineSession
{
public:
	ULobby* Lobby;

	FNamedOnlineLobbySessionBeamable(FName InSessionName, ULobby* InLobby, const FOnlineSessionSettings& InSessionSettings) :
		FNamedOnlineSession(InSessionName, InSessionSettings)
	{
		Lobby = InLobby;
	}

	FNamedOnlineLobbySessionBeamable(FName InSessionName, ULobby* InLobby, const FOnlineSession& Session) :
		FNamedOnlineSession(FName(InSessionName), Session)
	{
		Lobby = InLobby;
	}

	virtual ~FNamedOnlineLobbySessionBeamable()
	{
		Lobby = nullptr;
	}

	void SetLobby(ULobby* InLobby);
	void SetLobby(ULobby* InLobby, FUniqueNetIdPtr LocalOwnerIdPtr);
};

DEFINE_BEAM_OPERATION_HOOK_FourParams(FPreStartMatchmakingHook, const TArray<FUniqueNetIdRef>&, FName, const FOnlineSessionSettings&, TSharedRef<FOnlineSessionSearch>&);
DEFINE_BEAM_OPERATION_HOOK_ThreeParams(FPreCreatedSessionHook, const FUniqueNetId&, FName, const FOnlineSessionSettings&);
DEFINE_BEAM_OPERATION_HOOK_ThreeParams(FPreJoinedSessionHook, const FUniqueNetId&, FName, const FOnlineSessionSearchResult&);
DEFINE_BEAM_OPERATION_HOOK_OneParam(FPingSearchHook, const FOnlineSessionSearchResult&);


/**
 * Interface definition for the online services session services 
 * Session services are defined as anything related managing a session 
 * and its state within a platform service
 */
class FOnlineSessionBeamable : public IOnlineSession
{
private:
	/** Reference to the main Beamable subsystem */
	class FOnlineSubsystemBeamable* BeamableSubsystem;

	/** Handles advertising sessions over LAN and client searches */
	FLANSession LANSessionManager;
	FDelegateHandle LobbyNotificationHandle;

public:
	/** Hidden on purpose */
	FOnlineSessionBeamable() : BeamableSubsystem(nullptr), CurrentSessionSearch(nullptr), SessionSearchStartInSeconds(0)
	{
	}

	FOnlineSessionBeamable(class FOnlineSubsystemBeamable* InSubsystem) : BeamableSubsystem(InSubsystem), CurrentSessionSearch(nullptr), SessionSearchStartInSeconds(0)
	{
	}

	virtual ~FOnlineSessionBeamable() override
	{
	}

	/**
	 * Session tick for various background tasks
	 */
	void Tick(float DeltaTime);

	// IOnlineSession
	virtual FUniqueNetIdPtr CreateSessionIdFromString(const FString& SessionIdStr) override;

	// Local Session Querying 	
	virtual FNamedOnlineSession* GetNamedSession(FName SessionName) override;
	virtual void RemoveNamedSession(FName SessionName) override;
	virtual EOnlineSessionState::Type GetSessionState(FName SessionName) const override;
	virtual bool HasPresenceSession() override;
	FNamedOnlineLobbySessionBeamable* GetNamedLobbySessionBeamable(FName SessionName);
	FNamedOnlineSessionBeamable* GetNamedSessionBeamable(FName SessionName);
	FNamedOnlineLobbySessionBeamable* AddNamedSession(FName InSessionName, ULobby* InLobby, const FOnlineSessionSettings& SessionSettings);
	FNamedOnlineLobbySessionBeamable* AddNamedSession(FName InSessionName, ULobby* InLobby, const FOnlineSession& Session);
	FNamedOnlineSessionBeamable* AddNamedSession(FName& InSessionName, UTicket* InToken, const FOnlineSessionSettings& SessionSettings);
	FNamedOnlineSessionBeamable* AddNamedSession(FName& InSessionName, UTicket* InToken, const FOnlineSession& Session);

	// Matchmaking Queues
	virtual bool StartMatchmaking(const TArray<FUniqueNetIdRef>& LocalPlayers, FName SessionName, const FOnlineSessionSettings& NewSessionSettings, TSharedRef<FOnlineSessionSearch>& SearchSettings) override;
	virtual bool CancelMatchmaking(int32 SearchingPlayerNum, FName SessionName) override;
	virtual bool CancelMatchmaking(const FUniqueNetId& SearchingPlayerId, FName SessionName) override;

	// Lobby - Creation/Destruction
	virtual bool CreateSession(int32 HostingPlayerNum, FName SessionName, const FOnlineSessionSettings& NewSessionSettings) override;
	virtual bool CreateSession(const FUniqueNetId& HostingPlayerId, FName SessionName, const FOnlineSessionSettings& NewSessionSettings) override;
	virtual bool StartSession(FName SessionName) override;
	virtual bool UpdateSession(FName SessionName, FOnlineSessionSettings& UpdatedSessionSettings, bool bShouldRefreshOnlineData = true) override;
	virtual bool EndSession(FName SessionName) override;
	virtual bool DestroySession(FName SessionName, const FOnDestroySessionCompleteDelegate& CompletionDelegate = FOnDestroySessionCompleteDelegate()) override;
	virtual bool IsPlayerInSession(FName SessionName, const FUniqueNetId& UniqueId) override;

	// Lobby - Querying and Joining 
	virtual bool FindSessions(int32 SearchingPlayerNum, const TSharedRef<FOnlineSessionSearch>& SearchSettings) override;
	virtual bool FindSessions(const FUniqueNetId& SearchingPlayerId, const TSharedRef<FOnlineSessionSearch>& SearchSettings) override;
	virtual bool FindSessionById(const FUniqueNetId& SearchingUserId, const FUniqueNetId& SessionId, const FUniqueNetId& FriendId, const FOnSingleSessionResultCompleteDelegate& CompletionDelegate) override;
	virtual bool CancelFindSessions() override;
	virtual bool JoinSession(int32 PlayerNum, FName SessionName, const FOnlineSessionSearchResult& DesiredSession) override;
	virtual bool JoinSession(const FUniqueNetId& PlayerId, FName SessionName, const FOnlineSessionSearchResult& DesiredSession) override;
	virtual bool PingSearchResults(const FOnlineSessionSearchResult& SearchResult) override;

	// TODO: Requires BeamableCoreRuntime UFriendsSubsystem implementation   
	virtual bool FindFriendSession(int32 LocalUserNum, const FUniqueNetId& Friend) override;
	virtual bool FindFriendSession(const FUniqueNetId& LocalUserId, const FUniqueNetId& Friend) override;
	virtual bool FindFriendSession(const FUniqueNetId& LocalUserId, const TArray<FUniqueNetIdRef>& FriendList) override;
	virtual bool SendSessionInviteToFriend(int32 LocalUserNum, FName SessionName, const FUniqueNetId& Friend) override;
	virtual bool SendSessionInviteToFriend(const FUniqueNetId& LocalUserId, FName SessionName, const FUniqueNetId& Friend) override;
	virtual bool SendSessionInviteToFriends(int32 LocalUserNum, FName SessionName, const TArray<FUniqueNetIdRef>& Friends) override;
	virtual bool SendSessionInviteToFriends(const FUniqueNetId& LocalUserId, FName SessionName, const TArray<FUniqueNetIdRef>& Friends) override;

	// Lobby - Connection
	virtual bool GetResolvedConnectString(FName SessionName, FString& ConnectInfo, FName PortType) override;
	virtual bool GetResolvedConnectString(const FOnlineSessionSearchResult& SearchResult, FName PortType, FString& ConnectInfo) override;

	// Lobby - Tracking Players in Session
	virtual bool RegisterPlayer(FName SessionName, const FUniqueNetId& PlayerId, bool bWasInvited) override;
	virtual bool RegisterPlayers(FName SessionName, const TArray<FUniqueNetIdRef>& Players, bool bWasInvited = false) override;
	virtual bool UnregisterPlayer(FName SessionName, const FUniqueNetId& PlayerId) override;
	virtual bool UnregisterPlayers(FName SessionName, const TArray<FUniqueNetIdRef>& Players) override;
	virtual void RegisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnRegisterLocalPlayerCompleteDelegate& Delegate) override;
	virtual void UnregisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnUnregisterLocalPlayerCompleteDelegate& Delegate) override;
	void RegisterLocalPlayers(class FNamedOnlineSession* Session) const;

	// Utilities
	virtual FOnlineSessionSettings* GetSessionSettings(FName SessionName) override;
	virtual int32 GetNumSessions() override;
	virtual void DumpSessionState() override;

	virtual FNamedOnlineSession* AddNamedSession(FName InSessionName, const FOnlineSession& Session) override { return nullptr; }
	virtual FNamedOnlineSession* AddNamedSession(FName InSessionName, const FOnlineSessionSettings& SessionSettings) override { return nullptr; }
	// End of IOnlineSession


protected:
	/**
	 * Critical sections for thread safe operation of session lists
	 * 
	 */
	mutable FCriticalSection SessionLock;

	/**
	 * Current session settings
	 * 
	 */
	TArray<FNamedOnlineLobbySessionBeamable> Sessions;

	/**
	 * Current search object
	 * 
	 */
	TSharedPtr<FOnlineSessionSearch> CurrentSessionSearch;

	/**
	 * Per User Delegates.
	 * */
	TUniqueNetIdMap<FDelegateHandle> OnLobbyUpdatedDelegates;

	/**
	 * Per User Delegates for lobby disbanded.
	 * */
	TUniqueNetIdMap<FDelegateHandle> OnLobbyDisbandedDelegates;

	/**
	 * Current search start time. 
	 */
	double SessionSearchStartInSeconds;

	/**
	 * The SessionName passed into StartMatchmaking
	 */
	FName InProgressMatchmakingSearchName;

	/**
	 * The matchmaking search in progress
	*/
	TSharedPtr<FOnlineSessionSearch> InProgressMatchmakingSearch;

	/**
	 * Keep track of the state of a matchmaking search.  
	 */
	TSharedPtr<FOnlineSessionSettings> InProgressMatchmakingSessionSettings;

	void OnMatchmakingReady(const FBeamMatchmakingTicket& Ticket);
	void OnMatchmakingCanceled(const FBeamMatchmakingTicket& Ticket);
	void OnMatchmakingSearching(const FBeamMatchmakingTicket& Ticket);
	void OnMatchmakingTimedOut(const FBeamMatchmakingTicket& Ticket);

	/**
	 * Callback bound to UBeamLobbyState's whenever a user joins/creates a lobby. 
	 */
	void OnLobbyUpdated(const FUserSlot& UserSlot, ULobby* Lobby, FLobbyUpdateNotificationMessage Evt, FName SessionName);

public:
	/**
	 * Creates a dummy lobby instance to serve as a stand-in while we wait for requests that make the actual lobby to finish. 
	 */
	static ULobby* CreateDummyLobby(FBeamGamerTag HostGamerTag);

	/**
	 * Creates a new FOnlineSession instance from a ULobby. 
	 */
	static TSharedRef<FOnlineSession> CreateSessionFromLobby(ULobby* Lobby);
	/**
	 * Maps ULobby properties into FOnlineSessionSettings. This defines where each ULobby property ends up in the UE representation. 
	 */
	static void MapLobbyToSessionSettings(ULobby* Lobby, FOnlineSessionSettings& SessionSettings);

	/**
	 * Maps ULobby properties into FOnlineSessionSettings. This defines where each ULobby property ends up in the UE representation.
	 */
	static void MapLobbyToOnlineSession(ULobby* Lobby, FOnlineSession* Session);

	/**
	 * Determines whether this particular session is joinable.
	 *
	 * @return true if yes
	 */
	static bool IsSessionJoinable(const FNamedOnlineSession& Session);

	/**
	 * Gets the connection string from a beamable session.
	 */
	static bool GetConnectStringFromSessionInfo(TSharedPtr<FOnlineSessionInfoBeamable>& SessionInfo, FString& ConnectInfo, int32 PortOverride);

	// Hooks	
	TArray<FPreStartMatchmakingHook> StartMatchmakingHooks;
	TArray<FPreCreatedSessionHook> PreCreateSessionHooks;
	TArray<FPreJoinedSessionHook> PreJoinSessionHooks;
	TArray<FPingSearchHook> PingSearchHooks;
};

typedef TSharedPtr<FOnlineSessionBeamable, ESPMode::ThreadSafe> FOnlineSessionBeamablePtr;
