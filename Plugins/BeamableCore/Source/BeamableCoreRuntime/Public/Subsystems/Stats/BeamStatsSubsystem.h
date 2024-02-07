// ================================ Copyright (c) Wildcard Alliance , All Rights Reserved. ================================

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/SubSystems/BeamStatsApi.h"
#include "BeamBackend/SemanticTypes/BeamStatsTypeLibrary.h"
#include "Internationalization/Regex.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "BeamStatsSubsystem.generated.h"


class UBeamStatsSubsystem;

UCLASS(BlueprintType)
class UBeamStatsState : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FBeamStatsType OwnerType;

	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FString> StringStats;
};

UCLASS(BlueprintType)
class BEAMABLECORERUNTIME_API UBeamStatUpdateCommand : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	UBeamStatsSubsystem* StatsSubsystem;

public:
	explicit UBeamStatUpdateCommand() = default;

	void Init(UBeamStatsSubsystem* Subsystem, FUserSlot Slot, FBeamStatsType Type, TMap<FString, FString> StartingStats);

	UPROPERTY(BlueprintReadOnly)
	FUserSlot UserSlot;

	UPROPERTY(BlueprintReadOnly)
	FBeamStatsType StatType;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> StatNames;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> StatValues;

	UFUNCTION(BlueprintCallable)
	void AddStat(FString Key, FString Value);

	UFUNCTION(BlueprintCallable)
	void AddStats(TArray<FString> Key, TArray<FString> Value);

	UFUNCTION(BlueprintCallable)
	void AddStatsMap(TMap<FString, FString> Stats);

	UFUNCTION(BlueprintCallable)
	void RemoveStat(FString Key);

	UFUNCTION(BlueprintCallable)
	void Discard();

	UFUNCTION(BlueprintCallable)
	TMap<FString, FString> AsMap();
};

/** Stats Updated ----- Event fired whenever 1+ Stats are updated. **/

USTRUCT(BlueprintType)
struct FBeamStatsUpdatedEvent
{
	GENERATED_BODY()

	/**
	 * Contains only the keys of the updated values.
	 */
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FString> OldValues;

	/**
	 * Contains only the keys of the updated values.
	 */
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FString> NewValues;

	UPROPERTY(BlueprintReadOnly, meta=(PinHiddenByDefault))
	FBeamGamerTag GamerTag;

	UPROPERTY(BlueprintReadOnly, meta=(PinHiddenByDefault))
	FUserSlot LocalSlot;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeamStatsUpdated, FBeamStatsUpdatedEvent, Evt);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnBeamStatsUpdatedCode, FBeamStatsUpdatedEvent);

/**
 * 
 */
UCLASS()
class BEAMABLECORERUNTIME_API UBeamStatsSubsystem : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UBeamUserSlots* UserSlots;
	UPROPERTY()
	UBeamStatsApi* StatsApi;
	UPROPERTY()
	UBeamRequestTracker* RequestTracker;

	/**
	 * Holds stats for all players. 
	 */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FBeamStatsType, UBeamStatsState*> PlayerStatCache;

	/**
	 * Triggered whenever the local stats for a particular BeamStatsType is over.
	 * When the GamerTag in the StatsType struct is associated with one of the user slots,
	 * the user slot is provided.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnBeamStatsUpdated OnStatsUpdated;
	/**
	 * @copybrief OnStatsUpdated
	 */
	FOnBeamStatsUpdatedCode OnStatsUpdatedCode;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FUserSlot, UBeamStatUpdateCommand*> UpdateCommands;

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp) override;
	virtual void OnUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp) override;

public:
	// Update Command
	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="Stats", ExpandBoolAsExecs="ReturnValue"))
	bool TryCreateUpdateCommand(FUserSlot Slot, const TMap<FString, FString>& Stats, UBeamStatUpdateCommand*& Command);
	UFUNCTION(BlueprintCallable)
	void AddStatToUpdateCommand(FUserSlot Slot, FString Key, FString Value);
	UFUNCTION(BlueprintCallable)
	void RemoveStatFromUpdateCommand(FUserSlot Slot, FString Key);
	UFUNCTION(BlueprintCallable)
	void ResetUpdateCommand(FUserSlot Slot);

	// Operations
	/**
	 * @brief Refreshes the client/public stats the user at the given user slot. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Stats", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle RefreshStatsOperation(FUserSlot UserSlot, FBeamStatsType Type, FBeamOperationEventHandler OnOperationEvent);
	/**
	 * @copydoc RefreshStatsOperation
	 */
	FBeamOperationHandle CPP_RefreshStatsOperation(FUserSlot UserSlot, FBeamStatsType Type, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief Takes whatever is the current stat update command for the given user slot and submits it to the Beamable backend.
	 * Call this only after you've called TryCreateUpdateCommand for this slot.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Stats", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle CommitStatsOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent);
	/**
	 * @copydoc CommitStatsOperation
	 */
	FBeamOperationHandle CPP_CommitStatsOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief Updates a single stat for the calling user slot.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Stats", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle SetStatOperation(FUserSlot UserSlot, FString Key, FString Value, FBeamOperationEventHandler OnOperationEvent);
	/**
	 * @copydoc SetStatOperation
	 */
	FBeamOperationHandle CPP_SetStatOperation(FUserSlot UserSlot, const FString& Key, const FString& Value, FBeamOperationEventHandlerCode OnOperationEvent);

private:
	// Operation Implementations
	void RefreshStats(FUserSlot UserSlot, FBeamStatsType Type, FBeamOperationHandle Op);
	void CommitStats(FUserSlot UserSlot, FBeamOperationHandle Op);
	void SetStat(FUserSlot Slot, FString StatKey, FString StatValue, FBeamOperationHandle Op);

	// Request Helper Functions
	FBeamRequestContext RequestGetStats(const FUserSlot& UserSlot, FBeamStatsType StatsType, FBeamOperationHandle Op, FOnGetClientFullResponse Handler) const;
	FBeamRequestContext RequestGetStats(const FUserSlot& UserSlot, const TEnumAsByte<EBeamStatsDomain>& Domain, const TEnumAsByte<EBeamStatsVisibility>& Visibility, const FBeamGamerTag& GamerTag, const FBeamOperationHandle Op, const FOnGetClientFullResponse Handler) const;
	FBeamRequestContext RequestSetStats(const FUserSlot& UserSlot, TMap<FString, FString> Stats, const FBeamOperationHandle Op, const FOnPostClientFullResponse Handler) const;
};
