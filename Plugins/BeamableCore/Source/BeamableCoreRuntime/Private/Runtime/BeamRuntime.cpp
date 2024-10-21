// Fill out your copyright notice in the Description page of Project Settings.


#include "Runtime/BeamRuntime.h"

#include "HttpModule.h"

#include "BeamLogging.h"
#include "AutoGen/SubSystems/BeamRealmsApi.h"
#include "AutoGen/SubSystems/Realms/GetClientDefaultsRequest.h"
#include "BeamNotifications/BeamNotifications.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "Subsystems/Content/BeamContentSubsystem.h"


#if WITH_EDITOR
#include "Kismet/KismetSystemLibrary.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#endif

#define LOCTEXT_NAMESPACE "BeamRuntime"


void UBeamRuntime::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// We do some initialization for dedicated servers... 
	if (GetGameInstance()->IsDedicatedServerInstance())
	{
		// Let's just load up the target realm's PID from the follow hierarchy:
		//   - If we got an CLI Arg called --beamable-realm-override <Target Realm's PID>, use this argument.
		//   - If there's no CLI Arg, check for an environment variable called BEAMABLE_REALM_OVERRIDE and use that if it exists.
		//   - If there's no EnvVar, we'll use whatever was configured in "Config/DefaultEngine.ini" (which is edited by using the "Apply To Build" button).

		// We do this so game-makers can choose their preferred ways of setting up dedicated server builds and deployments.
		FString OverridenCustomer;
		if (!FParse::Value(FCommandLine::Get(), TEXT("beamable-customer-override"), OverridenCustomer))
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
		if (!FParse::Value(FCommandLine::Get(), TEXT("beamable-realm-override"), OverridenRealm))
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
		if (!FParse::Value(FCommandLine::Get(), TEXT("beamable-environment-override"), OverridenRealm))
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
	
	if (GetDefault<UBeamRuntimeSettings>()->bAutoInitializeSdkAtStartup)
	{
		ExecuteOnGameThread(TEXT("Initialize"), [this]()
		{
			this->TriggerInitializeWhenUnrealReady();
		});
		CurrentSdkState = ESDKState::Initializing;
	}

	UE_LOG(LogBeamRuntime, Verbose, TEXT("Initializing UBeamRuntime Subsystem!"));

	UBeamBackend* EngineSubsystem = GEngine->GetEngineSubsystem<UBeamBackend>();
	EngineSubsystem->UpdatePieState();
	if (EngineSubsystem->IsInPIE())
	{
		// When running as a dedicated server instance, swap out the execute request delegate
		const FName ExecuteRequestImpl = GET_FUNCTION_NAME_CHECKED(UBeamRuntime, PIEExecuteRequestImpl);

		EngineSubsystem->ExecuteRequestDelegate.BindUFunction(this, ExecuteRequestImpl);
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
}

void UBeamRuntime::InitSDK()
{
	if (CurrentSdkState == ESDKState::NotInitialized || CurrentSdkState == ESDKState::InitializationFailed)
	{
		ExecuteOnGameThread(TEXT("Initialize"), [this]()
		{
			this->TriggerInitializeWhenUnrealReady();
		});
		CurrentSdkState = ESDKState::Initializing;
	}
	else
	{
		UE_LOG(LogBeamRuntime, Warning, TEXT("Trying to call InitSDK while the SDK is already initialized"));
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

void UBeamRuntime::PIEExecuteRequestImpl(int64 ActiveRequestId, FBeamConnectivity& Connectivity)
{
	UBeamBackend* BeamBackend = GEngine->GetEngineSubsystem<UBeamBackend>();

	// TODO: We'll need to change the code-gen to be able to detect whether or not the request is actually coming from the PIE session.
	// TODO: Basically, we need to have one delegate for build and another for editor. And the Beam___API classes need to not care about this other than forwarding the calling context to a function of BeamBackend.
	// TODO: That function should decide which to use based on who is making the request ('Runtime' source PIE/Build or 'Editor' source).
	const TUnrealRequestPtr Req = BeamBackend->InFlightRequests.FindRef(ActiveRequestId);
	BeamBackend->InFlightPIERequests.Add(Req);

	GetGameInstance()->IsDedicatedServerInstance()
		? BeamBackend->DedicatedServerExecuteRequestImpl(ActiveRequestId, Connectivity)
		: BeamBackend->DefaultExecuteRequestImpl(ActiveRequestId, Connectivity);
}

// On Beamable Start Flow

void UBeamRuntime::TriggerInitializeWhenUnrealReady()
{
	const FBeamRealmHandle TargetRealm = GetDefault<UBeamCoreSettings>()->TargetRealm;
	const FString TargetAPIUrl = GEngine->GetEngineSubsystem<UBeamEnvironment>()->GetAPIUrl();

	// Initialize user ConnectivityState for each slot
	for (FString RuntimeUserSlot : GetDefault<UBeamCoreSettings>()->RuntimeUserSlots)
	{
		URuntimeConnectivityManager* ConnectivityManager = NewObject<URuntimeConnectivityManager>();
		ConnectivityManager->OwnerSlot = RuntimeUserSlot;
		ConnectivityManager->CurrentState = CONN_Offline;
		ConnectivityManager->CurrentConnectionLostTime = FDateTime::UtcNow();
		ConnectivityManager->ConnectionLostCountInSession = 0;
		ConnectivityManager->FixupOperationDAG = {};
		ConnectivityState.Add(RuntimeUserSlot, ConnectivityManager);
	}

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
	}
	else
	{
		UE_LOG(LogBeamRuntime, Warning, TEXT("Starting configured Target Realm: CID=%s, PID=%s, URL=%s!"), *TargetRealm.Cid.AsString, *TargetRealm.Pid.AsString, *TargetAPIUrl);

		UBeamRequestTracker* RequestTracker = RequestTrackerSystem;
		if (const UWorld* World = GetWorld())
		{
			if (const UGameInstance* GameInstance = World->GetGameInstance())
			{
				const TArray<UBeamRuntimeSubsystem*> Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();

				TArray<TSubclassOf<UBeamRuntimeSubsystem>> ManuallyInitializedSubsystems =
					GetDefault<UBeamRuntimeSettings>()->ManualyInitializedRuntimeSubsystems;
				TArray<UBeamRuntimeSubsystem*> AutomaticallyInitializedSubsystems;

				bool DependencyWarning = false;
				FString WarningMsg;
				//Search for subsystems that depend on subsystems that will be manually initialized and add them to the list of manually initialized subsystems
				for (auto &Subsystem : Subsystems)
				{
					if (!ManuallyInitializedSubsystems.Contains(Subsystem->GetClass()))
					{
						TArray<TSubclassOf<UBeamRuntimeSubsystem>> DependingSubsystems = Subsystem->GetDependingOnSubsystems();

						for (auto &DependingSubsystem : DependingSubsystems)
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
					UE_LOG(LogBeamRuntime, Warning, TEXT("%s"),*WarningMsg);
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

				const auto OnCompleteCode = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::TriggerOnBeamableStarting,AutomaticallyInitializedSubsystems);
				OnInitializeWhenUnrealReadyWait = RequestTracker->CPP_WaitAll({}, InitializeWhenUnrealReadyOps, {}, OnCompleteCode);
			}
		}
	}
}

void UBeamRuntime::TriggerOnBeamableStarting(FBeamWaitCompleteEvent Evt,
	TArray<UBeamRuntimeSubsystem*> AutomaticallyInitializedSubsystems)
{
	// Handle errors in operations we were waiting on...
	TArray<FString> Errors;
	if (RequestTrackerSystem->IsWaitFailed(Evt, Errors))
	{
		FString Err;
		for (const auto& Error : Errors) Err += Error + TEXT("\n");
		UE_LOG(LogBeamRuntime, Error, TEXT("%s"), *Err);

		CurrentSdkState = ESDKState::InitializationFailed;
		
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
		if (!FParse::Value(FCommandLine::Get(), TEXT("beamable-realm-secret"), RealmSecret))
		{
			RealmSecret = FPlatformMisc::GetEnvironmentVariable(TEXT("BEAMABLE_REALM_SECRET"));
			if (!GIsEditor)
			{
				checkf(!RealmSecret.IsEmpty(), TEXT("To run a dedicated server that communicates with Beamable, either:\n"
					       "- Start it with the command line \'-beamable-realm-secret <realm_secret>\'\n"
					       "- Start it in an environment with the EnvVar \'BEAMABLE_REALM_SECRET\' set to your realm secret.\n"
					       "To find your realm secret for your realms, look into your Project Settings => Editor => Beamable Editor => PerSlotDeveloperProjectData => All Realms\n"
					       "Remember to set this command line argument in your Networking settings for playmode in Editor Settings => Level Editor => Play => Multiplayer Options => Server => Additional Server Launch Parameters."
				       ))
			}
		}
		GEngine->GetEngineSubsystem<UBeamBackend>()->RealmSecret = RealmSecret;
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
			const auto OnCompleteCode = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::TriggerOnContentReady,AutomaticallyInitializedSubsystems);
			OnBeamableStartingWait = RequestTrackerSystem->CPP_WaitAll({}, OnBeamableStartingOps, {}, OnCompleteCode);
		}
	}
}

void UBeamRuntime::TriggerOnContentReady(FBeamWaitCompleteEvent Evt,
	TArray<UBeamRuntimeSubsystem*> AutomaticallyInitializedSubsystems)
{
	// Handle errors in operations we were waiting on...
	TArray<FString> Errors;
	if (RequestTrackerSystem->IsWaitFailed(Evt, Errors))
	{
		FString Err;
		for (const auto& Error : Errors) Err += Error + TEXT("\n");
		UE_LOG(LogBeamRuntime, Error, TEXT("%s"), *Err);

		CurrentSdkState = ESDKState::InitializationFailed;
		
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

			const auto OnCompleteCode = FOnWaitCompleteCode::CreateUObject(this,
				&UBeamRuntime::TriggerOnStartedAndFrictionlessAuth,AutomaticallyInitializedSubsystems);
			OnBeamableContentReadyWait = RequestTrackerSystem->CPP_WaitAll({}, OnBeamableStartingOps, {}, OnCompleteCode);
		}
	}
}

