// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "RequestTracker/BeamOperation.h"
#include "RequestTracker/BeamOperationHandle.h"
#include "RequestTracker/BeamRequestTracker.h"
#include "UserSlots/BeamUserSlots.h"
#include "BeamRuntime.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRuntimeStateChangedEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRuntimeUserSlotAuthenticatedEvent, FUserSlot, UserSlot);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuntimeUserSlotClearedEvent, FUserSlot, UserSlot, EUserSlotClearedReason, ClearedReason);

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
	virtual void DelayedInitialize();

	/** Cleans up the system.  */
	virtual void Deinitialize() override;

	/**
	 * @brief Called after we authenticate to go fetch the users GamerTag. 
	 * @param UserSlot The user that we just authenticated and whose GamerTag we want to fetch.
	 * @param OnComplete What we'll do once we fetch or fail.
	 * @param CallingContext The calling Actor, World, Subsystem or Blueprint.
	 */
	void FetchAndUpdateGamerTag(FUserSlot UserSlot, FBeamOperationHandle Handle, UObject* CallingContext);

	/**
	 * @brief Stored lambda delegate handle for what this subsystem does when a user slot is authenticated.
	 */
	TMap<FUserSlot, FDelegateHandle> UserSlotAuthenticatedHandler;

	/**
	 * @brief Stored lambda delegate handle for what this subsystem does when a user slot is cleared.
	 */
	TMap<FUserSlot, FDelegateHandle> UserSlotClearedHandler;


protected:
	UPROPERTY()
	UBeamUserSlots* UserSlotSystem;

	UPROPERTY()
	UBeamRequestTracker* RequestTrackerSystem;


public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamRuntime* GetSelf(const UObject* CallingContext) { return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamRuntime>(); }

	UPROPERTY()
	const UBeamCoreSettings* CoreSettings;

	/**
	 * @brief Whenever a Runtime User Slot is authenticated successfully.
	 * Existing UBeamRuntimeSubsystems all subscribe to this during their initialization in order to know when they can start making requests to fetch the data that might be necessary for them.
	 * Each UBeamRuntimeSubsystems is responsible for defining when they're loaded data is ready for use and exposing them to blueprint.
	 * We provide no such guarantees here.
	 *
	 * Relevant info and guarantees:
	 *  - The Slot will be correctly authenticated and you can make authenticated requests with said FBeamRealmUser.
	 *  - There are no guarantees regarding the order of these events, so registered callbacks should not assume another callback will have ran. 
	 *  - Basically, each registered callback cannot depend on data retrieved by another callback.	 
	 */
	UPROPERTY()
	FRuntimeUserSlotAuthenticatedEvent OnRuntimeUserSlotAuthenticatedEvents;

	/**
	 * @brief Whenever a Runtime User Slot is cleared successfully.
	 * Existing UBeamRuntimeSubsystems all subscribe to this during their initialization in order to clean up data associated with that user slot.
	 *
	 * Relevant info and guarantees:
	 *  - The Slot will be cleared and you can no longer make authenticated requests with it.
	 *  - There are no guarantees regarding the order of these events, so registered callbacks should not assume another callback will have ran. 
	 *  - Basically, each registered callback cannot depend on data retrieved by another callback.	 
	 */
	UPROPERTY()
	FRuntimeUserSlotClearedEvent OnRuntimeUserSlotClearedEvent;

	/**
	 * @brief Callback that exposes to Blueprints an event that gets called as the last step in DelayedInitialize.
	 * At this point, BPs can query the UserSlot system and get valid FBeamRealmUsers.
	 * Here you are not guaranteed to have the data from UBeamRuntimeSubsystems available. For that, use that subsystem's own events.
	 *
	 * The main use for this is to kick off the frictionless auth flow from Blueprints.
	 * At the time this event is called all slots are guaranteed to be authenticated if there was a serialized authentication data stored locally.
	 * Therefore, if a slot is not auth'ed here it means there is no signed in user and we need to perform the Frictionless Auth flow.  
	 */
	UPROPERTY(BlueprintAssignable)
	FRuntimeStateChangedEvent OnInitialized;

	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Auth", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FrictionlessAuthentication(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, UObject* CallingContext = nullptr);
	void FetchAndUpdateAccountId(FUserSlot UserSlot, FBeamOperationHandle Handle, UObject* CallingContext);
};
