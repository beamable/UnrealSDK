// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Matchmaking/BeamMatchmakingSubsystem.h"

#include "Subsystems/Lobby/BeamLobbySubsystem.h"

void UBeamMatchmakingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ContentSubsystem = Collection.InitializeDependency<UBeamContentSubsystem>();

	MatchmakingApi = GEngine->GetEngineSubsystem<UBeamMatchmakingApi>();
	MatchmakingNotifications = GEngine->GetEngineSubsystem<UBeamMatchmakingNotifications>();

	UserSlots = Runtime->UserSlotSystem;
	RequestTracker = Runtime->RequestTrackerSystem;
}

void UBeamMatchmakingSubsystem::InitializeWhenUnrealReady_Implementation(FBeamOperationHandle& ResultOp)
{
	const auto RuntimeSlots = GetDefault<UBeamCoreSettings>()->RuntimeUserSlots;
	for (FString RuntimeSlot : RuntimeSlots)
	{
		Slots.Add(RuntimeSlot, FBeamMatchmakingState{RuntimeSlot, FGuid{}});
	}
	Super::InitializeWhenUnrealReady_Implementation(ResultOp);
}

void UBeamMatchmakingSubsystem::OnPostUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp)
{
	TArray<FBeamContentId> AllGameTypes;
	ContentSubsystem->GetIdsOfContentType(UBeamGameTypeContent::StaticClass(), AllGameTypes);
	for (FBeamContentId GameType : AllGameTypes)
	{
		UE_LOG(LogBeamMatchmaking, Display, TEXT("Beamable Matchmaking | Registering for notifications of GAME_TYPE=%s"), *GameType.AsString);

		const auto UpdateHandler = FOnMatchmakingUpdateNotificationCode::CreateUObject(this, &UBeamMatchmakingSubsystem::OnMatchmakingUpdateReceived);
		const auto TimeoutHandler = FOnMatchmakingTimeoutNotificationCode::CreateUObject(this, &UBeamMatchmakingSubsystem::OnMatchmakingTimeoutReceived);

		MatchmakingNotifications->CPP_SubscribeToMatchmakingUpdate(UserSlot, Runtime->DefaultNotificationChannel, GameType, UpdateHandler, this);
		MatchmakingNotifications->CPP_SubscribeToMatchmakingTimeout(UserSlot, Runtime->DefaultNotificationChannel, GameType, TimeoutHandler, this);
	}

	Super::OnPostUserSignedIn_Implementation(UserSlot, BeamRealmUser, bIsOwnerUserAuth, ResultOp);
}

TArray<TSubclassOf<UBeamRuntimeSubsystem>> UBeamMatchmakingSubsystem::GetDependingOnSubsystems()
{
	TArray<TSubclassOf<UBeamRuntimeSubsystem>> DependantSubsystems =
	Super::GetDependingOnSubsystems();
	DependantSubsystems.Add(UBeamLobbySubsystem::StaticClass());
	return DependantSubsystems;
}

// LOCAL STATE GETTERS

bool UBeamMatchmakingSubsystem::IsUserSlotInQueue(const FUserSlot& Slot)
{
	const auto State = Slots.Find(Slot);
	return State && State->InTicket.IsValid();
}

bool UBeamMatchmakingSubsystem::TryGetTicketId(const FUserSlot& Slot, FGuid& TicketId)
{
	if (IsUserSlotInQueue(Slot))
	{
		TicketId = Slots[Slot].InTicket;
		return true;
	}

	TicketId = {};
	return false;
}

bool UBeamMatchmakingSubsystem::TryGetTicket(const FUserSlot& Slot, FBeamMatchmakingTicket& Ticket)
{
	if (IsUserSlotInQueue(Slot))
	{
		Ticket = *LiveTickets.FindByKey(Slots[Slot].InTicket);
		return true;
	}

	Ticket = {};
	return false;
}


// OPERATIONS

FBeamOperationHandle UBeamMatchmakingSubsystem::TryJoinQueueOperation(FUserSlot UserSlot, FBeamContentId GameTypeQueue, FOptionalString Team, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	TryJoinQueue(UserSlot, GameTypeQueue, Team, {}, Handle);
	return Handle;
}

