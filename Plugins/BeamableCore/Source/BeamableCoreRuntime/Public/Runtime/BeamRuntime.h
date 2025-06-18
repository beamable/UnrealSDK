// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "AutoGen/SubSystems/BeamAccountsApi.h"
#include "AutoGen/SubSystems/BeamAuthApi.h"
#include "AutoGen/SubSystems/Realms/GetClientDefaultsRequest.h"
#include "BeamNotifications/BeamNotifications.h"

#include "UserSlots/BeamUserSlots.h"

#include "RequestTracker/BeamWaitHandle.h"
#include "RequestTracker/BeamOperationHandle.h"
#include "RequestTracker/BeamOperation.h"
#include "RequestTracker/BeamRequestTracker.h"

#include "Serialization/ObjectReader.h"
#include "Serialization/ObjectWriter.h"

#include "BeamRuntime.generated.h"

class UBeamRuntimeSubsystem;
class UBeamNotifications;
class UBeamConnectivityManager;

/**
 * State of connectivity for a specific UserSlot.
 *
 * - Offline: UserSlot is not authenticated OR the websocket connection for that slot was lost. 
 * - Fixup: UserSlot's websocket connection has been reestablished but user-code has not yet called 
 * - Online: UserSlot is connected and has the local state synchronized with the Beamable Backend.
 */
UENUM()
enum EBeamRuntimeConnectivityState
{
	CONN_Offline,
	CONN_Fixup,
	CONN_Online,
};


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORERUNTIME_API UBeamMultiFactorLoginData : public UObject, public IBeamOperationEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, DisplayName="Microservice Id", Category="Beam")
	FString MicroserviceId = {};
	UPROPERTY(BlueprintReadOnly, EditAnywhere, DisplayName="Microservice Id", Category="Beam")
	FString FederationId = {};
	UPROPERTY(BlueprintReadOnly, EditAnywhere, DisplayName="Microservice Id", Category="Beam")
	FString FederatedUserId = {};
	UPROPERTY(BlueprintReadOnly, EditAnywhere, DisplayName="Microservice Id", Category="Beam")
	FString FederatedUserAuthToken = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Challenge Token", Category="Beam")
	FString ChallengeToken = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Solution", Category="Beam")
	FString Solution = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Original Operation", Category="Beam")
	FBeamOperationHandle OperationHandler;


	UChallengeSolution* GetChallengeSolutionGenerated();

	void SetChallengeSolution(UChallengeSolution* ChallengeSolution);

	UFUNCTION(BlueprintCallable)
	inline FString GetChallengeDecoded()
	{
		FString ChallengeDecodedString = "";
		FString _;

		ChallengeToken.Split(".", &ChallengeDecodedString, &_);

		FString ChallengeDecodedBytes;
		FBase64::Decode(ChallengeDecodedString, ChallengeDecodedBytes);

		return ChallengeDecodedBytes;
	}
};

DECLARE_DELEGATE_OneParam(FOnBeamConnectivityEventCode, UBeamConnectivityManager*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeamConnectivityEvent, UBeamConnectivityManager*, Manager);

/**
 * Manager that tracks connectivity states and the DAG of FOfflineOperationData to run during the Fixup process.
 * Exposes an API to manage the DAG while in Offline modes.
 */
UCLASS(BlueprintType)
class BEAMABLECORERUNTIME_API UBeamConnectivityManager : public UObject
{
	GENERATED_BODY()

	friend class UBeamRuntime;

	EBeamRuntimeConnectivityState CurrentState;
	FTSTicker::FDelegateHandle FixupUpdateHandle;
	FTSTicker::FDelegateHandle ReconnectingUpdateHandle;

	/**
	 * Websocket notifications connection handler. 
	 */
	void ConnectionHandler(const FNotificationEvent& Evt, FBeamRealmUser BeamRealmUser, FBeamOperationHandle Op);

public:
	UPROPERTY()
	UBeamRuntime* Runtime;
	UPROPERTY()
	UBeamUserSlots* UserSlots;
	UPROPERTY()
	UBeamRequestTracker* RequestTracker;
	UPROPERTY()
	UBeamNotifications* Notifications;

	UPROPERTY(BlueprintReadOnly)
	FUserSlot UserSlot;

	/**
		* @brief Bind a function to this that defines the process of recovering from a connectivity loss event (CurrentState == CONN_Fixup).
		*/
	UPROPERTY(BlueprintAssignable)
	FOnBeamConnectivityEvent FixupTick;
	/** @copydoc FixupTick	 */
	FOnBeamConnectivityEventCode FixupTickCode;


	/**
	* @brief Bind a function to this that will run ONCE when the connection is re-established but BEFORE we set up the FixupUpdate.  
	 */
	UPROPERTY(BlueprintAssignable)
	FOnBeamConnectivityEvent OnReconnected;

	/**	@copydoc OnReconnected	 */
	FOnBeamConnectivityEventCode OnReconnectedCode;

	/**
	*  @brief Bind a function to this that defines a tick function that runs every frame while this user's CurrentState == CONN_Offline.
	*/
	UPROPERTY(BlueprintAssignable)
	FOnBeamConnectivityEvent ReconnectionTick;
	/** @copydoc ReconnectionTick	*/
	FOnBeamConnectivityEventCode ReconnectionTickCode;

	/**
	* @brief Bind a function to this that will run ONCE when the reconnection process begins (when is detected BEFORE we set up the ReconnectionUpdate tick).  
	 */
	UPROPERTY(BlueprintAssignable)
	FOnBeamConnectivityEvent OnConnectionLost;

	/**	@copydoc OnConnectionLost	 */
	FOnBeamConnectivityEventCode OnConnectionLostCode;


	/**
	 * The number of times the connection was dropped this session.
	 * TODO: Should reset when a user logs out from this user slot.
	 */
	UPROPERTY(BlueprintReadOnly)
	int32 ConnectionLostCountInSession;


	/**
	 * Current number of reconnection attempts.
	 */
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentReconnectionCount;

	/**
	 * The last time in which we detected a connection loss.
	 * Holds the session start time.  
	 */
	UPROPERTY(BlueprintReadOnly)
	FDateTime CurrentConnectionLostTime;


	/**
	 * @return Whether the owner of this manager is authenticated.
	 */
	UFUNCTION(BlueprintCallable)
	bool IsAuthenticated() const { return GEngine->GetEngineSubsystem<UBeamUserSlots>()->IsUserSlotAuthenticated(UserSlot, this); }

	/**
	 * @return Whether the slot this manager is associated with is authenticated AND if we are offline. The common case being: frictionless auth is disabled.
	 */
	UFUNCTION(BlueprintCallable)
	bool IsUnauthenticatedOfflineUser() const { return !IsAuthenticated() && CurrentState == CONN_Offline; }

	/**
	 * @return If we are authenticated, but have failed to connect the websocket during the auth flow. 
	 */
	UFUNCTION(BlueprintCallable)
	bool HasNeverConnectedThisSession() const { return IsAuthenticated() && CurrentState == CONN_Offline && !ConnectionLostCountInSession; }

