// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/SubSystems/BeamPartyApi.h"
#include "AutoGen/SubSystems/BeamPlayerPartyApi.h"
#include "BeamNotifications/SubSystems/BeamPartyNotifications.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "BeamPartySubsystem.generated.h"

UENUM(BlueprintType, Category="Beam")
enum class EBeamPartyRestriction : uint8
{
	BEAM_Unrestricted,
	BEAM_InviteOnly,
};

USTRUCT(BlueprintType)
struct FBeamPartyPlayerState
{
	GENERATED_BODY()

	FBeamGamerTag GameTag;
};

USTRUCT(BlueprintType)
struct FBeamPartyState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGuid PartyId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FBeamGamerTag Leader;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EBeamPartyRestriction Restriction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxPlayers;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FBeamGamerTag, FBeamPartyPlayerState> PlayerStates;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FBeamGamerTag> InvitedPlayers;
};

USTRUCT(BlueprintType)
struct FBeamPartyInviteState
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGuid PartyId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FBeamGamerTag Sender;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPartyEventReceived, FGuid, PartyId, FUserSlot, UserSlot);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPartyEventReceivedCode, FGuid, FUserSlot);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPartyEventReceivedError, FGuid, PartyId, FUserSlot, UserSlot, EBeamPartyEvent, PartyEvent);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnPartyEventReceivedErrorCode, FGuid, FUserSlot, EBeamPartyEvent);

/**
 * 
 */
UCLASS()
class BEAMABLECORERUNTIME_API UBeamPartySubsystem : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	UBeamPartyApi* PartyApi;

	UPROPERTY()
	UBeamPlayerPartyApi* PlayerPartyApi;
	
	UPROPERTY()
	UBeamPartyNotifications* PartyNotifications;

	TMap<FGuid, FBeamPartyState> PartyStates;
	
	TMap<FUserSlot, TArray<FBeamPartyInviteState>> PartyInvitesState;

	virtual void InitializeWhenUnrealReady_Implementation(FBeamOperationHandle& ResultOp) override;

	virtual void OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp) override;

	virtual void OnPostUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp) override;

