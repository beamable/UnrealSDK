// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Party/BeamPartySubsystem.h"

#include "AutoGen/Optionals/OptionalGamerTag.h"
#include "AutoGen/SubSystems/Friends/PostFriendsInviteRequest.h"
#include "BeamNotifications/SubSystems/BeamInventoryNotifications.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Subsystems/Inventory/BeamInventorySubsystem.h"

#define stringify( name ) # name

void UBeamPartySubsystem::InitializeWhenUnrealReady_Implementation(FBeamOperationHandle& ResultOp)
{
	// Initializing the subsystems after unreal is ready
	PartyApi = GEngine->GetEngineSubsystem<UBeamPartyApi>();
	PartyNotifications = GEngine->GetEngineSubsystem<UBeamPartyNotifications>();


	Super::InitializeWhenUnrealReady_Implementation(ResultOp);
}

void UBeamPartySubsystem::OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser,
                                                        const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp)
{
	if (!IsRunningDedicatedServer())
	{
		//Register notifications for party on user signed in
		const auto PartyUpdateHandler = FOnPartyRefreshNotificationCode::CreateUFunction(
			this, GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, PartyUpdatedMessageHandler), UserSlot);
		PartyNotifications->CPP_SubscribeToPartyRefresh(UserSlot, Runtime->DefaultNotificationChannel,
		                                                PartyUpdateHandler,
		                                                this);

		// Fetch the PartyInvites 
		FBeamOperationHandle FetchPartyInvitesHandle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
			{UserSlot}, GetName(), FBeamOperationEventHandlerCode::CreateLambda(
				[this](const FBeamOperationEvent& Evt)
				{
					if (Evt.EventType != OET_SUCCESS)
					{
						UE_LOG(LogBeamParty, Error, TEXT("Error on %hs: Failed to fetch the party invites state"),
						       __FUNCTION__);
					}
				}));
		FetchPartyInvites(UserSlot, FetchPartyInvitesHandle);

		ResultOp = FetchPartyInvitesHandle;
	}
	else
	{
		ResultOp = Runtime->RequestTrackerSystem->CPP_BeginSuccessfulOperation({}, GetName(), {}, {});
	}
}

void UBeamPartySubsystem::OnPostUserSignedOut_Implementation(const FUserSlot& UserSlot,
                                                             const EUserSlotClearedReason Reason,
                                                             const FBeamRealmUser& BeamRealmUser,
                                                             FBeamOperationHandle& ResultOp)
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


bool UBeamPartySubsystem::IsPlayerInAParty(FUserSlot UserSlot)
{
	FBeamPartyState PartyState;
	return TryGetUserPartyState(UserSlot, PartyState);
}

bool UBeamPartySubsystem::IsInAParty(FBeamGamerTag PlayerGamerTag)
{
	FBeamPartyState PartyState;
	return TryGetPlayerPartyState(PlayerGamerTag, PartyState);
}

bool UBeamPartySubsystem::IsThePartyLeader(FUserSlot UserSlot)
{
	FBeamRealmUser RealmUser;
	if (!Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		return false;
	}
	FBeamPartyState PartyState;
	if (!TryGetUserPartyState(UserSlot, PartyState))
	{
		return false;
	}
	return PartyState.Leader == RealmUser.GamerTag;
}

bool UBeamPartySubsystem::TryGetUserPartyState(FUserSlot UserSlot, FBeamPartyState& PartyState)
{
	FBeamRealmUser RealmUser;

	if (!Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		return false;
	}

	return TryGetPlayerPartyState(RealmUser.GamerTag, PartyState);
}

bool UBeamPartySubsystem::GetUserPartyPlayerStates(FUserSlot UserSlot, FGuid& PartyId, FBeamGamerTag& LeaderGamerTag, EBeamPartyRestriction& PartyRestriction, TArray<FBeamPartyPlayerState>& PlayerStates)
{
	FBeamPartyState PartyState;
	if (!TryGetUserPartyState(UserSlot, PartyState))
	{
		return false;
	}

	PartyId = PartyState.PartyId;
	LeaderGamerTag = PartyState.Leader;
	PartyRestriction = PartyState.Restriction;

	PlayerStates.Reset();
	for (auto PlayerState : PartyState.PlayerStates)
	{
		PlayerStates.Add(PlayerState.Value);
	}
	return true;
}

bool UBeamPartySubsystem::TryGetPlayerPartyState(FBeamGamerTag PlayerGamerTag, FBeamPartyState& PartyState)
{
	// Iterate over the party states to find the party that contains the FBeamGameTag of the UserSlot
	for (const auto& Item : PartyStates)
	{
		if (Item.Value.PlayerStates.Contains(PlayerGamerTag))
		{
			PartyState = Item.Value;
			return true;
		}
	}

	return false;
}