void UBeamRuntime::TriggerOnStartedAndFrictionlessAuth(FBeamWaitCompleteEvent Evt,
			TArray<UBeamRuntimeSubsystem*> AutomaticallyInitializedSubsystems)
{
	// Handle errors in operations we were waiting on...
	TArray<FString> Errors;
	if (RequestTrackerSystem->IsWaitFailed(Evt, Errors))
	{
		FString Err;
		for (const auto& Error : Errors) Err += Error + TEXT("\n");
		UE_LOG(LogBeamRuntime, Error, TEXT("%s"), *Err);

		CurrentSdkState = ESDKState::InitializationFailed;
		// Early out and don't initialize if errors happen here.
		return;
	}
	for (auto& Subsystem : AutomaticallyInitializedSubsystems)
	{
		Subsystem->CurrentState = ESubsystemState::InitializedNoUserData;
	}
	// Everything is fine so let's continue initializing Beamable by firing off the OnStarted callback.
	OnStartedCode.Broadcast();
	OnStarted.Broadcast();
	CurrentSdkState = ESDKState::Initialized;

	// For servers, don't try to authenticate.
	if (const bool bIsDedicatedServer = GetGameInstance()->IsDedicatedServerInstance())
	{
	}
	// Sign in automatically to the owner player slot (if configured to do so).
	else if (GetDefault<UBeamCoreSettings>()->bAutomaticFrictionlessAuthForOwnerPlayer)
	{
		FrictionlessLoginIntoSlot(GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot(), AutomaticallyInitializedSubsystems);
	}
}

// On Beamable Ready / OnUserReady flow

void UBeamRuntime::TriggerOnUserSlotAuthenticated(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context)
{
	if (!Context || (Context && (Context->GetWorld() != GetWorld()))) return;

	const auto RequestTracker = RequestTrackerSystem;

	if (!OnUserSignedInOps.Contains(UserSlot))
		OnUserSignedInOps.Add(UserSlot, {});

	if (!OnUserSignedInWaits.Contains(UserSlot))
		OnUserSignedInWaits.Add(UserSlot, {});

	auto& SignedInOps = *OnUserSignedInOps.Find(UserSlot);
	auto& SignedInOpsWait = *OnUserSignedInWaits.Find(UserSlot);

	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			const TArray<UBeamRuntimeSubsystem*> Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();

			TArray<TSubclassOf<UBeamRuntimeSubsystem>> ManuallyInitializedSubsystems =
				GetDefault<UBeamRuntimeSettings>()->ManualyInitializedRuntimeSubsystems;

			TArray<UBeamRuntimeSubsystem*> AutomaticallyInitializedSubsystems;
			
			//Search for subsystems that depend on subsystems that will be manually initialized and add them to the list of manually initialized subsystems
			for (auto &Subsystem : Subsystems)
			{
				if (!ManuallyInitializedSubsystems.Contains(Subsystem->GetClass()))
				{
					TArray<TSubclassOf<UBeamRuntimeSubsystem>> DependingSubsystems = Subsystem->GetDependingOnSubsystems();

					for (auto &DependingSubsystem : DependingSubsystems)
					{
						if (ManuallyInitializedSubsystems.Contains(DependingSubsystem) && !GetRequiredSubsystems().Contains(DependingSubsystem) )
						{
							ManuallyInitializedSubsystems.AddUnique(Subsystem->GetClass());
						}
					}
				}
			}
			SignedInOps.Reset(Subsystems.Num() - ManuallyInitializedSubsystems.Num());
			
			for (auto& Subsystem : Subsystems)
			{
				if (!ManuallyInitializedSubsystems.Contains(Subsystem->GetClass())
					|| GetRequiredSubsystems().Contains(Subsystem->GetClass()))
				{
					FBeamOperationHandle Handle;
					Subsystem->OnUserSignedIn(UserSlot, BeamRealmUser, GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot().Equals(UserSlot), Handle);
					SignedInOps.Add(Handle);
					AutomaticallyInitializedSubsystems.Add(Subsystem);
				}
			}
			const auto SignedInOpsHandler = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::TriggerSubsystemPostUserSignIn, UserSlot, BeamRealmUser,AutomaticallyInitializedSubsystems);
			SignedInOpsWait = RequestTracker->CPP_WaitAll({}, SignedInOps, {}, SignedInOpsHandler);
		}
	}
}


