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

	FGuid PartyId;

	FBeamGamerTag Leader;
	
	int32 MaxPlayers;
	
	TMap<FBeamGamerTag, FBeamPartyPlayerState> PlayerStates;

	
};

USTRUCT(BlueprintType)
struct FBeamPartyInviteState
{
	GENERATED_BODY()

	FGuid PartyId;

	FBeamGamerTag Sender;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPlayerJoinedEventReceived, FGuid, PartyId);
DECLARE_DELEGATE_OneParam(FOnPlayerJoinedEventReceivedCode, FGuid);

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPlayerLeftEventReceived, FGuid, PartyId);
DECLARE_DELEGATE_OneParam(FOnPlayerLeftEventReceivedCode, FGuid);


DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPlayerInvitedEventReceived, FGuid, PartyId);
DECLARE_DELEGATE_OneParam(FOnPlayerInvitedEventReceivedCode, FGuid);

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPartyUpdatedEventReceived, FGuid, PartyId);
DECLARE_DELEGATE_OneParam(FOnPartyUpdatedEventReceivedCode, FGuid);


DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPlayerPromotedToLeaderEventReceived, FGuid, PartyId);
DECLARE_DELEGATE_OneParam(FOnPlayerPromotedToLeaderEventReceivedCode, FGuid);

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPlayerKickedEventReceived, FGuid, PartyId);
DECLARE_DELEGATE_OneParam(FOnPlayerKickedEventReceivedCode, FGuid);

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPlayerInviteCanceledEventReceived, FGuid, PartyId);
DECLARE_DELEGATE_OneParam(FOnPlayerInviteCanceledEventReceivedCode, FGuid);

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPlayerInviteExpiredEventReceived, FGuid, PartyId);
DECLARE_DELEGATE_OneParam(FOnPlayerInviteExpiredEventReceivedCode, FGuid);

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
	
	TArray<FBeamPartyInviteState> PartyInvites;

	virtual void InitializeWhenUnrealReady_Implementation(FBeamOperationHandle& ResultOp) override;

	virtual void OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp) override;

	virtual void OnPostUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp) override;

public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamPartySubsystem* GetSelf(const UObject* CallingContext) { return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamPartySubsystem>(); }

	/**
	 * @brief Try to get Party State locally for a specific user slot.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Party", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	bool TryGetUserPartyState(const FUserSlot& User, FBeamPartyState& PlayerState);

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
private:
	
	
	bool TryAcceptPartyInvite(FUserSlot User, FBeamOperationHandle Op);

	void FetchPartyState(FUserSlot User, FGuid PartyId, FBeamOperationHandle Op);

	void FetchPartyInvites(FUserSlot User, FBeamOperationHandle Op);
	
	bool CreateParty(FUserSlot User, EBeamPartyRestriction Restriction, int32 maxPlayers, FBeamOperationHandle Op);

	void JoinParty(FUserSlot User, FGuid PartyId, FBeamOperationHandle Op);
	
	void InvitePlayerToParty(FUserSlot User, FGuid PartyId, FBeamGamerTag Player, FBeamOperationHandle Op);

	void DeletePlayerPartyInvite(FUserSlot User, FGuid PartyId, FBeamGamerTag Player, FBeamOperationHandle Op);
	
	void LeaveParty(FUserSlot User, FGuid PartyId, FBeamOperationHandle Op);
	
	// Leader - Only can be called by the leader of the party.

	void KickPlayer(FUserSlot User, FGuid PartyId, FBeamGamerTag Player, FBeamOperationHandle Op);

	void PromotePlayerToLeader(FUserSlot User, FGuid PartyId, FBeamGamerTag Player, FBeamOperationHandle Op);

	// Notification Hooks
	UFUNCTION()
	void OnPartyUpdatedHandler(FPartyRefreshNotificationMessage Msg, FUserSlot Slot);

	void OnPlayerJoinedEventReceived(FGuid PartyId);
	void OnPlayerLeftEventReceived(FGuid PartyId);
	void OnPlayerInvitedEventReceived(FGuid PartyId);
	void OnPartyUpdatedEventReceived(FGuid PartyId);
	void OnPlayerPromotedToLeaderEventReceived(FGuid PartyId);
	void OnPlayerKickedEventReceived(FGuid PartyId);
	void OnPlayerInviteCanceledEventReceived(FGuid PartyId);
	void OnPlayerInviteExpiredEventReceived(FGuid PartyId);
	
	// Utilities

	bool TryGetPlayerParty(FUserSlot User, FGuid& PartyId);

	FBeamPartyState MakePartyState(UParty* Party);

	static FString GetRestrictionString(EBeamPartyRestriction RestrictionType);
};
