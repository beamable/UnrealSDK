#include "Subsystems/LiveOps/BeamAnnouncementsSubsystem.h"
#include "BeamNotifications/SubSystems/BeamAnnouncementsNotifications.h"
#include "Subsystems/Inventory/BeamInventorySubsystem.h"

void UBeamAnnouncementsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UserSlots = Runtime->UserSlotSystem;
	RequestTracker = Runtime->RequestTrackerSystem;
	AnnouncementsApi = GEngine->GetEngineSubsystem<UBeamAnnouncementsApi>();
}

void UBeamAnnouncementsSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

TArray<TSubclassOf<UBeamRuntimeSubsystem>> UBeamAnnouncementsSubsystem::GetDependingOnSubsystems()
{
	TArray<TSubclassOf<UBeamRuntimeSubsystem>> DependingSubsytems =
		Super::GetDependingOnSubsystems();
	DependingSubsytems.Add(UBeamInventorySubsystem::StaticClass());
	return DependingSubsytems;
}

void UBeamAnnouncementsSubsystem::OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp)
{
	PerUserAnnouncements.Add(UserSlot, FBeamAnnouncementsState{});

	// We set up the announcement refresh notification here whenever the owner user signs in (we need to set this up again as websocket connections are established per-UserSlot).
	const auto NotificationHandler = FOnAnnouncementRefreshNotificationCode::CreateLambda([this, UserSlot](const FAnnouncementRefreshNotificationMessage& Msg)
	{
		UE_LOG(LogBeamContent, Warning, TEXT("Received announcement refresh."));
		RefreshAnnouncementsOperation(UserSlot, {});
	});
	GEngine->GetEngineSubsystem<UBeamAnnouncementsNotifications>()->CPP_SubscribeToAnnouncementRefresh(UserSlot, Runtime->DefaultNotificationChannel, NotificationHandler, this);

	ResultOp = CPP_RefreshAnnouncementsOperation(UserSlot, {});
}

void UBeamAnnouncementsSubsystem::OnUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp)
{
	Super::OnUserSignedOut_Implementation(UserSlot, Reason, BeamRealmUser, ResultOp);
	PerUserAnnouncements.Remove(UserSlot);
}

void UBeamAnnouncementsSubsystem::TriggerAnnouncementsUpdated(const FUserSlot& UserSlot)
{
	OnAnnouncementsUpdatedCode.Broadcast(UserSlot);
	OnAnnouncementsUpdated.Broadcast(UserSlot);
}

/* * STATS SUBSYSTEM - Operations * */

FBeamOperationHandle UBeamAnnouncementsSubsystem::RefreshAnnouncementsOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	RefreshAnnouncements(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamAnnouncementsSubsystem::CPP_RefreshAnnouncementsOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	RefreshAnnouncements(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamAnnouncementsSubsystem::MarkSingleAnnouncementReadOperation(FUserSlot UserSlot,
                                                                                      FBeamOperationEventHandler OnOperationEvent,
                                                                                      const FString& AnnouncementId)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot},
	                                                                  GetClass()->GetFName().ToString(), OnOperationEvent);

	FOptionalString OptionalAnnouncementID{AnnouncementId};

	FOptionalArrayOfString EmptyArrayString;

	MarkAnnouncementRead(UserSlot, Handle, OptionalAnnouncementID, EmptyArrayString);
	return Handle;
}

FBeamOperationHandle UBeamAnnouncementsSubsystem::CPP_MarkSingleAnnouncementReadOperation(FUserSlot UserSlot,
                                                                                          FBeamOperationEventHandlerCode OnOperationEvent,
                                                                                          FOptionalString& AnnouncementId)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot},
	                                                                      GetClass()->GetFName().ToString(), OnOperationEvent);

	FOptionalArrayOfString EmptyArrayString;

	MarkAnnouncementRead(UserSlot, Handle, AnnouncementId, EmptyArrayString);
	return Handle;
}

