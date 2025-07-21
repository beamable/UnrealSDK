// Fill out your copyright notice in the Description page of Project Settings.


#include "Runtime/BeamRuntime.h"

#include "HttpModule.h"

#include "BeamLogging.h"
#include "AutoGen/SubSystems/BeamRealmsApi.h"
#include "AutoGen/SubSystems/Realms/GetClientDefaultsRequest.h"
#include "BeamNotifications/BeamNotifications.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "Subsystems/Content/BeamContentSubsystem.h"


#if WITH_EDITOR
#include "Kismet/KismetSystemLibrary.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#endif

#define LOCTEXT_NAMESPACE "BeamRuntime"


UChallengeSolution* UBeamMultiFactorLoginData::GetChallengeSolutionGenerated()
{
	UChallengeSolution* ChallengeSolution = NewObject<UChallengeSolution>(GetTransientPackage());

	ChallengeSolution->Solution = Solution;
	ChallengeSolution->ChallengeToken = ChallengeToken;

	return ChallengeSolution;
}

void UBeamMultiFactorLoginData::SetChallengeSolution(UChallengeSolution* ChallengeSolution)
{
	Solution = ChallengeSolution->Solution;
	ChallengeToken = ChallengeSolution->ChallengeToken;
}

void UBeamConnectivityManager::ConnectionHandler(const FNotificationEvent& Evt, FBeamRealmUser BeamRealmUser, FBeamOperationHandle Op)
{
	// If the operation is active so that is happening during a login.
	auto IsDuringLogin = RequestTracker->IsOperationActive(Op);

	if (Evt.EventType == BEAM_Connected)
	{
		// This only runs during Authentication
		if (IsDuringLogin)
		{
			// Set the current state as online.
			CurrentState = CONN_Online;

			UE_LOG(LogBeamNotifications, Display, TEXT("Connected to beamable notification service! SLOT=%s, EVT_TYPE=%s"), *UserSlot.Name,
			       *StaticEnum<ENotificationMessageType>()->GetNameByValue(Evt.EventType).ToString())

			Runtime->DefaultNotificationChannels.Add(UserSlot, Evt.ConnectedData.ConnectedHandle);

			UserSlots->SaveSlot(UserSlot, this);
			UserSlots->TriggerUserAuthenticatedIntoSlot(UserSlot, Op, this);
		}
		// This only runs during reconnection...
		else
		{
			UE_LOG(LogBeamNotifications, Warning, TEXT("Connected on reconnect! SLOT=%s, EVT_TYPE=%s"), *UserSlot.Name,
			       *StaticEnum<ENotificationMessageType>()->GetNameByValue(Evt.EventType).ToString())

			if (CurrentState == CONN_Offline)
			{
				CurrentState = CONN_Fixup;

				OnReconnectedCode.ExecuteIfBound(this);
				OnReconnected.Broadcast(this);

				if (GetDefault<UBeamRuntimeSettings>()->AutomaticallyNotifyFixupComplete)
				{
					NotifyFixupComplete();
				}
				else
				{
					const auto Handler = FTickerDelegate::CreateLambda([this](float)
					{
						if (CurrentState == CONN_Fixup)
						{
							FixupTickCode.ExecuteIfBound(this);
							FixupTick.Broadcast(this);
						}
						return CurrentState == CONN_Fixup;
					});
					FixupUpdateHandle = FTSTicker::GetCoreTicker().AddTicker(Handler);
				}
			}
		}
	}
	else if (Evt.EventType == BEAM_ConnectionFailed)
	{
		// This only runs during Authentication
		if (IsDuringLogin)
		{
			UE_LOG(LogBeamNotifications, Error, TEXT("Failed to connect to beamable's notification service! SLOT=%s, EVT_TYPE=%s"), *UserSlot.Name,
			       *StaticEnum<ENotificationMessageType>()->GetNameByValue(Evt.EventType).ToString())
			UserSlots->ClearUserAtSlot(UserSlot, USCR_FailedAuthentication, true, this);
			RequestTracker->TriggerOperationError(Op, Evt.ConnectionFailedData.Error);
		}
		// This only runs during reconnection...
		else
		{
			UE_LOG(LogBeamNotifications, Warning, TEXT("Connection failed on reconnect! SLOT=%s, EVT_TYPE=%s, ERROR=%s"), *UserSlot.Name,
			       *StaticEnum<ENotificationMessageType>()->GetNameByValue(Evt.EventType).ToString(),
			       *Evt.ConnectionFailedData.Error)

			// If we're already offline and just failed to reconnect, we just bump this counter.
			if (this->CurrentState == CONN_Offline)
			{
				this->CurrentReconnectionCount += 1;
			}

			// If we fail to reconnect more than once, we should go into offline mode.
			if (this->CurrentState != CONN_Offline && Evt.ConnectionFailedData.RetryCount > GetDefault<UBeamRuntimeSettings>()->ConnectivityRetryCountBeforeOffline)
			{
				this->CurrentState = CONN_Offline;
				this->ConnectionLostCountInSession += 1;
				this->CurrentReconnectionCount = 0;
				this->CurrentConnectionLostTime = FDateTime::UtcNow();

				OnConnectionLostCode.ExecuteIfBound(this);
				OnConnectionLost.Broadcast(this);

				const auto Handler = FTickerDelegate::CreateLambda([this](float)
				{
					if (CurrentState == CONN_Offline)
					{
						const auto _ = ReconnectionTickCode.ExecuteIfBound(this);
						ReconnectionTick.Broadcast(this);
					}
					return CurrentState == CONN_Offline;
				});
				ReconnectingUpdateHandle = FTSTicker::GetCoreTicker().AddTicker(Handler);
			}
		}
	}
	else if (Evt.EventType == BEAM_Closed)
	{
		// This only runs during Authentication
		if (IsDuringLogin && Evt.ClosedData.StatusCode != Notifications->UserSignOutCloseCode)
		{
			UE_LOG(LogBeamNotifications, Error, TEXT("Connection closed during login flow's attempt to connect to beamable's notification service! SLOT=%s, EVT_TYPE=%s"), *UserSlot.Name,
			       *StaticEnum<ENotificationMessageType>()->GetNameByValue(Evt.EventType).ToString())
			UserSlots->ClearUserAtSlot(UserSlot, USCR_FailedAuthentication, true, this);
			RequestTracker->TriggerOperationError(Op, Evt.ConnectionFailedData.Error);
		}
		else
		{
			UE_LOG(LogBeamNotifications, Warning, TEXT("Connection closed after login operation! SLOT=%s, EVT_TYPE=%s, CLEAN=%s, REASON=%s"), *UserSlot.Name,
			       *StaticEnum<ENotificationMessageType>()->GetNameByValue(Evt.EventType).ToString(),
			       Evt.ClosedData.bWasClean ? TEXT("true") : TEXT("false"),
			       *Evt.ClosedData.Reason)

			// Always try to reconnect on close...
			Notifications->Reconnect(Runtime->DefaultNotificationChannels[UserSlot]);

			// Store the latest Closed data in an "ConnectionLossReasonData"
		}
	}
}

void UBeamRuntime::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CurrentSdkState = NotInitialized;
	AutomaticallyInitializedSubsystems = {};

	// We do some initialization for dedicated servers... 
	if (GetGameInstance()->IsDedicatedServerInstance())
	{
		// Let's just load up the target realm's PID from the follow hierarchy:
		//   - If we got an CLI Arg called --beamable-realm-override <Target Realm's PID>, use this argument.
		//   - If there's no CLI Arg, check for an environment variable called BEAMABLE_REALM_OVERRIDE and use that if it exists.
		//   - If there's no EnvVar, we'll use whatever was configured in "Config/DefaultEngine.ini" (which is edited by using the "Apply To Build" button).

		// We do this so game-makers can choose their preferred ways of setting up dedicated server builds and deployments.
		FString OverridenCustomer;
		if (!FParse::Value(FCommandLine::Get(), TEXT("beamable-customer-override="), OverridenCustomer))
		{
			OverridenCustomer = FPlatformMisc::GetEnvironmentVariable(TEXT("BEAMABLE_CUSTOMER_OVERRIDE"));
			if (!OverridenCustomer.IsEmpty())
			{
				GetMutableDefault<UBeamCoreSettings>()->TargetRealm.Cid = FBeamCid{OverridenCustomer};
			}
		}
		else
		{
			if (!OverridenCustomer.IsEmpty())
			{
				GetMutableDefault<UBeamCoreSettings>()->TargetRealm.Cid = FBeamCid{OverridenCustomer};
			}
		}

		// We do this so game-makers can choose their preferred ways of setting up dedicated server builds and deployments.
		FString OverridenRealm;
		if (!FParse::Value(FCommandLine::Get(), TEXT("beamable-realm-override="), OverridenRealm))
		{
			OverridenRealm = FPlatformMisc::GetEnvironmentVariable(TEXT("BEAMABLE_REALM_OVERRIDE"));
			if (!OverridenRealm.IsEmpty())
			{
				GetMutableDefault<UBeamCoreSettings>()->TargetRealm.Pid = FBeamPid{OverridenRealm};
			}
		}
		else
		{
			if (!OverridenRealm.IsEmpty())
			{
				GetMutableDefault<UBeamCoreSettings>()->TargetRealm.Pid = FBeamPid{OverridenRealm};
			}
		}

		// We do this so game-makers can override any builds we provide to point to our BeamProdEnv regardless
		FString OverridenEnv;
		if (!FParse::Value(FCommandLine::Get(), TEXT("beamable-environment-override="), OverridenRealm))
		{
			OverridenEnv = FPlatformMisc::GetEnvironmentVariable(TEXT("BEAMABLE_ENVIRONMENT_OVERRIDE"));
			if (!OverridenEnv.IsEmpty())
			{
				if (OverridenEnv.Equals(TEXT("BeamProdEnv")))
					GetMutableDefault<UBeamCoreSettings>()->BeamableEnvironment = GetMutableDefault<UBeamCoreSettings>()->BeamablePossibleEnvironments[0];
				else if (OverridenEnv.Equals(TEXT("BeamStagingEnv")))
					GetMutableDefault<UBeamCoreSettings>()->BeamableEnvironment = GetMutableDefault<UBeamCoreSettings>()->BeamablePossibleEnvironments[1];
				else
					GetMutableDefault<UBeamCoreSettings>()->BeamableEnvironment = GetMutableDefault<UBeamCoreSettings>()->BeamablePossibleEnvironments[2];

				UE_LOG(LogBeamRuntime, Display, TEXT("Initializing UBeamRuntime Subsystem - Overriden Environment: %s!"), *GetDefault<UBeamCoreSettings>()->BeamableEnvironment.ToString());
			}
		}
		else
		{
			if (!OverridenEnv.IsEmpty())
			{
				if (OverridenEnv.Equals(TEXT("BeamProdEnv")))
					GetMutableDefault<UBeamCoreSettings>()->BeamableEnvironment = GetMutableDefault<UBeamCoreSettings>()->BeamablePossibleEnvironments[0];
				else if (OverridenEnv.Equals(TEXT("BeamStagingEnv")))
					GetMutableDefault<UBeamCoreSettings>()->BeamableEnvironment = GetMutableDefault<UBeamCoreSettings>()->BeamablePossibleEnvironments[1];
				else
					GetMutableDefault<UBeamCoreSettings>()->BeamableEnvironment = GetMutableDefault<UBeamCoreSettings>()->BeamablePossibleEnvironments[2];

				UE_LOG(LogBeamRuntime, Display, TEXT("Initializing UBeamRuntime Subsystem - Overriden Environment: %s!"), *GetDefault<UBeamCoreSettings>()->BeamableEnvironment.ToString());
			}
		}
	}

	// Set us up to handle sign-in/out flows in editor as well as tracking multiple developer user slots.
	UserSlotSystem = GEngine->GetEngineSubsystem<UBeamUserSlots>();
	RequestTrackerSystem = GEngine->GetEngineSubsystem<UBeamRequestTracker>();
	NotificationSystem = GEngine->GetEngineSubsystem<UBeamNotifications>();

	UserSlotAuthenticatedHandler = UserSlotSystem->GlobalUserSlotAuthenticatedCodeHandler.AddUObject(this, &UBeamRuntime::TriggerOnUserSlotAuthenticated);
	UserSlotClearedHandler = UserSlotSystem->GlobalUserSlotClearedCodeHandler.AddUObject(this, &UBeamRuntime::TriggerOnUserSlotCleared);

	UE_LOG(LogBeamRuntime, Verbose, TEXT("Initializing UBeamRuntime Subsystem!"));

	UBeamBackend* EngineSubsystem = GEngine->GetEngineSubsystem<UBeamBackend>();
	EngineSubsystem->UpdatePieState();
	if (EngineSubsystem->IsInPIE())
	{
		// When running as a dedicated server instance, swap out the execute request delegate
		EngineSubsystem->ExecuteRequestDelegate.BindStatic(&UBeamRuntime::PIEExecuteRequestImpl);
		UE_LOG(LogBeamRuntime, Verbose, TEXT("Initializing UBeamRuntime Subsystem - FROM PIE INSTANCE %d!"), GetGameInstance()->GetWorldContext()->PIEInstance);
	}
	else
	{
		// When running as a dedicated server instance, swap out the execute request delegate
		const FName ExecuteRequestImpl = GetGameInstance()->IsDedicatedServerInstance()
			                                 ? GET_FUNCTION_NAME_CHECKED(UBeamBackend, DedicatedServerExecuteRequestImpl)
			                                 : GET_FUNCTION_NAME_CHECKED(UBeamBackend, DefaultExecuteRequestImpl);
		EngineSubsystem->ExecuteRequestDelegate.BindUFunction(EngineSubsystem, ExecuteRequestImpl);

		UE_LOG(LogBeamRuntime, Verbose, TEXT("Initializing UBeamRuntime Subsystem - FROM BUILD!"));
	}

	// Initialize user ConnectivityState for each slot
	for (FString RuntimeUserSlot : GetDefault<UBeamCoreSettings>()->RuntimeUserSlots)
	{
		EnsureConnectivityManagerForSlot({RuntimeUserSlot});
	}
}

bool UBeamRuntime::TryGetExternalIdentity(FUserSlot Slot, FString FederationId, FString& ExternalId)
{
	FBeamRealmUser RealmUser;
	if (!UserSlotSystem->GetUserDataAtSlot(Slot, RealmUser, this))
	{
		return false;
	}

	for (auto ExternalIdentity : RealmUser.ExternalIdentities)
	{
		if (ExternalIdentity.ProviderNamespace == FederationId)
		{
			ExternalId = ExternalIdentity.UserId;
			return true;
		}
	}

	return false;
}