	/**
	 * @return If we are authenticated and were connected at some point and the connection was lost. 
	 */
	UFUNCTION(BlueprintCallable)
	bool IsDisconnected() const { return IsAuthenticated() && CurrentState == CONN_Offline && ConnectionLostCountInSession; }

	/**
	 * @return If we are authenticated, lost our websocket connection and then recovered it; we are now in Fixup. 
	 */
	UFUNCTION(BlueprintCallable)
	bool IsInFixup() const { return IsAuthenticated() && CurrentState == CONN_Fixup; }

	/**
	 * Game-makers should call this from inside their FixupUpdate once their fix up is finished.
	 */
	UFUNCTION(BlueprintCallable)
	void NotifyFixupComplete() { if (IsInFixup()) { CurrentState = CONN_Online; } }
};


DECLARE_DYNAMIC_DELEGATE(FBeamRuntimeHandler);

DECLARE_DELEGATE(FBeamRuntimeHandlerCode);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeamRuntimeEvent);

DECLARE_MULTICAST_DELEGATE(FBeamRuntimeEventCode);

DECLARE_DYNAMIC_DELEGATE_OneParam(FUserStateChangedHandler, const FUserSlot&, UserSlot);

DECLARE_DELEGATE_OneParam(FUserStateChangedHandlerCode, const FUserSlot&);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUserStateChangedEvent, const FUserSlot&, Slot);

DECLARE_MULTICAST_DELEGATE_OneParam(FUserStateChangedEventCode, const FUserSlot&);

DECLARE_DYNAMIC_DELEGATE_OneParam(FRuntimeError, FString, ErrorMessage);

DECLARE_DYNAMIC_DELEGATE_OneParam(FOperationError, const TArray<FBeamOperationEvent>&, OperationEventsWithErrors);

DECLARE_DELEGATE_OneParam(FOperationErrorCode, const TArray<FBeamOperationEvent>&);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSdkInitFailedEvent, const TArray<FBeamOperationEvent>&, OperationEventsWithErrors);

DECLARE_MULTICAST_DELEGATE_OneParam(FSdkInitFailedEventCode, const TArray<FBeamOperationEvent>&) ;

DECLARE_DYNAMIC_DELEGATE_TwoParams(FUserInitFailedHandler, const FUserSlot&, UserSlot, const TArray<FBeamOperationEvent>&, OperationEventsWithErrors);

DECLARE_DELEGATE_TwoParams(FUserInitFailedHandlerCode, const FUserSlot&, const TArray<FBeamOperationEvent>&);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUserInitFailedEvent, const FUserSlot&, UserSlot, const TArray<FBeamOperationEvent>&, OperationEventsWithErrors);

DECLARE_MULTICAST_DELEGATE_TwoParams(FUserInitFailedEventCode, const FUserSlot&, const TArray<FBeamOperationEvent>&);

/**
 * State of SDK intialization.
 *
 * - NotInitialized: The sdk initialization did not start yet.
 * - Initializing: The sdk initialization has begun but did not finish yet.
 * - Initialized: The sdk is now initialized and ready to be used.
 * - InitializationFailed : The sdk initialization process started but ended up with error.
 */
UENUM()
enum ESDKState
{
	NotInitialized,
	Initializing,
	Initialized,
	InitializationFailed
};

/**
 * 
 */
UCLASS(BlueprintType, meta=(Namespace="Beam"))
class BEAMABLECORERUNTIME_API UBeamRuntime : public UGameInstanceSubsystem
{
	friend class UBeamConnectivityManager;

	GENERATED_BODY()

	/** @brief Initializes the subsystem.  */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** List of subsystems that can not be manually initialized because all the other sub systems are dependent on
	* Or the sdk will not be functioning without it
	 */
	TArray<TSubclassOf<UBeamRuntimeSubsystem>> GetRequiredSubsystems();

	/**
	 * @brief This gets called the frame after all the subsystem initializations have happened.
	 * This enables all subsystems to have a chance to subscribe to BeamRuntime events should they choose to do so.
	 * This is handled automatically for by all UBeamRuntimeSubsystems.
	 */
	virtual void TriggerInitializeWhenUnrealReady(bool bApplyFrictionlessLogin, TMap<FString, FString> LoginInitProperties, FBeamRuntimeHandler OnStartedHandler, FRuntimeError OnStartedFailedHandler);

	/**
	 * @brief This gets called after all runtime systems had the opportunity to make requests to Beamable that do not depend on content information.
	 */
	void TriggerOnBeamableStarting(FBeamWaitCompleteEvent Evt, bool bApplyFrictionlessLogin, TMap<FString, FString> LoginInitProperties, FBeamRuntimeHandler OnStartedHandler, FRuntimeError OnStartedFailedHandler);

	/**
	 * @brief This gets called after all runtime systems had the opportunity to make initialization requests to Beamable that DO depend on content data.
	 */
	void TriggerOnContentReady(FBeamWaitCompleteEvent Evt, bool bApplyFrictionlessLogin, TMap<FString, FString> LoginInitProperties, FBeamRuntimeHandler OnStartedHandler, FRuntimeError OnStartedFailedHandler);

	/**
	 * @brief This gets called after all runtime subsystems have been initialized, but before the Owner Player's auth has been made.
	 */
	void TriggerOnStartedAndFrictionlessAuth(FBeamWaitCompleteEvent, bool bApplyFrictionlessLogin, TMap<FString, FString> LoginInitProperties, FBeamRuntimeHandler OnStartedHandler, FRuntimeError OnStartedFailedHandler);

	/**
	 * @brief This function gets called to start the flow of initializing subsystems manually
	 */
	void ManuallyInitializeSubsystem(TArray<TSubclassOf<UBeamRuntimeSubsystem>>& SubsystemsToInit, bool bInitializeUsers, FBeamOperationHandle Op);
	/**
	* @brief This gets called after the first initialize call to set manually subsystems as started but without initializing the content
	 */
	void TriggerManuallySetSubsystemStarted(FBeamWaitCompleteEvent Evt, TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsToInit, bool bInitializeUsers, FBeamOperationHandle Op);
	/**
	 * @brief This gets called after all the manually initialized subsystems had the opportunity to make initialization requests to Beamable that DO depend on content data.
	 */
	void TriggerManuallySetSubsystemContentReady(FBeamWaitCompleteEvent Evt, TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsToInit, bool bInitializeUsers, FBeamOperationHandle Op);
	/**
	 * @brief This gets called to initialize the users for the manually initialized subsystems.
	 */
	void TriggerManuallySetSubsystemsUserReady(FBeamWaitCompleteEvent Evt, TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsToInit, bool bInitializeUsers, FBeamOperationHandle Op);

	/**
	 * @brief This gets called to trigger the post user sign in for the manually initialized subsystems.
	 */
	void TriggerManuallySubsystemsPostUserSignIn(FBeamWaitCompleteEvent Evt, TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsToInit, FBeamOperationHandle Op);


