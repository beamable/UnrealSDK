#pragma once

#include "AutoGen/SubSystems/BeamAnnouncementsApi.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "UserSlots/BeamUserSlots.h"
#include "BeamAnnouncementsSubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeamAnnouncementsUpdated, FUserSlot, Evt);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnBeamAnnouncementsUpdatedCode, FUserSlot);

/**
 * 
 */
UCLASS()
class BEAMABLECORERUNTIME_API UBeamAnnouncementsSubsystem : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UBeamUserSlots* UserSlots;
	UPROPERTY()
	UBeamAnnouncementsApi* AnnouncementsApi;
	UPROPERTY()
	UBeamRequestTracker* RequestTracker;

	TMap<FUserSlot, TArray<UAnnouncementView*>> PerUserAnnouncements;

	/**
	 * @brief Triggered whenever we refresh the state of announcements from a particular player. 
	 */
	UPROPERTY(BlueprintAssignable)
	FOnBeamAnnouncementsUpdated OnAnnouncementsUpdated;

	/**
	 * @copybrief OnAnnouncementsUpdated
	 */
	FOnBeamAnnouncementsUpdatedCode OnAnnouncementsUpdatedCode;

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual void OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp) override;
	virtual void OnUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp) override;

	void TriggerAnnouncementsUpdated(const FUserSlot& UserSlot);

	// Operations
	FBeamOperationHandle RefreshAnnouncementsOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent);
	FBeamOperationHandle CPP_RefreshAnnouncementsOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent);

	// Operation Implementations
	void RefreshAnnouncements(FUserSlot UserSlot, FBeamOperationHandle Op);

	// Request Helper Functions
	FBeamRequestContext RequestGetAnnouncements(const FUserSlot& UserSlot, FBeamOperationHandle Op, FOnGetAnnouncementsFullResponse Handler) const;

public:
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool GetAnnouncements(FUserSlot Slot, TArray<UAnnouncementView*>& Announcements);
};