FBeamOperationHandle UBeamMatchmakingSubsystem::CPP_TryJoinQueueOperation(FUserSlot UserSlot, const FBeamContentId& GameTypeQueue, FOptionalString Team, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	TryJoinQueue(UserSlot, GameTypeQueue, Team, {}, Handle);
	return Handle;
}

FBeamOperationHandle UBeamMatchmakingSubsystem::TryJoinQueueWithTagsOperation(FUserSlot UserSlot, FBeamContentId GameTypeQueue, FOptionalString Team, TArray<FBeamTag> Tags,
	FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	TryJoinQueue(UserSlot, GameTypeQueue, Team, FOptionalArrayOfBeamTag{Tags}, Handle);
	return Handle;
}

FBeamOperationHandle UBeamMatchmakingSubsystem::CPP_TryJoinQueueWithTagsOperation(FUserSlot UserSlot, const FBeamContentId& GameTypeQueue, FOptionalString Team, TArray<FBeamTag> Tags,
	FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	TryJoinQueue(UserSlot, GameTypeQueue, Team, FOptionalArrayOfBeamTag{Tags}, Handle);
	return Handle;
}

FBeamOperationHandle UBeamMatchmakingSubsystem::TryLeaveQueueOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	TryLeaveQueue(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamMatchmakingSubsystem::CPP_TryLeaveQueueOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	TryLeaveQueue(UserSlot, Handle);
	return Handle;
}

// OPERATION IMPLEMENTATIONS

void UBeamMatchmakingSubsystem::TryJoinQueue(FUserSlot Slot, FBeamContentId GameTypeQueue, FOptionalString Team, FOptionalArrayOfBeamTag Tags, FBeamOperationHandle Op)
{
	// Validate the user is not already in the queue.
	if (IsUserSlotInQueue(Slot))
	{
		const auto ErrMsg = FString::Printf(TEXT("User Slot \"%s\" already in queue."), *Slot.Name);
		RequestTracker->TriggerOperationError(Op, ErrMsg);
		return;
	}

	// Validate the content is a valid game type content.
	if (!GameTypeQueue.AsString.StartsWith(UBeamGameTypeContent::ContentId))
	{
		const auto ErrMsg = FString::Printf(TEXT("ContentId \"%s\" must be a %s."), *GameTypeQueue.AsString, *UBeamGameTypeContent::StaticClass()->GetFName().ToString());

		RequestTracker->TriggerOperationError(Op, ErrMsg);
		return;
	}

	UBeamGameTypeContent* GameType;
	ContentSubsystem->TryGetContentOfType<UBeamGameTypeContent>(GameTypeQueue, GameType);

	// If the game type is team-based, ensure we are being given a valid team. 
	if (GameType->Teams.Num() > 1)
	{
		if (!Team.IsSet)
		{
			const auto ErrMsg = FString::Printf(TEXT("Game Type \"%s\" expects a team to be passed in."), *GameTypeQueue.AsString);
			RequestTracker->TriggerOperationError(Op, ErrMsg);
			return;
		}

		const auto MatchingTeam = GameType->Teams.ContainsByPredicate([Team](const FBeamMatchmakingTeamsRule& TeamRule) { return Team.Val.Equals(TeamRule.Name); });
		if (!MatchingTeam)
		{
			const auto ErrMsg = FString::Printf(TEXT("Game Type \"%s\" does not have team %s."), *GameTypeQueue.AsString, *Team.Val);
			RequestTracker->TriggerOperationError(Op, ErrMsg);
			return;
		}
	}
	// If the game type is not team based (as in, has just one team), force it.
	else if (GameType->Teams.Num() == 1)
	{
		Team = FOptionalString{GameType->Teams[0].Name};
	}
	// If no team is configured, error out.
	else
	{
		const auto ErrMsg = FString::Printf(TEXT("Game Type must have at least one team configured to tell us how many players are required to form a match."));
		RequestTracker->TriggerOperationError(Op, ErrMsg);
		return;
	}

	const auto Handler = FOnPostTicketsFullResponse::CreateLambda([this, Slot, Op](const FPostTicketsFullResponse& Resp)
	{
		if (Resp.State == RS_Retrying) return;
		
		if (Resp.State == RS_Success)
		{
			const auto Tickets = Resp.SuccessData;
			if (!Tickets->Tickets.IsSet)
			{
				const auto ErrMsg = FString::Printf(TEXT("Something went wrong and no ticket was returned. You should never see this."));
				RequestTracker->TriggerOperationError(Op, ErrMsg);
				return;
			}

			const auto Ticket = Tickets->Tickets.Val[0];
			const auto TicketId = FGuid{Ticket->TicketId.Val};
			if (!TicketId.IsValid())
			{
				const auto ErrMsg = FString::Printf(TEXT("Something went wrong and the returned ticket had no valid GUID. You should never see this."));
				RequestTracker->TriggerOperationError(Op, ErrMsg);
				return;
			}

			// For players that were added to the queue, check if they are local to this running client and update their matchmaking state.
			TArray<FUserSlot> SlotsInTicket;
			TArray<FBeamGamerTag> GamerTagsInTicket;
			for (FBeamGamerTag GamerTag : Ticket->Players.Val)
			{
				FUserSlot SlotInTicket;
				FBeamRealmUser RealmUser{};
				FString _;
				if (UserSlots->GetUserDataWithGamerTag(GamerTag, RealmUser, SlotInTicket, _))
					SlotsInTicket.Add(SlotInTicket);

				GamerTagsInTicket.Add(GamerTag);
			}

			FBeamMatchmakingTicket NewTicket;
			NewTicket.TicketId = TicketId;
			NewTicket.SlotsInTicket = SlotsInTicket;
			NewTicket.GamerTagsInTicket = GamerTagsInTicket;
			ContentSubsystem->TryGetContentOfType(FBeamContentId{Ticket->MatchType.Val}, NewTicket.GameType);

			// Update the per-slot state of matchmaking
			for (FUserSlot InMsg : SlotsInTicket)
			{
				auto SlotState = Slots.Find(InMsg);
				int64 TicketCreated;
				FDefaultValueHelper::ParseInt64(Ticket->Created.Val, TicketCreated);

				SlotState->InTicket = TicketId;
				SlotState->LastJoinTime = FDateTime::FromUnixTimestamp(TicketCreated);
			}
			LiveTickets.Add(NewTicket);
			RequestTracker->TriggerOperationSuccess(Op, TicketId.ToString());
		}
		else
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.message);
		}
	});

	FBeamRequestContext Ctx;
	const auto Req = UPostTicketsRequest::Make(FOptionalBool{true}, {}, Team, {}, FOptionalArrayOfBeamContentId{{GameTypeQueue}}, Tags, GetTransientPackage(), {});
	MatchmakingApi->CPP_PostTickets(Slot, Req, Handler, Ctx, Op, this);
}

