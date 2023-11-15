// Fill out your copyright notice in the Description page of Project Settings.


#include "Runtime/BeamRuntime.h"

#include "BeamLogging.h"
#include "PacketHandler.h"
#include "AutoGen/SubSystems/BeamRealmsApi.h"
#include "AutoGen/SubSystems/Realms/GetClientDefaultsRequest.h"
#include "BeamNotifications/BeamNotifications.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/BeamRuntimeSubsystem.h"

#if WITH_EDITOR
#include "Kismet/KismetSystemLibrary.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#endif

#define LOCTEXT_NAMESPACE "BeamRuntime"


void UBeamRuntime::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Set us up to handle sign-in/out flows in editor as well as tracking multiple developer user slots.
	UserSlotSystem       = GEngine->GetEngineSubsystem<UBeamUserSlots>();
	RequestTrackerSystem = GEngine->GetEngineSubsystem<UBeamRequestTracker>();
	NotificationSystem   = GEngine->GetEngineSubsystem<UBeamNotifications>();

	UserSlotAuthenticatedHandler = UserSlotSystem->GlobalUserSlotAuthenticatedCodeHandler.AddUObject(this, &UBeamRuntime::TriggerOnUserSlotAuthenticated);
	UserSlotClearedHandler       = UserSlotSystem->GlobalUserSlotClearedCodeHandler.AddUObject(this, &UBeamRuntime::TriggerOnUserSlotCleared);

	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UBeamRuntime::TriggerInitializeWhenUnrealReady);
	UE_LOG(LogBeamRuntime, Verbose, TEXT("Initializing UBeamRuntime Subsystem!"));

	if (GetGameInstance()->GetWorld()->IsPlayInEditor())
	{
		// When running as a dedicated server instance, swap out the execute request delegate
		const FName ExecuteRequestImpl = GET_FUNCTION_NAME_CHECKED(UBeamRuntime, PIEExecuteRequestImpl);

		UBeamBackend* EngineSubsystem = GEngine->GetEngineSubsystem<UBeamBackend>();
		EngineSubsystem->ExecuteRequestDelegate.BindUFunction(this, ExecuteRequestImpl);
		EngineSubsystem->bIsInPIE = true;
		UE_LOG(LogBeamRuntime, Verbose, TEXT("Initializing UBeamRuntime Subsystem - FROM PIE!"));
	}
	else
	{
		// When running as a dedicated server instance, swap out the execute request delegate
		const FName ExecuteRequestImpl = GetGameInstance()->IsDedicatedServerInstance()
			                                 ? GET_FUNCTION_NAME_CHECKED(UBeamBackend, DedicatedServerExecuteRequestImpl)
			                                 : GET_FUNCTION_NAME_CHECKED(UBeamBackend, DefaultExecuteRequestImpl);

		UBeamBackend* EngineSubsystem = GEngine->GetEngineSubsystem<UBeamBackend>();
		EngineSubsystem->ExecuteRequestDelegate.BindUFunction(EngineSubsystem, ExecuteRequestImpl);

		UE_LOG(LogBeamRuntime, Verbose, TEXT("Initializing UBeamRuntime Subsystem!"));
	}
}


void UBeamRuntime::Deinitialize()
{
	Super::Deinitialize();
	UserSlotSystem->GlobalUserSlotAuthenticatedCodeHandler.Remove(UserSlotAuthenticatedHandler);
	UserSlotSystem->GlobalUserSlotClearedCodeHandler.Remove(UserSlotClearedHandler);

	for (const auto& SlotName : GetDefault<UBeamCoreSettings>()->RuntimeUserSlots)
	{
		UserSlotSystem->ClearUserAtSlot(SlotName, ExitPIE, false, this);
	}

	// When running as a dedicated server instance, swap out the execute request delegate
	const FName ExecuteRequestImpl = GET_FUNCTION_NAME_CHECKED(UBeamBackend, DefaultExecuteRequestImpl);

	UBeamBackend* EngineSubsystem = GEngine->GetEngineSubsystem<UBeamBackend>();
	EngineSubsystem->ExecuteRequestDelegate.BindUFunction(EngineSubsystem, ExecuteRequestImpl);
	EngineSubsystem->bIsInPIE = false;

	NotificationSystem->ClearPIESockets();
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

void UBeamRuntime::TriggerInitializeWhenUnrealReady()
{
	const FBeamRealmHandle TargetRealm = GetDefault<UBeamCoreSettings>()->TargetRealm;

	// Initialize user ConnectivityState for each slot
	for (FString RuntimeUserSlot : GetDefault<UBeamCoreSettings>()->RuntimeUserSlots)
	{
		URuntimeConnectivityManager* ConnectivityManager  = NewObject<URuntimeConnectivityManager>();
		ConnectivityManager->OwnerSlot                    = RuntimeUserSlot;
		ConnectivityManager->CurrentState                 = Offline;
		ConnectivityManager->CurrentConnectionLostTime    = FDateTime::UtcNow();
		ConnectivityManager->ConnectionLostCountInSession = 0;
		ConnectivityManager->FixupOperationDAG            = {};
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
		Info.Image          = FCoreStyle::Get().GetBrush(TEXT("MessageLog.Warning"));
		FSlateNotificationManager::Get().AddNotification(Info);
#else
		checkf(false, TEXT("Builds with Beamable cannot exist without a configured target realm!"))
#endif
	}
	else
	{
		UE_LOG(LogBeamRuntime, Warning, TEXT("Starting configured Target Realm: CID=%s, PID=%s!"), *TargetRealm.Cid.AsString, *TargetRealm.Pid.AsString);

		UBeamRequestTracker* RequestTracker = RequestTrackerSystem;
		if (const UWorld* World = GetWorld())
		{
			if (const UGameInstance* GameInstance = World->GetGameInstance())
			{
				const TArray<UBeamRuntimeSubsystem*> Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();

				InitializeWhenUnrealReadyOps.Reset(Subsystems.Num());
				for (auto& Subsystem : Subsystems)
				{
					FBeamOperationHandle Handle;
					Subsystem->InitializeWhenUnrealReady(Handle);
					InitializeWhenUnrealReadyOps.Add(Handle);
				}

				OnInitializeWhenUnrealReadyCompleted = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::TriggerOnBeamableStarting);
				OnInitializeWhenUnrealReadyWait      = RequestTracker->CPP_WaitAll({}, InitializeWhenUnrealReadyOps, {}, OnInitializeWhenUnrealReadyCompleted);
			}
		}
	}
}

