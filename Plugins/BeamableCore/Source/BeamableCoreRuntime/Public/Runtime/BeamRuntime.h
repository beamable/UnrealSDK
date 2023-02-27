// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/SubSystems/BeamAccountsApi.h"
#include "AutoGen/SubSystems/BeamAuthApi.h"

#include "RequestTracker/BeamOperation.h"
#include "RequestTracker/BeamOperationHandle.h"
#include "RequestTracker/BeamRequestTracker.h"
#include "UserSlots/BeamUserSlots.h"
#include "BeamRuntime.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRuntimeStateChangedEvent);

/**
 * 
 */
UCLASS(BlueprintType, meta=(Namespace="Beam"))
class BEAMABLECORERUNTIME_API UBeamRuntime : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	/** @brief Initializes the subsystem.  */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/**
	 * @brief This gets called the frame after all the subsystem initializations have happened.
	 * This enables all subsystems to have a chance to subscribe to BeamRuntime events should they choose to do so.
	 * This is handled automatically for by all UBeamRuntimeSubsystems.
	 */
	virtual void Initialize_DelayedInit();

	/**
	 * @brief This gets called after all runtime systems had the opportunity to get ready for authentication to happen.
	 */
	void Initialize_OnRuntimeSubsystemsInitialized(const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&,
	                                               const TArray<FBeamErrorResponse>&);


	/**
	 * @brief Callback added to the UserSlot global callback so that we can respond to users signing in. 
	 */
	void OnUserSlotAuthenticated(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context);

	/**
	 * @brief After all subsystems have finished their respective handling of UserSlot sign-in, we give them all a chance to respond to that. 
	 */
	void OnUserSlotAuthenticated_PostUserSignedIn(const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&,
	                                              const TArray<FBeamErrorResponse>&, FUserSlot UserSlot, FBeamRealmUser BeamRealmUser);

	/**
	 * @brief Callback added to the UserSlot global callback so that we can respond to users signing out. 
	 */
	UFUNCTION()
	void OnUserSlotCleared(const EUserSlotClearedReason& Reason, const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context);

	/**
	 * @brief After all subsystems have finished their respective handling of UserSlot sign-out, we give them all a chance to respond to that. 
	 */
	void OnUserSlotCleared_PostUserSignedOut(const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&,
	                                         const TArray<FBeamErrorResponse>&, FUserSlot UserSlot, EUserSlotClearedReason Reason, FBeamRealmUser BeamRealmUser);

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
	 * @brief When we boot up the game instance (and it's subsystems), after all Initialize calls have finished, we allow BeamSubsystems to kick-off operations in parallel.
	 * They return operation handles that we wait on. When done, these subsystems are be ready to make unauthenticated requests to the Beamable backend.
	 */
	TArray<FBeamOperationHandle> InitializeAfterGameInstanceOps = {};
	FBeamWaitHandle OnInitializeAfterGameInstanceWait;
	FOnWaitCompleteCode OnInitializeAfterGameInstance;


	/**
	 * @brief Every time a user signs into beamable, we give each subsystem the ability to run an operation for that user.
	 * We also give them the list of currently authenticated UserSlots (so that they can tell if the user that just signed in is the last one for example).
	 */
	TMap<FUserSlot, TArray<FBeamOperationHandle>> OnUserSignedInOps = {};
	TMap<FUserSlot, FBeamWaitHandle> OnUserSignedInWaits;
	TMap<FUserSlot, FOnWaitCompleteCode> OnOnUserSignedIn;

	/**
	 * @brief Every time a user signs out of beamable we give each subsystem the ability to run an operation for that user.
	 * We also give them the list of currently authenticated User Slots and the reason for the sign out so that they can correctly decide what to do in each instance.
	 */
	TMap<FUserSlot, TArray<FBeamOperationHandle>> OnUserSignedOutOps = {};
	TMap<FUserSlot, FBeamWaitHandle> OnUserSignedOutWaits;
	TMap<FUserSlot, FOnWaitCompleteCode> OnOnUserSignedOut;

	/**
	 * @brief This flag is used for beamable's automatic initialization. It ensures that the OnBeamableReady event is only ever called once in one of two moments after the game boots up:
	 *  - If UserSlot at index 0 is signed in already, we wait for it's authentication flow to finish and then call it.
	 *  - If UserSlot at index 0 is NOT signed in already, we call it during DelayedInitialize (for now, we assume this is the "owner" player of the game -- player 1).
	 *
	 *  BeamRuntimeSubsystems can implement their OnBeamableReady event to: either set up UIs or kick-off operations to fetch data (and let the UIs poll whatever subsystems
	 *  they need to be ready).
	 *	  
	 */
	bool bDidBeamableRuntimeBoot = false;

public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamRuntime* GetSelf(const UObject* CallingContext) { return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamRuntime>(); }

	UPROPERTY()
	UBeamUserSlots* UserSlotSystem;

	UPROPERTY()
	UBeamRequestTracker* RequestTrackerSystem;

	/**
	 * @brief An operation that will authenticate a user with the beamable and persist that authentication locally.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Auth", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle AuthenticateFrictionlessOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, UObject* CallingContext = nullptr);

	/**
	 * @brief An operation that will authenticate a user with the beamable and persist that authentication locally.
	 */
	FBeamOperationHandle CPP_AuthenticateFrictionlessOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, UObject* CallingContext = nullptr);

	// Operation Implementations
private:
	void AuthenticateFrictionless(FUserSlot UserSlot, FBeamOperationHandle Op, UObject* CallingContext);
	void AuthenticateFrictionless_OnAuthenticated(FAuthenticateFullResponse Resp, FUserSlot UserSlot, FBeamOperationHandle Op);
	void UpdateAuthenticatedUserData(FUserSlot UserSlot, FString AccessToken, FString RefreshToken, int64 ExpiresIn, FBeamCid Cid, FBeamPid Pid, FBeamOperationHandle Op);
	void UpdateAuthenticatedUserData_OnFetchAndUpdateGamerTag(FBasicAccountsGetMeFullResponse Response, FUserSlot UserSlot, FBeamOperationHandle Op);
};
