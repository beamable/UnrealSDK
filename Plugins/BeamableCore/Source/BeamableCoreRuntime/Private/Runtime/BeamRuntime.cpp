// Fill out your copyright notice in the Description page of Project Settings.


#include "Runtime/BeamRuntime.h"

#include "BeamLogging.h"
#include "AutoGen/SubSystems/BeamAccountsApi.h"
#include "AutoGen/SubSystems/BeamAuthApi.h"


void UBeamRuntime::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogBeamRuntime, Verbose, TEXT("Initializing UBeamRuntime Subsystem!"));

	// Set us up to handle sign-in/out flows in editor as well as tracking multiple developer user slots.
	CoreSettings = GetDefault<UBeamCoreSettings>();
	UserSlotSystem = GEngine->GetEngineSubsystem<UBeamUserSlots>();
	RequestTrackerSystem = GEngine->GetEngineSubsystem<UBeamRequestTracker>();

	for (const auto& SlotName : CoreSettings->RuntimeUserSlots)
	{
		const FUserSlot Slot = SlotName;

		UserSlotAuthenticatedHandler.Add(Slot, UserSlotSystem->GlobalUserSlotAuthenticatedCodeHandler.AddLambda([this, Slot]
		                                 (const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context)
			                                 {
				                                 if (Slot.Equals(UserSlot))
				                                 {
					                                 UE_LOG(LogBeamRuntime, Verbose, TEXT("Running callback  User at Slot! SLOT=%s"), *UserSlot.Name);

					                                 // If we are bound...
					                                 if (OnRuntimeUserSlotAuthenticatedEvents.IsBound())
						                                 OnRuntimeUserSlotAuthenticatedEvents.Broadcast(Slot);
				                                 }
			                                 }));

		UserSlotClearedHandler.Add(Slot, UserSlotSystem->GlobalUserSlotClearedCodeHandler.AddLambda([this, Slot]
		                           (const EUserSlotClearedReason Reason, const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context)
			                           {
				                           if (Slot.Equals(UserSlot))
				                           {
					                           UE_LOG(LogBeamRuntime, Verbose, TEXT("User cleared from Slot! SLOT=%s"), *UserSlot.Name);
					                           if (OnRuntimeUserSlotClearedEvent.IsBound())
						                           OnRuntimeUserSlotClearedEvent.Broadcast(Slot, Reason);
				                           }
			                           }));
	}

	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UBeamRuntime::DelayedInitialize);
}

void UBeamRuntime::DelayedInitialize()
{
	// We try to load the Saved User Slots
	for (const auto& SlotName : CoreSettings->RuntimeUserSlots)
	{
		const FUserSlot UserSlot = SlotName;
		if (UserSlotSystem->TryLoadSavedUserAtSlot(UserSlot, this))
		{
			UE_LOG(LogBeamRuntime, Verbose, TEXT("Authenticated User at Slot! SLOT=%s"), *UserSlot.Name);
		}
	}
	OnInitialized.Broadcast();
}

void UBeamRuntime::Deinitialize()
{
	Super::Deinitialize();
	for (const auto& Handler : UserSlotAuthenticatedHandler)
	{
		UserSlotSystem->GlobalUserSlotAuthenticatedCodeHandler.Remove(Handler.Value);
	}

	for (const auto& Handler : UserSlotClearedHandler)
	{
		UserSlotSystem->GlobalUserSlotClearedCodeHandler.Remove(Handler.Value);
	}

	for (const auto& SlotName : CoreSettings->RuntimeUserSlots)
	{
		UserSlotSystem->ClearUserAtSlot(SlotName, ExitPIE, false, this);
	}
}

FBeamOperationHandle UBeamRuntime::FrictionlessAuthentication(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, UObject* CallingContext)
{
	const auto Handle = RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent, 2);
	FBeamRealmUser RealmUser;

	// If we are already authenticated (we had a saved user in this slot), we simply broadcast this message out
	if (UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, CallingContext))
	{
		RequestTrackerSystem->TriggerOperationSuccess(Handle, TEXT(""));
	}
	else
	{
		UE_LOG(LogBeamRuntime, Verbose, TEXT("Frictionless Auth - Not signed into slot! Starting Frictionless Auth process! SLOT=%s"), *UserSlot.Name);

		const auto AuthSubsystem = GEngine->GetEngineSubsystem<UBeamAuthApi>();
		const auto Req = NewObject<UAuthenticateRequest>(CallingContext);
		Req->Body = NewObject<UTokenRequestWrapper>(Req);
		Req->Body->GrantType = TEXT("guest");

		const auto AuthenticateHandler = FOnAuthenticateFullResponse::CreateLambda([this, UserSlot, OnOperationEvent, CallingContext, Handle](FAuthenticateFullResponse Resp)
		{
			if (Resp.State == Success)
			{
				const auto Token = Resp.SuccessData;

				const auto Cid = GetDefault<UBeamCoreSettings>()->TargetRealm.Cid;
				const auto Pid = GetDefault<UBeamCoreSettings>()->TargetRealm.Pid;

				UserSlotSystem->SetAuthenticationDataAtSlot(UserSlot, Token->AccessToken.Val, Token->RefreshToken.Val, Token->ExpiresIn, Cid, Pid, CallingContext);
				UE_LOG(LogBeamRuntime, Verbose, TEXT("Auth - Authenticated... now grabbing account id! SLOT=%s"), *UserSlot.Name);

				FetchAndUpdateAccountId(UserSlot, Handle, CallingContext);
			}
			else
			{
				RequestTrackerSystem->TriggerOperationError(Handle, Resp.ErrorData.message);				
			}
		});
		FBeamRequestContext RequestContext;
		AuthSubsystem->CPP_Authenticate(Req, AuthenticateHandler, RequestContext, Handle);
	}

	return Handle;
}

void UBeamRuntime::FetchAndUpdateAccountId(FUserSlot UserSlot, FBeamOperationHandle Handle, UObject* CallingContext = nullptr)
{
	const auto AccountSubsystem = GEngine->GetEngineSubsystem<UBeamAccountsApi>();
	const auto MeReq = NewObject<UBasicAccountsGetMeRequest>(CallingContext);

	const auto GetMeHandler = FOnBasicAccountsGetMeFullResponse::CreateLambda([this, UserSlot, CallingContext, Handle](FBasicAccountsGetMeFullResponse Resp)
	{
		if (Resp.State == Success)
		{
			const auto GamerTag = Resp.SuccessData->Id;
			UserSlotSystem->SetGamerTagAtSlot(UserSlot, GamerTag, CallingContext);
			UserSlotSystem->SaveSlot(UserSlot, CallingContext);
			RequestTrackerSystem->TriggerOperationSuccess(Handle, TEXT(""));
		}
		else
		{
			RequestTrackerSystem->TriggerOperationError(Handle, Resp.ErrorData.message);			
		}
	});
	FBeamRequestContext RequestContext;
	AccountSubsystem->CPP_GetMe(UserSlot, MeReq, GetMeHandler, RequestContext, Handle, CallingContext);
}