void UBeamRuntime::TriggerOnBeamableStarting(const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&, const TArray<FBeamErrorResponse>&)
{
	UBeamRequestTracker* RequestTracker = RequestTrackerSystem;
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
			checkf(!RealmSecret.IsEmpty(), TEXT("To run a dedicated server that communicates with Beamable, either:\n"
				       "- Start it with the command line \'-beamable-realm-secret <realm_secret>\'\n"
				       "- Start it in an environment with the EnvVar \'BEAMABLE_REALM_SECRET\' set to your realm secret.\n"
				       "To find your realm secret for your realms, look into your Project Settings => Editor => Beamable Editor => PerSlotDeveloperProjectData => All Realms\n"
				       "Remember to set this command line argument in your Networking settings for playmode in Editor Settings => Level Editor => Play => Multiplayer Options => Server => Additional Server Launch Parameters."
			       ))
		}
		GEngine->GetEngineSubsystem<UBeamBackend>()->RealmSecret = RealmSecret;
	}

	// After we have set up the RealmSecret (for dedicated servers only) --- the UBeamRuntimeSubsystem's OnBeamableStarted gets called.
	// OnBeamableReady is never called in the server, as the server never authenticates via the UserSlot system.
	// This is not great semantics, but necessary while we don't have server tokens for authentication.
	// OnBeamableStarted basically means we are ready for authentication, but nothing else. And... that until you authenticate into the OwnerPlayer slot, OnBeamableReady functions will not run
	// on BeamableRuntimeSubsystems.
	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			const TArray<UBeamRuntimeSubsystem*> Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();

			OnBeamableStartedOps.Reset(Subsystems.Num());
			for (auto& Subsystem : Subsystems)
			{
				FBeamOperationHandle Handle;
				Subsystem->OnBeamableStarting(Handle);
				OnBeamableStartedOps.Add(Handle);
			}

			OnBeamableStartedCompleted = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::TriggerOnStartedAndFrictionlessAuth);
			OnBeamableStartedWait      = RequestTracker->CPP_WaitAll({}, OnBeamableStartedOps, {}, OnBeamableStartedCompleted);
		}
	}
}

void UBeamRuntime::TriggerOnStartedAndFrictionlessAuth(const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&, const TArray<FBeamErrorResponse>&)
{
	OnStarted.Broadcast();
	bIsBeamableStarted = true;

	// For servers, don't try to authenticate.
	if (const bool bIsDedicatedServer = GetGameInstance()->IsDedicatedServerInstance())
	{
	}
	// Sign in automatically to the owner player slot (if configured to do so).
	else if (GetDefault<UBeamCoreSettings>()->bAutomaticFrictionlessAuthForOwnerPlayer)
	{
		FrictionlessLoginIntoSlot(GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot());
	}
}


void UBeamRuntime::TriggerOnUserSlotAuthenticated(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context)
{
	const auto RequestTracker = RequestTrackerSystem;

	if (!OnUserSignedInOps.Contains(UserSlot))
		OnUserSignedInOps.Add(UserSlot, {});

	if (!OnUserSignedInWaits.Contains(UserSlot))
		OnUserSignedInWaits.Add(UserSlot, {});

	if (!OnUserSignedInCompleted.Contains(UserSlot))
		OnUserSignedInCompleted.Add(UserSlot, {});

	auto& SignedInOps        = *OnUserSignedInOps.Find(UserSlot);
	auto& SignedInOpsWait    = *OnUserSignedInWaits.Find(UserSlot);
	auto& SignedInOpsHandler = *OnUserSignedInCompleted.Find(UserSlot);

	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			const auto Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();

			SignedInOps.Reset(Subsystems.Num());
			for (auto& Subsystem : Subsystems)
			{
				FBeamOperationHandle Handle;
				Subsystem->OnUserSignedIn(UserSlot, BeamRealmUser, GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot().Equals(UserSlot), Handle);
				SignedInOps.Add(Handle);
			}

			SignedInOpsHandler = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::TriggerSubsystemPostUserSignIn, UserSlot, BeamRealmUser);
			SignedInOpsWait    = RequestTracker->CPP_WaitAll({}, SignedInOps, {}, SignedInOpsHandler);
		}
	}
}