void UBeamRuntime::TriggerSubsystemPostUserSignIn(FBeamWaitCompleteEvent Evt, FUserSlot UserSlot, FBeamRealmUser BeamRealmUser,
	TArray<UBeamRuntimeSubsystem*> AutomaticallyInitializedSubsystems)
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

	// Everything went well so let's continue with this user's initialization process
	if (!OnPostUserSignedInOps.Contains(UserSlot))
		OnPostUserSignedInOps.Add(UserSlot, {});

	if (!OnPostUserSignedInWaits.Contains(UserSlot))
		OnPostUserSignedInWaits.Add(UserSlot, {});

	FBeamWaitHandle& SignedInOpsWait = *OnPostUserSignedInWaits.Find(UserSlot);
	TArray<FBeamOperationHandle>& SignedInOps = *OnPostUserSignedInOps.Find(UserSlot);

	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			
			for (auto& Subsystem : AutomaticallyInitializedSubsystems)
			{
				FBeamOperationHandle Handle;
				Subsystem->OnPostUserSignedIn(UserSlot, BeamRealmUser, GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot().Equals(UserSlot), Handle);
				SignedInOps.Add(Handle);
			}

			const auto SignedInOpsHandler = FOnWaitCompleteCode::CreateLambda([this, UserSlot,AutomaticallyInitializedSubsystems](const FBeamWaitCompleteEvent& PostEvt)
			{x
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
				for (auto& Subsystem : AutomaticallyInitializedSubsystems)
				{
					Subsystem->CurrentState = ESubsystemState::InitializedWithUserData;
				}
				// By default, only UserSlot at index 0 of RuntimeUserSlots always gets loaded.
				// This actually only be called ONCE during the entire lifecycle of your program.
				if (!bDidFirstAuthRun && UserSlot.Name.Equals(GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot()))
				{
					OnReadyCode.Broadcast();
					OnReady.Broadcast();
					bDidFirstAuthRun = true;
				}

				OnUserReadyCode.Broadcast(UserSlot);
				OnUserReady.Broadcast(UserSlot);
			});
			SignedInOpsWait = RequestTrackerSystem->CPP_WaitAll({}, SignedInOps, {}, SignedInOpsHandler);
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
	
	ManuallyInitializeSubsystem(SubsystemsTypesToInitialize,false,Handle);
	return Handle;
}
FBeamOperationHandle UBeamRuntime::CPP_ManuallyInitializeSubsystemOperation(FUserSlot UserSlot,
	TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsTypesToInitialize,
		FBeamOperationEventHandlerCode OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot},
GetClass()->GetFName().ToString(), OnOperationEvent);
	
	ManuallyInitializeSubsystem(SubsystemsTypesToInitialize,false,Handle);
	return Handle;
}
FBeamOperationHandle UBeamRuntime::ManuallyInitializeSubsystemOperationWithUserData(FUserSlot UserSlot,
		TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsTypesToInitialize,
		FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot},
		GetClass()->GetFName().ToString(), OnOperationEvent);
	
	ManuallyInitializeSubsystem(SubsystemsTypesToInitialize,true,Handle);
	return Handle;
}
FBeamOperationHandle UBeamRuntime::CPP_ManuallyInitializeSubsystemOperationWithUserData(FUserSlot UserSlot,
	TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsTypesToInitialize,
		FBeamOperationEventHandlerCode OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot},
GetClass()->GetFName().ToString(), OnOperationEvent);
	
	ManuallyInitializeSubsystem(SubsystemsTypesToInitialize,true,Handle);
	return Handle;
}


