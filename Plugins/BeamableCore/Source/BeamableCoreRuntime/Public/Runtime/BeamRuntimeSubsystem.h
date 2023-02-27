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
	 * @brief This is just a flag that informs the caller on whether or not this specific subsystem has finished it's initialization flow.
	 * This should never be set before OnBeamableReady has been called. This may be called at some later point if this subsystem's initialization flow needs to kick-off Operations
	 * on OnBeamableReady in order to get ready for use.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsInitialized = false;

	UFUNCTION(Category="Beam")
	virtual FBeamOperationHandle InitializeWhenUnrealReady();

	/**
	 * @brief Called whenever a user authenticates into a user slot.
	 * The returned operation is added to a list of operations containing all other subsystem's OnUserSignedIn operation.
	 * We wait for this list of operations to finish and then call OnPostUserSignedIn.
	 */
	FBeamOperationHandle OnUserSignedIn(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser);
	/**
	 * @brief Called whenever a user signs out of a user slot.
	 * The returned operation is added to a list of operations containing all other subsystem's OnUserSignedOut operation.
	 * We wait for this list of operations to finish and then call OnPostUserSignedOut.
	 */
	FBeamOperationHandle OnUserSignedOut(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser);

	/**
	 * @brief Called on each BeamRuntimeSubsystem after the OnUserSignedIn operations of ALL BeamRuntimeSubsystems have run to completion (success or otherwise). 
	 */
	UFUNCTION(BlueprintNativeEvent)
	void OnPostUserSignedIn(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser);

	/**
	 * @brief Called on each BeamRuntimeSubsystem after the OnUserSignedOut operations of ALL BeamRuntimeSubsystems have run to completion (success or otherwise). 
	 */
	UFUNCTION(BlueprintNativeEvent)
	void OnPostUserSignedOut(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser);

	/**
	 * @brief Called whenever UBeamRuntime is fully initialized. You can think of this as OnBeginPlay, but for use with Beamable.
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnBeamableReady();
	void OnBeamableReady_Implementation();
};


/**
 * @brief Used to initialize all Blueprint-first subsystems that we make. See the link below for more info on why this is needed.
 * TLDR: Blueprints that inherit from UGameInstanceSubsystems/UWorldSubsystem are not loaded unless they are opened in the editor.
 * If you want a guarantee, you need to add them to a list and forcibly initialize that list.
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
