// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Party/BeamPartySubsystem.h"

#include "AutoGen/Optionals/OptionalGamerTag.h"
#include "AutoGen/SubSystems/Social/PostFriendsInviteRequest.h"
#include "BeamNotifications/SubSystems/BeamInventoryNotifications.h"
#include "Subsystems/Inventory/BeamInventorySubsystem.h"

#define stringify( name ) # name

void UBeamPartySubsystem::InitializeWhenUnrealReady_Implementation(FBeamOperationHandle& ResultOp)
{
	// Initializing the subsystems after unreal is ready
	PartyApi = GEngine->GetEngineSubsystem<UBeamPartyApi>();
	PlayerPartyApi = GEngine->GetEngineSubsystem<UBeamPlayerPartyApi>();
	PartyNotifications = GEngine->GetEngineSubsystem<UBeamPartyNotifications>();
	
	
	Super::InitializeWhenUnrealReady_Implementation(ResultOp);
}

void UBeamPartySubsystem::OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser,
	const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp)
{
	//Register notifications for party on user signed in
	const auto PartyUpdateHandler = FOnPartyRefreshNotificationCode::CreateUFunction(this, GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, PartyUpdatedMessageHandler), UserSlot);
	PartyNotifications->CPP_SubscribeToPartyRefresh(UserSlot, Runtime->DefaultNotificationChannel, PartyUpdateHandler, this);

	Super::OnUserSignedIn_Implementation(UserSlot, BeamRealmUser, bIsOwnerUserAuth, ResultOp);
}

void UBeamPartySubsystem::OnPostUserSignedOut_Implementation(const FUserSlot& UserSlot,
	const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp)
{
	// Clean up party and invite states
	PartyStates.Reset();
	if (PartyInvitesState.Contains(UserSlot))
	{
		PartyInvitesState[UserSlot].Reset();
		PartyInvitesState.Remove(UserSlot);
	}
	
	Super::OnPostUserSignedOut_Implementation(UserSlot, Reason, BeamRealmUser, ResultOp);
}


bool UBeamPartySubsystem::TryGetUserPartyState(FUserSlot UserSlot, FBeamPartyState& PartyState)
{
	return TryGetPlayerParty(UserSlot, PartyState);
}

bool UBeamPartySubsystem::TryGetUserInvitesState(FUserSlot UserSlot, TArray<FBeamPartyInviteState>& Invites)
{
	return TryGetAvailableInvites(UserSlot, Invites);
}