void UBeamRuntime::TriggerSubsystemPostUserSignIn(const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&, const TArray<FBeamErrorResponse>&, FUserSlot UserSlot, FBeamRealmUser BeamRealmUser)
{
	UBeamRequestTracker* RequestTracker = RequestTrackerSystem;

	if (!OnPostUserSignedInOps.Contains(UserSlot))
		OnPostUserSignedInOps.Add(UserSlot, {});

	if (!OnPostUserSignedInWaits.Contains(UserSlot))
		OnPostUserSignedInWaits.Add(UserSlot, {});

	if (!OnPostUserSignedInCompleted.Contains(UserSlot))
		OnPostUserSignedInCompleted.Add(UserSlot, {});

	FBeamWaitHandle&              SignedInOpsWait    = *OnPostUserSignedInWaits.Find(UserSlot);
	FOnWaitCompleteCode&          SignedInOpsHandler = *OnPostUserSignedInCompleted.Find(UserSlot);
	TArray<FBeamOperationHandle>& SignedInOps        = *OnPostUserSignedInOps.Find(UserSlot);

	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			const TArray<UBeamRuntimeSubsystem*> Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();

			SignedInOps.Reset(Subsystems.Num());
			for (auto& Subsystem : Subsystems)
			{
				FBeamOperationHandle Handle;
				Subsystem->OnPostUserSignedIn(UserSlot, BeamRealmUser, GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot().Equals(UserSlot), Handle);
				SignedInOps.Add(Handle);
			}

			SignedInOpsHandler = FOnWaitCompleteCode::CreateLambda([this, UserSlot](const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&, const TArray<FBeamErrorResponse>&)
			{
				// By default, only UserSlot at index 0 of RuntimeUserSlots always gets loaded.
				// This actually only be called ONCE during the entire lifecycle of your program.
				if (!bDidFirstAuthRun && UserSlot.Name.Equals(GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot()))
				{
					OnReady.Broadcast();
					bDidFirstAuthRun = true;
				}

				OnUserReadyCode.Broadcast(UserSlot);
				OnUserReady.Broadcast(UserSlot);
			});
			SignedInOpsWait = RequestTracker->CPP_WaitAll({}, SignedInOps, {}, SignedInOpsHandler);
		}
	}
}


void UBeamRuntime::TriggerOnUserSlotCleared(const EUserSlotClearedReason& Reason, const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context)
{
	// We unsubscribe automatically all notification handlers associated with a user slot when that user signs out --- then we close the connection
	NotificationSystem->TryUnsubscribeAllFromSlot(UserSlot, DefaultNotificationChannel);
	NotificationSystem->CloseSocketsForSlot(UserSlot);

	// If we clear the slot during login or signup due to failure, we don't need to run the rest of the flow.
	if (Reason == FailedAuthentication)
		return;

	// Let BeamRuntimeSubsystems run their callbacks
	UBeamRequestTracker* RequestTracker = RequestTrackerSystem;
	if (!OnUserSignedOutOps.Contains(UserSlot))
		OnUserSignedOutOps.Add(UserSlot, {});

	if (!OnUserSignedOutWaits.Contains(UserSlot))
		OnUserSignedOutWaits.Add(UserSlot, {});

	if (!OnUserSignedOutCompleted.Contains(UserSlot))
		OnUserSignedOutCompleted.Add(UserSlot, {});

	FBeamWaitHandle&              SignedOutOpsWait    = *OnUserSignedOutWaits.Find(UserSlot);
	FOnWaitCompleteCode&          SignedOutOpsHandler = *OnUserSignedOutCompleted.Find(UserSlot);
	TArray<FBeamOperationHandle>& SignedOutOps        = *OnUserSignedOutOps.Find(UserSlot);

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

			SignedOutOpsHandler = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::TriggerPostUserSignedOut, UserSlot, Reason, BeamRealmUser);
			SignedOutOpsWait    = RequestTracker->CPP_WaitAll({}, SignedOutOps, {}, SignedOutOpsHandler);
		}
	}
}

void UBeamRuntime::TriggerPostUserSignedOut(const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&, const TArray<FBeamErrorResponse>&, FUserSlot UserSlot, EUserSlotClearedReason Reason, FBeamRealmUser BeamRealmUser)
{
	UBeamRequestTracker* RequestTracker = RequestTrackerSystem;

	if (!OnPostUserSignedOutOps.Contains(UserSlot))
		OnPostUserSignedOutOps.Add(UserSlot, {});

	if (!OnPostUserSignedOutWaits.Contains(UserSlot))
		OnPostUserSignedOutWaits.Add(UserSlot, {});

	if (!OnPostUserSignedOutCompleted.Contains(UserSlot))
		OnPostUserSignedOutCompleted.Add(UserSlot, {});

	FBeamWaitHandle&              SignedOutOpsWait    = *OnPostUserSignedOutWaits.Find(UserSlot);
	FOnWaitCompleteCode&          SignedOutOpsHandler = *OnPostUserSignedOutCompleted.Find(UserSlot);
	TArray<FBeamOperationHandle>& SignedOutOps        = *OnPostUserSignedOutOps.Find(UserSlot);

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

			SignedOutOpsHandler = FOnWaitCompleteCode::CreateLambda([this, UserSlot](const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&, const TArray<FBeamErrorResponse>&)
			{
				OnUserClearedCode.Broadcast(UserSlot);
				OnUserCleared.Broadcast(UserSlot);
			});
			SignedOutOpsWait = RequestTracker->CPP_WaitAll({}, SignedOutOps, {}, SignedOutOpsHandler);
		}
	}
}

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

