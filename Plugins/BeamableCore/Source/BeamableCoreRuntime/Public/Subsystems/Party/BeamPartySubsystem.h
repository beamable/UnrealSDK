// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/SubSystems/BeamPartyApi.h"
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
struct BEAMABLECORERUNTIME_API FBeamPartyPlayerState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FBeamGamerTag GameTag;

	FBeamPartyPlayerState() = default;

	explicit FBeamPartyPlayerState(const FBeamGamerTag& GameTag)
		: GameTag(GameTag)
	{
	}
};

USTRUCT(BlueprintType)
struct BEAMABLECORERUNTIME_API FBeamPartyState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGuid PartyId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FBeamGamerTag Leader;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EBeamPartyRestriction Restriction = EBeamPartyRestriction::BEAM_Unrestricted;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxPlayers = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FBeamGamerTag, FBeamPartyPlayerState> PlayerStates;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FBeamGamerTag> InvitedPlayers;
};

USTRUCT(BlueprintType)
struct BEAMABLECORERUNTIME_API FBeamPartyInviteState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGuid PartyId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FBeamGamerTag Sender;

	FBeamPartyInviteState() = default;

	FBeamPartyInviteState(const FGuid& PartyId, const FBeamGamerTag& Sender)
		: PartyId(PartyId),
		  Sender(Sender)
	{
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPartyEventReceived, FGuid, PartyId, FUserSlot, UserSlot);

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPartyEventReceivedCode, FGuid, FUserSlot);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPartyEventReceivedError, FGuid, PartyId, FUserSlot, UserSlot,
                                               EBeamPartyEvent, PartyEvent);

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
	UBeamPartyNotifications* PartyNotifications;

	TMap<FGuid, FBeamPartyState> PartyStates;

	TMap<FUserSlot, TArray<FBeamPartyInviteState>> PartyInvitesState;

	virtual void InitializeWhenUnrealReady_Implementation(FBeamOperationHandle& ResultOp) override;

	virtual void OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser,
	                                           const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp) override;

	virtual void OnPostUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason,
	                                                const FBeamRealmUser& BeamRealmUser,
	                                                FBeamOperationHandle& ResultOp) override;