void UBeamMatchmakingSubsystem::TryLeaveQueue(FUserSlot Slot, FBeamOperationHandle Op)
{
	if (!IsUserSlotInQueue(Slot))
	{
		const auto ErrMsg = FString::Printf(TEXT("User Slot \"%s\" not in queue."), *Slot.Name);
		RequestTracker->TriggerOperationError(Op, ErrMsg);
		return;
	}

	const auto SlotState = Slots.Find(Slot);
	const auto TicketId = SlotState->InTicket;
	if (!TicketId.IsValid())
	{
		const auto ErrMsg = FString::Printf(TEXT("User Slot \"%s\" ticket is invalid. You should never see this."), *Slot.Name);
		RequestTracker->TriggerOperationError(Op, ErrMsg);
		return;
	}

	const auto DeleteHandler = FOnDeleteTicketsFullResponse::CreateLambda([this, Slot, Op, TicketId](FDeleteTicketsFullResponse Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			for (FBeamMatchmakingTicket& LiveTicket : LiveTickets)
			{
				if (LiveTicket.TicketId != TicketId) continue;
				InvalidateLiveTicket(LiveTicket);
				RequestTracker->TriggerOperationSuccess(Op, TicketId.ToString());
			}
		}
		else
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.message);
		}
	});

	FBeamRequestContext Ctx;
	const auto Req = UDeleteTicketsRequest::Make(TicketId, GetTransientPackage(), {});
	MatchmakingApi->CPP_DeleteTickets(Slot, Req, DeleteHandler, Ctx, Op, this);
}