void UBeamRuntime::UnregisterAllCallbacks()
{
	// Clean up initialization successful handlers
	OnStarted.Clear();
	OnStartedCode.Clear();

	// Clean up initialization error handlers
	OnStartedFailed.Clear();
	OnStartedFailedCode.Clear();

	// Clean up user ready handlers	
	OnUserReady.Clear();
	OnUserReadyCode.Clear();

	// Clean up user initialization failure handles
	OnUserInitFailed.Clear();
	OnUserInitFailedCode.Clear();

	// Clean up user initialization failed handlers
	OnUserCleared.Clear();
	OnUserClearedCode.Clear();
}

void UBeamRuntime::InitSDK(FBeamRuntimeHandler OnStartedHandler, FRuntimeError SDKInitializationErrorHandler)
{
	if (CurrentSdkState == ESDKState::NotInitialized || CurrentSdkState == ESDKState::InitializationFailed)
	{
		ExecuteOnGameThread(TEXT("Initialize"), [this,OnStartedHandler,SDKInitializationErrorHandler]()
		{
			this->TriggerInitializeWhenUnrealReady(false, {}, OnStartedHandler, SDKInitializationErrorHandler);
		});
		CurrentSdkState = ESDKState::Initializing;
	}
	else
	{
		FString ErrMsg = TEXT("Trying to call InitSDK while the SDK is already initialized");
		SDKInitializationErrorHandler.ExecuteIfBound(ErrMsg);
		UE_LOG(LogBeamRuntime, Warning, TEXT("%s"), *ErrMsg);
	}
}

TArray<TSubclassOf<UBeamRuntimeSubsystem>> UBeamRuntime::GetRequiredSubsystems()
{
	TArray<TSubclassOf<UBeamRuntimeSubsystem>> RequiredSubsystems;
	RequiredSubsystems.Add(UBeamContentSubsystem::StaticClass());

	return RequiredSubsystems;
}

void UBeamRuntime::Deinitialize()
{
	Super::Deinitialize();
	UserSlotSystem->GlobalUserSlotAuthenticatedCodeHandler.Remove(UserSlotAuthenticatedHandler);
	UserSlotSystem->GlobalUserSlotClearedCodeHandler.Remove(UserSlotClearedHandler);

	for (const auto& SlotName : GetDefault<UBeamCoreSettings>()->RuntimeUserSlots)
	{
		UserSlotSystem->ClearUserAtSlot(SlotName, USCR_ExitPIE, false, this);
	}

	// When running as a dedicated server instance, swap out the execute request delegate
	const FName ExecuteRequestImpl = GET_FUNCTION_NAME_CHECKED(UBeamBackend, DefaultExecuteRequestImpl);

	UBeamBackend* EngineSubsystem = GEngine->GetEngineSubsystem<UBeamBackend>();
	EngineSubsystem->ExecuteRequestDelegate.BindUFunction(EngineSubsystem, ExecuteRequestImpl);

	NotificationSystem->ClearPIESockets(this);

	CurrentSdkState = ESDKState::NotInitialized;
}

void UBeamRuntime::PIEExecuteRequestImpl(int64 ActiveRequestId, const UObject* CallingContext)
{
	UBeamBackend* BeamBackend = GEngine->GetEngineSubsystem<UBeamBackend>();	
	const TUnrealRequestPtr Req = BeamBackend->InFlightRequests.FindRef(ActiveRequestId);
	BeamBackend->InFlightPIERequests.Add(Req);

	CallingContext->GetWorld()->GetGameInstance()->IsDedicatedServerInstance()
		? BeamBackend->DedicatedServerExecuteRequestImpl(ActiveRequestId, CallingContext)
		: BeamBackend->DefaultExecuteRequestImpl(ActiveRequestId, CallingContext);
}

// On Start Flow

void UBeamRuntime::TriggerInitializeWhenUnrealReady(bool bApplyFrictionlessLogin, TMap<FString, FString> LoginInitProperties, FBeamRuntimeHandler SDKInitializedHandler, FRuntimeError SDKInitializationErrorHandler)
{
	const FBeamRealmHandle TargetRealm = GetDefault<UBeamCoreSettings>()->TargetRealm;
	const FString TargetAPIUrl = GEngine->GetEngineSubsystem<UBeamEnvironment>()->GetAPIUrl();

	// Start-up flow
	if (TargetRealm.Cid.AsLong == -1 || TargetRealm.Pid.AsString.IsEmpty())
	{
#if WITH_EDITOR
		UE_LOG(LogBeamRuntime, Warning, TEXT("Starting PIE with no Target Realm configured for Beamable will make Beamable not work correctly."
			       "Please sign-in and select a realm if you want to use Beamable features."));

		//Creates a new notification info, we pass in our text as the parameter.
		FNotificationInfo Info(LOCTEXT("Notification_NoTargetRealmConfigured", "Starting PIE with no Target Realm configured for Beamable will make Beamable not work correctly."
		                               "Please sign-in and select a realm if you want to use Beamable features."));
		//Set a default expire duration
		Info.ExpireDuration = 5.0f;
		Info.Image = FCoreStyle::Get().GetBrush(TEXT("MessageLog.Warning"));
		FSlateNotificationManager::Get().AddNotification(Info);
#else
		checkf(false, TEXT("Builds with Beamable cannot exist without a configured target realm!"))
#endif
		CurrentSdkState = ESDKState::InitializationFailed;

		OnStartedFailed.Broadcast({});
		OnStartedFailedCode.Broadcast({});
		SDKInitializationErrorHandler.ExecuteIfBound(TEXT("Trying to initialize the SDK without having a Target Realm configured"));
	}
	else
	{
		UE_LOG(LogBeamRuntime, Warning, TEXT("Starting configured Target Realm: CID=%s, PID=%s, URL=%s!"), *TargetRealm.Cid.AsString, *TargetRealm.Pid.AsString, *TargetAPIUrl);

		UBeamRequestTracker* RequestTracker = RequestTrackerSystem;
		if (const UWorld* World = GetWorld())
		{
			if (const UGameInstance* GameInstance = World->GetGameInstance())
			{
				const TArray<UBeamRuntimeSubsystem*> Subsystems = GameInstance->GetSubsystemArrayCopy<UBeamRuntimeSubsystem>();

				TArray<TSubclassOf<UBeamRuntimeSubsystem>> ManuallyInitializedSubsystems = GetDefault<UBeamRuntimeSettings>()->ManualyInitializedRuntimeSubsystems;

				bool DependencyWarning = false;
				FString WarningMsg;
				//Search for subsystems that depend on subsystems that will be manually initialized and add them to the list of manually initialized subsystems
				for (auto& Subsystem : Subsystems)
				{
					if (!ManuallyInitializedSubsystems.Contains(Subsystem->GetClass()))
					{
						TArray<TSubclassOf<UBeamRuntimeSubsystem>> DependingSubsystems = Subsystem->GetDependingOnSubsystems();

						for (auto& DependingSubsystem : DependingSubsystems)
						{
							if (ManuallyInitializedSubsystems.Contains(DependingSubsystem) && !GetRequiredSubsystems().Contains(DependingSubsystem))
							{
								ManuallyInitializedSubsystems.AddUnique(Subsystem->GetClass());

								DependencyWarning = true;

								WarningMsg += "Subsystem " + Subsystem->GetName() + " will not be initialized because it has a dependency on " + DependingSubsystem->GetName() + "\n";
							}
						}
					}
				}

				if (DependencyWarning)
				{
					UE_LOG(LogBeamRuntime, Warning, TEXT("%s"), *WarningMsg);
				}
				InitializeWhenUnrealReadyOps.Reset(Subsystems.Num() - ManuallyInitializedSubsystems.Num());
				for (auto& Subsystem : Subsystems)
				{
					if (!ManuallyInitializedSubsystems.Contains(Subsystem->GetClass())
						|| GetRequiredSubsystems().Contains(Subsystem->GetClass()))
					{
						FBeamOperationHandle Handle;
						Subsystem->InitializeWhenUnrealReady(Handle);
						InitializeWhenUnrealReadyOps.Add(Handle);

						AutomaticallyInitializedSubsystems.Add(Subsystem);
					}
				}

				const auto OnCompleteCode = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::TriggerOnBeamableStarting, bApplyFrictionlessLogin, LoginInitProperties, SDKInitializedHandler,
				                                                               SDKInitializationErrorHandler);
				OnInitializeWhenUnrealReadyWait = RequestTracker->CPP_WaitAll({}, InitializeWhenUnrealReadyOps, {}, OnCompleteCode);
			}
		}
	}
}

void UBeamRuntime::TriggerOnBeamableStarting(FBeamWaitCompleteEvent Evt, bool bApplyFrictionlessLogin, TMap<FString, FString> LoginInitProperties, FBeamRuntimeHandler OnStartedHandler,
                                             FRuntimeError OnStartedFailedHandler)
{
	// Handle errors in operations we were waiting on...
	TArray<FString> Errors;
	if (RequestTrackerSystem->IsWaitFailed(Evt, Errors))
	{
		CurrentSdkState = ESDKState::InitializationFailed;

		FString Err;
		for (const auto& Error : Errors) Err += Error + TEXT("\n");
		UE_LOG(LogBeamRuntime, Error, TEXT("%s"), *Err);

		CachedInitializationErrors.Empty();
		for (auto& Op : Evt.Operations)
		{
			RequestTrackerSystem->TryGetOperationEvents(Op, EBeamOperationEventType::OET_ERROR, NAME_All, CachedInitializationErrors);
		}
		OnStartedFailed.Broadcast(CachedInitializationErrors);
		OnStartedFailedCode.Broadcast(CachedInitializationErrors);

		OnStartedFailedHandler.ExecuteIfBound(Err);
		// Early out and don't initialize if errors happen here.
		return;
	}

	// If everything is fine... so let's continue with initializing Beamable.
	if (const bool bIsDedicatedServer = GetGameInstance()->IsDedicatedServerInstance())
	{
		// We don't ever automatically sign in for dedicated server builds (the flow for authentication is different when in the server).
		UE_LOG(LogBeamRuntime, Display,
		       TEXT(
			       "Skipping Frictionless Auth with Beamable since we are a dedicated server! When we have server-auth tokens, this will have to change to support that."
		       ));

		// Let's just load up the target realm secret from the follow hierarchy:
		//   - If we got an cmd line argument called --realm-secret <realm_secret>, use this
		//   - If there's no cmd line argument, check for an environment variable called BEAMABLE_REALM_SECRET
		//   - If there's no EnvVar, explode.
		// We need this to support signed requests as the preferred way of having a secure server talk to beamable.
		// This will likely change once we have Server Tokens (at which point, the request flow will likely leverage the UserSlot auth system and this should be removed).
		FString RealmSecret;
		if (!FParse::Value(FCommandLine::Get(), TEXT("beamable-realm-secret="), RealmSecret))
		{
			RealmSecret = FPlatformMisc::GetEnvironmentVariable(TEXT("BEAMABLE_REALM_SECRET"));			
		}

		// Set the realm secret outside of the editor
		// In the editor, this is set by the UBeamEditor subsystem whenever you change realms. 
		if (!GIsEditor)
		{
			checkf(!RealmSecret.IsEmpty(), TEXT("To run a dedicated server that communicates with Beamable, either:\n"
					   "- Start it with the command line \'-beamable-realm-secret <realm_secret>\'\n"
					   "- Start it in an environment with the EnvVar \'BEAMABLE_REALM_SECRET\' set to your realm secret.\n"
					   "To find your realm secret for your realms, look into your Project Settings => Editor => Beamable Editor => PerSlotDeveloperProjectData => All Realms\n"
					   "Remember to set this command line argument in your Networking settings for playmode in Editor Settings => Level Editor => Play => Multiplayer Options => Server => Additional Server Launch Parameters."
				   ))
			
			GEngine->GetEngineSubsystem<UBeamBackend>()->RealmSecret = RealmSecret;			
		}		
	}

	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			OnBeamableStartingOps.Reset(AutomaticallyInitializedSubsystems.Num());
			for (auto& Subsystem : AutomaticallyInitializedSubsystems)
			{
				FBeamOperationHandle Handle;
				Subsystem->OnBeamableStarting(Handle);
				OnBeamableStartingOps.Add(Handle);
			}
			const auto OnCompleteCode = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::TriggerOnContentReady, bApplyFrictionlessLogin, LoginInitProperties, OnStartedHandler, OnStartedFailedHandler);
			OnBeamableStartingWait = RequestTrackerSystem->CPP_WaitAll({}, OnBeamableStartingOps, {}, OnCompleteCode);
		}
	}
}

void UBeamRuntime::TriggerOnContentReady(FBeamWaitCompleteEvent Evt, bool bApplyFrictionlessLogin, TMap<FString, FString> LoginInitProperties, FBeamRuntimeHandler OnStartedHandler,
                                         FRuntimeError OnStartedFailedHandler)
{
	// Handle errors in operations we were waiting on...
	TArray<FString> Errors;
	if (RequestTrackerSystem->IsWaitFailed(Evt, Errors))
	{
		CurrentSdkState = ESDKState::InitializationFailed;

		FString Err;
		for (const auto& Error : Errors) Err += Error + TEXT("\n");
		UE_LOG(LogBeamRuntime, Error, TEXT("%s"), *Err);

		CachedInitializationErrors.Empty();
		for (auto& Op : Evt.Operations)
		{
			RequestTrackerSystem->TryGetOperationEvents(Op, EBeamOperationEventType::OET_ERROR, NAME_All, CachedInitializationErrors);
		}
		OnStartedFailed.Broadcast(CachedInitializationErrors);
		OnStartedFailedCode.Broadcast(CachedInitializationErrors);

		OnStartedFailedHandler.ExecuteIfBound(Err);
		// Early out and don't initialize if errors happen here.
		return;
	}

	// Here, we are just giving UBeamRuntimeSubsystem implementations the opportunity to initialize themselves based on content definitions (but not FUserSlots).
	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			OnBeamableContentReadyOps.Reset(AutomaticallyInitializedSubsystems.Num());
			for (auto& Subsystem : AutomaticallyInitializedSubsystems)
			{
				FBeamOperationHandle Handle;
				Subsystem->OnBeamableContentReady(Handle);
				OnBeamableContentReadyOps.Add(Handle);
			}

			const auto OnCompleteCode = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::TriggerOnStartedAndFrictionlessAuth, bApplyFrictionlessLogin, LoginInitProperties, OnStartedHandler,
			                                                               OnStartedFailedHandler);
			OnBeamableContentReadyWait = RequestTrackerSystem->CPP_WaitAll({}, OnBeamableContentReadyOps, {}, OnCompleteCode);
		}
	}
}

