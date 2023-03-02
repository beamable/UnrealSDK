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
	RequestTrackerSystem =  GEngine->GetEngineSubsystem<UBeamRequestTracker>();

	UserSlotAuthenticatedHandler = UserSlotSystem->GlobalUserSlotAuthenticatedCodeHandler.AddUObject(this, &UBeamRuntime::OnUserSlotAuthenticated);
	UserSlotClearedHandler = UserSlotSystem->GlobalUserSlotClearedCodeHandler.AddUObject(this, &UBeamRuntime::OnUserSlotCleared);

	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UBeamRuntime::Initialize_DelayedInit);
	UE_LOG(LogBeamRuntime, Verbose, TEXT("Initializing UBeamRuntime Subsystem!"));
}

void UBeamRuntime::Initialize_DelayedInit()
{	
	const auto TargetRealm = GetDefault<UBeamCoreSettings>()->TargetRealm;

	if (TargetRealm.Cid.AsLong == -1 || TargetRealm.Pid.AsString.IsEmpty())
	{
#if WITH_EDITOR
		UE_LOG(LogBeamRuntime, Error, TEXT("Cannot start beamable with no configured Target Realm!"));
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
		//Creates a new notification info, we pass in our text as the parameter.
		FNotificationInfo Info(LOCTEXT("Notification_NoTargetRealmConfigured", "No Target Realm configured!"));
		//Set a default expire duration
		Info.ExpireDuration = 5.0f;
		Info.Image = FCoreStyle::Get().GetBrush(TEXT("MessageLog.Error"));
		FSlateNotificationManager::Get().AddNotification(Info);
#else
		checkf(false, TEXT("Builds with Beamable cannot exist without a configured target realm!"))
#endif
	}
	else
	{
		UE_LOG(LogBeamRuntime, Warning, TEXT("Starting configured Target Realm: CID=%s, PID=%s!"), *TargetRealm.Cid.AsString, *TargetRealm.Pid.AsString);
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

				OnInitializeAfterGameInstance = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::Initialize_OnRuntimeSubsystemsInitialized);
				OnInitializeAfterGameInstanceWait = RequestTracker->CPP_WaitAll({}, InitializeAfterGameInstanceOps, {}, OnInitializeAfterGameInstance);
			}
		}
	}
}

void UBeamRuntime::Initialize_OnRuntimeSubsystemsInitialized(const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&,
                                                             const TArray<FBeamErrorResponse>&)
{
	// TODO: Expose configurations in core settings about which UserSlots should we try to sign in automatically.
	// INFO: By default (and, for now), only UserSlot at index 0 of RuntimeUserSlots always gets loaded.		
	const auto UserSlot = GetDefault<UBeamCoreSettings>()->RuntimeUserSlots[0];
	if (UserSlotSystem->TryLoadSavedUserAtSlot(UserSlot, this))
	{
		UE_LOG(LogBeamRuntime, Verbose, TEXT("Authenticated User at Slot! SLOT=%s"), *UserSlot);
	}
	else
	{
		// If we are not already signed-into the first user slot, we simply let all of our BeamRuntimeSubsystems know that we are ready. 
		if (!bDidBeamableRuntimeBoot)
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
}


void UBeamRuntime::OnUserSlotAuthenticated(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context)
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
				const auto Handle = Subsystem->OnUserSignedIn(UserSlot, BeamRealmUser);
				SignedInOps.Add(Handle);
			}

			SignedInOpsHandler = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::OnUserSlotAuthenticated_PostUserSignedIn, UserSlot, BeamRealmUser);
			SignedInOpsWait = RequestTracker->CPP_WaitAll({}, SignedInOps, {}, SignedInOpsHandler);
		}
	}
}

void UBeamRuntime::OnUserSlotAuthenticated_PostUserSignedIn(const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&,
                                                            const TArray<FBeamErrorResponse>&, FUserSlot UserSlot, FBeamRealmUser BeamRealmUser)
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

	// TODO: Expose configurations in core settings about which UserSlots should we try to sign in automatically.
	// INFO: By default (and, for now), only UserSlot at index 0 of RuntimeUserSlots always gets loaded.
	// INFO: This will actually only be called ONCE
	if (!bDidBeamableRuntimeBoot && UserSlot.Name.Equals(GetDefault<UBeamCoreSettings>()->RuntimeUserSlots[0]))
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

