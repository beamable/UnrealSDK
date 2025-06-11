// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/SubSystems/BeamMailApi.h"
#include "AutoGen/SubSystems/BeamPresenceApi.h"
#include "AutoGen/SubSystems/BeamFriendsApi.h"
#include "BeamNotifications/SubSystems/BeamMailNotifications.h"
#include "BeamNotifications/SubSystems/BeamSocialNotifications.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "BeamFriendsSubsystem.generated.h"


USTRUCT(BlueprintType)
struct BEAMABLECORERUNTIME_API FBeamFriendPresenceStatus
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Online = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime LastOnline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBeamPresenceStatus Status = EBeamPresenceStatus::BEAM_Invisible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	FBeamFriendPresenceStatus() = default;

	FBeamFriendPresenceStatus(bool bOnline, const FDateTime& LastOnline, EBeamPresenceStatus Status, const FString& Description)
		: Online(bOnline),
		  LastOnline(LastOnline),
		  Status(Status),
		  Description(Description)
	{
	}
};

USTRUCT(BlueprintType)
struct BEAMABLECORERUNTIME_API FBeamFriendInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBeamGamerTag FriendGamerTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid PartyId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid LobbyId;

	FBeamFriendInfo() = default;

	explicit FBeamFriendInfo(const FBeamGamerTag& FriendGamerTag)
		: FriendGamerTag(FriendGamerTag)
	{
	}

	bool operator==(const FBeamFriendInfo& Other) const
	{
		return Other.FriendGamerTag == FriendGamerTag;
	}
};

USTRUCT(BlueprintType)
struct BEAMABLECORERUNTIME_API FBeamPlayerBlocked
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBeamGamerTag PlayerGamerTag;

	FBeamPlayerBlocked() = default;

	explicit FBeamPlayerBlocked(const FBeamGamerTag& PlayerGamerTag)
		: PlayerGamerTag(PlayerGamerTag)
	{
	}

	bool operator==(const FBeamPlayerBlocked& Other) const
	{
		return Other.PlayerGamerTag == PlayerGamerTag;
	}
};

USTRUCT(BlueprintType)
struct BEAMABLECORERUNTIME_API FBeamFriendInvite
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBeamGamerTag FriendGamerTag;

	FBeamFriendInvite() = default;

	explicit FBeamFriendInvite(const FBeamGamerTag& FriendGamerTag)
		: FriendGamerTag(FriendGamerTag)
	{
	}

	bool operator==(const FBeamFriendInvite& Other) const
	{
		return Other.FriendGamerTag == FriendGamerTag;
	}
};

USTRUCT(BlueprintType)
struct BEAMABLECORERUNTIME_API FBeamFriendState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FBeamGamerTag PlayerGamerTag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FBeamFriendPresenceStatus Status;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FBeamFriendInfo> Friends;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FBeamFriendInvite> ReceivedInvites;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FBeamFriendInvite> SentInvites;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FBeamPlayerBlocked> BlockedPlayers;

	FBeamFriendState() = default;

	FBeamFriendState(const FBeamGamerTag& PlayerGamerTag, const FBeamFriendPresenceStatus& Status)
		: PlayerGamerTag(PlayerGamerTag),
		  Status(Status)
	{
	}

	FBeamFriendState(const FBeamGamerTag& SenderId) : PlayerGamerTag(SenderId)
	{
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateFriend, FBeamGamerTag, FriendGamerTag, FUserSlot, UserSlot);

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUpdateFriendCode, FBeamGamerTag, FUserSlot);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerBlockedStatusChanged, FBeamGamerTag, PlayerGamerTag, FUserSlot,
                                             UserSlot);

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerBlockedStatusChangedCode, FBeamGamerTag, FUserSlot);

/**
 * 
 */
UCLASS()
class BEAMABLECORERUNTIME_API UBeamFriendsSubsystem : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	UBeamFriendsApi* BeamFriendsApi;

	UPROPERTY()
	UBeamMailApi* BeamMailApi;

	UPROPERTY()
	UBeamPresenceApi* BeamPresenceApi;

	UPROPERTY()
	UBeamSocialNotifications* SocialNotifications;

	UPROPERTY()
	UBeamMailNotifications* MailNotifications;

	TMap<FBeamGamerTag, FBeamFriendState> FriendStates;

	virtual void InitializeWhenUnrealReady_Implementation(FBeamOperationHandle& ResultOp) override;

	virtual void OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser,
	                                           const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp) override;

	virtual void OnUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason,
	                                            const FBeamRealmUser& BeamRealmUser,
	                                            FBeamOperationHandle& ResultOp) override;

