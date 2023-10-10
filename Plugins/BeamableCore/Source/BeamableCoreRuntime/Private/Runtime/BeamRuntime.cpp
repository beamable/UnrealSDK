// Fill out your copyright notice in the Description page of Project Settings.


#include "Runtime/BeamRuntime.h"

#include "BeamLogging.h"
#include "AutoGen/SubSystems/BeamRealmsApi.h"
#include "AutoGen/SubSystems/Realms/GetClientDefaultsRequest.h"
#include "BeamNotifications/BeamNotifications.h"
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

	UserSlotAuthenticatedHandler = UserSlotSystem->GlobalUserSlotAuthenticatedCodeHandler.AddUObject(this, &UBeamRuntime::OnUserSlotAuthenticated);
	UserSlotClearedHandler       = UserSlotSystem->GlobalUserSlotClearedCodeHandler.AddUObject(this, &UBeamRuntime::OnUserSlotCleared);

	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UBeamRuntime::Initialize_DelayedInit);
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

void UBeamRuntime::Initialize_DelayedInit()
{
	const FBeamRealmHandle TargetRealm = GetDefault<UBeamCoreSettings>()->TargetRealm;

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

				InitializeAfterGameInstanceOps.Reset(Subsystems.Num());
				for (auto& Subsystem : Subsystems)
				{
					const FBeamOperationHandle Handle = Subsystem->InitializeWhenUnrealReady();
					InitializeAfterGameInstanceOps.Add(Handle);
				}

				OnInitializeAfterGameInstance     = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::Initialize_OnRuntimeSubsystemsInitialized);
				OnInitializeAfterGameInstanceWait = RequestTracker->CPP_WaitAll({}, InitializeAfterGameInstanceOps, {}, OnInitializeAfterGameInstance);
			}
		}
	}
}

void UBeamRuntime::Initialize_OnRuntimeSubsystemsInitialized(const TArray<FBeamRequestContext>&,
                                                             const TArray<TScriptInterface<IBeamBaseRequestInterface>>&,
                                                             const TArray<UObject*>&,
                                                             const TArray<FBeamErrorResponse>&)
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
			RealmSecret = FGenericPlatformMisc::GetEnvironmentVariable(TEXT("BEAMABLE_REALM_SECRET"));
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
				const auto Handle = Subsystem->OnBeamableStarted();
				OnBeamableStartedOps.Add(Handle);
			}

			OnBeamableStartedHandler = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::Initialize_OnBeamableStartedFinished);
			OnBeamableStartedWait    = RequestTracker->CPP_WaitAll({}, OnBeamableStartedOps, {}, OnBeamableStartedHandler);
		}
	}
}

void UBeamRuntime::Initialize_OnBeamableStartedFinished(const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&, const TArray<FBeamErrorResponse>&)
{
	OnStarted.Broadcast();
	bIsBeamableStarted = true;

	// Sign in automatically to the owner player slot (if configured to do so).
	if (GetDefault<UBeamCoreSettings>()->bAutomaticFrictionlessAuthForOwnerPlayer)
	{
		const FUserSlot OwnerPlayerUserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();

		const int32 Result = UserSlotSystem->TryLoadSavedUserAtSlot(OwnerPlayerUserSlot, this);
		if (Result != UBeamUserSlots::LoadSavedUserResult_Failed)
		{
			// If expired, let's make a request to get a new token through the auto-refresh for expired tokens and then trigger the auth.
			if (Result == UBeamUserSlots::LoadSavedUserResult_ExpiredToken)
			{
				UBasicAccountsGetMeRequest*       MeReq = UBasicAccountsGetMeRequest::Make(GetTransientPackage());
				FOnBasicAccountsGetMeFullResponse Handler;

				Handler.BindLambda([this, OwnerPlayerUserSlot](const FBasicAccountsGetMeFullResponse& Resp)
				{
					if (Resp.State == EBeamFullResponseState::Success)
					{
						UserSlotSystem->TriggerUserAuthenticatedIntoSlot(OwnerPlayerUserSlot, this);
						UE_LOG(LogBeamRuntime, Display, TEXT("Authenticated User at Slot! SLOT=%s"), *OwnerPlayerUserSlot.Name);
					}
				});

				const UBeamAccountsApi* AccountsApi = GEngine->GetEngineSubsystem<UBeamAccountsApi>();
				FBeamRequestContext     Ctx;
				AccountsApi->CPP_GetMe(OwnerPlayerUserSlot, MeReq, Handler, Ctx, {}, this);
				UE_LOG(LogBeamRuntime, Display, TEXT("User at Slot has an expired token. Refreshing the token. SLOT=%s"), *OwnerPlayerUserSlot.Name);
			}

			// If we loaded and the token wasn't expired. Let's notify everyone that the user has been authenticated.
			if (Result == UBeamUserSlots::LoadSavedUserResult_Success)
			{
				UserSlotSystem->TriggerUserAuthenticatedIntoSlot(OwnerPlayerUserSlot, this);
				UE_LOG(LogBeamRuntime, Display, TEXT("Authenticated User at Slot! SLOT=%s"), *OwnerPlayerUserSlot.Name);
			}
		}
		else
		{
			// If we are not already signed-into the first user slot and we are configured to automatically run auth, we run it. 			
			if (!bIsOwnerPlayerAuthenticated)
			{
				CPP_AuthenticateFrictionlessOperation(OwnerPlayerUserSlot, {}, this);
			}
		}
	}
}


