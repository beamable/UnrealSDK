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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerJoinedEventReceived, FGuid, PartyId, FUserSlot, UserSlot);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerJoinedEventReceivedCode, FGuid, FUserSlot);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerLeftEventReceived, FGuid, PartyId, FUserSlot, UserSlot);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerLeftEventReceivedCode, FGuid, FUserSlot);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerInvitedEventReceived, FGuid, PartyId, FUserSlot, UserSlot);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerInvitedEventReceivedCode, FGuid, FUserSlot);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPartyUpdatedEventReceived, FGuid, PartyId, FUserSlot, UserSlot);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPartyUpdatedEventReceivedCode, FGuid, FUserSlot);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerPromotedToLeaderEventReceived, FGuid, PartyId, FUserSlot, UserSlot);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerPromotedToLeaderEventReceivedCode, FGuid, FUserSlot);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerKickedEventReceived, FGuid, PartyId, FUserSlot, UserSlot);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerKickedEventReceivedCode, FGuid, FUserSlot);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerInviteCanceledEventReceived, FGuid, PartyId, FUserSlot, UserSlot);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerInviteCanceledEventReceivedCode, FGuid, FUserSlot);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerInviteExpiredEventReceived, FGuid, PartyId, FUserSlot, UserSlot);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerInviteExpiredEventReceivedCode, FGuid, FUserSlot);

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
	FOnPartyUpdatedEventReceived OnPartyUpdated;

	/**
	 * @copybrief OnPartyUpdated
	 */
	FOnPartyUpdatedEventReceivedCode OnPartyUpdatedCode;

	/**
	 * This gets called when the player received an invitation to join a party
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPlayerInvitedEventReceived OnPlayerInvited;

	/**
	 * @copybrief OnPlayerInvited
	 */
	FOnPlayerInvitedEventReceivedCode OnPlayerInvitedCode;
	
	/**
	 * This gets called when a new player join to the party
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPlayerJoinedEventReceived OnPlayerJoined;

	/**
	 * @copybrief OnPlayerJoined
	 */
	FOnPlayerJoinedEventReceivedCode OnPlayerJoinedCode;
	
	/**
	 * This gets called when a player is kicked from the party by the leader 
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPlayerKickedEventReceived OnPlayerKicked;

	/**
	 * @copybrief OnPlayerKicked
	 */
	FOnPlayerKickedEventReceivedCode OnPlayerKickedCode;
	
	/**
	 * This gets called when a player left the party 
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPlayerLeftEventReceived OnPlayerLeft;

	/**
	 * @copybrief OnPlayerLeft
	 */
	FOnPlayerLeftEventReceivedCode OnPlayerLeftCode;

	/**
	 * This gets called when a invitation is canceled - It could be trigger by the leader or the even by the receiver of the invitation
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPlayerInviteCanceledEventReceived OnPlayerInviteCanceled;

	/**
	 * @copybrief OnPlayerInviteCanceled
	 */
	FOnPlayerInviteCanceledEventReceivedCode OnPlayerInviteCanceledCode;
	
	/**
	 * This gets called when an invite expires
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPlayerInviteExpiredEventReceived OnPlayerInviteExpired;

	/**
	 * @copybrief OnPlayerInviteExpired
	 */
	FOnPlayerInviteExpiredEventReceivedCode OnPlayerInviteExpiredCode;
	
	/**
	 * This gets called when another player is promoted to be leader - This could happen if the leader leaves the party or if the leader promote another player to be the new leader
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPlayerPromotedToLeaderEventReceived OnPlayerPromotedToLeader;

	/**
	 * @copybrief OnPlayerPromotedToLeader
	 */
	FOnPlayerPromotedToLeaderEventReceivedCode OnPlayerPromotedToLeaderCode;
	
	/**
	 * @brief Attempts to retrieve the party state for a specific user slot. Returns false if the user is not in any party.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	bool TryGetUserPartyState(FUserSlot User, FBeamPartyState& PartyState);

	/**
	 * @brief Operation to join a party using the PartyId. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle JoinPartyOperation(FUserSlot User, FGuid PartyId, FBeamOperationEventHandler OperationEventHandler);

	/**
	 * @copydoc JoinPartyOperation
	 */
	FBeamOperationHandle CPP_JoinPartyOperation(FUserSlot User, FGuid PartyId, FBeamOperationEventHandlerCode OperationEventHandler);

	/**
	* @brief Fetch party invites for a specific user
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchPartyInvitesOperation(FUserSlot User, FBeamOperationEventHandler OperationEventHandler);
	
	/**
	 * @copydoc FetchPartyInvitesOperation
	 */
	FBeamOperationHandle CPP_FetchPartyInvitesOperation(FUserSlot User, FBeamOperationEventHandlerCode OperationEventHandler);
	
	/**
	 * @brief Get the party state data for a given party id
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchPartyStateOperation(FUserSlot User, FGuid PartyId, FBeamOperationEventHandler OperationEventHandler);

	/**
	 * @copydoc FetchPartyStateOperation
	 */
	FBeamOperationHandle CPP_FetchPartyStateOperation(FUserSlot User, FGuid PartyId, FBeamOperationEventHandlerCode OperationEventHandler);
	
	/**
	* @brief Create the party with the user who calls it as leader.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle CreatePartyOperation(FUserSlot User, EBeamPartyRestriction Restriction, int32 maxPlayers, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc CreatePartyOperation
	 */
	FBeamOperationHandle CPP_CreatePartyOperation(FUserSlot User, EBeamPartyRestriction Restriction, int32 maxPlayers, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 *	@brief Invite another player to join the current party.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle InvitePlayerToPartyOperation(FUserSlot User, FGuid PartyId, FBeamGamerTag Player, FBeamOperationEventHandler OperationEventHandler);

	/**
	 *	@copydoc InvitePlayerToPartyOperation
	 */
	FBeamOperationHandle CPP_InvitePlayerToPartyOperation(FUserSlot User, FGuid PartyId, FBeamGamerTag Player, FBeamOperationEventHandlerCode OperationEventHandler);

	/**
	 * @brief Cancel the party invite sent to another player.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle DeletePlayerPartyInviteOperation(FUserSlot User, FGuid PartyId, FBeamGamerTag Player, FBeamOperationEventHandler OperationEventHandler);

	/**
	 * @copydoc DeletePlayerPartyInviteOperation
	 */
	FBeamOperationHandle CPP_DeletePlayerPartyInviteOperation(FUserSlot User, FGuid PartyId, FBeamGamerTag Player, FBeamOperationEventHandlerCode OperationEventHandler);

	/**
	* @brief Leave the current party the player are in.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle LeavePartyOperation(FUserSlot User, FGuid PartyId, FBeamOperationEventHandler OperationEventHandler);

	/**
	 * @copydoc LeavePartyOperation
	 */
	FBeamOperationHandle CPP_LeavePartyOperation(FUserSlot User, FGuid PartyId, FBeamOperationEventHandlerCode OperationEventHandler);

	/**
	* @brief The party leader can kick another player from the party.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle KickPlayerOperation(FUserSlot User, FGuid PartyId, FBeamGamerTag Player, FBeamOperationEventHandler OperationEventHandler);

	/**
	 * @copydoc KickPlayerOperation
	 */
	FBeamOperationHandle CPP_KickPlayerOperation(FUserSlot User, FGuid PartyId, FBeamGamerTag Player, FBeamOperationEventHandlerCode OperationEventHandler);

	/**
	* @brief The party leader can promote a player to be the new leader.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle PromotePlayerToLeaderOperation(FUserSlot User, FGuid PartyId, FBeamGamerTag Player, FBeamOperationEventHandler OperationEventHandler);

	/**
	 * @copydoc PromotePlayerToLeaderOperation
	 */
	FBeamOperationHandle CPP_PromotePlayerToLeaderOperation(FUserSlot User, FGuid PartyId, FBeamGamerTag Player, FBeamOperationEventHandlerCode OperationEventHandler);

	/**
	 * @brief The party leader can update the party meta-data (Restriction and MaxPlayers) for the party after create it.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle UpdatePartyOperation(FUserSlot User, FGuid PartyId, EBeamPartyRestriction Restriction, FOptionalInt32 MaxPlayers, FBeamOperationEventHandler OperationEventHandler);

	/**
	 * @copydoc UpdatePartyOperation
	 */
	FBeamOperationHandle CPP_UpdatePartyOperation(FUserSlot User, FGuid PartyId, EBeamPartyRestriction Restriction, FOptionalInt32 MaxPlayers, FBeamOperationEventHandlerCode OperationEventHandler);

private:

	bool TryGetPlayerParty(FUserSlot User, FBeamPartyState& PartyState);
	
	bool TryGetAvailableInvites(FUserSlot User, TArray<FBeamPartyInviteState>& Invites);

	void FetchPartyState(FUserSlot User, FGuid PartyId, FBeamOperationHandle Op);

	void FetchPartyInvites(FUserSlot User, FBeamOperationHandle Op);
	
	bool CreateParty(FUserSlot User, EBeamPartyRestriction Restriction, int32 maxPlayers, FBeamOperationHandle Op);
	
	void JoinParty(FUserSlot User, FGuid PartyId, FBeamOperationHandle Op);
	
	void InvitePlayerToParty(FUserSlot User, FGuid PartyId, FBeamGamerTag Player, FBeamOperationHandle Op);

	void DeletePlayerPartyInvite(FUserSlot User, FGuid PartyId, FBeamGamerTag Player, FBeamOperationHandle Op);
	
	void LeaveParty(FUserSlot User, FGuid PartyId, FBeamOperationHandle Op);
	
	// Leader - Only can be called by the leader of the party.

	void UpdateParty(FUserSlot User, FGuid PartyId, EBeamPartyRestriction Restriction, FOptionalInt32 MaxPlayers, FBeamOperationHandle Op);
	
	void KickPlayer(FUserSlot User, FGuid PartyId, FBeamGamerTag Player, FBeamOperationHandle Op);

	void PromotePlayerToLeader(FUserSlot User, FGuid PartyId, FBeamGamerTag Player, FBeamOperationHandle Op);

	// Notification Hooks
	UFUNCTION()
	void OnPartyUpdatedHandler(FPartyRefreshNotificationMessage Msg, FUserSlot User);

	void OnPlayerJoinedEventReceived(FGuid PartyId, FUserSlot User);
	void OnPlayerLeftEventReceived(FGuid PartyId, FUserSlot User);
	void OnPlayerInvitedEventReceived(FGuid PartyId, FUserSlot User);
	void OnPartyUpdatedEventReceived(FGuid PartyId, FUserSlot User);
	void OnPlayerPromotedToLeaderEventReceived(FGuid PartyId, FUserSlot User);
	void OnPlayerKickedEventReceived(FGuid PartyId, FUserSlot User);
	void OnPlayerInviteCanceledEventReceived(FGuid PartyId, FUserSlot User);
	void OnPlayerInviteExpiredEventReceived(FGuid PartyId, FUserSlot User);
	
	// Utilities

	FBeamPartyState MakePartyState(UParty* Party);

	static FString GetRestrictionString(EBeamPartyRestriction RestrictionType);
	EBeamPartyRestriction GetRestrictionType(FString RestrictionName);
};