bool UBeamPartySubsystem::TryGetPartyState(FGuid PartyId, FBeamPartyState& PartyState)
{
	if (!PartyStates.Contains(PartyId))
	{
		return false;
	}

	PartyState = PartyStates[PartyId];
	return true;
}

bool UBeamPartySubsystem::TryGetUserInvitesState(FUserSlot UserSlot, TArray<FBeamPartyInviteState>& Invites)
{
	if (!PartyInvitesState.Contains(UserSlot))
	{
		return false;
	}

	// Clean up result list
	Invites.Reset();

	// Add invites to the result list
	for (const auto& InviteState : PartyInvitesState[UserSlot])
	{
		Invites.Add(InviteState);
	}
	return Invites.Num() != 0;
}

FBeamOperationHandle UBeamPartySubsystem::JoinPartyOperation(FUserSlot UserSlot, FGuid PartyId,
                                                             FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	JoinParty(UserSlot, PartyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_JoinPartyOperation(FUserSlot UserSlot, FGuid PartyId,
                                                                 FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	JoinParty(UserSlot, PartyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::JoinPlayerPartyOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
                                                                   FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	JoinPlayerParty(UserSlot, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_JoinPlayerPartyOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
                                                                       FBeamOperationEventHandlerCode
                                                                       OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	JoinPlayerParty(UserSlot, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::FetchPartyInvitesOperation(FUserSlot UserSlot,
                                                                     FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	FetchPartyInvites(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_FetchPartyInvitesOperation(FUserSlot UserSlot,
                                                                         FBeamOperationEventHandlerCode
                                                                         OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchPartyInvites(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::FetchPartyStateOperation(FUserSlot UserSlot, FGuid PartyId,
                                                                   FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	FetchPartyState(UserSlot, PartyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_FetchPartyStateOperation(FUserSlot UserSlot, FGuid PartyId,
                                                                       FBeamOperationEventHandlerCode
                                                                       OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchPartyState(UserSlot, PartyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::FetchPlayerPartyStateOperation(FUserSlot UserSlot,
                                                                         FBeamOperationEventHandler
                                                                         OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	FetchPlayerPartyState(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_FetchPlayerPartyStateOperation(FUserSlot UserSlot,
                                                                             FBeamOperationEventHandlerCode
                                                                             OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);

	FetchPlayerPartyState(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CreatePartyOperation(FUserSlot UserSlot, EBeamPartyRestriction Restriction,
                                                               int32 MaxPlayers,
                                                               FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	CreateParty(UserSlot, Restriction, MaxPlayers, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_CreatePartyOperation(FUserSlot UserSlot,
                                                                   EBeamPartyRestriction Restriction,
                                                                   int32 maxPlayers,
                                                                   FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CreateParty(UserSlot, Restriction, maxPlayers, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::InvitePlayerToPartyOperation(FUserSlot UserSlot, FGuid PartyId,
                                                                       FBeamGamerTag PlayerGamerTag,
                                                                       FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	InvitePlayerToParty(UserSlot, PartyId, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_InvitePlayerToPartyOperation(
	FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag PlayerGamerTag,
	FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	InvitePlayerToParty(UserSlot, PartyId, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::InvitePlayerToMyPartyOperation(
	FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	InvitePlayerToMyParty(UserSlot, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_InvitePlayerToMyPartyOperation(
	FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	FBeamOperationEventHandlerCode
	OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);

	InvitePlayerToMyParty(UserSlot, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::DeclinePartyInviteOperation(FUserSlot UserSlot, FGuid PartyId,
                                                                      FBeamOperationEventHandler
                                                                      OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	DeclinePartyInvite(UserSlot, PartyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_DeclinePartyInviteOperation(FUserSlot UserSlot, FGuid PartyId,
                                                                          FBeamOperationEventHandlerCode
                                                                          OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	DeclinePartyInvite(UserSlot, PartyId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::DeclinePlayerPartyInviteOperation(
	FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	FBeamOperationEventHandler
	OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	DeclinePlayerInvite(UserSlot, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_DeclinePlayerPartyInviteOperation(FUserSlot UserSlot,
                                                                                FBeamGamerTag PlayerGamerTag, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	DeclinePlayerInvite(UserSlot, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::LeavePartyOperation(FUserSlot UserSlot,
                                                              FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	LeaveParty(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_LeavePartyOperation(FUserSlot UserSlot,
                                                                  FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	LeaveParty(UserSlot, Handle);
	return Handle;
}


FBeamOperationHandle UBeamPartySubsystem::CancelSentPartyInviteOperation(
	FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag PlayerGamerTag,
	FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	CancelSentPartyInvite(UserSlot, PartyId, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_CancelSentPartyInviteOperation(
	FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag PlayerGamerTag,
	FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CancelSentPartyInvite(UserSlot, PartyId, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CancelPlayerPartyInviteOperation(FUserSlot UserSlot,
                                                                           FBeamGamerTag PlayerGamerTag,
                                                                           FBeamOperationEventHandler
                                                                           OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	CancelPlayerPartyInvite(UserSlot, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_CancelPlayerPartyInviteOperation(FUserSlot UserSlot,
                                                                               FBeamGamerTag PlayerGamerTag,
                                                                               FBeamOperationEventHandlerCode
                                                                               OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CancelPlayerPartyInvite(UserSlot, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::KickPlayerOperation(FUserSlot UserSlot, FGuid PartyId,
                                                              FBeamGamerTag PlayerGamerTag,
                                                              FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	KickPlayer(UserSlot, PartyId, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_KickPlayerOperation(FUserSlot UserSlot, FGuid PartyId,
                                                                  FBeamGamerTag PlayerGamerTag,
                                                                  FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	KickPlayer(UserSlot, PartyId, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::KickPlayerFromMyPartyOperation(
	FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	KickPlayerFromMyParty(UserSlot, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_KickPlayerFromMyPartyOperation(
	FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	FBeamOperationEventHandlerCode
	OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	KickPlayerFromMyParty(UserSlot, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::PromotePlayerToLeaderOperation(
	FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag PlayerGamerTag,
	FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	PromotePlayerToLeader(UserSlot, PartyId, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_PromotePlayerToLeaderOperation(
	FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag PlayerGamerTag,
	FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	PromotePlayerToLeader(UserSlot, PartyId, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::PromotePlayerToMyPartyLeaderOperation(FUserSlot UserSlot,
                                                                                FBeamGamerTag PlayerGamerTag, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	PromotePlayerAsMyPartyLeader(UserSlot, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_PromotePlayerToMyPartyLeaderOperation(FUserSlot UserSlot,
                                                                                    FBeamGamerTag PlayerGamerTag, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	PromotePlayerAsMyPartyLeader(UserSlot, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::UpdatePartyMetaOperation(FUserSlot UserSlot, FGuid PartyId,
                                                                   EBeamPartyRestriction Restriction,
                                                                   FOptionalInt32 MaxPlayers,
                                                                   FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	UpdatePartyMeta(UserSlot, PartyId, Restriction, MaxPlayers, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_UpdatePartyMetaOperation(FUserSlot UserSlot, FGuid PartyId,
                                                                       EBeamPartyRestriction Restriction,
                                                                       FOptionalInt32 MaxPlayers,
                                                                       FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	UpdatePartyMeta(UserSlot, PartyId, Restriction, MaxPlayers, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::UpdateMyPartyMetaOperation(FUserSlot UserSlot,
                                                                     EBeamPartyRestriction Restriction,
                                                                     FOptionalInt32 MaxPlayers,
                                                                     FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	UpdateMyPartyMeta(UserSlot, Restriction, MaxPlayers, Handle);
	return Handle;
}

FBeamOperationHandle UBeamPartySubsystem::CPP_UpdateMyPartyMetaOperation(FUserSlot UserSlot,
                                                                         EBeamPartyRestriction Restriction,
                                                                         FOptionalInt32 MaxPlayers,
                                                                         FBeamOperationEventHandlerCode
                                                                         OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	UpdateMyPartyMeta(UserSlot, Restriction, MaxPlayers, Handle);
	return Handle;
}


void UBeamPartySubsystem::FetchPartyState(FUserSlot UserSlot, FGuid PartyId, FBeamOperationHandle Op)
{
	FOnGetPartyFullResponse Handler = FOnGetPartyFullResponse::CreateLambda(
		[this, PartyId, Op](const FBeamFullResponse<UGetPartyRequest*, UParty*>& Resp)
		{
			if (Resp.State == RS_Retrying)
			{
				return;
			}

			if (Resp.State == RS_Success)
			{
				// It's creating the PartyState using the UParty in the SuccessData.
				FBeamPartyState PartyState = MakePartyState(Resp.SuccessData);

				if (PartyStates.Contains(PartyId))
				{
					PartyStates[PartyId] = PartyState;
				}
				else
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

void UBeamPartySubsystem::FetchPlayerPartyState(FUserSlot UserSlot, FBeamOperationHandle Op)
{
	FOnGetPartiesFullResponse Handler = FOnGetPartiesFullResponse::CreateLambda(
		[this, Op](const FGetPartiesFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying)
			{
				return;
			}

			if (Resp.State == RS_Success)
			{
				// Check if the Id is set, if not the player isn't in any party.
				if (Resp.SuccessData->Id.IsSet)
				{
					// It's creating the PartyState using the UParty in the SuccessData.
					FBeamPartyState PartyState = MakePartyState(Resp.SuccessData);

					if (PartyStates.Contains(PartyState.PartyId))
					{
						PartyStates[PartyState.PartyId] = PartyState;
					}
					else
					{
						PartyStates.Add(PartyState.PartyId, PartyState);
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
			}
		});

	FBeamRealmUser RealUser;

	if (!Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealUser, this))
	{
		UE_LOG(LogBeamParty, Error, TEXT("Error on %hs: Wasn't able to find the Real User for the UserSlot %s"),
		       __FUNCTION__, *UserSlot.Name)
		return;
	}

	UGetPartiesRequest* const Request = UGetPartiesRequest::Make(RealUser.GamerTag.AsString, this, {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_GetParties(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::FetchPartyInvites(FUserSlot UserSlot, FBeamOperationHandle Op)
{
	FOnGetPartyInvitesFullResponse Handler = FOnGetPartyInvitesFullResponse::CreateLambda(
		[this, UserSlot, Op](const FGetPartyInvitesFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying)
			{
				return;
			}

			if (Resp.State == RS_Success)
			{
				// Clean up the invites for the user
				if (!PartyInvitesState.Contains(UserSlot))
				{
					PartyInvitesState.Add(UserSlot, {});
				}
				else
				{
					PartyInvitesState[UserSlot].Reset();
				}

				for (auto Invitation : Resp.SuccessData->Invitations.Val)
				{
					PartyInvitesState[UserSlot].Add(
						FBeamPartyInviteState(FGuid(Invitation->PartyId.Val),
						                      FBeamGamerTag(Invitation->InvitedBy.Val)));
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

	PartyApi->CPP_GetPartyInvites(UserSlot, Request, Handler, Ctx, Op, this);
}


bool UBeamPartySubsystem::CreateParty(FUserSlot UserSlot, EBeamPartyRestriction Restriction, int32 maxPlayers,
                                      FBeamOperationHandle Op)
{
	if (!IsUserSlotAuthenticated(UserSlot, __FUNCTION__, Op))
	{
		return false;
	}
	FOnPostPartiesFullResponse Handler = FOnPostPartiesFullResponse::CreateLambda(
		[this, UserSlot, Op](const FPostPartiesFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying)
			{
				return;
			}

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


	UPostPartiesRequest* const Request = UPostPartiesRequest::Make(FOptionalString(GetRestrictionString(Restriction)),
	                                                               FOptionalBeamGamerTag(RealmUser.GamerTag),
	                                                               FOptionalInt32(maxPlayers), GetTransientPackage(),
	                                                               {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_PostParties(UserSlot, Request, Handler, Ctx, Op, this);

	return true;
}

void UBeamPartySubsystem::JoinParty(FUserSlot UserSlot, FGuid PartyId, FBeamOperationHandle Op)
{
	if (!IsUserSlotAuthenticated(UserSlot, __FUNCTION__, Op))
	{
		return;
	}

	if (IsPlayerInAParty(UserSlot))
	{
		Runtime->RequestTrackerSystem->TriggerOperationError(Op, TEXT("Player already in a Party"));
		return;
	}

	FOnPutPartyFullResponse Handler = FOnPutPartyFullResponse::CreateLambda(
		[this, UserSlot, PartyId, Op](const FPutPartyFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying)
			{
				return;
			}

			if (Resp.State == RS_Success)
			{
				// It's creating the PartyState using the UParty in the SuccessData.
				FBeamPartyState PartyState = MakePartyState(Resp.SuccessData);

				if (PartyStates.Contains(PartyId))
				{
					PartyStates[PartyId] = PartyState;
				}
				else
				{
					PartyStates.Add(PartyId, PartyState);
				}

				if (PartyInvitesState.Contains(UserSlot))
				{
					TArray<FBeamPartyInviteState>& Invites = *PartyInvitesState.Find(UserSlot);
					for (auto i = 0; i < Invites.Num(); i++)
					{
						if (Invites[i].PartyId == PartyId)
						{
							Invites.RemoveAt(i);
							//As the party invitation has been accepted the invite it's will trigger as an expired event to locally to handle that change
							InvokePartyEventUpdate(UserSlot, PartyId, EBeamPartyEvent::BEAM_PlayerInviteExpired);
							break;
						}
					}
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
			}
		});

	UPutPartyRequest* const Request = UPutPartyRequest::Make(PartyId, this, {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_PutParty(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::JoinPlayerParty(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag, FBeamOperationHandle Op)
{
	if (!IsUserSlotAuthenticated(UserSlot, __FUNCTION__, Op))
	{
		return;
	}

	if (IsPlayerInAParty(UserSlot))
	{
		Runtime->RequestTrackerSystem->TriggerOperationError(Op, TEXT("Player already in a Party"));
		return;
	}

	TArray<FBeamPartyInviteState> Invites;
	// Validate if there's any invite in the local state that the PlayerGamerTag sent to the current user
	if (!TryGetUserInvitesState(UserSlot, Invites))
	{
		return;
	}

	bool HasSenderInvite = false;
	FGuid PartyId;
	for (auto Invite : Invites)
	{
		if (Invite.Sender == PlayerGamerTag)
		{
			PartyId = Invite.PartyId;
			HasSenderInvite = true;
			break;
		}
	}
	if (!HasSenderInvite)
	{
		return;
	}

	FOnPutPartyFullResponse Handler = FOnPutPartyFullResponse::CreateLambda(
		[this, UserSlot, PartyId, Op](const FPutPartyFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying)
			{
				return;
			}

			if (Resp.State == RS_Success)
			{
				FBeamRealmUser RealmUser;
				// The realm user should exist 
				ensureAlways(Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this));

				FBeamPartyState OldPartyState;
				// Check if the player was part of a party to remove that locally when it join another
				if (TryGetPlayerPartyState(RealmUser.GamerTag, OldPartyState))
				{
					if (OldPartyState.PartyId != PartyId)
					{
						PartyStates.Find(OldPartyState.PartyId)->PlayerStates.Remove(RealmUser.GamerTag);
					}
				}
				// It's creating the PartyState using the UParty in the SuccessData.
				FBeamPartyState PartyState = MakePartyState(Resp.SuccessData);

				if (PartyStates.Contains(PartyId))
				{
					PartyStates[PartyId] = PartyState;
				}
				else
				{
					PartyStates.Add(PartyId, PartyState);
				}

				if (PartyInvitesState.Contains(UserSlot))
				{
					TArray<FBeamPartyInviteState>& Invites = *PartyInvitesState.Find(UserSlot);
					for (auto i = 0; i < Invites.Num(); i++)
					{
						if (Invites[i].PartyId == PartyId)
						{
							Invites.RemoveAt(i);
							//As the party invitation has been accepted the invite it's will trigger as an expired event to locally to handle that change
							InvokePartyEventUpdate(UserSlot, PartyId, EBeamPartyEvent::BEAM_PlayerInviteExpired);
							break;
						}
					}
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
			}
		});

	UPutPartyRequest* const Request = UPutPartyRequest::Make(PartyId, this, {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_PutParty(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::InvitePlayerToParty(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag PlayerGamerTag,
                                              FBeamOperationHandle Op)
{
	if (!IsUserSlotAuthenticated(UserSlot, __FUNCTION__, Op))
	{
		return;
	}
	FOnApiPartyPostInviteByIdFullResponse Handler = FOnApiPartyPostInviteByIdFullResponse::CreateLambda(
		[this, UserSlot, PlayerGamerTag, PartyId, Op](const FApiPartyPostInviteByIdFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying)
			{
				return;
			}

			if (Resp.State == RS_Success)
			{
				FBeamPartyState PartyState;
				if (!TryGetUserPartyState(UserSlot, PartyState))
				{
					UE_LOG(LogBeamParty, Error, TEXT("PartyState not found for user slot %s"), *UserSlot.Name);
					Runtime->RequestTrackerSystem->TriggerOperationError(
						Op, TEXT("PartyState not found for the user slot caller"));
					return;
				}

				PartyState.InvitedPlayers.Add(PlayerGamerTag);

				//Local Notification
				FBeamRealmUser RealmUser;
				FUserSlot OtherUserSlot;
				FString NamespacedSlotId;
				if (Runtime->UserSlotSystem->
				             GetUserDataWithGamerTag(PlayerGamerTag, RealmUser, OtherUserSlot, NamespacedSlotId))
				{
					InvokePartyEventUpdate(UserSlot, PartyId, EBeamPartyEvent::BEAM_PlayerInvited);
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

	UApiPartyPostInviteByIdRequest* const Request = UApiPartyPostInviteByIdRequest::Make(
		PartyId, FOptionalBeamGamerTag(PlayerGamerTag), this, {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_PostInvite(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::InvitePlayerToMyParty(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
                                                FBeamOperationHandle Op)
{
	if (!IsUserSlotAuthenticated(UserSlot, __FUNCTION__, Op))
	{
		return;
	}
	FBeamRealmUser RealmUser;
	ensureAlwaysMsgf(Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this),
	                 TEXT(
		                 "It's not possible to user don't have a realm if we validated it is authenticated before this call."
	                 ));

	FBeamPartyState PartyState;

	if (!TryGetUserPartyState(UserSlot, PartyState))
	{
		Runtime->RequestTrackerSystem->TriggerOperationError(
			Op, TEXT(
				"Player isn't in any party, please make sure that the player is in a party before call this operation"));
		return;
	}

	InvitePlayerToParty(UserSlot, PartyState.PartyId, PlayerGamerTag, Op);
}

void UBeamPartySubsystem::DeclinePartyInvite(FUserSlot UserSlot, FGuid PartyId, FBeamOperationHandle Op)
{
	if (!IsUserSlotAuthenticated(UserSlot, __FUNCTION__, Op))
	{
		return;
	}
	FOnDeleteInviteFullResponse Handler = FOnDeleteInviteFullResponse::CreateLambda(
		[this, UserSlot, PartyId, Op](const FDeleteInviteFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying)
			{
				return;
			}

			if (Resp.State == RS_Success)
			{
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
			}
		});

	FBeamRealmUser RealmUser;

	ensureAlwaysMsgf(Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this),
	                 TEXT("Cannot get the RealUser for the UserSlot that call DeclinePlayerPartyInvite"));

	UDeleteInviteRequest* const Request = UDeleteInviteRequest::Make(PartyId, FOptionalBeamGamerTag(RealmUser.GamerTag),
	                                                                 this, {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_DeleteInvite(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::DeclinePlayerInvite(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
                                              FBeamOperationHandle Op)
{
	if (!IsUserSlotAuthenticated(UserSlot, __FUNCTION__, Op))
	{
		return;
	}
	TArray<FBeamPartyInviteState> Invites;
	// Validate if there's any invite in the local state that the PlayerGamerTag sent to the current user
	if (!TryGetUserInvitesState(UserSlot, Invites))
	{
		Runtime->RequestTrackerSystem->TriggerOperationError(Op, TEXT("There's no invites for the player to decline!"));
		return;
	}

	bool HasSenderInvite = false;
	FGuid PartyId;
	for (auto Invite : Invites)
	{
		if (Invite.Sender == PlayerGamerTag)
		{
			PartyId = Invite.PartyId;
			HasSenderInvite = true;
			break;
		}
	}
	if (!HasSenderInvite)
	{
		return;
	}

	DeclinePartyInvite(UserSlot, PartyId, Op);
}


void UBeamPartySubsystem::LeaveParty(FUserSlot UserSlot, FBeamOperationHandle Op)
{
	if (!IsUserSlotAuthenticated(UserSlot, __FUNCTION__, Op))
	{
		return;
	}

	FBeamPartyState PartyState;
	if (!TryGetUserPartyState(UserSlot, PartyState))
	{
		Runtime->RequestTrackerSystem->TriggerOperationError(
			Op, TEXT("There's no party to leave for the given user slot."));
		return;
	}

	FGuid PartyId = PartyState.PartyId;

	FOnDeleteMembersFullResponse Handler = FOnDeleteMembersFullResponse::CreateLambda(
		[this, PartyId, Op, UserSlot](const FDeleteMembersFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying)
			{
				return;
			}

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
			}
		});

	FBeamRealmUser RealmUser;

	if (!Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		return;
	}

	UDeleteMembersRequest* const Request = UDeleteMembersRequest::Make(
		PartyId, FOptionalBeamGamerTag(RealmUser.GamerTag), this, {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_DeleteMembers(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::UpdatePartyMeta(FUserSlot UserSlot, FGuid PartyId, EBeamPartyRestriction Restriction,
                                          FOptionalInt32 MaxPlayers, FBeamOperationHandle Op)
{
	FOnApiPartyPutMetadataByIdFullResponse Handler = FOnApiPartyPutMetadataByIdFullResponse::CreateLambda(
		[this, UserSlot, PartyId, Op](const FApiPartyPutMetadataByIdFullResponse Resp)
		{
			if (Resp.State == RS_Retrying)
			{
				return;
			}

			if (Resp.State == RS_Success)
			{
				// It's creating the PartyState using the UParty in the SuccessData.
				FBeamPartyState PartyState = MakePartyState(Resp.SuccessData);

				if (PartyStates.Contains(PartyId))
				{
					PartyStates[PartyId] = PartyState;
				}
				else
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
			}
		});

	UApiPartyPutMetadataByIdRequest* Request = UApiPartyPutMetadataByIdRequest::Make(
		PartyId, FOptionalString(GetRestrictionString(Restriction)), MaxPlayers, this, {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_PutMetadata(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::UpdateMyPartyMeta(FUserSlot UserSlot, EBeamPartyRestriction Restriction,
                                            FOptionalInt32 MaxPlayers, FBeamOperationHandle Op)
{
	if (!IsUserSlotAuthenticated(UserSlot, __FUNCTION__, Op))
	{
		return;
	}
	FBeamPartyState PartyState;
	if (!TryGetUserPartyState(UserSlot, PartyState))
	{
		Runtime->RequestTrackerSystem->TriggerOperationError(
			Op, TEXT("The give user slot isn't in any party."));
		return;
	}

	UpdatePartyMeta(UserSlot, PartyState.PartyId, Restriction, MaxPlayers, Op);
}

void UBeamPartySubsystem::KickPlayer(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag PlayerGamerTag,
                                     FBeamOperationHandle Op)
{
	FOnDeleteMembersFullResponse Handler = FOnDeleteMembersFullResponse::CreateLambda(
		[this, UserSlot, Op, PartyId, PlayerGamerTag](const FDeleteMembersFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying)
			{
				return;
			}

			if (Resp.State == RS_Success)
			{
				FBeamPartyState PartyState;
				if (TryGetUserPartyState(UserSlot, PartyState))
				{
					PartyStates[PartyId].PlayerStates.Remove(PlayerGamerTag);
				}

				FBeamRealmUser RealmUser;
				FUserSlot OtherUserSlot;
				FString NamespacedSlotId;

				if (Runtime->UserSlotSystem->
				             GetUserDataWithGamerTag(PlayerGamerTag, RealmUser, OtherUserSlot, NamespacedSlotId))
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
			}
		});

	UDeleteMembersRequest* const Request =
		UDeleteMembersRequest::Make(PartyId, FOptionalBeamGamerTag(PlayerGamerTag), this, {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_DeleteMembers(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::KickPlayerFromMyParty(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
                                                FBeamOperationHandle Op)
{
	if (!IsUserSlotAuthenticated(UserSlot, __FUNCTION__, Op))
	{
		return;
	}
	FBeamPartyState PartyState;
	if (!TryGetUserPartyState(UserSlot, PartyState))
	{
		Runtime->RequestTrackerSystem->TriggerOperationError(
			Op, TEXT("The give user slot isn't in any party."));
		return;
	}
	KickPlayer(UserSlot, PartyState.PartyId, PlayerGamerTag, Op);
}

void UBeamPartySubsystem::PromotePlayerToLeader(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag PlayerGamerTag,
                                                FBeamOperationHandle Op)
{
	FOnPutPromoteFullResponse Handler = FOnPutPromoteFullResponse::CreateLambda(
		[this, UserSlot, PartyId, Op](const FPutPromoteFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying)
			{
				return;
			}

			if (Resp.State == RS_Success)
			{
				if (PartyStates.Contains(PartyId))
				{
					PartyStates[PartyId] = MakePartyState(Resp.SuccessData);
				}
				else
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
			}
		});


	UPutPromoteRequest* const Request = UPutPromoteRequest::Make(PartyId, FOptionalBeamGamerTag(PlayerGamerTag), this,
	                                                             {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_PutPromote(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::PromotePlayerAsMyPartyLeader(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
                                                       FBeamOperationHandle Op)
{
	if (!IsUserSlotAuthenticated(UserSlot, __FUNCTION__, Op))
	{
		return;
	}
	FBeamPartyState PartyState;
	if (!TryGetUserPartyState(UserSlot, PartyState))
	{
		Runtime->RequestTrackerSystem->TriggerOperationError(
			Op, TEXT("The give user slot isn't in any party."));
		return;
	}
	PromotePlayerToLeader(UserSlot, PartyState.PartyId, PlayerGamerTag, Op);
}

void UBeamPartySubsystem::CancelSentPartyInvite(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag PlayerGamerTag,
                                                FBeamOperationHandle Op)
{
	FOnDeleteInviteFullResponse Handler = FOnDeleteInviteFullResponse::CreateLambda(
		[this, UserSlot, PartyId, PlayerGamerTag, Op](const FDeleteInviteFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying)
			{
				return;
			}

			if (Resp.State == RS_Success)
			{
				FBeamPartyState PartyState;

				if (TryGetUserPartyState(UserSlot, PartyState))
				{
					PartyState.InvitedPlayers.Remove(PlayerGamerTag);
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
				if (Runtime->UserSlotSystem->
				             GetUserDataWithGamerTag(PlayerGamerTag, RealmUser, OtherUserSlot, NamespacedSlotId))
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
			}
		});

	UDeleteInviteRequest* const Request = UDeleteInviteRequest::Make(PartyId, FOptionalBeamGamerTag(PlayerGamerTag),
	                                                                 this, {});

	FBeamRequestContext Ctx;

	PartyApi->CPP_DeleteInvite(UserSlot, Request, Handler, Ctx, Op, this);
}

void UBeamPartySubsystem::CancelPlayerPartyInvite(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
                                                  FBeamOperationHandle Op)
{
	if (!IsUserSlotAuthenticated(UserSlot, __FUNCTION__, Op))
	{
		return;
	}
	FBeamPartyState PartyState;
	if (!TryGetUserPartyState(UserSlot, PartyState))
	{
		Runtime->RequestTrackerSystem->TriggerOperationError(
			Op, TEXT("The give user slot isn't in any party."));
		return;
	}

	CancelSentPartyInvite(UserSlot, PartyState.PartyId, PlayerGamerTag, Op);
}

void UBeamPartySubsystem::PartyUpdatedMessageHandler(FPartyRefreshNotificationMessage RefreshNotificationMessage,
                                                     FUserSlot UserSlot)
{
	switch (RefreshNotificationMessage.Type)
	{
	case EBeamPartyEvent::BEAM_PlayerInvited:
		HandlePartyEventReceivedUpdateInvitesState(RefreshNotificationMessage.PartyId, UserSlot,
		                                           RefreshNotificationMessage.Type);
		break;
	case EBeamPartyEvent::BEAM_PlayerInviteCanceled:
		HandlePartyEventReceivedUpdateInvitesState(RefreshNotificationMessage.PartyId, UserSlot,
		                                           RefreshNotificationMessage.Type);
		break;
	case EBeamPartyEvent::BEAM_PlayerInviteExpired:
		HandlePartyEventReceivedUpdateInvitesState(RefreshNotificationMessage.PartyId, UserSlot,
		                                           RefreshNotificationMessage.Type);
		break;
	case EBeamPartyEvent::BEAM_PlayerLeft:
		// Only update player left event if the player still in the party.
		// The player that left will trigger this locally when the request return success
		{
			FBeamPartyState PartyState;
			if (TryGetUserPartyState(UserSlot, PartyState) && PartyState.PartyId == RefreshNotificationMessage.PartyId)
			{
				HandlePartyEventReceivedUpdatePartyState(RefreshNotificationMessage.PartyId, UserSlot,
				                                         RefreshNotificationMessage.Type);
			}
		}
		break;
	default:
		HandlePartyEventReceivedUpdatePartyState(RefreshNotificationMessage.PartyId, UserSlot,
		                                         RefreshNotificationMessage.Type);
		break;
	}
}


void UBeamPartySubsystem::HandlePartyEventReceivedUpdatePartyState(FGuid PartyId, FUserSlot UserSlot,
                                                                   EBeamPartyEvent PartyEvent)
{
	UEnum* pEnum = StaticEnum<EBeamPartyEvent>();

	FString PartyEventName = "";
	if (pEnum)
	{
		PartyEventName = pEnum->GetNameStringByIndex(static_cast<int32>(PartyEvent));
	}

	FBeamOperationEventHandlerCode Handler = FBeamOperationEventHandlerCode::CreateLambda(
		[this, PartyId, UserSlot, PartyEvent, PartyEventName](FBeamOperationEvent Evt)
		{
			if (Evt.EventType == OET_SUCCESS)
			{
				InvokePartyEventUpdate(UserSlot, PartyId, PartyEvent);
			}
			else
			{
				OnPartyEventReceivedError.Broadcast(PartyId, UserSlot, PartyEvent);
				OnPartyEventReceivedErrorCode.Broadcast(PartyId, UserSlot, PartyEvent);
				UE_LOG(LogBeamParty, Error,
				       TEXT("Error on fetch the party state for PartyId: %s, UserSlot: %s, PartyEvent %s"),
				       *PartyId.ToString(), *UserSlot.Name, *PartyEventName);
			}
		});
	CPP_FetchPartyStateOperation(UserSlot, PartyId, Handler);

	UE_LOG(LogBeamParty, Verbose, TEXT("OnReceivedEvent %s"), *pEnum->GetNameStringByIndex((int32)PartyEvent));
}

void UBeamPartySubsystem::HandlePartyEventReceivedUpdateInvitesState(FGuid PartyId, FUserSlot UserSlot,
                                                                     EBeamPartyEvent PartyEvent)
{
	UEnum* pEnum = StaticEnum<EBeamPartyEvent>();

	FString PartyEventName = "";
	if (pEnum)
	{
		PartyEventName = pEnum->GetNameStringByIndex(static_cast<int32>(PartyEvent));
	}

	FBeamOperationEventHandlerCode Handler = FBeamOperationEventHandlerCode::CreateLambda(
		[this, PartyId, UserSlot, PartyEvent, PartyEventName](FBeamOperationEvent Evt)
		{
			if (Evt.EventType == OET_SUCCESS)
			{
				InvokePartyEventUpdate(UserSlot, PartyId, PartyEvent);
			}
			else
			{
				OnPartyEventReceivedError.Broadcast(PartyId, UserSlot, PartyEvent);
				OnPartyEventReceivedErrorCode.Broadcast(PartyId, UserSlot, PartyEvent);
				UE_LOG(LogBeamParty, Error,
				       TEXT("Error on fetch the invites party state for PartyId: %s, UserSlot: %s, PartyEvent %s"),
				       *PartyId.ToString(), *UserSlot.Name, *PartyEventName);
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
