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
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamStatsSubsystem* GetSelf(const UObject* CallingContext) { return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamStatsSubsystem>(); }

	// Update Command
	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="Stats", ExpandBoolAsExecs="ReturnValue"))
	bool TryCreateUpdateCommand(FUserSlot Slot, const TMap<FString, FString>& Stats, UBeamStatUpdateCommand*& Command);
	UFUNCTION(BlueprintCallable)
	void AddStatToUpdateCommand(FUserSlot Slot, FString Key, FString Value);
	UFUNCTION(BlueprintCallable)
	void RemoveStatFromUpdateCommand(FUserSlot Slot, FString Key);
	UFUNCTION(BlueprintCallable)
	void ResetUpdateCommand(FUserSlot Slot);

	// Read Local State
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetAllStats(FUserSlot Slot, EBeamStatsDomain StatDomain, EBeamStatsVisibility StatVisibility, TArray<FString>& Keys, TArray<FString>& Values);

	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetAllStatsByGamerTag(FUserSlot Slot, EBeamStatsDomain StatDomain, EBeamStatsVisibility StatVisibility, FBeamGamerTag StatOwner, TArray<FString>& Keys, TArray<FString>& Values);

	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetStat(FUserSlot Slot, EBeamStatsDomain StatDomain, EBeamStatsVisibility StatVisibility, FString StatKey, FString& Value);

	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetStatByGamerTag(FUserSlot Slot, EBeamStatsDomain StatDomain, EBeamStatsVisibility StatVisibility, FBeamGamerTag StatOwner, FString StatKey, FString& Value);


	// Operations
	/**
	 * @brief Refreshes the stats the user at the given user slot. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Stats", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle RefreshStatsOperation(FUserSlot UserSlot, FBeamStatsType Type, FBeamOperationEventHandler OnOperationEvent);
	/**
	 * @copydoc RefreshStatsOperation
	 */
	FBeamOperationHandle CPP_RefreshStatsOperation(FUserSlot UserSlot, FBeamStatsType Type, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief Refreshes the given stat for the user at the given user slot. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Stats", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle RefreshSingleStatOperation(FUserSlot UserSlot, FBeamStatsType Type, FString StatKey, FBeamOperationEventHandler OnOperationEvent);
	/**
	 * @copydoc RefreshSingleStatOperation
	 */
	FBeamOperationHandle CPP_RefreshSingleStatOperation(FUserSlot UserSlot, FBeamStatsType Type, FString StatKey, FBeamOperationEventHandlerCode OnOperationEvent);

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

	/**
	 * @brief Removes a single stat for the calling user slot.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Stats", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle DeleteStatOperation(FUserSlot UserSlot, FString Key, FBeamOperationEventHandler OnOperationEvent);
	/**
	 * @copydoc DeleteStatOperation
	 */
	FBeamOperationHandle CPP_DeleteStatOperation(FUserSlot UserSlot, const FString& Key, FBeamOperationEventHandlerCode OnOperationEvent);


	/**
	 * @brief Increments any integer stat by some amount for the calling user slot.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Stats", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle IncrementStatsOperation(FUserSlot UserSlot, const TMap<FString, int32>& Stats, FBeamOperationEventHandler OnOperationEvent);
	/**
	 * @copydoc IncrementStatsOperation
	 */
	FBeamOperationHandle CPP_IncrementStatsOperation(FUserSlot UserSlot, const TMap<FString, int32>& Stats, FBeamOperationEventHandlerCode OnOperationEvent);

private:
	// Operation Implementations
	void RefreshStats(FUserSlot UserSlot, FBeamStatsType Type, FBeamOperationHandle Op);
	void RefreshSingleStat(FUserSlot UserSlot, FBeamStatsType Type, FString StatKey, FBeamOperationHandle Op);
	void CommitStats(FUserSlot UserSlot, FBeamOperationHandle Op);
	void SetStat(FUserSlot Slot, FString StatKey, FString StatValue, FBeamOperationHandle Op);
	void DeleteStat(FUserSlot Slot, FString StatKey, FBeamOperationHandle Op);
	void IncrementStats(FUserSlot Slot, TMap<FString, int> StatIncrements, FBeamOperationHandle Op);

	// Request Helper Functions
	FBeamRequestContext RequestGetStats(const FUserSlot& UserSlot, FBeamStatsType StatsType, FBeamOperationHandle Op, FOnGetClientFullResponse Handler) const;
	FBeamRequestContext RequestGetSingleStat(const FUserSlot& UserSlot, FBeamStatsType StatsType, FString StatKey, FBeamOperationHandle Op, FOnGetClientFullResponse Handler) const;
	FBeamRequestContext RequestGetStats(const FUserSlot& UserSlot, const TEnumAsByte<EBeamStatsDomain>& Domain, const TEnumAsByte<EBeamStatsVisibility>& Visibility, const FBeamGamerTag& GamerTag,
	                                    const FBeamOperationHandle Op,
	                                    const FOnGetClientFullResponse Handler) const;
	FBeamRequestContext RequestSetStats(const FUserSlot& UserSlot, TMap<FString, FString> Stats, const FBeamOperationHandle Op, const FOnPostClientFullResponse Handler) const;
	FBeamRequestContext RequestIncrementStats(const FUserSlot& UserSlot, TMap<FString, int32> StatsToAdd, const FBeamOperationHandle Op, const FOnPostClientFullResponse Handler) const;
	FBeamRequestContext RequestDeleteStats(const FUserSlot& UserSlot, FString StatName, FBeamOperationHandle Op, FOnDeleteStatsFullResponse Handler) const;

	// Local Helper Functions
	bool _TryGetAllStats(FBeamStatsType Type, TArray<FString>& Keys, TArray<FString>& Values);
	bool _TryGetStat(FBeamStatsType Type, FString StatKey, FString& Value);
};
