// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Content/BeamContentTypes/BeamGameTypeContent.h"
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
	FGuid TicketId = {};

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	UBeamGameTypeContent* GameType = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	TArray<FUserSlot> SlotsInTicket = {};

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	TArray<FBeamGamerTag> GamerTagsInTicket = {};

	/**
	 * This will be empty until the OnMatchReady callback is invoked.
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	FGuid FoundMatchLobbyId;

	friend bool operator==(const FBeamMatchmakingTicket& Lhs, const FBeamMatchmakingTicket& RHS)
	{
		return Lhs.TicketId == RHS.TicketId;
	}

	friend bool operator==(const FBeamMatchmakingTicket& Lhs, const FGuid& RHS)
	{
		return Lhs.TicketId == RHS;
	}

	friend bool operator!=(const FBeamMatchmakingTicket& Lhs, const FBeamMatchmakingTicket& RHS)
	{
		return !(Lhs == RHS);
	}

	FString ToString() const
	{
		const auto Ticket = TicketId.ToString(EGuidFormats::DigitsWithHyphensLower);
		FString GameTypeId = FString(TEXT("None"));
		if (GameType) GameTypeId = GameType->Id;
		TArray<FString> GamerTags = {};
		for (const auto& InTicket : GamerTagsInTicket) GamerTags.Add(InTicket.AsString);

		TArray<FString> Slots = {};
		for (const auto& InTicket : SlotsInTicket) Slots.Add(InTicket.Name);

		return FString::Printf(TEXT("TICKET=%s, GAME_TYPE=%s, GAMERTAGS=[%s], USER_SLOTS=[%s]"), *Ticket, *GameTypeId, *FString::Join(GamerTags, TEXT(", ")), *FString::Join(Slots, TEXT(", ")));
	}
};


DECLARE_DELEGATE_OneParam(FOnMatchmakingTicketUpdatedCode, const FBeamMatchmakingTicket&)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchmakingTicketUpdated, const FBeamMatchmakingTicket&, Ticket);


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

	/*
	 * For easy binding from blueprints. You are responsible for unregistering these as your objects are destroyed or when the ticket is invalidated.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnMatchmakingTicketUpdated OnMatchSearchStarted;
	FOnMatchmakingTicketUpdatedCode OnMatchSearchStartedCode;

	/*
	 * For easy binding from blueprints. You are responsible for unregistering these as your objects are destroyed or when the ticket is invalidated.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnMatchmakingTicketUpdated OnMatchReady;
	TMultiMap<FGuid, FOnMatchmakingTicketUpdatedCode> OnMatchReadyCode;

	/*
	 * For easy binding from blueprints. You are responsible for unregistering these as your objects are destroyed or when the ticket is invalidated.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnMatchmakingTicketUpdated OnMatchCancelled;
	TMultiMap<FGuid, FOnMatchmakingTicketUpdatedCode> OnMatchCancelledCode;

	/*
	 * For easy binding from blueprints. You are responsible for unregistering these as your objects are destroyed or when the ticket is invalidated.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnMatchmakingTicketUpdated OnMatchTimedOut;
	TMultiMap<FGuid, FOnMatchmakingTicketUpdatedCode> OnMatchTimedOutCode;

	/**
	 * This gets called whenever a ticket is invalidated.
	 * Use this to unbind the BP OnMatch____ you have bound for that ticket.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnMatchmakingTicketUpdated OnMatchTicketInvalidated;
};

DEFINE_BEAM_OPERATION_HOOK_OneParam(FOnBeamableTryJoinMatchmakingQueueParallel, FBeamOperationHandle);
DEFINE_BEAM_OPERATION_HOOK_OneParam(FOnBeamableTryJoinMatchmakingQueueSequentially, FBeamOperationHandle);

/**
 * 
 */