void UBeamRuntime::OnUserSlotAuthenticated(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context)
{
	// Before we call the OnPostUserSignedIn callback, let's connect to the websocket protocol
	const FOnGetClientDefaultsFullResponse HandlerConfig = FOnGetClientDefaultsFullResponse::CreateUObject(this, &UBeamRuntime::OnUserSlotAuthenticated_PrepareNotificationService, UserSlot, BeamRealmUser);

	UGetClientDefaultsRequest* GetClientDefaultsReq = UGetClientDefaultsRequest::Make(this);
	FBeamRequestContext        GetClientDefaultsCtx;
	GEngine->GetEngineSubsystem<UBeamRealmsApi>()->CPP_GetClientDefaults(GetClientDefaultsReq, HandlerConfig, GetClientDefaultsCtx, {}, this);
}


void UBeamRuntime::OnUserSlotAuthenticated_PrepareNotificationService(FGetClientDefaultsFullResponse Resp, FUserSlot UserSlot, FBeamRealmUser BeamRealmUser)
{
	if (Resp.State == Success)
	{
		FOnNotificationEvent ConnHandler;

		ConnHandler.BindLambda([this, UserSlot, BeamRealmUser](const FNotificationEvent& Evt)
		{
			if (Evt.EventType == Connected)
			{
				UE_LOG(LogBeamNotifications, Display, TEXT("Connected to beamable notification service! SLOT=%s, EVT_TYPE=%s"), *UserSlot.Name, *StaticEnum<ENotificationMessageType>()->GetNameByValue(Evt.EventType).ToString())
				DefaultNotificationChannels.Add(UserSlot, Evt.ConnectedData.ConnectedHandle);

				OnUserSlotAuthenticated_TriggerSubsystemOnUserSlotAuthenticated(UserSlot, BeamRealmUser);
			}
			else if (Evt.EventType == ConnectionFailed)
			{
				UE_LOG(LogBeamNotifications, Error, TEXT("Failed to connect to beamable's notification service! SLOT=%s, EVT_TYPE=%s"), *UserSlot.Name, *StaticEnum<ENotificationMessageType>()->GetNameByValue(Evt.EventType).ToString())
			}
		});

		UE_LOG(LogBeamNotifications, Warning, TEXT("WebSocket URI=%s, Setting=%s"), *Resp.SuccessData->WebsocketConfig->Uri.Val, *Resp.SuccessData->WebsocketConfig->Provider)
		const FString Uri = Resp.SuccessData->WebsocketConfig->Uri.Val / TEXT("connect");

		FBeamWebSocketHandle Handle;
		GEngine->GetEngineSubsystem<UBeamNotifications>()->Connect(UserSlot, BeamRealmUser, DefaultNotificationChannel, Uri, {}, ConnHandler, Handle, this->GetWorld());
	}
}

void UBeamRuntime::OnUserSlotAuthenticated_TriggerSubsystemOnUserSlotAuthenticated(FUserSlot UserSlot, FBeamRealmUser BeamRealmUser)
{
	const auto RequestTracker = RequestTrackerSystem;

	if (!OnUserSignedInOps.Contains(UserSlot))
		OnUserSignedInOps.Add(UserSlot, {});

	if (!OnUserSignedInWaits.Contains(UserSlot))
		OnUserSignedInWaits.Add(UserSlot, {});

	if (!OnOnUserSignedIn.Contains(UserSlot))
		OnOnUserSignedIn.Add(UserSlot, {});

	auto& SignedInOps        = *OnUserSignedInOps.Find(UserSlot);
	auto& SignedInOpsWait    = *OnUserSignedInWaits.Find(UserSlot);
	auto& SignedInOpsHandler = *OnOnUserSignedIn.Find(UserSlot);

	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			const auto Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();

			SignedInOps.Reset(Subsystems.Num());
			for (auto& Subsystem : Subsystems)
			{
				const auto Handle = Subsystem->OnUserSignedIn(UserSlot, BeamRealmUser, !bIsOwnerPlayerAuthenticated);
				SignedInOps.Add(Handle);
			}

			SignedInOpsHandler = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::OnUserSlotAuthenticated_PostUserSignIn, UserSlot, BeamRealmUser);
			SignedInOpsWait    = RequestTracker->CPP_WaitAll({}, SignedInOps, {}, SignedInOpsHandler);
		}
	}
}

