// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Friends/BeamFriendsSubsystem.h"

#include "BeamableDefines.h"

void UBeamFriendsSubsystem::InitializeWhenUnrealReady_Implementation(FBeamOperationHandle& ResultOp)
{
	//Initialize all the subsystem and APIs required to the FriendSubsystem to work
	BeamFriendsApi = GEngine->GetEngineSubsystem<UBeamFriendsApi>();
	SocialNotifications = GEngine->GetEngineSubsystem<UBeamSocialNotifications>();
	BeamPresenceApi = GEngine->GetEngineSubsystem<UBeamPresenceApi>();
	MailNotifications = GEngine->GetEngineSubsystem<UBeamMailNotifications>();

	Super::InitializeWhenUnrealReady_Implementation(ResultOp);
}

void UBeamFriendsSubsystem::OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser,
                                                          const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp)
{
	if (!IsRunningDedicatedServer())
	{
		//Start to listening on the callbacks for the mail changes, this is responsible for receive the callbacks related to friend invites
		const auto MailNotificationHandler = FOnMailRefreshNotificationCode::CreateUFunction(
			this, GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, MailRefreshNotificationHandler), UserSlot);

		MailNotifications->CPP_SubscribeToMailRefresh(UserSlot, Runtime->DefaultNotificationChannel,
		                                              MailNotificationHandler, this);

		//Start to listening on the callbacks for the friends presence changes
		const auto SocialPresenceNotificationHandler = FOnSocialPresenceRefreshNotificationCode::CreateUFunction(
			this, GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, SocialPresenceRefreshNotificationHandler), UserSlot);

		SocialNotifications->CPP_SubscribeToSocialPresenceRefresh(UserSlot, Runtime->DefaultNotificationChannel,
		                                                          SocialPresenceNotificationHandler, this);

		//Start to listening on the callbacks for the friends changes
		const auto SocialNotificationHandler = FOnSocialRefreshNotificationCode::CreateUFunction(
			this, GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, SocialRefreshNotificationHandler), UserSlot);

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
						if (TryGetPlayerFriendState(BeamRealmUser.GamerTag, FriendState))
						{
							TArray<FBeamGamerTag> FriendIds;
							for (auto Friend : FriendState.Friends)
							{
								FriendIds.Add(Friend.FriendGamerTag);
							}
							FetchFriendPresenceStatus(UserSlot, FriendIds, FetchPlayerFriendPresenceStateHandle);
						}
					}
					else
					{
						UE_LOG(LogBeamFriend, Error, TEXT("%hs() failed. Operation failed!"), BEAM_FUNC_SIG);
					}
				}));

		FetchPlayerFriendState(UserSlot, FetchPlayerFriendStateHandle);

		ResultOp = FetchPlayerFriendPresenceStateHandle;
	}
	else
	{
		ResultOp = Runtime->RequestTrackerSystem->CPP_BeginSuccessfulOperation({}, GetName(), {}, {});
	}
}