// NOTIFICATION HANDLERS

void UBeamMatchmakingSubsystem::OnMatchmakingUpdateReceived(FMatchmakingUpdateNotificationMessage Msg)
{
	const auto MsgTicketId = FGuid{Msg.TicketId};
	UE_LOG(LogBeamMatchmaking, Warning, TEXT("Received Matchmaking Update with Status=%s"), *Msg.Status)
	if (Msg.Status.Equals("Searching"))
	{
		bool bIsNewTicket = true;

		FBeamMatchmakingTicket* FoundTicket = nullptr;
		for (FBeamMatchmakingTicket& LiveTicket : LiveTickets)
		{
			if (LiveTicket.TicketId != MsgTicketId) continue;
			bIsNewTicket = false;
			FoundTicket = &LiveTicket;
		}

		if (bIsNewTicket)
		{
			TArray<FUserSlot> SlotsInMsg;
			TArray<FBeamGamerTag> GamerTagsInMsg;
			for (FString GamerTagStr : Msg.Players)
			{
				FBeamGamerTag GamerTag{GamerTagStr};
				FUserSlot SlotInTicket;
				FBeamRealmUser RealmUser{};
				FString _;
				if (UserSlots->GetUserDataWithGamerTag(GamerTag, RealmUser, SlotInTicket, _))
					SlotsInMsg.Add(SlotInTicket);

				GamerTagsInMsg.Add(GamerTag);
			}

			FBeamMatchmakingTicket NewTicket;
			NewTicket.TicketId = MsgTicketId;
			NewTicket.SlotsInTicket = SlotsInMsg;
			NewTicket.GamerTagsInTicket = GamerTagsInMsg;
			ContentSubsystem->TryGetContentOfType(FBeamContentId{Msg.MatchType}, NewTicket.GameType);

			// Update the per-slot state of matchmaking
			for (FUserSlot InMsg : SlotsInMsg)
			{
				auto SlotState = Slots.Find(InMsg);
				int64 TicketCreated;
				FDefaultValueHelper::ParseInt64(Msg.Created, TicketCreated);

				SlotState->InTicket = MsgTicketId;
				SlotState->LastJoinTime = FDateTime::FromUnixTimestamp(TicketCreated);
			}

			LiveTickets.Add(NewTicket);
			FoundTicket = &NewTicket;

			// Trigger the system level callbacks for "my party leader in another client joined and I now know that"			
			OnMatchRemoteSearchStarted.Broadcast(NewTicket);
			TArray<FOnMatchmakingTicketUpdatedCode> CodeCallbacks;
			OnMatchRemoteSearchStartedCode.MultiFind(MsgTicketId, CodeCallbacks, true);
			for (auto Callback : CodeCallbacks) auto _ = Callback.ExecuteIfBound(NewTicket);
		}

		// Trigger this ticket's OnMatchSearching callback.		
		OnMatchSearching.Broadcast(*FoundTicket);
		TArray<FOnMatchmakingTicketUpdatedCode> CodeCallbacks;
		OnMatchSearchingCode.MultiFind(MsgTicketId, CodeCallbacks, true);
		for (auto Callback : CodeCallbacks) auto _ = Callback.ExecuteIfBound(*FoundTicket);
	}

	if (Msg.Status.Equals("Ready"))
	{
		for (FBeamMatchmakingTicket& LiveTicket : LiveTickets)
		{
			if (LiveTicket.TicketId != MsgTicketId) continue;

			// Update the ticket with the LobbyId for the match.
			LiveTicket.FoundMatchLobbyId = FGuid(Msg.MatchId);

			const auto Handler = FBeamOperationEventHandlerCode::CreateLambda(
				[this, MsgTicketId](FBeamOperationEvent Evt)
				{
					FBeamMatchmakingTicket& T = *LiveTickets.FindByKey(MsgTicketId);
					if (Evt.EventType == OET_SUCCESS)
					{
						ULobby* L;
						ensureAlways(
							GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>()->TryGetLobbyById(T.
								FoundMatchLobbyId, L));

						UE_LOG(LogBeamMatchmaking, Warning, TEXT("Match Lobby Locally Fetched LobbyId=%s"),
						       *L->LobbyId.Val)

						for (auto Val : L->Data.Val)
							UE_LOG(LogBeamMatchmaking, Warning, TEXT("Lobby Data. Key=%s, Val=%s"), *Val.Key,
						       *Val.Value)

						// Trigger this ticket's OnMatchReady callback.			
						OnMatchReady.Broadcast(T);
						TArray<FOnMatchmakingTicketUpdatedCode> CodeCallbacks;
						OnMatchReadyCode.MultiFind(MsgTicketId, CodeCallbacks, true);
						for (auto Callback : CodeCallbacks) auto _ = Callback.ExecuteIfBound(T);
					}
					else
					{
						T.FoundMatchLobbyId = FGuid();

						OnMatchCancelled.Broadcast(T);
						TArray<FOnMatchmakingTicketUpdatedCode> CodeCallbacks;
						OnMatchCancelledCode.MultiFind(MsgTicketId, CodeCallbacks, true);
						for (auto Callback : CodeCallbacks) auto _ = Callback.ExecuteIfBound(T);

						InvalidateLiveTicket(T);
					}
				});

			GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>()->CPP_RefreshLobbyDataOperation(LiveTicket.SlotsInTicket[0], Handler, LiveTicket.FoundMatchLobbyId);
			UE_LOG(LogBeamMatchmaking, Warning, TEXT("Match Ready with LobbyId=%s"), *LiveTicket.FoundMatchLobbyId.ToString(EGuidFormats::DigitsWithHyphensLower))
		}
	}

	if (Msg.Status.Equals("Cancelled"))
	{
		for (FBeamMatchmakingTicket& LiveTicket : LiveTickets)
		{
			if (LiveTicket.TicketId != MsgTicketId) continue;


			OnMatchCancelled.Broadcast(LiveTicket);
			TArray<FOnMatchmakingTicketUpdatedCode> CodeCallbacks;
			OnMatchCancelledCode.MultiFind(MsgTicketId, CodeCallbacks, true);
			for (auto Callback : CodeCallbacks) auto _ = Callback.ExecuteIfBound(LiveTicket);
			InvalidateLiveTicket(LiveTicket);
		}
	}
}

