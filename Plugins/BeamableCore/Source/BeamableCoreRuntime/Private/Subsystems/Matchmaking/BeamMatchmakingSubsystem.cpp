// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Matchmaking/BeamMatchmakingSubsystem.h"

#include "Subsystems/Lobby/BeamLobbySubsystem.h"
#include "Subsystems/Matchmaking/BeamMatchmakingHooks.h"
#include "Subsystems/Stats/BeamStatsSubsystem.h"

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
	// Enable test user slots by ensuring a slot exists whenever one signs in
	if (!Slots.Contains(UserSlot))
		Slots.Add(UserSlot, FBeamMatchmakingState{UserSlot, FGuid{}});

	// Subscribe to the remote update (receives notifications about joining a queue while in a party but not as the party leader)
	const auto RemoteUpdateHandler = FOnMatchmakingRemoteUpdateNotificationCode::CreateUObject(this, &UBeamMatchmakingSubsystem::OnMatchmakingRemoteUpdateReceived, UserSlot);
	MatchmakingNotifications->CPP_SubscribeToRemoteUpdate(UserSlot, Runtime->DefaultNotificationChannel, RemoteUpdateHandler, this);

	// Subscribe to per-queue notifications
	// TODO: Replace these notifications with the RemoteUpdate one (we get all the events in the remote update)
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

void UBeamMatchmakingSubsystem::OnUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp)
{
	this->Slots[UserSlot] = FBeamMatchmakingState{UserSlot, FGuid{}};
	for (auto& LiveTicket : this->LiveTickets)
	{
		if (LiveTicket.SlotsInTicket.Contains(UserSlot))
		{
			InvalidateLiveTicket(LiveTicket);
		}
	}

	Super::OnUserSignedOut_Implementation(UserSlot, Reason, BeamRealmUser, ResultOp);
}

TArray<TSubclassOf<UBeamRuntimeSubsystem>> UBeamMatchmakingSubsystem::GetDependingOnSubsystems()
{
	TArray<TSubclassOf<UBeamRuntimeSubsystem>> DependantSubsystems =
		Super::GetDependingOnSubsystems();
	DependantSubsystems.Add(UBeamLobbySubsystem::StaticClass());
	return DependantSubsystems;
}

// LOCAL STATE GETTERS

bool UBeamMatchmakingSubsystem::IsUserSlotInQueue(FUserSlot Slot)
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
	UBeamMatchmakingTryJoinQueueHookHandle* BeamMatchmakingTryJoinQueueHookHandle = Runtime->RequestTrackerSystem->BeginHookHandle<UBeamMatchmakingTryJoinQueueHookHandle>(OnOperationEvent, GetTransientPackage());

	TryJoinQueueHook(UserSlot, GameTypeQueue, Team, {}, BeamMatchmakingTryJoinQueueHookHandle);
	
	return BeamMatchmakingTryJoinQueueHookHandle->MainOperationHandle;
}

FBeamOperationHandle UBeamMatchmakingSubsystem::CPP_TryJoinQueueOperation(FUserSlot UserSlot, const FBeamContentId& GameTypeQueue, FOptionalString Team,
                                                                          FBeamOperationEventHandlerCode OnOperationEvent)
{
	UBeamMatchmakingTryJoinQueueHookHandle* BeamMatchmakingTryJoinQueueHookHandle = Runtime->RequestTrackerSystem->CPP_BeginHookHandle<UBeamMatchmakingTryJoinQueueHookHandle>(OnOperationEvent, GetTransientPackage());

	TryJoinQueueHook(UserSlot, GameTypeQueue, Team, {}, BeamMatchmakingTryJoinQueueHookHandle);
	
	return BeamMatchmakingTryJoinQueueHookHandle->MainOperationHandle;
}

FBeamOperationHandle UBeamMatchmakingSubsystem::TryJoinQueueWithTagsOperation(FUserSlot UserSlot, FBeamContentId GameTypeQueue, FOptionalString Team, TArray<FBeamTag> Tags,
                                                                              FBeamOperationEventHandler OnOperationEvent)
{
	UBeamMatchmakingTryJoinQueueHookHandle* BeamMatchmakingTryJoinQueueHookHandle = Runtime->RequestTrackerSystem->BeginHookHandle<UBeamMatchmakingTryJoinQueueHookHandle>(OnOperationEvent, GetTransientPackage());

	TryJoinQueueHook(UserSlot, GameTypeQueue, Team, FOptionalArrayOfBeamTag{Tags}, BeamMatchmakingTryJoinQueueHookHandle);
	
	return BeamMatchmakingTryJoinQueueHookHandle->MainOperationHandle;
}

