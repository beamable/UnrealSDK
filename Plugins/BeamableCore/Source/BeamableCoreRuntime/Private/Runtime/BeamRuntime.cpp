// Fill out your copyright notice in the Description page of Project Settings.


#include "Runtime/BeamRuntime.h"

#include "BeamLogging.h"
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
	UserSlotSystem = GEngine->GetEngineSubsystem<UBeamUserSlots>();
	RequestTrackerSystem = GEngine->GetEngineSubsystem<UBeamRequestTracker>();

	UserSlotAuthenticatedHandler = UserSlotSystem->GlobalUserSlotAuthenticatedCodeHandler.AddUObject(
		this, &UBeamRuntime::OnUserSlotAuthenticated);
	UserSlotClearedHandler = UserSlotSystem->GlobalUserSlotClearedCodeHandler.AddUObject(
		this, &UBeamRuntime::OnUserSlotCleared);

	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UBeamRuntime::Initialize_DelayedInit);
	UE_LOG(LogBeamRuntime, Verbose, TEXT("Initializing UBeamRuntime Subsystem!"));

	// When running as a dedicated server instance, swap out the execute request delegate
	const auto ExecuteRequestImpl = GetGameInstance()->IsDedicatedServerInstance()
		                                ? GET_FUNCTION_NAME_CHECKED(UBeamBackend, DedicatedServerExecuteRequestImpl)
		                                : GET_FUNCTION_NAME_CHECKED(UBeamBackend, DefaultExecuteRequestImpl);
	const auto EngineSubsystem = GEngine->GetEngineSubsystem<UBeamBackend>();
	EngineSubsystem->ExecuteRequestDelegate.BindUFunction(EngineSubsystem, ExecuteRequestImpl);
}

void UBeamRuntime::Initialize_DelayedInit()
{
	const auto TargetRealm = GetDefault<UBeamCoreSettings>()->TargetRealm;

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
	}
	else
	{
		UE_LOG(LogBeamRuntime, Warning, TEXT("Starting configured Target Realm: CID=%s, PID=%s!"),
		       *TargetRealm.Cid.AsString, *TargetRealm.Pid.AsString);
		const auto RequestTracker = RequestTrackerSystem;
		if (const UWorld* World = GetWorld())
		{
			if (const UGameInstance* GameInstance = World->GetGameInstance())
			{
				const auto Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();

				InitializeAfterGameInstanceOps.Reset(Subsystems.Num());
				for (auto& Subsystem : Subsystems)
				{
					const auto Handle = Subsystem->InitializeWhenUnrealReady();
					InitializeAfterGameInstanceOps.Add(Handle);
				}

				OnInitializeAfterGameInstance = FOnWaitCompleteCode::CreateUObject(
					this, &UBeamRuntime::Initialize_OnRuntimeSubsystemsInitialized);
				OnInitializeAfterGameInstanceWait = RequestTracker->CPP_WaitAll(
					{}, InitializeAfterGameInstanceOps, {}, OnInitializeAfterGameInstance);
			}
		}
	}
}