void UBeamRuntime::TriggerOnStartedAndFrictionlessAuth(FBeamWaitCompleteEvent Evt, bool bApplyFrictionlessLogin, TMap<FString, FString> LoginInitProperties, FBeamRuntimeHandler OnStartedHandler,
                                                       FRuntimeError OnStartedFailedHandler)
{
	// Handle errors in operations we were waiting on...
	TArray<FString> Errors;
	if (RequestTrackerSystem->IsWaitFailed(Evt, Errors))
	{
		CurrentSdkState = ESDKState::InitializationFailed;

		FString Err;
		for (const auto& Error : Errors) Err += Error + TEXT("\n");
		UE_LOG(LogBeamRuntime, Error, TEXT("%s"), *Err);

		CachedInitializationErrors.Empty();
		for (auto& Op : Evt.Operations)
		{
			RequestTrackerSystem->TryGetOperationEvents(Op, EBeamOperationEventType::OET_ERROR, NAME_All, CachedInitializationErrors);
		}
		OnStartedFailed.Broadcast(CachedInitializationErrors);
		OnStartedFailedCode.Broadcast(CachedInitializationErrors);

		OnStartedFailedHandler.ExecuteIfBound(Err);
		// Early out and don't initialize if errors happen here.
		return;
	}
	for (auto& Subsystem : AutomaticallyInitializedSubsystems)
	{
		Subsystem->CurrentState = ESubsystemState::BeamInitialized;
	}
	// Everything is fine so let's continue initializing Beamable by firing off the OnStarted callback.
	OnStartedCode.Broadcast();
	OnStarted.Broadcast();
	OnStartedHandler.ExecuteIfBound();

	CurrentSdkState = ESDKState::Initialized;

	// For servers, don't try to authenticate.
	if (const bool bIsDedicatedServer = GetGameInstance()->IsDedicatedServerInstance())
	{
	}
	// Sign in automatically to the owner player slot (if configured to do so).
	else if (bApplyFrictionlessLogin)
	{
		CPP_LoginFrictionlessOperation(GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot(), LoginInitProperties, {});
	}
}

// OnUserReady flow / OnUserCleared flow

void UBeamRuntime::TriggerOnUserSlotAuthenticated(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const FBeamOperationHandle& AuthOpHandle, const UObject* Context)
{
	if (!Context)
	{
		RequestTrackerSystem->TriggerOperationError(AuthOpHandle, "ERR_INVALID_WORLD_CONTEXT");
		return;
	}
	else if (Context && (Context->GetWorld() != GetWorld()))
	{
		//This can happen in multiplayer mode in which this function will be triggered more than once for every running instance
		return;
	}

	UE_LOG(LogBeamRuntime, Verbose, TEXT("Running OnUserSignedIn for Slot. USER_SLOT=%s"), *UserSlot.Name);
	const auto RequestTracker = RequestTrackerSystem;

	if (!OnUserSignedInOps.Contains(UserSlot))
		OnUserSignedInOps.Add(UserSlot, {});

	if (!OnUserSignedInWaits.Contains(UserSlot))
		OnUserSignedInWaits.Add(UserSlot, {});

	auto& SignedInOps = *OnUserSignedInOps.Find(UserSlot);
	auto& SignedInOpsWait = *OnUserSignedInWaits.Find(UserSlot);
	SignedInOps.Empty();

	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			const TArray<UBeamRuntimeSubsystem*> Subsystems = GameInstance->GetSubsystemArrayCopy<UBeamRuntimeSubsystem>();
			for (auto& Subsystem : Subsystems)
			{
				if (Subsystem->CurrentState == BeamInitialized)
				{
					if (!Subsystem->CurrentUserState.Contains(UserSlot))
						Subsystem->CurrentUserState.Add(UserSlot, BeamInitializedNoUserData);

					if (Subsystem->CurrentUserState[UserSlot] == BeamInitializedNoUserData)
					{
						FBeamOperationHandle Handle;
						Subsystem->OnUserSignedIn(UserSlot, BeamRealmUser, GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot().Equals(UserSlot), Handle);
						SignedInOps.Add(Handle);
					}
				}
			}
			const auto SignedInOpsHandler = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::TriggerSubsystemPostUserSignIn, UserSlot, BeamRealmUser, AuthOpHandle);
			SignedInOpsWait = RequestTracker->CPP_WaitAll({}, SignedInOps, {}, SignedInOpsHandler);
		}
	}
}

void UBeamRuntime::TriggerSubsystemPostUserSignIn(FBeamWaitCompleteEvent Evt, FUserSlot UserSlot, FBeamRealmUser BeamRealmUser, FBeamOperationHandle AuthOpHandle)
{
	// Handle errors in operations we were waiting on...
	TArray<FString> Errors;
	if (RequestTrackerSystem->IsWaitFailed(Evt, Errors))
	{
		FString Err;
		for (const auto& Error : Errors) Err += Error + TEXT("\n");
		UE_LOG(LogBeamRuntime, Error, TEXT("%s"), *Err);

		TArray<FBeamOperationEvent> ErrorEvents;
		for (auto& Op : Evt.Operations)
		{
			RequestTrackerSystem->TryGetOperationEvents(Op, EBeamOperationEventType::OET_ERROR, NAME_All, ErrorEvents);
		}

		OnUserInitFailed.Broadcast(UserSlot, ErrorEvents);
		OnUserInitFailedCode.Broadcast(UserSlot, ErrorEvents);
		RequestTrackerSystem->TriggerOperationError(AuthOpHandle, {});
		// Early out and don't initialize if errors happen here.
		return;
	}

	UE_LOG(LogBeamRuntime, Verbose, TEXT("Running OnPostUserSignedIn for Slot. USER_SLOT=%s"), *UserSlot.Name);

	// Everything went well so let's continue with this user's initialization process
	if (!OnPostUserSignedInOps.Contains(UserSlot))
		OnPostUserSignedInOps.Add(UserSlot, {});

	if (!OnPostUserSignedInWaits.Contains(UserSlot))
		OnPostUserSignedInWaits.Add(UserSlot, {});

	FBeamWaitHandle& SignedInOpsWait = *OnPostUserSignedInWaits.Find(UserSlot);
	TArray<FBeamOperationHandle>& SignedInOps = *OnPostUserSignedInOps.Find(UserSlot);
	SignedInOps.Empty();

	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			const TArray<UBeamRuntimeSubsystem*> Subsystems = GameInstance->GetSubsystemArrayCopy<UBeamRuntimeSubsystem>();
			for (auto& Subsystem : Subsystems)
			{
				if (Subsystem->CurrentState == BeamInitialized)
				{
					if (!Subsystem->CurrentUserState.Contains(UserSlot))
						Subsystem->CurrentUserState.Add(UserSlot, BeamInitializedNoUserData);

					if (Subsystem->CurrentUserState[UserSlot] == BeamInitializedNoUserData)
					{
						FBeamOperationHandle Handle;
						Subsystem->OnPostUserSignedIn(UserSlot, BeamRealmUser, GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot().Equals(UserSlot), Handle);
						SignedInOps.Add(Handle);
					}
				}
			}

			const auto SignedInOpsHandler = FOnWaitCompleteCode::CreateLambda([this, UserSlot, Subsystems, AuthOpHandle](const FBeamWaitCompleteEvent& PostEvt)
			{
				// Handle errors in operations we were waiting on...
				TArray<FString> Errors;
				if (RequestTrackerSystem->IsWaitFailed(PostEvt, Errors))
				{
					FString Err;
					for (const auto& Error : Errors) Err += Error + TEXT("\n");
					UE_LOG(LogBeamRuntime, Error, TEXT("%s"), *Err);

					TArray<FBeamOperationEvent> ErrorEvents;
					for (auto& Op : PostEvt.Operations)
					{
						RequestTrackerSystem->TryGetOperationEvents(Op, EBeamOperationEventType::OET_ERROR, NAME_All, ErrorEvents);
					}

					OnUserInitFailed.Broadcast(UserSlot, ErrorEvents);
					OnUserInitFailedCode.Broadcast(UserSlot, ErrorEvents);
					RequestTrackerSystem->TriggerOperationError(AuthOpHandle, {});

					// Early out and don't initialize if errors happen here.
					return;
				}

				for (auto& Subsystem : Subsystems)
				{
					if (!Subsystem->CurrentUserState.Contains(UserSlot))
						Subsystem->CurrentUserState.Add(UserSlot, BeamInitializedNoUserData);

					if (Subsystem->CurrentUserState[UserSlot] == BeamInitializedNoUserData)
					{
						Subsystem->CurrentUserState[UserSlot] = BeamInitializedWithUserData;
					}
				}
				RequestTrackerSystem->TriggerOperationSuccess(AuthOpHandle, {});

				OnUserReadyCode.Broadcast(UserSlot);
				OnUserReady.Broadcast(UserSlot);
			});
			SignedInOpsWait = RequestTrackerSystem->CPP_WaitAll({}, SignedInOps, {}, SignedInOpsHandler);
		}
	}
}

void UBeamRuntime::TriggerOnUserSlotCleared(const EUserSlotClearedReason& Reason, const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context)
{
	if (!Context || (Context && (Context->GetWorld() != GetWorld()))) return;

	// We unsubscribe automatically all notification handlers associated with a user slot when that user signs out --- then we close the connection
	NotificationSystem->TryUnsubscribeAllFromSlot(UserSlot, DefaultNotificationChannel, this);
	NotificationSystem->CloseSocketsForSlot(UserSlot, this);

	// If we clear the slot during login or signup due to failure, we don't need to run the rest of the flow.
	if (Reason == USCR_FailedAuthentication)
		return;

	// Reset some connectivity metrics
	if (ConnectivityState.Contains(UserSlot))
	{
		UBeamConnectivityManager* ConnectivityManager = ConnectivityState.FindRef(UserSlot);
		ConnectivityManager->CurrentState = CONN_Offline;
		ConnectivityManager->CurrentConnectionLostTime = FDateTime::UtcNow();
		ConnectivityManager->ConnectionLostCountInSession = 0;
		ConnectivityManager->CurrentReconnectionCount = 0;
	}

	const auto Connectivity = ConnectivityState.FindRef(UserSlot);

	// Let BeamRuntimeSubsystems run their callbacks
	UBeamRequestTracker* RequestTracker = RequestTrackerSystem;
	if (!OnUserSignedOutOps.Contains(UserSlot))
		OnUserSignedOutOps.Add(UserSlot, {});

	if (!OnUserSignedOutWaits.Contains(UserSlot))
		OnUserSignedOutWaits.Add(UserSlot, {});

	FBeamWaitHandle& SignedOutOpsWait = *OnUserSignedOutWaits.Find(UserSlot);
	TArray<FBeamOperationHandle>& SignedOutOps = *OnUserSignedOutOps.Find(UserSlot);
	SignedOutOps.Empty();

	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			const TArray<UBeamRuntimeSubsystem*> Subsystems = GameInstance->GetSubsystemArrayCopy<UBeamRuntimeSubsystem>();

			SignedOutOps.Reset(Subsystems.Num());
			for (auto& Subsystem : Subsystems)
			{
				FBeamOperationHandle Handle;
				Subsystem->OnUserSignedOut(UserSlot, Reason, BeamRealmUser, Handle);
				SignedOutOps.Add(Handle);
			}

			const auto SignedOutOpsHandler = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::TriggerPostUserSignedOut, UserSlot, Reason, BeamRealmUser);
			SignedOutOpsWait = RequestTracker->CPP_WaitAll({}, SignedOutOps, {}, SignedOutOpsHandler);
		}
	}
}

void UBeamRuntime::TriggerPostUserSignedOut(FBeamWaitCompleteEvent Evt, FUserSlot UserSlot, EUserSlotClearedReason Reason, FBeamRealmUser BeamRealmUser)
{
	// Handle errors in operations we were waiting on...
	TArray<FString> Errors;
	if (RequestTrackerSystem->IsWaitFailed(Evt, Errors))
	{
		FString Err;
		for (const auto& Error : Errors) Err += Error + TEXT("\n");
		UE_LOG(LogBeamRuntime, Error, TEXT("%s"), *Err);

		// Early out and don't initialize if errors happen here.
		return;
	}

	// Everything went well with the first step in the user sign out flow so lets continue 
	if (!OnPostUserSignedOutOps.Contains(UserSlot))
		OnPostUserSignedOutOps.Add(UserSlot, {});

	if (!OnPostUserSignedOutWaits.Contains(UserSlot))
		OnPostUserSignedOutWaits.Add(UserSlot, {});

	FBeamWaitHandle& SignedOutOpsWait = *OnPostUserSignedOutWaits.Find(UserSlot);
	TArray<FBeamOperationHandle>& SignedOutOps = *OnPostUserSignedOutOps.Find(UserSlot);
	SignedOutOps.Empty();

	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			const TArray<UBeamRuntimeSubsystem*> Subsystems = GameInstance->GetSubsystemArrayCopy<UBeamRuntimeSubsystem>();

			SignedOutOps.Reset(Subsystems.Num());
			for (auto& Subsystem : Subsystems)
			{
				FBeamOperationHandle Handle;
				Subsystem->OnPostUserSignedOut(UserSlot, Reason, BeamRealmUser, Handle);
				SignedOutOps.Add(Handle);
			}

			const auto SignedOutOpsHandler = FOnWaitCompleteCode::CreateLambda([this, UserSlot, Subsystems](const FBeamWaitCompleteEvent& PostEvt)
			{
				// Handle errors in operations we were waiting on...
				TArray<FString> Errors;
				if (RequestTrackerSystem->IsWaitFailed(PostEvt, Errors))
				{
					FString Err;
					for (const auto& Error : Errors) Err += Error + TEXT("\n");
					UE_LOG(LogBeamRuntime, Error, TEXT("%s"), *Err);

					// Early out and don't initialize if errors happen here.
					return;
				}

				for (auto& Subsystem : Subsystems)
				{
					Subsystem->CurrentUserState[UserSlot] = BeamInitializedNoUserData;
				}

				OnUserClearedCode.Broadcast(UserSlot);
				OnUserCleared.Broadcast(UserSlot);
			});
			SignedOutOpsWait = RequestTrackerSystem->CPP_WaitAll({}, SignedOutOps, {}, SignedOutOpsHandler);
		}
	}
}