void UBeamRuntime::ManuallyInitializeSubsystem(TArray<TSubclassOf<UBeamRuntimeSubsystem>>& SubsystemsTypesToInitialize,
		bool bInitializeUsers,FBeamOperationHandle OnOperationEvent)
{
	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			const auto AllSubsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();

			bool DependencyError= false;
			FString ErrorMessage;
			//Check subsystems  dependency before proceeding with initialization
			for (auto& SubsystemType : SubsystemsTypesToInitialize)
			{
				UBeamRuntimeSubsystem* Subsystem = Cast<UBeamRuntimeSubsystem>(GameInstance->GetSubsystemBase(SubsystemType));

				TArray<TSubclassOf<UBeamRuntimeSubsystem>> DependingSubsystemsTypes = Subsystem->GetDependingOnSubsystems();
				
				for (auto& SingleDependingSubsystemType : DependingSubsystemsTypes)
				{
					
					if (!SubsystemsTypesToInitialize.Contains(SingleDependingSubsystemType))
					{
						UBeamRuntimeSubsystem* DependingSubsystem = Cast<UBeamRuntimeSubsystem>(GameInstance->GetSubsystemBase(SingleDependingSubsystemType));

						/*if the subsystem we are trying to initialize has dependency on another subsystem that is not going
						to be initialized in this call, print an error */

						if (DependingSubsystem->CurrentState != ESubsystemState::InitializedWithUserData)
						{
							DependencyError = true;

							ErrorMessage +=  "Subsystem " + SubsystemType->GetName() + "is trying to be initialized without its dependency: " + DependingSubsystem->GetName() + "\n";
						}
					}
				}
			}
			ensureAlwaysMsgf(!DependencyError,TEXT("%s"),*ErrorMessage);
			
			if (CurrentSdkState == ESDKState::Initialized)
			{
				TArray<FBeamOperationHandle> ManualInitializeWhenUnrealReadyOps;
				ManualInitializeWhenUnrealReadyOps.Reset(SubsystemsTypesToInitialize.Num());
				
				for (auto& SubsystemType : SubsystemsTypesToInitialize)
				{
					UBeamRuntimeSubsystem* Subsystem = Cast<UBeamRuntimeSubsystem>(GameInstance->GetSubsystemBase(SubsystemType));

					if (Subsystem)
					{
						FBeamOperationHandle Handle;
						Subsystem->InitializeWhenUnrealReady(Handle);
						ManualInitializeWhenUnrealReadyOps.Add(Handle);

					}
				}
							
				const auto RequestTracker = RequestTrackerSystem;
				const auto OnCompleteCode = FOnWaitCompleteCode::CreateUObject(this,
					&UBeamRuntime::TriggerManuallySetSubsystemStarted,SubsystemsTypesToInitialize,bInitializeUsers,OnOperationEvent);
				RequestTracker->CPP_WaitAll({}, ManualInitializeWhenUnrealReadyOps, {}, OnCompleteCode);
			}
			else
			{
				UE_LOG(LogBeamRuntime, Error,	TEXT("Attempting to manually initialize subsystem while the sdk is not initialized"));
				RequestTrackerSystem->TriggerOperationError(OnOperationEvent, TEXT("Beamable SDK Not Initalized"));
			}
		}
	}
}
void UBeamRuntime::TriggerManuallySetSubsystemStarted(FBeamWaitCompleteEvent Evt,
	TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsTypesToInitialize,bool bInitializeUsers
	,FBeamOperationHandle OnOperationEvent)
{
	TArray<FString> Errors;
	if (RequestTrackerSystem->IsWaitFailed(Evt, Errors))
	{
		FString Err;
		for (const auto& Error : Errors) Err += Error + TEXT("\n");
		UE_LOG(LogBeamRuntime, Error, TEXT("%s"), *Err);

		RequestTrackerSystem->TriggerOperationError(OnOperationEvent, *Err);
		
		// Early out and don't initialize if errors happen here.;
		return;
	}
	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			TArray<FBeamOperationHandle> ManualInitializeWhenSubsystemsStartedOps;
			ManualInitializeWhenSubsystemsStartedOps.Reset(SubsystemsTypesToInitialize.Num());
					
			for (auto& SubsystemType : SubsystemsTypesToInitialize)
			{
				UBeamRuntimeSubsystem* Subsystem = Cast<UBeamRuntimeSubsystem>(GameInstance->GetSubsystemBase(SubsystemType));
				
				FBeamOperationHandle Handle;
				Subsystem->OnBeamableStarting(Handle);
				ManualInitializeWhenSubsystemsStartedOps.Add(Handle);
				
			}

			const auto RequestTracker = RequestTrackerSystem;
			const auto OnCompleteCode = FOnWaitCompleteCode::CreateUObject(this,
			&UBeamRuntime::TriggerManuallySetSubsystemContentReady,SubsystemsTypesToInitialize,bInitializeUsers,OnOperationEvent);
			RequestTracker->CPP_WaitAll({}, ManualInitializeWhenSubsystemsStartedOps, {}, OnCompleteCode);
		}
	}
}
void UBeamRuntime::TriggerManuallySetSubsystemContentReady(FBeamWaitCompleteEvent Evt,
	TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsTypesToInitialize,bool bInitializeUsers
	,FBeamOperationHandle OnOperationEvent)
{
	TArray<FString> Errors;
	if (RequestTrackerSystem->IsWaitFailed(Evt, Errors))
	{
		FString Err;
		for (const auto& Error : Errors) Err += Error + TEXT("\n");
		UE_LOG(LogBeamRuntime, Error, TEXT("%s"), *Err);

		RequestTrackerSystem->TriggerOperationError(OnOperationEvent, *Err);
		
		// Early out and don't initialize if errors happen here.
		return;
	}
	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			TArray<FBeamOperationHandle> ManualInitializeWhenContentReadyOps;
			ManualInitializeWhenContentReadyOps.Reset(SubsystemsTypesToInitialize.Num());
					
			for (auto& SubsystemType : SubsystemsTypesToInitialize)
			{
				UBeamRuntimeSubsystem* Subsystem = Cast<UBeamRuntimeSubsystem>(GameInstance->GetSubsystemBase(SubsystemType));
				
				FBeamOperationHandle Handle;
				Subsystem->OnBeamableContentReady(Handle);
				ManualInitializeWhenContentReadyOps.Add(Handle);
			}

			const auto RequestTracker = RequestTrackerSystem;
			const auto OnCompleteCode = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::TriggerManuallySetSubsystemsUserReady,
			SubsystemsTypesToInitialize,bInitializeUsers,OnOperationEvent);
				
			RequestTracker->CPP_WaitAll({}, ManualInitializeWhenContentReadyOps, {}, OnCompleteCode);
		}
	}
}
void UBeamRuntime::TriggerManuallySetSubsystemsUserReady(FBeamWaitCompleteEvent Evt,
	TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsTypesToInitialize,bool bInitializeUsers
	,FBeamOperationHandle OnOperationEvent)
{

	TArray<FString> Errors;
	if (RequestTrackerSystem->IsWaitFailed(Evt, Errors))
	{
		FString Err;
		for (const auto& Error : Errors) Err += Error + TEXT("\n");
		UE_LOG(LogBeamRuntime, Error, TEXT("%s"), *Err);

		RequestTrackerSystem->TriggerOperationError(OnOperationEvent, *Err);

		// Early out and don't initialize if errors happen here.
		return;
	}
	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			for (auto& SubsystemType : SubsystemsTypesToInitialize)
			{
				UBeamRuntimeSubsystem* Subsystem = Cast<UBeamRuntimeSubsystem>(GameInstance->GetSubsystemBase(SubsystemType));

				Subsystem->CurrentState = ESubsystemState::InitializedNoUserData;
			}
		}
	}
	if (!bInitializeUsers)
	{
		RequestTrackerSystem->TriggerOperationSuccess(OnOperationEvent,TEXT(""));
		return;
	}
	else
	{
		RequestTrackerSystem->TriggerOperationEvent(OnOperationEvent,EBeamOperationEventType::OET_SUCCESS,
			GetManualSubsystemsStartedEventID(),"");
	}
	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			TArray<FBeamOperationHandle> ManualInitializeOnUserReadyOps;
			ManualInitializeOnUserReadyOps.Reset(SubsystemsTypesToInitialize.Num());
					
			for (auto& SubsystemType : SubsystemsTypesToInitialize)
			{
				UBeamRuntimeSubsystem* Subsystem = Cast<UBeamRuntimeSubsystem>(GameInstance->GetSubsystemBase(SubsystemType));
				
				for (auto UserSlot : GetDefault<UBeamCoreSettings>()->RuntimeUserSlots)
				{
					FBeamRealmUser UserData;
					if (UserSlotSystem->GetUserDataAtSlot(UserSlot, UserData, this))
					{
						FBeamOperationHandle Handle;
						Subsystem->OnUserSignedIn(UserSlot,UserData,GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot().Equals(UserSlot), Handle);
						ManualInitializeOnUserReadyOps.Add(Handle);
					}
				}
				
			}
			
			const auto RequestTracker = RequestTrackerSystem;
			const auto OnCompleteCode = FOnWaitCompleteCode::CreateUObject(this,
				&UBeamRuntime::TriggerManuallySubsystemsPostUserSignIn,SubsystemsTypesToInitialize,OnOperationEvent);
			RequestTracker->CPP_WaitAll({}, ManualInitializeOnUserReadyOps, {}, OnCompleteCode);
		}
	}
}