public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamPartySubsystem* GetSelf(const UObject* CallingContext) { return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamPartySubsystem>(); }

	/**
	 * This gets called when a party have any changes on this
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnPartyUpdated;

	/**
	 * @copybrief OnPartyUpdated
	 */
	FOnPartyEventReceivedCode OnPartyUpdatedCode;

	/**
	 * This gets called when the player received an invitation to join a party
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnPlayerInvited;

	/**
	 * @copybrief OnPlayerInvited
	 */
	FOnPartyEventReceivedCode OnPlayerInvitedCode;
	
	/**
	 * This gets called when a new player join to the party
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnPlayerJoined;

	/**
	 * @copybrief OnPlayerJoined
	 */
	FOnPartyEventReceivedCode OnPlayerJoinedCode;
	
	/**
	 * This gets called when a player is kicked from the party by the leader 
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnPlayerKicked;

	/**
	 * @copybrief OnPlayerKicked
	 */
	FOnPartyEventReceivedCode OnPlayerKickedCode;
	
	/**
	 * This gets called when a player left the party 
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnPlayerLeft;

	/**
	 * @copybrief OnPlayerLeft
	 */
	FOnPartyEventReceivedCode OnPlayerLeftCode;

	/**
	 * This gets called when a invitation is canceled - It could be trigger by the leader or the even by the receiver of the invitation
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnPlayerInviteCanceled;

	/**
	 * @copybrief OnPlayerInviteCanceled
	 */
	FOnPartyEventReceivedCode OnPlayerInviteCanceledCode;
	
	/**
	 * This gets called when an invite expires
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnPlayerInviteExpired;

	/**
	 * @copybrief OnPlayerInviteExpired
	 */
	FOnPartyEventReceivedCode OnPlayerInviteExpiredCode;
	
	/**
	 * This gets called when another player is promoted to be leader - This could happen if the leader leaves the party or if the leader promote another player to be the new leader
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnPlayerPromotedToLeader;

	/**
	 * @copybrief OnPlayerPromotedToLeader
	 */
	FOnPartyEventReceivedCode OnPlayerPromotedToLeaderCode;

	/**
	 * This gets called when there's an internal error during the process of received party event.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceivedError OnPartyEventReceivedError;

	/**
	 * @copybrief OnPartyEventReceivedError
	 */
	FOnPartyEventReceivedErrorCode OnPartyEventReceivedErrorCode;
	
	/**
	 * @brief Attempts to retrieve the party state for a specific user slot. Returns false if the user is not in any party.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetUserPartyState(FUserSlot UserSlot, FBeamPartyState& PartyState);

	/**
	 * @brief Attempts to retrieve the invites state for a specific user slot. Returns false if the user is not in any party.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetUserInvitesState(FUserSlot UserSlot, TArray<FBeamPartyInviteState>& Invites);
	
	/**
	 * @brief Operation to join a party using the PartyId. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle JoinPartyOperation(FUserSlot UserSlot, FGuid PartyId, FBeamOperationEventHandler OperationEventHandler);

	/**
	 * @copydoc JoinPartyOperation
	 */
	FBeamOperationHandle CPP_JoinPartyOperation(FUserSlot UserSlot, FGuid PartyId, FBeamOperationEventHandlerCode OperationEventHandler);

	/**
	* @brief Fetch party invites for a specific user
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchPartyInvitesOperation(FUserSlot UserSlot, FBeamOperationEventHandler OperationEventHandler);
	
	/**
	 * @copydoc FetchPartyInvitesOperation
	 */
	FBeamOperationHandle CPP_FetchPartyInvitesOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OperationEventHandler);
	
	/**
	 * @brief Get the party state data for a given party id
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchPartyStateOperation(FUserSlot UserSlot, FGuid PartyId, FBeamOperationEventHandler OperationEventHandler);

	/**
	 * @copydoc FetchPartyStateOperation
	 */
	FBeamOperationHandle CPP_FetchPartyStateOperation(FUserSlot UserSlot, FGuid PartyId, FBeamOperationEventHandlerCode OperationEventHandler);
	
	/**
	* @brief Create the party with the user who calls it as leader.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle CreatePartyOperation(FUserSlot UserSlot, EBeamPartyRestriction Restriction, int32 maxPlayers, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc CreatePartyOperation
	 */
	FBeamOperationHandle CPP_CreatePartyOperation(FUserSlot UserSlot, EBeamPartyRestriction Restriction, int32 maxPlayers, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 *	@brief Invite another player to join the current party.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle InvitePlayerToPartyOperation(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player, FBeamOperationEventHandler OperationEventHandler);

	/**
	 *	@copydoc InvitePlayerToPartyOperation
	 */
	FBeamOperationHandle CPP_InvitePlayerToPartyOperation(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player, FBeamOperationEventHandlerCode OperationEventHandler);

	/**
	 * @brief Cancel the party invite sent to another player.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle DeletePlayerPartyInviteOperation(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player, FBeamOperationEventHandler OperationEventHandler);

	/**
	 * @copydoc DeletePlayerPartyInviteOperation
	 */
	FBeamOperationHandle CPP_DeletePlayerPartyInviteOperation(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player, FBeamOperationEventHandlerCode OperationEventHandler);

	/**
	* @brief Leave the current party the player are in.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle LeavePartyOperation(FUserSlot UserSlot, FGuid PartyId, FBeamOperationEventHandler OperationEventHandler);

	/**
	 * @copydoc LeavePartyOperation
	 */
	FBeamOperationHandle CPP_LeavePartyOperation(FUserSlot UserSlot, FGuid PartyId, FBeamOperationEventHandlerCode OperationEventHandler);

	/**
	* @brief The party leader can kick another player from the party.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle KickPlayerOperation(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player, FBeamOperationEventHandler OperationEventHandler);

	/**
	 * @copydoc KickPlayerOperation
	 */
	FBeamOperationHandle CPP_KickPlayerOperation(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player, FBeamOperationEventHandlerCode OperationEventHandler);

	/**
	* @brief The party leader can promote a player to be the new leader.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle PromotePlayerToLeaderOperation(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player, FBeamOperationEventHandler OperationEventHandler);

	/**
	 * @copydoc PromotePlayerToLeaderOperation
	 */
	FBeamOperationHandle CPP_PromotePlayerToLeaderOperation(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player, FBeamOperationEventHandlerCode OperationEventHandler);

	/**
	 * @brief The party leader can update the party meta-data (Restriction and MaxPlayers) for the party after create it.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle UpdatePartyOperation(FUserSlot UserSlot, FGuid PartyId, EBeamPartyRestriction Restriction, FOptionalInt32 MaxPlayers, FBeamOperationEventHandler OperationEventHandler);

	/**
	 * @copydoc UpdatePartyOperation
	 */
	FBeamOperationHandle CPP_UpdatePartyOperation(FUserSlot UserSlot, FGuid PartyId, EBeamPartyRestriction Restriction, FOptionalInt32 MaxPlayers, FBeamOperationEventHandlerCode OperationEventHandler);


private:

	bool TryGetPlayerParty(FUserSlot UserSlot, FBeamPartyState& PartyState);
	
	bool TryGetAvailableInvites(FUserSlot UserSlot, TArray<FBeamPartyInviteState>& Invites);

	void FetchPartyState(FUserSlot UserSlot, FGuid PartyId, FBeamOperationHandle Op);

	void FetchPartyInvites(FUserSlot UserSlot, FBeamOperationHandle Op);
	
	bool CreateParty(FUserSlot UserSlot, EBeamPartyRestriction Restriction, int32 maxPlayers, FBeamOperationHandle Op);
	
	void JoinParty(FUserSlot UserSlot, FGuid PartyId, FBeamOperationHandle Op);
	
	void InvitePlayerToParty(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player, FBeamOperationHandle Op);

	void DeletePlayerPartyInvite(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player, FBeamOperationHandle Op);
	
	void LeaveParty(FUserSlot UserSlot, FGuid PartyId, FBeamOperationHandle Op);
	
	// Leader - Only can be called by the leader of the party.

	void UpdateParty(FUserSlot UserSlot, FGuid PartyId, EBeamPartyRestriction Restriction, FOptionalInt32 MaxPlayers, FBeamOperationHandle Op);
	
	void KickPlayer(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player, FBeamOperationHandle Op);

	void PromotePlayerToLeader(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag Player, FBeamOperationHandle Op);

	// Notification Hooks
	UFUNCTION()
	void PartyUpdatedMessageHandler(FPartyRefreshNotificationMessage RefreshNotificationMessage, FUserSlot UserSlot);

	void HandlePartyEventReceivedUpdatePartyState(FGuid PartyId, FUserSlot UserSlot, EBeamPartyEvent PartyEvent);

	void HandlePartyEventReceivedUpdateInvitesState(FGuid PartyId, FUserSlot UserSlot, EBeamPartyEvent PartyEvent);

	void InvokePartyEventUpdate(FUserSlot UserSlot, FGuid PartyId, EBeamPartyEvent PartyEvent);
	
	// Utilities

	FBeamPartyState MakePartyState(UParty* Party);

	static FString GetRestrictionString(EBeamPartyRestriction RestrictionType);
	EBeamPartyRestriction GetRestrictionType(FString RestrictionName);
};
