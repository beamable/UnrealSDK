// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Friends/BeamFriendSubsystem.h"

void UBeamFriendSubsystem::InitializeWhenUnrealReady_Implementation(FBeamOperationHandle& ResultOp)
{
	//Initialize all the subsystem and APIs required to the FriendSubsystem to work
	BeamSocialApi = GEngine->GetEngineSubsystem<UBeamSocialApi>();
	SocialNotifications = GEngine->GetEngineSubsystem<UBeamSocialNotifications>();
	BeamPresenceApi = GEngine->GetEngineSubsystem<UBeamPresenceApi>();
	MailNotifications = GEngine->GetEngineSubsystem<UBeamMailNotifications>();

	Super::InitializeWhenUnrealReady_Implementation(ResultOp);
}

void UBeamFriendSubsystem::OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser,
                                                         const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp)
{
	//Start to listening on the callbacks for the mail changes, this is responsible for receive the callbacks related to friend invites
	const auto MailNotificationHandler = FOnMailRefreshNotificationCode::CreateUFunction(
		this, GET_FUNCTION_NAME_CHECKED(UBeamFriendSubsystem, MailRefreshNotificationHandler), UserSlot);

	MailNotifications->CPP_SubscribeToMailRefresh(UserSlot, Runtime->DefaultNotificationChannel,
	                                              MailNotificationHandler, this);

	//Start to listening on the callbacks for the friends presence changes
	const auto SocialPresenceNotificationHandler = FOnSocialPresenceRefreshNotificationCode::CreateUFunction(
		this, GET_FUNCTION_NAME_CHECKED(UBeamFriendSubsystem, SocialPresenceRefreshNotificationHandler), UserSlot);

	SocialNotifications->CPP_SubscribeToSocialPresenceRefresh(UserSlot, Runtime->DefaultNotificationChannel,
	                                                          SocialPresenceNotificationHandler, this);

	//Start to listening on the callbacks for the friends changes
	const auto SocialNotificationHandler = FOnSocialRefreshNotificationCode::CreateUFunction(
		this, GET_FUNCTION_NAME_CHECKED(UBeamFriendSubsystem, SocialRefreshNotificationHandler), UserSlot);

	SocialNotifications->CPP_SubscribeToSocialRefresh(UserSlot, Runtime->DefaultNotificationChannel,
	                                                  SocialNotificationHandler, this);

	// Fetch the friend presence state for the SignedIn player. 
	const auto FetchPlayerFriendPresenceStateHandle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetName(), {});

	// Fetch the friend state for the SignedIn player. 
	const auto FetchPlayerFriendStateHandle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetName(), FBeamOperationEventHandlerCode::CreateLambda(
			[this, UserSlot, BeamRealmUser, FetchPlayerFriendPresenceStateHandle](const FBeamOperationEvent& Evt)
			{
				if (Evt.EventType == OET_SUCCESS)
				{
					FBeamFriendState FriendState;
					if (TryGetFriendState(BeamRealmUser.GamerTag, FriendState))
					{
						TArray<FBeamGamerTag> FriendIds;
						for (auto Friend : FriendState.Friends)
						{
							FriendIds.Add(Friend.FriendId);
						}
						FetchFriendPresenceStatus(UserSlot, FriendIds, FetchPlayerFriendPresenceStateHandle);
					}
				}
				else
				{
					UE_LOG(LogBeamFriend, Error, TEXT("%hs() failed. Operation failed!"), __FUNCTION__);
				}
			}));

	FetchPlayerFriendState(UserSlot, FetchPlayerFriendStateHandle);

	ResultOp = FetchPlayerFriendPresenceStateHandle;
}

void UBeamFriendSubsystem::OnUserSignedOut_Implementation(const FUserSlot& UserSlot,
                                                          const EUserSlotClearedReason Reason,
                                                          const FBeamRealmUser& BeamRealmUser,
                                                          FBeamOperationHandle& ResultOp)
{
	//Clean up all the states for the specific userslot
	if (FriendStates.Contains(BeamRealmUser.GamerTag))
	{
		FriendStates.Remove(BeamRealmUser.GamerTag);
	}
	Super::OnUserSignedOut_Implementation(UserSlot, Reason, BeamRealmUser, ResultOp);
}

bool UBeamFriendSubsystem::TryGetUserFriendState(FUserSlot UserSlot, FBeamFriendState& FriendState)
{
	return TryGetPlayerFriendState(UserSlot, FriendState);
}

bool UBeamFriendSubsystem::TryGetPlayerFriendState(FBeamGamerTag PlayerId, FBeamFriendState& FriendState)
{
	return TryGetFriendState(PlayerId, FriendState);
}

bool UBeamFriendSubsystem::TryGetFriendPresenceState(FBeamGamerTag PlayerId, FBeamFriendPresenceStatus& StatusState)
{
	return TryGetFriendPresenceStatus(PlayerId, StatusState);
}