FBeamOperationHandle UBeamRuntime::LoginExternalIdentityOperation(FUserSlot UserSlot, FString ExternalService, FString ExternalNamespace, FString ExternalToken, FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	LoginExternalIdentity(UserSlot, ExternalService, ExternalNamespace, ExternalToken, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_LoginExternalIdentityOperation(FUserSlot UserSlot, FString ExternalService, FString ExternalNamespace, FString ExternalToken, FBeamOperationEventHandlerCode OnOperationEvent)
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


FBeamOperationHandle UBeamRuntime::AttachExternalIdentityOperation(FUserSlot UserSlot, FString MicroserviceName, FString IdentityNamespace, FString IdentityUserId, FString IdentityAuthToken, FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	AttachExternalIdentity(UserSlot, MicroserviceName, IdentityNamespace, IdentityUserId, IdentityAuthToken, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_AttachExternalIdentityOperation(FUserSlot UserSlot, FString MicroserviceName, FString IdentityNamespace, FString IdentityUserId, FString IdentityAuthToken, FBeamOperationEventHandlerCode OnOperationEvent)
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

FBeamOperationHandle UBeamRuntime::SignUpExternalIdentityOperation(FUserSlot UserSlot, FString MicroserviceName, FString IdentityNamespace, FString IdentityUserId, FString IdentityAuthToken, FBeamOperationEventHandler OnOperationEvent)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	SignUpExternalIdentity(UserSlot, MicroserviceName, IdentityNamespace, IdentityUserId, IdentityAuthToken, Handle);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_SignUpExternalIdentityOperation(FUserSlot UserSlot, FString MicroserviceName, FString IdentityNamespace, FString IdentityUserId, FString IdentityAuthToken, FBeamOperationEventHandlerCode OnOperationEvent)
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


void UBeamRuntime::FrictionlessLoginIntoSlot(const FUserSlot& UserSlot)
{
	/**
	 * If runs the FrictionlessAuthentication flow for the given user slot. You can make this call whenever you want to create a new user into a new slot.
	 * Passing nothing, will sign into the OwnerPlayerSlot. If the given slot is already authenticated, this is a no-op.
	 */

	// No-Op if we are already authed at this slot.
	if (UserSlotSystem->IsUserSlotAuthenticated(UserSlot)) return;

	// Create the OperationHandle for the FrictionlessAuth operation
	// This will handle errors by clearing up the data for the slot being signed into into and triggering the FailedUserAuth callback of all BeamRuntimeSubsystems.
	const FBeamOperationEventHandlerCode AuthOpHandler = FBeamOperationEventHandlerCode::CreateLambda([this, UserSlot](const TArray<FUserSlot>&, FBeamOperationEvent Evt)
	{
		// If any errors occur during this process, 
		if (Evt.EventType == OET_ERROR)
		{
			// Make sure any partial state for the user slot is cleared (this is necessary since authentication is a multi-step process)
			UserSlotSystem->ClearUserAtSlot(UserSlot, FailedAuthentication);

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

			const UBeamAccountsApi*     AccountsApi = GEngine->GetEngineSubsystem<UBeamAccountsApi>();
			UBasicAccountsGetMeRequest* MeReq       = UBasicAccountsGetMeRequest::Make(GetTransientPackage(), {});
			FBeamRequestContext         Ctx;
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
	UAuthenticateRequest* Req    = NewObject<UAuthenticateRequest>(GetTransientPackage());
	Req->Body                    = NewObject<UTokenRequestWrapper>(Req);
	Req->Body->GrantType         = TEXT("external");
	Req->Body->ExternalToken     = FOptionalString{ExternalToken};
	Req->Body->ProviderService   = FOptionalString{ExternalService};
	Req->Body->ProviderNamespace = FOptionalString{ExternalNamespace};

	const UBeamAuthApi* AuthSubsystem = GEngine->GetEngineSubsystem<UBeamAuthApi>();

	// If we are already authenticated (we had a saved user in this slot), we sign out of the user at that slot, wait for all runtime systems to clean up the user and then sign back into the given user.
	FBeamRealmUser RealmUser;
	if (UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		// Configure us to wait until the slot is fully unauthenticated and then sign in.
		OnUserClearedCode.AddLambda([this, AuthSubsystem](FUserSlot UserSlot, FBeamOperationHandle OpHandle, UAuthenticateRequest* AuthReq)
		{
			const auto          AuthenticateHandler = FOnAuthenticateFullResponse::CreateUObject(this, &UBeamRuntime::OnAuthenticated, UserSlot, OpHandle, FDelayedOperation{});
			FBeamRequestContext RequestContext;
			AuthSubsystem->CPP_Authenticate(AuthReq, AuthenticateHandler, RequestContext, OpHandle);
		}, Op, Req);
		UserSlotSystem->ClearUserAtSlot(UserSlot, Manual, true, this);
	}
	else
	{
		const auto          AuthenticateHandler = FOnAuthenticateFullResponse::CreateUObject(this, &UBeamRuntime::OnAuthenticated, UserSlot, Op, FDelayedOperation{});
		FBeamRequestContext RequestContext;
		AuthSubsystem->CPP_Authenticate(Req, AuthenticateHandler, RequestContext, Op);
	}
}

void UBeamRuntime::LoginEmailAndPassword(FUserSlot UserSlot, FString Email, FString Password, FBeamOperationHandle Op)
{
	UAuthenticateRequest* Req = NewObject<UAuthenticateRequest>(GetTransientPackage());
	Req->Body                 = NewObject<UTokenRequestWrapper>(Req);
	Req->Body->GrantType      = TEXT("password");
	Req->Body->Username       = FOptionalString{Email};
	Req->Body->Password       = FOptionalString{Password};

	const UBeamAuthApi* AuthSubsystem = GEngine->GetEngineSubsystem<UBeamAuthApi>();

	// If we are already authenticated (we had a saved user in this slot), we sign out of the user at that slot, wait for all runtime systems to clean up the user and then sign back into the given user.
	FBeamRealmUser RealmUser;
	if (UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		// Configure us to wait until the slot is fully unauthenticated and then sign in.
		OnUserClearedCode.AddLambda([this, AuthSubsystem](FUserSlot UserSlot, FBeamOperationHandle OpHandle, UAuthenticateRequest* AuthReq)
		{
			const auto          AuthenticateHandler = FOnAuthenticateFullResponse::CreateUObject(this, &UBeamRuntime::OnAuthenticated, UserSlot, OpHandle, FDelayedOperation{});
			FBeamRequestContext RequestContext;
			AuthSubsystem->CPP_Authenticate(AuthReq, AuthenticateHandler, RequestContext, OpHandle);
		}, Op, Req);
		UserSlotSystem->ClearUserAtSlot(UserSlot, Manual, true, this);
	}
	else
	{
		const auto          AuthenticateHandler = FOnAuthenticateFullResponse::CreateUObject(this, &UBeamRuntime::OnAuthenticated, UserSlot, Op, FDelayedOperation{});
		FBeamRequestContext RequestContext;
		AuthSubsystem->CPP_Authenticate(Req, AuthenticateHandler, RequestContext, Op);
	}
}

void UBeamRuntime::AttachExternalIdentity(FUserSlot UserSlot, FString MicroserviceName, FString IdentityNamespace, FString IdentityUserId, FString IdentityAuthToken, FBeamOperationHandle Op)
{
	const auto CheckIdentityAvailableHandler = FOnGetAvailableExternalIdentityFullResponse::CreateLambda([this,UserSlot, Op, MicroserviceName, IdentityNamespace, IdentityUserId, IdentityAuthToken](FGetAvailableExternalIdentityFullResponse Resp)
	{
		if (Resp.State == RS_Success)
		{
			const auto bIsAvailable = Resp.SuccessData->bAvailable;
			UE_LOG(LogTemp, Warning, TEXT("Is Available Identity Id: %s, %s"), *IdentityUserId, bIsAvailable ? TEXT("true") : TEXT("false"));

			// If the External Identity has never been assigned in this realm, we attach it to the account at the given slot. 
			if (bIsAvailable)
			{
				const auto AttachIdentityHandler = FOnPostExternalIdentityFullResponse::CreateLambda([this, Op](FBeamFullResponse<UPostExternalIdentityRequest*, UAttachExternalIdentityApiResponse*> Resp)
				{
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
				AttachIdentityToUser(UserSlot, MicroserviceName, IdentityNamespace, IdentityAuthToken, Op, AttachIdentityHandler);
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

	CheckExternalIdentityAvailable(MicroserviceName, IdentityNamespace, IdentityUserId, Op, CheckIdentityAvailableHandler);
}

void UBeamRuntime::AttachEmailAndPassword(FUserSlot UserSlot, FString Email, FString Password, FBeamOperationHandle Op)
{
	const auto CheckIdentityAvailableHandler = FOnGetAvailableFullResponse::CreateLambda([this,UserSlot, Op, Email, Password](FGetAvailableFullResponse Resp)
	{
		if (Resp.State == RS_Success)
		{
			const auto bIsAvailable = Resp.SuccessData->bAvailable;
			UE_LOG(LogTemp, Warning, TEXT("Is Available Email: %s, %s"), *Email, bIsAvailable ? TEXT("true") : TEXT("false"));

			// If the External Identity has never been assigned in this realm, we attach it to the account at the given slot. 
			if (bIsAvailable)
			{
				const auto RegisterEmailHandler = FOnBasicAccountsPostRegisterFullResponse::CreateLambda([this, Op](FBasicAccountsPostRegisterFullResponse Resp)
				{
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
				AttachEmailAndPasswordToUser(UserSlot, Email, Password, Op, RegisterEmailHandler);
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

	CheckEmailAvailable(Email, Op, CheckIdentityAvailableHandler);
}

void UBeamRuntime::SignUpExternalIdentity(FUserSlot UserSlot, FString MicroserviceName, FString IdentityNamespace, FString IdentityUserId, FString IdentityAuthToken, FBeamOperationHandle Op)
{
	const auto CheckIdentityAvailableHandler = FOnGetAvailableExternalIdentityFullResponse::CreateLambda([this,UserSlot, Op, MicroserviceName, IdentityNamespace, IdentityUserId, IdentityAuthToken](FGetAvailableExternalIdentityFullResponse Resp)
	{
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
					const auto                                                                                                                                                                             DelayedOp = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetName(),
					                                                                FBeamOperationEventHandlerCode::CreateLambda([this, Op, UserSlot](const TArray<FUserSlot>&, const FBeamOperationEvent& Evt)
					                                                                {
						                                                                if (Evt.EventType == OET_ERROR)
						                                                                {
							                                                                UserSlotSystem->ClearUserAtSlot(UserSlot, FailedAuthentication, true, this);
							                                                                RequestTrackerSystem->TriggerOperationError(Op, Evt.EventData);
						                                                                }
					                                                                }));

					// Attach email/password to the new guest user BEFORE notifying the SDK's runtime systems.
					// If fail to attach, will fail the DelayedOp and error out the entire sign up operation and clear the slots auth state.					
					const auto AttachIdentityHandler = FOnPostExternalIdentityFullResponse::CreateLambda([this, DelayedOp](FBeamFullResponse<UPostExternalIdentityRequest*, UAttachExternalIdentityApiResponse*> Resp)
					{
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
					AttachIdentityToUser(UserSlot, MicroserviceName, IdentityNamespace, IdentityAuthToken, Op, AttachIdentityHandler);
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

	CheckExternalIdentityAvailable(MicroserviceName, IdentityNamespace, IdentityUserId, Op, CheckIdentityAvailableHandler);
}

void UBeamRuntime::SignUpEmailAndPassword(FUserSlot UserSlot, FString Email, FString Password, FBeamOperationHandle Op)
{
	const auto CheckIdentityAvailableHandler = FOnGetAvailableFullResponse::CreateLambda([this,UserSlot, Op, Email, Password](FGetAvailableFullResponse Resp)
	{
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
					const auto                                                                                                                                                                             DelayedOp = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetName(),
					                                                                FBeamOperationEventHandlerCode::CreateLambda([this, Op, UserSlot](const TArray<FUserSlot>&, const FBeamOperationEvent& Evt)
					                                                                {
						                                                                if (Evt.EventType == OET_ERROR)
						                                                                {
							                                                                UserSlotSystem->ClearUserAtSlot(UserSlot, FailedAuthentication, true, this);
							                                                                RequestTrackerSystem->TriggerOperationError(Op, Evt.EventData);
						                                                                }
					                                                                }));

					// Attach email/password to the new guest user BEFORE notifying the SDK's runtime systems.
					// If fail to attach, will fail the DelayedOp and error out the entire sign up operation and clear the slots auth state.
					const auto RegisterEmailHandler = FOnBasicAccountsPostRegisterFullResponse::CreateLambda([this, DelayedOp](FBasicAccountsPostRegisterFullResponse Resp)
					{
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
					AttachEmailAndPasswordToUser(UserSlot, Email, Password, Op, RegisterEmailHandler);
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
	CheckEmailAvailable(Email, Op, CheckIdentityAvailableHandler);
}


void UBeamRuntime::OnAuthenticated(FAuthenticateFullResponse Resp, FUserSlot UserSlot, FBeamOperationHandle Op, FDelayedOperation BeforeUserNotifyOperation)
{
	if (Resp.State == RS_Success)
	{
		const UTokenResponse* Token = Resp.SuccessData;
		AuthenticateWithToken(UserSlot, Token, Op, BeforeUserNotifyOperation);
	}
	else
	{
		UserSlotSystem->ClearUserAtSlot(UserSlot, FailedAuthentication, true, this);
		RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
	}
}

void UBeamRuntime::AuthenticateWithToken(FUserSlot UserSlot, const UTokenResponse* Token, FBeamOperationHandle Op, FDelayedOperation BeforeUserNotifyOperation)
{
	const FBeamCid Cid = GetDefault<UBeamCoreSettings>()->TargetRealm.Cid;
	const FBeamPid Pid = GetDefault<UBeamCoreSettings>()->TargetRealm.Pid;

	const FString AccessToken  = Token->AccessToken.Val;
	const FString RefreshToken = Token->RefreshToken.Val;
	const int64   ExpiresIn    = Token->ExpiresIn;

	UserSlotSystem->SetAuthenticationDataAtSlot(UserSlot, AccessToken, RefreshToken, FDateTime::UtcNow().ToUnixTimestamp(), ExpiresIn, Cid, Pid, this);

	// If I'm given a function that returns an Operation, run and wait for that operation before continuing this one.
	// We use this to provide much better semantics for SignUp with Email/Password or ThirdParty/Federated identities.
	// This is because the sign up/in operation will result in success only if the attachment is successful.
	// This also means that the [Post]UserSignIn and UserReady callbacks are only invoked after the attach/register stuff has ran.
	// This is a much better flow for PC/Console games where we can disable frictionless auth and instead call SignUpOrLoginWith_____.
	if (BeforeUserNotifyOperation.IsBound())
	{
		const auto BeforeAuthSetupOp          = BeforeUserNotifyOperation.Execute();
		const auto BeforeAuthSetupWaitHandler = FOnWaitCompleteCode::CreateLambda([this, UserSlot, Op](const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&, const TArray<FBeamErrorResponse>&)
		{
			RunPostAuthenticationSetup(UserSlot, Op);
		});
		RequestTrackerSystem->CPP_WaitAll({}, {BeforeAuthSetupOp}, {}, BeforeAuthSetupWaitHandler);
	}
	else
	{
		RunPostAuthenticationSetup(UserSlot, Op);
	}
}

void UBeamRuntime::RunPostAuthenticationSetup(FUserSlot UserSlot, FBeamOperationHandle Op)
{
	// Makes a GetMe request to get the updated account data.
	FBeamRequestContext                     RequestContext;
	const UBeamAccountsApi*                 AccountSubsystem = GEngine->GetEngineSubsystem<UBeamAccountsApi>();
	const FOnBasicAccountsGetMeFullResponse GetMeHandler     = FOnBasicAccountsGetMeFullResponse::CreateUObject(this, &UBeamRuntime::RunPostAuthenticationSetup_OnGetMe, UserSlot, Op);
	UBasicAccountsGetMeRequest*             MeReq            = UBasicAccountsGetMeRequest::Make(this, {});
	AccountSubsystem->CPP_GetMe(UserSlot, MeReq, GetMeHandler, RequestContext, Op, this);
}

void UBeamRuntime::RunPostAuthenticationSetup_OnGetMe(FBasicAccountsGetMeFullResponse Response, FUserSlot UserSlot, FBeamOperationHandle Op)
{
	if (Response.State == RS_Success)
	{
		const auto GamerTag    = Response.SuccessData->Id;
		const auto Email       = Response.SuccessData->Email;
		const auto ExternalIds = Response.SuccessData->External;
		UserSlotSystem->SetGamerTagAtSlot(UserSlot, GamerTag, this);
		if (Email.IsSet) UserSlotSystem->SetEmailAtSlot(UserSlot, Email.Val, this);
		if (ExternalIds.IsSet) UserSlotSystem->SetExternalIdsAtSlot(UserSlot, ExternalIds.Val, this);

		FBeamRealmUser BeamRealmUser;
		if (UserSlotSystem->GetUserDataAtSlot(UserSlot, BeamRealmUser, this))
		{
			const FOnGetClientDefaultsFullResponse HandlerConfig = FOnGetClientDefaultsFullResponse::CreateUObject(this, &UBeamRuntime::RunPostAuthenticationSetup_PrepareNotificationService, UserSlot, BeamRealmUser, Op);

			UGetClientDefaultsRequest* GetClientDefaultsReq = UGetClientDefaultsRequest::Make(this, {});
			FBeamRequestContext        GetClientDefaultsCtx;
			GEngine->GetEngineSubsystem<UBeamRealmsApi>()->CPP_GetClientDefaults(GetClientDefaultsReq, HandlerConfig, GetClientDefaultsCtx, Op, this);
		}
		else
		{
			UserSlotSystem->ClearUserAtSlot(UserSlot, FailedAuthentication, true, this);
			RequestTrackerSystem->TriggerOperationError(Op, TEXT("Failed to find user data. This should never be seen."));
		}
	}
	else
	{
		UserSlotSystem->ClearUserAtSlot(UserSlot, FailedAuthentication, true, this);
		RequestTrackerSystem->TriggerOperationError(Op, Response.ErrorData.message);
	}
}

void UBeamRuntime::RunPostAuthenticationSetup_PrepareNotificationService(FGetClientDefaultsFullResponse Resp, FUserSlot UserSlot, FBeamRealmUser BeamRealmUser, FBeamOperationHandle Op)
{
	if (Resp.State == RS_Success)
	{
		FOnNotificationEvent ConnHandler = FOnNotificationEvent::CreateLambda([this, UserSlot, Op](const FNotificationEvent& Evt)
		{
			if (Evt.EventType == Connected)
			{
				UE_LOG(LogBeamNotifications, Display, TEXT("Connected to beamable notification service! SLOT=%s, EVT_TYPE=%s"), *UserSlot.Name, *StaticEnum<ENotificationMessageType>()->GetNameByValue(Evt.EventType).ToString())
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
				UE_LOG(LogBeamNotifications, Error, TEXT("Failed to connect to beamable's notification service! SLOT=%s, EVT_TYPE=%s"), *UserSlot.Name, *StaticEnum<ENotificationMessageType>()->GetNameByValue(Evt.EventType).ToString())
				UserSlotSystem->ClearUserAtSlot(UserSlot, FailedAuthentication, true, this);
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
		UserSlotSystem->ClearUserAtSlot(UserSlot, FailedAuthentication, true, this);
		RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
	}
}


void UBeamRuntime::LoginGuest(FUserSlot UserSlot, FBeamOperationHandle Op, FDelayedOperation OnBeforePostAuthentication)
{
	const UBeamAuthApi*               AuthSubsystem       = GEngine->GetEngineSubsystem<UBeamAuthApi>();
	const FOnAuthenticateFullResponse AuthenticateHandler = FOnAuthenticateFullResponse::CreateUObject(this, &UBeamRuntime::OnAuthenticated, UserSlot, Op, OnBeforePostAuthentication);

	UAuthenticateRequest* Req = NewObject<UAuthenticateRequest>(GetTransientPackage());
	Req->Body                 = NewObject<UTokenRequestWrapper>(Req);
	Req->Body->GrantType      = TEXT("guest");

	FBeamRequestContext RequestContext;
	AuthSubsystem->CPP_Authenticate(Req, AuthenticateHandler, RequestContext, Op);
}

void UBeamRuntime::CheckExternalIdentityAvailable(FString ExternalService, FString ExternalNamespace, FString ExternalUserId, FBeamOperationHandle Op, FOnGetAvailableExternalIdentityFullResponse Handler) const
{
	const auto AccountAPI = GEngine->GetEngineSubsystem<UBeamAccountsApi>();

	FBeamRequestContext                   Ctx;
	UGetAvailableExternalIdentityRequest* Req = UGetAvailableExternalIdentityRequest::Make(ExternalService, ExternalUserId, FOptionalString{ExternalNamespace}, GetTransientPackage(), {});
	AccountAPI->CPP_GetAvailableExternalIdentity(Req, Handler, Ctx, Op, this);
}

void UBeamRuntime::CheckEmailAvailable(FString Email, FBeamOperationHandle Op, FOnGetAvailableFullResponse Handler) const
{
	const auto AccountAPI = GEngine->GetEngineSubsystem<UBeamAccountsApi>();

	FBeamRequestContext   Ctx;
	UGetAvailableRequest* Req = UGetAvailableRequest::Make(Email, GetTransientPackage(), {});
	AccountAPI->CPP_GetAvailable(Req, Handler, Ctx, Op, this);
}

void UBeamRuntime::AttachIdentityToUser(FUserSlot UserSlot, FString ExternalService, FString ExternalNamespace, FString ExternalToken, FBeamOperationHandle Op, FOnPostExternalIdentityFullResponse Handler) const
{
	const auto AccountAPI = GEngine->GetEngineSubsystem<UBeamAccountsApi>();

	const auto          Req = UPostExternalIdentityRequest::Make(ExternalService, ExternalToken, {}, FOptionalString{ExternalNamespace}, GetTransientPackage(), {});
	FBeamRequestContext Ctx;
	AccountAPI->CPP_PostExternalIdentity(UserSlot, Req, Handler, Ctx, Op, this);
}

void UBeamRuntime::AttachEmailAndPasswordToUser(FUserSlot UserSlot, FString Email, FString Password, FBeamOperationHandle Op, FOnBasicAccountsPostRegisterFullResponse Handler) const
{
	const auto AccountAPI = GEngine->GetEngineSubsystem<UBeamAccountsApi>();

	const auto          Req = UBasicAccountsPostRegisterRequest::Make(Email, Password, GetTransientPackage(), {});
	FBeamRequestContext Ctx;
	AccountAPI->CPP_PostRegister(UserSlot, Req, Handler, Ctx, Op, this);
}

void UBeamRuntime::RemoveIdentityFromUser(FUserSlot UserSlot, FString ExternalService, FString ExternalNamespace, FString ExternalToken, FBeamOperationHandle Op, FOnDeleteExternalIdentityFullResponse Handler) const
{
	const auto AccountAPI = GEngine->GetEngineSubsystem<UBeamAccountsApi>();

	const auto          Req = UDeleteExternalIdentityRequest::Make(ExternalService, ExternalToken, FOptionalString{ExternalNamespace}, GetTransientPackage(), {});
	FBeamRequestContext Ctx;
	AccountAPI->CPP_DeleteExternalIdentity(UserSlot, Req, Handler, Ctx, Op, this);
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
	const FString Locale   = FPlatformMisc::GetDefaultLocale();
	const FString Device   = FPlatformMisc::GetLoginId();
	UE_LOG(LogBeamRuntime, Verbose, TEXT("PLATFORM = %s, LANGUAGE = %s, LOCALE = %s, DEVICE = %s"), *Platform, *Language, *Locale, *Device)

	Headers.Add(BEAM_SESSION_HEADER_PLATFORM, Platform);
	Headers.Add(BEAM_SESSION_HEADER_DEVICE, Device);
	Headers.Add(BEAM_SESSION_HEADER_SOURCE, TEXT(""));
	Headers.Add(BEAM_SESSION_HEADER_LOCALE, Locale);
	Headers.Add(BEAM_SESSION_HEADER_LANGUAGE, FString::Format(TEXT("{0},{1}"), {Locale, TEXT("ISO639")}));
}
#undef LOCTEXT_NAMESPACE