FBeamOperationHandle UBeamPartySubsystem::JoinPartyOperation(FUserSlot UserSlot, FGuid PartyId,
                                                             FBeamOperationEventHandler OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OperationEventHandler);
	JoinParty(UserSlot, PartyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_JoinPartyOperation(FUserSlot UserSlot, FGuid PartyId,
	FBeamOperationEventHandlerCode OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OperationEventHandler);
	JoinParty(UserSlot, PartyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::FetchPartyInvitesOperation(FUserSlot UserSlot,
	FBeamOperationEventHandler OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OperationEventHandler);
	FetchPartyInvites(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_FetchPartyInvitesOperation(FUserSlot UserSlot,
	FBeamOperationEventHandlerCode OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OperationEventHandler);
	FetchPartyInvites(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::FetchPartyStateOperation(FUserSlot UserSlot, FGuid PartyId,
                                                                   FBeamOperationEventHandler OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OperationEventHandler);
	FetchPartyState(UserSlot, PartyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_FetchPartyStateOperation(FUserSlot UserSlot, FGuid PartyId,
	FBeamOperationEventHandlerCode OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OperationEventHandler);
	FetchPartyState(UserSlot, PartyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CreatePartyOperation(FUserSlot UserSlot, EBeamPartyRestriction Restriction,
                                                               int32 maxPlayers, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CreateParty(UserSlot, Restriction, maxPlayers, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_CreatePartyOperation(FUserSlot UserSlot, EBeamPartyRestriction Restriction,
	int32 maxPlayers, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CreateParty(UserSlot, Restriction, maxPlayers, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::InvitePlayerToPartyOperation(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player,
	FBeamOperationEventHandler OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OperationEventHandler);
	InvitePlayerToParty(UserSlot, PartyId, Player, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_InvitePlayerToPartyOperation(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player,
	FBeamOperationEventHandlerCode OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OperationEventHandler);
	InvitePlayerToParty(UserSlot, PartyId, Player, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::DeclinePlayerPartyInviteOperation(FUserSlot UserSlot, FGuid PartyId,
	FBeamOperationEventHandler OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OperationEventHandler);
	DeclinePlayerPartyInvite(UserSlot, PartyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_DeclinePlayerPartyInviteOperation(FUserSlot UserSlot, FGuid PartyId,
	FBeamOperationEventHandlerCode OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OperationEventHandler);
	DeclinePlayerPartyInvite(UserSlot, PartyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::LeavePartyOperation(FUserSlot UserSlot, FGuid PartyId,
	FBeamOperationEventHandler OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OperationEventHandler);
	LeaveParty(UserSlot, PartyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_LeavePartyOperation(FUserSlot UserSlot, FGuid PartyId,
	FBeamOperationEventHandlerCode OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OperationEventHandler);
	LeaveParty(UserSlot, PartyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::KickPlayerOperation(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player,
	FBeamOperationEventHandler OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OperationEventHandler);
	KickPlayer(UserSlot, PartyId, Player, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CancelPlayerPartyInviteOperation(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player,
	FBeamOperationEventHandler OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OperationEventHandler);
	DeletePlayerPartyInvite(UserSlot, PartyId, Player, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_CancelPlayerPartyInviteOperation(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player,
	FBeamOperationEventHandlerCode OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OperationEventHandler);
	DeletePlayerPartyInvite(UserSlot, PartyId, Player, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_KickPlayerOperation(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player,
                                                                  FBeamOperationEventHandlerCode OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OperationEventHandler);
	KickPlayer(UserSlot, PartyId, Player, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::PromotePlayerToLeaderOperation(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player,
	FBeamOperationEventHandler OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OperationEventHandler);
	PromotePlayerToLeader(UserSlot, PartyId, Player, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_PromotePlayerToLeaderOperation(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player,
	FBeamOperationEventHandlerCode OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OperationEventHandler);
	PromotePlayerToLeader(UserSlot, PartyId, Player, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::UpdatePartyOperation(FUserSlot UserSlot, FGuid PartyId,
	EBeamPartyRestriction Restriction, FOptionalInt32 MaxPlayers, FBeamOperationEventHandler OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OperationEventHandler);
	UpdateParty(UserSlot, PartyId, Restriction, MaxPlayers, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_UpdatePartyOperation(FUserSlot UserSlot, FGuid PartyId,
	EBeamPartyRestriction Restriction, FOptionalInt32 MaxPlayers, FBeamOperationEventHandlerCode OperationEventHandler)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OperationEventHandler);
	UpdateParty(UserSlot, PartyId, Restriction, MaxPlayers, Handle);
	return Handle;
}


bool UBeamPartySubsystem::TryGetPlayerParty(FUserSlot UserSlot, FBeamPartyState& PartyState)
{
	FBeamRealmUser RealmUser;

	if (!Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
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


bool UBeamPartySubsystem::TryGetAvailableInvites(FUserSlot UserSlot, TArray<FBeamPartyInviteState>& Invites)
{
	if (!PartyInvitesState.Contains(UserSlot)) return false;

	// Clean up result list
	Invites.Reset();

	// Add invites to the result list
	for (const auto& InviteState : PartyInvitesState[UserSlot])
	{
		Invites.Add(InviteState);
	}
	return true;
}


void UBeamPartySubsystem::FetchPartyState(FUserSlot UserSlot, FGuid PartyId, FBeamOperationHandle Op)
{
	FOnGetPartyFullResponse Handler = FOnGetPartyFullResponse::CreateLambda([this, PartyId, Op](const FBeamFullResponse<UGetPartyRequest*, UParty*>& Resp)
	{
		if(Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			// It's creating the PartyState using the UParty in the SuccessData.
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
	
	PartyApi->CPP_GetParty(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::FetchPartyInvites(FUserSlot UserSlot, FBeamOperationHandle Op)
{
	FOnGetPartyInvitesFullResponse Handler = FOnGetPartyInvitesFullResponse::CreateLambda([this, UserSlot, Op](const FGetPartyInvitesFullResponse& Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			// Clean up the invites for the user
			if (!PartyInvitesState.Contains(UserSlot))
			{
				PartyInvitesState.Add(UserSlot, {});
			}else
			{
				PartyInvitesState[UserSlot].Reset();
			}
			
			for (auto Invitation : Resp.SuccessData->Invitations.Val)
			{
				PartyInvitesState[UserSlot].Add(FBeamPartyInviteState(FGuid(Invitation->PartyId.Val), FBeamGamerTag(Invitation->InvitedBy.Val)));
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

	if (!Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		return;
	}

	FBeamRequestContext Ctx;

	UGetPartyInvitesRequest* const Request = UGetPartyInvitesRequest::Make(RealmUser.GamerTag.AsString, this, {});

	PlayerPartyApi->CPP_GetPartyInvites(UserSlot, Request, Handler, Ctx, Op, this);
}


bool UBeamPartySubsystem::CreateParty(FUserSlot UserSlot, EBeamPartyRestriction Restriction, int32 maxPlayers, FBeamOperationHandle Op)
{
	FOnPostPartiesFullResponse Handler = FOnPostPartiesFullResponse::CreateLambda([this, UserSlot, Op] (const FPostPartiesFullResponse& Resp)
	{
		if(Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			// It's creating the PartyState using the UParty in the SuccessData.
			FBeamPartyState PartyState = MakePartyState(Resp.SuccessData);
			
			PartyStates.Add(PartyState.PartyId, PartyState);

			//Local Notification
			InvokePartyEventUpdate(UserSlot, PartyState.PartyId, EBeamPartyEvent::BEAM_PlayerJoined);
			
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

	if (!Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		return false;
	}

	
	UPostPartiesRequest* const Request = UPostPartiesRequest::Make(FOptionalString(GetRestrictionString(Restriction)), FOptionalBeamGamerTag(RealmUser.GamerTag), FOptionalInt32(maxPlayers), GetTransientPackage(),{});

	FBeamRequestContext Ctx;
	
	PartyApi->CPP_PostParties(UserSlot, Request, Handler, Ctx, Op, this);
	
	return true;
}

void UBeamPartySubsystem::JoinParty(FUserSlot UserSlot, FGuid PartyId, FBeamOperationHandle Op)
{
	FOnPutPartyFullResponse Handler = FOnPutPartyFullResponse::CreateLambda([this, UserSlot, PartyId, Op] (const FPutPartyFullResponse& Resp)
	{
		if (Resp.State == RS_Retrying) return;
		
		if (Resp.State == RS_Success)
		{
			// It's creating the PartyState using the UParty in the SuccessData.
			FBeamPartyState PartyState = MakePartyState(Resp.SuccessData);
			
			if (PartyStates.Contains(PartyId))
			{
				PartyStates[PartyId] = PartyState;
			}else
			{
				PartyStates.Add(PartyId, PartyState);
			}

			//Local Notification
			InvokePartyEventUpdate(UserSlot, PartyId, EBeamPartyEvent::BEAM_PlayerJoined);
			
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

	PartyApi->CPP_PutParty(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::InvitePlayerToParty(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player, FBeamOperationHandle Op)
{
	FOnApiPartyPostInviteByIdFullResponse Handler = FOnApiPartyPostInviteByIdFullResponse::CreateLambda([this, UserSlot, Player, PartyId, Op](const FApiPartyPostInviteByIdFullResponse& Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			FBeamPartyState PartyState;
			if (!TryGetUserPartyState(UserSlot, PartyState))
			{
				UE_LOG(LogBeamParty, Error, TEXT("PartyState not found for user slot %s"), *UserSlot.Name );
				Runtime->RequestTrackerSystem->TriggerOperationError(Op, TEXT("PartyState not found for the user slot caller"));
				return;
			}
		
			PartyState.InvitedPlayers.Add(Player);

			FBeamRealmUser RealmUser;
			FUserSlot OtherUserSlot;
			FString NamespacedSlotId;
			if (Runtime->UserSlotSystem->GetUserDataWithGamerTag(Player, RealmUser, OtherUserSlot, NamespacedSlotId))
			{
				//Local Notification
				InvokePartyEventUpdate(UserSlot, PartyId, EBeamPartyEvent::BEAM_PlayerInviteCanceled);
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
	
	UApiPartyPostInviteByIdRequest* const Request = UApiPartyPostInviteByIdRequest::Make(PartyId, FOptionalBeamGamerTag(Player), this, {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_PostInvite(UserSlot, Request, Handler, Ctx, Op, this);
	
}

void UBeamPartySubsystem::DeclinePlayerPartyInvite(FUserSlot UserSlot, FGuid PartyId, FBeamOperationHandle Op)
{
	FOnDeleteInviteFullResponse Handler = FOnDeleteInviteFullResponse::CreateLambda([this, UserSlot, PartyId, Op](const FDeleteInviteFullResponse& Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			
			TArray<FBeamPartyInviteState>& Invites = *PartyInvitesState.Find(UserSlot);
	
			for (auto i = 0; i < Invites.Num(); i++)
			{
				if (Invites[i].PartyId == PartyId)
				{
					Invites.RemoveAt(i);
					break;
				}
			}
			
			//Local Notification
			InvokePartyEventUpdate(UserSlot, PartyId, EBeamPartyEvent::BEAM_PlayerInviteCanceled);
			
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

	ensureAlwaysMsgf(Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this), TEXT("Cannot get the RealUser for the UserSlot that call DeclinePlayerPartyInvite"));
	
	UDeleteInviteRequest* const Request = UDeleteInviteRequest::Make(PartyId, FOptionalBeamGamerTag(RealmUser.GamerTag), this, {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_DeleteInvite(UserSlot, Request, Handler, Ctx, Op, this);
}


void UBeamPartySubsystem::LeaveParty(FUserSlot UserSlot, FGuid PartyId, FBeamOperationHandle Op)
{
	FOnDeleteMembersFullResponse Handler = FOnDeleteMembersFullResponse::CreateLambda([this, PartyId, Op, UserSlot](const FDeleteMembersFullResponse& Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			if (PartyStates.Contains(PartyId))
			{
				PartyStates.Remove(PartyId);
			}
			
			//Local Notification
			InvokePartyEventUpdate(UserSlot, PartyId, EBeamPartyEvent::BEAM_PlayerLeft);
			
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

	if (!Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		return;
	}
	
	UDeleteMembersRequest* const Request = UDeleteMembersRequest::Make(PartyId, FOptionalBeamGamerTag(RealmUser.GamerTag), this, {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_DeleteMembers(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::UpdateParty(FUserSlot UserSlot, FGuid PartyId, EBeamPartyRestriction Restriction,
	FOptionalInt32 MaxPlayers, FBeamOperationHandle Op)
{
	FOnApiPartyPutMetadataByIdFullResponse Handler = FOnApiPartyPutMetadataByIdFullResponse::CreateLambda([this, UserSlot, PartyId, Restriction, MaxPlayers, Op](const FApiPartyPutMetadataByIdFullResponse Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			// It's creating the PartyState using the UParty in the SuccessData.
			FBeamPartyState PartyState = MakePartyState(Resp.SuccessData);
				
			if (PartyStates.Contains(PartyId))
			{
				PartyStates[PartyId] = PartyState;
			}else
			{
				PartyStates.Add(PartyId, PartyState);
			}
			
			//Local Notification
			InvokePartyEventUpdate(UserSlot, PartyId, EBeamPartyEvent::BEAM_PartyUpdated);
			
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

	UApiPartyPutMetadataByIdRequest* Request = UApiPartyPutMetadataByIdRequest::Make(PartyId, FOptionalString(GetRestrictionString(Restriction)), MaxPlayers, this, {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_PutMetadata(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::KickPlayer(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player, FBeamOperationHandle Op)
{
	FOnDeleteMembersFullResponse Handler = FOnDeleteMembersFullResponse::CreateLambda([this, UserSlot, Op, PartyId, Player](const FDeleteMembersFullResponse& Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			FBeamPartyState PartyState;
			if (TryGetUserPartyState(UserSlot, PartyState))
			{
				PartyStates[PartyId].PlayerStates.Remove(Player);
			}

			FBeamRealmUser RealmUser;
			FUserSlot OtherUserSlot;
			FString NamespacedSlotId;
			
			if (Runtime->UserSlotSystem->GetUserDataWithGamerTag(Player, RealmUser, OtherUserSlot, NamespacedSlotId))
			{
				//Local Notification
				InvokePartyEventUpdate(OtherUserSlot, PartyId, EBeamPartyEvent::BEAM_PlayerKicked);
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
	
	UDeleteMembersRequest* const Request = UDeleteMembersRequest::Make(PartyId, FOptionalBeamGamerTag(Player), this, {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_DeleteMembers(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::PromotePlayerToLeader(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player, FBeamOperationHandle Op)
{
	FOnPutPromoteFullResponse Handler = FOnPutPromoteFullResponse::CreateLambda([this, UserSlot, PartyId, Op](const FPutPromoteFullResponse& Resp)
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

			//Local Notification
			InvokePartyEventUpdate(UserSlot, PartyId, EBeamPartyEvent::BEAM_PlayerPromotedToLeader);
			
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

	PartyApi->CPP_PutPromote(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::DeletePlayerPartyInvite(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player,
	FBeamOperationHandle Op)
{
	FOnDeleteInviteFullResponse Handler = FOnDeleteInviteFullResponse::CreateLambda([this, UserSlot, PartyId, Player, Op](const FDeleteInviteFullResponse& Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			FBeamPartyState PartyState;
	
			if (TryGetUserPartyState(UserSlot, PartyState))
			{
				PartyState.InvitedPlayers.Remove(Player);
			}
			
			if (PartyInvitesState.Contains(UserSlot))
			{
				TArray<FBeamPartyInviteState>& Invites = *PartyInvitesState.Find(UserSlot);
		
				for (auto i = 0; i < Invites.Num(); i++)
				{
					if (Invites[i].PartyId == PartyId)
					{
						Invites.RemoveAt(i);
						break;
					}
				}
			}
			
			FBeamRealmUser RealmUser;
			FUserSlot OtherUserSlot;
			FString NamespacedSlotId;
			if (Runtime->UserSlotSystem->GetUserDataWithGamerTag(Player, RealmUser, OtherUserSlot, NamespacedSlotId))
			{
				//Local Notification
				InvokePartyEventUpdate(UserSlot, PartyId, EBeamPartyEvent::BEAM_PlayerInviteCanceled);
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
	
	UDeleteInviteRequest* const Request = UDeleteInviteRequest::Make(PartyId, FOptionalBeamGamerTag(Player), this, {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_DeleteInvite(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::PartyUpdatedMessageHandler(FPartyRefreshNotificationMessage RefreshNotificationMessage, FUserSlot UserSlot)
{
	switch (RefreshNotificationMessage.Type)
	{
		case EBeamPartyEvent::BEAM_PlayerInvited:
			HandlePartyEventReceivedUpdateInvitesState(RefreshNotificationMessage.PartyId, UserSlot, RefreshNotificationMessage.Type);
			break;
		case EBeamPartyEvent::BEAM_PlayerInviteCanceled:
			HandlePartyEventReceivedUpdateInvitesState(RefreshNotificationMessage.PartyId, UserSlot, RefreshNotificationMessage.Type);
			break;
		case EBeamPartyEvent::BEAM_PlayerInviteExpired:
			HandlePartyEventReceivedUpdateInvitesState(RefreshNotificationMessage.PartyId, UserSlot, RefreshNotificationMessage.Type);
			break;
		default:
			HandlePartyEventReceivedUpdatePartyState(RefreshNotificationMessage.PartyId, UserSlot, RefreshNotificationMessage.Type);
			break;
	}
}


void UBeamPartySubsystem::HandlePartyEventReceivedUpdatePartyState(FGuid PartyId, FUserSlot UserSlot, EBeamPartyEvent PartyEvent)
{
	UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT(stringify(EBeamPartyEvent)), true);
	
	FString PartyEventName = pEnum->GetNameStringByIndex(static_cast<int32>(PartyEvent));
	
	FBeamOperationEventHandlerCode Handler = FBeamOperationEventHandlerCode::CreateLambda([this, PartyId, UserSlot, PartyEvent, PartyEventName](FBeamOperationEvent Evt)
	{
		if (Evt.EventType == OET_SUCCESS)
		{
			InvokePartyEventUpdate(UserSlot, PartyId, PartyEvent);
		}else
		{
			OnPartyEventReceivedError.Broadcast(PartyId, UserSlot, PartyEvent);
			OnPartyEventReceivedErrorCode.Broadcast(PartyId, UserSlot, PartyEvent);
			UE_LOG(LogBeamParty, Error, TEXT("Error on fetch the party state for PartyId: %s, UserSlot: %s, PartyEvent %s"), *PartyId.ToString(), *UserSlot.Name, *PartyEventName);
		}
	});
	CPP_FetchPartyStateOperation(UserSlot, PartyId, Handler);
	
	UE_LOG(LogBeamParty, Verbose, TEXT("OnReceivedEvent %s"), *pEnum->GetNameStringByIndex((int32)PartyEvent));
}

void UBeamPartySubsystem::HandlePartyEventReceivedUpdateInvitesState(FGuid PartyId, FUserSlot UserSlot, EBeamPartyEvent PartyEvent)
{
	UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT(stringify(EBeamPartyEvent)), true);

	FString PartyEventName = pEnum->GetNameStringByIndex(static_cast<int32>(PartyEvent));
	
	FBeamOperationEventHandlerCode Handler = FBeamOperationEventHandlerCode::CreateLambda([this, PartyId, UserSlot, PartyEvent, PartyEventName](FBeamOperationEvent Evt)
	{
		if (Evt.EventType == OET_SUCCESS)
		{
			InvokePartyEventUpdate(UserSlot, PartyId, PartyEvent);
		}else
		{
			OnPartyEventReceivedError.Broadcast(PartyId, UserSlot, PartyEvent);
			OnPartyEventReceivedErrorCode.Broadcast(PartyId, UserSlot, PartyEvent);
			UE_LOG(LogBeamParty, Error, TEXT("Error on fetch the invites party state for PartyId: %s, UserSlot: %s, PartyEvent %s"), *PartyId.ToString(), *UserSlot.Name, *PartyEventName);
		}
	});
	CPP_FetchPartyInvitesOperation(UserSlot, Handler);


	UE_LOG(LogBeamParty, Verbose, TEXT("OnReceivedEvent %s"), *PartyEventName);
}

void UBeamPartySubsystem::InvokePartyEventUpdate(FUserSlot UserSlot, FGuid PartyId, EBeamPartyEvent PartyEvent)
{
	switch (PartyEvent)
	{
	case EBeamPartyEvent::BEAM_PlayerJoined:
		OnPlayerJoined.Broadcast(PartyId, UserSlot);
		OnPlayerJoinedCode.Broadcast(PartyId, UserSlot);
		break;
	case EBeamPartyEvent::BEAM_PartyUpdated:
		OnPartyUpdated.Broadcast(PartyId, UserSlot);
		OnPartyUpdatedCode.Broadcast(PartyId, UserSlot);
		break;
	case EBeamPartyEvent::BEAM_PlayerKicked:
		OnPlayerKicked.Broadcast(PartyId, UserSlot);
		OnPlayerKickedCode.Broadcast(PartyId, UserSlot);
		break;
	case EBeamPartyEvent::BEAM_PlayerLeft:
		OnPlayerLeft.Broadcast(PartyId, UserSlot);
		OnPlayerLeftCode.Broadcast(PartyId, UserSlot);
		break;
	case EBeamPartyEvent::BEAM_PlayerPromotedToLeader:
		OnPlayerPromotedToLeader.Broadcast(PartyId, UserSlot);
		OnPlayerPromotedToLeaderCode.Broadcast(PartyId, UserSlot);
		break;
	case EBeamPartyEvent::BEAM_PlayerInvited:
		OnPlayerInvited.Broadcast(PartyId, UserSlot);
		OnPlayerInvitedCode.Broadcast(PartyId, UserSlot);
		break;
	case EBeamPartyEvent::BEAM_PlayerInviteCanceled:
		OnPlayerInviteCanceled.Broadcast(PartyId, UserSlot);
		OnPlayerInviteCanceledCode.Broadcast(PartyId, UserSlot);
		break;
	case EBeamPartyEvent::BEAM_PlayerInviteExpired:
		OnPlayerInviteExpired.Broadcast(PartyId, UserSlot);
		OnPlayerInviteExpiredCode.Broadcast(PartyId, UserSlot);
		break;
	}
}

FBeamPartyState UBeamPartySubsystem::MakePartyState(UParty* Party)
{
	FBeamPartyState PartyState = FBeamPartyState();
	PartyState.PartyId = FGuid(Party->Id.Val);
	PartyState.MaxPlayers = Party->MaxSize.Val;
	PartyState.Leader = Party->Leader.Val;
	PartyState.Restriction = GetRestrictionType(Party->Restriction.Val);
	
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
EBeamPartyRestriction UBeamPartySubsystem::GetRestrictionType(FString RestrictionName)
{
	if (RestrictionName == "Unrestricted")
	{
		return EBeamPartyRestriction::BEAM_Unrestricted;
	}
	if (RestrictionName == "InviteOnly")
	{
		return EBeamPartyRestriction::BEAM_InviteOnly;
	}

	return EBeamPartyRestriction::BEAM_Unrestricted;
}