FBeamOperationHandle UBeamFriendSubsystem::FetchPlayerFriendStateOperation(FUserSlot UserSlot,
                                                                           FBeamOperationEventHandler
                                                                           OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	FetchPlayerFriendState(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamFriendSubsystem::CPP_FetchPlayerFriendStateOperation(FUserSlot UserSlot,
                                                                               FBeamOperationEventHandlerCode
                                                                               OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                      OnOperationEvent);
	FetchPlayerFriendState(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamFriendSubsystem::FetchFriendsStateOperation(FUserSlot UserSlot,
                                                                      TArray<FBeamGamerTag> PlayerIds,
                                                                      FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	FetchFriendsState(UserSlot, PlayerIds, Handle);
	return Handle;
}

FBeamOperationHandle UBeamFriendSubsystem::CPP_FetchFriendsStateOperation(FUserSlot UserSlot,
                                                                          TArray<FBeamGamerTag> PlayerIds,
                                                                          FBeamOperationEventHandlerCode
                                                                          OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                      OnOperationEvent);
	FetchFriendsState(UserSlot, PlayerIds, Handle);
	return Handle;
}

FBeamOperationHandle UBeamFriendSubsystem::FetchFriendPresenceStatusOperation(FUserSlot UserSlot,
                                                                              TArray<FBeamGamerTag> PlayerIds,
                                                                              FBeamOperationEventHandler
                                                                              OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	FetchFriendPresenceStatus(UserSlot, PlayerIds, Handle);
	return Handle;
}

FBeamOperationHandle UBeamFriendSubsystem::CPP_FetchFriendPresenceStatusOperation(FUserSlot UserSlot,
	TArray<FBeamGamerTag> PlayerIds, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                      OnOperationEvent);
	FetchFriendPresenceStatus(UserSlot, PlayerIds, Handle);
	return Handle;
}

FBeamOperationHandle UBeamFriendSubsystem::SendFriendInviteOperation(FUserSlot UserSlot, FBeamGamerTag FriendId,
                                                                     FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	SendFriendInvite(UserSlot, FriendId, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendSubsystem::CPP_SendFriendInviteOperation(FUserSlot UserSlot, FBeamGamerTag FriendId,
                                                                         FBeamOperationEventHandlerCode
                                                                         OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                      OnOperationEvent);
	SendFriendInvite(UserSlot, FriendId, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendSubsystem::AcceptFriendInviteOperation(FUserSlot UserSlot, FBeamGamerTag FriendId,
                                                                       FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	AcceptFriendInvite(UserSlot, FriendId, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendSubsystem::CPP_AcceptFriendInviteOperation(FUserSlot UserSlot, FBeamGamerTag FriendId,
                                                                           FBeamOperationEventHandlerCode
                                                                           OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                      OnOperationEvent);
	AcceptFriendInvite(UserSlot, FriendId, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendSubsystem::DeclineFriendInviteOperation(FUserSlot UserSlot, FBeamGamerTag FriendId,
                                                                        FBeamOperationEventHandler
                                                                        OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	DeclineFriendInvite(UserSlot, FriendId, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendSubsystem::CPP_DeclineFriendInviteOperation(FUserSlot UserSlot, FBeamGamerTag FriendId,
                                                                            FBeamOperationEventHandlerCode
                                                                            OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                      OnOperationEvent);
	DeclineFriendInvite(UserSlot, FriendId, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendSubsystem::BlockPlayerOperation(FUserSlot UserSlot, FBeamGamerTag PlayerId,
                                                                FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	BlockPlayer(UserSlot, PlayerId, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendSubsystem::CPP_BlockPlayerOperation(FUserSlot UserSlot, FBeamGamerTag PlayerId,
                                                                    FBeamOperationEventHandlerCode
                                                                    OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                      OnOperationEvent);
	BlockPlayer(UserSlot, PlayerId, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendSubsystem::UnblockPlayerOperation(FUserSlot UserSlot, FBeamGamerTag PlayerId,
                                                                  FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	UnblockPlayer(UserSlot, PlayerId, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendSubsystem::CPP_UnblockPlayerOperation(FUserSlot UserSlot, FBeamGamerTag PlayerId,
                                                                      FBeamOperationEventHandlerCode
                                                                      OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                      OnOperationEvent);
	UnblockPlayer(UserSlot, PlayerId, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendSubsystem::RemoveFriendOperation(FUserSlot UserSlot, FBeamGamerTag FriendId,
                                                                 FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	RemoveFriend(UserSlot, FriendId, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendSubsystem::CPP_RemoveFriendOperation(FUserSlot UserSlot, FBeamGamerTag FriendId,
                                                                     FBeamOperationEventHandlerCode
                                                                     OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                      OnOperationEvent);
	RemoveFriend(UserSlot, FriendId, Handle);

	return Handle;
}

bool UBeamFriendSubsystem::TryGetPlayerFriendState(FUserSlot UserSlot, FBeamFriendState& FriendState)
{
	FBeamRealmUser RealmUser;
	if (!Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		return false;
	}
	return TryGetFriendState(RealmUser.GamerTag, FriendState);
}

bool UBeamFriendSubsystem::TryGetFriendState(FBeamGamerTag PlayerId, FBeamFriendState& FriendState)
{
	if (!FriendStates.Contains(PlayerId))
	{
		return false;
	}

	FriendState = FriendStates[PlayerId];

	return true;
}

bool UBeamFriendSubsystem::TryGetFriendPresenceStatus(FBeamGamerTag PlayerId, FBeamFriendPresenceStatus& StatusState)
{
	if (!FriendPresenceStatusState.Contains(PlayerId))
	{
		return false;
	}

	StatusState = FriendPresenceStatusState[PlayerId];

	return true;
}

void UBeamFriendSubsystem::FetchPlayerFriendState(FUserSlot UserSlot, FBeamOperationHandle Op)
{
	const auto Handler = FOnGetMyFullResponse::CreateLambda([this, UserSlot, Op](const FGetMyFullResponse& Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			FBeamFriendState FriendState = MakeFriendState(Resp.SuccessData);

			// Refreshing the state of the PlayerId in the FriendStates
			if (FriendStates.Contains(FriendState.PlayerId))
			{
				FriendStates[FriendState.PlayerId] = FriendState;
			}
			else
			{
				FriendStates.Add(FriendState.PlayerId, FriendState);
			}
			Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
			return;
		}

		if (Resp.State == RS_Error)
		{
			Runtime->RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
			return;
		}

		if (Resp.State == RS_Cancelled)
		{
			Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Resp.ErrorData.message);
			return;
		}
	});

	UGetMyRequest* const Request = UGetMyRequest::Make(this, {});

	FBeamRequestContext Ctx;

	BeamSocialApi->CPP_GetMy(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamFriendSubsystem::FetchFriendsState(FUserSlot UserSlot, TArray<FBeamGamerTag> PlayerIds,
                                             FBeamOperationHandle Op)
{
	const auto Handler = FOnGetSocialFullResponse::CreateLambda([this, UserSlot, Op](const FGetSocialFullResponse& Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			// For each asked player id will update the match state in the FriendStates
			for (auto FriendResponse : Resp.SuccessData->Statuses)
			{
				FBeamFriendState FriendState = MakeFriendState(FriendResponse);

				// Refreshing the state of the PlayerId in the FriendStates
				if (FriendStates.Contains(FriendState.PlayerId))
				{
					FriendStates[FriendState.PlayerId] = FriendState;
				}
				else
				{
					FriendStates.Add(FriendState.PlayerId, FriendState);
				}
			}

			Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
			return;
		}

		if (Resp.State == RS_Error)
		{
			Runtime->RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
			return;
		}

		if (Resp.State == RS_Cancelled)
		{
			Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Resp.ErrorData.message);
			return;
		}
	});

	TArray<FString> PlayerIdArray;

	for (auto PlayerId : PlayerIds)
	{
		PlayerIdArray.Add(PlayerId.AsString);
	}

	UGetSocialRequest* const Request = UGetSocialRequest::Make(PlayerIdArray, this, {});

	FBeamRequestContext Ctx;

	BeamSocialApi->CPP_GetSocial(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamFriendSubsystem::FetchFriendPresenceStatus(FUserSlot UserSlot, TArray<FBeamGamerTag> PlayerIds,
                                                     FBeamOperationHandle Op)
{
	const auto Handler = FOnPostQueryFullResponse::CreateLambda(
		[this, Op](const FPostQueryFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying) return;

			if (Resp.State == RS_Success)
			{
				if (Resp.SuccessData->PlayersStatus.IsSet)
				{
					for (UOnlineStatus* PlayerStatus : Resp.SuccessData->PlayersStatus.Val)
					{
						auto PresenceRefreshMessage = FSocialPresenceRefreshNotificationMessage(PlayerStatus);
						auto FriendPresenceStatus = MakeFriendPresenceStatus(PresenceRefreshMessage);

						// Updates the local state for the Message PlayerId 
						if (FriendPresenceStatusState.Contains(FriendPresenceStatus.PlayerId))
						{
							FriendPresenceStatusState[FriendPresenceStatus.PlayerId] = FriendPresenceStatus;
						}
						else
						{
							FriendPresenceStatusState.Add(FriendPresenceStatus.PlayerId, FriendPresenceStatus);
						}
					}
				}

				Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
				return;
			}

			if (Resp.State == RS_Error)
			{
				Runtime->RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
				return;
			}

			if (Resp.State == RS_Cancelled)
			{
				Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Resp.ErrorData.message);
				return;
			}
		});
	TArray<FString> PlayerIdArray;
	for (auto PlayerId : PlayerIds)
	{
		PlayerIdArray.Add(PlayerId.AsString);
	}
	UPostQueryRequest* const Request = UPostQueryRequest::Make(FOptionalArrayOfString(PlayerIdArray), this, {});

	FBeamRequestContext Ctx;

	BeamPresenceApi->CPP_PostQuery(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamFriendSubsystem::SendFriendInvite(FUserSlot UserSlot, FBeamGamerTag FriendId, FBeamOperationHandle Op)
{
	const auto Handler = FOnPostFriendsInviteFullResponse::CreateLambda(
		[this, UserSlot, FriendId, Op](const FPostFriendsInviteFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying) return;

			if (Resp.State == RS_Success)
			{
				FBeamGamerTag SenderId;

				// Update the local state for the sender, adding the new invite sent to the state.
				if (TryGetBeamGameTagFromUserSlot(UserSlot, SenderId))
				{
					// If there's no data for this player friend list we are adding a dummy at some point it will be updated by the subsystem.
					if (!FriendStates.Contains(SenderId))
					{
						FriendStates.Add(SenderId, FBeamFriendState(SenderId, {}, {}, {}, {}));
					}
					FriendStates[SenderId].SentInvites.Add(FBeamFriendInvite(FriendId));
				}

				Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
				return;
			}

			if (Resp.State == RS_Error)
			{
				Runtime->RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
				return;
			}

			if (Resp.State == RS_Cancelled)
			{
				Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Resp.ErrorData.message);
				return;
			}
		});

	UPostFriendsInviteRequest* const Request = UPostFriendsInviteRequest::Make(FriendId, this, {});

	FBeamRequestContext Ctx;

	BeamSocialApi->CPP_PostFriendsInvite(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamFriendSubsystem::AcceptFriendInvite(FUserSlot UserSlot, FBeamGamerTag FriendId, FBeamOperationHandle Op)
{
	const auto Handler = FOnPostFriendsMakeFullResponse::CreateLambda(
		[this, UserSlot, FriendId, Op](const FPostFriendsMakeFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying) return;

			if (Resp.State == RS_Success)
			{
				FBeamGamerTag PlayerId;

				// Update the local state for the UserSlot, removing the invite from the invites received list and adding the FriendId in the list of the friends.
				if (TryGetBeamGameTagFromUserSlot(UserSlot, PlayerId))
				{
					// If there's no data for this player friend list we are adding a dummy at some point it will be updated by the subsystem.
					if (!FriendStates.Contains(PlayerId))
					{
						FriendStates.Add(PlayerId, FBeamFriendState(PlayerId, {}, {}, {}, {}));
					}

					bool ShouldTriggerEvent = false;

					FBeamFriendInvite Invite(FriendId);
					if (FriendStates[PlayerId].ReceivedInvites.Contains(Invite))
					{
						FriendStates[PlayerId].ReceivedInvites.Remove(Invite);
						ShouldTriggerEvent = true;
					}

					FBeamFriendInfo FriendInfo(FriendId);
					if (!FriendStates[PlayerId].Friends.Contains(FriendInfo))
					{
						FriendStates[PlayerId].Friends.Add(FriendInfo);
					}

					//Sometimes the notification could arrive early then the response so we only trigger the event if something actually change in the state
					if (ShouldTriggerEvent)
					{
						//Call when the player accept the another player invite, the notification from the backend will be ignored because of the local already will be called here.
						OnInviteAccepted.Broadcast(FriendId, UserSlot);
						OnInviteAcceptedCode.Broadcast(FriendId, UserSlot);
					}
				}
				Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
				return;
			}

			if (Resp.State == RS_Error)
			{
				Runtime->RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
				return;
			}

			if (Resp.State == RS_Cancelled)
			{
				Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Resp.ErrorData.message);
				return;
			}
		});

	UPostFriendsMakeRequest* const Request = UPostFriendsMakeRequest::Make(FriendId, this, {});

	FBeamRequestContext Ctx;

	BeamSocialApi->CPP_PostFriendsMake(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamFriendSubsystem::DeclineFriendInvite(FUserSlot UserSlot, FBeamGamerTag FriendId, FBeamOperationHandle Op)
{
	const auto Handler = FOnDeleteFriendsInviteFullResponse::CreateLambda(
		[this, UserSlot, FriendId, Op](const FDeleteFriendsInviteFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying) return;

			if (Resp.State == RS_Success)
			{
				FBeamGamerTag PlayerId;

				// Update the local state for the UserSlot, removing the FriendId in the list of the friends.
				if (TryGetBeamGameTagFromUserSlot(UserSlot, PlayerId))
				{
					// If there's no data for this player friend list we are adding a dummy at some point it will be updated by the subsystem.
					if (!FriendStates.Contains(PlayerId))
					{
						FriendStates.Add(PlayerId, FBeamFriendState(PlayerId, {}, {}, {}, {}));
					}

					FriendStates[PlayerId].ReceivedInvites.Remove(FBeamFriendInvite(FriendId));
					//Call the on declined event OBS: It's only for the local player that call the event, the sender player will not receive this event as a callback 
					OnInviteDeclined.Broadcast(FriendId, UserSlot);
					OnInviteDeclinedCode.Broadcast(FriendId, UserSlot);
				}
				Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
				return;
			}

			if (Resp.State == RS_Error)
			{
				Runtime->RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
				return;
			}

			if (Resp.State == RS_Cancelled)
			{
				Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Resp.ErrorData.message);
				return;
			}
		});

	UDeleteFriendsInviteRequest* const Request = UDeleteFriendsInviteRequest::Make(FriendId, this, {});

	FBeamRequestContext Ctx;

	BeamSocialApi->CPP_DeleteFriendsInvite(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamFriendSubsystem::BlockPlayer(FUserSlot UserSlot, FBeamGamerTag PlayerId, FBeamOperationHandle Op)
{
	const auto Handler = FOnPostBlockedFullResponse::CreateLambda(
		[this, UserSlot, PlayerId, Op](const FPostBlockedFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying) return;

			if (Resp.State == RS_Success)
			{
				FBeamGamerTag SenderId;

				// Update the local state for the UserSlot, removing the PlayerId in the list of the friends, and adding to the blocked list
				if (TryGetBeamGameTagFromUserSlot(UserSlot, SenderId))
				{
					// If there's no data for this player friend list we are adding a dummy at some point it will be updated by the subsystem.
					if (!FriendStates.Contains(SenderId))
					{
						FriendStates.Add(SenderId, FBeamFriendState(SenderId, {}, {}, {}, {}));
					}

					bool ShouldTriggerEvent = false;

					FBeamFriendInfo FriendInfo(PlayerId);

					if (FriendStates[SenderId].Friends.Contains(FriendInfo))
					{
						FriendStates[SenderId].Friends.Remove(FriendInfo);
					}

					FBeamPlayerBlocked BlockedPlayer(PlayerId);
					if (!FriendStates[SenderId].BlockedPlayers.Contains(BlockedPlayer))
					{
						FriendStates[SenderId].BlockedPlayers.Add(BlockedPlayer);
						ShouldTriggerEvent = true;
					}


					//Triggers the player blocked event for the local player
					// Sometimes the changed notifications arrive early then the response, so we need to use that flag to prevent trigger the event twice.
					if (ShouldTriggerEvent)
					{
						OnPlayerBlocked.Broadcast(PlayerId, UserSlot);
						OnPlayerBlockedCode.Broadcast(PlayerId, UserSlot);
					}
				}
				Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
				return;
			}

			if (Resp.State == RS_Error)
			{
				Runtime->RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
				return;
			}

			if (Resp.State == RS_Cancelled)
			{
				Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Resp.ErrorData.message);
				return;
			}
		});

	UPostBlockedRequest* const Request = UPostBlockedRequest::Make(PlayerId, this, {});

	FBeamRequestContext Ctx;

	BeamSocialApi->CPP_PostBlocked(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamFriendSubsystem::UnblockPlayer(FUserSlot UserSlot, FBeamGamerTag PlayerId, FBeamOperationHandle Op)
{
	const auto Handler = FOnDeleteBlockedFullResponse::CreateLambda(
		[this, UserSlot, PlayerId, Op](const FDeleteBlockedFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying) return;

			if (Resp.State == RS_Success)
			{
				FBeamGamerTag SenderId;

				// Update the local state for the UserSlot, removing the PlayerId from the blocked list
				if (TryGetBeamGameTagFromUserSlot(UserSlot, SenderId))
				{
					// If there's no data for this player friend list we are adding a dummy at some point it will be updated by the subsystem.
					if (!FriendStates.Contains(SenderId))
					{
						FriendStates.Add(SenderId, FBeamFriendState(SenderId, {}, {}, {}, {}));
					}
					FBeamPlayerBlocked UnblockedPlayer(PlayerId);

					if (FriendStates[SenderId].BlockedPlayers.Contains(UnblockedPlayer))
					{
						FriendStates[SenderId].BlockedPlayers.Remove(UnblockedPlayer);
					}

					//Triggers the player unblocked event for the local player
					OnPlayerUnblocked.Broadcast(PlayerId, UserSlot);
					OnPlayerUnblockedCode.Broadcast(PlayerId, UserSlot);
				}
				Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
				return;
			}

			if (Resp.State == RS_Error)
			{
				Runtime->RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
				return;
			}

			if (Resp.State == RS_Cancelled)
			{
				Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Resp.ErrorData.message);
				return;
			}
		});

	UDeleteBlockedRequest* const Request = UDeleteBlockedRequest::Make(PlayerId, this, {});

	FBeamRequestContext Ctx;

	BeamSocialApi->CPP_DeleteBlocked(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamFriendSubsystem::RemoveFriend(FUserSlot UserSlot, FBeamGamerTag FriendId, FBeamOperationHandle Op)
{
	const auto Handler = FOnDeleteFriendsFullResponse::CreateLambda(
		[this, UserSlot, FriendId, Op](const FDeleteFriendsFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying) return;

			if (Resp.State == RS_Success)
			{
				FBeamGamerTag SenderId;

				// Update the local state for the UserSlot, removing the PlayerId in the list of the friends
				if (TryGetBeamGameTagFromUserSlot(UserSlot, SenderId))
				{
					// If there's no data for this player friend list we are adding a dummy at some point it will be updated by the subsystem.
					if (!FriendStates.Contains(SenderId))
					{
						FriendStates.Add(SenderId, FBeamFriendState(SenderId, {}, {}, {}, {}));
					}

					bool ShouldTriggerEvent = false;

					FBeamFriendInfo FriendInfo(FriendId);

					if (FriendStates[SenderId].Friends.Contains(FriendInfo))
					{
						FriendStates[SenderId].Friends.Remove(FriendInfo);
						ShouldTriggerEvent = true;
					}
					// Only triggers the event if actually something has been removed
					if (ShouldTriggerEvent)
					{
						//Triggers the friend removed for the local player
						OnFriendRemoved.Broadcast(FriendId, UserSlot);
						OnFriendRemovedCode.Broadcast(FriendId, UserSlot);
					}
				}


				Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
				return;
			}

			if (Resp.State == RS_Error)
			{
				Runtime->RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
				return;
			}

			if (Resp.State == RS_Cancelled)
			{
				Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Resp.ErrorData.message);
				return;
			}
		});

	UDeleteFriendsRequest* const Request = UDeleteFriendsRequest::Make(FriendId, this, {});

	FBeamRequestContext Ctx;

	BeamSocialApi->CPP_DeleteFriends(UserSlot, Request, Handler, Ctx, Op, this);
}

EBeamPresenceStatus UBeamFriendSubsystem::GetStatus(FString StatusStr)
{
	if (StatusStr == "Visible")
	{
		return EBeamPresenceStatus::Visible;
	}
	if (StatusStr == "Invisible")
	{
		return EBeamPresenceStatus::Invisible;
	}
	if (StatusStr == "Away")
	{
		return EBeamPresenceStatus::Away;
	}
	if (StatusStr == "Dnd")
	{
		return EBeamPresenceStatus::Dnd;
	}

	return EBeamPresenceStatus::Visible;
}


void UBeamFriendSubsystem::SocialRefreshNotificationHandler(FSocialRefreshNotificationMessage Message,
                                                            FUserSlot UserSlot)
{
	UE_LOG(LogBeamFriend, Display,
	       TEXT(
		       "Received notification from the FriendNotification for the UserSlot: %s with the Friend Id: %lld | Player Id: %lld"
	       ),
	       *UserSlot.Name,
	       Message.FriendId.AsLong,
	       Message.PlayerId.AsLong);

	FBeamRealmUser RealmUser;
	if (!Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		UE_LOG(LogBeamFriend, Error,
		       TEXT(
			       "Received notification from the FriendNotification for the UserSlot: %s, but wasn't possible to retrieve the RealUser for this UserSlot."
		       ),
		       *UserSlot.Name);
		//Call the internal error for the friends refresh state.
		return;
	}

	if (RealmUser.GamerTag == Message.PlayerId)
	{
		// If there's no data for this player friend list we are adding a dummy at some point it will be updated by the subsystem.
		// It's only create for the player id because we assume that the friend already been updated once it is who made the request.
		if (!FriendStates.Contains(RealmUser.GamerTag))
		{
			FriendStates.Add(RealmUser.GamerTag, FBeamFriendState(RealmUser.GamerTag, {}, {}, {}, {}));
		}
	}

	switch (Message.EventType)
	{
	case EBeamFriendEventType::BEAM_friend:
		//Check if the Message Player Id is the current UserSlot that received the message
		//This will allow to refresh the state of this player after received the event
		if (RealmUser.GamerTag == Message.PlayerId)
		{
			// Adding the friend to the player that sent the invite
			auto FriendState = FBeamFriendInfo(Message.FriendId);

			if (!FriendStates[RealmUser.GamerTag].Friends.Contains(FriendState))
			{
				FriendStates[RealmUser.GamerTag].Friends.Add(FriendState);
			}
			// Removing the invite after the other player accept it.
			auto FriendInviteState = FBeamFriendInvite(Message.FriendId);
			if (FriendStates[RealmUser.GamerTag].SentInvites.Contains(FriendInviteState))
			{
				FriendStates[RealmUser.GamerTag].SentInvites.Remove(FriendInviteState);
			}

			OnInviteAccepted.Broadcast(Message.FriendId, UserSlot);
			OnInviteAcceptedCode.Broadcast(Message.FriendId, UserSlot);
		}
		else if (RealmUser.GamerTag == Message.FriendId)
		{
			bool ShouldTriggerEvent = false;

			// Adding the friend to the player that sent the invite
			auto FriendState = FBeamFriendInfo(Message.PlayerId);

			if (!FriendStates[RealmUser.GamerTag].Friends.Contains(FriendState))
			{
				FriendStates[RealmUser.GamerTag].Friends.Add(FriendState);
				ShouldTriggerEvent = true;
			}

			// Removing the invite after accept it.
			auto FriendInviteState = FBeamFriendInvite(Message.PlayerId);
			if (FriendStates[RealmUser.GamerTag].ReceivedInvites.Contains(FriendInviteState))
			{
				FriendStates[RealmUser.GamerTag].ReceivedInvites.Remove(FriendInviteState);
			}
			//This flag guarantee if the player still don't exist in the local state this means the local state wasn't updated before received the notification
			//Without verify it we probably call it twice once in the AcceptFriendInvite and another here
			//This is only true for the player that made the action of accept the invite (the friend)
			if (ShouldTriggerEvent)
			{
				OnInviteAccepted.Broadcast(Message.PlayerId, UserSlot);
				OnInviteAcceptedCode.Broadcast(Message.PlayerId, UserSlot);
			}
		}
		break;
	case EBeamFriendEventType::BEAM_unfriend:
		//The Message.PlayerId is the GamerTag of the player who did the action of remove the friend
		if (RealmUser.GamerTag == Message.PlayerId)
		{
			bool ShouldTriggerEvent = false;

			// Removing the friend to the player that was removed from other player friend list.
			auto FriendState = FBeamFriendInfo(Message.FriendId);
			if (FriendStates[RealmUser.GamerTag].Friends.Contains(FriendState))
			{
				FriendStates[RealmUser.GamerTag].Friends.Remove(FriendState);
				ShouldTriggerEvent = true;
			}
			// This only should called if the Friend has been removed from the local state
			if (ShouldTriggerEvent)
			{
				OnFriendRemoved.Broadcast(Message.FriendId, UserSlot);
				OnFriendRemovedCode.Broadcast(Message.FriendId, UserSlot);
			}
		}
		else if (RealmUser.GamerTag == Message.FriendId)
		{
			bool ShouldTriggerEvent = false;

			// Removing the friend to the player that was removed from other player friend list.
			auto FriendState = FBeamFriendInfo(Message.PlayerId);
			if (FriendStates[RealmUser.GamerTag].Friends.Contains(FriendState))
			{
				FriendStates[RealmUser.GamerTag].Friends.Remove(FriendState);
				ShouldTriggerEvent = true;
			}

			if (ShouldTriggerEvent)
			{
				OnFriendRemoved.Broadcast(Message.PlayerId, UserSlot);
				OnFriendRemovedCode.Broadcast(Message.PlayerId, UserSlot);
			}
		}
		break;
	case EBeamFriendEventType::BEAM_block:
		if (RealmUser.GamerTag == Message.PlayerId)
		{
			bool ShouldTriggerEvent = false;

			// Adding the blocked friend to the list of the blocked players.
			auto BlockedPlayer = FBeamPlayerBlocked(Message.FriendId);
			if (!FriendStates[RealmUser.GamerTag].BlockedPlayers.Contains(BlockedPlayer))
			{
				FriendStates[RealmUser.GamerTag].BlockedPlayers.Add(BlockedPlayer);
				ShouldTriggerEvent = true;
			}
			// Removing the friend from the friend list as it has been blocked by the player
			auto FriendState = FBeamFriendInfo(Message.FriendId);
			if (FriendStates[RealmUser.GamerTag].Friends.Contains(FriendState))
			{
				FriendStates[RealmUser.GamerTag].Friends.Remove(FriendState);
			}
			// Only triggers the event if actually something change in the blocked list
			if (ShouldTriggerEvent)
			{
				OnPlayerBlocked.Broadcast(Message.FriendId, UserSlot);
				OnPlayerBlockedCode.Broadcast(Message.FriendId, UserSlot);
			}
		}
		else if (RealmUser.GamerTag == Message.FriendId)
		{
			// Warning the player about being blocked by another player
			OnPlayerBeenBlocked.Broadcast(Message.PlayerId, UserSlot);
			OnPlayerBeenBlockedCode.Broadcast(Message.PlayerId, UserSlot);
		}
		break;
	case EBeamFriendEventType::BEAM_unblock:
		if (RealmUser.GamerTag == Message.PlayerId)
		{
			bool ShouldTriggerEvent = false;
			// Removing the blocked player from the local state.
			auto BlockedPlayer = FBeamPlayerBlocked(Message.FriendId);
			if (FriendStates[RealmUser.GamerTag].BlockedPlayers.Contains(BlockedPlayer))
			{
				FriendStates[RealmUser.GamerTag].BlockedPlayers.Remove(BlockedPlayer);
				ShouldTriggerEvent = true;
			}
			// Only will trigger the event if something actually happen in the blocked players states
			if (ShouldTriggerEvent)
			{
				OnPlayerUnblocked.Broadcast(Message.FriendId, UserSlot);
				OnPlayerUnblockedCode.Broadcast(Message.FriendId, UserSlot);
			}
		}
		else if (RealmUser.GamerTag == Message.FriendId)
		{
			// Warning the player about being unblocked by another player
			OnPlayerBeenUnblocked.Broadcast(Message.PlayerId, UserSlot);
			OnPlayerBeenUnblockedCode.Broadcast(Message.PlayerId, UserSlot);
		}
		break;
	default:

		break;
	}
}

void UBeamFriendSubsystem::SocialPresenceRefreshNotificationHandler(FSocialPresenceRefreshNotificationMessage Message,
                                                                    FUserSlot UserSlot)
{
	auto FriendPresenceStatus = MakeFriendPresenceStatus(Message);
	// Updates the local state for the Message PlayerId 
	if (FriendPresenceStatusState.Contains(Message.PlayerId))
	{
		FriendPresenceStatusState[Message.PlayerId] = FriendPresenceStatus;
	}
	else
	{
		FriendPresenceStatusState.Add(Message.PlayerId, FriendPresenceStatus);
	}

	UE_LOG(LogBeamFriend, Display,
	       TEXT(
		       "Received notification from the FriendPresenceNotification for the UserSlot: %s with the Friend Id: %lld"
	       ),
	       *UserSlot.Name,
	       Message.PlayerId.AsLong);

	// Triggers the event of the Friend Presence Changed.
	OnFriendPresenceStatusUpdate.Broadcast(Message.PlayerId, UserSlot);
	OnFriendPresenceStatusUpdateCode.Broadcast(Message.PlayerId, UserSlot);
}

void UBeamFriendSubsystem::MailRefreshNotificationHandler(FMailRefreshNotificationMessage Message,
                                                          FUserSlot UserSlot)
{
	FBeamRealmUser RealmUser;

	if (Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		// Get the state before fetch the data to compare the state with the new data and get the player that sent the invite.
		TArray<FBeamFriendInvite> ReceivedInvites;
		FBeamGamerTag PlayerId = RealmUser.GamerTag;
		if (FriendStates.Contains(PlayerId))
		{
			ReceivedInvites = FriendStates[PlayerId].ReceivedInvites;
		}

		// Fetch the state for the FriendStates, when it is called the state is already updated.
		const FBeamOperationEventHandlerCode Handler = FBeamOperationEventHandlerCode::CreateLambda(
			[this, PlayerId, ReceivedInvites, UserSlot](const FBeamOperationEvent Evt)
			{
				if (Evt.EventType == OET_SUCCESS)
				{
					//Compare the old invites with the new one and trigger the OnFriendInviteReceived with all the PlayerIds of the received invites.
					if (FriendStates.Contains(PlayerId))
					{
						for (auto FriendInvite : FriendStates[PlayerId].ReceivedInvites)
						{
							if (!ReceivedInvites.Contains(FriendInvite))
							{
								OnInviteReceived.Broadcast(FriendInvite.FriendId, UserSlot);
								OnInviteReceivedCode.Broadcast(FriendInvite.FriendId, UserSlot);
							}
						}
					}
				}
				else
				{
					UE_LOG(LogBeamFriend, Error, TEXT("Failed to fetch the state of the friends in the %hs"), __func__);
				}
			});
		CPP_FetchPlayerFriendStateOperation(UserSlot, Handler);
	}
}

FBeamFriendState UBeamFriendSubsystem::MakeFriendState(USocial* Social)
{
	FBeamFriendState FriendState;

	FriendState.PlayerId = Social->PlayerId;

	for (auto Friend : Social->Friends)
	{
		FriendState.Friends.Add(FBeamFriendInfo(Friend->PlayerId));
	}

	for (auto Invite : Social->Invites)
	{
		if (Invite->Direction == EInvitationDirection::BEAM_outgoing)
		{
			FriendState.SentInvites.Add(FBeamFriendInvite(Invite->PlayerId));
		}
		else if (Invite->Direction == EInvitationDirection::BEAM_incoming)
		{
			FriendState.ReceivedInvites.Add(FBeamFriendInvite(Invite->PlayerId));
		}
	}

	for (auto Blocked : Social->Blocked)
	{
		FriendState.BlockedPlayers.Add(FBeamPlayerBlocked(Blocked->PlayerId));
	}

	return FriendState;
}

FBeamFriendPresenceStatus UBeamFriendSubsystem::MakeFriendPresenceStatus(
	FSocialPresenceRefreshNotificationMessage PresenceStatusMessage)
{
	auto FriendPresenceStatus = FBeamFriendPresenceStatus(PresenceStatusMessage.PlayerId, PresenceStatusMessage.Online,
	                                                      PresenceStatusMessage.LastOnline,
	                                                      GetStatus(
		                                                      PresenceStatusMessage.Status),
	                                                      PresenceStatusMessage.Description);
	return FriendPresenceStatus;
}