void UBeamRuntime::Initialize_OnRuntimeSubsystemsInitialized(const TArray<FBeamRequestContext>&,
                                                             const TArray<TScriptInterface<IBeamBaseRequestInterface>>&,
                                                             const TArray<UObject*>&,
                                                             const TArray<FBeamErrorResponse>&)
{
	const auto bIsDedicatedServer = GetGameInstance()->IsDedicatedServerInstance();
	if (bIsDedicatedServer)
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
			RealmSecret = FGenericPlatformMisc::GetEnvironmentVariable(TEXT("BEAMABLE_REALM_SECRET"));
			checkf(!RealmSecret.IsEmpty(), TEXT("To run a dedicated server that communicates with Beamable, either:\n"
				       "- Start it with the command line \'-beamable-realm-secret <realm_secret>\'\n"
				       "- Start it in an environment with the EnvVar \'BEAMABLE_REALM_SECRET\' set to your realm secret.\n"
				       "To find your realm secret for your realms, look into your Project Settings => Editor => Beamable Editor => PerSlotDeveloperProjectData => All Realms\n"
				       "Remember to set this command line argument in your Networking settings for playmode in Editor Settings => Level Editor => Play => Multiplayer Options => Server => Additional Server Launch Parameters."
			       ))
		}
		GEngine->GetEngineSubsystem<UBeamBackend>()->RealmSecret = RealmSecret;

		// In dedicated servers, after we have set up the RealmSecret --- the UBeamRuntimeSubsystem's OnBeamableStarted gets called.
		// OnBeamableReady is never called in the server, as the server never authenticates via the UserSlot system.
		// This is not great semantics, but necessary while we don't have server tokens for authentication. 
		if (const UWorld* World = GetWorld())
		{
			if (const UGameInstance* GameInstance = World->GetGameInstance())
			{
				const auto Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();
				for (auto& Subsystem : Subsystems)
				{
					Subsystem->OnBeamableStarted();
				}
			}
		}
	}
	else
	{
		// Sign in automatically to the owner player slot.
		if (GetDefault<UBeamCoreSettings>()->bAutomaticFrictionlessAuthForOwnerPlayer)
		{
			const auto OwnerPlayerUserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();
			if (UserSlotSystem->TryLoadSavedUserAtSlot(OwnerPlayerUserSlot, this))
			{
				UE_LOG(LogBeamRuntime, Verbose, TEXT("Authenticated User at Slot! SLOT=%s"), *OwnerPlayerUserSlot.Name);
			}
			else
			{
				// If we are not already signed-into the first user slot and we are configured to automatically run auth, we run it. Otherwise, we call OnBeamableStarted on every runtime subsystem.
				// OnBeamableStarted basically means we are ready for authentication, but nothing else. And... that until you authenticate into the OwnerPlayer slot, OnBeamableReady functions will not run
				// on BeamableRuntimeSubsystems.
				if (!bDidBeamableRuntimeBoot)
				{
					CPP_AuthenticateFrictionlessOperation(OwnerPlayerUserSlot, {}, this);
				}
			}
		}
		else
		{
			// By default, only UserSlot at index 0 of RuntimeUserSlots always gets loaded. This actually only be called ONCE during the entire lifecycle of your program.
			if (const UWorld* World = GetWorld())
			{
				if (const UGameInstance* GameInstance = World->GetGameInstance())
				{
					const auto Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();
					for (auto& Subsystem : Subsystems)
					{
						Subsystem->OnBeamableStarted();
					}
				}
			}
		}
	}
}


void UBeamRuntime::OnUserSlotAuthenticated(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser,
                                           const UObject* Context)
{
	const auto RequestTracker = RequestTrackerSystem;

	if (!OnUserSignedInOps.Contains(UserSlot))
		OnUserSignedInOps.Add(UserSlot, {});

	if (!OnUserSignedInWaits.Contains(UserSlot))
		OnUserSignedInWaits.Add(UserSlot, {});

	if (!OnOnUserSignedIn.Contains(UserSlot))
		OnOnUserSignedIn.Add(UserSlot, {});

	auto& SignedInOps = *OnUserSignedInOps.Find(UserSlot);
	auto& SignedInOpsWait = *OnUserSignedInWaits.Find(UserSlot);
	auto& SignedInOpsHandler = *OnOnUserSignedIn.Find(UserSlot);

	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			const auto Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();

			SignedInOps.Reset(Subsystems.Num());
			for (auto& Subsystem : Subsystems)
			{
				const auto Handle = Subsystem->OnUserSignedIn(UserSlot, BeamRealmUser, !bDidBeamableRuntimeBoot);
				SignedInOps.Add(Handle);
			}

			SignedInOpsHandler = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::OnUserSlotAuthenticated_PostUserSignedIn, UserSlot, BeamRealmUser);
			SignedInOpsWait = RequestTracker->CPP_WaitAll({}, SignedInOps, {}, SignedInOpsHandler);
		}
	}
}

void UBeamRuntime::OnUserSlotAuthenticated_PostUserSignedIn(const TArray<FBeamRequestContext>&,
                                                            const TArray<TScriptInterface<IBeamBaseRequestInterface>>&,
                                                            const TArray<UObject*>&,
                                                            const TArray<FBeamErrorResponse>&, FUserSlot UserSlot,
                                                            FBeamRealmUser BeamRealmUser)
{
	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			const auto Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();
			for (auto& Subsystem : Subsystems)
			{
				Subsystem->OnPostUserSignedIn(UserSlot, BeamRealmUser);
			}
		}
	}

	// By default, only UserSlot at index 0 of RuntimeUserSlots always gets loaded. This actually only be called ONCE during the entire lifecycle of your program.
	if (!bDidBeamableRuntimeBoot && UserSlot.Name.Equals(GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot()))
	{
		if (const UWorld* World = GetWorld())
		{
			if (const UGameInstance* GameInstance = World->GetGameInstance())
			{
				const auto Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();
				for (auto& Subsystem : Subsystems)
				{
					Subsystem->OnBeamableReady();
				}
			}
		}
		bDidBeamableRuntimeBoot = true;
	}
}

