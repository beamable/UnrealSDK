// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Party/BeamPartySubsystem.h"

#include "AutoGen/SubSystems/Social/PostFriendsInviteRequest.h"
#include "BeamNotifications/SubSystems/BeamInventoryNotifications.h"


void UBeamPartySubsystem::InitializeWhenUnrealReady_Implementation(FBeamOperationHandle& ResultOp)
{
	PartyApi = GEngine->GetEngineSubsystem<UBeamPartyApi>();
	PlayerPartyApi = GEngine->GetEngineSubsystem<UBeamPlayerPartyApi>();
	PartyNotifications = GEngine->GetEngineSubsystem<UBeamPartyNotifications>();
	
	
	Super::InitializeWhenUnrealReady_Implementation(ResultOp);
}

void UBeamPartySubsystem::OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser,
	const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp)
{
	const auto PartyUpdateHandler = FOnPartyRefreshNotificationCode::CreateUFunction(this, GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, OnPartyUpdatedHandler), UserSlot);
	PartyNotifications->CPP_SubscribeToPartyRefresh(UserSlot, Runtime->DefaultNotificationChannel, PartyUpdateHandler, this);

	Super::OnUserSignedIn_Implementation(UserSlot, BeamRealmUser, bIsOwnerUserAuth, ResultOp);
}

void UBeamPartySubsystem::OnPostUserSignedIn_Implementation(const FUserSlot& UserSlot,
	const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp)
{

	Super::OnPostUserSignedIn_Implementation(UserSlot, BeamRealmUser, bIsOwnerUserAuth, ResultOp);
}

bool UBeamPartySubsystem::TryGetUserPartyState(const FUserSlot& User, FBeamPartyState& PartyState)
{
	return TryGetPlayerParty(User, PartyState);
}