void UBeamFriendsSubsystem::OnUserSignedOut_Implementation(const FUserSlot& UserSlot,
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

bool UBeamFriendsSubsystem::TryGetUserFriendState(FUserSlot UserSlot, FBeamFriendState& FriendState)
{
	FBeamRealmUser RealmUser;
	if (!Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		return false;
	}
	return TryGetPlayerFriendState(RealmUser.GamerTag, FriendState);
}

bool UBeamFriendsSubsystem::TryGetPlayerFriendState(FBeamGamerTag PlayerGamerTag, FBeamFriendState& FriendState)
{
	if (!FriendStates.Contains(PlayerGamerTag))
	{
		return false;
	}

	FriendState = FriendStates[PlayerGamerTag];

	return true;
}

bool UBeamFriendsSubsystem::TryGetFriendPresenceState(FBeamGamerTag PlayerGamerTag,
                                                      FBeamFriendPresenceStatus& StatusState)
{
	if (!FriendStates.Contains(PlayerGamerTag))
	{
		return false;
	}

	StatusState = FriendStates[PlayerGamerTag].Status;

	return true;
}

FBeamOperationHandle UBeamFriendsSubsystem::FetchPlayerFriendStateOperation(FUserSlot UserSlot,
                                                                            FBeamOperationEventHandler
                                                                            OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	FetchPlayerFriendState(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamFriendsSubsystem::CPP_FetchPlayerFriendStateOperation(FUserSlot UserSlot,
                                                                                FBeamOperationEventHandlerCode
                                                                                OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                      OnOperationEvent);
	FetchPlayerFriendState(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamFriendsSubsystem::FetchFriendsStateOperation(FUserSlot UserSlot,
                                                                       TArray<FBeamGamerTag> PlayerGamerTags,
                                                                       FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	FetchFriendsState(UserSlot, PlayerGamerTags, Handle);
	return Handle;
}

FBeamOperationHandle UBeamFriendsSubsystem::CPP_FetchFriendsStateOperation(FUserSlot UserSlot,
                                                                           TArray<FBeamGamerTag> PlayerGamerTags,
                                                                           FBeamOperationEventHandlerCode
                                                                           OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                      OnOperationEvent);
	FetchFriendsState(UserSlot, PlayerGamerTags, Handle);
	return Handle;
}

FBeamOperationHandle UBeamFriendsSubsystem::FetchFriendPresenceStatusOperation(FUserSlot UserSlot,
                                                                               TArray<FBeamGamerTag> PlayerGamerTags,
                                                                               FBeamOperationEventHandler
                                                                               OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	FetchFriendPresenceStatus(UserSlot, PlayerGamerTags, Handle);
	return Handle;
}

FBeamOperationHandle UBeamFriendsSubsystem::CPP_FetchFriendPresenceStatusOperation(FUserSlot UserSlot,
                                                                                   TArray<FBeamGamerTag> PlayerGamerTags, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                      OnOperationEvent);
	FetchFriendPresenceStatus(UserSlot, PlayerGamerTags, Handle);
	return Handle;
}

FBeamOperationHandle UBeamFriendsSubsystem::SendFriendInviteOperation(FUserSlot UserSlot, FBeamGamerTag FriendGamerTag,
                                                                      FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	SendFriendInvite(UserSlot, FriendGamerTag, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendsSubsystem::CPP_SendFriendInviteOperation(
	FUserSlot UserSlot, FBeamGamerTag FriendGamerTag,
	FBeamOperationEventHandlerCode
	OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                      OnOperationEvent);
	SendFriendInvite(UserSlot, FriendGamerTag, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendsSubsystem::AcceptFriendInviteOperation(FUserSlot UserSlot, FBeamGamerTag FriendGamerTag,
                                                                        FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	AcceptFriendInvite(UserSlot, FriendGamerTag, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendsSubsystem::CPP_AcceptFriendInviteOperation(
	FUserSlot UserSlot, FBeamGamerTag FriendGamerTag,
	FBeamOperationEventHandlerCode
	OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                      OnOperationEvent);
	AcceptFriendInvite(UserSlot, FriendGamerTag, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendsSubsystem::DeclineFriendInviteOperation(
	FUserSlot UserSlot, FBeamGamerTag FriendGamerTag,
	FBeamOperationEventHandler
	OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	DeclineFriendInvite(UserSlot, FriendGamerTag, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendsSubsystem::CPP_DeclineFriendInviteOperation(
	FUserSlot UserSlot, FBeamGamerTag FriendGamerTag,
	FBeamOperationEventHandlerCode
	OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                      OnOperationEvent);
	DeclineFriendInvite(UserSlot, FriendGamerTag, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendsSubsystem::BlockPlayerOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
                                                                 FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	BlockPlayer(UserSlot, PlayerGamerTag, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendsSubsystem::CPP_BlockPlayerOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
                                                                     FBeamOperationEventHandlerCode
                                                                     OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                      OnOperationEvent);
	BlockPlayer(UserSlot, PlayerGamerTag, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendsSubsystem::UnblockPlayerOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
                                                                   FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	UnblockPlayer(UserSlot, PlayerGamerTag, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendsSubsystem::CPP_UnblockPlayerOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
                                                                       FBeamOperationEventHandlerCode
                                                                       OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                      OnOperationEvent);
	UnblockPlayer(UserSlot, PlayerGamerTag, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendsSubsystem::RemoveFriendOperation(FUserSlot UserSlot, FBeamGamerTag FriendGamerTag,
                                                                  FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	RemoveFriend(UserSlot, FriendGamerTag, Handle);

	return Handle;
}

FBeamOperationHandle UBeamFriendsSubsystem::CPP_RemoveFriendOperation(FUserSlot UserSlot, FBeamGamerTag FriendGamerTag,
                                                                      FBeamOperationEventHandlerCode
                                                                      OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                      OnOperationEvent);
	RemoveFriend(UserSlot, FriendGamerTag, Handle);

	return Handle;
}

void UBeamFriendsSubsystem::FetchPlayerFriendState(FUserSlot UserSlot, FBeamOperationHandle Op)
{
	if (!IsUserSlotAuthenticated(UserSlot, BEAM_FUNC_SIG, Op))
	{
		return;
	}
	const auto Handler = FOnGetMyFullResponse::CreateLambda([this, Op, UserSlot](const FGetMyFullResponse& Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			FBeamRealmUser BeamRealmUser;
			if (!Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, BeamRealmUser, this))
			{
				Runtime->RequestTrackerSystem->TriggerOperationError(Op, TEXT("Invalid UserSlot"));
				return;
			}
			FBeamFriendState FriendState = MakeFriendState(Resp.SuccessData);
			FriendState.ReceivedInvites.RemoveAll([BeamRealmUser](const FBeamFriendInvite& FriendInvite)
			{
				return FriendInvite.FriendGamerTag == BeamRealmUser.GamerTag;
			});

			// Refreshing the state of the PlayerGamerTag in the FriendStates
			if (FriendStates.Contains(FriendState.PlayerGamerTag))
			{
				auto CachedStatus = FriendStates[FriendState.PlayerGamerTag].Status;
				FriendStates[FriendState.PlayerGamerTag] = FriendState;
				FriendStates[FriendState.PlayerGamerTag].Status = CachedStatus;
			}
			else
			{
				FriendStates.Add(FriendState.PlayerGamerTag, FriendState);
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

	BeamFriendsApi->CPP_GetMy(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamFriendsSubsystem::FetchFriendsState(FUserSlot UserSlot, TArray<FBeamGamerTag> PlayerGamerTags,
                                              FBeamOperationHandle Op)
{
	const auto Handler = FOnBasicFriendsGetFriendsFullResponse::CreateLambda([this, UserSlot, Op](const FBasicFriendsGetFriendsFullResponse& Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			// For each asked player id will update the match state in the FriendStates
			for (auto FriendResponse : Resp.SuccessData->Statuses)
			{
				FBeamFriendState FriendState = MakeFriendState(FriendResponse);

				// Refreshing the state of the PlayerGamerTag in the FriendStates
				if (FriendStates.Contains(FriendState.PlayerGamerTag))
				{
					auto CachedStatus = FriendStates[FriendState.PlayerGamerTag].Status;
					FriendStates[FriendState.PlayerGamerTag] = FriendState;
					FriendStates[FriendState.PlayerGamerTag].Status = CachedStatus;
				}
				else
				{
					FriendStates.Add(FriendState.PlayerGamerTag, FriendState);
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

	for (auto PlayerGamerTag : PlayerGamerTags)
	{
		PlayerIdArray.Add(PlayerGamerTag.AsString);
	}

	UBasicFriendsGetFriendsRequest* const Request = UBasicFriendsGetFriendsRequest::Make(PlayerIdArray, this, {});

	FBeamRequestContext Ctx;

	BeamFriendsApi->CPP_GetFriends(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamFriendsSubsystem::FetchFriendPresenceStatus(FUserSlot UserSlot, TArray<FBeamGamerTag> PlayerGamerTags,
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

						// Updates the local state for the Message PlayerGamerTag 
						if (FriendStates.Contains(PresenceRefreshMessage.PlayerGamerTag))
						{
							FriendStates.Find(PresenceRefreshMessage.PlayerGamerTag)->Status = FriendPresenceStatus;
						}
						else
						{
							FriendStates.Add(PresenceRefreshMessage.PlayerGamerTag,
							                 FBeamFriendState(PresenceRefreshMessage.PlayerGamerTag,
							                                  FriendPresenceStatus));
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
	for (auto PlayerGamerTag : PlayerGamerTags)
	{
		PlayerIdArray.Add(PlayerGamerTag.AsString);
	}
	UPostQueryRequest* const Request = UPostQueryRequest::Make(FOptionalArrayOfString(PlayerIdArray), this, {});

	FBeamRequestContext Ctx;

	BeamPresenceApi->CPP_PostQuery(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamFriendsSubsystem::SendFriendInvite(FUserSlot UserSlot, FBeamGamerTag FriendGamerTag, FBeamOperationHandle Op)
{
	if (!IsUserSlotAuthenticated(UserSlot, BEAM_FUNC_SIG, Op))
	{
		return;
	}
	const auto Handler = FOnPostFriendsInviteFullResponse::CreateLambda(
		[this, UserSlot, FriendGamerTag, Op](const FPostFriendsInviteFullResponse& Resp)
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
						FriendStates.Add(SenderId, FBeamFriendState(SenderId));
					}
					FriendStates[SenderId].SentInvites.Add(FBeamFriendInvite(FriendGamerTag));
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

	UPostFriendsInviteRequest* const Request = UPostFriendsInviteRequest::Make(FriendGamerTag, this, {});

	FBeamRequestContext Ctx;

	BeamFriendsApi->CPP_PostFriendsInvite(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamFriendsSubsystem::AcceptFriendInvite(FUserSlot UserSlot, FBeamGamerTag FriendGamerTag, FBeamOperationHandle Op)
{
	if (!IsUserSlotAuthenticated(UserSlot, BEAM_FUNC_SIG, Op))
	{
		return;
	}
	const auto Handler = FOnPostFriendsMakeFullResponse::CreateLambda(
		[this, UserSlot, FriendGamerTag, Op](const FPostFriendsMakeFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying) return;

			if (Resp.State == RS_Success)
			{
				FBeamGamerTag PlayerGamerTag;

				// Update the local state for the UserSlot, removing the invite from the invites received list and adding the FriendGamerTag in the list of the friends.
				if (TryGetBeamGameTagFromUserSlot(UserSlot, PlayerGamerTag))
				{
					// If there's no data for this player friend list we are adding a dummy at some point it will be updated by the subsystem.
					if (!FriendStates.Contains(PlayerGamerTag))
					{
						FriendStates.Add(PlayerGamerTag, FBeamFriendState(PlayerGamerTag));
					}

					bool ShouldTriggerEvent = false;

					FBeamFriendInvite Invite(FriendGamerTag);
					if (FriendStates[PlayerGamerTag].ReceivedInvites.Contains(Invite))
					{
						FriendStates[PlayerGamerTag].ReceivedInvites.Remove(Invite);
						ShouldTriggerEvent = true;
					}

					FBeamFriendInfo FriendInfo(FriendGamerTag);
					if (!FriendStates[PlayerGamerTag].Friends.Contains(FriendInfo))
					{
						FriendStates[PlayerGamerTag].Friends.Add(FriendInfo);
					}

					//Sometimes the notification could arrive early then the response so we only trigger the event if something actually change in the state
					if (ShouldTriggerEvent)
					{
						//Call when the player accept the another player invite, the notification from the backend will be ignored because of the local already will be called here.
						OnInviteAccepted.Broadcast(FriendGamerTag, UserSlot);
						OnInviteAcceptedCode.Broadcast(FriendGamerTag, UserSlot);

						// Fetching and refreshing the presence status to trigger the presence update
						RefreshPresenceAndTriggerEvent(FriendGamerTag, UserSlot);
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

	UPostFriendsMakeRequest* const Request = UPostFriendsMakeRequest::Make(FriendGamerTag, this, {});

	FBeamRequestContext Ctx;

	BeamFriendsApi->CPP_PostFriendsMake(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamFriendsSubsystem::DeclineFriendInvite(FUserSlot UserSlot, FBeamGamerTag FriendGamerTag,
                                                FBeamOperationHandle Op)
{
	if (!IsUserSlotAuthenticated(UserSlot, BEAM_FUNC_SIG, Op))
	{
		return;
	}
	const auto Handler = FOnDeleteFriendsInviteFullResponse::CreateLambda(
		[this, UserSlot, FriendGamerTag, Op](const FDeleteFriendsInviteFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying) return;

			if (Resp.State == RS_Success)
			{
				FBeamGamerTag PlayerGamerTag;

				// Update the local state for the UserSlot, removing the FriendGamerTag in the list of the friends.
				if (TryGetBeamGameTagFromUserSlot(UserSlot, PlayerGamerTag))
				{
					// If there's no data for this player friend list we are adding a dummy at some point it will be updated by the subsystem.
					if (!FriendStates.Contains(PlayerGamerTag))
					{
						FriendStates.Add(PlayerGamerTag, FBeamFriendState(PlayerGamerTag));
					}

					FriendStates[PlayerGamerTag].ReceivedInvites.Remove(FBeamFriendInvite(FriendGamerTag));
					//Call the on declined event OBS: It's only for the local player that call the event, the sender player will not receive this event as a callback 
					OnInviteDeclined.Broadcast(FriendGamerTag, UserSlot);
					OnInviteDeclinedCode.Broadcast(FriendGamerTag, UserSlot);
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

	UDeleteFriendsInviteRequest* const Request = UDeleteFriendsInviteRequest::Make(FriendGamerTag, this, {});

	FBeamRequestContext Ctx;

	BeamFriendsApi->CPP_DeleteFriendsInvite(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamFriendsSubsystem::BlockPlayer(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag, FBeamOperationHandle Op)
{
	if (!IsUserSlotAuthenticated(UserSlot, BEAM_FUNC_SIG, Op))
	{
		return;
	}
	const auto Handler = FOnPostBlockedFullResponse::CreateLambda(
		[this, UserSlot, PlayerGamerTag, Op](const FPostBlockedFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying) return;

			if (Resp.State == RS_Success)
			{
				FBeamGamerTag SenderId;

				// Update the local state for the UserSlot, removing the PlayerGamerTag in the list of the friends, and adding to the blocked list
				if (TryGetBeamGameTagFromUserSlot(UserSlot, SenderId))
				{
					// If there's no data for this player friend list we are adding a dummy at some point it will be updated by the subsystem.
					if (!FriendStates.Contains(SenderId))
					{
						FriendStates.Add(SenderId, FBeamFriendState(SenderId));
					}

					bool ShouldTriggerEvent = false;

					FBeamFriendInfo FriendInfo(PlayerGamerTag);

					if (FriendStates[SenderId].Friends.Contains(FriendInfo))
					{
						FriendStates[SenderId].Friends.Remove(FriendInfo);
					}

					FBeamPlayerBlocked BlockedPlayer(PlayerGamerTag);
					if (!FriendStates[SenderId].BlockedPlayers.Contains(BlockedPlayer))
					{
						FriendStates[SenderId].BlockedPlayers.Add(BlockedPlayer);
						ShouldTriggerEvent = true;
					}


					//Triggers the player blocked event for the local player
					// Sometimes the changed notifications arrive early then the response, so we need to use that flag to prevent trigger the event twice.
					if (ShouldTriggerEvent)
					{
						OnPlayerBlocked.Broadcast(PlayerGamerTag, UserSlot);
						OnPlayerBlockedCode.Broadcast(PlayerGamerTag, UserSlot);
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

	UPostBlockedRequest* const Request = UPostBlockedRequest::Make(PlayerGamerTag, this, {});

	FBeamRequestContext Ctx;

	BeamFriendsApi->CPP_PostBlocked(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamFriendsSubsystem::UnblockPlayer(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag, FBeamOperationHandle Op)
{
	if (!IsUserSlotAuthenticated(UserSlot, BEAM_FUNC_SIG, Op))
	{
		return;
	}
	const auto Handler = FOnDeleteBlockedFullResponse::CreateLambda(
		[this, UserSlot, PlayerGamerTag, Op](const FDeleteBlockedFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying) return;

			if (Resp.State == RS_Success)
			{
				FBeamGamerTag SenderId;

				// Update the local state for the UserSlot, removing the PlayerGamerTag from the blocked list
				if (TryGetBeamGameTagFromUserSlot(UserSlot, SenderId))
				{
					// If there's no data for this player friend list we are adding a dummy at some point it will be updated by the subsystem.
					if (!FriendStates.Contains(SenderId))
					{
						FriendStates.Add(SenderId, FBeamFriendState(SenderId));
					}
					FBeamPlayerBlocked UnblockedPlayer(PlayerGamerTag);

					if (FriendStates[SenderId].BlockedPlayers.Contains(UnblockedPlayer))
					{
						FriendStates[SenderId].BlockedPlayers.Remove(UnblockedPlayer);
					}

					//Triggers the player unblocked event for the local player
					OnPlayerUnblocked.Broadcast(PlayerGamerTag, UserSlot);
					OnPlayerUnblockedCode.Broadcast(PlayerGamerTag, UserSlot);
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

	UDeleteBlockedRequest* const Request = UDeleteBlockedRequest::Make(PlayerGamerTag, this, {});

	FBeamRequestContext Ctx;

	BeamFriendsApi->CPP_DeleteBlocked(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamFriendsSubsystem::RemoveFriend(FUserSlot UserSlot, FBeamGamerTag FriendGamerTag, FBeamOperationHandle Op)
{
	if (!IsUserSlotAuthenticated(UserSlot, BEAM_FUNC_SIG, Op))
	{
		return;
	}
	const auto Handler = FOnDeleteFriendsFullResponse::CreateLambda(
		[this, UserSlot, FriendGamerTag, Op](const FDeleteFriendsFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying) return;

			if (Resp.State == RS_Success)
			{
				FBeamGamerTag SenderId;

				// Update the local state for the UserSlot, removing the PlayerGamerTag in the list of the friends
				if (TryGetBeamGameTagFromUserSlot(UserSlot, SenderId))
				{
					// If there's no data for this player friend list we are adding a dummy at some point it will be updated by the subsystem.
					if (!FriendStates.Contains(SenderId))
					{
						FriendStates.Add(SenderId, FBeamFriendState(SenderId));
					}

					bool ShouldTriggerEvent = false;

					FBeamFriendInfo FriendInfo(FriendGamerTag);

					if (FriendStates[SenderId].Friends.Contains(FriendInfo))
					{
						FriendStates[SenderId].Friends.Remove(FriendInfo);
						ShouldTriggerEvent = true;
					}
					// Only triggers the event if actually something has been removed
					if (ShouldTriggerEvent)
					{
						//Triggers the friend removed for the local player
						OnFriendRemoved.Broadcast(FriendGamerTag, UserSlot);
						OnFriendRemovedCode.Broadcast(FriendGamerTag, UserSlot);
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

	UDeleteFriendsRequest* const Request = UDeleteFriendsRequest::Make(FriendGamerTag, this, {});

	FBeamRequestContext Ctx;

	BeamFriendsApi->CPP_DeleteFriends(UserSlot, Request, Handler, Ctx, Op, this);
}

bool UBeamFriendsSubsystem::TryGetBeamGameTagFromUserSlot(FUserSlot UserSlot, FBeamGamerTag& PlayerGamerTag)
{
	FBeamRealmUser RealmUser;
	bool success = Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this);
	PlayerGamerTag = RealmUser.GamerTag;
	return success;
}

FBeamFriendState UBeamFriendsSubsystem::MakeFriendState(USocial* Social)
{
	FBeamFriendState FriendState;

	FriendState.PlayerGamerTag = Social->PlayerId;

	for (auto Friend : Social->Friends)
	{
		FriendState.Friends.Add(FBeamFriendInfo(Friend->PlayerId));
	}

	for (auto Invite : Social->Invites)
	{
		if (Invite->Direction == EBeamInvitationDirection::BEAM_outgoing)
		{
			FriendState.SentInvites.Add(FBeamFriendInvite(Invite->PlayerId));
		}
		else if (Invite->Direction == EBeamInvitationDirection::BEAM_incoming)
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

FBeamFriendPresenceStatus UBeamFriendsSubsystem::MakeFriendPresenceStatus(
	FSocialPresenceRefreshNotificationMessage PresenceStatusMessage)
{
	auto FriendPresenceStatus = FBeamFriendPresenceStatus(PresenceStatusMessage.Online,
	                                                      PresenceStatusMessage.LastOnline,
	                                                      PresenceStatusMessage.Status,
	                                                      PresenceStatusMessage.Description);
	return FriendPresenceStatus;
}

void UBeamFriendsSubsystem::RefreshPresenceAndTriggerEvent(FBeamGamerTag FriendGamerTag, FUserSlot UserSlot)
{
	auto Handle = FBeamOperationEventHandlerCode::CreateLambda(
		[this, FriendGamerTag, UserSlot](const FBeamOperationEvent& Evt)
		{
			if (Evt.EventType == OET_SUCCESS)
			{
				OnFriendPresenceStatusUpdate.Broadcast(FriendGamerTag, UserSlot);
				OnFriendPresenceStatusUpdateCode.Broadcast(FriendGamerTag, UserSlot);
			}
			else
			{
				OnFriendPresenceStatusUpdateError.Broadcast(FriendGamerTag, UserSlot);
				OnFriendPresenceStatusUpdateErrorCode.Broadcast(FriendGamerTag, UserSlot);
			}
		});
	CPP_FetchFriendPresenceStatusOperation(UserSlot, {FriendGamerTag}, Handle);
}

void UBeamFriendsSubsystem::SocialRefreshNotificationHandler(FSocialRefreshNotificationMessage Message,
                                                             FUserSlot UserSlot)
{
	UE_LOG(LogBeamFriend, Display,
	       TEXT(
		       "Received notification from the FriendNotification for the UserSlot: %s with the Friend Id: %lld | Player Id: %lld"
	       ),
	       *UserSlot.Name,
	       Message.FriendGamerTag.AsLong,
	       Message.PlayerGamerTag.AsLong);

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

	if (RealmUser.GamerTag == Message.PlayerGamerTag)
	{
		// If there's no data for this player friend list we are adding a dummy at some point it will be updated by the subsystem.
		// It's only create for the player id because we assume that the friend already been updated once it is who made the request.
		if (!FriendStates.Contains(RealmUser.GamerTag))
		{
			FriendStates.Add(RealmUser.GamerTag, FBeamFriendState(RealmUser.GamerTag));
		}
	}

	switch (Message.EventType)
	{
	case EBeamFriendEventType::BEAM_friend:
		//Check if the Message Player Id is the current UserSlot that received the message
		//This will allow to refresh the state of this player after received the event
		if (RealmUser.GamerTag == Message.PlayerGamerTag)
		{
			// Adding the friend to the player that sent the invite
			auto FriendState = FBeamFriendInfo(Message.FriendGamerTag);

			bool ShouldTriggerEvent = false;

			if (!FriendStates[RealmUser.GamerTag].Friends.Contains(FriendState))
			{
				FriendStates[RealmUser.GamerTag].Friends.Add(FriendState);
				ShouldTriggerEvent = true;
			}
			// Removing the invite after the other player accept it.
			auto FriendInviteState = FBeamFriendInvite(Message.FriendGamerTag);
			if (FriendStates[RealmUser.GamerTag].SentInvites.Contains(FriendInviteState))
			{
				FriendStates[RealmUser.GamerTag].SentInvites.Remove(FriendInviteState);
			}
			if (ShouldTriggerEvent)
			{
				OnInviteAccepted.Broadcast(Message.FriendGamerTag, UserSlot);
				OnInviteAcceptedCode.Broadcast(Message.FriendGamerTag, UserSlot);

				// Fetching and refreshing the presence status to trigger the presence update
				RefreshPresenceAndTriggerEvent(Message.FriendGamerTag, UserSlot);
			}
		}
		else if (RealmUser.GamerTag == Message.FriendGamerTag)
		{
			bool ShouldTriggerEvent = false;

			// Adding the friend to the player that sent the invite
			auto FriendState = FBeamFriendInfo(Message.PlayerGamerTag);

			if (!FriendStates[RealmUser.GamerTag].Friends.Contains(FriendState))
			{
				FriendStates[RealmUser.GamerTag].Friends.Add(FriendState);
				ShouldTriggerEvent = true;
			}

			// Removing the invite after accept it.
			auto FriendInviteState = FBeamFriendInvite(Message.PlayerGamerTag);
			if (FriendStates[RealmUser.GamerTag].ReceivedInvites.Contains(FriendInviteState))
			{
				FriendStates[RealmUser.GamerTag].ReceivedInvites.Remove(FriendInviteState);
			}
			//This flag guarantee if the player still don't exist in the local state this means the local state wasn't updated before received the notification
			//Without verify it we probably call it twice once in the AcceptFriendInvite and another here
			//This is only true for the player that made the action of accept the invite (the friend)
			if (ShouldTriggerEvent)
			{
				OnInviteAccepted.Broadcast(Message.PlayerGamerTag, UserSlot);
				OnInviteAcceptedCode.Broadcast(Message.PlayerGamerTag, UserSlot);

				// Fetching and refreshing the presence status to trigger the presence update
				RefreshPresenceAndTriggerEvent(Message.PlayerGamerTag, UserSlot);
			}
		}
		break;
	case EBeamFriendEventType::BEAM_unfriend:
		//The Message.PlayerGamerTag is the GamerTag of the player who did the action of remove the friend
		if (RealmUser.GamerTag == Message.PlayerGamerTag)
		{
			bool ShouldTriggerEvent = false;

			// Removing the friend to the player that was removed from other player friend list.
			auto FriendState = FBeamFriendInfo(Message.FriendGamerTag);
			if (FriendStates[RealmUser.GamerTag].Friends.Contains(FriendState))
			{
				FriendStates[RealmUser.GamerTag].Friends.Remove(FriendState);
				ShouldTriggerEvent = true;
			}
			// This only should called if the Friend has been removed from the local state
			if (ShouldTriggerEvent)
			{
				OnFriendRemoved.Broadcast(Message.FriendGamerTag, UserSlot);
				OnFriendRemovedCode.Broadcast(Message.FriendGamerTag, UserSlot);
			}
		}
		else if (RealmUser.GamerTag == Message.FriendGamerTag)
		{
			bool ShouldTriggerEvent = false;

			// Removing the friend to the player that was removed from other player friend list.
			auto FriendState = FBeamFriendInfo(Message.PlayerGamerTag);
			if (FriendStates[RealmUser.GamerTag].Friends.Contains(FriendState))
			{
				FriendStates[RealmUser.GamerTag].Friends.Remove(FriendState);
				ShouldTriggerEvent = true;
			}

			if (ShouldTriggerEvent)
			{
				OnFriendRemoved.Broadcast(Message.PlayerGamerTag, UserSlot);
				OnFriendRemovedCode.Broadcast(Message.PlayerGamerTag, UserSlot);
			}
		}
		break;
	case EBeamFriendEventType::BEAM_block:
		if (RealmUser.GamerTag == Message.PlayerGamerTag)
		{
			bool ShouldTriggerEvent = false;

			// Adding the blocked friend to the list of the blocked players.
			auto BlockedPlayer = FBeamPlayerBlocked(Message.FriendGamerTag);
			if (!FriendStates[RealmUser.GamerTag].BlockedPlayers.Contains(BlockedPlayer))
			{
				FriendStates[RealmUser.GamerTag].BlockedPlayers.Add(BlockedPlayer);
				ShouldTriggerEvent = true;
			}
			// Removing the friend from the friend list as it has been blocked by the player
			auto FriendState = FBeamFriendInfo(Message.FriendGamerTag);
			if (FriendStates[RealmUser.GamerTag].Friends.Contains(FriendState))
			{
				FriendStates[RealmUser.GamerTag].Friends.Remove(FriendState);
			}
			// Only triggers the event if actually something change in the blocked list
			if (ShouldTriggerEvent)
			{
				OnPlayerBlocked.Broadcast(Message.FriendGamerTag, UserSlot);
				OnPlayerBlockedCode.Broadcast(Message.FriendGamerTag, UserSlot);
			}
		}
		else if (RealmUser.GamerTag == Message.FriendGamerTag)
		{
			// Warning the player about being blocked by another player
			OnPlayerBeenBlocked.Broadcast(Message.PlayerGamerTag, UserSlot);
			OnPlayerBeenBlockedCode.Broadcast(Message.PlayerGamerTag, UserSlot);
		}
		break;
	case EBeamFriendEventType::BEAM_unblock:
		if (RealmUser.GamerTag == Message.PlayerGamerTag)
		{
			bool ShouldTriggerEvent = false;
			// Removing the blocked player from the local state.
			auto BlockedPlayer = FBeamPlayerBlocked(Message.FriendGamerTag);
			if (FriendStates[RealmUser.GamerTag].BlockedPlayers.Contains(BlockedPlayer))
			{
				FriendStates[RealmUser.GamerTag].BlockedPlayers.Remove(BlockedPlayer);
				ShouldTriggerEvent = true;
			}
			// Only will trigger the event if something actually happen in the blocked players states
			if (ShouldTriggerEvent)
			{
				OnPlayerUnblocked.Broadcast(Message.FriendGamerTag, UserSlot);
				OnPlayerUnblockedCode.Broadcast(Message.FriendGamerTag, UserSlot);
			}
		}
		else if (RealmUser.GamerTag == Message.FriendGamerTag)
		{
			// Warning the player about being unblocked by another player
			OnPlayerBeenUnblocked.Broadcast(Message.PlayerGamerTag, UserSlot);
			OnPlayerBeenUnblockedCode.Broadcast(Message.PlayerGamerTag, UserSlot);
		}
		break;
	default:

		break;
	}
}

void UBeamFriendsSubsystem::SocialPresenceRefreshNotificationHandler(FSocialPresenceRefreshNotificationMessage Message,
                                                                     FUserSlot UserSlot)
{
	auto FriendPresenceStatus = MakeFriendPresenceStatus(Message);
	// Updates the local state for the Message PlayerGamerTag 
	if (FriendStates.Contains(Message.PlayerGamerTag))
	{
		FriendStates.Find(Message.PlayerGamerTag)->Status = FriendPresenceStatus;
	}
	else
	{
		FriendStates.Add(Message.PlayerGamerTag, FBeamFriendState(Message.PlayerGamerTag, FriendPresenceStatus));
	}

	UE_LOG(LogBeamFriend, Display,
	       TEXT(
		       "Received notification from the FriendPresenceNotification for the UserSlot: %s with the Friend Id: %lld"
	       ),
	       *UserSlot.Name,
	       Message.PlayerGamerTag.AsLong);

	// Triggers the event of the Friend Presence Changed.
	OnFriendPresenceStatusUpdate.Broadcast(Message.PlayerGamerTag, UserSlot);
	OnFriendPresenceStatusUpdateCode.Broadcast(Message.PlayerGamerTag, UserSlot);
}

void UBeamFriendsSubsystem::MailRefreshNotificationHandler(FMailRefreshNotificationMessage Message,
                                                           FUserSlot UserSlot)
{
	FBeamRealmUser RealmUser;

	if (Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		// Get the state before fetch the data to compare the state with the new data and get the player that sent the invite.
		TArray<FBeamFriendInvite> ReceivedInvites;
		FBeamGamerTag PlayerGamerTag = RealmUser.GamerTag;
		if (FriendStates.Contains(PlayerGamerTag))
		{
			ReceivedInvites = FriendStates[PlayerGamerTag].ReceivedInvites;
		}

		// Fetch the state for the FriendStates, when it is called the state is already updated.
		const FBeamOperationEventHandlerCode Handler = FBeamOperationEventHandlerCode::CreateLambda(
			[this, PlayerGamerTag, ReceivedInvites, UserSlot](const FBeamOperationEvent Evt)
			{
				if (Evt.EventType == OET_SUCCESS)
				{
					//Compare the old invites with the new one and trigger the OnFriendInviteReceived with all the PlayerGamerTags of the received invites.
					if (FriendStates.Contains(PlayerGamerTag))
					{
						for (FBeamFriendInvite FriendInvite : FriendStates[PlayerGamerTag].ReceivedInvites)
						{
							if (!ReceivedInvites.Contains(FriendInvite))
							{
								OnInviteReceived.Broadcast(FriendInvite.FriendGamerTag, UserSlot);
								OnInviteReceivedCode.Broadcast(FriendInvite.FriendGamerTag, UserSlot);
							}
						}
					}
				}
				else
				{
					UE_LOG(LogBeamFriend, Error, TEXT("Failed to fetch the state of the friends in the %hs"),
					       BEAM_FUNC_SIG);
				}
			});
		CPP_FetchPlayerFriendStateOperation(UserSlot, Handler);
	}
}