void UBeamRuntime::OnUserSlotCleared(const EUserSlotClearedReason& Reason, const FUserSlot& UserSlot,
                                     const FBeamRealmUser& BeamRealmUser, const UObject* Context)
{
	const auto RequestTracker = RequestTrackerSystem;

	if (!OnUserSignedOutOps.Contains(UserSlot))
		OnUserSignedOutOps.Add(UserSlot, {});

	if (!OnUserSignedOutWaits.Contains(UserSlot))
		OnUserSignedOutWaits.Add(UserSlot, {});

	if (!OnOnUserSignedOut.Contains(UserSlot))
		OnOnUserSignedOut.Add(UserSlot, {});

	auto& SignedOutOps = *OnUserSignedOutOps.Find(UserSlot);
	auto& SignedOutOpsWait = *OnUserSignedOutWaits.Find(UserSlot);
	auto& SignedOutOpsHandler = *OnOnUserSignedOut.Find(UserSlot);

	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			const auto Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();

			SignedOutOps.Reset(Subsystems.Num());
			for (auto& Subsystem : Subsystems)
			{
				const auto Handle = Subsystem->OnUserSignedOut(UserSlot, Reason, BeamRealmUser);
				SignedOutOps.Add(Handle);
			}

			SignedOutOpsHandler = FOnWaitCompleteCode::CreateUObject(
				this, &UBeamRuntime::OnUserSlotCleared_PostUserSignedOut, UserSlot, Reason, BeamRealmUser);
			SignedOutOpsWait = RequestTracker->CPP_WaitAll({}, SignedOutOps, {}, SignedOutOpsHandler);
		}
	}
}

void UBeamRuntime::OnUserSlotCleared_PostUserSignedOut(const TArray<FBeamRequestContext>&,
                                                       const TArray<TScriptInterface<IBeamBaseRequestInterface>>&,
                                                       const TArray<UObject*>&,
                                                       const TArray<FBeamErrorResponse>&, FUserSlot UserSlot,
                                                       EUserSlotClearedReason Reason, FBeamRealmUser BeamRealmUser)
{
	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			const auto Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();
			for (auto& Subsystem : Subsystems)
			{
				Subsystem->OnPostUserSignedOut(UserSlot, Reason, BeamRealmUser);
			}
		}
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
	const auto ExecuteRequestImpl = GET_FUNCTION_NAME_CHECKED(UBeamBackend, DefaultExecuteRequestImpl);
	const auto EngineSubsystem = GEngine->GetEngineSubsystem<UBeamBackend>();
	EngineSubsystem->ExecuteRequestDelegate.BindUFunction(EngineSubsystem, ExecuteRequestImpl);
}

FBeamOperationHandle UBeamRuntime::AuthenticateFrictionlessOperation(FUserSlot UserSlot,
                                                                     FBeamOperationEventHandler OnOperationEvent,
                                                                     UObject* CallingContext)
{
	const auto Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                         OnOperationEvent, 2);
	AuthenticateFrictionless(UserSlot, Handle, CallingContext);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_AuthenticateFrictionlessOperation(
	FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, UObject* CallingContext)
{
	const auto Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                             OnOperationEvent, 2);
	AuthenticateFrictionless(UserSlot, Handle, CallingContext);
	return Handle;
}


