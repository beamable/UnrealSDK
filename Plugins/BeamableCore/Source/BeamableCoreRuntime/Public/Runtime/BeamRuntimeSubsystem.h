// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamRuntimeSettings.h"
#include "UObject/Object.h"
#include "Runtime/BeamRuntime.h"
#include "BeamRuntimeSubsystem.generated.h"

class UBeamContentSubsystem;

/**
 * State of Subsystem intialization.
 *
 * - UnInitialized: The subsystem is not initialized, using the subsystem in this state may result in a crash
 * - InitializedNoUserData: The subsystem is initialized but without the user data.
 * - InitializedWithUserData: The sdk is now initialized and ready to be used.
 */
UENUM()
enum ESubsystemState
{
	BeamUninitialized,
	BeamInitialized,
};

UENUM()
enum ESubsystemUserState
{
	BeamInitializedNoUserData,
	BeamInitializedWithUserData
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRuntimeUserSlotDataChangedEvent, FUserSlot, UserSlot);

UCLASS(Abstract, Blueprintable, meta=(IsBlueprintBase=true, ShowWorldContextPin))
class BEAMABLECORERUNTIME_API UBeamRuntimeSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

	friend class UBeamRuntime;

protected:
	/** @brief Initializes the subsystem.  */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Cleans up the system.  */
	virtual void Deinitialize() override;

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void Tick(float DeltaTime) override
	{
	}

	virtual bool IsAllowedToTick() const override
	{
		return true;
	}

	virtual TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(UBeamRuntimeSubsystem, STATGROUP_Tickables);
	}

	/** @brief an enum that represents the state of the sdk if it is currently initialized and ready to be used or not */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, DisplayName="Subsystem State", Category="Beam")
	TEnumAsByte<ESubsystemState> CurrentState;

	/** @brief an enum that represents the state of the sdk if it is currently initialized and ready to be used or not */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, DisplayName="Subsystem State", Category="Beam")
	TMap<FUserSlot, TEnumAsByte<ESubsystemUserState>> CurrentUserState;

public:
	UPROPERTY()
	UBeamRuntime* Runtime;

	/** @brief returns the state of the subsystem if it is initalized and ready to be used or not */
	UFUNCTION(BlueprintCallable, Category="Beam")
	TEnumAsByte<ESubsystemState> GetSubsystemState() { return CurrentState; }

	/**
	 * This is called after unreal is fully initialized but Beamable is not. Basically, this runs after all Engine and GameInstance Subsystems have
	 * completed running their Initialize function. This callback is useful for reading cached local state and local configuration files.  
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Beam")
	void InitializeWhenUnrealReady(FBeamOperationHandle& ResultOp);
	virtual void InitializeWhenUnrealReady_Implementation(FBeamOperationHandle& ResultOp);

	/**
	 * This returns a list of the subsystems that needs to be initialized for this subsystem to work correctly.
	 */
	UFUNCTION()
	virtual TArray<TSubclassOf<UBeamRuntimeSubsystem>> GetDependingOnSubsystems();

	/**
	 * @brief At this point, you can make any non-authenticated request to beamable. But... you don't have access to any beamable content types (they are fetched at this point).
	 * For example, downloading content at the start of a player session (see UBeamContentSubsystem for an example).
	 * This is guaranteed to run only once per game-client/server session. Also, for UBeamRuntimeSubsystems running in dedicated servers, this is the last of the callbacks here that will actually run.
	 * After this runs, UBeamRuntime::OnStarted is invoked and user-level code can run to make non-authenticated requests to beamable (ie: game-specific signup/login flows). 
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Beam")
	void OnBeamableStarting(FBeamOperationHandle& ResultOp);
	virtual void OnBeamableStarting_Implementation(FBeamOperationHandle& ResultOp);

	/**
	 * @brief UBeamRuntime::OnStarted runs after all these callbacks have completed. At this point, you can make any non-authenticated request to beamable and you have access to your content manifest).
	 * For example, pre-fetching store data based on store content.
	 * This is guaranteed to run only once per game-client/server session. Also, for UBeamRuntimeSubsystems running in dedicated servers, this is the last of the callbacks here that will actually run.
	 * After this runs, UBeamRuntime::OnStarted is invoked and user-level code can run to make non-authenticated requests to beamable (ie: game-specific signup/login flows). 
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Beam")
	void OnBeamableContentReady(FBeamOperationHandle& ResultOp);
	virtual void OnBeamableContentReady_Implementation(FBeamOperationHandle& ResultOp);

	/**
	 * @brief Called whenever a user authenticates into a user slot.
	 * The returned operation is added to a list of operations containing all other subsystem's OnUserSignedIn operation.
	 * We wait for this list of operations to finish and then call OnPostUserSignedIn.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Beam")
	void OnUserSignedIn(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp);
	virtual void OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp);
	/**
	 * @brief Called whenever a user signs out of a user slot.
	 * The returned operation is added to a list of operations containing all other subsystem's OnUserSignedOut operation.
	 * We wait for this list of operations to finish and then call OnPostUserSignedOut.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Beam")
	void OnUserSignedOut(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp);
	virtual void OnUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp);

	/**
	 * @brief Called on each BeamRuntimeSubsystem after the OnUserSignedIn operations of ALL BeamRuntimeSubsystems have run to completion (success or otherwise).	 
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Beam")
	void OnPostUserSignedIn(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp);
	virtual void OnPostUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp);

	/**
	 * @brief Called on each BeamRuntimeSubsystem after the OnUserSignedOut operations of ALL BeamRuntimeSubsystems have run to completion (success or otherwise). 
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Beam")
	void OnPostUserSignedOut(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp);
	virtual void OnPostUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp);


	/**
	 * @brief Called whenever UBeamRuntime fails its frictionless authentication flow. This is only called if you have automatic frictionless authentication set up.
	 * By default, this is called after the OnBeamableStarted step ONLY IF we fail to authenticate.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Beam")
	void OnFailedUserAuth(const FUserSlot& UserSlot);
	virtual void OnFailedUserAuth_Implementation(const FUserSlot& UserSlot);

	/**
	 * @brief Called whenever a user's websocket connection is lost. This either means that either the Beamable service is unavailable (or had a problem with this particular user's socket)
	 * OR the player has lost internet access. We don't give you By default, this is called after the OnBeamableStarted step ONLY IF we fail to authenticate.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Beam")
	void OnUserConnectionLost(const FUserSlot& UserSlot);
	virtual void OnUserConnectionLost_Implementation(const FUserSlot& UserSlot);

	/**
	 * Check if the user slot is authenticated and print the caller as a error.
	 */
	virtual bool IsUserSlotAuthenticated(FUserSlot UserSlot, FString FunctionName, FBeamOperationHandle OperationHandle);
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
		for (const auto& SubsystemBlueprint : RuntimeSettings->RuntimeSubsystemBlueprints)
		{
			Collection.InitializeDependency(SubsystemBlueprint);
		}

		if (IsRunningDedicatedServer())
		{
			for (const auto& SubsystemBlueprint : RuntimeSettings->ServerOnlyRuntimeSubsystemBlueprints)
			{
				Collection.InitializeDependency(SubsystemBlueprint);
			}
		}
		else
		{
			for (const auto& SubsystemBlueprint : RuntimeSettings->ClientRuntimeSubsystemBlueprints)
			{
				Collection.InitializeDependency(SubsystemBlueprint);
			}
		}
	}


	/** Cleans up the system.  */
	virtual void Deinitialize() override
	{
		Super::Deinitialize();
	}
};