UCLASS(BlueprintType)
class BEAMABLECORERUNTIME_API UBeamMatchmakingSubsystem : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()
	
	const FString StatRegionPingKey = "beam.region.pings";

	friend class UBeamDefaultMatchmakingHooks;
	
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
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamMatchmakingSubsystem* GetSelf(const UObject* CallingContext) { return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamMatchmakingSubsystem>(); }

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	TArray<FBeamMatchmakingTicket> LiveTickets;

	

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Beam")
	TMap<FUserSlot, FBeamMatchmakingState> Slots;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void InitializeWhenUnrealReady_Implementation(FBeamOperationHandle& ResultOp) override;

	virtual void OnPostUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp) override;
	virtual void OnUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp) override;

	//Returns a list of subsystems that this system is depending on
	virtual TArray<TSubclassOf<UBeamRuntimeSubsystem>> GetDependingOnSubsystems() override;

	// LOCAL STATE GETTERS

	
	/**
	 * Checks if the given user slot is in a queue. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AutoCreateRefTerm="Slot", ExpandBoolAsExecs="ReturnValue"))
	bool IsUserSlotInQueue(FUserSlot Slot);

	/**
	 * Gets the TicketId for the given user slot, if any. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AutoCreateRefTerm="Slot", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetTicketId(const FUserSlot& Slot, FGuid& TicketId);

	/**
	 * Gets the ticket data for the given user slot. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AutoCreateRefTerm="Slot", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetTicket(const FUserSlot& Slot, FBeamMatchmakingTicket& Ticket);
	
	/**
	 * Binds a callback to be invoked when a match search starts for the owner player slot.
	 * This callback is triggered when the matchmaking ticket is successfully created and the search begins.
	 * Only one callback can be bound at a time - calling this again will replace the previous callback.
	 * 
	 * @param Callback The delegate to invoke when match search starts, passing the ticket information.
	 */
	void CPP_BindOnMatchSearchStarted(FOnMatchmakingTicketUpdatedCode Callback);
	
	/**
	 * Binds a callback to be invoked when a match is found and ready for the specified ticket.
	 * Multiple callbacks can be bound to the same ticket. The callback receives the ticket with the FoundMatchLobbyId populated.
	 * You are responsible for unbinding these callbacks when your objects are destroyed or when the ticket is invalidated.
	 * 
	 * @param TicketId The matchmaking ticket ID to bind the callback to.
	 * @param Callback The delegate to invoke when a match is ready, passing the updated ticket information.
	 */
	void CPP_BindOnMatchReady(const FGuid& TicketId, FOnMatchmakingTicketUpdatedCode Callback);
	
	/**
	 * Binds a callback to be invoked when a matchmaking ticket is cancelled for the specified ticket.
	 * This can occur when the player explicitly leaves the queue or when the match search is cancelled by the server.
	 * Multiple callbacks can be bound to the same ticket.
	 * You are responsible for unbinding these callbacks when your objects are destroyed or when the ticket is invalidated.
	 * 
	 * @param TicketId The matchmaking ticket ID to bind the callback to.
	 * @param Callback The delegate to invoke when the match is cancelled, passing the ticket information.
	 */
	void CPP_BindOnMatchCancelled(const FGuid& TicketId, FOnMatchmakingTicketUpdatedCode Callback);
	
	/**
	 * Binds a callback to be invoked when a matchmaking ticket times out without finding a match.
	 * Multiple callbacks can be bound to the same ticket.
	 * You are responsible for unbinding these callbacks when your objects are destroyed or when the ticket is invalidated.
	 * 
	 * @param TicketId The matchmaking ticket ID to bind the callback to.
	 * @param Callback The delegate to invoke when the match search times out, passing the ticket information.
	 */
	void CPP_BindOnMatchTimedOut(const FGuid& TicketId, FOnMatchmakingTicketUpdatedCode Callback);
	
	/**
	 * Unbinds all callbacks (OnMatchReady, OnMatchCancelled, OnMatchTimedOut) for the specified ticket.
	 * Call this when you no longer need to receive updates for a particular ticket, such as when your object is being destroyed
	 * or when the ticket has been invalidated. Note that OnMatchSearchStarted is not affected as it's not ticket-specific.
	 * 
	 * @param TicketId The matchmaking ticket ID to unbind all callbacks from.
	 */
	void CPP_UnbindTicketCallbacks(const FGuid& TicketId);
	
	/**
	 * Gets the current matchmaking state for the owner player slot.
	 * 
	 * @param OutState The matchmaking state structure to populate with the current state.
	 * @return True if the state was successfully retrieved, false if no state exists for the owner slot.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AutoCreateRefTerm="Slot", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetMatchmakingState(FBeamMatchmakingState& OutState);


	// OPERATIONS

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
	FBeamOperationHandle TryJoinQueueOperation(FUserSlot UserSlot, UPARAM(meta=(BeamFilter="game_types"))FBeamContentId GameTypeQueue, FOptionalString Team, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc TryJoinQueueOperation 
	 */
	FBeamOperationHandle CPP_TryJoinQueueOperation(FUserSlot UserSlot, const FBeamContentId& GameTypeQueue, FOptionalString Team, FBeamOperationEventHandlerCode OnOperationEvent);

	
	/**
	 * @brief Joins the given game type queue.
	 * The user in the given user slot is added to the queue. If that user is in a party:
	 *   - If its the party leader, the entire party will be added to the queue and other clients will receive notifications for it.
	 *   - If its not the party leader, the operation will fail.
	 *
	 * If the user is already in a queue, it'll fail. If the queue type has more than one team, the provided team must match one of the team names.
	 * If the queue type has a single team (FFA, for example), you can leave the team blank. Queue types with no teams are not valid.
	 *
	 * The array of tags here are added to ULobbyPlayer::Tags when the match gets made.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Matchmaking", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle TryJoinQueueWithTagsOperation(FUserSlot UserSlot, UPARAM(meta=(BeamFilter="game_types"))FBeamContentId GameTypeQueue, FOptionalString Team, TArray<FBeamTag> Tags,
	                                                   FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc TryJoinQueueWithTagsOperation 
	 */
	FBeamOperationHandle CPP_TryJoinQueueWithTagsOperation(FUserSlot UserSlot, const FBeamContentId& GameTypeQueue, FOptionalString Team, TArray<FBeamTag> Tags,
	                                                       FBeamOperationEventHandlerCode OnOperationEvent);

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
	FBeamOperationHandle TryLeaveQueueOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc TryLeaveQueueOperation 
	 */
	FBeamOperationHandle CPP_TryLeaveQueueOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent);

private:
	
	// Operation Implementations
	void TryJoinQueue(FUserSlot Slot, FBeamContentId GameTypeQueue, FOptionalString Team, FOptionalArrayOfBeamTag Tags, FBeamOperationHandle Op);
	void TryLeaveQueue(FUserSlot Slot, FBeamOperationHandle Op);


	// Notification Handlers
	void OnMatchmakingRemoteUpdateReceived(FMatchmakingRemoteUpdateNotificationMessage Msg, FUserSlot UserSlot);
	void OnMatchmakingUpdateReceived(FMatchmakingUpdateNotificationMessage Msg);
	void OnMatchmakingTimeoutReceived(FMatchmakingTimeoutNotificationMessage Msg);

	// Utility Functions
	void InvalidateLiveTicket(FBeamMatchmakingTicket& LiveTicket);

	void CommitRegionPing(FUserSlot UserSlot, TMap<FString, int32> RegionPings, FBeamOperationHandle OperationHandle);
	
	static FString ConvertRegionPingsToJson(TMap<FString, int32> RegionPings);
};