FBeamOperationHandle UBeamPartySubsystem::JoinPartyOperation(FUserSlot User, FGuid PartyId,
	FBeamOperationEventHandler OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({User}, GetClass()->GetFName().ToString(), OperationEventHandler);
	JoinParty(User, PartyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_JoinPartyOperation(FUserSlot User, FGuid PartyId,
	FBeamOperationEventHandlerCode OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({User}, GetClass()->GetFName().ToString(), OperationEventHandler);
	JoinParty(User, PartyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::FetchPartyInvitesOperation(FUserSlot User,
	FBeamOperationEventHandler OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({User}, GetClass()->GetFName().ToString(), OperationEventHandler);
	FetchPartyInvites(User, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_FetchPartyInvitesOperation(FUserSlot User,
	FBeamOperationEventHandlerCode OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({User}, GetClass()->GetFName().ToString(), OperationEventHandler);
	FetchPartyInvites(User, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::FetchPartyStateOperation(FUserSlot User, FGuid PartyId,
                                                                   FBeamOperationEventHandler OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({User}, GetClass()->GetFName().ToString(), OperationEventHandler);
	FetchPartyState(User, PartyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_FetchPartyStateOperation(FUserSlot User, FGuid PartyId,
	FBeamOperationEventHandlerCode OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({User}, GetClass()->GetFName().ToString(), OperationEventHandler);
	FetchPartyState(User, PartyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CreatePartyOperation(FUserSlot User, EBeamPartyRestriction Restriction,
                                                               int32 maxPlayers, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({User}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CreateParty(User, Restriction, maxPlayers, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_CreatePartyOperation(FUserSlot User, EBeamPartyRestriction Restriction,
	int32 maxPlayers, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({User}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CreateParty(User, Restriction, maxPlayers, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::InvitePlayerToPartyOperation(FUserSlot User, FGuid PartyId, FBeamGamerTag Player,
	FBeamOperationEventHandler OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({User}, GetClass()->GetFName().ToString(), OperationEventHandler);
	InvitePlayerToParty(User, PartyId, Player, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_InvitePlayerToPartyOperation(FUserSlot User, FGuid PartyId, FBeamGamerTag Player,
	FBeamOperationEventHandlerCode OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({User}, GetClass()->GetFName().ToString(), OperationEventHandler);
	InvitePlayerToParty(User, PartyId, Player, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::DeletePlayerPartyInviteOperation(FUserSlot User, FGuid PartyId, FBeamGamerTag Player,
	FBeamOperationEventHandler OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({User}, GetClass()->GetFName().ToString(), OperationEventHandler);
	DeletePlayerPartyInvite(User, PartyId, Player, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_DeletePlayerPartyInviteOperation(FUserSlot User, FGuid PartyId, FBeamGamerTag Player,
	FBeamOperationEventHandlerCode OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({User}, GetClass()->GetFName().ToString(), OperationEventHandler);
	DeletePlayerPartyInvite(User, PartyId, Player, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::LeavePartyOperation(FUserSlot User, FGuid PartyId,
	FBeamOperationEventHandler OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({User}, GetClass()->GetFName().ToString(), OperationEventHandler);
	LeaveParty(User, PartyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_LeavePartyOperation(FUserSlot User, FGuid PartyId,
	FBeamOperationEventHandlerCode OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({User}, GetClass()->GetFName().ToString(), OperationEventHandler);
	LeaveParty(User, PartyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::KickPlayerOperation(FUserSlot User, FGuid PartyId, FBeamGamerTag Player,
	FBeamOperationEventHandler OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({User}, GetClass()->GetFName().ToString(), OperationEventHandler);
	KickPlayer(User, PartyId, Player, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_KickPlayerOperation(FUserSlot User, FGuid PartyId, FBeamGamerTag Player,
	FBeamOperationEventHandlerCode OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({User}, GetClass()->GetFName().ToString(), OperationEventHandler);
	KickPlayer(User, PartyId, Player, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::PromotePlayerToLeaderOperation(FUserSlot User, FGuid PartyId, FBeamGamerTag Player,
	FBeamOperationEventHandler OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({User}, GetClass()->GetFName().ToString(), OperationEventHandler);
	PromotePlayerToLeader(User, PartyId, Player, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_PromotePlayerToLeaderOperation(FUserSlot User, FGuid PartyId, FBeamGamerTag Player,
	FBeamOperationEventHandlerCode OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({User}, GetClass()->GetFName().ToString(), OperationEventHandler);
	PromotePlayerToLeader(User, PartyId, Player, Handle);
	return Handle;
}


bool UBeamPartySubsystem::TryGetPlayerParty(FUserSlot User, FBeamPartyState& PartyState)
{
	FBeamRealmUser RealmUser;
	
	if (!Runtime->UserSlotSystem->GetUserDataAtSlot(User, RealmUser, this))
	{
		return false;
	}

	for (const auto& Item : PartyStates)
	{
		if (Item.Value.PlayerStates.Contains(RealmUser.GamerTag))
		{
			PartyState = Item.Value;
			return true;
		}
	}

	return false;
}


bool UBeamPartySubsystem::TryGetAvailableInvites(FUserSlot User, TArray<FBeamPartyInviteState>& Invites)
{
	if (!PartyInvitesState.Contains(User)) return false;

	Invites.Reset();
	
	for (const auto& InviteState : PartyInvitesState[User])
	{
		Invites.Add(InviteState);
	}
	return true;
}


void UBeamPartySubsystem::FetchPartyState(FUserSlot User, FGuid PartyId, FBeamOperationHandle Op)
{
	FOnGetPartyFullResponse Handler = FOnGetPartyFullResponse::CreateLambda([this, PartyId, Op](const FBeamFullResponse<UGetPartyRequest*, UParty*>& Resp)
	{
		if(Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			FBeamPartyState PartyState = MakePartyState(Resp.SuccessData);
			
			if (PartyStates.Contains(PartyId))
			{
				PartyStates[PartyId] = PartyState;
			}else
			{
				PartyStates.Add(PartyState.PartyId, PartyState);
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
		}
	});

	UGetPartyRequest* const Request = UGetPartyRequest::Make(PartyId, this, {});

	FBeamRequestContext Ctx;
	
	PartyApi->CPP_GetParty(User, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::FetchPartyInvites(FUserSlot User, FBeamOperationHandle Op)
{
	FOnGetPartyInvitesFullResponse Handler = FOnGetPartyInvitesFullResponse::CreateLambda([this, User, Op](const FGetPartyInvitesFullResponse& Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			if (!PartyInvitesState.Contains(User))
			{
				PartyInvitesState.Add(User, {});
			}else
			{
				PartyInvitesState[User].Reset();
			}
			
			for (auto Invitation : Resp.SuccessData->Invitations.Val)
			{
				PartyInvitesState[User].Add(FBeamPartyInviteState(FGuid(Invitation->PartyId.Val), FBeamGamerTag(Invitation->InvitedBy.Val)));
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
		}
	});

	FBeamRealmUser RealmUser;

	if (!Runtime->UserSlotSystem->GetUserDataAtSlot(User, RealmUser, this))
	{
		return;
	}

	FBeamRequestContext Ctx;

	UGetPartyInvitesRequest* const Request = UGetPartyInvitesRequest::Make(RealmUser.GamerTag.AsString, this, {});

	PlayerPartyApi->CPP_GetPartyInvites(User, Request, Handler, Ctx, Op, this);
}


bool UBeamPartySubsystem::CreateParty(FUserSlot User, EBeamPartyRestriction Restriction, int32 maxPlayers, FBeamOperationHandle Op)
{
	FOnPostPartiesFullResponse Handler = FOnPostPartiesFullResponse::CreateLambda([this, Op] (const FPostPartiesFullResponse& Resp)
	{
		if(Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			FBeamPartyState PartyState = MakePartyState(Resp.SuccessData);
			PartyStates.Add(PartyState.PartyId, PartyState);
			
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
		}
	});

	FBeamRealmUser RealmUser;

	if (!Runtime->UserSlotSystem->GetUserDataAtSlot(User, RealmUser, this))
	{
		return false;
	}


	
	UPostPartiesRequest* const Request = UPostPartiesRequest::Make(FOptionalString(GetRestrictionString(Restriction)), FOptionalBeamGamerTag(RealmUser.GamerTag), FOptionalInt32(maxPlayers), GetTransientPackage(),{});

	FBeamRequestContext Ctx;
	
	PartyApi->CPP_PostParties(User, Request, Handler, Ctx, Op, this);
	
	return true;
}

void UBeamPartySubsystem::JoinParty(FUserSlot User, FGuid PartyId, FBeamOperationHandle Op)
{
	FOnPutPartyFullResponse Handler = FOnPutPartyFullResponse::CreateLambda([this, PartyId, Op] (const FPutPartyFullResponse& Resp)
	{
		if (Resp.State == RS_Retrying) return;
		
		if (Resp.State == RS_Success)
		{
			if (PartyStates.Contains(PartyId))
			{
				PartyStates[PartyId] = MakePartyState(Resp.SuccessData);
			}else
			{
				PartyStates.Add(PartyId, MakePartyState(Resp.SuccessData));
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

	UPutPartyRequest* const Request = UPutPartyRequest::Make(PartyId, this, {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_PutParty(User, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::InvitePlayerToParty(FUserSlot User, FGuid PartyId, FBeamGamerTag Player, FBeamOperationHandle Op)
{
	FOnApiPartyPostInviteByIdFullResponse Handler = FOnApiPartyPostInviteByIdFullResponse::CreateLambda([this,  Op](const FApiPartyPostInviteByIdFullResponse& Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
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
	
	UApiPartyPostInviteByIdRequest* const Request = UApiPartyPostInviteByIdRequest::Make(PartyId, FOptionalBeamGamerTag(Player), this, {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_PostInvite(User, Request, Handler, Ctx, Op, this);
	
}

void UBeamPartySubsystem::DeletePlayerPartyInvite(FUserSlot User, FGuid PartyId, FBeamGamerTag Player, FBeamOperationHandle Op)
{
	FOnDeleteInviteFullResponse Handler = FOnDeleteInviteFullResponse::CreateLambda([this, Op](const FDeleteInviteFullResponse& Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
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
	
	UDeleteInviteRequest* const Request = UDeleteInviteRequest::Make(PartyId, FOptionalBeamGamerTag(Player), this, {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_DeleteInvite(User, Request, Handler, Ctx, Op, this);
}


void UBeamPartySubsystem::LeaveParty(FUserSlot User, FGuid PartyId, FBeamOperationHandle Op)
{
	FOnDeleteMembersFullResponse Handler = FOnDeleteMembersFullResponse::CreateLambda([this, Op](const FDeleteMembersFullResponse& Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
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

	FBeamRealmUser RealmUser;

	if (!Runtime->UserSlotSystem->GetUserDataAtSlot(User, RealmUser, this))
	{
		return;
	}
	
	UDeleteMembersRequest* const Request = UDeleteMembersRequest::Make(PartyId, FOptionalBeamGamerTag(RealmUser.GamerTag), this, {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_DeleteMembers(User, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::KickPlayer(FUserSlot User, FGuid PartyId, FBeamGamerTag Player, FBeamOperationHandle Op)
{
	FOnDeleteMembersFullResponse Handler = FOnDeleteMembersFullResponse::CreateLambda([this, Op](const FDeleteMembersFullResponse& Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
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
	
	UDeleteMembersRequest* const Request = UDeleteMembersRequest::Make(PartyId, FOptionalBeamGamerTag(Player), this, {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_DeleteMembers(User, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::PromotePlayerToLeader(FUserSlot User, FGuid PartyId, FBeamGamerTag Player, FBeamOperationHandle Op)
{
	FOnPutPromoteFullResponse Handler = FOnPutPromoteFullResponse::CreateLambda([this, PartyId, Op](const FPutPromoteFullResponse& Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			if (PartyStates.Contains(PartyId))
			{
				PartyStates[PartyId] = MakePartyState(Resp.SuccessData);
			}else
			{
				PartyStates.Add(PartyId, MakePartyState(Resp.SuccessData));
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
	
	
	UPutPromoteRequest* const Request = UPutPromoteRequest::Make(PartyId, FOptionalBeamGamerTag(Player), this, {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_PutPromote(User, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::OnPartyUpdatedHandler(FPartyRefreshNotificationMessage Msg, FUserSlot User)
{
	switch (Msg.Type)
	{
		case EBeamPartyEvent::BEAM_PlayerJoined:
			OnPlayerJoinedEventReceived(Msg.PartyId, User);
			break;
		case EBeamPartyEvent::BEAM_PartyUpdated:
			OnPartyUpdatedEventReceived(Msg.PartyId, User);
			break;
		case EBeamPartyEvent::BEAM_PlayerInvited:
			OnPlayerInvitedEventReceived(Msg.PartyId, User);
			break;
		case EBeamPartyEvent::BEAM_PlayerKicked:
			OnPlayerKickedEventReceived(Msg.PartyId, User);
			break;
		case EBeamPartyEvent::BEAM_PlayerLeft:
			OnPlayerLeftEventReceived(Msg.PartyId, User);
			break;
		case EBeamPartyEvent::BEAM_PlayerInviteCanceled:
			OnPlayerInviteCanceledEventReceived(Msg.PartyId, User);
			break;
		case EBeamPartyEvent::BEAM_PlayerInviteExpired:
			OnPlayerInviteExpiredEventReceived(Msg.PartyId, User);
			break;
		case EBeamPartyEvent::BEAM_PlayerPromotedToLeader:
			OnPlayerPromotedToLeaderEventReceived(Msg.PartyId, User);
			break;
	}
}

void UBeamPartySubsystem::OnPlayerJoinedEventReceived(FGuid PartyId, FUserSlot User)
{
	FBeamOperationEventHandlerCode Handler = FBeamOperationEventHandlerCode::CreateLambda([this, PartyId, User](FBeamOperationEvent Evt)
	{
		if (Evt.EventType == OET_SUCCESS)
		{
			OnPlayerJoinedCode.Broadcast(PartyId, User);
			OnPlayerJoined.Broadcast(PartyId, User);
		}else
		{
			UE_LOG(LogTemp, Error, TEXT("Error on FetchPartyStateOperation"));
		}
	});
	CPP_FetchPartyStateOperation(User, PartyId, Handler);

	UE_LOG(LogTemp, Display, TEXT("OnPlayerJoinedEventReceived PartyID: %s"), *PartyId.ToString());
	
}

void UBeamPartySubsystem::OnPlayerLeftEventReceived(FGuid PartyId, FUserSlot User)
{
	FBeamOperationEventHandlerCode Handler = FBeamOperationEventHandlerCode::CreateLambda([this, PartyId, User](FBeamOperationEvent Evt)
	{
		if (Evt.EventType == OET_SUCCESS)
		{
			OnPlayerLeftCode.Broadcast(PartyId, User);
			OnPlayerLeft.Broadcast(PartyId, User);
		}else
		{
			UE_LOG(LogTemp, Error, TEXT("Error on FetchPartyStateOperation"));
		}
	});
	CPP_FetchPartyStateOperation(User, PartyId, Handler);

	UE_LOG(LogTemp, Display, TEXT("OnPlayerLeftEventReceived"));
}

void UBeamPartySubsystem::OnPlayerInvitedEventReceived(FGuid PartyId, FUserSlot User)
{
	FBeamOperationEventHandlerCode Handler = FBeamOperationEventHandlerCode::CreateLambda([this, PartyId, User](FBeamOperationEvent Evt)
	{
		if (Evt.EventType == OET_SUCCESS)
		{
			OnPlayerInvitedCode.Broadcast(PartyId, User);
			OnPlayerInvited.Broadcast(PartyId, User);
		}else
		{
			UE_LOG(LogTemp, Error, TEXT("Error on FetchInvitesStatesOperation"));
		}
	});
	CPP_FetchPartyInvitesOperation(User, Handler);
	UE_LOG(LogTemp, Warning, TEXT("OnPlayerInvitedEventReceived"));
}

void UBeamPartySubsystem::OnPartyUpdatedEventReceived(FGuid PartyId, FUserSlot User)
{
	FBeamOperationEventHandlerCode Handler = FBeamOperationEventHandlerCode::CreateLambda([this, PartyId, User](FBeamOperationEvent Evt)
	{
		if (Evt.EventType == OET_SUCCESS)
		{
			OnPartyUpdatedCode.Broadcast(PartyId, User);
			OnPartyUpdated.Broadcast(PartyId, User);
		}else
		{
			UE_LOG(LogTemp, Error, TEXT("Error on FetchPartyStateOperation"));
		}
	});
	CPP_FetchPartyStateOperation(User, PartyId, Handler);
	UE_LOG(LogTemp, Warning, TEXT("OnPartyUpdatedEventReceived"));
}

void UBeamPartySubsystem::OnPlayerPromotedToLeaderEventReceived(FGuid PartyId, FUserSlot User)
{
	FBeamOperationEventHandlerCode Handler = FBeamOperationEventHandlerCode::CreateLambda([this, PartyId, User](FBeamOperationEvent Evt)
	{
		if (Evt.EventType == OET_SUCCESS)
		{
			OnPlayerPromotedToLeaderCode.Broadcast(PartyId, User);
			OnPlayerPromotedToLeader.Broadcast(PartyId, User);
		}else
		{
			UE_LOG(LogTemp, Error, TEXT("Error on FetchPartyStateOperation"));
		}
	});
	CPP_FetchPartyStateOperation(User, PartyId, Handler);
	UE_LOG(LogTemp, Warning, TEXT("OnPlayerPromotedToLeaderEventReceived"));
}

void UBeamPartySubsystem::OnPlayerKickedEventReceived(FGuid PartyId, FUserSlot User)
{
	FBeamOperationEventHandlerCode Handler = FBeamOperationEventHandlerCode::CreateLambda([this, PartyId, User](FBeamOperationEvent Evt)
	{
		if (Evt.EventType == OET_SUCCESS)
		{
			OnPlayerKickedCode.Broadcast(PartyId, User);
			OnPlayerKicked.Broadcast(PartyId, User);
		}else
		{
			UE_LOG(LogTemp, Error, TEXT("Error on FetchPartyStateOperation"));
		}
	});
	CPP_FetchPartyStateOperation(User, PartyId, Handler);
	UE_LOG(LogTemp, Warning, TEXT("OnPlayerKickedEventReceived"));
}

void UBeamPartySubsystem::OnPlayerInviteCanceledEventReceived(FGuid PartyId, FUserSlot User)
{
	FBeamOperationEventHandlerCode Handler = FBeamOperationEventHandlerCode::CreateLambda([this, PartyId, User](FBeamOperationEvent Evt)
	{
		if (Evt.EventType == OET_SUCCESS)
		{
			FBeamOperationEventHandlerCode Handler = FBeamOperationEventHandlerCode::CreateLambda([this, PartyId, User](FBeamOperationEvent Evt)
			{
				if (Evt.EventType == OET_SUCCESS)
				{
					OnPlayerInviteCanceledCode.Broadcast(PartyId, User);
					OnPlayerInviteCanceled.Broadcast(PartyId, User);
				}else
				{
					UE_LOG(LogTemp, Error, TEXT("Error on FetchInvitesStatesOperation"));
				}
			});
			CPP_FetchPartyInvitesOperation(User, Handler);
		}else
		{
			UE_LOG(LogTemp, Error, TEXT("Error on FetchPartyStateOperation"));
		}
	});
	CPP_FetchPartyStateOperation(User, PartyId, Handler);
	
	UE_LOG(LogTemp, Warning, TEXT("OnPlayerInviteCanceledEventReceived"));
}

void UBeamPartySubsystem::OnPlayerInviteExpiredEventReceived(FGuid PartyId, FUserSlot User)
{
	FBeamOperationEventHandlerCode Handler = FBeamOperationEventHandlerCode::CreateLambda([this, PartyId, User](FBeamOperationEvent Evt)
	{
		if (Evt.EventType == OET_SUCCESS)
		{
			FBeamOperationEventHandlerCode Handler = FBeamOperationEventHandlerCode::CreateLambda([this, PartyId, User](FBeamOperationEvent Evt)
			{
				if (Evt.EventType == OET_SUCCESS)
				{
					OnPlayerInviteCanceledCode.Broadcast(PartyId, User);
					OnPlayerInviteCanceled.Broadcast(PartyId, User);
				}else
				{
					UE_LOG(LogTemp, Error, TEXT("Error on FetchInvitesStatesOperation"));
				}
			});
			CPP_FetchPartyInvitesOperation(User, Handler);
		}else
		{
			UE_LOG(LogTemp, Error, TEXT("Error on FetchPartyStateOperation"));
		}
	});
	CPP_FetchPartyStateOperation(User, PartyId, Handler);
	
	UE_LOG(LogTemp, Warning, TEXT("OnPlayerInviteExpiredEventReceived"));
}


FBeamPartyState UBeamPartySubsystem::MakePartyState(UParty* Party)
{
	FBeamPartyState PartyState = FBeamPartyState();
	PartyState.PartyId = FGuid(Party->Id.Val);
	PartyState.MaxPlayers = Party->MaxSize.Val;
	PartyState.Leader = Party->Leader.Val;
	for (auto BeamGameTag : Party->Members.Val)
	{
		PartyState.PlayerStates.Add(BeamGameTag, FBeamPartyPlayerState(BeamGameTag));
	}
	for (auto InvitedPlayer : Party->PendingInvites.Val)
	{
		PartyState.InvitedPlayers.Add(InvitedPlayer);
	}
	return PartyState;
}

FString UBeamPartySubsystem::GetRestrictionString(EBeamPartyRestriction RestrictionType)
{
	switch (RestrictionType)
	{
		case EBeamPartyRestriction::BEAM_Unrestricted:
			return "Unrestricted";
		case EBeamPartyRestriction::BEAM_InviteOnly:
			return "InviteOnly";
		default:
			return "";
	}
}