void UBeamRuntime::OnUserSlotCleared(const EUserSlotClearedReason& Reason, const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context)
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

			SignedOutOpsHandler = FOnWaitCompleteCode::CreateUObject(this, &UBeamRuntime::OnUserSlotCleared_PostUserSignedOut, UserSlot, Reason, BeamRealmUser);
			SignedOutOpsWait = RequestTracker->CPP_WaitAll({}, SignedOutOps, {}, SignedOutOpsHandler);
		}
	}
}

void UBeamRuntime::OnUserSlotCleared_PostUserSignedOut(const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&,
                                                       const TArray<FBeamErrorResponse>&, FUserSlot UserSlot, EUserSlotClearedReason Reason, FBeamRealmUser BeamRealmUser)
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
}

FBeamOperationHandle UBeamRuntime::AuthenticateFrictionlessOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, UObject* CallingContext)
{
	const auto Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent, 2);
	AuthenticateFrictionless(UserSlot, Handle, CallingContext);
	return Handle;
}

FBeamOperationHandle UBeamRuntime::CPP_AuthenticateFrictionlessOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, UObject* CallingContext)
{
	const auto Handle = RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent, 2);
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
		UE_LOG(LogBeamRuntime, Verbose, TEXT("Frictionless Auth - Not signed into slot! Starting Frictionless Auth process! SLOT=%s"), *UserSlot.Name);

		FBeamRequestContext RequestContext;
		const auto AuthSubsystem = GEngine->GetEngineSubsystem<UBeamAuthApi>();
		const auto Req = NewObject<UAuthenticateRequest>(CallingContext);
		Req->Body = NewObject<UTokenRequestWrapper>(Req);
		Req->Body->GrantType = TEXT("guest");
		const auto AuthenticateHandler = FOnAuthenticateFullResponse::CreateUObject(this, &UBeamRuntime::AuthenticateFrictionless_OnAuthenticated, UserSlot, Op);
		AuthSubsystem->CPP_Authenticate(Req, AuthenticateHandler, RequestContext, Op);
	}
}

void UBeamRuntime::AuthenticateFrictionless_OnAuthenticated(FAuthenticateFullResponse Resp, FUserSlot UserSlot, FBeamOperationHandle Op)
{
	if (Resp.State == Success)
	{
		const auto Token = Resp.SuccessData;

		const auto Cid = GetDefault<UBeamCoreSettings>()->TargetRealm.Cid;
		const auto Pid = GetDefault<UBeamCoreSettings>()->TargetRealm.Pid;
		const auto AccessToken = Token->AccessToken.Val;
		const auto RefreshToken = Token->RefreshToken.Val;
		const auto ExpiresIn = Token->ExpiresIn;

		UpdateAuthenticatedUserData(UserSlot, AccessToken, RefreshToken, ExpiresIn, Cid, Pid, Op);
	}
	else
	{
		RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
	}
}

void UBeamRuntime::UpdateAuthenticatedUserData(FUserSlot UserSlot, FString AccessToken, FString RefreshToken, int64 ExpiresIn, FBeamCid Cid, FBeamPid Pid, FBeamOperationHandle Op)
{
	UserSlotSystem->SetAuthenticationDataAtSlot(UserSlot, AccessToken, RefreshToken, ExpiresIn, Cid, Pid, this);

	// Makes the GetMe request
	FBeamRequestContext RequestContext;
	const auto AccountSubsystem = GEngine->GetEngineSubsystem<UBeamAccountsApi>();
	const auto MeReq = NewObject<UBasicAccountsGetMeRequest>(this);
	const auto GetMeHandler = FOnBasicAccountsGetMeFullResponse::CreateUObject(this, &UBeamRuntime::UpdateAuthenticatedUserData_OnFetchAndUpdateGamerTag, UserSlot, Op);
	AccountSubsystem->CPP_GetMe(UserSlot, MeReq, GetMeHandler, RequestContext, Op, this);
}

void UBeamRuntime::UpdateAuthenticatedUserData_OnFetchAndUpdateGamerTag(FBasicAccountsGetMeFullResponse Response, FUserSlot UserSlot, FBeamOperationHandle Op)
{
	if (Response.State == Success)
	{
		const auto GamerTag = Response.SuccessData->Id;
		UserSlotSystem->SetGamerTagAtSlot(UserSlot, GamerTag, this);
		UserSlotSystem->SaveSlot(UserSlot, this);
		RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
	}
	else
	{
		RequestTrackerSystem->TriggerOperationError(Op, Response.ErrorData.message);
	}
}
#undef LOCTEXT_NAMESPACE