void UBeamRuntime::TriggerManuallySubsystemsPostUserSignIn(FBeamWaitCompleteEvent Evt, 
	TArray<TSubclassOf<UBeamRuntimeSubsystem>> SubsystemsTypesToInitialize,
	FBeamOperationHandle OnOperationEvent)
{
	TArray<FString> Errors;
	if (RequestTrackerSystem->IsWaitFailed(Evt, Errors))
	{
		FString Err;
		for (const auto& Error : Errors) Err += Error + TEXT("\n");
		UE_LOG(LogBeamRuntime, Error, TEXT("%s"), *Err);

		RequestTrackerSystem->TriggerOperationError(OnOperationEvent, *Err);
		
		// Early out and don't initialize if errors happen here.
		return;
	}
	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			//this lambda will be called after post user sign in is called on all subsystems
			const auto SignedInOpsHandler = FOnWaitCompleteCode::CreateLambda([this,OnOperationEvent,SubsystemsTypesToInitialize](const FBeamWaitCompleteEvent& PostEvt)
			{
				// Handle errors in operations we were waiting on...
				TArray<FString> Errors;
				if (RequestTrackerSystem->IsWaitFailed(PostEvt, Errors))
				{
					FString Err;
					for (const auto& Error : Errors) Err += Error + TEXT("\n");
					UE_LOG(LogBeamRuntime, Error, TEXT("%s"), *Err);

					RequestTrackerSystem->TriggerOperationError(OnOperationEvent, *Err);
					
					// Early out and don't initialize if errors happen here.
					return;
				}
				if (const UWorld* World = GetWorld())
				{
					if (const UGameInstance* GameInstance = World->GetGameInstance())
					{
						for (auto& SubsystemType : SubsystemsTypesToInitialize)
						{
							UBeamRuntimeSubsystem* Subsystem = Cast<UBeamRuntimeSubsystem>(GameInstance->GetSubsystemBase(SubsystemType));

							Subsystem->CurrentState = ESubsystemState::InitializedWithUserData;
						}
					}
				}
				RequestTrackerSystem->TriggerOperationSuccess(OnOperationEvent, TEXT(""));
			});
			
			TArray<FBeamOperationHandle> ManualInitializePostUserSignInOps;
			ManualInitializePostUserSignInOps.Reset(SubsystemsTypesToInitialize.Num());
					
			for (auto& SubsystemType : SubsystemsTypesToInitialize)
			{
				UBeamRuntimeSubsystem* Subsystem = Cast<UBeamRuntimeSubsystem>(GameInstance->GetSubsystemBase(SubsystemType));
				
				for (auto UserSlot : GetDefault<UBeamCoreSettings>()->RuntimeUserSlots)
				{
					FBeamRealmUser UserData;
					if (UserSlotSystem->GetUserDataAtSlot(UserSlot, UserData, this))
					{
						FBeamOperationHandle Handle;
						Subsystem->OnPostUserSignedIn(UserSlot,UserData,GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot().Equals(UserSlot), Handle);
						ManualInitializePostUserSignInOps.Add(Handle);
					}
				}
			}
			
			const auto RequestTracker = RequestTrackerSystem;
			RequestTracker->CPP_WaitAll({}, ManualInitializePostUserSignInOps, {}, SignedInOpsHandler);
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

	// Let BeamRuntimeSubsystems run their callbacks
	UBeamRequestTracker* RequestTracker = RequestTrackerSystem;
	if (!OnUserSignedOutOps.Contains(UserSlot))
		OnUserSignedOutOps.Add(UserSlot, {});

	if (!OnUserSignedOutWaits.Contains(UserSlot))
		OnUserSignedOutWaits.Add(UserSlot, {});

	FBeamWaitHandle& SignedOutOpsWait = *OnUserSignedOutWaits.Find(UserSlot);
	TArray<FBeamOperationHandle>& SignedOutOps = *OnUserSignedOutOps.Find(UserSlot);

	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			const TArray<UBeamRuntimeSubsystem*> Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();

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

	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			const TArray<UBeamRuntimeSubsystem*> Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();

			SignedOutOps.Reset(Subsystems.Num());
			for (auto& Subsystem : Subsystems)
			{
				FBeamOperationHandle Handle;
				Subsystem->OnPostUserSignedOut(UserSlot, Reason, BeamRealmUser, Handle);
				SignedOutOps.Add(Handle);
			}

			const auto SignedOutOpsHandler = FOnWaitCompleteCode::CreateLambda([this, UserSlot](const FBeamWaitCompleteEvent& PostEvt)
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

				OnUserClearedCode.Broadcast(UserSlot);
				OnUserCleared.Broadcast(UserSlot);
			});
			SignedOutOpsWait = RequestTrackerSystem->CPP_WaitAll({}, SignedOutOps, {}, SignedOutOpsHandler);
		}
	}
}


// Login/Signup/Attach Operations