public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamFriendsSubsystem* GetSelf(const UObject* CallingContext)
	{
		return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamFriendsSubsystem>();
	}

	/**
	 * Triggers when a Player received an invitation from another player
	 *
	 * This uses the @link UBeamMailNotifications @endlink to triggers the fetch of the received invite.
	 *
	 * When it's called the local state is already updated.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnUpdateFriend OnInviteReceived;

	/**
	 * @copydoc OnInviteReceived
	 */
	FOnUpdateFriendCode OnInviteReceivedCode;

	/**
	 * Triggers when a Player accept the invite from another Player.
	 *
	 * This uses the @link UBeamSocialNotifications @endlink to triggers the fetch for changes in the @link FriendStates @endlink .
	 *
	 * When it's called the local state is already updated.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnUpdateFriend OnInviteAccepted;

	/**
	 * @copydoc OnInviteAccepted
	 */
	FOnUpdateFriendCode OnInviteAcceptedCode;

	/**
	 * Triggers when a Player decline the invite from another Player.
	 *
	 * It's only triggered locally, so this event will not trigger anything on the sender Player.
	 *
	 * This uses the @link UBeamSocialNotifications @endlink to triggers the fetch for changes in the @link FriendStates @endlink .
	 *
	 * When it's called the local state is already updated.
	*/
	UPROPERTY(BlueprintAssignable)
	FOnUpdateFriend OnInviteDeclined;

	/**
	 * @copydoc OnInviteDeclined
	 */
	FOnUpdateFriendCode OnInviteDeclinedCode;

	/**
	 * Triggers when a Player is removed from the friend list.
	 *
	 * When a friend be blocked this will be triggered as the players will stop from being friends.
	 *
	 * This uses the @link UBeamSocialNotifications @endlink to triggers the fetch for changes in the @link FriendStates @endlink .
	 *
	 * When it's called the local state is already updated.
	*/
	UPROPERTY(BlueprintAssignable)
	FOnUpdateFriend OnFriendRemoved;

	/**
	 * @copydoc OnFriendRemoved
	 */
	FOnUpdateFriendCode OnFriendRemovedCode;

	/**
	 * Triggers when the current Player blocks another Player.
	 *
	 * This uses the @link UBeamSocialNotifications @endlink triggers the fetch for changes in the @link FriendStates @endlink .
	 *
	 * When it's called the local state is already updated.
	*/
	UPROPERTY(BlueprintAssignable)
	FOnPlayerBlockedStatusChanged OnPlayerBlocked;

	/**
	 * @copydoc OnPlayerBlocked
	 */
	FOnPlayerBlockedStatusChangedCode OnPlayerBlockedCode;

	/**
	 * Triggers when a Player is blocked by another Player.
	 *
	 * This usually is not a use case as is not a common case to warning someone about being blocked, but we are covering this case.
	 *
	 * This uses the @link UBeamSocialNotifications @endlink triggers the fetch for changes in the @link FriendStates @endlink .
	 *
	 * When it's called the local state is already updated.
	*/
	UPROPERTY(BlueprintAssignable)
	FOnPlayerBlockedStatusChanged OnPlayerBeenBlocked;

	/**
	* @copydoc OnPlayerBeenBlocked
	*/
	FOnPlayerBlockedStatusChangedCode OnPlayerBeenBlockedCode;

	/**
	 * Triggers when a Player is unblocked.
	 *
	 * This uses the @link UBeamSocialNotifications @endlink triggers the fetch for changes in the @link FriendStates @endlink .
	 *
	 * When it's called the local state is already updated.
	*/
	UPROPERTY(BlueprintAssignable)
	FOnPlayerBlockedStatusChanged OnPlayerUnblocked;

	/**
	 * @copydoc OnPlayerUnblocked
	 */
	FOnPlayerBlockedStatusChangedCode OnPlayerUnblockedCode;


	/**
	 * Triggers when a Player is unblocked by another Player.
	 *
	 * This usually is not a use case as is not a common case to warning someone about being unblocked, but we are covering this case.
	 *
	 * This uses the @link UBeamSocialNotifications @endlink triggers the fetch for changes in the @link FriendStates @endlink .
	 *
	 * When it's called the local state is already updated.
	*/
	UPROPERTY(BlueprintAssignable)
	FOnPlayerBlockedStatusChanged OnPlayerBeenUnblocked;

	/**
	* @copydoc OnPlayerBeenUnblocked
	*/
	FOnPlayerBlockedStatusChangedCode OnPlayerBeenUnblockedCode;

	/**
	 * Triggers when a friend change anything in the status (Online, LastLogin, etc. See @link FBeamFriendPresenceStatus @endlink ) 
	 *
	 * This uses the @link UBeamSocialNotifications @endlink to triggers the fetch for changes in the @link FriendPresenceStatusState @endlink .
	 *
	 * When it's called the local state is already updated.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnUpdateFriend OnFriendPresenceStatusUpdate;

	/**
	 * @copydoc OnFriendPresenceStatusUpdate
	 */
	FOnUpdateFriendCode OnFriendPresenceStatusUpdateCode;

	/**
	 * Triggers when some error happens fetching the presence status 
	 *
	 */
	UPROPERTY(BlueprintAssignable)
	FOnUpdateFriend OnFriendPresenceStatusUpdateError;

	/**
	 * @copydoc OnFriendPresenceStatusUpdateError
	 */
	FOnUpdateFriendCode OnFriendPresenceStatusUpdateErrorCode;


	/**
	 * @brief Attempts to retrieve the friend state for a specific user slot.
	 *
	 * This gets the FriendState from the local state.
	 *
	 * @param UserSlot: The UserSlot that you try to get the friend state.
	 * @param FriendState: The reference for the out result of the player friend state.
	 *
	 * @return Returns False if the user don't have the friend state initialized or if it's not possible to retrieve the data.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Friend",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetUserFriendState(FUserSlot UserSlot, FBeamFriendState& FriendState);

	/**
	 * @brief Attempts to retrieve the friend state for a specific player using the FBeamGamerTag.
	 *
	 * This gets the FriendState from the local state.
	 *
	 * @param PlayerGamerTag: The PlayerGamerTag that you try to get the friend state.
	 * @param FriendState: The reference for the out result of the player friend state.
	 *
	 * @return Returns False if the user don't have the friend state initialized or if it's not possible to retrieve the data.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Friend",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetPlayerFriendState(FBeamGamerTag PlayerGamerTag, FBeamFriendState& FriendState);

	/**
	 * @brief Attempts to retrieve the friend presence status for a specific player using the FBeamGamerTag.
	 *
	 * This gets the FriendState from the local state.
	 *
	 * @param PlayerGamerTag: The PlayerGamerTag that you try to get the friend state.
	 * @param StatusState: The reference for the out result of the player presence status.
	 *
	 * @return Returns False if the user don't have the friend state initialized or if it's not possible to retrieve the data.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Friend",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetFriendPresenceState(FBeamGamerTag PlayerGamerTag, FBeamFriendPresenceStatus& StatusState);

	/**
	 * @brief Fetch the state for a given UserSlot.
	 *
	 * This will fetch the state of the give user slot and update the local state with the fetched data.
	 *
	 * Updates the local state of: @link FriendStates @endlink 
	 *
	 * @param UserSlot: The target UserSlot to fetch the state.
	 * @param OnOperationEvent: The callback event that handles the result.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Friends",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchPlayerFriendStateOperation(FUserSlot UserSlot,
	                                                     FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchPlayerFriendStateOperation
	 */
	FBeamOperationHandle CPP_FetchPlayerFriendStateOperation(FUserSlot UserSlot,
	                                                         FBeamOperationEventHandlerCode OnOperationEvent);
	/**
	 * @brief Fetch the friend state for multiple players ids.
	 *
	 * This will fetch the friend state for multiple players Ids, it could be useful for the case of facilitate the invite a friend of a friend.
	 *
	 * Updates the local state of: @link FriendStates @endlink 
	 *
	 * @param UserSlot: The target UserSlot to fetch the state.
	 * @param PlayerGamerTags: The Ids for the players that will be fetched to local state.
	 * @param OnOperationEvent: The callback event that handles the result.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Friends",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchFriendsStateOperation(FUserSlot UserSlot, TArray<FBeamGamerTag> PlayerGamerTags,
	                                                FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchFriendsStateOperation
	 */
	FBeamOperationHandle CPP_FetchFriendsStateOperation(FUserSlot UserSlot, TArray<FBeamGamerTag> PlayerGamerTags,
	                                                    FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief Fetch the friend STATUS state for multiple players ids.
	 *
	 * This will fetch the friend status for multiple players Ids, would be helpful for update the friend list at once.
	 *
	 * Updates the local state of: @link FriendPresenceStatusState @endlink 
	 *
	 * @param UserSlot: The target UserSlot to fetch the state.
	 * @param PlayerGamerTags: The Ids for the players that will be fetched to local state.
	 * @param OnOperationEvent: The callback event that handles the result.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Friends",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchFriendPresenceStatusOperation(FUserSlot UserSlot, TArray<FBeamGamerTag> PlayerGamerTags,
	                                                        FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchFriendPresenceStatusOperation
	 */
	FBeamOperationHandle CPP_FetchFriendPresenceStatusOperation(FUserSlot UserSlot,
	                                                            TArray<FBeamGamerTag> PlayerGamerTags,
	                                                            FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief Invite a player to be friend.
	 *
	 * Send a friend invitation to a specific player, that invitation will update the local state of FriendStates in SentInvites.
	 *
	 * It's possible to send and accept multiple friend invitation from the same player, it's necessary to validate that in your end before send the invite.
	 *
	 * Updates the local state of: @link FriendStates @endlink
	 *
	 * @param UserSlot: The sender UserSlot that will be used for validate the invite.
	 * @param FriendGamerTag: The target PlayerGamerTag that will receive the invite.
	 * @param OnOperationEvent: The callback event that handles the result.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Friends",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle SendFriendInviteOperation(FUserSlot UserSlot, FBeamGamerTag FriendGamerTag,
	                                               FBeamOperationEventHandler OnOperationEvent);
	/**
	 * @copydoc SendFriendInviteOperation
	 */
	FBeamOperationHandle CPP_SendFriendInviteOperation(FUserSlot UserSlot, FBeamGamerTag FriendGamerTag,
	                                                   FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief Accept an invitation sent to a given UserSlot.
	 *
	 * Update the local state of: @link FriendStates @endlink
	 *
	 * @param UserSlot: The UserSlot that will accept the invitation
	 * @param FriendGamerTag: The sender PlayerGamerTag that sent the friend invitation.
	 * @param OnOperationEvent: The callback event that handles the result.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Friends",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle AcceptFriendInviteOperation(FUserSlot UserSlot, FBeamGamerTag FriendGamerTag,
	                                                 FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc AcceptFriendInviteOperation
	 */
	FBeamOperationHandle CPP_AcceptFriendInviteOperation(FUserSlot UserSlot, FBeamGamerTag FriendGamerTag,
	                                                     FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief Delete the friend invitation received or sent.
	 *
	 * This can be called by the sender or the receiver of the invitation.
	 *
	 * Updates the local state of: @link FriendStates @endlink
	 *
	 * @param UserSlot: The UserSlot that would like to delete the invitation
	 * @param FriendGamerTag: The target PlayerGamerTag that the invitation has been sent or received.
	 * @param OnOperationEvent: The callback event that handles the result.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Friends",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle DeclineFriendInviteOperation(FUserSlot UserSlot, FBeamGamerTag FriendGamerTag,
	                                                  FBeamOperationEventHandler OnOperationEvent);
	/**
	 * @copydoc DeclineFriendInviteOperation
	 */
	FBeamOperationHandle CPP_DeclineFriendInviteOperation(FUserSlot UserSlot, FBeamGamerTag FriendGamerTag,
	                                                      FBeamOperationEventHandlerCode OnOperationEvent);
	/**
	 * @brief Block a player from being friends.
	 *
	 * Blocked players cannot be friends, and it will prevent the player from receive or send invites.
	 * If you block a friend, that will be removed from your friend list and you will be removed from his friend list.
	 *
	 * @param UserSlot: The UserSlot that would like to block another Player.
	 * @param PlayerGamerTag: The target PlayerGamerTag that will be blocked.
	 * @param OnOperationEvent: The callback event that handles the result.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Friends",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle BlockPlayerOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	                                          FBeamOperationEventHandler OnOperationEvent);
	/**
	 * @copydoc BlockPlayerOperation
	 */
	FBeamOperationHandle CPP_BlockPlayerOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	                                              FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief Unblock a player.
	 *
	 * That will allow for you to be friend again of this player.
	 * Just unblock the player won't will make you both friends again, it's required to send an invitation again.
	 *
	 * @param UserSlot: The UserSlot that blocked the player and would like to unlbock.
	 * @param PlayerGamerTag: The target PlayerGamerTag of the player to be Unblocked.
	 * @param OnOperationEvent: The callback event that handles the result.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Friends",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle UnblockPlayerOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	                                            FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc UnblockPlayerOperation
	 */
	FBeamOperationHandle CPP_UnblockPlayerOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	                                                FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * Remove a friend from the friend list.
	 *
	 * @param UserSlot: The UserSlot that would like to remove a friend from the friend list.
	 * @param FriendGamerTag: The target FriendGamerTag that will be removed from the friend list.
	 * @param OnOperationEvent: The callback event that handles the result.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Friends",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle RemoveFriendOperation(FUserSlot UserSlot, FBeamGamerTag FriendGamerTag,
	                                           FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc RemoveFriendOperation
	 */
	FBeamOperationHandle CPP_RemoveFriendOperation(FUserSlot UserSlot, FBeamGamerTag FriendGamerTag,
	                                               FBeamOperationEventHandlerCode OnOperationEvent);

protected:
	// Operation Functions
	void FetchPlayerFriendState(FUserSlot UserSlot, FBeamOperationHandle Op);

	void FetchFriendsState(FUserSlot UserSlot, TArray<FBeamGamerTag> PlayerGamerTags, FBeamOperationHandle Op);

	void FetchFriendPresenceStatus(FUserSlot UserSlot, TArray<FBeamGamerTag> PlayerGamerTags, FBeamOperationHandle Op);

	void SendFriendInvite(FUserSlot UserSlot, FBeamGamerTag FriendGamerTag, FBeamOperationHandle Op);

	void AcceptFriendInvite(FUserSlot UserSlot, FBeamGamerTag FriendGamerTag, FBeamOperationHandle Op);

	void DeclineFriendInvite(FUserSlot UserSlot, FBeamGamerTag FriendGamerTag, FBeamOperationHandle Op);

	void BlockPlayer(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag, FBeamOperationHandle Op);

	void UnblockPlayer(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag, FBeamOperationHandle Op);

	void RemoveFriend(FUserSlot UserSlot, FBeamGamerTag FriendGamerTag, FBeamOperationHandle Op);

	// Utility

	bool TryGetBeamGameTagFromUserSlot(FUserSlot UserSlot, FBeamGamerTag& PlayerGamerTag);

	FBeamFriendState MakeFriendState(USocial* Social);

	FBeamFriendPresenceStatus MakeFriendPresenceStatus(FSocialPresenceRefreshNotificationMessage PresenceStatusMessage);

	/*
	 * As the presence status and the friend info comes from different apis it will triggers to update the presence status of the player in case of adding a new player
	 */
	void RefreshPresenceAndTriggerEvent(FBeamGamerTag FriendGamerTag, FUserSlot UserSlot);

	//Notifications - Handle update and callbacks from the backend
	UFUNCTION()
	void SocialRefreshNotificationHandler(FSocialRefreshNotificationMessage Message, FUserSlot UserSlot);

	UFUNCTION()
	void SocialPresenceRefreshNotificationHandler(FSocialPresenceRefreshNotificationMessage Message,
	                                              FUserSlot UserSlot);

	UFUNCTION()
	void MailRefreshNotificationHandler(FMailRefreshNotificationMessage Message, FUserSlot UserSlot);
};