	/**
	 * @brief Callback added to the UserSlot global callback so that we can respond to users signing in.
	 * We start a chain of requests that:
	 * - Establishes a websocket connection and connectivity state.
	 * - If connected:
	 *   - Calls the User Authenticated callbacks on BeamRuntimeSubsystems.
	 *   - Then the PostUserSign in callback on every BeamRuntimeSubsystems.
	 * - If not connected:
	 *   - Go into offline mode.
	 */
	void TriggerOnUserSlotAuthenticated(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const FBeamOperationHandle& AuthOpHandle, const UObject* Context);

	/**
	 * @brief This is triggered after the user being authenticated and wait until all the system initialize to triggers the call back for the operation and then call the event of the OnUserReady Event
	 */
	void TriggerSubsystemPostUserSignIn(FBeamWaitCompleteEvent, FUserSlot UserSlot, FBeamRealmUser BeamRealmUser,
	                                    FBeamOperationHandle AuthOpHandle);

	/**
	 * @brief Callback added to the UserSlot global callback so that we can respond to users signing out. 
	 */
	UFUNCTION()
	void TriggerOnUserSlotCleared(const EUserSlotClearedReason& Reason, const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context);

	/**
	 * @brief After all subsystems have finished their respective handling of UserSlot sign-out, we give them all a chance to respond to that. 
	 */
	void TriggerPostUserSignedOut(FBeamWaitCompleteEvent, FUserSlot UserSlot, EUserSlotClearedReason Reason, FBeamRealmUser BeamRealmUser);

	/** Cleans up the system.  */
	virtual void Deinitialize() override;

	/**
	 * @brief Stored lambda delegate handle for what this subsystem does when a user slot is authenticated.
	 */
	FDelegateHandle UserSlotAuthenticatedHandler;

	/**
	 * @brief Stored lambda delegate handle for what this subsystem does when a user slot is cleared.
	 */
	FDelegateHandle UserSlotClearedHandler;

	/**
	 * @brief In a bunch of cases, we want to automatically sign a user out and, once done, sign a new user in.
	 * This is done in most login calls, and we need a place to store the lambda handle so that we can clean it up after it runs. 
	 */
	FDelegateHandle UserSlotClearedEnqueuedHandle;

	/**
	 * Automatically initialized systems. This is computed during the process for initializing the SDK and then never updated. 
	 */
	TArray<UBeamRuntimeSubsystem*> AutomaticallyInitializedSubsystems;

	/**
	 * @brief When we boot up the game instance (and it's subsystems), after all Initialize calls have finished, we allow BeamSubsystems to kick-off operations in parallel.
	 * They return operation handles that we wait on. When done, these subsystems are be ready to make unauthenticated requests to the Beamable backend.
	 */
	TArray<FBeamOperationHandle> InitializeWhenUnrealReadyOps = {};
	FBeamWaitHandle OnInitializeWhenUnrealReadyWait;

	/**
	 * @brief After beamable has finished it's initialization but has yet to download its content manifest.	 
	 */
	TArray<FBeamOperationHandle> OnBeamableStartingOps = {};
	FBeamWaitHandle OnBeamableStartingWait;

	/**
	 * @brief After beamable has finished fetching the content manifest, but has yet to finish initializing the runtime subsystems and has not yet attempted its frictionless auth.	 
	 */
	TArray<FBeamOperationHandle> OnBeamableContentReadyOps = {};
	FBeamWaitHandle OnBeamableContentReadyWait;

	/**
	 * @brief This is a list of the operation that ended with errors after the initialization fails.
	 */
	UPROPERTY()
	TArray<FBeamOperationEvent> CachedInitializationErrors;

	/**
	 * @brief Every time a user signs into beamable, we give each subsystem the ability to run an operation for that user.
	 * We also give them the list of currently authenticated UserSlots (so that they can tell if the user that just signed in is the last one for example).
	 */
	TMap<FUserSlot, TArray<FBeamOperationHandle>> OnUserSignedInOps = {};
	TMap<FUserSlot, FBeamWaitHandle> OnUserSignedInWaits;

	/**
	 * @brief After Beamable all UBeamRuntimeSubsystem::OnUserSignedIn operations have finished.
	 * This is a second layer of operations that makes it easier for users to make BeamRuntimeSystems of their own that are allowed
	 * to depend on data from our own SDK systems implementations.
	 */
	TMap<FUserSlot, TArray<FBeamOperationHandle>> OnPostUserSignedInOps = {};
	TMap<FUserSlot, FBeamWaitHandle> OnPostUserSignedInWaits;

	/**
	 * @brief So that actors and components can react to failures in the user authentication flow.
	 * This runs after all of the BeamRuntimeSubsystems have run their OnFailedUserAuth callback. 
	 */
	UPROPERTY(BlueprintAssignable, meta=(DeprecatedProperty, DeprecationMessage = "Use OnUserReadyFailed instead for the same semantics."))
	FBeamRuntimeEvent OnFailedUserAuth;

	/**
	 * @brief Every time a user signs out of beamable we give each subsystem the ability to run an operation for that user.
	 * We also give them the list of currently authenticated User Slots and the reason for the sign out so that they can correctly decide what to do in each instance.
	 */
	TMap<FUserSlot, TArray<FBeamOperationHandle>> OnUserSignedOutOps = {};
	TMap<FUserSlot, FBeamWaitHandle> OnUserSignedOutWaits;

	/**
	 * @brief After Beamable all UBeamRuntimeSubsystem::OnUserSignedOut operations have finished.
	 * This is a second layer of operations that makes it easier for users to make BeamRuntimeSystems of their own that are allowed
	 * need to perform cleanup after our own SDK systems have finished theirs.
	 */
	TMap<FUserSlot, TArray<FBeamOperationHandle>> OnPostUserSignedOutOps = {};
	TMap<FUserSlot, FBeamWaitHandle> OnPostUserSignedOutWaits;

	/**
	 * @brief For each user slot, we automatically open and connect to the beamable notification service
	 * (web-socket protocol through which we receive).
	 */
	TMap<FUserSlot, FBeamWebSocketHandle> DefaultNotificationChannels;

public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamRuntime* GetSelf(const UObject* CallingContext) { return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamRuntime>(); }

	static const inline FName DefaultNotificationChannel = FName(TEXT("Default"));

	/**
	 * @brief Function that replaces UBeamBackend::DefaultExecuteRequestImpl when running in PIE mode.
	 * 
	 */
	UFUNCTION()
	void PIEExecuteRequestImpl(int64 ActiveRequestId);