//Manual subsystems initialization flow

FBeamOperationHandle UBeamRuntime::ManuallyInitializeSubsystemOperation(FUserSlot UserSlot,
                                                                        TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsTypesToInitialize,
                                                                        FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot},
	                                                                         GetClass()->GetFName().ToString(), OnOperationEvent);

	ManuallyInitializeSubsystem(SubsystemsTypesToInitialize, false, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_ManuallyInitializeSubsystemOperation(FUserSlot UserSlot,
                                                                            TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsTypesToInitialize,
                                                                            FBeamOperationEventHandlerCode OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot},
	                                                                             GetClass()->GetFName().ToString(), OnOperationEvent);

	ManuallyInitializeSubsystem(SubsystemsTypesToInitialize, false, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::ManuallyInitializeSubsystemOperationWithUserData(FUserSlot UserSlot,
                                                                                    TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsTypesToInitialize,
                                                                                    FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot},
	                                                                         GetClass()->GetFName().ToString(), OnOperationEvent);

	ManuallyInitializeSubsystem(SubsystemsTypesToInitialize, true, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_ManuallyInitializeSubsystemOperationWithUserData(FUserSlot UserSlot,
                                                                                        TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsTypesToInitialize,
                                                                                        FBeamOperationEventHandlerCode OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot},
	                                                                             GetClass()->GetFName().ToString(), OnOperationEvent);

	ManuallyInitializeSubsystem(SubsystemsTypesToInitialize, true, Handle);
	return Handle;
}


void UBeamRuntime::ManuallyInitializeSubsystem(TArray<TSubclassOf<UBeamRuntimeSubsystem>>& SubsystemsToInit, bool bInitializeUsers, FBeamOperationHandle Op)
{
	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			if (CurrentSdkState == ESDKState::Initialized)
			{
				for (int i = 0; i < SubsystemsToInit.Num(); i++)
				{
					UBeamRuntimeSubsystem* Subsystem = Cast<UBeamRuntimeSubsystem>(GameInstance->GetSubsystemBase(SubsystemsToInit[i]));

					if (Subsystem->GetSubsystemState() == ESubsystemState::BeamInitialized || (Subsystem->GetSubsystemState() == ESubsystemState::BeamInitialized && !bInitializeUsers))
					{
						SubsystemsToInit.RemoveAt(i);
						i--;
					}
				}
				if (SubsystemsToInit.Num() == 0)
				{
					const auto RequestTracker = RequestTrackerSystem;
					RequestTracker->TriggerOperationCancelled(Op,
					                                          TEXT("Attempting to initialize subsystems that are already initialized"));
					return;
				}
				const auto AllSubsystems = GameInstance->GetSubsystemArrayCopy<UBeamRuntimeSubsystem>();

				bool DependencyError = false;
				FString ErrorMessage;
				//Check subsystems  dependency before proceeding with initialization
				for (auto& SubsystemType : SubsystemsToInit)
				{
					UBeamRuntimeSubsystem* Subsystem = Cast<UBeamRuntimeSubsystem>(GameInstance->GetSubsystemBase(SubsystemType));

					TArray<TSubclassOf<UBeamRuntimeSubsystem>> DependingSubsystemsTypes = Subsystem->GetDependingOnSubsystems();

					for (auto& SingleDependingSubsystemType : DependingSubsystemsTypes)
					{
						if (!SubsystemsToInit.Contains(SingleDependingSubsystemType))
						{
							UBeamRuntimeSubsystem* DependingSubsystem = Cast<UBeamRuntimeSubsystem>(GameInstance->GetSubsystemBase(SingleDependingSubsystemType));

							/*if the subsystem we are trying to initialize has dependency on another subsystem that is not going
							to be initialized in this call and not initialized, print an error */

							if (DependingSubsystem->CurrentState != ESubsystemState::BeamInitialized)
							{
								DependencyError = true;

								ErrorMessage += "Subsystem " + SubsystemType->GetName() + "is trying to be initialized without its dependency: " + DependingSubsystem->GetName() + "\n";
							}
						}
					}
				}
				ensureAlwaysMsgf(!DependencyError, TEXT("%s"), *ErrorMessage);


				TArray<FBeamOperationHandle> ManualInitializeWhenUnrealReadyOps;
				ManualInitializeWhenUnrealReadyOps.Reset(SubsystemsToInit.Num());

				for (auto& SubsystemType : SubsystemsToInit)
				{
					UBeamRuntimeSubsystem* Subsystem = Cast<UBeamRuntimeSubsystem>(GameInstance->GetSubsystemBase(SubsystemType));

					if (Subsystem->CurrentState == ESubsystemState::BeamUninitialized)
					{
						FBeamOperationHandle Handle;
						Subsystem->InitializeWhenUnrealReady(Handle);
						ManualInitializeWhenUnrealReadyOps.Add(Handle);
					}
				}

				const auto RequestTracker = RequestTrackerSystem;
				const auto OnCompleteCode = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::TriggerManuallySetSubsystemStarted, SubsystemsToInit, bInitializeUsers,
				                                                               Op);
				RequestTracker->CPP_WaitAll({}, ManualInitializeWhenUnrealReadyOps, {}, OnCompleteCode);
			}
			else
			{
				UE_LOG(LogBeamRuntime, Error, TEXT("Attempting to manually initialize subsystem while the sdk is not initialized"));
				RequestTrackerSystem->TriggerOperationError(Op, TEXT("Beamable SDK Not Initalized"));
			}
		}
	}
}

void UBeamRuntime::TriggerManuallySetSubsystemStarted(FBeamWaitCompleteEvent Evt, TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsToInit, bool bInitializeUsers, FBeamOperationHandle Op)
{
	TArray<FString> Errors;
	if (RequestTrackerSystem->IsWaitFailed(Evt, Errors))
	{
		FString Err;
		for (const auto& Error : Errors) Err += Error + TEXT("\n");
		UE_LOG(LogBeamRuntime, Error, TEXT("%s"), *Err);

		RequestTrackerSystem->TriggerOperationError(Op, *Err);

		// Early out and don't initialize if errors happen here.;
		return;
	}
	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			TArray<FBeamOperationHandle> ManualInitializeWhenSubsystemsStartedOps;
			ManualInitializeWhenSubsystemsStartedOps.Reset(SubsystemsToInit.Num());

			for (auto& SubsystemType : SubsystemsToInit)
			{
				UBeamRuntimeSubsystem* Subsystem = Cast<UBeamRuntimeSubsystem>(GameInstance->GetSubsystemBase(SubsystemType));

				if (Subsystem->CurrentState == ESubsystemState::BeamUninitialized)
				{
					FBeamOperationHandle Handle;
					Subsystem->OnBeamableStarting(Handle);
					ManualInitializeWhenSubsystemsStartedOps.Add(Handle);
				}
			}

			const auto RequestTracker = RequestTrackerSystem;
			const auto OnCompleteCode = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::TriggerManuallySetSubsystemContentReady, SubsystemsToInit, bInitializeUsers,
			                                                               Op);
			RequestTracker->CPP_WaitAll({}, ManualInitializeWhenSubsystemsStartedOps, {}, OnCompleteCode);
		}
	}
}

void UBeamRuntime::TriggerManuallySetSubsystemContentReady(FBeamWaitCompleteEvent Evt, TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsToInit, bool bInitializeUsers, FBeamOperationHandle Op)
{
	TArray<FString> Errors;
	if (RequestTrackerSystem->IsWaitFailed(Evt, Errors))
	{
		FString Err;
		for (const auto& Error : Errors) Err += Error + TEXT("\n");
		UE_LOG(LogBeamRuntime, Error, TEXT("%s"), *Err);

		RequestTrackerSystem->TriggerOperationError(Op, *Err);

		// Early out and don't initialize if errors happen here.
		return;
	}
	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			TArray<FBeamOperationHandle> ManualInitializeWhenContentReadyOps;
			ManualInitializeWhenContentReadyOps.Reset(SubsystemsToInit.Num());

			for (auto& SubsystemType : SubsystemsToInit)
			{
				UBeamRuntimeSubsystem* Subsystem = Cast<UBeamRuntimeSubsystem>(GameInstance->GetSubsystemBase(SubsystemType));

				if (Subsystem->CurrentState == ESubsystemState::BeamUninitialized)
				{
					FBeamOperationHandle Handle;
					Subsystem->OnBeamableContentReady(Handle);
					ManualInitializeWhenContentReadyOps.Add(Handle);
				}
			}

			const auto RequestTracker = RequestTrackerSystem;
			const auto OnCompleteCode = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::TriggerManuallySetSubsystemsUserReady, SubsystemsToInit, bInitializeUsers, Op);

			RequestTracker->CPP_WaitAll({}, ManualInitializeWhenContentReadyOps, {}, OnCompleteCode);
		}
	}
}

void UBeamRuntime::TriggerManuallySetSubsystemsUserReady(FBeamWaitCompleteEvent Evt, TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsToInit, bool bInitializeUsers, FBeamOperationHandle Op)
{
	TArray<FString> Errors;
	if (RequestTrackerSystem->IsWaitFailed(Evt, Errors))
	{
		FString Err;
		for (const auto& Error : Errors) Err += Error + TEXT("\n");
		UE_LOG(LogBeamRuntime, Error, TEXT("%s"), *Err);

		RequestTrackerSystem->TriggerOperationError(Op, *Err);

		// Early out and don't initialize if errors happen here.
		return;
	}
	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			for (auto& SubsystemType : SubsystemsToInit)
			{
				UBeamRuntimeSubsystem* Subsystem = Cast<UBeamRuntimeSubsystem>(GameInstance->GetSubsystemBase(SubsystemType));

				Subsystem->CurrentState = ESubsystemState::BeamInitialized;
			}
		}
	}
	if (!bInitializeUsers)
	{
		RequestTrackerSystem->TriggerOperationSuccess(Op,TEXT(""));
		return;
	}

	RequestTrackerSystem->TriggerOperationEvent(Op, OET_SUCCESS, GetOperationEventID_SubsystemsInitializedWithoutUserData(), "");
	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			TArray<FBeamOperationHandle> ManualInitializeOnUserReadyOps;
			ManualInitializeOnUserReadyOps.Reset(SubsystemsToInit.Num());

			for (auto& SubsystemType : SubsystemsToInit)
			{
				UBeamRuntimeSubsystem* Subsystem = Cast<UBeamRuntimeSubsystem>(GameInstance->GetSubsystemBase(SubsystemType));

				for (auto UserSlot : UserSlotSystem->GetKnownSlots())
				{
					FBeamRealmUser UserData;
					if (UserSlotSystem->GetUserDataAtSlot(UserSlot, UserData, this))
					{
						FBeamOperationHandle Handle;
						Subsystem->OnUserSignedIn(UserSlot, UserData, GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot().Equals(UserSlot), Handle);
						ManualInitializeOnUserReadyOps.Add(Handle);
					}
				}
			}

			const auto RequestTracker = RequestTrackerSystem;
			const auto OnCompleteCode = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::TriggerManuallySubsystemsPostUserSignIn, SubsystemsToInit, Op);
			RequestTracker->CPP_WaitAll({}, ManualInitializeOnUserReadyOps, {}, OnCompleteCode);
		}
	}
}

void UBeamRuntime::TriggerManuallySubsystemsPostUserSignIn(FBeamWaitCompleteEvent Evt, TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsToInit, FBeamOperationHandle Op)
{
	TArray<FString> Errors;
	if (RequestTrackerSystem->IsWaitFailed(Evt, Errors))
	{
		FString Err;
		for (const auto& Error : Errors) Err += Error + TEXT("\n");
		UE_LOG(LogBeamRuntime, Error, TEXT("%s"), *Err);

		RequestTrackerSystem->TriggerOperationError(Op, *Err);

		// Early out and don't initialize if errors happen here.
		return;
	}
	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			//this lambda will be called after post user sign in is called on all subsystems
			const auto SignedInOpsHandler = FOnWaitCompleteCode::CreateLambda([this,Op,SubsystemsToInit](const FBeamWaitCompleteEvent& PostEvt)
			{
				// Handle errors in operations we were waiting on...
				TArray<FString> Errors;
				if (RequestTrackerSystem->IsWaitFailed(PostEvt, Errors))
				{
					FString Err;
					for (const auto& Error : Errors) Err += Error + TEXT("\n");
					UE_LOG(LogBeamRuntime, Error, TEXT("%s"), *Err);

					RequestTrackerSystem->TriggerOperationError(Op, *Err);

					// Early out and don't initialize if errors happen here.
					return;
				}
				if (const UWorld* World = GetWorld())
				{
					if (const UGameInstance* GameInstance = World->GetGameInstance())
					{
						for (auto& SubsystemType : SubsystemsToInit)
						{
							UBeamRuntimeSubsystem* Subsystem = Cast<UBeamRuntimeSubsystem>(GameInstance->GetSubsystemBase(SubsystemType));
							for (auto UserSlot : UserSlotSystem->GetKnownSlots())
							{
								FBeamRealmUser UserData;
								if (UserSlotSystem->GetUserDataAtSlot(UserSlot, UserData, this))
								{
									Subsystem->CurrentUserState[UserSlot] = BeamInitializedWithUserData;
								}
							}
						}
					}
				}
				RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
			});

			TArray<FBeamOperationHandle> ManualInitializePostUserSignInOps;
			ManualInitializePostUserSignInOps.Reset(SubsystemsToInit.Num());

			for (auto& SubsystemType : SubsystemsToInit)
			{
				UBeamRuntimeSubsystem* Subsystem = Cast<UBeamRuntimeSubsystem>(GameInstance->GetSubsystemBase(SubsystemType));

				for (auto UserSlot : GetDefault<UBeamCoreSettings>()->RuntimeUserSlots)
				{
					FBeamRealmUser UserData;
					if (UserSlotSystem->GetUserDataAtSlot(UserSlot, UserData, this))
					{
						FBeamOperationHandle Handle;
						Subsystem->OnPostUserSignedIn(UserSlot, UserData, GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot().Equals(UserSlot), Handle);
						ManualInitializePostUserSignInOps.Add(Handle);
					}
				}
			}

			const auto RequestTracker = RequestTrackerSystem;
			RequestTracker->CPP_WaitAll({}, ManualInitializePostUserSignInOps, {}, SignedInOpsHandler);
		}
	}
}

// Login/Signup/Attach Operations