FBeamOperationHandle UBeamMatchmakingSubsystem::CPP_TryJoinQueueWithTagsOperation(FUserSlot UserSlot, const FBeamContentId& GameTypeQueue, FOptionalString Team, TArray<FBeamTag> Tags,
                                                                                  FBeamOperationEventHandlerCode OnOperationEvent)
{
	UBeamMatchmakingTryJoinQueueHookHandle* BeamMatchmakingTryJoinQueueHookHandle = Runtime->RequestTrackerSystem->CPP_BeginHookHandle<UBeamMatchmakingTryJoinQueueHookHandle>(OnOperationEvent, GetTransientPackage());

	TryJoinQueueHook(UserSlot, GameTypeQueue, Team, FOptionalArrayOfBeamTag{Tags}, BeamMatchmakingTryJoinQueueHookHandle);
	
	return BeamMatchmakingTryJoinQueueHookHandle->MainOperationHandle;
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

void UBeamMatchmakingSubsystem::StartParallelHookOperation(TArray<FOnBeamableTryJoinMatchmakingQueueParallel> PreTryJoinMatchmakingQueueParallel, FBeamOperationHandle ParallelHandle)
{
	FBeamWaitHandle _;
	RequestTracker->InvokeAndWaitForHooks(_, PreTryJoinMatchmakingQueueParallel, FOnWaitCompleteCode::CreateLambda([this, ParallelHandle](FBeamWaitCompleteEvent Evt)
	{
		TArray<FString> Errs;
		if (RequestTracker->IsWaitFailed(Evt, Errs))
		{
			FString Err;
			for (const auto& Error : Errs) Err += FString::Printf(TEXT("%s\n"), *Error);
				
			RequestTracker->TriggerOperationError(ParallelHandle, Err);
			return;
		}
		RequestTracker->TriggerOperationSuccess(ParallelHandle, TEXT("SUCCESS"));
	}), ParallelHandle);
}

void UBeamMatchmakingSubsystem::TryJoinQueueHook(FUserSlot UserSlot, FBeamContentId GameTypeQueue, FOptionalString Team, FOptionalArrayOfBeamTag Tags, UBeamMatchmakingTryJoinQueueHookHandle* BeamMatchmakingTryJoinQueueHookHandle)
{

	TArray<FOnBeamableTryJoinMatchmakingQueueParallel> PreTryJoinMatchmakingQueueParallel;
	
	TArray<TSoftClassPtr<UBeamMatchmakingHooks>> PreBeamHooksSoftPtrParallel = GetDefault<UBeamRuntimeSettings>()->PreJoinMatchmakingHookParallel;
	
	// Running Pre Hook Calls
	for (auto BeamMatchmakingHook : PreBeamHooksSoftPtrParallel)
	{
		if (!BeamMatchmakingHook.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("The pre matchmaking setup for is invalid"));
			continue;
		}
		PreTryJoinMatchmakingQueueParallel.Add(FOnBeamableTryJoinMatchmakingQueueParallel::CreateLambda([this, BeamMatchmakingHook](FBeamOperationHandle HookHandle)
		{
			UBeamMatchmakingHooks* Extension = NewObject<UBeamMatchmakingHooks>(GetTransientPackage(), BeamMatchmakingHook.LoadSynchronous());
			Extension->SetContext(this);
			auto ParallelHandle = RequestTracker->CPP_BeginOperation({}, GetName(), {});
				
			Extension->PreTryJoinQueueHookActionParallel(ParallelHandle);
				
			return ParallelHandle;
		}));
	}

	// Start the parallel PreTryJoinQueue
	FBeamOperationHandle ParallelHandle = RequestTracker->CPP_BeginOperation({}, GetName(), {});
	StartParallelHookOperation(PreTryJoinMatchmakingQueueParallel, ParallelHandle);

	TArray<FOnBeamableTryJoinMatchmakingQueue> TryJoinMatchmakingQueueSequentially;
	
	TArray<TSoftClassPtr<UBeamMatchmakingHooks>> PreBeamHooksSoftPtrSequentially = GetDefault<UBeamRuntimeSettings>()->PreJoinMatchmakingHookSequentially;
	
	// Running Pre Hook Calls
	for (auto BeamMatchmakingHook : PreBeamHooksSoftPtrSequentially)
	{
		if (!BeamMatchmakingHook.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("The pre matchmaking setup for is invalid"));
			continue;
		}
	
		TryJoinMatchmakingQueueSequentially.Add(FOnBeamableTryJoinMatchmakingQueue::CreateLambda([this, BeamMatchmakingHook](UBeamMatchmakingTryJoinQueueHookHandle* HookHandle)
		{
			UBeamMatchmakingHooks* Extension = NewObject<UBeamMatchmakingHooks>(GetTransientPackage(), BeamMatchmakingHook.LoadSynchronous());
			Extension->SetContext(this);
			
			auto OperationHandle = RequestTracker->CPP_PreHookCall( HookHandle );
			Extension->PreTryJoinQueueHookAction(HookHandle);
			return OperationHandle;
		}));
	}

	// Wait for the parallel
	TryJoinMatchmakingQueueSequentially.Add(FOnBeamableTryJoinMatchmakingQueue::CreateLambda([this, ParallelHandle](UBeamMatchmakingTryJoinQueueHookHandle* HookHandle)
	{
		return ParallelHandle;
	}));
	
	
	if (GetDefault<UBeamRuntimeSettings>()->DefaultMatchmakingHook.IsValid())
	{
		// Running Update Ping
	
		TryJoinMatchmakingQueueSequentially.Add(FOnBeamableTryJoinMatchmakingQueue::CreateLambda([this](UBeamMatchmakingTryJoinQueueHookHandle* HookHandle)
		{
			UBeamMatchmakingHooks* Extension = NewObject<UBeamMatchmakingHooks>(GetTransientPackage(), GetDefault<UBeamRuntimeSettings>()->DefaultMatchmakingHook.LoadSynchronous());
			Extension->SetContext(this);
		
			auto OperationHandle = RequestTracker->CPP_PreHookCall( HookHandle );
			Extension->UpdatePings(HookHandle);
			return OperationHandle;
		}));
	
		// Running Commit Ping
		TryJoinMatchmakingQueueSequentially.Add(FOnBeamableTryJoinMatchmakingQueue::CreateLambda([this, UserSlot](UBeamMatchmakingTryJoinQueueHookHandle* HookHandle)
		{
			for (auto JoinMatchmakingQueue : HookHandle->PingsPerRegion)
			{
				UE_LOG(LogTemp, Warning, TEXT("Ping - %s %d"), *JoinMatchmakingQueue.Key, JoinMatchmakingQueue.Value);
			}
			auto OperationHandle = RequestTracker->CPP_PreHookCall( HookHandle );
			CommitRegionPing(UserSlot, HookHandle->PingsPerRegion, OperationHandle);
			return OperationHandle;
		}));

		// Try Join Queue
		TryJoinMatchmakingQueueSequentially.Add(FOnBeamableTryJoinMatchmakingQueue::CreateLambda([this, UserSlot, GameTypeQueue, Team](UBeamMatchmakingTryJoinQueueHookHandle* HookHandle)
		{
			UBeamMatchmakingHooks* Extension = NewObject<UBeamMatchmakingHooks>(GetTransientPackage(), GetDefault<UBeamRuntimeSettings>()->DefaultMatchmakingHook.LoadSynchronous());
			auto OperationHandle = RequestTracker->CPP_PreHookCall( HookHandle );
		
			UE_LOG(LogTemp, Warning, TEXT("Join Matchmaking Queue"));
			if (Extension != nullptr)
			{
				Extension->SetContext(this);
				Extension->TryJoinQueue(UserSlot, GameTypeQueue, Team, {}, OperationHandle);
			}else
			{
				// In the case of a none be setup in the default hook we call the default implementation
				TryJoinQueue(UserSlot, GameTypeQueue, Team, {}, OperationHandle);
			}
	
			return OperationHandle;
		}));
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("The default matchmaking setup for %s is invalid"), *GetDefault<UBeamRuntimeSettings>()->DefaultMatchmakingHook->GetName());
	}
	// Start the parallel PreTryJoinQueue
	FBeamOperationHandle AfterParallelHandle = RequestTracker->CPP_BeginOperation({}, GetName(), {});

	
	TArray<TSoftClassPtr<UBeamMatchmakingHooks>> AfterBeamHooksSoftPtrSequentially = GetDefault<UBeamRuntimeSettings>()->AfterTryJoinMatchmakingHookSequentially;


	// Wait for the parallel
	TryJoinMatchmakingQueueSequentially.Add(FOnBeamableTryJoinMatchmakingQueue::CreateLambda([this, AfterParallelHandle](UBeamMatchmakingTryJoinQueueHookHandle* HookHandle)
	{
		TArray<FOnBeamableTryJoinMatchmakingQueueParallel> AfterTryJoinMatchmakingQueueParallel;
		
		TArray<TSoftClassPtr<UBeamMatchmakingHooks>> AfterBeamHooksSoftPtrParallel = GetDefault<UBeamRuntimeSettings>()->AfterTryJoinMatchmakingHookParallel;

		for (auto MatchmakingHookPtr : AfterBeamHooksSoftPtrParallel)
		{
			if (!MatchmakingHookPtr.IsValid())
			{
				UE_LOG(LogTemp, Error, TEXT("The pos matchmaking setup for is invalid"));
				continue;
			}
	
			AfterTryJoinMatchmakingQueueParallel.Add(FOnBeamableTryJoinMatchmakingQueueParallel::CreateLambda([this, MatchmakingHookPtr](FBeamOperationHandle HookHandle)
			{
				UBeamMatchmakingHooks* Extension = NewObject<UBeamMatchmakingHooks>(GetTransientPackage(), MatchmakingHookPtr.LoadSynchronous());
				Extension->SetContext(this);
				auto ParallelHandle = RequestTracker->CPP_BeginOperation({}, GetName(), {});
			
				Extension->AfterTryJoinQueueHookActionParallel(ParallelHandle);
			
				return ParallelHandle;
			}));
		}
		StartParallelHookOperation(AfterTryJoinMatchmakingQueueParallel, AfterParallelHandle);
		return RequestTracker->CPP_BeginSuccessfulOperation({}, GetName(), TEXT(""), {});
	}));
	
	for (auto MatchmakingHookPtr : AfterBeamHooksSoftPtrSequentially)
	{
		if (!MatchmakingHookPtr.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("The pos matchmaking setup for is invalid"));
			continue;
		}
	
		TryJoinMatchmakingQueueSequentially.Add(FOnBeamableTryJoinMatchmakingQueue::CreateLambda([this, MatchmakingHookPtr](UBeamMatchmakingTryJoinQueueHookHandle* HookHandle)
		{
			UBeamMatchmakingHooks* Extension = NewObject<UBeamMatchmakingHooks>(GetTransientPackage(), MatchmakingHookPtr.LoadSynchronous());
			Extension->SetContext(this);
			
			auto OperationHandle = RequestTracker->CPP_PreHookCall( HookHandle );
			Extension->AfterTryJoinQueueHookAction(HookHandle);
			return OperationHandle;
		}));
	}

	
	// Wait for the parallel
	TryJoinMatchmakingQueueSequentially.Add(FOnBeamableTryJoinMatchmakingQueue::CreateLambda([this, AfterParallelHandle](UBeamMatchmakingTryJoinQueueHookHandle* HookHandle)
	{
		return AfterParallelHandle;
	}));
	
	const auto HookWaitHandler = TDelegate<void(FBeamWaitCompleteEvent)>::CreateLambda([this, UserSlot, GameTypeQueue, Team, BeamMatchmakingTryJoinQueueHookHandle](FBeamWaitCompleteEvent Evt)
	{
		TArray<FString> Errs;
		if (RequestTracker->IsWaitFailed(Evt, Errs))
		{
			FString Err;
			for (const auto& Error : Errs) Err += FString::Printf(TEXT("%s\n"), *Error);
			
			RequestTracker->TriggerOperationError(BeamMatchmakingTryJoinQueueHookHandle->MainOperationHandle, Err);
			return;
		}
		RequestTracker->TriggerOperationSuccess(BeamMatchmakingTryJoinQueueHookHandle->MainOperationHandle, TEXT("SUCCESS"));
	});
	FBeamWaitHandle __;
	
	RequestTracker->InvokeAndWaitSequentiallyForHooks(__, TryJoinMatchmakingQueueSequentially, HookWaitHandler,  BeamMatchmakingTryJoinQueueHookHandle);
	
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
				if (UserSlots->GetUserDataWithGamerTag(GamerTag, RealmUser, SlotInTicket, _, this))
					SlotsInTicket.Add(SlotInTicket);

				GamerTagsInTicket.Add(GamerTag);
			}

			FBeamMatchmakingTicket NewTicket;
			NewTicket.TicketId = TicketId;
			NewTicket.SlotsInTicket = SlotsInTicket;
			NewTicket.GamerTagsInTicket = GamerTagsInTicket;
			ContentSubsystem->TryGetContentOfType(FBeamContentId{Ticket->MatchType.Val}, NewTicket.GameType);

			// Update the requesting slot's state of matchmaking and then complete the operation
			auto SlotState = Slots.Find(Slot);

			SlotState->InTicket = TicketId;
			SlotState->LastJoinTime = Ticket->Created.Val;
			LiveTickets.Add(NewTicket);

			RequestTracker->TriggerOperationSuccess(Op, TicketId.ToString());
		}
		else
		{
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.message);
		}
	});

	// We use this to enable compatibility with UE's Real-Time Multiplayer Gameplay Framework
	const auto LocalPlayer = Runtime->GetLocalPlayerForSlot(Slot);
	if (LocalPlayer && LocalPlayer->GetPreferredUniqueNetId().IsValid())
	{
		auto TagsVal = Tags.GetValueOrDefault(TArray<FBeamTag>{});
		TagsVal.Add(FBeamTag{UBeamLobbySubsystem::Reserved_PlayerTag_UniqueNetId_Property, LocalPlayer->GetPreferredUniqueNetId().GetUniqueNetId()->ToString()});
		Tags.Val = TagsVal;
	}
	
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
			for (FBeamMatchmakingTicket LiveTicket : LiveTickets)
			{
				if (LiveTicket.TicketId != TicketId) continue;
				InvalidateLiveTicket(LiveTicket);
				RequestTracker->TriggerOperationSuccess(Op, TicketId.ToString());
				break;
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

void UBeamMatchmakingSubsystem::OnMatchmakingRemoteUpdateReceived(FMatchmakingRemoteUpdateNotificationMessage Msg, FUserSlot UserSlot)
{
	const auto MsgTicketId = FGuid{Msg.TicketId};
	UE_LOG(LogBeamMatchmaking, Warning, TEXT("Received Matchmaking Update with Status=%s"), *Msg.Event)
	if (Msg.Event.Equals("Searching"))
	{
		// If we were not in a ticket... but now we are...
		if (Slots[UserSlot].InTicket == FGuid{})
		{
			const auto Req = UApiMatchmakingGetTicketsByIdRequest::Make(MsgTicketId, GetTransientPackage(), {});
			const auto Handler = FOnApiMatchmakingGetTicketsByIdFullResponse::CreateLambda([this, MsgTicketId, UserSlot](FApiMatchmakingGetTicketsByIdFullResponse Resp)
			{
				if (Resp.State == RS_Success)
				{
					const auto TicketData = Resp.SuccessData;

					TArray<FUserSlot> SlotsInMsg;
					TArray<FBeamGamerTag> GamerTagsInMsg;
					for (FBeamGamerTag GamerTag : TicketData->Players.Val)
					{
						FUserSlot SlotInTicket;
						FBeamRealmUser RealmUser{};
						FString _;
						if (UserSlots->GetUserDataWithGamerTag(GamerTag, RealmUser, SlotInTicket, _, this))
							SlotsInMsg.Add(SlotInTicket);

						GamerTagsInMsg.Add(GamerTag);
					}

					FBeamMatchmakingTicket NewTicket;
					NewTicket.TicketId = MsgTicketId;
					NewTicket.SlotsInTicket = SlotsInMsg;
					NewTicket.GamerTagsInTicket = GamerTagsInMsg;
					if (!LiveTickets.Contains(NewTicket))
					{
						ContentSubsystem->TryGetContentOfType(TicketData->MatchType.Val, NewTicket.GameType);
						LiveTickets.Add(NewTicket);
					}

					// Update the per-slot state of matchmaking
					auto SlotState = Slots.Find(UserSlot);

					SlotState->InTicket = MsgTicketId;
					SlotState->LastJoinTime = TicketData->Created.Val;


					// Trigger the system level callbacks for "my party leader in another client joined and I now know that"			
					const auto _ = OnMatchSearchStartedCode.ExecuteIfBound(NewTicket);
					OnMatchSearchStarted.Broadcast(NewTicket);
				}
			});
			FBeamRequestContext Ctx;
			MatchmakingApi->CPP_ApiMatchmakingGetTicketsById(UserSlot, Req, Handler, Ctx, {}, this);
		}
	}
}

void UBeamMatchmakingSubsystem::OnMatchmakingUpdateReceived(FMatchmakingUpdateNotificationMessage Msg)
{
	const auto MsgTicketId = FGuid{Msg.TicketId};
	UE_LOG(LogBeamMatchmaking, Warning, TEXT("Received Matchmaking Update with Status=%s"), *Msg.Status)
	if (Msg.Status.Equals("Searching"))
	{
		// We are now ignoring the Searching end-point here and instead handling it in the RemoteUpdate callback instead.		
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
						TArray<FOnMatchmakingTicketUpdatedCode> CodeCallbacks;
						OnMatchReadyCode.MultiFind(MsgTicketId, CodeCallbacks, true);
						for (auto Callback : CodeCallbacks) auto _ = Callback.ExecuteIfBound(T);

						OnMatchReady.Broadcast(T);

						// We should invalidate the ticket as we already have the match ready.
						InvalidateLiveTicket(T);
					}
					else
					{
						T.FoundMatchLobbyId = FGuid();

						TArray<FOnMatchmakingTicketUpdatedCode> CodeCallbacks;
						OnMatchCancelledCode.MultiFind(MsgTicketId, CodeCallbacks, true);
						for (auto Callback : CodeCallbacks) auto _ = Callback.ExecuteIfBound(T);

						OnMatchCancelled.Broadcast(T);

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

			TArray<FOnMatchmakingTicketUpdatedCode> CodeCallbacks;
			OnMatchCancelledCode.MultiFind(MsgTicketId, CodeCallbacks, true);
			for (auto Callback : CodeCallbacks) auto _ = Callback.ExecuteIfBound(LiveTicket);

			OnMatchCancelled.Broadcast(LiveTicket);

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

		TArray<FOnMatchmakingTicketUpdatedCode> CodeCallbacks;
		OnMatchTimedOutCode.MultiFind(MsgTicketId, CodeCallbacks, true);
		for (auto Callback : CodeCallbacks) auto _ = Callback.ExecuteIfBound(LiveTicket);

		OnMatchTimedOut.Broadcast(LiveTicket);

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
	OnMatchReadyCode.Remove(InvalidatedTicket.TicketId);
	OnMatchCancelledCode.Remove(InvalidatedTicket.TicketId);
	OnMatchTimedOutCode.Remove(InvalidatedTicket.TicketId);
}

void UBeamMatchmakingSubsystem::CommitRegionPing(FUserSlot UserSlot, TMap<FString, int32> RegionPings, FBeamOperationHandle OperationHandle)
{
	FBeamOperationEventHandlerCode StatsOperationHandle;
	StatsOperationHandle.BindLambda([this, OperationHandle](FBeamOperationEvent Evt)
	{
		UE_LOG(LogTemp, Display, TEXT("Updated Region Pings"));
	
		if (Evt.EventType == OET_SUCCESS)
		{
			RequestTracker->TriggerOperationSuccess(OperationHandle, "Success");
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Failed to update Region Pings"));
			RequestTracker->TriggerOperationError(OperationHandle, "Failed to update Region Pings");
		}
	});
	
	const FString PingsJson = ConvertRegionPingsToJson(RegionPings);

	TMap<FString, FString> StatsMap;
	StatsMap.Add("beam.region.pings", PingsJson);

	UBeamStatsSubsystem* Stats = GetGameInstance()->GetSubsystem<UBeamStatsSubsystem>();
	UBeamStatUpdateCommand* Command;
	
	if (Stats->TryCreateUpdateCommand(UserSlot, StatsMap, Command))
	{
		Stats->CPP_CommitStatsOperation(UserSlot, StatsOperationHandle);
	}else
	{
		RequestTracker->TriggerOperationError(OperationHandle, "Failed to update Region Pings");
	}
}

FString UBeamMatchmakingSubsystem::ConvertRegionPingsToJson(TMap<FString, int32> RegionPings)
{
	// Create a new JSON object
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	// For each pair in the Pings map, add it to the JSON object
	for (const auto& Pair : RegionPings)
	{
		if (Pair.Value != 0)
		{
			JsonObject->SetNumberField(Pair.Key, Pair.Value);
		}
	}

	// Serialize the JSON object to a string
	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer))
	{
		return OutputString;
	}

	return TEXT("{}");
}