FBeamOperationHandle UBeamAnnouncementsSubsystem::MarkAnnouncementsReadOperation(FUserSlot UserSlot,
                                                                                 FBeamOperationEventHandler OnOperationEvent,
                                                                                 const TArray<FString>& AnnouncementsIds)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot},
	                                                                  GetClass()->GetFName().ToString(), OnOperationEvent);

	FOptionalArrayOfString OptionalAnnouncementIds{AnnouncementsIds};

	FOptionalString EmptyString;

	MarkAnnouncementRead(UserSlot, Handle, EmptyString, OptionalAnnouncementIds);
	return Handle;
}

FBeamOperationHandle UBeamAnnouncementsSubsystem::CPP_MarkAnnouncementReadOperation(FUserSlot UserSlot,
                                                                                    FBeamOperationEventHandlerCode OnOperationEvent,
                                                                                    FOptionalArrayOfString& AnnouncementsIds)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot},
	                                                                      GetClass()->GetFName().ToString(), OnOperationEvent);

	FOptionalString EmptyString;

	MarkAnnouncementRead(UserSlot, Handle, EmptyString, AnnouncementsIds);
	return Handle;
}

FBeamOperationHandle UBeamAnnouncementsSubsystem::ClaimSingleAnnouncementOperation(FUserSlot UserSlot,
                                                                                   FBeamOperationEventHandler OnOperationEvent, const FString& AnnouncementId)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot},
	                                                                  GetClass()->GetFName().ToString(), OnOperationEvent);

	FOptionalString OptionalAnnouncementID{AnnouncementId};

	FOptionalArrayOfString EmptyArrayString;

	ClaimAnnouncement(UserSlot, Handle, OptionalAnnouncementID, EmptyArrayString);
	return Handle;
}

FBeamOperationHandle UBeamAnnouncementsSubsystem::CPP_ClaimSingleAnnouncementOperation(FUserSlot UserSlot,
                                                                                       FBeamOperationEventHandlerCode OnOperationEvent, FOptionalString& AnnouncementId)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot},
	                                                                      GetClass()->GetFName().ToString(), OnOperationEvent);

	FOptionalArrayOfString EmptyArrayString;

	ClaimAnnouncement(UserSlot, Handle, AnnouncementId, EmptyArrayString);
	return Handle;
}

FBeamOperationHandle UBeamAnnouncementsSubsystem::ClaimAnnouncementsOperation(FUserSlot UserSlot,
                                                                              FBeamOperationEventHandler OnOperationEvent, const TArray<FString>& AnnouncementsIds)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot},
	                                                                  GetClass()->GetFName().ToString(), OnOperationEvent);

	FOptionalArrayOfString OptionalAnnouncementIDs{AnnouncementsIds};

	FOptionalString EmptyString;

	ClaimAnnouncement(UserSlot, Handle, EmptyString, OptionalAnnouncementIDs);
	return Handle;
}

FBeamOperationHandle UBeamAnnouncementsSubsystem::CPP_ClaimAnnouncementsOperation(FUserSlot UserSlot,
                                                                                  FBeamOperationEventHandlerCode OnOperationEvent, FOptionalArrayOfString& AnnouncementsIds)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot},
	                                                                      GetClass()->GetFName().ToString(), OnOperationEvent);

	FOptionalString EmptyString;

	ClaimAnnouncement(UserSlot, Handle, EmptyString, AnnouncementsIds);
	return Handle;
}

/* * STATS SUBSYSTEM - Operation Implementations * */