public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamPartySubsystem* GetSelf(const UObject* CallingContext)
	{
		return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamPartySubsystem>();
	}

	/**
	 * This is called when the Restriction or the MaxPlayer has been changed by the leader
	 * The local state of the PartyStates is updated before this event is called.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnPartyUpdated;

	/**
	 * @copybrief OnPartyUpdated
	 */
	FOnPartyEventReceivedCode OnPartyUpdatedCode;

	/**
	 * This gets called when a new player join to the party.
	 * For the player that joined the party it will only call locally by the JoinPartyOperation.
	 * The local state of the PartyStates is updated before this event is called.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnPlayerJoined;

	/**
	 * @copybrief OnPlayerJoined
	 */
	FOnPartyEventReceivedCode OnPlayerJoinedCode;

	/**
	 * This gets called when a player is kicked from the party by the leader.
	 * The leader gets the OnPlayerKicked event called twice, one for the local state change after the request and another when it gets notified by the backend.
	 * The local state of the PartyStates is updated before this event is called.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnPlayerKicked;

	/**
	 * @copybrief OnPlayerKicked
	 */
	FOnPartyEventReceivedCode OnPlayerKickedCode;

	/**
	 * This gets called when a player left the party.
	 * The local state of the PartyStates is updated before this event is called.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnPlayerLeft;

	/**
	 * @copybrief OnPlayerLeft
	 */
	FOnPartyEventReceivedCode OnPlayerLeftCode;

	/**
	 * This gets called when another player is promoted to be leader.
	 * Could be trigger by the PromotePlayerToLeaderOperation or if the current leader leave the party, than another random person in the party will be promoted to new leader.
	 * The local state of the PartyStates is updated before this event is called.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnPlayerPromotedToLeader;

	/**
	 * @copybrief OnPlayerPromotedToLeader
	 */
	FOnPartyEventReceivedCode OnPlayerPromotedToLeaderCode;

	/**
	 * This gets called when the Player received an invitation to a party.
	 * The local state of the PartyInvitesState is updated before this event is called.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnPlayerInvited;

	/**
	 * @copybrief OnPlayerInvited
	 */
	FOnPartyEventReceivedCode OnPlayerInvitedCode;

	/**
	 * This gets called when an invitation is canceled.
	 * The leader and the player receiver of the invitation can cancel the invitation that will trigger this event, others players aren't allowed to do this.
	 * The local state of the PartyInvitesState is updated before this event is called.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnPlayerInviteCanceled;

	/**
	 * @copybrief OnPlayerInviteCanceled
	 */
	FOnPartyEventReceivedCode OnPlayerInviteCanceledCode;

	/**
	 * This gets called when a party invite expires.
	 * The player that accept the party invite will receive this event locally, that means the Invite Expires will be called because of the acceptance of the invite.
	 * The local state of the PartyInvitesState is updated before this event is called.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceived OnPlayerInviteExpired;

	/**
	 * @copybrief OnPlayerInviteExpired
	 */
	FOnPartyEventReceivedCode OnPlayerInviteExpiredCode;


	/**
	 * This gets called when there's an internal error during the process of received party event.
	 * 
	 * As the party notifications don't receive any payload, after received a party notification we need to update the state of the party.
	 * In the process of update the party state it could happen a internal error, in this case this event will be called.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPartyEventReceivedError OnPartyEventReceivedError;

	/**
	 * @copybrief OnPartyEventReceivedError
	 */
	FOnPartyEventReceivedErrorCode OnPartyEventReceivedErrorCode;

	/**
	 * @brief Check if the user slot is currently on a party.
	 *
	 * This will check in the PartyStates if the UserSlot is currently in any party on the list of states.
	 *
	 * @param UserSlot: The UserSlot used to search in the party state.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool IsPlayerInAParty(FUserSlot UserSlot);

	/**
	 * @brief Check if the user slot is currently on a party.
	 *
	 * This will check in the PartyStates if the UserSlot is currently in any party on the list of states.
	 *
	 * @param PlayerGamerTag: The PlayerGamerTag used to search in the party state.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool IsInAParty(FBeamGamerTag PlayerGamerTag);


	/**
	 * @brief Check if the user slot is the leader of the party.
	 *
	 * This will check in the @link PartyStates @endlink if the UserSlot is the leader of any party in the state.
	 *
	 * @param UserSlot: The UserSlot used to search in the party state.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool IsThePartyLeader(FUserSlot UserSlot);

	/**
	 * @brief Attempts to retrieve the party state for a specific user slot.
	 *
	 * This gets the PartyState from the local state.
	 *
	 * @param UserSlot: The UserSlot that you try to get the party.
	 * @param PartyState: The reference for the out result of the player party state.
	 *
	 * @return Returns False if the user is not in any party.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetUserPartyState(FUserSlot UserSlot, FBeamPartyState& PartyState);

	/**
	 * @brief Returns an iterator list for the Party Player State.
	 *
	 * This gets the PartyState from the local state.
	 *
	 * @return Returns False if the user is not in any party.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool GetUserPartyPlayerStates(FUserSlot UserSlot, FGuid& PartyId, FBeamGamerTag& LeaderGamerTag, EBeamPartyRestriction& PartyRestriction, TArray<FBeamPartyPlayerState>& PlayerStates);

	/**
	 * @brief Attempts to retrieve the party state for a specific player id.
	 *
	 * This gets the PartyState from the local state.
	 *
	 * @param PlayerGamerTag: The player id that you try to get the party.
	 * @param PartyState: The reference for the out result of the player party state.
	 *
	 * @return Returns False if the user is not in any party.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetPlayerPartyState(FBeamGamerTag PlayerGamerTag, FBeamPartyState& PartyState);

	/**
	 * @brief Attempts to retrieve the party state for a specific party id.
	 *
	 * This gets the PartyState from the local state.
	 *
	 * @param PartyId: The party id to get the state.
	 * @param PartyState: The reference for the out result of the player party state.
	 *
	 * @return Returns False if the party don't exists.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetPartyState(FGuid PartyId, FBeamPartyState& PartyState);

	/**
	* @brief Attempts to retrieve the invites state for a specific user slot.
	*
	* This gets the Invites for the UserSlot from the local state.
	*
	* @param UserSlot: The UserSlot that you try to get the current invites.
	* @param Invites: The reference for the out result of the Invites States.
	*
	* @return Returns False if the UserSlot don't have any Invite in the local state.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetUserInvitesState(FUserSlot UserSlot, TArray<FBeamPartyInviteState>& Invites);

	/**
	* @brief The Operation is called for join a party using PartyId.
	*
	* If the player already is in a party and join another party it will trigger an error, for player join another party it's required to leave the current party and join.
	* If you try to join a party that has the restriction InviteOnly without being invited this will return an error.
	* 
	*
	* Updates the local state of: @link PartyStates @endlink 
	* 
	* Triggers the delegate locally : @link OnPlayerJoined @endlink 
	*
	* @param UserSlot: The UserSlot that is calling the join party.
	* @param PartyId: The PartyId that the Player would like to join.
	* @param OnOperationEvent: The call back event that handles the result
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle JoinPartyOperation(FUserSlot UserSlot, FGuid PartyId,
	                                        FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc JoinPartyOperation
	 */
	FBeamOperationHandle CPP_JoinPartyOperation(FUserSlot UserSlot, FGuid PartyId,
	                                            FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	* @brief The Operation is called for join a party using the Player Id.
	*
	* If the player already is in a party and join another party it will trigger an error, for player join another party it's required to leave the current party and join.
	* If you try to join a party that has the restriction InviteOnly without being invited this will return an error.
	*
	* Updates the local state of: @link PartyStates @endlink 
	* 
	* Triggers the delegate locally : @link OnPlayerJoined @endlink 
	*
	* @param UserSlot: The UserSlot that is calling the join party.
	* @param PlayerGamerTag: The Player Id that invited the Player to join.
	* @param OnOperationEvent: The call back event that handles the result
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle JoinPlayerPartyOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	                                              FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc JoinPlayerPartyOperation
	 */
	FBeamOperationHandle CPP_JoinPlayerPartyOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	                                                  FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	* @brief Fetch party invites for a UserSlot and update the local state.
	*
	* It's uses the UserSlot as the target to get all the invites for this specific User and then updates the local state for Invites.
	*
	* @param UserSlot: The target UserSlot that will be used to fetch the invites.
	* @param OnOperationEvent: The callback event that handles the result.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchPartyInvitesOperation(FUserSlot UserSlot,
	                                                FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchPartyInvitesOperation
	 */
	FBeamOperationHandle CPP_FetchPartyInvitesOperation(FUserSlot UserSlot,
	                                                    FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	* @brief Fetch party state and update the local state.
	*
	* Gets the party state of a given PartyId
	* It's NOT required for the UserSlot that calls this Fetch being in the party
	*
	* Update the local state of: @link PartyStates @endlink 
	*
	* @param UserSlot: The UserSlot used for validation to get the Party State.
	* @param PartyId: The PartyId used to get the Party State.
	* @param OnOperationEvent: The callback event that handles the result.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchPartyStateOperation(FUserSlot UserSlot, FGuid PartyId,
	                                              FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchPartyStateOperation
	 */
	FBeamOperationHandle CPP_FetchPartyStateOperation(FUserSlot UserSlot, FGuid PartyId,
	                                                  FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	* @brief Fetch party state for a given UserSlot and update the local state.
	*
	* Update the local state of: @link PartyStates @endlink 
	*
	* @param UserSlot: The UserSlot used for validation to get the Party State.
	* @param OnOperationEvent: The callback event that handles the result.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchPlayerPartyStateOperation(FUserSlot UserSlot,
	                                                    FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchPlayerPartyStateOperation
	 */
	FBeamOperationHandle CPP_FetchPlayerPartyStateOperation(FUserSlot UserSlot,
	                                                        FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	* @brief Creates the Party using the UserSlot who calls it as leader.
	*
	* If the user already in a party and create another it will be removed from the current party and creates the new one normally.
	*
	* Updates the local state of: @link PartyStates @endlink 
	*
	* Triggers the delegate locally : @link OnPlayerJoined @endlink 
	* 
	* @param UserSlot: The UserSlot that will create the party and be the leader.
	* @param Restriction: The type of restriction for this party (	BEAM_Unrestricted, BEAM_InviteOnly ).
	* @param OnOperationEvent: The callback event that handles the result.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle CreatePartyOperation(FUserSlot UserSlot, EBeamPartyRestriction Restriction, int32 MaxPlayers,
	                                          FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc CreatePartyOperation
	 */
	FBeamOperationHandle CPP_CreatePartyOperation(FUserSlot UserSlot, EBeamPartyRestriction Restriction,
	                                              int32 maxPlayers,
	                                              FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 *	@brief Send a party invite to a player.
	 *
	 *	It's possible to send the invite yourself to party.
	 *
	 *	Updates the local state of: @link PartyStates @endlink 
	 *
	 * Triggers the delegate locally : @link OnPlayerInvited @endlink  (only in the case of the invited player exists locally, e.g. being another user slot)
	 *
	 *	@param UserSlot: The leader user slot that will be sending the invite.
	 *	@param PartyId: The PartyId that the player will be invited.
	 *	@param PlayerGamerTag: The BeamGamerTag of the target player to be invited.
	 * @param OnOperationEvent: The callback event that handles the result.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle InvitePlayerToPartyOperation(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag PlayerGamerTag,
	                                                  FBeamOperationEventHandler OnOperationEvent);

	/**
	 *	@copydoc InvitePlayerToPartyOperation
	 */
	FBeamOperationHandle CPP_InvitePlayerToPartyOperation(FUserSlot UserSlot, FGuid PartyId,
	                                                      FBeamGamerTag PlayerGamerTag,
	                                                      FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 *	@brief Send a invite to the party that the player is currently in.
	 *
	 *	It's possible to send the invite yourself to party.
	 *
	 *	Updates the local state of: @link PartyStates @endlink 
	 *
	 * Triggers the delegate locally : @link OnPlayerInvited @endlink  (only in the case of the invited player exists locally, e.g. being another user slot)
	 *
	 *	@param UserSlot: The leader user slot that will be sending the invite.
	 *	@param PlayerGamerTag: The BeamGamerTag of the target player to be invited.
	 * @param OnOperationEvent: The callback event that handles the result.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle InvitePlayerToMyPartyOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	                                                    FBeamOperationEventHandler OnOperationEvent);

	/**
	 *	@copydoc InvitePlayerToMyPartyOperation
	 */
	FBeamOperationHandle CPP_InvitePlayerToMyPartyOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	                                                        FBeamOperationEventHandlerCode OnOperationEvent);


	/**
	 * @brief Decline the invite received to a party.
	 *
	 * The player that has been invited to the party can decline it using this Operation.
	 *
	 * Updates locally the state of: @link PartyInvitesState @endlink .
	 *
	 * Triggers the delegate: @link OnPlayerInviteCanceled @endlink 
	 *
	 * @param UserSlot: The UserSlot that has been invited and will decline.
	 * @param PartyId: The PartyId that the player has been invited.
	 * @param OnOperationEvent: The callback event that handles the result.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle DeclinePartyInviteOperation(FUserSlot UserSlot, FGuid PartyId,
	                                                 FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc DeclinePartyInviteOperation
	 */
	FBeamOperationHandle CPP_DeclinePartyInviteOperation(FUserSlot UserSlot, FGuid PartyId,
	                                                     FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief Decline the invite received to a party.
	 *
	 * The player that has been invited to the party can decline it using this Operation.
	 *
	 * Updates locally the state of: @link PartyInvitesState @endlink .
	 *
	 * Triggers the delegate: @link OnPlayerInviteCanceled @endlink 
	 *
	 * @param UserSlot: The UserSlot that has been invited and will decline.
	 * @param PlayerGamerTag: The player Id that sent the invite.
	 * @param OnOperationEvent: The callback event that handles the result.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle DeclinePlayerPartyInviteOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	                                                       FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc DeclinePlayerPartyInviteOperation
	 */
	FBeamOperationHandle CPP_DeclinePlayerPartyInviteOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	                                                           FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	* @brief Leave the party that the UserSlot are in.
	*
	* This will remove the given UserSlot from the party that has the PartyId, if the UserSlot is not in this party it will trigger an error.
	*
	* Updates locally the state of: @link PartyStates @endlink .
	*
	* Triggers the delegate locally: @link OnPlayerLeft @endlink 
	*
	* @param UserSlot: The target UserSlot that is leaving the party.
	* @param PartyId: The PartyId that the UserSlot is leaving.
	* @param OnOperationEvent: The callback event that handles the result.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle LeavePartyOperation(FUserSlot UserSlot,
	                                         FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc LeavePartyOperation
	 */
	FBeamOperationHandle CPP_LeavePartyOperation(FUserSlot UserSlot,
	                                             FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	* @brief The party leader can kick another player from the party.
	*
	* The party leader can also kick himself from the party or leave as other player
	*
	* Updates the local state of: @link PartyStates @endlink 
	*
	* Triggers the delegate locally: @link OnPlayerKicked @endlink
	*
	* @param UserSlot: The UserSlot that is the leader.
	* @param PartyId: The PartyId to kick the player.
	* @param PlayerGamerTag: The target player BeamGaemTag who will be kicked from the party.
	* @param OnOperationEvent: The callback event that handles the result.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle KickPlayerOperation(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag PlayerGamerTag,
	                                         FBeamOperationEventHandler OnOperationEvent);
	/**
	 * @copydoc KickPlayerOperation
	 */
	FBeamOperationHandle CPP_KickPlayerOperation(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag PlayerGamerTag,
	                                             FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	* @brief The party leader can kick another player from the party.
	*
	* The party leader can also kick himself from the party or leave as other player.
	* It will use the UserSlot to get the party, if the UserSlot isn't in any party will trigger an error.
	*
	* Updates the local state of: @link PartyStates @endlink 
	*
	* Triggers the delegate locally: @link OnPlayerKicked @endlink
	*
	* @param UserSlot: The UserSlot that is the leader.
	* @param PlayerGamerTag: The target player BeamGaemTag who will be kicked from the party.
	* @param OnOperationEvent: The callback event that handles the result.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle KickPlayerFromMyPartyOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	                                                    FBeamOperationEventHandler OnOperationEvent);
	/**
	 * @copydoc KickPlayerFromMyPartyOperation
	 */
	FBeamOperationHandle CPP_KickPlayerFromMyPartyOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	                                                        FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	* @brief Cancel the invite sent to another player.
	*
	* This only can be called by the leader of the party.
	*
	* Update the state of: @link PartyInvitesState @endlink (Only if the target Player exists locally)
	*
	* Triggers the delegate: @link OnPlayerInviteCanceled @endlink
	*
	* @param UserSlot: The leader UserSlot that is canceling the invite.
	* @param PartyId: The PartyId that the player has been invited.
	* @param PlayerGamerTag: The target player to cancel the invite.
	* @param OnOperationEvent: The callback event that handles the result.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle CancelSentPartyInviteOperation(FUserSlot UserSlot, FGuid PartyId,
	                                                    FBeamGamerTag PlayerGamerTag,
	                                                    FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc CancelSentPartyInviteOperation
	 */
	FBeamOperationHandle CPP_CancelSentPartyInviteOperation(FUserSlot UserSlot, FGuid PartyId,
	                                                        FBeamGamerTag PlayerGamerTag,
	                                                        FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	* @brief Cancel the invite sent to another player using the user slot.
	*
	* This only can be called by the leader of the party.
	* Is required to the player to be party of a party.
	*
	* Update the state of: @link PartyInvitesState @endlink (Only if the target Player exists locally)
	*
	* Triggers the delegate: @link OnPlayerInviteCanceled @endlink
	*
	* @param UserSlot: The leader UserSlot that is canceling the invite.
	* @param PlayerGamerTag: The target player to cancel the invite.
	* @param OnOperationEvent: The callback event that handles the result.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle CancelPlayerPartyInviteOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	                                                      FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc CancelPlayerPartyInviteOperation
	 */
	FBeamOperationHandle CPP_CancelPlayerPartyInviteOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	                                                          FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	* @brief The party leader can promote a player to be the new leader.
	*
	* It only can be called by the party leader.
	*
	* Update locally the state of: @link PartyStates @endlink 
	*
	* Triggers the delegate: @link OnPlayerPromotedToLeader @endlink 
	*
	* @param UserSlot: The leader UserSlot that will be used to validate the operation.
	* @param PartyId: The PartyId that will happen the promotion.
	* @param PlayerGamerTag: The target player that will be promoted to leader of the party.
	* @param OnOperationEvent: The callback event that handles the result.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle PromotePlayerToLeaderOperation(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag PlayerGamerTag,
	                                                    FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc PromotePlayerToLeaderOperation
	 */
	FBeamOperationHandle CPP_PromotePlayerToLeaderOperation(FUserSlot UserSlot, FGuid PartyId,
	                                                        FBeamGamerTag PlayerGamerTag,
	                                                        FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	* @brief The party leader can promote a player to be the new leader.
	*
	* It only can be called by the party leader.
	* It will use the party leader UserSlot to get the party, if the UserSlot isn't in any party, it will trigger a error.
	*
	* Update locally the state of: @link PartyStates @endlink 
	*
	* Triggers the delegate: @link OnPlayerPromotedToLeader @endlink 
	*
	* @param UserSlot: The leader UserSlot that will be used to validate the operation.
	* @param PlayerGamerTag: The target player that will be promoted to leader of the party.
	* @param OnOperationEvent: The callback event that handles the result.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle PromotePlayerToMyPartyLeaderOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	                                                           FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc PromotePlayerToMyPartyLeaderOperation
	 */
	FBeamOperationHandle CPP_PromotePlayerToMyPartyLeaderOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	                                                               FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief The party leader can update the party meta-data (Restriction and MaxPlayers) for the party after create it
	 *
	 * Update the local state of: @link PartyStates @endlink 
	 *
	 * Triggers the delegate: @link OnPartyUpdated @endlink
	 *
	 * @param UserSlot: The leader UserSlot that will be used to do the validation.
	 * @param PartyId: The PartyId that will be updated.
	 * @param Restriction: The new Restriction (If you don't want to update the restriction just pass the old one from the current state).
	 * @param MaxPlayers: The new MaxPlayer (If you don't want to update the MaxPlayer just pass 0 in the value).
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle UpdatePartyMetaOperation(FUserSlot UserSlot, FGuid PartyId, EBeamPartyRestriction Restriction,
	                                              FOptionalInt32 MaxPlayers,
	                                              FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc UpdatePartyMetaOperation
	 */
	FBeamOperationHandle CPP_UpdatePartyMetaOperation(FUserSlot UserSlot, FGuid PartyId,
	                                                  EBeamPartyRestriction Restriction,
	                                                  FOptionalInt32 MaxPlayers,
	                                                  FBeamOperationEventHandlerCode OnOperationEvent);
	/**
	 * @brief The party leader can update the party meta-data (Restriction and MaxPlayers) for the party after create it.
	 *
	 * The UserSlot will be used to get the party, guarantee that it is in a party before call it.
	 *
	 * Update the local state of: @link PartyStates @endlink 
	 *
	 * Triggers the delegate: @link OnPartyUpdated @endlink
	 *
	 * @param UserSlot: The leader UserSlot that will be used to do the validation.
	 * @param Restriction: The new Restriction (If you don't want to update the restriction just pass the old one from the current state).
	 * @param MaxPlayers: The new MaxPlayer (If you don't want to update the MaxPlayer just pass 0 in the value).
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle UpdateMyPartyMetaOperation(FUserSlot UserSlot, EBeamPartyRestriction Restriction,
	                                                FOptionalInt32 MaxPlayers,
	                                                FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc UpdateMyPartyMetaOperation
	 */
	FBeamOperationHandle CPP_UpdateMyPartyMetaOperation(FUserSlot UserSlot,
	                                                    EBeamPartyRestriction Restriction,
	                                                    FOptionalInt32 MaxPlayers,
	                                                    FBeamOperationEventHandlerCode OnOperationEvent);

private:
	void FetchPartyState(FUserSlot UserSlot, FGuid PartyId, FBeamOperationHandle Op);

	void FetchPlayerPartyState(FUserSlot UserSlot, FBeamOperationHandle Op);

	void FetchPartyInvites(FUserSlot UserSlot, FBeamOperationHandle Op);

	bool CreateParty(FUserSlot UserSlot, EBeamPartyRestriction Restriction, int32 maxPlayers, FBeamOperationHandle Op);

	void JoinParty(FUserSlot UserSlot, FGuid PartyId, FBeamOperationHandle Op);

	void JoinPlayerParty(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag, FBeamOperationHandle Op);

	void InvitePlayerToParty(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag PlayerGamerTag, FBeamOperationHandle Op);

	void InvitePlayerToMyParty(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag, FBeamOperationHandle Op);

	void DeclinePartyInvite(FUserSlot UserSlot, FGuid PartyId, FBeamOperationHandle Op);

	void DeclinePlayerInvite(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag, FBeamOperationHandle Op);

	void LeaveParty(FUserSlot UserSlot, FBeamOperationHandle Op);

	// Leader - Only can be called by the leader of the party.

	void UpdatePartyMeta(FUserSlot UserSlot, FGuid PartyId, EBeamPartyRestriction Restriction,
	                     FOptionalInt32 MaxPlayers,
	                     FBeamOperationHandle Op);

	void UpdateMyPartyMeta(FUserSlot UserSlot, EBeamPartyRestriction Restriction, FOptionalInt32 MaxPlayers,
	                       FBeamOperationHandle Op);

	void KickPlayer(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag PlayerGamerTag, FBeamOperationHandle Op);

	void KickPlayerFromMyParty(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag, FBeamOperationHandle Op);

	void PromotePlayerToLeader(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag PlayerGamerTag,
	                           FBeamOperationHandle Op);

	void PromotePlayerAsMyPartyLeader(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag, FBeamOperationHandle Op);

	void CancelSentPartyInvite(FUserSlot UserSlot, FGuid PartyId, FBeamGamerTag PlayerGamerTag,
	                           FBeamOperationHandle Op);

	void CancelPlayerPartyInvite(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag, FBeamOperationHandle Op);

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
