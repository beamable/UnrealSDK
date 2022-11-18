// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamRuntimeSettings.h"
#include "UObject/Object.h"
#include "Runtime/BeamRuntime.h"

#include "BeamRuntimeSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRuntimeUserSlotDataChangedEvent, FUserSlot, UserSlot);

UCLASS(Abstract, Blueprintable, meta=(IsBlueprintBase=true))
class BEAMABLECORERUNTIME_API UBeamRuntimeSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	/** @brief Initializes the subsystem.  */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Cleans up the system.  */
	virtual void Deinitialize() override;


	/**
	 * @brief Handle for the registered OnUserSlotAuthenticated binding to UBeamRuntime authenticated event.
	 */
	FDelegateHandle OnAuthenticatedUserHandle;

	/**
	 * @brief Handle for the registered OnUserSlotAuthenticated binding to UBeamRuntime cleared event.
	 */
	FDelegateHandle OnClearedUserHandle;


public:
	UPROPERTY()
	UBeamRuntime* Runtime;

	/**
	 * @brief You can check if the system has initialized all the user slots.
	 * During Widget construction, you can verify whether or not you have the initial data you need and decide whether or not to show a loading animation/pop-up (or whatever your UX is).
	 * If you are initialized, you can simply access the data and build up the UI. Otherwise, you can hook up to the OnInitialUserSlotDataReady event to modify the UI once its available.
	 * 
	 * @return Whether or not the system has all the data it fetches automatically whenever the given user becomes authenticated.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool IsInitialized(FUserSlot Slot) const;

	/**
	 * @brief You can use this instead of IsInitialized if:
	 *  - You have a single RuntimeUserSlot.
	 *  - You have multiple RuntimeUserSlot and want to see if all of them have their data ready.
	 *  
	 * @return Whether or not the system has all the data it fetches automatically for all RuntimeUserSlots.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool AreAllInitialized() const;

	/**
	 * @brief Callback that gets called whenever the initial data associated with a user slot for this subsystem is ready for use.
	 * Initial data meaning data we know we'll need so we ask for it and cache it.
	 * 
	 * Implementations of this subsystem should trigger this in two points by calling TriggerOnInitialUserSlotDataReady:
	 *   - If we are loading locally cached data, we should trigger this after we load it up.
	 *   - If we are requesting data and updating our state, we should trigger this after we correctly put it up.
	 *
	 * The main use for this is to provide a hook that specific meta-game UIs that rely on the data in these systems can safely hook into for their initialization.
	 * At the time this event is called all slots are guaranteed to be authenticated if there was a serialized authentication data stored locally.
	 * Therefore, if a slot is not auth'ed here it means there is no signed in user and we need to perform the Frictionless Auth flow.  
	 */
	UPROPERTY(BlueprintAssignable, Category="Beam")
	FRuntimeUserSlotDataChangedEvent OnInitialUserSlotDataReady;

	/**
	 * @brief Callback that gets called whenever the initial data for ALL runtime user slots becomes available. Always invoked after OnInitialUserSlotDataReady.
	 *
	 * The main use for this is for cases where you have UI that relies on data of more than one RuntimeUserSlot and the UI can't work without the data for all of them.
	 * Ex: In a local co-op gameplay, imagine an "Item Trade system" and UI for trading. 
	 */
	UPROPERTY(BlueprintAssignable, Category="Beam")
	FRuntimeStateChangedEvent OnAllInitialUserSlotDataReady;

protected:
	/**
	 * @brief Whether or not the data for each individual user slot is initialized.
	 */
	TMap<FUserSlot, bool> UserSlotInitialDataLoaded;

	/**
	 * @brief Called whenever UBeamRuntime is fully initialized. You can think of this as OnBeginPlay, but for use with Beamable.
	 */
	UFUNCTION(BlueprintNativeEvent)
	void OnBeamableReady();	
	
	/**
	 * @brief Called whenever a RuntimeUserSlot is authenticated by UBeamRuntime.
	 *
	 * Implementations of this subsystem should make requests to fetch data we know will be needed by the users and organize them in useful ways.
	 * Once this data is readily available and organized, it should call TriggerOnInitialUserSlotDataReady to notify Widgets that the data is good to go.
	 * 
	 * @param UserSlot The slot that was authenticated.
	 */
	UFUNCTION(BlueprintNativeEvent)
	void OnUserSlotAuthenticated(FUserSlot UserSlot);

	/**
	 * @brief Called whenever a RuntimeUserSlot is cleared by UBeamRuntime.
	 * @param UserSlot The slot that was authenticated.
	 * @param ClearedReason If the slot was cleared due to a failure to re-auth or not.
	 */
	UFUNCTION(BlueprintNativeEvent)
	void OnUserSlotCleared(FUserSlot UserSlot, EUserSlotClearedReason ClearedReason);

	
	
	
	/**
	 * @brief Implementations of this class must call this function whenever their initial data is fetched, be it from a local point or from remote endpoints.
	 * @param Slot The user slot whose data was just fetched/loaded.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void TriggerOnInitialUserSlotDataReady(FUserSlot Slot);
};


/**
 * @brief Used to initialize all Blueprint-first subsystems that we make. See the link below for more info on why this is needed.
 * 
 * https://forums.unrealengine.com/t/configuring-subsystems-via-editor/134784/20
 */
UCLASS(Hidden)
class BEAMABLECORERUNTIME_API UBeamRuntimeBlueprintSubsystems : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	/** @brief Initializes the subsystem.  */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		Super::Initialize(Collection);
		const auto RuntimeSettings = GetDefault<UBeamRuntimeSettings>();
		for (const auto SubsystemBlueprint : RuntimeSettings->BeamRuntimeSubsystemBlueprints)
		{
			Collection.InitializeDependency(SubsystemBlueprint);
		}
	}

	/** Cleans up the system.  */
	virtual void Deinitialize() override
	{
		Super::Deinitialize();
	}
};