void UBeamAnnouncementsSubsystem::RefreshAnnouncements(FUserSlot UserSlot, FBeamOperationHandle Op)
{
	// Ensure we have a user at the given slot.
	FBeamRealmUser RealmUser;
	if (!IsRunningDedicatedServer())
	{
		if (!UserSlots->GetUserDataAtSlot(UserSlot, RealmUser, this))
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_AUTHENTICATED_USER_AT_SLOT"));
			return;
		}
	}

	auto Handler = FOnGetAnnouncementsFullResponse::CreateLambda([this, Op, UserSlot](FGetAnnouncementsFullResponse Resp)
	{
		// If we are invoking this before retrying, we just don't do anything 
		if (Resp.State == RS_Retrying) return;

		if (Resp.State != RS_Success)
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error);
		}
		else
		{
			TArray<UAnnouncementView*> Views = {};
			for (UAnnouncementView* Announcement : Resp.SuccessData->Announcements)
			{
				Views.Add(DuplicateObject<UAnnouncementView>(Announcement, GetTransientPackage()));
			}

			PerUserAnnouncements.Add(UserSlot, FBeamAnnouncementsState(UserSlot, Views));
			TriggerAnnouncementsUpdated(UserSlot);
			RequestTracker->TriggerOperationSuccess(Op, {});
		}
	});

	auto Ctx = RequestGetAnnouncements(UserSlot, Op, Handler);
}

void UBeamAnnouncementsSubsystem::MarkAnnouncementRead(FUserSlot UserSlot, FBeamOperationHandle Op,
                                                       FOptionalString& Announcement, FOptionalArrayOfString& Announcements)
{
	// Ensure we have a user at the given slot.
	FBeamRealmUser RealmUser;
	if (!IsRunningDedicatedServer())
	{
		if (!UserSlots->GetUserDataAtSlot(UserSlot, RealmUser, this))
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_AUTHENTICATED_USER_AT_SLOT"));
			return;
		}
	}

	auto Handler = FOnPutReadFullResponse::CreateLambda([this, Op, UserSlot](
		const FBeamFullResponse<UPutReadRequest*, UCommonResponse*>& Resp)
		{
			// If we are invoking this before retrying, we just don't do anything 
			if (Resp.State == RS_Retrying) return;

			if (Resp.State != RS_Success)
			{
				RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error);
			}
			else
			{
				if (PerUserAnnouncements.Contains(UserSlot))
				{
					TArray<UAnnouncementView*> AnnouncementViewArr = PerUserAnnouncements[UserSlot].Announcements;

					if (!Resp.RequestData->Body->Announcement.Val.IsEmpty())
					{
						FOptionalArrayOfString AllAnnouncements;
						for (UAnnouncementView* AnnouncementView : AnnouncementViewArr)
						{
							if (AnnouncementView->Id == Resp.RequestData->Body->Announcement.Val)
							{
								AnnouncementView->bIsRead = true;
							}
						}
					}
					else
					{
						FOptionalArrayOfString AllAnnouncements;
						for (UAnnouncementView* AnnouncementView : AnnouncementViewArr)
						{
							for (FString AnnouncementId : Resp.RequestData->Body->Announcements.Val)
							{
								if (AnnouncementView->Id == AnnouncementId)
								{
									AnnouncementView->bIsRead = true;
								}
							}
						}
					}
				}
				RequestTracker->TriggerOperationSuccess(Op, {});
			}
		});

	auto Ctx = RequestMarkAnnouncementRead(UserSlot, Op, Handler, Announcement, Announcements);
}