	/** @brief an enum that represents the state of the sdk if it is currently initialized and ready to be used or not */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, DisplayName="SDK State")
	TEnumAsByte<ESDKState> CurrentSdkState;

	UPROPERTY()
	UBeamUserSlots* UserSlotSystem;

	UPROPERTY()
	UBeamRequestTracker* RequestTrackerSystem;

	UPROPERTY()
	UBeamNotifications* NotificationSystem;

	/**
	 * Manages connectivity and recovery for every user slot.
	 */
	UPROPERTY(BlueprintReadOnly)
	TMap<FUserSlot, UBeamConnectivityManager*> ConnectivityState;

	/**
	 * Gets the UBeamConnectivityManager for the owner user slot.
	 */
	UFUNCTION(BlueprintCallable)
	UBeamConnectivityManager* GetOwnerSlotConnectivity() { return ConnectivityState[GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot()]; }

	UFUNCTION(BlueprintCallable)
	UBeamConnectivityManager* GetSlotConnectivity(FUserSlot Slot) { return ConnectivityState[Slot]; }

	/**
	 * Try gets the external identity for a given namespace 
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetExternalIdentity(FUserSlot Slot, FString FederationId, FString& ExternalId);

	/**
	 * Returns true when the SDK was initialized.  
	 */
	UFUNCTION(BlueprintCallable)
	bool IsInitialized() { return CurrentSdkState == Initialized; }

	/**
	 * For cases where you want to de-register all the callbacks to the various runtime events:
	 *  - OnStarted
	 *  - OnStartedFailed
	 *  - OnUserReady
	 *  - OnUserInitFailed
	 *  - OnUserCleared
	 *
	 *  If your game, reloads to your main menu, you can use this to reset all your bound callbacks to make it easier to write your initialization logic.
	 */
	UFUNCTION(Blueprintable)
	void UnregisterAllCallbacks();

	/**
	 * @brief Call this function to initialize the SDK.
	 * SDKReadyHandler : Is triggered after the sdk initialization has finished without errors.
	 * SDKInitilizationErrorHandler : Is triggered if an error happened while initializing the SDK. 
	 */
	UFUNCTION(BlueprintCallable)
	void InitSDK(FBeamRuntimeHandler OnStartedHandler, FRuntimeError OnStartedFailedHandler);

	/**
	 * @brief Get the operation event id for the 2FA auth subevent
	 */
	UFUNCTION(BlueprintCallable)
	static inline FName GetOperationEventID_MultiFactorAuthTriggered() { return FName("ON_MULTI-FACTOR_AUTH"); }

	/**
	 * @brief Call this function if you want to initialize a subsystem that was set to manually initialize from the project settings.
	 * This function will initialize all the passed subsystems
	 * See @link ManuallyInitializeSubsystemOperation @endlink and @link TriggerManuallySetSubsystemsUserReady @endlink. 
	 */
	UFUNCTION(BlueprintCallable)
	static inline FName GetOperationEventID_SubsystemsInitializedWithoutUserData() { return FName("SUBSYSTEMS_STARTED"); }

	/**
	 * @brief Call this function if you want to initialize a subsystem that was set to manually initialize from the project settings.
	 * This function will initialize all the passed subsystems.
	 */
	UFUNCTION(BlueprintCallable)
	FBeamOperationHandle ManuallyInitializeSubsystemOperation(FUserSlot UserSlot, TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsTypesToInitialize, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc ManuallyInitializeSubsystemOperation
	 */
	FBeamOperationHandle CPP_ManuallyInitializeSubsystemOperation(FUserSlot UserSlot, TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsTypesToInitialize, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief Call this function if you want to initialize a subsystem that was set to manually initialize from the project settings.
	 * This function will initialize all the passed subsystems along with the user data
	 */
	UFUNCTION(BlueprintCallable)
	FBeamOperationHandle ManuallyInitializeSubsystemOperationWithUserData(FUserSlot UserSlot, TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsTypesToInitialize, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc ManuallyInitializeSubsystemOperationWithUserData
	 */
	FBeamOperationHandle CPP_ManuallyInitializeSubsystemOperationWithUserData(FUserSlot UserSlot, TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsTypesToInitialize, FBeamOperationEventHandlerCode OnOperationEvent);

	// UserSlot State
public:
	/**
	 * Whether a particular slot has a user authenticated in it.	  
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool IsLoggedIn(FUserSlot Slot) { return UserSlotSystem->IsUserSlotAuthenticated(Slot, this); }

	/**
	 * Tries to get the @link FBeamRealmUser @endlink for the user logged into the given Slot.
	 * Returns false when no user is signed in and everything except the RealmHandle will be empty.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetSlotUserData(FUserSlot Slot, FBeamRealmUser& Data)
	{
		if (UserSlotSystem->GetUserDataAtSlot(Slot, Data, this))
			return true;

		Data.RealmHandle = GetDefault<UBeamCoreSettings>()->TargetRealm;
		return false;
	}

	/**
	 * Gets the @link FBeamGamerTag @endlink for the user logged into the given Slot.
	 * If no user is signed in, returns an empty @link FBeamGamerTag @endlink.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetSlotGamerTag(FUserSlot Slot, FBeamGamerTag& GamerTag) const
	{
		FBeamRealmUser Data;
		if (UserSlotSystem->GetUserDataAtSlot(Slot, Data, this))
		{
			GamerTag = Data.GamerTag;
			return true;
		}
		Data = {};
		return false;
	}

	/**
	 * Gets the @link FBeamGamerTag @endlink for the user logged into the given Slot.
	 * If no user is signed in, returns an empty @link FBeamGamerTag @endlink.
	 */
	UFUNCTION(BlueprintPure)
	FBeamGamerTag GetSlotGamerTag(FUserSlot Slot) const
	{
		FBeamRealmUser Data;
		if (UserSlotSystem->GetUserDataAtSlot(Slot, Data, this)) return Data.GamerTag;
		return {};
	}

	/**
	 * Gets the @link FBeamRealmUser @endlink for the user logged into the given Slot.
	 * If no user is signed in, everything except the RealmHandle will be empty.
	 */
	UFUNCTION(BlueprintPure)
	FBeamRealmUser GetSlotUserData(FUserSlot Slot) const
	{
		FBeamRealmUser Data;
		if (UserSlotSystem->GetUserDataAtSlot(Slot, Data, this))return Data;

		Data.RealmHandle = GetDefault<UBeamCoreSettings>()->TargetRealm;
		return Data;
	}

private:
	/**
	 * @brief So that actors and components can react to beamable's initialization flow being finished.
	 * This runs only once during your game's execution: after all UBeamRuntimeSubsystem::OnBeamableStarted have run.
	 * If you have Automatic Frictionless Auth disabled, from this point forward, you can make Authentication calls to Beamable.
	 */
	UPROPERTY()
	FBeamRuntimeEvent OnStarted;
	FBeamRuntimeEventCode OnStartedCode;

	/**
	 * @brief This is called when the operations for starting the sdk fails.
	 */
	UPROPERTY()
	FSdkInitFailedEvent OnStartedFailed;
	FSdkInitFailedEventCode OnStartedFailedCode;

public:
	/**
	 * @brief In BP, use this function to bind initialization functions to OnStarted. Which executes after the SDK is initialized. 
	 */
	UFUNCTION(BlueprintCallable)
	void RegisterOnStarted(FBeamRuntimeHandler Handler)
	{
		if (CurrentSdkState == ESDKState::Initialized) const auto _ = Handler.ExecuteIfBound();
		OnStarted.Add(Handler);
	}

	/**
	 * @brief In BP, use this function to bind initialization functions to OnStarted. This will NOT execute the delegate if you're already ready. 
	 */
	UFUNCTION(BlueprintCallable)
	void RegisterOnStarted_NoExecute(FBeamRuntimeHandler Handler)
	{
		OnStarted.Add(Handler);
	}

	/**
	 * @brief In BP, use this function to unbind initialization custom events to OnStarted.  Which executes after the SDK is initialized. 
	 */
	UFUNCTION(BlueprintCallable)
	void UnregisterOnStarted(FBeamRuntimeHandler Handler)
	{
		if (OnStarted.Contains(Handler))
			OnStarted.Remove(Handler);
	}

	/**
	 * @brief In CPP, use this function to bind initialization functions to OnStarted. Which executes after the SDK is initialized. 
	 */
	FDelegateHandle CPP_RegisterOnStarted(FBeamRuntimeHandlerCode Handler)
	{
		if (CurrentSdkState == ESDKState::Initialized) const auto _ = Handler.ExecuteIfBound();
		return OnStartedCode.Add(Handler);
	}

	/**
	 * @brief In CPP, use this function to bind initialization functions to OnStarted. This will NOT execute the delegate if you're already ready. 
	 */
	FDelegateHandle CPP_RegisterOnStarted_NoExecute(FBeamRuntimeHandlerCode Handler)
	{
		return OnStartedCode.Add(Handler);
	}

	/**
	 * @brief In CPP, use this function to unbind initialization custom events to OnStarted.  Which executes after the SDK is initialized. 
	 */
	void CPP_UnregisterOnStarted(FDelegateHandle Handle)
	{
		OnStartedCode.Remove(Handle);
	}

	/**
	 * @brief In BP, use this function to bind error handling logic to OnSDKInitializationFailed. This will execute the delegate if sdk already failed initialization before it binds it. 
	 */
	UFUNCTION(BlueprintCallable)
	void RegisterOnSdkInitFailed(FOperationError Handler)
	{
		if (CurrentSdkState == ESDKState::InitializationFailed) const auto _ = Handler.ExecuteIfBound(CachedInitializationErrors);
		OnStartedFailed.Add(Handler);
	}

	/**
	 * @brief In BP, use this function to bind error handling logic to OnSDKInitializationFailed. This will NOT execute the delegate if initialization already failed. 
	 */
	UFUNCTION(BlueprintCallable)
	void RegisterOnSdkInitFailed_NoExecute(FOperationError Handler)
	{
		OnStartedFailed.Add(Handler);
	}

	/**
	 * @brief In BP, use this function to unbind error handling events to OnSDKInitializationFailed. 
	 */
	UFUNCTION(BlueprintCallable)
	void UnregisterOnSdkInitFailed(FOperationError Handler)
	{
		if (OnStartedFailed.Contains(Handler))
		{
			OnStartedFailed.Remove(Handler);
		}
	}

	/**
	 * @brief In CPP, use this function to bind error handling logic to OnSDKInitializationFailed. This will execute the delegate if sdk already failed initialization before it binds it. 
	 */
	FDelegateHandle CPP_RegisterOnSdkInitFailed(FOperationErrorCode Handler)
	{
		if (CurrentSdkState == ESDKState::InitializationFailed) const auto _ = Handler.ExecuteIfBound(CachedInitializationErrors);
		return OnStartedFailedCode.Add(Handler);
	}

	/**
	 * @brief In CPP, use this function to bind error handling logic to OnSDKInitializationFailed. This will NOT execute the delegate if initialization already failed. 
	 */
	FDelegateHandle CPP_RegisterOnSdkInitFailed_NoExecute(FOperationErrorCode Handler)
	{
		return OnStartedFailedCode.Add(Handler);
	}

	/**
	 * @brief In CPP, use this function to unbind error handling events to OnSDKInitializationFailed. 
	 */
	void CPP_UnregisterOnSdkInitFailed(FDelegateHandle Handle)
	{
		OnStartedFailedCode.Remove(Handle);
	}

private:
	/**
	 * @brief So that actors and components can react to user data being ready for a specific user slot. 
	 *  The event is what game makers should use when registering their actors, systems, etc... if they wish to depend on a specific user slot's data in BeamRuntimeSubsystems.
	 *
	 *  This runs every time a UserSlot is authenticated into. 
	 */
	UPROPERTY(BlueprintAssignable)
	FUserStateChangedEvent OnUserReady;
	FUserStateChangedEventCode OnUserReadyCode;

	/**
	 * @brief This is called when the initialization of the subsystems user slots fails.
	 */
	UPROPERTY()
	FUserInitFailedEvent OnUserInitFailed;
	FUserInitFailedEventCode OnUserInitFailedCode;

	/**
	 * @brief So that actors and components can react to user data being cleared for a specific user slot. 
	 *  The event is what game makers should use when registering their actors, systems, etc... if they wish to react to a specific user slot's data in BeamRuntimeSubsystems being cleared.
	 *
	 *  This runs every time a UserSlot is cleared, after all BeamRuntimeSubsystems have run their SignOut callbacks. 
	 */
	UPROPERTY(BlueprintAssignable)
	FUserStateChangedEvent OnUserCleared;
	FUserStateChangedEventCode OnUserClearedCode;

public:
	/**
	 * @brief In BP, use this function to bind functions that will execute when any user slot is initialized.
	 */
	UFUNCTION(BlueprintCallable)
	void RegisterOnUserReady(FUserStateChangedHandler Handler)
	{
		OnUserReady.Add(Handler);
	}

	/**
	 * @brief In BP, use this function to unbind functions to the user slot initialization. 
	 */
	UFUNCTION(BlueprintCallable)
	void UnregisterOnUserReady(FUserStateChangedHandler Handler)
	{
		if (OnUserReady.Contains(Handler))
		{
			OnUserReady.Remove(Handler);
		}
	}

	/**
	 * @brief In CPP, use this function to bind functions that will execute when any user slot is initialized.
	 */
	FDelegateHandle CPP_RegisterOnUserReady(FUserStateChangedHandlerCode Handler)
	{
		return OnUserReadyCode.Add(Handler);
	}

	/**
	 * @brief In CPP, use this function to unbind functions that will execute when any user slot is initialized.
	 */
	void CPP_UnregisterOnUserReady(FDelegateHandle Handler)
	{
		OnUserReadyCode.Remove(Handler);
	}

	/**
	 * @brief In BP, use this function to bind functions that will execute when any user slot is initialized.
	 */
	UFUNCTION(BlueprintCallable)
	void RegisterOnUserInitFailed(FUserInitFailedHandler Handler)
	{
		OnUserInitFailed.Add(Handler);
	}

	/**
	 * @brief In BP, use this function to unbind functions to the user slot initialization. 
	 */
	UFUNCTION(BlueprintCallable)
	void UnregisterOnUserInitFailed(FUserInitFailedHandler Handler)
	{
		if (OnUserInitFailed.Contains(Handler))
		{
			OnUserInitFailed.Remove(Handler);
		}
	}

	/**
	 * @brief In CPP, use this function to bind functions that will execute when any user slot is initialized.
	 */
	FDelegateHandle CPP_RegisterOnUserInitFailed(FUserInitFailedHandlerCode Handler)
	{
		return OnUserInitFailedCode.Add(Handler);
	}

	/**
	 * @brief In CPP, use this function to unbind functions that will execute when any user slot is initialized.
	 */
	void CPP_UnregisterOnUserInitFailed(FDelegateHandle Handler)
	{
		OnUserInitFailedCode.Remove(Handler);
	}

	/**
	 * @brief In BP, use this function to bind functions that will execute when any user slot is initialized.
	 */
	UFUNCTION(BlueprintCallable)
	void RegisterOnUserCleared(FUserStateChangedHandler Handler)
	{
		OnUserCleared.Add(Handler);
	}

	/**
	 * @brief In BP, use this function to unbind functions to the user slot initialization. 
	 */
	UFUNCTION(BlueprintCallable)
	void UnregisterOnUserCleared(FUserStateChangedHandler Handler)
	{
		if (OnUserCleared.Contains(Handler))
		{
			OnUserCleared.Remove(Handler);
		}
	}

	/**
	 * @brief In CPP, use this function to bind functions that will execute when any user slot is initialized.
	 */
	FDelegateHandle CPP_RegisterOnUserCleared(FUserStateChangedHandlerCode Handler)
	{
		return OnUserClearedCode.Add(Handler);
	}

	/**
	 * @brief In CPP, use this function to unbind functions that will execute when any user slot is initialized.
	 */
	void CPP_UnregisterOnUserCleared(FDelegateHandle Handler)
	{
		OnUserClearedCode.Remove(Handler);
	}


	// OPERATIONS
public:
	/**
	 * @brief An operation that will try to load the last user that logged into the given user slot.
	 * This operation errors if there is no local user OR it failed to fully log in with the cached user.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Auth", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle LoginFromCacheOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent);
	/**
	 * @brief An operation that will try to load the last user that logged into the given user slot.
	 * This operation errors if there is no local user OR it failed to fully log in with the cached user. 
	 */
	FBeamOperationHandle CPP_LoginFromCacheOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief An operation that will authenticate a user with the beamable and persist that authentication locally.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Auth", meta=(DefaultToSelf="CallingContext", AutoCreateRefTerm="InitProperties", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle LoginFrictionlessOperation(FUserSlot UserSlot, TMap<FString, FString> InitProperties, FBeamOperationEventHandler OnOperationEvent);
	/**
	 * @brief An operation that will authenticate a user with the beamable and persist that authentication locally.
	 */
	FBeamOperationHandle CPP_LoginFrictionlessOperation(FUserSlot UserSlot, TMap<FString, FString> InitProperties, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief An operation that will authenticate a user with the beamable using a Federated Identity and persist that authentication locally.
	 * If a user is already in the given slot, this operation will sign out entirely before signing in.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Auth", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle LoginFederatedOperation(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedAuthToken, FBeamOperationEventHandler OnOperationEvent);
	/**
	 * @brief An operation that will authenticate a user with the beamable using a Federated Identity and persist that authentication locally.
	 * If a user is already in the given slot, this operation will sign out entirely before signing in.
	 */
	FBeamOperationHandle CPP_LoginFederatedOperation(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedAuthToken, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief It will get all the external identities for the user slot and set it to the given user slot. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Auth", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchExternalIdentityOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchExternalIdentityOperation
	 */
	FBeamOperationHandle CPP_FetchExternalIdentityOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent);


	/**
	 * Call this to submit a solved @link UBeamMultiFactorLoginData::ChallengeToken @endlink as part of the multi-factor login flows. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Auth", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle CommitLoginFederatedOperation(FUserSlot UserSlot, UBeamMultiFactorLoginData* MultiFactorData, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * Call this to submit a solved @link UBeamMultiFactorLoginData::ChallengeToken @endlink as part of the multi-factor login flows. 
	 */
	FBeamOperationHandle CPP_CommitLoginFederatedOperation(FUserSlot UserSlot, UBeamMultiFactorLoginData* MultiFactorData, FBeamOperationEventHandlerCode OnOperationEvent);


	/**
	 * @brief An operation that will authenticate a user with the beamable using a Federated Identity and persist that authentication locally.
	 * If a user is already in the given slot, this operation will sign out entirely before signing in.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Auth", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle LoginEmailAndPasswordOperation(FUserSlot UserSlot, FString Email, FString Password, FBeamOperationEventHandler OnOperationEvent);
	/**
	 * @brief An operation that will authenticate a user with the beamable using a Federated Identity and persist that authentication locally.
	 * If a user is already in the given slot, this operation will sign out entirely before signing in.
	 */
	FBeamOperationHandle CPP_LoginEmailAndPasswordOperation(FUserSlot UserSlot, FString Email, FString Password, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * If the given IdentityUserId is NOT attached to an account in the current realm, we attach it to the account in the given slot.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Auth", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle AttachFederatedOperation(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedUserId, FString FederatedAuthToken,
	                                              FBeamOperationEventHandler OnOperationEvent);
	/**
	 * If the given IdentityUserId is NOT attached to an account in the current realm, we attach it to the account in the given slot.
	 */
	FBeamOperationHandle CPP_AttachFederatedOperation(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedUserId, FString FederatedAuthToken,
	                                                  FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * Call this to submit a solved @link UBeamMultiFactorLoginData::ChallengeToken @endlink as part of the multi-factor login flows. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Auth", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle CommitAttachFederatedOperation(FUserSlot UserSlot, UBeamMultiFactorLoginData* MultiFactorData, FBeamOperationEventHandler OnOperationEvent);
	/**
	 * Call this to submit a solved @link UBeamMultiFactorLoginData::ChallengeToken @endlink as part of the multi-factor login flows. 
	 */
	FBeamOperationHandle CPP_CommitAttachFederatedOperation(FUserSlot UserSlot, UBeamMultiFactorLoginData* MultiFactorData, FBeamOperationEventHandlerCode OnOperationEvent);

	/**	 
	 * If the given Email is NOT attached to an account in the current realm, we attach it to the account in the given slot.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Auth", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle AttachEmailAndPasswordOperation(FUserSlot UserSlot, FString Email, FString Password, FBeamOperationEventHandler OnOperationEvent);
	/**	 	 
	 * If the given Email is NOT attached to an account in the current realm, we attach it to the account in the given slot.
	 */
	FBeamOperationHandle CPP_AttachEmailAndPasswordOperation(FUserSlot UserSlot, FString Email, FString Password, FBeamOperationEventHandlerCode OnOperationEvent);

	/**	 
	 * If no user is in the given slot and the given Federated Identity is NOT attached to an account in the current realm, we create a new account and attach the given email/password to it as an atomic operation (client-side).
	 * The new user is authenticated into the target slot at the end of this process ONLY IF THE ENTIRE PROCESS IS SUCCESSFUL.
	 *
	 * When bAutoLogin is true, if the identity is already in use by some account, we'll log in to that account instead.
	 * The semantics for that login are like the ones in @link LoginFederated @endlink.
	 * 
	 * When using along with IFederatedPlayerInit in a microservice, this passes in the IdentityUserId and IdentityAuthToken values as InitProperties, in addition to the ones provided as a parameter here.
	 * Their keys are '__beam_3rd_party_user_id__' and '__beam_3rd_party_auth_token__' respectively.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Auth", meta=(DefaultToSelf="CallingContext", AutoCreateRefTerm="InitProperties", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle SignUpFederatedOperation(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedUserId, FString FederatedAuthToken,
	                                              bool bAutoLogin, TMap<FString, FString> InitProperties, FBeamOperationEventHandler OnOperationEvent);

	/**	 
	 * If no user is in the given slot and the given Federated Identity is NOT attached to an account in the current realm, we create a new account and attach the given email/password to it as an atomic operation (client-side).
	 * The new user is authenticated into the target slot at the end of this process ONLY IF THE ENTIRE PROCESS IS SUCCESSFUL.
	 *
	 * When bAutoLogin is true, if the identity is already in use by some account, we'll log in to that account instead.
	 * The semantics for that login are like the ones in @link LoginFederated @endlink.
	 * 
	 * When using along with IFederatedPlayerInit in a microservice, this passes in the IdentityUserId and IdentityAuthToken values as InitProperties, in addition to the ones provided as a parameter here.
	 * Their keys are '__beam_3rd_party_user_id__' and '__beam_3rd_party_auth_token__' respectively.
	 */
	FBeamOperationHandle CPP_SignUpFederatedOperation(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedUserId, FString FederatedAuthToken,
	                                                  bool bAutoLogin, TMap<FString, FString> InitProperties, FBeamOperationEventHandlerCode OnOperationEvent);

	/**	 
	 * If no user is in the given slot and the given Email is NOT attached to an account in the current realm, we create a new account and attach the given email/password to it as an atomic operation (client-side).
	 * The new user is authenticated into the target slot at the end of this process ONLY IF THE ENTIRE PROCESS IS SUCCESSFUL.
	 *
	 * When bAutoLogin is true, if the email account is already in use, we'll try to log in to that account with the provided email and password.
	 * The semantics for that login are like the ones in @link LoginEmailAndPasswordOperation @endlink.
	 *
	 * When using along with IFederatedPlayerInit in a microservice, this passes in the email and password values as InitProperties, in addition to the ones provided  as a parameter here.
	 * Their keys are '__beam_email__' and '__beam_password__' respectively.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Auth", meta=(DefaultToSelf="CallingContext", AutoCreateRefTerm="InitProperties", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle SignUpEmailAndPasswordOperation(FUserSlot UserSlot, FString Email, FString Password, bool bAutoLogin, TMap<FString, FString> InitProperties, FBeamOperationEventHandler OnOperationEvent);
	/**	 
	 * If no user is in the given slot and the given Email is NOT attached to an account in the current realm, we create a new account and attach the given email/password to it as an atomic operation (client-side).
	 * The new user is authenticated into the target slot at the end of this process ONLY IF THE ENTIRE PROCESS IS SUCCESSFUL.
	 *
	 * When bAutoLogin is true, if the email account is already in use, we'll try to log in to that account with the provided email and password.
	 * The semantics for that login are like the ones in @link LoginEmailAndPasswordOperation @endlink.
	 *
	 * When using along with IFederatedPlayerInit in a microservice, this passes in the email and password values as InitProperties, in addition to the ones provided  as a parameter here.
	 * Their keys are '__beam_email__' and '__beam_password__' respectively.
	 */
	FBeamOperationHandle CPP_SignUpEmailAndPasswordOperation(FUserSlot UserSlot, FString Email, FString Password, bool bAutoLogin, TMap<FString, FString> InitProperties, FBeamOperationEventHandlerCode OnOperationEvent);

	/**	 
	 * If a user is logged into the given slot, we sign out (waiting for all systems to sign out) and then we trigger the operation's success.   
	 * If no user is in the given slot, we fail this operation.
	 *
	 * When invoking this manually in your game, always pass in USCR_Manual as your reason.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Auth", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle LogoutOperation(FUserSlot UserSlot, EUserSlotClearedReason Reason, bool bRemoveLocalData, FBeamOperationEventHandler OnOperationEvent);

	/**	 
	 * If a user is logged into the given slot, we sign out (waiting for all systems to sign out) and then we trigger the operation's success. 
	 * If no user is in the given slot, we fail this operation.
	 *
	 * When invoking this manually in your game, always pass in USCR_Manual as your reason.
	 */
	FBeamOperationHandle CPP_LogoutOperation(FUserSlot UserSlot, EUserSlotClearedReason Reason, bool bRemoveLocalData, FBeamOperationEventHandlerCode OnOperationEvent);

private:
	// BP/CPP Independent Operation Implementations
	void LoginFromCache(FUserSlot UserSlot, FBeamOperationHandle Op);
	void LoginFrictionless(FUserSlot UserSlot, TMap<FString, FString> InitProperties, FBeamOperationHandle Op);
	void LoginFederated(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedAuthToken, FBeamOperationHandle Op);
	void CommitLoginFederated(FUserSlot UserSlot, UBeamMultiFactorLoginData* ChallengeSolution, FBeamOperationHandle Op);
	void LoginEmailAndPassword(FUserSlot UserSlot, FString Email, FString Password, FBeamOperationHandle Op);
	void CommitAttachFederated(FUserSlot UserSlot, UBeamMultiFactorLoginData* ChallengeSolution, FBeamOperationHandle Op);
	void FetchExternalIdentities(FUserSlot UserSlot, FBeamOperationHandle Op);

	void AttachLocalIdentity(FUserSlot UserSlot, FString FederatedUserId, FString MicroserviceId, FString FederationId);
	void AttachFederated(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedUserId, FString FederatedAuthToken, FBeamOperationHandle Op);
	void AttachEmailAndPassword(FUserSlot UserSlot, FString Email, FString Password, FBeamOperationHandle Op);

	void SignUpFederated(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedUserId, FString FederatedAuthToken,
	                     bool bAutoLoginOnUnavailable, TMap<FString, FString> InitProperties, FBeamOperationHandle Op);
	void SignUpEmailAndPassword(FUserSlot UserSlot, FString Email, FString Password,
	                            bool bAutoLoginOnUnavailable, TMap<FString, FString> InitProperties, FBeamOperationHandle Op);

	void Logout(FUserSlot UserSlot, EUserSlotClearedReason Reason, bool bRemoveLocalData, FBeamOperationHandle Op);

	// Reusable Operation Callbacks
	void OnAuthenticated(FAuthenticateFullResponse Resp, FUserSlot UserSlot, FBeamOperationHandle Op, FDelayedOperation BeforeUserNotifyOperation, FString MicroserviceId, FString FederationId,
	                     FString FederatedAuthToken);
	void OnGetBeginTwoFactorResponse(FAuthenticateFullResponse Resp, FUserSlot UserSlot, FBeamOperationHandle Op);
	void AuthenticateWithToken(FUserSlot UserSlot, const UTokenResponse* Token, FBeamOperationHandle Op, FDelayedOperation BeforeUserNotifyOperation);
	void RunPostAuthenticationSetup(FUserSlot UserSlot, FBeamOperationHandle Op);
	void RunPostAuthenticationSetup_OnGetMe(FBasicAccountsGetMeFullResponse Resp, FUserSlot UserSlot, FBeamOperationHandle Op);
	void RunPostAuthenticationSetup_PrepareNotificationService(FGetClientDefaultsFullResponse Resp, FUserSlot UserSlot, FBeamRealmUser BeamRealmUser, FBeamOperationHandle Op);

	// Reusable Helper Functions
	void LoadCachedUserAtSlot(FUserSlot UserSlot, FBeamOperationHandle AuthOp, FSimpleDelegate RunIfNoUser);
	FBeamRequestContext LoginGuest(FUserSlot UserSlot, FBeamOperationHandle Op, TMap<FString, FString> InitProperties, FDelayedOperation OnBeforePostAuthentication = {});
	FBeamRequestContext CheckFederatedIdentityAvailable(FString MicroserviceId, FString FederationId, FString FederatedUserId, FBeamOperationHandle Op,
	                                                    FOnGetAvailableExternalIdentityFullResponse Handler) const;
	FBeamRequestContext CheckEmailAvailable(FString Email, FBeamOperationHandle Op, FOnGetAvailableFullResponse Handler) const;
	FBeamRequestContext AttachIdentityToUser(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedAuthToken, FBeamOperationHandle Op,
	                                         FOnPostExternalIdentityFullResponse Handler) const;
	FBeamRequestContext AttachIdentityToUserTwoFactor(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedAuthToken, UChallengeSolution* ChallengeSolution, FBeamOperationHandle Op,
	                                                  FOnPostExternalIdentityFullResponse Handler) const;
	FBeamRequestContext AttachEmailAndPasswordToUser(FUserSlot UserSlot, FString Email, FString Password, FBeamOperationHandle Op, FOnBasicAccountsPostRegisterFullResponse Handler) const;
	FBeamRequestContext RemoveIdentityFromUser(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedAuthToken, FBeamOperationHandle Op,
	                                           FOnDeleteExternalIdentityFullResponse Handler) const;

	// Runtime Notification Configuration and Automated Session Tracking 
	static inline FString BEAM_SESSION_HEADER_PLATFORM = FString(TEXT("X-BEAM-SESSION-PLATFORM"));
	static inline FString BEAM_SESSION_HEADER_DEVICE = FString(TEXT("X-BEAM-SESSION-DEVICE"));
	static inline FString BEAM_SESSION_HEADER_SOURCE = FString(TEXT("X-BEAM-SESSION-SOURCE"));
	static inline FString BEAM_SESSION_HEADER_LOCALE = FString(TEXT("X-BEAM-SESSION-LOCALE"));
	static inline FString BEAM_SESSION_HEADER_LANGUAGE = FString(TEXT("X-BEAM-SESSION-LANGUAGE"));

	/**
	 * Tries to get the default notification channel for the given user slot. 
	 */
	bool GetDefaultNotificationChannel(const FUserSlot& UserSlot, FBeamWebSocketHandle& OutHandle) const;

	/**
	 * Adds the default information session information tracked by the SDK into the given header dictionary. 
	 */
	virtual void FillDefaultSessionHeaders(TMap<FString, FString>& Headers);

	/**
	 * Ensures a UBeamConnectivityManager exists for the given slot.
	 */
	void EnsureConnectivityManagerForSlot(FUserSlot UserSlot);

	/**
	 * Called within every Login/Sign-Up flows to inject a few reserved values into the InitProperties.
	 */
	void FillDefaultSignUpInitProperties(TMap<FString, FString>& InitProperties);

public:
	/**
	 * Sends analytics events to Beamable as the owner user. 
	 */
	void SendAnalyticsEvent(const FString& EventOpCode, const FString& EventCategory, const FString& EventName, const TArray<TSharedRef<FJsonObject>>& EventParamsObj) const;

	/**
	 * Sends analytics events to Beamable. 
	 */
	void SendAnalyticsEvent(const FUserSlot& Slot, const FString& EventOpCode, const FString& EventCategory, const FString& EventName, const TArray<TSharedRef<FJsonObject>>& EventParamsObj) const;


	/**
	 * Utility that can be used to subscribe to custom Notifications in an easier way than with UBeamNotifications::TrySubscribeForMessage.
	 * @tparam THandler Type of the Notification Handler. Its signature should be "void (TMessage)".
	 * @tparam TMessage Type of the message. A subtype of either IBeamJsonSerializableUObject (UMyType*) or FBeamJsonSerializableUStruct (FMyType). 
	 * @param UserSlot The user that will be listening for this notification.
	 * @param Key The Notification "context" key.
	 * @param Handler An instance of THandler.
	 * @return The delegate handle that you can use with UBeamRuntime::UnsubscribeToCustomNotification.
	 */
	template <typename THandler, typename TMessage>
	FDelegateHandle SubscribeToCustomNotification(const FUserSlot& UserSlot, FString Key, THandler Handler)
	{
		FDelegateHandle Handle;
		FBeamWebSocketHandle DefaultHandle;
		if (GetDefaultNotificationChannel(UserSlot, DefaultHandle))
		{
			if (NotificationSystem->TrySubscribeForMessage<THandler, TMessage>(UserSlot, DefaultHandle.Id, Key, Handler, Handle, this))
			{
				return Handle;
			}
		}

		return {};
	}

	/**
	 * Unsubscribes a specific handler for a specific notification.
	 * @param UserSlot The user that is listening for this notification.
	 * @param Key The Notification "context" key.
	 * @param Handle The handle returned by SubscribeToCustomNotification.
	 * @return Whether the subscribed handle was found and removed.
	 */
	bool UnsubscribeToCustomNotification(const FUserSlot& UserSlot, FString Key, FDelegateHandle Handle)
	{
		FBeamWebSocketHandle DefaultHandle;
		if (GetDefaultNotificationChannel(UserSlot, DefaultHandle))
			return NotificationSystem->TryUnsubscribeFromMessage(UserSlot, DefaultNotificationChannel, Key, Handle, this);
		return false;
	}
};