void UBeamRuntime::AuthenticateFrictionless(FUserSlot UserSlot, FBeamOperationHandle Op, UObject* CallingContext)
{
	FBeamRealmUser RealmUser;

	// If we are already authenticated (we had a saved user in this slot), we simply broadcast this message out
	if (UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, CallingContext))
	{
		RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
	}
	else
	{
		UE_LOG(LogBeamRuntime, Verbose,
		       TEXT("Frictionless Auth - Not signed into slot! Starting Frictionless Auth process! SLOT=%s"),
		       *UserSlot.Name);

		FBeamRequestContext RequestContext;
		const auto AuthSubsystem = GEngine->GetEngineSubsystem<UBeamAuthApi>();
		const auto Req = NewObject<UAuthenticateRequest>(CallingContext);
		Req->Body = NewObject<UTokenRequestWrapper>(Req);
		Req->Body->GrantType = TEXT("guest");
		const auto AuthenticateHandler = FOnAuthenticateFullResponse::CreateUObject(
			this, &UBeamRuntime::AuthenticateFrictionless_OnAuthenticated, UserSlot, Op);
		AuthSubsystem->CPP_Authenticate(Req, AuthenticateHandler, RequestContext, Op);
	}
}

void UBeamRuntime::AuthenticateFrictionless_OnAuthenticated(FAuthenticateFullResponse Resp, FUserSlot UserSlot,
                                                            FBeamOperationHandle Op)
{
	if (Resp.State == Success)
	{
		const auto Token = Resp.SuccessData;
		UpdateAuthenticatedUserData(UserSlot, Token, Op);
	}
	else
	{
		RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
	}
}

FBeamOperationHandle UBeamRuntime::AuthenticateWithTokenOperation(FUserSlot UserSlot, UTokenResponse* TokenResponse, FBeamOperationEventHandler Handler, UObject* CallingContext)
{
	const auto Op = RequestTrackerSystem->BeginOperation({UserSlot}, GetName(), Handler);
	UpdateAuthenticatedUserData(UserSlot, TokenResponse, Op);
	return Op;
}

FBeamOperationHandle UBeamRuntime::CPP_AuthenticateWithTokenOperation(FUserSlot UserSlot, const UTokenResponse* TokenResponse, FBeamOperationEventHandlerCode Handler, UObject* CallingContext)
{
	const auto Op = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetName(), Handler);
	UpdateAuthenticatedUserData(UserSlot, TokenResponse, Op);
	return Op;
}

void UBeamRuntime::UpdateAuthenticatedUserData(FUserSlot UserSlot, const UTokenResponse* Token, FBeamOperationHandle Op)
{
	const auto Cid = GetDefault<UBeamCoreSettings>()->TargetRealm.Cid;
	const auto Pid = GetDefault<UBeamCoreSettings>()->TargetRealm.Pid;
	const auto AccessToken = Token->AccessToken.Val;
	const auto RefreshToken = Token->RefreshToken.Val;
	const auto ExpiresIn = Token->ExpiresIn;

	UserSlotSystem->SetAuthenticationDataAtSlot(UserSlot, AccessToken, RefreshToken, ExpiresIn, Cid, Pid, this);

	// Makes the GetMe request
	FBeamRequestContext RequestContext;
	const auto AccountSubsystem = GEngine->GetEngineSubsystem<UBeamAccountsApi>();
	const auto MeReq = NewObject<UBasicAccountsGetMeRequest>(this);
	const auto GetMeHandler = FOnBasicAccountsGetMeFullResponse::CreateUObject(
		this, &UBeamRuntime::UpdateAuthenticatedUserData_OnFetchAndUpdateGamerTag, UserSlot, Op);
	AccountSubsystem->CPP_GetMe(UserSlot, MeReq, GetMeHandler, RequestContext, Op, this);
}

void UBeamRuntime::UpdateAuthenticatedUserData_OnFetchAndUpdateGamerTag(FBasicAccountsGetMeFullResponse Response,
                                                                        FUserSlot UserSlot, FBeamOperationHandle Op)
{
	if (Response.State == Success)
	{
		const auto GamerTag = Response.SuccessData->Id;
		const auto Email = Response.SuccessData->Email;
		UserSlotSystem->SetGamerTagAtSlot(UserSlot, GamerTag, this);
		if (Email.IsSet) UserSlotSystem->SetEmailAtSlot(UserSlot, Email.Val, this);
		UserSlotSystem->SaveSlot(UserSlot, this);
		UserSlotSystem->TriggerUserAuthenticatedIntoSlot(UserSlot, this);
		RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
	}
	else
	{
		RequestTrackerSystem->TriggerOperationError(Op, Response.ErrorData.message);
	}
}
#undef LOCTEXT_NAMESPACE