void UBeamAnnouncementsSubsystem::ClaimAnnouncement(FUserSlot UserSlot, FBeamOperationHandle Op,
                                                    FOptionalString& Announcement, FOptionalArrayOfString& Announcements)
{
	// Ensure we have a user at the given slot.
	FBeamRealmUser RealmUser;
	if (!IsRunningDedicatedServer())
	{
		if (!UserSlots->GetUserDataAtSlot(UserSlot, RealmUser, this))
		{
			RequestTracker->TriggerOperationError(Op, TEXT("NO_AUTHENTICATED_USER_AT_SLOT"));
			return;
		}
	}

	auto Handler = FOnObjectAnnouncementsPostClaimByObjectIdFullResponse::CreateLambda([this, Op, UserSlot](const FObjectAnnouncementsPostClaimByObjectIdFullResponse& Resp)
	{
		// If we are invoking this before retrying, we just don't do anything 
		if (Resp.State == RS_Retrying) return;

		if (Resp.State != RS_Success)
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error);
		}
		else
		{
			if (PerUserAnnouncements.Contains(UserSlot))
			{
				TArray<UAnnouncementView*> AnnouncementViewArr = PerUserAnnouncements[UserSlot].Announcements;

				if (!Resp.RequestData->Body->Announcement.Val.IsEmpty())
				{
					FOptionalArrayOfString AllAnnouncements;
					for (UAnnouncementView* AnnouncementView : AnnouncementViewArr)
					{
						if (AnnouncementView->Id == Resp.RequestData->Body->Announcement.Val)
						{
							AnnouncementView->bIsClaimed = true;
						}
					}
				}
				else
				{
					FOptionalArrayOfString AllAnnouncements;
					for (UAnnouncementView* AnnouncementView : AnnouncementViewArr)
					{
						for (FString AnnouncementId : Resp.RequestData->Body->Announcements.Val)
						{
							if (AnnouncementView->Id == AnnouncementId)
							{
								AnnouncementView->bIsClaimed = true;
							}
						}
					}
				}
			}

			//TODO : Refresh inventory ?
			RequestTracker->TriggerOperationSuccess(Op, {});
		}
	});

	auto Ctx = RequestClaimAnnouncement(UserSlot, Op, Handler, Announcement, Announcements);
}


/* * ANNOUNCEMENTS SUBSYSTEM - Request Helper Functions * */

FBeamRequestContext UBeamAnnouncementsSubsystem::RequestGetAnnouncements(const FUserSlot& UserSlot, const FBeamOperationHandle Op, const FOnGetAnnouncementsFullResponse Handler) const
{
	FBeamRealmUser RealmUser;
	Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this);

	const auto Req = UGetAnnouncementsRequest::Make(RealmUser.GamerTag.AsLong, FOptionalBool(), GetTransientPackage(), {});
	FBeamRequestContext Ctx;
	AnnouncementsApi->CPP_GetAnnouncements(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}

FBeamRequestContext UBeamAnnouncementsSubsystem::RequestMarkAnnouncementRead(const FUserSlot& UserSlot, const FBeamOperationHandle Op,
                                                                             const FOnPutReadFullResponse Handler, FOptionalString Announcement, FOptionalArrayOfString Announcements) const
{
	FBeamRealmUser RealmUser;
	Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this);

	const auto Req = UPutReadRequest::Make(RealmUser.GamerTag.AsLong,
	                                       Announcement, Announcements,
	                                       GetTransientPackage(), {});
	FBeamRequestContext Ctx;
	AnnouncementsApi->CPP_PutRead(UserSlot, Req, Handler, Ctx, Op, this);

	return Ctx;
}

FBeamRequestContext UBeamAnnouncementsSubsystem::RequestClaimAnnouncement(const FUserSlot& UserSlot, const FBeamOperationHandle Op,
                                                                          const FOnObjectAnnouncementsPostClaimByObjectIdFullResponse Handler, FOptionalString Announcement,
                                                                          FOptionalArrayOfString Announcements) const
{
	FBeamRealmUser RealmUser;
	Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this);


	const auto Req = UObjectAnnouncementsPostClaimByObjectIdRequest::Make(RealmUser.GamerTag.AsLong,
	                                                                      Announcement, Announcements,
	                                                                      GetTransientPackage(), {});

	FBeamRequestContext Ctx;
	AnnouncementsApi->CPP_PostClaim(UserSlot, Req, Handler, Ctx, Op, this);
	return Ctx;
}


/* * ANNOUNCEMENTS SUBSYSTEM - Read Local State Functions * */

bool UBeamAnnouncementsSubsystem::GetAnnouncements(FUserSlot Slot, FBeamAnnouncementsState& Announcements)
{
	Announcements = FBeamAnnouncementsState{};
	if (!PerUserAnnouncements.Contains(Slot))
		return false;

	Announcements = PerUserAnnouncements.FindChecked(Slot);
	return true;
}