FBeamOperationHandle UBeamRuntime::LoginFrictionlessOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	LoginFrictionless(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_LoginFrictionlessOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	LoginFrictionless(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::LoginExternalIdentityOperation(FUserSlot UserSlot, FString ExternalService, FString ExternalNamespace, FString ExternalToken,
                                                                  FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	LoginExternalIdentity(UserSlot, ExternalService, ExternalNamespace, ExternalToken, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_LoginExternalIdentityOperation(FUserSlot UserSlot, FString ExternalService, FString ExternalNamespace, FString ExternalToken,
                                                                      FBeamOperationEventHandlerCode OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	LoginExternalIdentity(UserSlot, ExternalService, ExternalNamespace, ExternalToken, Handle);
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


FBeamOperationHandle UBeamRuntime::AttachExternalIdentityOperation(FUserSlot UserSlot, FString MicroserviceName, FString IdentityNamespace, FString IdentityUserId, FString IdentityAuthToken,
                                                                   FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	AttachExternalIdentity(UserSlot, MicroserviceName, IdentityNamespace, IdentityUserId, IdentityAuthToken, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_AttachExternalIdentityOperation(FUserSlot UserSlot, FString MicroserviceName, FString IdentityNamespace, FString IdentityUserId, FString IdentityAuthToken,
                                                                       FBeamOperationEventHandlerCode OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	AttachExternalIdentity(UserSlot, MicroserviceName, IdentityNamespace, IdentityUserId, IdentityAuthToken, Handle);
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

FBeamOperationHandle UBeamRuntime::SignUpExternalIdentityOperation(FUserSlot UserSlot, FString MicroserviceName, FString IdentityNamespace, FString IdentityUserId, FString IdentityAuthToken,
                                                                   FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	SignUpExternalIdentity(UserSlot, MicroserviceName, IdentityNamespace, IdentityUserId, IdentityAuthToken, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_SignUpExternalIdentityOperation(FUserSlot UserSlot, FString MicroserviceName, FString IdentityNamespace, FString IdentityUserId, FString IdentityAuthToken,
                                                                       FBeamOperationEventHandlerCode OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	SignUpExternalIdentity(UserSlot, MicroserviceName, IdentityNamespace, IdentityUserId, IdentityAuthToken, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::SignUpEmailAndPasswordOperation(FUserSlot UserSlot, FString Email, FString Password, FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	SignUpEmailAndPassword(UserSlot, Email, Password, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_SignUpEmailAndPasswordOperation(FUserSlot UserSlot, FString Email, FString Password, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	SignUpEmailAndPassword(UserSlot, Email, Password, Handle);
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


void UBeamRuntime::FrictionlessLoginIntoSlot(const FUserSlot& UserSlot,
			TArray<UBeamRuntimeSubsystem*> AutomaticallyInitializedSubsystems)
{
	/**
	 * If runs the FrictionlessAuthentication flow for the given user slot. You can make this call whenever you want to create a new user into a new slot.
	 * Passing nothing, will sign into the OwnerPlayerSlot. If the given slot is already authenticated, this is a no-op.
	 */

	// No-Op if we are already authed at this slot.
	if (UserSlotSystem->IsUserSlotAuthenticated(UserSlot, this)) return;

	// Create the OperationHandle for the FrictionlessAuth operation
	// This will handle errors by clearing up the data for the slot being signed into into and triggering the FailedUserAuth callback of all BeamRuntimeSubsystems.
	const FBeamOperationEventHandlerCode AuthOpHandler = FBeamOperationEventHandlerCode::CreateLambda([this, UserSlot,AutomaticallyInitializedSubsystems](FBeamOperationEvent Evt)
	{
		// If any errors occur during this process, 
		if (Evt.EventType == OET_ERROR)
		{
			// Make sure any partial state for the user slot is cleared (this is necessary since authentication is a multi-step process)
			UserSlotSystem->ClearUserAtSlot(UserSlot, USCR_FailedAuthentication);

			// TODO: Set offline mode for this user slot.						

			// Call OnUserFailedFrictionlessAuth on all RuntimeSubsystems
			if (const UWorld* World = GetWorld())
			{
				if (const UGameInstance* GameInstance = World->GetGameInstance())
				{
					for (auto& Subsystem : AutomaticallyInitializedSubsystems)
					{
						Subsystem->OnFailedUserAuth(UserSlot);
					}
				}
			}
			this->OnFailedUserAuth.Broadcast();
		}
	});
	FBeamOperationHandle AuthOp = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetName(), AuthOpHandler);

	// Try to load the user at a specific slot
	const int32 Result = UserSlotSystem->TryLoadSavedUserAtSlot(UserSlot, this);
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
					UE_LOG(LogBeamRuntime, Display, TEXT("Authenticated User at Slot! SLOT=%s"), *UserSlot.Name);
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
		LoginFrictionless(UserSlot, AuthOp);
	}
}


void UBeamRuntime::LoginFrictionless(FUserSlot UserSlot, FBeamOperationHandle Op)
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
		LoginGuest(UserSlot, Op);
	}
}

void UBeamRuntime::LoginExternalIdentity(FUserSlot UserSlot, FString ExternalService, FString ExternalNamespace, FString ExternalToken, FBeamOperationHandle Op)
{
	UAuthenticateRequest* Req = NewObject<UAuthenticateRequest>(GetTransientPackage());
	Req->Body = NewObject<UTokenRequestWrapper>(Req);
	Req->Body->GrantType = TEXT("external");
	Req->Body->ExternalToken = FOptionalString{ExternalToken};
	Req->Body->ProviderService = FOptionalString{ExternalService};
	Req->Body->ProviderNamespace = FOptionalString{ExternalNamespace};

	const UBeamAuthApi* AuthSubsystem = GEngine->GetEngineSubsystem<UBeamAuthApi>();

	// If we are already authenticated (we had a saved user in this slot), we sign out of the user at that slot, wait for all runtime systems to clean up the user and then sign back into the given user.
	FBeamRealmUser RealmUser;
	if (UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		// Configure us to wait until the slot is fully unauthenticated and then sign in.
		OnUserClearedCode.AddLambda([this, AuthSubsystem](FUserSlot UserSlot, FBeamOperationHandle OpHandle, UAuthenticateRequest* AuthReq)
		{
			const auto AuthenticateHandler = FOnAuthenticateFullResponse::CreateUObject(this, &UBeamRuntime::OnAuthenticated, UserSlot, OpHandle, FDelayedOperation{});
			FBeamRequestContext RequestContext;
			AuthSubsystem->CPP_Authenticate(AuthReq, AuthenticateHandler, RequestContext, OpHandle);
		}, Op, Req);
		UserSlotSystem->ClearUserAtSlot(UserSlot, USCR_Manual, true, this);
	}
	else
	{
		const auto AuthenticateHandler = FOnAuthenticateFullResponse::CreateUObject(this, &UBeamRuntime::OnAuthenticated, UserSlot, Op, FDelayedOperation{});
		FBeamRequestContext RequestContext;
		AuthSubsystem->CPP_Authenticate(Req, AuthenticateHandler, RequestContext, Op);
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
		OnUserClearedCode.AddLambda([this, AuthSubsystem](FUserSlot UserSlot, FBeamOperationHandle OpHandle, UAuthenticateRequest* AuthReq)
		{
			const auto AuthenticateHandler = FOnAuthenticateFullResponse::CreateUObject(this, &UBeamRuntime::OnAuthenticated, UserSlot, OpHandle, FDelayedOperation{});
			FBeamRequestContext RequestContext;
			AuthSubsystem->CPP_Authenticate(AuthReq, AuthenticateHandler, RequestContext, OpHandle);
		}, Op, Req);
		UserSlotSystem->ClearUserAtSlot(UserSlot, USCR_Manual, true, this);
	}
	else
	{
		const auto AuthenticateHandler = FOnAuthenticateFullResponse::CreateUObject(this, &UBeamRuntime::OnAuthenticated, UserSlot, Op, FDelayedOperation{});
		FBeamRequestContext RequestContext;
		AuthSubsystem->CPP_Authenticate(Req, AuthenticateHandler, RequestContext, Op);
	}
}

void UBeamRuntime::AttachExternalIdentity(FUserSlot UserSlot, FString MicroserviceName, FString IdentityNamespace, FString IdentityUserId, FString IdentityAuthToken, FBeamOperationHandle Op)
{
	const auto CheckIdentityAvailableHandler = FOnGetAvailableExternalIdentityFullResponse::CreateLambda(
		[this,UserSlot, Op, MicroserviceName, IdentityNamespace, IdentityUserId, IdentityAuthToken](FGetAvailableExternalIdentityFullResponse Resp)
		{
			if (Resp.State == RS_Retrying) return;

			if (Resp.State == RS_Success)
			{
				const auto bIsAvailable = Resp.SuccessData->bAvailable;
				UE_LOG(LogTemp, Warning, TEXT("Is Available Identity Id: %s, %s"), *IdentityUserId, bIsAvailable ? TEXT("true") : TEXT("false"));

				// If the External Identity has never been assigned in this realm, we attach it to the account at the given slot. 
				if (bIsAvailable)
				{
					const auto AttachIdentityHandler = FOnPostExternalIdentityFullResponse::CreateLambda(
						[this, Op](FBeamFullResponse<UPostExternalIdentityRequest*, UAttachExternalIdentityApiResponse*> Resp)
						{
							if (Resp.State == RS_Retrying) return;

							if (Resp.State == RS_Success)
							{
								UE_LOG(LogTemp, Warning, TEXT("Successfully Attached Id! Result = %s"), *Resp.SuccessData->Result);
								GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(Op, TEXT(""));
							}

							if (Resp.State == RS_Error)
							{
								UE_LOG(LogTemp, Error, TEXT("Failed to Attach Id! Result = %s"), *Resp.ErrorData.message);
								GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, Resp.ErrorData.message);
							}
						});
					const auto _ = AttachIdentityToUser(UserSlot, MicroserviceName, IdentityNamespace, IdentityAuthToken, Op, AttachIdentityHandler);
				}
				// If it has been assigned in this realm (a user exists in this realm for this external identity id), we log in with that user account into the requesting slot.			 
				else
				{
					// If this external id is already in use in this realm, we error out.
					GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, TEXT("Given external Identity is already in use."));
				}
				return;
			}
			GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, Resp.ErrorData.message);
		});

	// If we are NOT already authenticated (we had a saved user in this slot), we fail the attach.
	if (!UserSlotSystem->IsUserSlotAuthenticated(UserSlot, this))
	{
		RequestTrackerSystem->TriggerOperationError(Op, TEXT("UserSlot contains no account to attach to."));
		return;
	}

	const auto _ = CheckExternalIdentityAvailable(MicroserviceName, IdentityNamespace, IdentityUserId, Op, CheckIdentityAvailableHandler);
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

			// If the External Identity has never been assigned in this realm, we attach it to the account at the given slot. 
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
			// If it has been assigned in this realm (a user exists in this realm for this external identity id), we log in with that user account into the requesting slot.			 
			else
			{
				// If this email is already in use we error out.
				GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, TEXT("Email is already in use."));
			}
			return;
		}

		GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, Resp.ErrorData.message);
	});

	// If we are NOT already authenticated (we had a saved user in this slot), we fail the attach.
	if (!UserSlotSystem->IsUserSlotAuthenticated(UserSlot, this))
	{
		RequestTrackerSystem->TriggerOperationError(Op, TEXT("UserSlot contains no account to attach to."));
		return;
	}

	const auto _ = CheckEmailAvailable(Email, Op, CheckIdentityAvailableHandler);
}

void UBeamRuntime::SignUpExternalIdentity(FUserSlot UserSlot, FString MicroserviceName, FString IdentityNamespace, FString IdentityUserId, FString IdentityAuthToken, FBeamOperationHandle Op)
{
	const auto CheckIdentityAvailableHandler = FOnGetAvailableExternalIdentityFullResponse::CreateLambda(
		[this,UserSlot, Op, MicroserviceName, IdentityNamespace, IdentityUserId, IdentityAuthToken](FGetAvailableExternalIdentityFullResponse Resp)
		{
			if (Resp.State == RS_Retrying) return;

			if (Resp.State == RS_Success)
			{
				const auto bIsAvailable = Resp.SuccessData->bAvailable;
				UE_LOG(LogTemp, Warning, TEXT("Is Available Identity Id: %s, %s"), *IdentityUserId, bIsAvailable ? TEXT("true") : TEXT("false"));

				// If the External Identity has never been assigned in this realm, we create a guest account and then immediately attach this identity to it. 
				if (bIsAvailable)
				{
					LoginGuest(UserSlot, Op, FDelayedOperation::CreateLambda([this, Op, UserSlot, MicroserviceName, IdentityNamespace, IdentityAuthToken]
					{
						// Begin an operation that'll only succeed if the attachment is successful
						const auto DelayedOp = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetName(), {});

						// Attach email/password to the new guest user BEFORE notifying the SDK's runtime systems.
						// If fail to attach, will fail the DelayedOp and error out the entire sign up operation and clear the slots auth state.					
						const auto AttachIdentityHandler = FOnPostExternalIdentityFullResponse::CreateLambda([this, DelayedOp](FPostExternalIdentityFullResponse Resp)
						{
							if (Resp.State == RS_Retrying) return;

							if (Resp.State == RS_Success)
							{
								UE_LOG(LogTemp, Warning, TEXT("Successfully Attached Id! Result = %s"), *Resp.SuccessData->Result);
								GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(DelayedOp, TEXT(""));
							}

							if (Resp.State == RS_Error)
							{
								UE_LOG(LogTemp, Error, TEXT("Failed to Attach Id! Result = %s"), *Resp.ErrorData.message);
								GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(DelayedOp, Resp.ErrorData.message);
							}
						});
						const auto _ = AttachIdentityToUser(UserSlot, MicroserviceName, IdentityNamespace, IdentityAuthToken, DelayedOp, AttachIdentityHandler);
						return DelayedOp;
					}));
				}
				// If it has been assigned in this realm (a user exists in this realm for this external identity id), we log in with that user account into the requesting slot.			 
				else
				{
					// If this external id is already in use in this realm, we error out.
					GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, TEXT("EXTERNAL_IDENTITY_IN_USE"));
				}
				return;
			}
			GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, Resp.ErrorData.message);
		});

	// If we are already authenticated (we had a saved user in this slot), we fail the sign up.
	if (UserSlotSystem->IsUserSlotAuthenticated(UserSlot, this))
	{
		RequestTrackerSystem->TriggerOperationError(Op, TEXT("UserSlot already contains a signed in user. Sign out first."));
		return;
	}

	const auto _ = CheckExternalIdentityAvailable(MicroserviceName, IdentityNamespace, IdentityUserId, Op, CheckIdentityAvailableHandler);
}

