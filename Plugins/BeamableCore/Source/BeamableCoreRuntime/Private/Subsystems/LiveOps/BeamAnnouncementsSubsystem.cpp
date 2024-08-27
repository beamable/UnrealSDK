#include "Subsystems/LiveOps/BeamAnnouncementsSubsystem.h"

#include "BeamNotifications/SubSystems/BeamAnnouncementsNotifications.h"


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

void UBeamAnnouncementsSubsystem::OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp)
{
	PerUserAnnouncements.Add(UserSlot, {});

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
	const FString& AnnouncementID)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot},
		GetClass()->GetFName().ToString(), OnOperationEvent);
	
	FOptionalString OptionalAnnouncementID;
	OptionalAnnouncementID.Val = AnnouncementID;
	MarkAnnouncementRead(UserSlot, Handle,OptionalAnnouncementID);
	return Handle;
}

FBeamOperationHandle UBeamAnnouncementsSubsystem::CPP_MarkAnnouncementReadOperation(FUserSlot UserSlot,
	FBeamOperationEventHandlerCode OnOperationEvent,
	FOptionalString &Announcement)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot},
		GetClass()->GetFName().ToString(), OnOperationEvent);
	FOptionalArrayOfString EmptyArrayString;
	MarkAnnouncementRead(UserSlot, Handle,Announcement);
	return Handle;
}
FBeamOperationHandle UBeamAnnouncementsSubsystem::MarkAnnouncementsReadOperation(FUserSlot UserSlot,
	FBeamOperationEventHandler OnOperationEvent,
	const TArray<FString>& AnnouncementsIDs)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot},
		GetClass()->GetFName().ToString(), OnOperationEvent);

	FOptionalArrayOfString OptionalAnnouncementIDs;
	OptionalAnnouncementIDs.Val = AnnouncementsIDs;
	
	MarkAnnouncementRead(UserSlot, Handle,OptionalAnnouncementIDs);
	return Handle;
}

FBeamOperationHandle UBeamAnnouncementsSubsystem::CPP_MarkAnnouncementReadOperation(FUserSlot UserSlot,
	FBeamOperationEventHandlerCode OnOperationEvent,
	FOptionalArrayOfString& Announcements)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot},
		GetClass()->GetFName().ToString(), OnOperationEvent);

	MarkAnnouncementRead(UserSlot, Handle,Announcements);
	return Handle;
}

/* * STATS SUBSYSTEM - Operation Implementations * */

void UBeamAnnouncementsSubsystem::MarkAnnouncementRead(FUserSlot UserSlot, FBeamOperationHandle Op,
	FOptionalString& Announcement)
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
				TArray<UAnnouncementView*> AnnouncementViewArr =  PerUserAnnouncements[UserSlot];

				FOptionalArrayOfString AllAnnouncements;
				for (UAnnouncementView *AnnouncementView : AnnouncementViewArr)
				{
					if (AnnouncementView->Id == Resp.RequestData->Body->Announcement.Val)
					{
						AnnouncementView->bIsRead = true;
					}
				}	
			}
			RequestTracker->TriggerOperationSuccess(Op, {});
		}
	});
	
	auto Ctx = RequestMarkAnnouncementRead(UserSlot,Op,Handler,Announcement,FOptionalArrayOfString());

}

void UBeamAnnouncementsSubsystem::MarkAnnouncementRead(FUserSlot UserSlot, FBeamOperationHandle Op,
	FOptionalArrayOfString& Announcements)
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
				TArray<UAnnouncementView*> AnnouncementViewArr =  PerUserAnnouncements[UserSlot];

				FOptionalArrayOfString AllAnnouncements;
				for (UAnnouncementView *AnnouncementView : AnnouncementViewArr)
				{
					for (int i = 0;i<Resp.RequestData->Body->Announcements.Val.Num();i++)
					{
						if (AnnouncementView->Id == Resp.RequestData->Body->Announcements.Val[i])
						{
							AnnouncementView->bIsRead = true;
						}
					}
				}
			}
			RequestTracker->TriggerOperationSuccess(Op, {});
		}
	});
	
	auto Ctx = RequestMarkAnnouncementRead(UserSlot,Op,Handler,FOptionalString(),Announcements);

}

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
			PerUserAnnouncements.Add(UserSlot, Resp.SuccessData->Announcements);
			TriggerAnnouncementsUpdated(UserSlot);
			RequestTracker->TriggerOperationSuccess(Op, {});
		}
	});

	auto Ctx = RequestGetAnnouncements(UserSlot, Op, Handler);
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
	const FOnPutReadFullResponse Handler,FOptionalString Announcement, FOptionalArrayOfString Announcements) const
{
	FBeamRealmUser RealmUser;
	Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this);
	
	const auto Req = UPutReadRequest::Make(RealmUser.GamerTag.AsLong,
		Announcement,Announcements,
		GetTransientPackage(), {});
	FBeamRequestContext Ctx;
	AnnouncementsApi->CPP_PutRead(UserSlot, Req, Handler, Ctx, Op, this);

	return Ctx;
}

/* * ANNOUNCEMENTS SUBSYSTEM - Read Local State Functions * */

bool UBeamAnnouncementsSubsystem::GetAnnouncements(FUserSlot Slot, TArray<UAnnouncementView*>& Announcements)
{
	Announcements = {};
	if (!PerUserAnnouncements.Contains(Slot))
		return false;

	Announcements = PerUserAnnouncements.FindChecked(Slot);
	return true;
}
