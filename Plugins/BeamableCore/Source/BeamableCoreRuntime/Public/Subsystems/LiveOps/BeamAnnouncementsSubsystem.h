#pragma once

#include "AutoGen/SubSystems/BeamAnnouncementsApi.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "UserSlots/BeamUserSlots.h"
#include "BeamAnnouncementsSubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeamAnnouncementsUpdated, FUserSlot, Evt);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnBeamAnnouncementsUpdatedCode, FUserSlot);

USTRUCT(BlueprintType)
struct FBeamAnnouncementsState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FUserSlot Slot;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<UAnnouncementView*> Announcements ={};

	FBeamAnnouncementsState()
	{
		Slot = {};
		Announcements = {};		
	}
	
	FBeamAnnouncementsState(const FUserSlot& Slot, const TArray<UAnnouncementView*>& Announcements)
		: Slot(Slot),
		  Announcements(Announcements)
	{
	}
};

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

	UPROPERTY()
	TMap<FUserSlot, FBeamAnnouncementsState> PerUserAnnouncements;

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

	void MarkAnnouncementRead(FUserSlot UserSlot, FBeamOperationHandle Op, FOptionalString& Announcement, FOptionalArrayOfString& Announcements);

	void ClaimAnnouncement(FUserSlot UserSlot, FBeamOperationHandle Op, FOptionalString& Announcement, FOptionalArrayOfString& Announcements);

	// Request Helper Functions
	FBeamRequestContext RequestGetAnnouncements(const FUserSlot& UserSlot, FBeamOperationHandle Op, FOnGetAnnouncementsFullResponse Handler) const;

	FBeamRequestContext RequestMarkAnnouncementRead(const FUserSlot& UserSlot, FBeamOperationHandle Op,
												FOnPutReadFullResponse Handler, FOptionalString Announcement,
												FOptionalArrayOfString Announcements) const;
	
	FBeamRequestContext RequestClaimAnnouncement(const FUserSlot& UserSlot, FBeamOperationHandle Op,
												 FOnObjectAnnouncementsPostClaimByObjectIdFullResponse Handler,
												 FOptionalString Announcement,
												 FOptionalArrayOfString Announcements) const;
public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamAnnouncementsSubsystem* GetSelf(const UObject* CallingContext) { return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamAnnouncementsSubsystem>(); }

	//Returns a list of subsystems that this system is depending on
	virtual TArray<TSubclassOf<UBeamRuntimeSubsystem>> GetDependingOnSubsystems() override;
	
	/**
	* @brief Marks one announcement as read.  
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Announcement", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle MarkSingleAnnouncementReadOperation(FUserSlot UserSlot,
													   FBeamOperationEventHandler OnOperationEvent,
													   const FString& AnnouncementId);

	/**
	 * @copydoc MarkSingleAnnouncementReadOperation 
	 */
	FBeamOperationHandle CPP_MarkSingleAnnouncementReadOperation(FUserSlot UserSlot,
														   FBeamOperationEventHandlerCode OnOperationEvent,
														   FOptionalString& AnnouncementId);
	/**
	* @brief Marks a group of announcement as read.  
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Announcement", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle MarkAnnouncementsReadOperation(FUserSlot UserSlot,
													   FBeamOperationEventHandler OnOperationEvent,
													   const TArray<FString>& AnnouncementsIds);
	/**
	 * @copydoc MarkAnnouncementsReadOperation 
	 */
	FBeamOperationHandle CPP_MarkAnnouncementReadOperation(FUserSlot UserSlot,
														   FBeamOperationEventHandlerCode OnOperationEvent,
														   FOptionalArrayOfString& AnnouncementsIds);

	/**
	* @brief Claim the rewards in a single announcement.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Announcement", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle ClaimSingleAnnouncementOperation(FUserSlot UserSlot,
													   FBeamOperationEventHandler OnOperationEvent,
													   const FString& Announcement);

	/**
	 * @copydoc ClaimSingleAnnouncementOperation 
	 */
	FBeamOperationHandle CPP_ClaimSingleAnnouncementOperation(FUserSlot UserSlot,
														   FBeamOperationEventHandlerCode OnOperationEvent,
														   FOptionalString& Announcement);
	/**
	* @brief Claim the rewards in a group of announcements.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Announcement", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle ClaimAnnouncementsOperation(FUserSlot UserSlot,
													   FBeamOperationEventHandler OnOperationEvent,
													   const TArray<FString>& Announcements);
	/**
	 * @copydoc ClaimAnnouncementsOperation 
	 */
	FBeamOperationHandle CPP_ClaimAnnouncementsOperation(FUserSlot UserSlot,
														   FBeamOperationEventHandlerCode OnOperationEvent,
														   FOptionalArrayOfString& Announcements);
	
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool GetAnnouncements(FUserSlot Slot, FBeamAnnouncementsState& Announcements);
};
