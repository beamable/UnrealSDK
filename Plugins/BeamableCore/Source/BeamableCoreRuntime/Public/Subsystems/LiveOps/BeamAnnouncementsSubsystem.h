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

	void MarkAnnouncementRead(FUserSlot UserSlot, FBeamOperationHandle Op, FOptionalString& Announcement);
	FBeamRequestContext RequestMarkAnnouncementRead(const FUserSlot& UserSlot, FBeamOperationHandle Op,
	                                                FOnPutReadFullResponse Handler, FOptionalString Announcement,
	                                                FOptionalArrayOfString Announcements) const;

	// Operation Implementations
	void RefreshAnnouncements(FUserSlot UserSlot, FBeamOperationHandle Op);
	
	void MarkAnnouncementRead(FUserSlot UserSlot, FBeamOperationHandle Op, FOptionalArrayOfString& Announcements);

	// Request Helper Functions
	FBeamRequestContext RequestGetAnnouncements(const FUserSlot& UserSlot, FBeamOperationHandle Op, FOnGetAnnouncementsFullResponse Handler) const;

public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamAnnouncementsSubsystem* GetSelf(const UObject* CallingContext) { return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamAnnouncementsSubsystem>(); }
	
	/**
	* @brief Marks one announcement as read.  
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Announcement", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle MarkSingleAnnouncementReadOperation(FUserSlot UserSlot,
													   FBeamOperationEventHandler OnOperationEvent,
													   const FString& Announcement);

	/**
	 * @copydoc MarkSingleAnnouncementReadOperation 
	 */
	FBeamOperationHandle CPP_MarkAnnouncementReadOperation(FUserSlot UserSlot,
														   FBeamOperationEventHandlerCode OnOperationEvent,
														   FOptionalString& Announcement);
	/**
	* @brief Marks a group of announcement as read.  
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Announcement", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle MarkAnnouncementsReadOperation(FUserSlot UserSlot,
													   FBeamOperationEventHandler OnOperationEvent,
													   const TArray<FString>& Announcements);
	/**
	 * @copydoc MarkAnnouncementsReadOperation 
	 */
	FBeamOperationHandle CPP_MarkAnnouncementReadOperation(FUserSlot UserSlot,
														   FBeamOperationEventHandlerCode OnOperationEvent,
														   FOptionalArrayOfString& Announcements);
	
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool GetAnnouncements(FUserSlot Slot, TArray<UAnnouncementView*>& Announcements);
};