void UBeamRuntime::SignUpEmailAndPassword(FUserSlot UserSlot, FString Email, FString Password, FBeamOperationHandle Op)
{
	const auto CheckIdentityAvailableHandler = FOnGetAvailableFullResponse::CreateLambda([this,UserSlot, Op, Email, Password](FGetAvailableFullResponse Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			const auto bIsAvailable = Resp.SuccessData->bAvailable;
			UE_LOG(LogTemp, Warning, TEXT("Is Available Email: %s, %s"), *Email, bIsAvailable ? TEXT("true") : TEXT("false"));

			// If this email has never been assigned in this realm, we create a guest account and then immediately attach this email and password to that account. 
			if (bIsAvailable)
			{
				LoginGuest(UserSlot, Op, FDelayedOperation::CreateLambda([this, Op, UserSlot, Email, Password]
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
			// If it has been assigned in this realm (a user exists in this realm for this external identity id), we log in with that user account into the requesting slot.			 
			else
			{
				// If this email is already in use we error out.
				GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, TEXT("EMAIL_IN_USE"));
			}
			return;
		}
		GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, Resp.ErrorData.message);
	});

	// If we are already authenticated (we had a saved user in this slot), we fail the sign up
	if (UserSlotSystem->IsUserSlotAuthenticated(UserSlot, this))
	{
		RequestTrackerSystem->TriggerOperationError(Op, TEXT("User already at slot."));
		return;
	}

	// Kick off the process for sign up 
	const auto _ = CheckEmailAvailable(Email, Op, CheckIdentityAvailableHandler);
}