void UBeamMatchmakingSubsystem::OnMatchmakingTimeoutReceived(FMatchmakingTimeoutNotificationMessage Msg)
{
	const auto MsgTicketId = FGuid{Msg.TicketId};
	for (FBeamMatchmakingTicket& LiveTicket : LiveTickets)
	{
		if (LiveTicket.TicketId != MsgTicketId) continue;

		OnMatchTimedOut.Broadcast(LiveTicket);
		TArray<FOnMatchmakingTicketUpdatedCode> CodeCallbacks;
		OnMatchTimedOutCode.MultiFind(MsgTicketId, CodeCallbacks, true);
		for (auto Callback : CodeCallbacks) auto _ = Callback.ExecuteIfBound(LiveTicket);

		InvalidateLiveTicket(LiveTicket);
	}
}

// UTILITY FUNCTIONS

void UBeamMatchmakingSubsystem::InvalidateLiveTicket(FBeamMatchmakingTicket& LiveTicket)
{
	// Copy the ticket than invalidate it
	const FBeamMatchmakingTicket InvalidatedTicket = LiveTicket;
	LiveTicket.TicketId.Invalidate();
	LiveTicket.GamerTagsInTicket.Reset();
	for (FUserSlot SlotsInTicket : LiveTicket.SlotsInTicket)
	{
		if (const auto SlotState = Slots.Find(SlotsInTicket); InvalidatedTicket.TicketId == SlotState->InTicket)
		{
			SlotState->InTicket.Invalidate();
		}
	}
	LiveTicket.SlotsInTicket.Reset();

	// Trigger the BP Cleanup for this ticket
	OnMatchTicketInvalidated.Broadcast(InvalidatedTicket);

	// Auto-Cleanup the C++ delegates.
	OnMatchSearchingCode.Remove(InvalidatedTicket.TicketId);
	OnMatchReadyCode.Remove(InvalidatedTicket.TicketId);
	OnMatchCancelledCode.Remove(InvalidatedTicket.TicketId);
	OnMatchTimedOutCode.Remove(InvalidatedTicket.TicketId);
}