void UBeamRuntime::OnUserSlotAuthenticated_PostUserSignIn(const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&, const TArray<FBeamErrorResponse>&, FUserSlot UserSlot, FBeamRealmUser BeamRealmUser)
{
	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			const TArray<UBeamRuntimeSubsystem*> Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();
			for (auto& Subsystem : Subsystems)
			{
				Subsystem->OnPostUserSignedIn(UserSlot, BeamRealmUser);
			}
		}
	}

	// By default, only UserSlot at index 0 of RuntimeUserSlots always gets loaded. This actually only be called ONCE during the entire lifecycle of your program.
	if (!bIsOwnerPlayerAuthenticated && UserSlot.Name.Equals(GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot()))
	{
		const auto RequestTracker = RequestTrackerSystem;
		if (const UWorld* World = GetWorld())
		{
			if (const UGameInstance* GameInstance = World->GetGameInstance())
			{
				const TArray<UBeamRuntimeSubsystem*> Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();

				OnBeamableReadyOps.Reset(Subsystems.Num());
				for (auto& Subsystem : Subsystems)
				{
					const FBeamOperationHandle Handle = Subsystem->OnBeamableReady();
					OnBeamableReadyOps.Add(Handle);
				}

				OnBeamableReadyWaitHandler = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::OnUserSlotAuthenticated_OnBeamableReady);
				OnBeamableReadyWait        = RequestTracker->CPP_WaitAll({}, OnBeamableReadyOps, {}, OnBeamableReadyWaitHandler);
			}
		}
		bIsOwnerPlayerAuthenticated = true;
	}
}

void UBeamRuntime::OnUserSlotAuthenticated_OnBeamableReady(const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&, const TArray<FBeamErrorResponse>&)
{
	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			const TArray<UBeamRuntimeSubsystem*> Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();
			for (auto& Subsystem : Subsystems)
				Subsystem->bIsReady = true;
		}
	}
	OnReady.Broadcast();
}

void UBeamRuntime::OnUserSlotCleared(const EUserSlotClearedReason& Reason, const FUserSlot&      UserSlot,
                                     const FBeamRealmUser&         BeamRealmUser, const UObject* Context)
{
	UBeamRequestTracker* RequestTracker = RequestTrackerSystem;

	if (!OnUserSignedOutOps.Contains(UserSlot))
		OnUserSignedOutOps.Add(UserSlot, {});

	if (!OnUserSignedOutWaits.Contains(UserSlot))
		OnUserSignedOutWaits.Add(UserSlot, {});

	if (!OnOnUserSignedOut.Contains(UserSlot))
		OnOnUserSignedOut.Add(UserSlot, {});

	FBeamWaitHandle&              SignedOutOpsWait    = *OnUserSignedOutWaits.Find(UserSlot);
	FOnWaitCompleteCode&          SignedOutOpsHandler = *OnOnUserSignedOut.Find(UserSlot);
	TArray<FBeamOperationHandle>& SignedOutOps        = *OnUserSignedOutOps.Find(UserSlot);

	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			const TArray<UBeamRuntimeSubsystem*> Subsystems = GameInstance->GetSubsystemArray<UBeamRuntimeSubsystem>();

			SignedOutOps.Reset(Subsystems.Num());
			for (auto& Subsystem : Subsystems)
			{
				const FBeamOperationHandle Handle = Subsystem->OnUserSignedOut(UserSlot, Reason, BeamRealmUser);
				SignedOutOps.Add(Handle);
			}

			SignedOutOpsHandler = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::OnUserSlotCleared_PostUserSignedOut, UserSlot, Reason, BeamRealmUser);
			SignedOutOpsWait    = RequestTracker->CPP_WaitAll({}, SignedOutOps, {}, SignedOutOpsHandler);
		}
	}
}

void UBeamRuntime::OnUserSlotCleared_PostUserSignedOut(const TArray<FBeamRequestContext>&,
                                                       const TArray<TScriptInterface<IBeamBaseRequestInterface>>&,
                                                       const TArray<UObject*>&,
                                                       const TArray<FBeamErrorResponse>&, FUserSlot UserSlot,
                                                       EUserSlotClearedReason                       Reason, FBeamRealmUser BeamRealmUser)
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