void UBeamRuntime::Logout(FUserSlot UserSlot, EUserSlotClearedReason Reason, bool bRemoveLocalData, FBeamOperationHandle Op)
{
	FBeamRealmUser RealmUser;
	if (UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		// Configure us to wait until the slot is fully unauthenticated and then sign in.		 
		FDelegateHandle Handle;
		Handle = OnUserClearedCode.AddLambda([this, Op, &Handle](FUserSlot UserSlot)
		{
			// Remove this lambda from the list of callbacks
			OnUserClearedCode.Remove(Handle);

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


void UBeamRuntime::OnAuthenticated(FAuthenticateFullResponse Resp, FUserSlot UserSlot, FBeamOperationHandle Op, FDelayedOperation BeforeUserNotifyOperation)
{
	if (Resp.State == RS_Retrying) return;

	if (Resp.State == RS_Success)
	{
		const UTokenResponse* Token = Resp.SuccessData;
		AuthenticateWithToken(UserSlot, Token, Op, BeforeUserNotifyOperation);
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
		FOnNotificationEvent ConnHandler = FOnNotificationEvent::CreateLambda([this, UserSlot, Op](const FNotificationEvent& Evt)
		{
			if (Evt.EventType == Connected)
			{
				UE_LOG(LogBeamNotifications, Display, TEXT("Connected to beamable notification service! SLOT=%s, EVT_TYPE=%s"), *UserSlot.Name,
				       *StaticEnum<ENotificationMessageType>()->GetNameByValue(Evt.EventType).ToString())
				DefaultNotificationChannels.Add(UserSlot, Evt.ConnectedData.ConnectedHandle);

				UserSlotSystem->SaveSlot(UserSlot, this);
				UserSlotSystem->TriggerUserAuthenticatedIntoSlot(UserSlot, this);

				if (const auto Connectivity = ConnectivityState.FindRef(UserSlot))
				{
					Connectivity->StartRecoveryFixup();
				}

				RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
			}
			else if (Evt.EventType == ConnectionFailed)
			{
				UE_LOG(LogBeamNotifications, Error, TEXT("Failed to connect to beamable's notification service! SLOT=%s, EVT_TYPE=%s"), *UserSlot.Name,
				       *StaticEnum<ENotificationMessageType>()->GetNameByValue(Evt.EventType).ToString())
				UserSlotSystem->ClearUserAtSlot(UserSlot, USCR_FailedAuthentication, true, this);
				RequestTrackerSystem->TriggerOperationError(Op, Evt.ConnectionFailedData.Error);
			}
			else if (Evt.EventType == Closed)
			{
				// TODO: Handle disconnect flow
			}
		});

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
		// TODO: Set offline mode for this user slot.	

		// Call OnUserFailedFrictionlessAuth on all RuntimeSubsystems
		if (const UWorld* World = GetWorld())
		{
			if (const UGameInstance* GameInstance = World->GetGameInstance())
			{
				const auto Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();
				for (auto& Subsystem : Subsystems)
				{
					Subsystem->OnFailedUserAuth(UserSlot);
				}
			}
		}
		UserSlotSystem->ClearUserAtSlot(UserSlot, USCR_FailedAuthentication, true, this);
		RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
	}
}


FBeamRequestContext UBeamRuntime::LoginGuest(FUserSlot UserSlot, FBeamOperationHandle Op, FDelayedOperation OnBeforePostAuthentication)
{
	const UBeamAuthApi* AuthSubsystem = GEngine->GetEngineSubsystem<UBeamAuthApi>();
	const FOnAuthenticateFullResponse AuthenticateHandler = FOnAuthenticateFullResponse::CreateUObject(this, &UBeamRuntime::OnAuthenticated, UserSlot, Op, OnBeforePostAuthentication);

	UAuthenticateRequest* Req = NewObject<UAuthenticateRequest>(GetTransientPackage());
	Req->Body = NewObject<UTokenRequestWrapper>(Req);
	Req->Body->GrantType = TEXT("guest");

	FBeamRequestContext RequestContext;
	AuthSubsystem->CPP_Authenticate(Req, AuthenticateHandler, RequestContext, Op, this);
	return RequestContext;
}

FBeamRequestContext UBeamRuntime::CheckExternalIdentityAvailable(FString ExternalService, FString ExternalNamespace, FString ExternalUserId, FBeamOperationHandle Op,
                                                                 FOnGetAvailableExternalIdentityFullResponse Handler) const
{
	const auto AccountAPI = GEngine->GetEngineSubsystem<UBeamAccountsApi>();

	FBeamRequestContext Ctx;
	UGetAvailableExternalIdentityRequest* Req = UGetAvailableExternalIdentityRequest::Make(ExternalService, ExternalUserId, FOptionalString{ExternalNamespace}, GetTransientPackage(), {});
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

FBeamRequestContext UBeamRuntime::AttachIdentityToUser(FUserSlot UserSlot, FString ExternalService, FString ExternalNamespace, FString ExternalToken, FBeamOperationHandle Op,
                                                       FOnPostExternalIdentityFullResponse Handler) const
{
	const auto AccountAPI = GEngine->GetEngineSubsystem<UBeamAccountsApi>();

	const auto Req = UPostExternalIdentityRequest::Make(ExternalService, ExternalToken, {}, FOptionalString{ExternalNamespace}, GetTransientPackage(), {});
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

FBeamRequestContext UBeamRuntime::RemoveIdentityFromUser(FUserSlot UserSlot, FString ExternalService, FString ExternalNamespace, FString ExternalToken, FBeamOperationHandle Op,
                                                         FOnDeleteExternalIdentityFullResponse Handler) const
{
	const auto AccountAPI = GEngine->GetEngineSubsystem<UBeamAccountsApi>();

	const auto Req = UDeleteExternalIdentityRequest::Make(ExternalService, ExternalToken, FOptionalString{ExternalNamespace}, GetTransientPackage(), {});
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
		TopJsonObject->SetStringField(TEXT("category"), EventCategory);
		TopJsonObject->SetStringField(TEXT("event"), EventName);
		TopJsonObject->SetObjectField(TEXT("params"), EventParamsObj[i]);

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
#undef LOCTEXT_NAMESPACE