FBeamOperationHandle UBeamRuntime::LoginFromCacheOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	LoginFromCache(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_LoginFromCacheOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	LoginFromCache(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::LoginFrictionlessOperation(FUserSlot UserSlot, TMap<FString, FString> InitProperties, FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	LoginFrictionless(UserSlot, InitProperties, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_LoginFrictionlessOperation(FUserSlot UserSlot, TMap<FString, FString> InitProperties, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	LoginFrictionless(UserSlot, InitProperties, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::LoginFederatedOperation(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedAuthToken,
                                                           FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	LoginFederated(UserSlot, MicroserviceId, FederationId, FederatedAuthToken, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_LoginFederatedOperation(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedAuthToken,
                                                               FBeamOperationEventHandlerCode OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	LoginFederated(UserSlot, MicroserviceId, FederationId, FederatedAuthToken, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::FetchExternalIdentityOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchExternalIdentities(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_FetchExternalIdentityOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchExternalIdentities(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CommitLoginFederatedOperation(FUserSlot UserSlot, UBeamMultiFactorLoginData* MultiFactorData, FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CommitLoginFederated(UserSlot, MultiFactorData, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_CommitLoginFederatedOperation(FUserSlot UserSlot, UBeamMultiFactorLoginData* MultiFactorData, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CommitLoginFederated(UserSlot, MultiFactorData, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::LoginEmailAndPasswordOperation(FUserSlot UserSlot, FString Email, FString Password, FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	LoginEmailAndPassword(UserSlot, Email, Password, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_LoginEmailAndPasswordOperation(FUserSlot UserSlot, FString Email, FString Password, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	LoginEmailAndPassword(UserSlot, Email, Password, Handle);
	return Handle;
}


FBeamOperationHandle UBeamRuntime::AttachFederatedOperation(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedUserId, FString FederatedAuthToken,
                                                            FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	AttachFederated(UserSlot, MicroserviceId, FederationId, FederatedUserId, FederatedAuthToken, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_AttachFederatedOperation(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedUserId, FString FederatedAuthToken,
                                                                FBeamOperationEventHandlerCode OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	AttachFederated(UserSlot, MicroserviceId, FederationId, FederatedUserId, FederatedAuthToken, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CommitAttachFederatedOperation(FUserSlot UserSlot, UBeamMultiFactorLoginData* MultiFactorData, FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CommitAttachFederated(UserSlot, MultiFactorData, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_CommitAttachFederatedOperation(FUserSlot UserSlot, UBeamMultiFactorLoginData* MultiFactorData, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CommitAttachFederated(UserSlot, MultiFactorData, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::AttachEmailAndPasswordOperation(FUserSlot UserSlot, FString Email, FString Password, FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	AttachEmailAndPassword(UserSlot, Email, Password, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_AttachEmailAndPasswordOperation(FUserSlot UserSlot, FString Email, FString Password, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	AttachEmailAndPassword(UserSlot, Email, Password, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::SignUpFederatedOperation(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedUserId, FString FederatedAuthToken,
                                                            bool bAutoLogin, TMap<FString, FString> InitProperties, FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	SignUpFederated(UserSlot, MicroserviceId, FederationId, FederatedUserId, FederatedAuthToken, bAutoLogin, InitProperties, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_SignUpFederatedOperation(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedUserId, FString FederatedAuthToken,
                                                                bool bAutoLogin, TMap<FString, FString> InitProperties, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	SignUpFederated(UserSlot, MicroserviceId, FederationId, FederatedUserId, FederatedAuthToken, bAutoLogin, InitProperties, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::SignUpEmailAndPasswordOperation(FUserSlot UserSlot, FString Email, FString Password, bool bAutoLogin, TMap<FString, FString> InitProperties, FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	SignUpEmailAndPassword(UserSlot, Email, Password, bAutoLogin, InitProperties, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_SignUpEmailAndPasswordOperation(FUserSlot UserSlot, FString Email, FString Password, bool bAutoLogin, TMap<FString, FString> InitProperties,
                                                                       FBeamOperationEventHandlerCode OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	SignUpEmailAndPassword(UserSlot, Email, Password, bAutoLogin, InitProperties, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::LogoutOperation(FUserSlot UserSlot, EUserSlotClearedReason Reason, bool bRemoveLocalData, FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	Logout(UserSlot, Reason, bRemoveLocalData, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_LogoutOperation(FUserSlot UserSlot, EUserSlotClearedReason Reason, bool bRemoveLocalData, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	Logout(UserSlot, Reason, bRemoveLocalData, Handle);
	return Handle;
}

void UBeamRuntime::LoginFromCache(FUserSlot UserSlot, FBeamOperationHandle Op)
{
	// Try to load the user at a specific slot and if it fails throws an exception.
	LoadCachedUserAtSlot(UserSlot, Op, FSimpleDelegate::CreateLambda([this, UserSlot, Op]()
	{
		FBeamRealmUser RealmUser;

		// If we are already authenticated (we had a saved user in this slot), we simply broadcast this message out
		if (UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
		{
			RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
		}
		else
		{
			RequestTrackerSystem->TriggerOperationError(Op, TEXT("There's no cached user to do the login."));
		}
	}));
}

void UBeamRuntime::LoginFrictionless(FUserSlot UserSlot, TMap<FString, FString> InitProperties, FBeamOperationHandle Op)
{
	// Try to load the user at a specific slot and if it fails... we login with a guest account.
	LoadCachedUserAtSlot(UserSlot, Op, FSimpleDelegate::CreateLambda([this, UserSlot, Op, InitProperties]()
	{
		FBeamRealmUser RealmUser;

		// If we are already authenticated (we had a saved user in this slot), we simply broadcast this message out
		if (UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
		{
			RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
		}
		else
		{
			UE_LOG(LogBeamRuntime, Verbose, TEXT("Frictionless Auth - Not signed into slot! Starting Frictionless Auth process! SLOT=%s"), *UserSlot.Name);
			LoginGuest(UserSlot, Op, InitProperties);
		}
	}));
}


void UBeamRuntime::LoginFederated(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedAuthToken, FBeamOperationHandle Op)
{
	UAuthenticateRequest* Req = NewObject<UAuthenticateRequest>(GetTransientPackage());
	Req->Body = NewObject<UTokenRequestWrapper>(Req);
	Req->Body->GrantType = TEXT("external");
	Req->Body->ExternalToken = FOptionalString{FederatedAuthToken};
	Req->Body->ProviderService = FOptionalString{MicroserviceId};
	Req->Body->ProviderNamespace = FOptionalString{FederationId};

	const UBeamAuthApi* AuthSubsystem = GEngine->GetEngineSubsystem<UBeamAuthApi>();

	// If we are already authenticated (we had a saved user in this slot), we sign out of the user at that slot, wait for all runtime systems to clean up the user and then sign back into the given user.
	FBeamRealmUser RealmUser;
	if (UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		// Configure us to wait until the slot is fully unauthenticated and then sign in.
		UserSlotClearedEnqueuedHandle = OnUserClearedCode.AddLambda(
			[this, AuthSubsystem](FUserSlot UserSlot, FBeamOperationHandle OpHandle, UAuthenticateRequest* AuthReq, FString MicroserviceId, FString FederationId, FString FederatedAuthToken)
			{
				const auto AuthenticateHandler = FOnAuthenticateFullResponse::CreateUObject(this, &UBeamRuntime::OnAuthenticated, UserSlot, OpHandle, FDelayedOperation{}, MicroserviceId, FederationId,
				                                                                            FederatedAuthToken);
				FBeamRequestContext RequestContext;
				AuthSubsystem->CPP_Authenticate(AuthReq, AuthenticateHandler, RequestContext, OpHandle, this);

				// Clean Up handle
				OnUserClearedCode.Remove(UserSlotClearedEnqueuedHandle);
				UserSlotClearedEnqueuedHandle = {};
			}, Op, Req, MicroserviceId, FederationId, FederatedAuthToken);
		UserSlotSystem->ClearUserAtSlot(UserSlot, USCR_Manual, true, this);
	}
	else
	{
		const auto AuthenticateHandler = FOnAuthenticateFullResponse::CreateUObject(this, &UBeamRuntime::OnAuthenticated, UserSlot, Op, FDelayedOperation{}, MicroserviceId, FederationId, FederatedAuthToken);
		FBeamRequestContext RequestContext;
		AuthSubsystem->CPP_Authenticate(Req, AuthenticateHandler, RequestContext, Op, this);
	}
}

void UBeamRuntime::CommitLoginFederated(FUserSlot UserSlot, UBeamMultiFactorLoginData* ChallengeSolution, FBeamOperationHandle Op)
{
	UAuthenticateRequest* Req = NewObject<UAuthenticateRequest>(GetTransientPackage());
	Req->Body = NewObject<UTokenRequestWrapper>(Req);
	Req->Body->GrantType = TEXT("external");
	Req->Body->ExternalToken = FOptionalString{ChallengeSolution->FederatedUserAuthToken};
	Req->Body->ProviderService = FOptionalString{ChallengeSolution->MicroserviceId};
	Req->Body->ProviderNamespace = FOptionalString{ChallengeSolution->FederationId};
	Req->Body->ChallengeSolution = FOptionalChallengeSolution{ChallengeSolution->GetChallengeSolutionGenerated()};

	const UBeamAuthApi* AuthSubsystem = GEngine->GetEngineSubsystem<UBeamAuthApi>();

	FOnAuthenticateFullResponse Handler =
		FOnAuthenticateFullResponse::CreateLambda([this, UserSlot, ChallengeSolution, Op](FAuthenticateFullResponse Response)
		{
			// Triggers the Op operation and then triggers the challenge operation handle in the on authenticated method
			if (Response.State == RS_Success)
			{
				RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
			}
			else
			{
				RequestTrackerSystem->TriggerOperationError(Op, Response.ErrorData.message);
			}
			// Triggers the on authenticated after with the challenge operation.
			OnAuthenticated(Response, UserSlot, ChallengeSolution->OperationHandler, FDelayedOperation{}, ChallengeSolution->MicroserviceId, ChallengeSolution->FederationId, ChallengeSolution->FederatedUserAuthToken);
		});

	// If we are already authenticated (we had a saved user in this slot), we sign out of the user at that slot, wait for all runtime systems to clean up the user and then sign back into the given user.
	FBeamRealmUser RealmUser;
	if (UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		// Configure us to wait until the slot is fully unauthenticated and then sign in.
		UserSlotClearedEnqueuedHandle = OnUserClearedCode.AddLambda([this, AuthSubsystem](FUserSlot UserSlot, FBeamOperationHandle OpHandle, UAuthenticateRequest* AuthReq, const FOnAuthenticateFullResponse& Handler)
		{
			FBeamRequestContext RequestContext;
			AuthSubsystem->CPP_Authenticate(AuthReq, Handler, RequestContext, OpHandle, this);

			// Clean Up handle
			OnUserClearedCode.Remove(UserSlotClearedEnqueuedHandle);
			UserSlotClearedEnqueuedHandle = {};
		}, Op, Req, Handler);
		UserSlotSystem->ClearUserAtSlot(UserSlot, USCR_Manual, true, this);
	}
	else
	{
		FBeamRequestContext RequestContext;
		AuthSubsystem->CPP_Authenticate(Req, Handler, RequestContext, Op, this);
	}
}


void UBeamRuntime::LoginEmailAndPassword(FUserSlot UserSlot, FString Email, FString Password, FBeamOperationHandle Op)
{
	UAuthenticateRequest* Req = NewObject<UAuthenticateRequest>(GetTransientPackage());
	Req->Body = NewObject<UTokenRequestWrapper>(Req);
	Req->Body->GrantType = TEXT("password");
	Req->Body->Username = FOptionalString{Email};
	Req->Body->Password = FOptionalString{Password};

	const UBeamAuthApi* AuthSubsystem = GEngine->GetEngineSubsystem<UBeamAuthApi>();

	// If we are already authenticated (we had a saved user in this slot), we sign out of the user at that slot, wait for all runtime systems to clean up the user and then sign back into the given user.
	FBeamRealmUser RealmUser;
	if (UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		// Configure us to wait until the slot is fully unauthenticated and then sign in.
		UserSlotClearedEnqueuedHandle = OnUserClearedCode.AddLambda(
			[this, AuthSubsystem](FUserSlot UserSlot, FBeamOperationHandle OpHandle, UAuthenticateRequest* AuthReq, FString MicroserviceId, FString FederationId, FString FederatedAuthToken)
			{
				const auto AuthenticateHandler = FOnAuthenticateFullResponse::CreateUObject(this, &UBeamRuntime::OnAuthenticated, UserSlot, OpHandle, FDelayedOperation{}, MicroserviceId, FederationId,
				                                                                            FederatedAuthToken);

				FBeamRequestContext RequestContext;
				AuthSubsystem->CPP_Authenticate(AuthReq, AuthenticateHandler, RequestContext, OpHandle, this);

				// Clean Up handle
				OnUserClearedCode.Remove(UserSlotClearedEnqueuedHandle);
				UserSlotClearedEnqueuedHandle = {};
			}, Op, Req, TEXT(""), TEXT(""), TEXT(""));

		UserSlotSystem->ClearUserAtSlot(UserSlot, USCR_Manual, true, this);
	}
	else
	{
		const auto AuthenticateHandler = FOnAuthenticateFullResponse::CreateUObject(this, &UBeamRuntime::OnAuthenticated, UserSlot, Op, FDelayedOperation{}, FString{}, FString{}, FString{});
		FBeamRequestContext RequestContext;
		AuthSubsystem->CPP_Authenticate(Req, AuthenticateHandler, RequestContext, Op, this);
	}
}

void UBeamRuntime::CommitAttachFederated(FUserSlot UserSlot, UBeamMultiFactorLoginData* ChallengeSolution, FBeamOperationHandle Op)
{
	const auto CheckIdentityAvailableHandler = FOnGetAvailableExternalIdentityFullResponse::CreateLambda(
		[this,UserSlot, Op, ChallengeSolution](FGetAvailableExternalIdentityFullResponse Resp)
		{
			if (Resp.State == RS_Retrying) return;

			if (Resp.State == RS_Success)
			{
				const auto bIsAvailable = Resp.SuccessData->bAvailable;
				UE_LOG(LogTemp, Warning, TEXT("Is Available Identity Id: %s, %s"), *ChallengeSolution->FederatedUserId, bIsAvailable ? TEXT("true") : TEXT("false"));

				// If the Federated Identity has never been assigned in this realm, we attach it to the account at the given slot. 
				if (bIsAvailable)
				{
					const auto AttachIdentityHandler = FOnPostExternalIdentityFullResponse::CreateLambda(
						[this, UserSlot, Op, ChallengeSolution](FPostExternalIdentityFullResponse Resp)
						{
							if (Resp.State == RS_Retrying) return;

							if (Resp.State == RS_Success)
							{
								UE_LOG(LogTemp, Warning, TEXT("Successfully Attached Id! Result = %s"), *Resp.SuccessData->Result);

								AttachLocalIdentity(UserSlot, ChallengeSolution->FederatedUserId, ChallengeSolution->MicroserviceId, ChallengeSolution->FederationId);

								// Trigger the operation as successful
								GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(Op, TEXT(""));
								// Triggers the success for this operation and for the opened operation in the authentication
								GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(ChallengeSolution->OperationHandler, TEXT(""));
							}

							if (Resp.State == RS_Error)
							{
								UE_LOG(LogTemp, Error, TEXT("Failed to Attach Id! Result = %s"), *Resp.ErrorData.message);
								GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, Resp.ErrorData.message);
								// Triggers the success for this operation and for the opened operation in the authentication
								GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(ChallengeSolution->OperationHandler, Resp.ErrorData.message);
							}
						});
					const auto _ = AttachIdentityToUserTwoFactor(UserSlot,
					                                             ChallengeSolution->MicroserviceId,
					                                             ChallengeSolution->FederationId,
					                                             ChallengeSolution->FederatedUserAuthToken,
					                                             ChallengeSolution->GetChallengeSolutionGenerated(), Op, AttachIdentityHandler);
				}
				// If it has been assigned in this realm (a user exists in this realm for this Federated Identity id), we log in with that user account into the requesting slot.			 
				else
				{
					// If this external id is already in use in this realm, we error out.
					GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, TEXT("EXTERNAL_IDENTITY_IN_USE"));
				}
				return;
			}

			GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, Resp.ErrorData.message);
			// Triggers the success for this operation and for the opened operation in the authentication
			GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(ChallengeSolution->OperationHandler, Resp.ErrorData.message);
		});

	// If we are NOT already authenticated (we had a saved user in this slot), we fail the attach.
	if (!UserSlotSystem->IsUserSlotAuthenticated(UserSlot, this))
	{
		RequestTrackerSystem->TriggerOperationError(Op, TEXT("NO_SIGNED_IN_USER_AT_SLOT"));
		return;
	}

	const auto _ = CheckFederatedIdentityAvailable(ChallengeSolution->MicroserviceId, ChallengeSolution->FederationId, ChallengeSolution->FederatedUserId, Op, CheckIdentityAvailableHandler);
}

void UBeamRuntime::FetchExternalIdentities(FUserSlot UserSlot, FBeamOperationHandle Op)
{
	auto Handler = FOnBasicAccountsGetMeFullResponse::CreateLambda([this, UserSlot, Op](const FBasicAccountsGetMeFullResponse& Response)
	{
		if (Response.State == RS_Retrying) return;

		if (Response.State == RS_Success)
		{
			const auto ExternalIds = Response.SuccessData->External;
			if (ExternalIds.IsSet) UserSlotSystem->SetExternalIdsAtSlot(UserSlot, ExternalIds.Val, this);

			RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
		}
		else
		{
			RequestTrackerSystem->TriggerOperationError(Op, Response.ErrorData.message);
		}
	});

	FBeamRequestContext RequestContext;

	const UBeamAccountsApi* AccountSubsystem = GEngine->GetEngineSubsystem<UBeamAccountsApi>();

	UBasicAccountsGetMeRequest* MeReq = UBasicAccountsGetMeRequest::Make(this, {});

	AccountSubsystem->CPP_GetMe(UserSlot, MeReq, Handler, RequestContext, Op, this);
}

void UBeamRuntime::AttachLocalIdentity(FUserSlot UserSlot, FString FederatedUserId, FString MicroserviceId, FString FederationId)
{
	// Update the local list of external ids if the IdentityUserId was provided
	// There are cases of external identities where the Ids are created automatically for the user (Web3 Wallets, for example).
	// In those cases, the IdentityUserId is null and we cannot automatically update the local state here.
	// For those cases, the user should call make an UBeamAccountsApi::CPP_GetMe request, find the newly added identity in the response of that API call and
	// add it to the local state manually like the code below does. 
	if (!FederatedUserId.IsEmpty())
	{
		FBeamRealmUser User;
		if (UserSlotSystem->GetUserDataAtSlot(UserSlot, User, this))
		{
			FBeamExternalIdentity AddedIdentity;
			AddedIdentity.ProviderService = MicroserviceId;
			AddedIdentity.ProviderNamespace = FederationId;
			AddedIdentity.UserId = FederatedUserId;

			User.ExternalIdentities.AddUnique(AddedIdentity);
			UserSlotSystem->SetExternalIdsAtSlot(UserSlot, User.ExternalIdentities, this);
			UserSlotSystem->SaveSlot(UserSlot, this);
		}
	}
}

void UBeamRuntime::AttachFederated(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedUserId, FString FederatedAuthToken, FBeamOperationHandle Op)
{
	const auto CheckIdentityAvailableHandler = FOnGetAvailableExternalIdentityFullResponse::CreateLambda(
		[this,UserSlot, Op, MicroserviceId, FederationId, FederatedUserId, FederatedAuthToken](FGetAvailableExternalIdentityFullResponse Resp)
		{
			if (Resp.State == RS_Retrying) return;

			if (Resp.State == RS_Success)
			{
				const auto bIsAvailable = Resp.SuccessData->bAvailable;
				UE_LOG(LogTemp, Warning, TEXT("Is Available Identity Id: %s, %s"), *FederatedUserId, bIsAvailable ? TEXT("true") : TEXT("false"));

				// If the Federated Identity has never been assigned in this realm, we attach it to the account at the given slot. 
				if (bIsAvailable)
				{
					const auto AttachIdentityHandler = FOnPostExternalIdentityFullResponse::CreateLambda(
						[this, UserSlot, MicroserviceId, FederationId, FederatedUserId, FederatedAuthToken, Op ](FPostExternalIdentityFullResponse Resp)
						{
							if (Resp.State == RS_Retrying) return;

							if (Resp.State == RS_Success)
							{
								// If it is a 2F auth we will trigger the sub event and then call the success when entire flow finish
								if (Resp.SuccessData->ChallengeToken.IsSet)
								{
									const auto ChallengeSolution = NewObject<UBeamMultiFactorLoginData>(GetTransientPackage());

									ChallengeSolution->MicroserviceId = MicroserviceId;
									ChallengeSolution->FederationId = FederationId;
									ChallengeSolution->FederatedUserId = FederatedUserId;
									ChallengeSolution->FederatedUserAuthToken = FederatedAuthToken;
									ChallengeSolution->ChallengeToken = Resp.SuccessData->ChallengeToken.Val;
									ChallengeSolution->OperationHandler = Op;

									RequestTrackerSystem->TriggerOperationEventWithData(Op, OET_SUCCESS, GetOperationEventID_MultiFactorAuthTriggered(), TEXT("2FA_AUTH"), ChallengeSolution);
								}
								else
								{
									UE_LOG(LogTemp, Warning, TEXT("Successfully Attached Id! Result = %s"), *Resp.SuccessData->Result);

									AttachLocalIdentity(UserSlot, FederatedUserId, MicroserviceId, FederationId);

									// Trigger the operation as successful
									GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(Op, TEXT(""));
								}
							}

							if (Resp.State == RS_Error)
							{
								UE_LOG(LogTemp, Error, TEXT("Failed to Attach Id! Result = %s"), *Resp.ErrorData.message);
								GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, Resp.ErrorData.message);
							}
						});
					const auto _ = AttachIdentityToUser(UserSlot, MicroserviceId, FederationId, FederatedAuthToken, Op, AttachIdentityHandler);
				}
				// If it has been assigned in this realm (a user exists in this realm for this Federated Identity id), we log in with that user account into the requesting slot.			 
				else
				{
					// If this external id is already in use in this realm, we error out.
					GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, TEXT("EXTERNAL_IDENTITY_IN_USE"));
				}
				return;
			}
			GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, Resp.ErrorData.message);
		});

	// If we are NOT already authenticated (we had a saved user in this slot), we fail the attach.
	if (!UserSlotSystem->IsUserSlotAuthenticated(UserSlot, this))
	{
		RequestTrackerSystem->TriggerOperationError(Op, TEXT("NO_SIGNED_IN_USER_AT_SLOT"));
		return;
	}

	const auto _ = CheckFederatedIdentityAvailable(MicroserviceId, FederationId, FederatedUserId, Op, CheckIdentityAvailableHandler);
}

void UBeamRuntime::AttachEmailAndPassword(FUserSlot UserSlot, FString Email, FString Password, FBeamOperationHandle Op)
{
	const auto CheckIdentityAvailableHandler = FOnGetAvailableFullResponse::CreateLambda([this,UserSlot, Op, Email, Password](FGetAvailableFullResponse Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			const auto bIsAvailable = Resp.SuccessData->bAvailable;
			UE_LOG(LogTemp, Warning, TEXT("Is Available Email: %s, %s"), *Email, bIsAvailable ? TEXT("true") : TEXT("false"));

			// If the Federated Identity has never been assigned in this realm, we attach it to the account at the given slot. 
			if (bIsAvailable)
			{
				const auto RegisterEmailHandler = FOnBasicAccountsPostRegisterFullResponse::CreateLambda([this, Op](FBasicAccountsPostRegisterFullResponse Resp)
				{
					if (Resp.State == RS_Retrying) return;

					if (Resp.State == RS_Success)
					{
						UE_LOG(LogTemp, Warning, TEXT("Successfully Attached Email! GAMERTAG = %s, EMAIL = %s"), *Resp.SuccessData->Id.AsString, *Resp.SuccessData->Email.Val);
						GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(Op, TEXT(""));
					}

					if (Resp.State == RS_Error)
					{
						UE_LOG(LogTemp, Error, TEXT("Failed to Attach Email! Result = %s"), *Resp.ErrorData.message);
						GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, Resp.ErrorData.message);
					}
				});
				const auto _ = AttachEmailAndPasswordToUser(UserSlot, Email, Password, Op, RegisterEmailHandler);
			}
			// If it has been assigned in this realm (a user exists in this realm for this Federated Identity id), we log in with that user account into the requesting slot.			 
			else
			{
				// If this email is already in use we error out.
				GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, TEXT("EMAIL_IN_USE"));
			}
			return;
		}

		GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, Resp.ErrorData.message);
	});

	// If we are NOT already authenticated (we had a saved user in this slot), we fail the attach.
	if (!UserSlotSystem->IsUserSlotAuthenticated(UserSlot, this))
	{
		RequestTrackerSystem->TriggerOperationError(Op, TEXT("NO_SIGNED_IN_USER_AT_SLOT"));
		return;
	}

	const auto _ = CheckEmailAvailable(Email, Op, CheckIdentityAvailableHandler);
}

void UBeamRuntime::SignUpFederated(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedUserId, FString FederatedAuthToken, bool bAutoLoginOnUnavailable,
                                   TMap<FString, FString> InitProperties,
                                   FBeamOperationHandle Op)
{
	const auto CheckIdentityAvailableHandler = FOnGetAvailableExternalIdentityFullResponse::CreateLambda(
		[this,UserSlot, Op, MicroserviceId, FederationId, FederatedUserId, FederatedAuthToken, InitProperties, bAutoLoginOnUnavailable](FGetAvailableExternalIdentityFullResponse Resp)
		{
			if (Resp.State == RS_Retrying) return;

			if (Resp.State == RS_Success)
			{
				const auto bIsAvailable = Resp.SuccessData->bAvailable;
				UE_LOG(LogTemp, Warning, TEXT("Is Available Identity Id: %s, %s"), *FederatedUserId, bIsAvailable ? TEXT("true") : TEXT("false"));

				// If the Federated Identity has never been assigned in this realm, we create a guest account and then immediately attach this identity to it. 
				if (bIsAvailable)
				{
					// Prepare Init Properties
					auto Props{InitProperties};
					FillDefaultSignUpInitProperties(Props);
					Props.Add(TEXT("__beam_3rd_party_user_id__"), FederatedUserId);
					Props.Add(TEXT("__beam_3rd_party_auth_token__"), FederatedAuthToken);
					LoginGuest(UserSlot, Op, Props, FDelayedOperation::CreateLambda([this, Op, UserSlot, MicroserviceId, FederationId, FederatedUserId, FederatedAuthToken]
					{
						// Begin an operation that'll only succeed if the attachment is successful
						const auto DelayedOp =
							CPP_AttachFederatedOperation(UserSlot,
							                             MicroserviceId,
							                             FederationId,
							                             FederatedUserId,
							                             FederatedAuthToken,
							                             FBeamOperationEventHandlerCode::CreateLambda([this, Op](FBeamOperationEvent Evt)
							                             {
								                             if (Evt.EventType == OET_SUCCESS && Evt.EventId == GetOperationEventID_MultiFactorAuthTriggered())
									                             RequestTrackerSystem->TriggerOperationEventWithData(Op,
									                                                                                 OET_SUCCESS,
									                                                                                 GetOperationEventID_MultiFactorAuthTriggered(),
									                                                                                 TEXT("2FA_AUTH"),
									                                                                                 Evt.EventData);
							                             }));
						return DelayedOp;
					}));
				}
				// If it has been assigned in this realm (a user exists in this realm for this Federated Identity id), we log in with that user account into the requesting slot.			 
				else
				{
					// If this external id is already in use we try to log in if asked to do so. Otherwise, we error out.				
					if (bAutoLoginOnUnavailable)
					{
						const auto _ =
							CPP_LoginFederatedOperation(UserSlot,
							                            MicroserviceId,
							                            FederationId,
							                            FederatedAuthToken,
							                            FBeamOperationEventHandlerCode::CreateLambda([this, Op](FBeamOperationEvent Evt)
							                            {
								                            if (Evt.EventType == OET_SUCCESS && Evt.EventId == GetOperationEventID_MultiFactorAuthTriggered())
									                            RequestTrackerSystem->TriggerOperationEventWithData(Op,
									                                                                                OET_SUCCESS,
									                                                                                GetOperationEventID_MultiFactorAuthTriggered(),
									                                                                                TEXT("2FA_AUTH"),
									                                                                                Evt.EventData);
								                            else if (Evt.EventType == OET_SUCCESS)
									                            RequestTrackerSystem->TriggerOperationSuccess(Op, Evt.EventCode);
								                            else if (Evt.EventType == OET_ERROR)
									                            RequestTrackerSystem->TriggerOperationError(Op, Evt.EventCode);
								                            else if (Evt.EventType == OET_CANCELLED)
									                            RequestTrackerSystem->TriggerOperationCancelled(Op, Evt.EventCode);
							                            }));
					}
					else
					{
						GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, TEXT("EXTERNAL_IDENTITY_IN_USE"));
					}
				}
				return;
			}
			GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, Resp.ErrorData.message);
		});

	// If we are already authenticated (we had a saved user in this slot), we fail the sign up.
	if (UserSlotSystem->IsUserSlotAuthenticated(UserSlot, this))
	{
		RequestTrackerSystem->TriggerOperationError(Op, TEXT("ALREADY_SIGNED_IN"));
		return;
	}

	const auto _ = CheckFederatedIdentityAvailable(MicroserviceId, FederationId, FederatedUserId, Op, CheckIdentityAvailableHandler);
}

void UBeamRuntime::SignUpEmailAndPassword(FUserSlot UserSlot, FString Email, FString Password, bool bAutoLoginOnUnavailable, TMap<FString, FString> InitProperties, FBeamOperationHandle Op)
{
	const auto EncodedEmail = FGenericPlatformHttp::UrlEncode(Email);

	const auto CheckIdentityAvailableHandler = FOnGetAvailableFullResponse::CreateLambda([this,UserSlot, Op, Email, Password, bAutoLoginOnUnavailable, InitProperties](FGetAvailableFullResponse Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			const auto bIsAvailable = Resp.SuccessData->bAvailable;
			UE_LOG(LogTemp, Warning, TEXT("Is Available Email: %s, %s"), *Email, bIsAvailable ? TEXT("true") : TEXT("false"));

			// If this email has never been assigned in this realm, we create a guest account and then immediately attach this email and password to that account. 
			if (bIsAvailable)
			{
				// Prepare Init Properties
				auto Props{InitProperties};
				FillDefaultSignUpInitProperties(Props);
				Props.Add(TEXT("__beam_user_email__"), Email);
				Props.Add(TEXT("__beam_user_password__"), Password);

				LoginGuest(UserSlot, Op, Props, FDelayedOperation::CreateLambda([this, Op, UserSlot, Email, Password]
				{
					// Begin an operation that'll only succeed if the attachment is successful
					const auto DelayedOp = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetName(), {});

					// Attach email/password to the new guest user BEFORE notifying the SDK's runtime systems.
					// If fail to attach, will fail the DelayedOp and error out the entire sign up operation and clear the slots auth state.
					const auto RegisterEmailHandler = FOnBasicAccountsPostRegisterFullResponse::CreateLambda([this, DelayedOp](FBasicAccountsPostRegisterFullResponse Resp)
					{
						if (Resp.State == RS_Retrying) return;

						if (Resp.State == RS_Success)
						{
							UE_LOG(LogTemp, Warning, TEXT("Successfully Attached Email! GAMERTAG = %s, EMAIL = %s"), *Resp.SuccessData->Id.AsString, *Resp.SuccessData->Email.Val);
							RequestTrackerSystem->TriggerOperationSuccess(DelayedOp, "");
						}

						if (Resp.State == RS_Error)
						{
							UE_LOG(LogTemp, Error, TEXT("Failed to Attach Email! Result = %s"), *Resp.ErrorData.message);
							RequestTrackerSystem->TriggerOperationError(DelayedOp, Resp.ErrorData.message);
						}
					});
					const auto AttachCtx = AttachEmailAndPasswordToUser(UserSlot, Email, Password, DelayedOp, RegisterEmailHandler);

					return DelayedOp;
				}));
			}
			// If it has been assigned in this realm (a user exists in this realm for this Federated Identity id), we log in with that user account into the requesting slot.			 
			else
			{
				// If this email is already in use we try to log in if asked to do so. Otherwise, we error out.				
				if (bAutoLoginOnUnavailable) LoginEmailAndPassword(UserSlot, Email, Password, Op);
				else GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, TEXT("EMAIL_IN_USE"));
			}
			return;
		}
		GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, Resp.ErrorData.message);
	});

	// If we are already authenticated (we had a saved user in this slot), we fail the sign up
	if (UserSlotSystem->IsUserSlotAuthenticated(UserSlot, this))
	{
		RequestTrackerSystem->TriggerOperationError(Op, TEXT("ALREADY_SIGNED_IN"));
		return;
	}

	// Kick off the process for sign up 
	const auto _ = CheckEmailAvailable(EncodedEmail, Op, CheckIdentityAvailableHandler);
}

void UBeamRuntime::Logout(FUserSlot UserSlot, EUserSlotClearedReason Reason, bool bRemoveLocalData, FBeamOperationHandle Op)
{
	FBeamRealmUser RealmUser;
	if (UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		// Configure us to wait until the slot is fully unauthenticated and then sign in.	 
		UserSlotClearedEnqueuedHandle = OnUserClearedCode.AddLambda([this, Op](FUserSlot UserSlot)
		{
			// Remove this lambda from the list of callbacks
			OnUserClearedCode.Remove(UserSlotClearedEnqueuedHandle);
			UserSlotClearedEnqueuedHandle = {};

			// Trigger the operation success
			RequestTrackerSystem->TriggerOperationSuccess(Op, UserSlot.Name);
		});
		UserSlotSystem->ClearUserAtSlot(UserSlot, Reason, bRemoveLocalData, this);
	}
	else
	{
		RequestTrackerSystem->TriggerOperationError(Op, TEXT("SLOT_NOT_LOGGED_IN"));
	}
}


void UBeamRuntime::OnAuthenticated(FAuthenticateFullResponse Resp, FUserSlot UserSlot, FBeamOperationHandle Op, FDelayedOperation BeforeUserNotifyOperation, FString MicroserviceId, FString FederationId,
                                   FString FederatedAuthToken)
{
	if (Resp.State == RS_Retrying) return;

	if (Resp.State == RS_Success)
	{
		// If the ChallengeToken is set that means the authentication is happening with a 2FA
		if (Resp.SuccessData->ChallengeToken.IsSet)
		{
			UBeamMultiFactorLoginData* ChallengeSolution = NewObject<UBeamMultiFactorLoginData>(GetTransientPackage());

			ChallengeSolution->MicroserviceId = MicroserviceId;
			ChallengeSolution->FederationId = FederationId;
			ChallengeSolution->FederatedUserAuthToken = FederatedAuthToken;
			ChallengeSolution->ChallengeToken = Resp.SuccessData->ChallengeToken.Val;
			ChallengeSolution->OperationHandler = Op;

			RequestTrackerSystem->TriggerOperationEventWithData(Op, OET_SUCCESS, GetOperationEventID_MultiFactorAuthTriggered(), TEXT("2FA_AUTH"), ChallengeSolution);
		}
		else
		{
			const UTokenResponse* Token = Resp.SuccessData;
			AuthenticateWithToken(UserSlot, Token, Op, BeforeUserNotifyOperation);
		}
	}
	else
	{
		UserSlotSystem->ClearUserAtSlot(UserSlot, USCR_FailedAuthentication, true, this);
		RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
	}
}

void UBeamRuntime::OnGetBeginTwoFactorResponse(FAuthenticateFullResponse Resp, FUserSlot UserSlot, FBeamOperationHandle Op)
{
	if (Resp.State == RS_Retrying) return;

	if (Resp.State == RS_Success)
	{
		UBeamMultiFactorLoginData* ChallengeSolution = NewObject<UBeamMultiFactorLoginData>(GetTransientPackage());
		if (ensureAlways(Resp.SuccessData->ChallengeToken.IsSet))
		{
			ChallengeSolution->ChallengeToken = Resp.SuccessData->ChallengeToken.Val;
		}

		RequestTrackerSystem->TriggerOperationSuccessWithData(Op, TEXT(""), ChallengeSolution);
		// Call the event on get begin two factor
	}
	else
	{
		UserSlotSystem->ClearUserAtSlot(UserSlot, USCR_FailedAuthentication, true, this);
		RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
	}
}

void UBeamRuntime::AuthenticateWithToken(FUserSlot UserSlot, const UTokenResponse* Token, FBeamOperationHandle Op, FDelayedOperation BeforeUserNotifyOperation)
{
	const FBeamCid Cid = GetDefault<UBeamCoreSettings>()->TargetRealm.Cid;
	const FBeamPid Pid = GetDefault<UBeamCoreSettings>()->TargetRealm.Pid;

	const FString AccessToken = Token->AccessToken.Val;
	const FString RefreshToken = Token->RefreshToken.Val;
	const int64 ExpiresIn = Token->ExpiresIn;

	UserSlotSystem->SetAuthenticationDataAtSlot(UserSlot, AccessToken, RefreshToken, FDateTime::UtcNow().ToUnixTimestamp(), ExpiresIn, Cid, Pid, this);

	// If I'm given a function that returns an Operation, run and wait for that operation before continuing this one.
	// We use this to provide much better semantics for SignUp with Email/Password or ThirdParty/Federated identities.
	// This is because the sign up/in operation will result in success only if the attachment is successful.
	// This also means that the [Post]UserSignIn and UserReady callbacks are only invoked after the attach/register stuff has ran.
	// This is a much better flow for PC/Console games where we can disable frictionless auth and instead call SignUpOrLoginWith_____.
	FBeamWaitHandle WaitHandle;
	const auto BeforeAuthSetupWaitHandler = FOnWaitCompleteCode::CreateLambda([this, UserSlot, Op](const FBeamWaitCompleteEvent& Evt)
	{
		// If any request here failed
		if (!RequestTrackerSystem->IsWaitSuccessful(Evt))
		{
			FString Errs;
			for (FBeamErrorResponse Error : Evt.Errors)
				Errs += FString::Printf(TEXT("%s, "), *Error.message);

			UE_LOG(LogBeamRuntime, Error, TEXT("Errors during Login Delayed Operation: %s"), *Errs)

			UserSlotSystem->ClearUserAtSlot(UserSlot, USCR_FailedAuthentication, true, this);
			RequestTrackerSystem->TriggerOperationError(Op, TEXT("FAILED_LOGIN_DELAYED_OPERATION"));
			return;
		}

		// Only run the auth setup if the operation above completed successfully.
		RunPostAuthenticationSetup(UserSlot, Op);
	});
	RequestTrackerSystem->InvokeAndWaitForHooks(WaitHandle, BeforeUserNotifyOperation, BeforeAuthSetupWaitHandler);
}

void UBeamRuntime::RunPostAuthenticationSetup(FUserSlot UserSlot, FBeamOperationHandle Op)
{
	// Makes a GetMe request to get the updated account data.
	FBeamRequestContext RequestContext;
	const UBeamAccountsApi* AccountSubsystem = GEngine->GetEngineSubsystem<UBeamAccountsApi>();
	const FOnBasicAccountsGetMeFullResponse GetMeHandler = FOnBasicAccountsGetMeFullResponse::CreateUObject(this, &UBeamRuntime::RunPostAuthenticationSetup_OnGetMe, UserSlot, Op);
	UBasicAccountsGetMeRequest* MeReq = UBasicAccountsGetMeRequest::Make(this, {});
	AccountSubsystem->CPP_GetMe(UserSlot, MeReq, GetMeHandler, RequestContext, Op, this);
}

void UBeamRuntime::RunPostAuthenticationSetup_OnGetMe(FBasicAccountsGetMeFullResponse Resp, FUserSlot UserSlot, FBeamOperationHandle Op)
{
	if (Resp.State == RS_Retrying) return;

	if (Resp.State == RS_Success)
	{
		const auto GamerTag = Resp.SuccessData->Id;
		const auto Email = Resp.SuccessData->Email;
		const auto ExternalIds = Resp.SuccessData->External;
		UserSlotSystem->SetGamerTagAtSlot(UserSlot, GamerTag, this);
		if (Email.IsSet) UserSlotSystem->SetEmailAtSlot(UserSlot, Email.Val, this);
		if (ExternalIds.IsSet) UserSlotSystem->SetExternalIdsAtSlot(UserSlot, ExternalIds.Val, this);

		FBeamRealmUser BeamRealmUser;
		if (UserSlotSystem->GetUserDataAtSlot(UserSlot, BeamRealmUser, this))
		{
			const FOnGetClientDefaultsFullResponse HandlerConfig = FOnGetClientDefaultsFullResponse::CreateUObject(this, &UBeamRuntime::RunPostAuthenticationSetup_PrepareNotificationService, UserSlot,
			                                                                                                       BeamRealmUser, Op);

			UGetClientDefaultsRequest* GetClientDefaultsReq = UGetClientDefaultsRequest::Make(this, {});
			FBeamRequestContext GetClientDefaultsCtx;
			GEngine->GetEngineSubsystem<UBeamRealmsApi>()->CPP_GetClientDefaults(GetClientDefaultsReq, HandlerConfig, GetClientDefaultsCtx, Op, this);
		}
		else
		{
			UserSlotSystem->ClearUserAtSlot(UserSlot, USCR_FailedAuthentication, true, this);
			RequestTrackerSystem->TriggerOperationError(Op, TEXT("Failed to find user data. This should never be seen."));
		}
	}
	else
	{
		UserSlotSystem->ClearUserAtSlot(UserSlot, USCR_FailedAuthentication, true, this);
		RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
	}
}

void UBeamRuntime::RunPostAuthenticationSetup_PrepareNotificationService(FGetClientDefaultsFullResponse Resp, FUserSlot UserSlot, FBeamRealmUser BeamRealmUser, FBeamOperationHandle Op)
{
	if (Resp.State == RS_Retrying) return;

	if (Resp.State == RS_Success)
	{
		EnsureConnectivityManagerForSlot(UserSlot);

		const auto Connectivity = ConnectivityState.FindRef(UserSlot);
		const auto ConnHandler = FOnNotificationEvent::CreateUObject(Connectivity, &UBeamConnectivityManager::ConnectionHandler, BeamRealmUser, Op);

		const FString Uri = Resp.SuccessData->WebsocketConfig->Uri.Val / TEXT("connect");
		UE_LOG(LogBeamRuntime, Verbose, TEXT("WebSocket URI=%s, Setting=%s"), *Resp.SuccessData->WebsocketConfig->Uri.Val, *Resp.SuccessData->WebsocketConfig->Provider)

		TMap<FString, FString> Headers;
		FillDefaultSessionHeaders(Headers);

		FBeamWebSocketHandle Handle;
		GEngine->GetEngineSubsystem<UBeamNotifications>()->Connect(UserSlot, BeamRealmUser, DefaultNotificationChannel, Uri, Headers, ConnHandler, Handle, this->GetWorld());
	}
	// If we failed the ClientDefaults request
	else if (Resp.State == RS_Error)
	{
		UserSlotSystem->ClearUserAtSlot(UserSlot, USCR_FailedAuthentication, true, this);
		RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
	}
}

void UBeamRuntime::LoadCachedUserAtSlot(FUserSlot UserSlot, FBeamOperationHandle AuthOp, FSimpleDelegate RunIfNoUser)
{
	// Try to load the user at a specific slot
	const int32 Result = UserSlotSystem->TryLoadSavedUserAtSlotAndAuth(UserSlot, this);
	if (Result != UBeamUserSlots::LoadSavedUserResult_Failed)
	{
		// If expired, let's make a request to get a new token through the auto-refresh for expired tokens and then trigger the auth.
		if (Result == UBeamUserSlots::LoadSavedUserResult_ExpiredToken)
		{
			const FOnBasicAccountsGetMeFullResponse Handler = FOnBasicAccountsGetMeFullResponse::CreateLambda([this, UserSlot, AuthOp](const FBasicAccountsGetMeFullResponse& Resp)
			{
				if (Resp.State == EBeamFullResponseState::RS_Success)
				{
					RunPostAuthenticationSetup(UserSlot, AuthOp);

					UE_LOG(LogBeamRuntime, Display, TEXT("Authenticated User at Slot! SLOT=%s GAMER TAG=%s"), *UserSlot.Name, *Resp.SuccessData->Id.AsString);
				}
				// If this request failed entirely (all retries)... 
				else if (Resp.State == EBeamFullResponseState::RS_Error)
				{
					RequestTrackerSystem->TriggerOperationError(AuthOp, Resp.ErrorData.message);
				}
			});

			const UBeamAccountsApi* AccountsApi = GEngine->GetEngineSubsystem<UBeamAccountsApi>();
			UBasicAccountsGetMeRequest* MeReq = UBasicAccountsGetMeRequest::Make(GetTransientPackage(), {});
			FBeamRequestContext Ctx;
			AccountsApi->CPP_GetMe(UserSlot, MeReq, Handler, Ctx, AuthOp, this);
			UE_LOG(LogBeamRuntime, Display, TEXT("User at Slot has an expired token. Refreshing the token. SLOT=%s"), *UserSlot.Name);
		}

		// If we loaded and the token wasn't expired. Let's continue the auth setup flow.
		if (Result == UBeamUserSlots::LoadSavedUserResult_Success)
		{
			RunPostAuthenticationSetup(UserSlot, AuthOp);
			UE_LOG(LogBeamRuntime, Display, TEXT("Authenticated User at Slot! SLOT=%s"), *UserSlot.Name);
		}
	}
	else
	{
		auto _ = RunIfNoUser.ExecuteIfBound();
	}
}

FBeamRequestContext UBeamRuntime::LoginGuest(FUserSlot UserSlot, FBeamOperationHandle Op, TMap<FString, FString> InitProperties, FDelayedOperation OnBeforePostAuthentication)
{
	const UBeamAuthApi* AuthSubsystem = GEngine->GetEngineSubsystem<UBeamAuthApi>();
	const FOnAuthenticateFullResponse AuthenticateHandler = FOnAuthenticateFullResponse::CreateUObject(this, &UBeamRuntime::OnAuthenticated, UserSlot, Op, OnBeforePostAuthentication, FString{}, FString{}, FString{});

	UAuthenticateRequest* Req = NewObject<UAuthenticateRequest>(GetTransientPackage());
	Req->Body = NewObject<UTokenRequestWrapper>(Req);
	Req->Body->GrantType = TEXT("guest");

	// Init the dictionary of init properties
	auto Props{InitProperties};
	FillDefaultSignUpInitProperties(Props);
	Req->Body->InitProperties = FOptionalMapOfString{Props};


	FBeamRequestContext RequestContext;
	AuthSubsystem->CPP_Authenticate(Req, AuthenticateHandler, RequestContext, Op, this);
	return RequestContext;
}

FBeamRequestContext UBeamRuntime::CheckFederatedIdentityAvailable(FString MicroserviceId, FString FederationId, FString FederatedUserId, FBeamOperationHandle Op, FOnGetAvailableExternalIdentityFullResponse Handler) const
{
	const auto AccountAPI = GEngine->GetEngineSubsystem<UBeamAccountsApi>();

	FBeamRequestContext Ctx;
	UGetAvailableExternalIdentityRequest* Req = UGetAvailableExternalIdentityRequest::Make(MicroserviceId, FederatedUserId, FOptionalString{FederationId}, GetTransientPackage(), {});
	AccountAPI->CPP_GetAvailableExternalIdentity(Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamRuntime::CheckEmailAvailable(FString Email, FBeamOperationHandle Op, FOnGetAvailableFullResponse Handler) const
{
	const auto AccountAPI = GEngine->GetEngineSubsystem<UBeamAccountsApi>();

	FBeamRequestContext Ctx;
	UGetAvailableRequest* Req = UGetAvailableRequest::Make(Email, GetTransientPackage(), {});
	AccountAPI->CPP_GetAvailable(Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamRuntime::AttachIdentityToUser(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedAuthToken, FBeamOperationHandle Op,
                                                       FOnPostExternalIdentityFullResponse Handler) const
{
	const auto AccountAPI = GEngine->GetEngineSubsystem<UBeamAccountsApi>();

	const auto Req = UPostExternalIdentityRequest::Make(MicroserviceId, FederatedAuthToken, {}, FOptionalString{FederationId}, GetTransientPackage(), {});
	FBeamRequestContext Ctx;
	AccountAPI->CPP_PostExternalIdentity(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamRuntime::AttachIdentityToUserTwoFactor(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedAuthToken,
                                                                UChallengeSolution* ChallengeSolution, FBeamOperationHandle Op, FOnPostExternalIdentityFullResponse Handler) const
{
	const auto AccountAPI = GEngine->GetEngineSubsystem<UBeamAccountsApi>();

	const auto Req = UPostExternalIdentityRequest::Make(MicroserviceId, FederatedAuthToken, FOptionalChallengeSolution(ChallengeSolution), FOptionalString{FederationId}, GetTransientPackage(), {});
	FBeamRequestContext Ctx;
	AccountAPI->CPP_PostExternalIdentity(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamRuntime::AttachEmailAndPasswordToUser(FUserSlot UserSlot, FString Email, FString Password, FBeamOperationHandle Op, FOnBasicAccountsPostRegisterFullResponse Handler) const
{
	const auto AccountAPI = GEngine->GetEngineSubsystem<UBeamAccountsApi>();

	const auto Req = UBasicAccountsPostRegisterRequest::Make(Email, Password, GetTransientPackage(), {});
	FBeamRequestContext Ctx;
	AccountAPI->CPP_PostRegister(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamRuntime::RemoveIdentityFromUser(FUserSlot UserSlot, FString MicroserviceId, FString FederationId, FString FederatedAuthToken, FBeamOperationHandle Op,
                                                         FOnDeleteExternalIdentityFullResponse Handler) const
{
	const auto AccountAPI = GEngine->GetEngineSubsystem<UBeamAccountsApi>();

	const auto Req = UDeleteExternalIdentityRequest::Make(MicroserviceId, FederatedAuthToken, FOptionalString{FederationId}, GetTransientPackage(), {});
	FBeamRequestContext Ctx;
	AccountAPI->CPP_DeleteExternalIdentity(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}


bool UBeamRuntime::GetDefaultNotificationChannel(const FUserSlot& UserSlot, FBeamWebSocketHandle& OutHandle) const
{
	if (DefaultNotificationChannels.Contains(UserSlot))
	{
		OutHandle = DefaultNotificationChannels.FindRef(UserSlot);
		return true;
	}

	return false;
}

void UBeamRuntime::FillDefaultSessionHeaders(TMap<FString, FString>& Headers)
{
	const FString Platform = UGameplayStatics::GetPlatformName();
	const FString Language = FPlatformMisc::GetDefaultLanguage();
	const FString Locale = FPlatformMisc::GetDefaultLocale();
	const FString Device = FPlatformMisc::GetLoginId();
	UE_LOG(LogBeamRuntime, Verbose, TEXT("PLATFORM = %s, LANGUAGE = %s, LOCALE = %s, DEVICE = %s"), *Platform, *Language, *Locale, *Device)

	Headers.Add(BEAM_SESSION_HEADER_PLATFORM, Platform);
	Headers.Add(BEAM_SESSION_HEADER_DEVICE, Device);
	Headers.Add(BEAM_SESSION_HEADER_SOURCE, TEXT(""));
	Headers.Add(BEAM_SESSION_HEADER_LOCALE, Locale);
	Headers.Add(BEAM_SESSION_HEADER_LANGUAGE, FString::Format(TEXT("{0},{1}"), {Locale, TEXT("ISO639")}));
}

void UBeamRuntime::EnsureConnectivityManagerForSlot(FUserSlot UserSlot)
{
	if (!ConnectivityState.Contains(UserSlot))
	{
		UBeamConnectivityManager* ConnectivityManager = NewObject<UBeamConnectivityManager>(this);
		ConnectivityManager->Runtime = this;
		ConnectivityManager->UserSlots = UserSlotSystem;
		ConnectivityManager->RequestTracker = RequestTrackerSystem;
		ConnectivityManager->Notifications = NotificationSystem;
		ConnectivityManager->UserSlot = UserSlot;
		ConnectivityManager->CurrentState = CONN_Offline;
		ConnectivityManager->CurrentConnectionLostTime = FDateTime::UtcNow();
		ConnectivityManager->ConnectionLostCountInSession = 0;
		ConnectivityState.Add(UserSlot, ConnectivityManager);
	}
}

void UBeamRuntime::SendAnalyticsEvent(const FString& EventOpCode, const FString& EventCategory, const FString& EventName, const TArray<TSharedRef<FJsonObject>>& EventParamsObj) const
{
	const auto Settings = GetDefault<UBeamCoreSettings>();
	SendAnalyticsEvent(Settings->GetOwnerPlayerSlot(), EventOpCode, EventCategory, EventName, EventParamsObj);
}

void UBeamRuntime::SendAnalyticsEvent(const FUserSlot& Slot, const FString& EventOpCode, const FString& EventCategory, const FString& EventName,
                                      const TArray<TSharedRef<FJsonObject>>& EventParamsObj) const
{
	// Create the request object
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

	// get UBeamRuntime		
	auto Slots = GEngine->GetEngineSubsystem<UBeamUserSlots>();
	auto Settings = GetDefault<UBeamCoreSettings>();

	FBeamRealmUser UserData;
	Slots->GetUserDataAtSlot(Slot, UserData, this);

	const auto AuthToken = UserData.AuthToken;

	const auto AuthTokenHeader = FString::Format(*UBeamBackend::HEADER_VALUE_AUTHORIZATION, {AuthToken.AccessToken});
	HttpRequest->SetHeader(UBeamBackend::HEADER_AUTHORIZATION, AuthTokenHeader);

	FString Url = FString::Format(
		TEXT("https://api.beamable.com/report/custom_batch/{0}/{1}/{2}"), {Settings->TargetRealm.Cid.AsString, Settings->TargetRealm.Pid.AsString, UserData.GamerTag.AsString});

	// Set the URL
	HttpRequest->SetURL(Url);

	// Set the verb to POST
	HttpRequest->SetVerb(TEXT("POST"));

	// Set the content type header
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	TArray<FString> EventJsons;

	// Build Json for events
	for (int i = 0; i < EventParamsObj.Num(); ++i)
	{
		TSharedPtr<FJsonObject> TopJsonObject = MakeShareable(new FJsonObject);

		TopJsonObject->SetStringField(TEXT("op"), EventOpCode);
		TopJsonObject->SetStringField(TEXT("c"), EventCategory);
		TopJsonObject->SetStringField(TEXT("e"), EventName);
		TopJsonObject->SetObjectField(TEXT("p"), EventParamsObj[i]);

		// Serialize the FJsonObject to a string
		FString AnalyticsEvent;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&AnalyticsEvent);
		if (FJsonSerializer::Serialize(TopJsonObject.ToSharedRef(), Writer))
		{
			EventJsons.Add(AnalyticsEvent);
		}
		else
		{
			UE_LOG(LogBeamRuntime, Warning, TEXT("Failed to serialize analytics event. OP=%s, CATEGORY=%s, EVENT=%s, PARAMS_IDX=%d"), *EventOpCode, *EventCategory, *EventName, i)
		}
	}

	// We only send this batch if all of them are working.
	if (EventJsons.Num())
	{
		const auto AnalyticsBatch = "[" + FString::Join(EventJsons, TEXT(", ")) + "]";

		// Convert FString to UTF-8
		FTCHARToUTF8 Converter(*AnalyticsBatch);
		// Create a TArray and fill it with the UTF-8 data
		TArray<uint8> ContentPayload;
		ContentPayload.Append(reinterpret_cast<const uint8*>(Converter.Get()), Converter.Length());

		// Note: Depending on your use case, you might want to append a null terminator to the array
		// MyUTF8Array.Add(0);

		// Set the request content
		HttpRequest->SetContent(ContentPayload);

		// Define the response callback
		HttpRequest->OnProcessRequestComplete().BindLambda([EventOpCode, EventCategory, EventName, AnalyticsBatch](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			if (bWasSuccessful && Response.IsValid())
			{
				UE_LOG(LogBeamRuntime, Verbose, TEXT("Analytics event successful. OP=%s, CATEGORY=%s, EVENT=%s, PARAMS=%s"), *EventOpCode, *EventCategory, *EventName, *AnalyticsBatch)
			}
			else
			{
				UE_LOG(LogBeamRuntime, Warning, TEXT("Analytics event request failed. OP=%s, CATEGORY=%s, EVENT=%s, PARAMS=%s"), *EventOpCode, *EventCategory, *EventName, *AnalyticsBatch)
			}
		});

		// Send the request
		HttpRequest->ProcessRequest();
	}
}


void UBeamRuntime::FillDefaultSignUpInitProperties(TMap<FString, FString>& InitProperties)
{
	InitProperties.Add(TEXT("__beam_game_project_version__"), GEngine->GetEngineSubsystem<UBeamBackend>()->GetProjectAppVersion());
	InitProperties.Add(TEXT("__beam_sdk_version__"), GetDefault<UBeamCoreSettings>()->BeamableEnvironment->Version.ToString());
	InitProperties.Add(TEXT("__beam_ue_engine_version__"), FEngineVersion::Current().ToString());
}
#undef LOCTEXT_NAMESPACE