FBeamOperationHandle UBeamRuntime::AuthenticateFrictionlessOperation(FUserSlot                  UserSlot,
                                                                     FBeamOperationEventHandler OnOperationEvent,
                                                                     UObject*                   CallingContext)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                         OnOperationEvent, 2);
	AuthenticateFrictionless(UserSlot, Handle, CallingContext);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_AuthenticateFrictionlessOperation(
	FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, UObject* CallingContext)
{
	const FBeamOperationHandle Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
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


		const UBeamAuthApi*               AuthSubsystem       = GEngine->GetEngineSubsystem<UBeamAuthApi>();
		const FOnAuthenticateFullResponse AuthenticateHandler = FOnAuthenticateFullResponse::CreateUObject(this, &UBeamRuntime::AuthenticateFrictionless_OnAuthenticated, UserSlot, Op);

		UAuthenticateRequest* Req = NewObject<UAuthenticateRequest>(CallingContext);
		Req->Body                 = NewObject<UTokenRequestWrapper>(Req);
		Req->Body->GrantType      = TEXT("guest");

		FBeamRequestContext RequestContext;
		AuthSubsystem->CPP_Authenticate(Req, AuthenticateHandler, RequestContext, Op);
	}
}

void UBeamRuntime::AuthenticateFrictionless_OnAuthenticated(FAuthenticateFullResponse Resp, FUserSlot UserSlot,
                                                            FBeamOperationHandle      Op)
{
	if (Resp.State == Success)
	{
		const UTokenResponse* Token = Resp.SuccessData;
		UpdateAuthenticatedUserData(UserSlot, Token, Op);
	}
	else
	{
		RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
	}
}

FBeamOperationHandle UBeamRuntime::AuthenticateWithTokenOperation(FUserSlot UserSlot, UTokenResponse* TokenResponse, FBeamOperationEventHandler Handler, UObject* CallingContext)
{
	const FBeamOperationHandle Op = RequestTrackerSystem->BeginOperation({UserSlot}, GetName(), Handler);
	UpdateAuthenticatedUserData(UserSlot, TokenResponse, Op);
	return Op;
}

FBeamOperationHandle UBeamRuntime::CPP_AuthenticateWithTokenOperation(FUserSlot UserSlot, const UTokenResponse* TokenResponse, FBeamOperationEventHandlerCode Handler, UObject* CallingContext)
{
	const FBeamOperationHandle Op = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetName(), Handler);
	UpdateAuthenticatedUserData(UserSlot, TokenResponse, Op);
	return Op;
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

void UBeamRuntime::UpdateAuthenticatedUserData(FUserSlot UserSlot, const UTokenResponse* Token, FBeamOperationHandle Op)
{
	const FBeamCid Cid = GetDefault<UBeamCoreSettings>()->TargetRealm.Cid;
	const FBeamPid Pid = GetDefault<UBeamCoreSettings>()->TargetRealm.Pid;

	const FString AccessToken  = Token->AccessToken.Val;
	const FString RefreshToken = Token->RefreshToken.Val;
	const int64   ExpiresIn    = Token->ExpiresIn;

	UserSlotSystem->SetAuthenticationDataAtSlot(UserSlot, AccessToken, RefreshToken, FDateTime::UtcNow().ToUnixTimestamp(), ExpiresIn, Cid, Pid, this);

	// Makes the GetMe request
	FBeamRequestContext                     RequestContext;
	const UBeamAccountsApi*                 AccountSubsystem = GEngine->GetEngineSubsystem<UBeamAccountsApi>();
	const FOnBasicAccountsGetMeFullResponse GetMeHandler     = FOnBasicAccountsGetMeFullResponse::CreateUObject(this, &UBeamRuntime::UpdateAuthenticatedUserData_OnFetchAndUpdateGamerTag, UserSlot, Op);
	UBasicAccountsGetMeRequest*             MeReq            = NewObject<UBasicAccountsGetMeRequest>(this);
	AccountSubsystem->CPP_GetMe(UserSlot, MeReq, GetMeHandler, RequestContext, Op, this);
}

void UBeamRuntime::UpdateAuthenticatedUserData_OnFetchAndUpdateGamerTag(FBasicAccountsGetMeFullResponse Response,
                                                                        FUserSlot                       UserSlot, FBeamOperationHandle Op)
{
	if (Response.State == Success)
	{
		const auto GamerTag = Response.SuccessData->Id;
		const auto Email    = Response.SuccessData->Email;
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
