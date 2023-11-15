// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamGameTypeContent.h"
#include "AutoGen/SubSystems/BeamMatchmakingApi.h"
#include "BeamBackend/SemanticTypes/BeamStatsType.h"
#include "BeamNotifications/SubSystems/BeamMatchmakingNotifications.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "Subsystems/Content/BeamContentSubsystem.h"
#include "BeamMatchmakingSubsystem.generated.h"

class UBeamMatchmakingSubsystem;

USTRUCT(BlueprintType)
struct FBeamMatchmakingTicket
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	FGuid TicketId;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	UBeamGameTypeContent* GameType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	TArray<FUserSlot> SlotsInTicket;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	TArray<FBeamGamerTag> GamerTagsInTicket;
};


DECLARE_DELEGATE_OneParam(FOnMatchmakingTicketUpdated, const FBeamMatchmakingTicket&)
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMatchmakingTicketUpdatedCode, const FBeamMatchmakingTicket&, Ticket);


USTRUCT(BlueprintType)
struct FBeamMatchmakingState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	FUserSlot OwnerSlot;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	FGuid InTicket;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	FDateTime LastJoinTime;
};


/**
 * 
 */
UCLASS(BlueprintType)
class BEAMABLECORERUNTIME_API UBeamMatchmakingSubsystem : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	UBeamMatchmakingApi* MatchmakingApi;

	UPROPERTY()
	UBeamMatchmakingNotifications* MatchmakingNotifications;

	UPROPERTY()
	UBeamUserSlots* UserSlots;

	UPROPERTY()
	UBeamRequestTracker* RequestTracker;

	UPROPERTY()
	UBeamContentSubsystem* ContentSubsystem;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	TArray<FBeamMatchmakingTicket> LiveTickets;

	FOnMatchmakingTicketUpdated     OnMatchRemoteSearchStarted;
	FOnMatchmakingTicketUpdatedCode OnMatchRemoteSearchStartedCode;

	TMap<FGuid, FOnMatchmakingTicketUpdated>     OnMatchSearching;
	TMap<FGuid, FOnMatchmakingTicketUpdatedCode> OnMatchSearchingCode;

	TMap<FGuid, FOnMatchmakingTicketUpdated>     OnMatchReady;
	TMap<FGuid, FOnMatchmakingTicketUpdatedCode> OnMatchReadyCode;

	TMap<FGuid, FOnMatchmakingTicketUpdated>     OnMatchCancelled;
	TMap<FGuid, FOnMatchmakingTicketUpdatedCode> OnMatchCancelledCode;

	TMap<FGuid, FOnMatchmakingTicketUpdated>     OnMatchTimedOut;
	TMap<FGuid, FOnMatchmakingTicketUpdatedCode> OnMatchTimedOutCode;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	TMap<FUserSlot, FBeamMatchmakingState> Slots;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		Super::Initialize(Collection);
		ContentSubsystem = Collection.InitializeDependency<UBeamContentSubsystem>();

		MatchmakingApi           = GEngine->GetEngineSubsystem<UBeamMatchmakingApi>();
		MatchmakingNotifications = GEngine->GetEngineSubsystem<UBeamMatchmakingNotifications>();

		UserSlots      = Runtime->UserSlotSystem;
		RequestTracker = Runtime->RequestTrackerSystem;
	}

	virtual void InitializeWhenUnrealReady_Implementation(FBeamOperationHandle& ResultOp) override
	{
		const auto RuntimeSlots = GetDefault<UBeamCoreSettings>()->RuntimeUserSlots;
		for (FString RuntimeSlot : RuntimeSlots)
		{
			Slots.Add(RuntimeSlot, FBeamMatchmakingState{RuntimeSlot, FGuid{}});
		}
		Super::InitializeWhenUnrealReady_Implementation(ResultOp);
	}

	virtual void OnPostUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp) override
	{
		TArray<FBeamContentId> AllGameTypes;
		ContentSubsystem->GetIdsOfContentType(UBeamGameTypeContent::StaticClass(), AllGameTypes);
		for (FBeamContentId GameType : AllGameTypes)
		{
			UE_LOG(LogBeamMatchmaking, Display, TEXT("Beamable Matchmaking | Registering for notifications of GAME_TYPE=%s"), *GameType.AsString);

			const auto UpdateHandler  = FOnMatchmakingUpdateNotificationCode::CreateUObject(this, &UBeamMatchmakingSubsystem::OnMatchmakingUpdateReceived);
			const auto TimeoutHandler = FOnMatchmakingTimeoutNotificationCode::CreateUObject(this, &UBeamMatchmakingSubsystem::OnMatchmakingTimeoutReceived);

			MatchmakingNotifications->CPP_SubscribeToMatchmakingUpdate(UserSlot, Runtime->DefaultNotificationChannel, GameType, UpdateHandler);
			MatchmakingNotifications->CPP_SubscribeToMatchmakingTimeout(UserSlot, Runtime->DefaultNotificationChannel, GameType, TimeoutHandler);
		}
		Super::OnPostUserSignedIn_Implementation(UserSlot, BeamRealmUser, bIsOwnerUserAuth, ResultOp);
	}

	/**
	 * @brief Joins the given game type queue.
	 * The user in the given user slot is added to the queue. If that user is in a party:
	 *   - If its the party leader, the entire party will be added to the queue and other clients will receive notifications for it.
	 *   - If its not the party leader, the operation will fail.
	 *
	 * If the user is already in a queue, it'll fail. If the queue type has more than one team, the provided team must match one of the team names.
	 * If the queue type has a single team (FFA, for example), you can leave the team blank. Queue types with no teams are not valid.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Matchmaking", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle TryJoinQueueOperation(FUserSlot UserSlot, FBeamContentId GameTypeQueue, FOptionalString Team, FBeamOperationEventHandler OnOperationEvent, UObject* CallingContext)
	{
		const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
		TryJoinQueue(UserSlot, GameTypeQueue, Team, Handle);
		return Handle;
	}

	/**
	 * @copydoc TryJoinQueueOperation 
	 */
	FBeamOperationHandle CPP_TryJoinQueueOperation(FUserSlot UserSlot, const FBeamContentId& GameTypeQueue, FOptionalString Team, FBeamOperationEventHandlerCode OnOperationEvent, UObject* CallingContext)
	{
		const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
		TryJoinQueue(UserSlot, GameTypeQueue, Team, Handle);
		return Handle;
	}

	/**
	 * @brief Leaves the given queue. If the user is not in a queue, this fails.
	 * The user in the given user slot is added to the queue. If that user is in a party:
	 *   - If its the party leader, the entire party will be added to the queue and other clients will receive notifications for it.
	 *   - If its not the party leader, the operation will fail.
	 *
	 * If the user is already in a queue, it'll fail. If the queue type has more than one team, the provided team must match one of the team names.
	 * If the queue type has a single team (FFA, for example), you can leave the team blank. Queue types with no teams are not valid.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Matchmaking", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle TryLeaveQueueOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, UObject* CallingContext)
	{
		const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
		TryLeaveQueue(UserSlot, Handle);
		return Handle;
	}

	/**
	 * @copydoc TryLeaveQueueOperation 
	 */
	FBeamOperationHandle CPP_TryLeaveQueueOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, UObject* CallingContext)
	{
		const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
		TryLeaveQueue(UserSlot, Handle);
		return Handle;
	}

	/**
	 * Checks if the given user slot is in a queue. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AutoCreateRefTerm="Slot"))
	bool IsUserSlotInQueue(const FUserSlot& Slot)
	{
		const auto State = Slots.Find(Slot);
		return State && State->InTicket.IsValid();
	}

private:
	// Operation Implementations
	void TryJoinQueue(FUserSlot Slot, FBeamContentId GameTypeQueue, FOptionalString Team, FBeamOperationHandle Op)
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
			const auto ErrMsg = FString::Printf(TEXT("ContentId \"%s\" must be a %s."), *GameTypeQueue.AsString,
			                                    *UBeamGameTypeContent::StaticClass()->GetFName().ToString());

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
			if (Resp.State == RS_Success)
			{
				const auto Tickets = Resp.SuccessData;
				if (!Tickets->Tickets.IsSet)
				{
					const auto ErrMsg = FString::Printf(TEXT("Something went wrong and no ticket was returned. You should never see this."));
					RequestTracker->TriggerOperationError(Op, ErrMsg);
					return;
				}

				const auto Ticket   = Tickets->Tickets.Val[0];
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
				for (FString Val : Ticket->Players.Val)
				{
					FBeamGamerTag  GamerTag{Val};
					FUserSlot      SlotInTicket;
					FBeamRealmUser RealmUser{};
					FString        _;
					if (UserSlots->GetUserDataWithGamerTag(GamerTag, RealmUser, SlotInTicket, _))
						SlotsInTicket.Add(SlotInTicket);
					
					GamerTagsInTicket.Add(GamerTag);
				}

				FBeamMatchmakingTicket NewTicket;
				NewTicket.TicketId          = TicketId;
				NewTicket.SlotsInTicket     = SlotsInTicket;
				NewTicket.GamerTagsInTicket = GamerTagsInTicket;
				ContentSubsystem->TryGetContentOfType(FBeamContentId{Ticket->MatchType.Val}, NewTicket.GameType);

				// Update the per-slot state of matchmaking
				for (FUserSlot InMsg : SlotsInTicket)
				{
					auto  SlotState = Slots.Find(InMsg);
					int64 TicketCreated;
					FDefaultValueHelper::ParseInt64(Ticket->Created.Val, TicketCreated);

					SlotState->InTicket     = TicketId;
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
		const auto          Req = UPostTicketsRequest::Make(FOptionalBool{true}, {}, Team, {}, FOptionalArrayOfBeamContentId{{GameTypeQueue}}, GetTransientPackage(), {});
		MatchmakingApi->CPP_PostTickets(Slot, Req, Handler, Ctx, Op, this);
	}

	void TryLeaveQueue(FUserSlot Slot, FBeamOperationHandle Op)
	{
		if (!IsUserSlotInQueue(Slot))
		{
			const auto ErrMsg = FString::Printf(TEXT("User Slot \"%s\" not in queue."), *Slot.Name);
			RequestTracker->TriggerOperationError(Op, ErrMsg);
			return;
		}

		const auto SlotState = Slots.Find(Slot);
		const auto TicketId  = SlotState->InTicket;
		if (!TicketId.IsValid())
		{
			const auto ErrMsg = FString::Printf(TEXT("User Slot \"%s\" ticket is invalid. You should never see this."), *Slot.Name);
			RequestTracker->TriggerOperationError(Op, ErrMsg);
			return;
		}

		const auto DeleteHandler = FOnDeleteTicketsFullResponse::CreateLambda([this, Slot, Op, TicketId](FDeleteTicketsFullResponse Resp)
		{
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
		const auto          Req = UDeleteTicketsRequest::Make(TicketId, GetTransientPackage(), {});
		MatchmakingApi->CPP_DeleteTickets(Slot, Req, DeleteHandler, Ctx, Op, this);
	}


	// Notification Handlers
	void OnMatchmakingUpdateReceived(FMatchmakingUpdateNotificationMessage Msg)
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
				FoundTicket  = &LiveTicket;
			}

			if (bIsNewTicket)
			{
				TArray<FUserSlot>     SlotsInMsg;
				TArray<FBeamGamerTag> GamerTagsInMsg;
				for (FString GamerTagStr : Msg.Players)
				{
					FBeamGamerTag  GamerTag{GamerTagStr};
					FUserSlot      SlotInTicket;
					FBeamRealmUser RealmUser{};
					FString        _;
					if (UserSlots->GetUserDataWithGamerTag(GamerTag, RealmUser, SlotInTicket, _))
						SlotsInMsg.Add(SlotInTicket);

					GamerTagsInMsg.Add(GamerTag);
				}

				FBeamMatchmakingTicket NewTicket;
				NewTicket.TicketId          = MsgTicketId;
				NewTicket.SlotsInTicket     = SlotsInMsg;
				NewTicket.GamerTagsInTicket = GamerTagsInMsg;
				ContentSubsystem->TryGetContentOfType(FBeamContentId{Msg.MatchType}, NewTicket.GameType);

				// Update the per-slot state of matchmaking
				for (FUserSlot InMsg : SlotsInMsg)
				{
					auto  SlotState = Slots.Find(InMsg);
					int64 TicketCreated;
					FDefaultValueHelper::ParseInt64(Msg.Created, TicketCreated);

					SlotState->InTicket     = MsgTicketId;
					SlotState->LastJoinTime = FDateTime::FromUnixTimestamp(TicketCreated);
				}

				LiveTickets.Add(NewTicket);
				FoundTicket = &NewTicket;

				// Trigger the system level callbacks for "my party leader in another client joined and I now know that"
				OnMatchRemoteSearchStarted.ExecuteIfBound(*FoundTicket);
				OnMatchRemoteSearchStartedCode.ExecuteIfBound(*FoundTicket);
			}

			// Trigger this ticket's OnMatchSearching callback.
			const auto SearchingBlueprintHandler = OnMatchSearching.Find(MsgTicketId);
			const auto SearchingCodeHandler      = OnMatchSearchingCode.Find(MsgTicketId);
			if (SearchingBlueprintHandler) SearchingBlueprintHandler->ExecuteIfBound(*FoundTicket);
			if (SearchingCodeHandler) SearchingCodeHandler->ExecuteIfBound(*FoundTicket);
		}

		if (Msg.Status.Equals("Ready"))
		{
			for (FBeamMatchmakingTicket& LiveTicket : LiveTickets)
			{
				if (LiveTicket.TicketId != MsgTicketId) continue;
				// Trigger this ticket's OnMatchReady callback.
				const auto SearchingBlueprintHandler = OnMatchSearching.Find(MsgTicketId);
				const auto SearchingCodeHandler      = OnMatchSearchingCode.Find(MsgTicketId);
				if (SearchingBlueprintHandler) SearchingBlueprintHandler->ExecuteIfBound(LiveTicket);
				if (SearchingCodeHandler) SearchingCodeHandler->ExecuteIfBound(LiveTicket);
			}
		}

		if (Msg.Status.Equals("Cancelled"))
		{
			for (FBeamMatchmakingTicket& LiveTicket : LiveTickets)
			{
				if (LiveTicket.TicketId != MsgTicketId) continue;
				const auto BlueprintHandler = OnMatchCancelled.Find(MsgTicketId);
				const auto CodeHandler      = OnMatchCancelledCode.Find(MsgTicketId);

				if (BlueprintHandler) BlueprintHandler->ExecuteIfBound(LiveTicket);
				if (CodeHandler) CodeHandler->ExecuteIfBound(LiveTicket);

				InvalidateLiveTicket(LiveTicket);
			}
		}
	}

	void OnMatchmakingTimeoutReceived(FMatchmakingTimeoutNotificationMessage Msg)
	{
		const auto MsgTicketId = FGuid{Msg.TicketId};
		for (FBeamMatchmakingTicket& LiveTicket : LiveTickets)
		{
			if (LiveTicket.TicketId != MsgTicketId) continue;
			const auto BlueprintHandler = OnMatchTimedOut.Find(MsgTicketId);
			const auto CodeHandler      = OnMatchTimedOutCode.Find(MsgTicketId);

			if (BlueprintHandler) BlueprintHandler->ExecuteIfBound(LiveTicket);
			if (CodeHandler) CodeHandler->ExecuteIfBound(LiveTicket);

			InvalidateLiveTicket(LiveTicket);
		}
	}

	// Utility functions
	void InvalidateLiveTicket(FBeamMatchmakingTicket& LiveTicket)
	{
		const FGuid TicketId = LiveTicket.TicketId;

		LiveTicket.TicketId.Invalidate();
		LiveTicket.GamerTagsInTicket.Reset();

		for (FUserSlot SlotsInTicket : LiveTicket.SlotsInTicket)
		{
			if (const auto SlotState = Slots.Find(SlotsInTicket); TicketId == SlotState->InTicket)
			{
				SlotState->InTicket.Invalidate();
			}
		}
		LiveTicket.SlotsInTicket.Reset();

		OnMatchSearching.Remove(TicketId);
		OnMatchSearchingCode.Remove(TicketId);

		OnMatchReady.Remove(TicketId);
		OnMatchReadyCode.Remove(TicketId);

		OnMatchCancelled.Remove(TicketId);
		OnMatchCancelledCode.Remove(TicketId);

		OnMatchTimedOut.Remove(TicketId);
		OnMatchTimedOutCode.Remove(TicketId);
	}
};
