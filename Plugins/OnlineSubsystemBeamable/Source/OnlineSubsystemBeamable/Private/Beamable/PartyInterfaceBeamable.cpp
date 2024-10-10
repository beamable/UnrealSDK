#include "PartyInterfaceBeamable.h"

#include "Beamable/OnlineSubsystemBeamable.h"
#include "OnlineSubsystemBeamableTypes.h"
#include "AutoGen/SubSystems/BeamLobbyApi.h"

// implement FBeamableOnlinePartyId
const uint8* FBeamableOnlinePartyId::GetBytes() const
{
	return reinterpret_cast<const uint8*>(Id.GetCharArray().GetData());
}

int32 FBeamableOnlinePartyId::GetSize() const
{
	return Id.Len();
}

bool FBeamableOnlinePartyId::IsValid() const
{
	return !Id.IsEmpty();
}

FString FBeamableOnlinePartyId::ToString() const
{
	return Id;
}

FString FBeamableOnlinePartyId::ToDebugString() const
{
	return Id;
}

FPartyInterfaceBeamable::FPartyInterfaceBeamable(FOnlineSubsystemBeamable* InSubsystem)
{
	BeamableSubsystem = InSubsystem;
}

// implement all the other IOnlineParty functions
void FPartyInterfaceBeamable::RestoreParties(const FUniqueNetId& LocalUserId, const FOnRestorePartiesComplete& CompletionDelegate)
{
	
}

void FPartyInterfaceBeamable::RestoreInvites(const FUniqueNetId& LocalUserId, const FOnRestoreInvitesComplete& CompletionDelegate)
{
	
}

void FPartyInterfaceBeamable::CleanupParties(const FUniqueNetId& LocalUserId, const FOnCleanupPartiesComplete& CompletionDelegate)
{
	
}

bool FPartyInterfaceBeamable::CreateParty(const FUniqueNetId& LocalUserId, const FOnlinePartyTypeId PartyTypeId, const FPartyConfiguration& PartyConfig, const FOnCreatePartyComplete& Delegate)
{
	return true;
}

bool FPartyInterfaceBeamable::UpdateParty(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FPartyConfiguration& PartyConfig, bool bShouldRegenerateReservationKey, const FOnUpdatePartyComplete& Delegate)
{
	return false;
}

bool FPartyInterfaceBeamable::JoinParty(const FUniqueNetId& LocalUserId, const IOnlinePartyJoinInfo& OnlinePartyJoinInfo, const FOnJoinPartyComplete& Delegate)
{
	return false;
}

void FPartyInterfaceBeamable::RequestToJoinParty(const FUniqueNetId& LocalUserId, const FOnlinePartyTypeId PartyTypeId, const FPartyInvitationRecipient& Recipient, const FOnRequestToJoinPartyComplete& Delegate)
{
	
}

void FPartyInterfaceBeamable::ClearRequestToJoinParty(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& Sender, EPartyRequestToJoinRemovedReason Reason)
{
	
}

void FPartyInterfaceBeamable::QueryPartyJoinability(const FUniqueNetId& LocalUserId, const IOnlinePartyJoinInfo& OnlinePartyJoinInfo, const FOnQueryPartyJoinabilityCompleteEx& Delegate)
{
	
}

bool FPartyInterfaceBeamable::RejoinParty(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FOnlinePartyTypeId& PartyTypeId, const TArray<FUniqueNetIdRef>& FormerMembers, const FOnJoinPartyComplete& Delegate)
{
	return false;
}

bool FPartyInterfaceBeamable::LeaveParty(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FOnLeavePartyComplete& Delegate)
{
	return false;
}

bool FPartyInterfaceBeamable::LeaveParty(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, bool bSynchronizeLeave, const FOnLeavePartyComplete& Delegate)
{
	return false;
}

bool FPartyInterfaceBeamable::ApproveJoinRequest(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& RecipientId, bool bIsApproved, int32 DeniedResultCode)
{
	return false;
}

void FPartyInterfaceBeamable::RespondToQueryJoinability(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& RecipientId, bool bCanJoin, int32 DeniedResultCode, FOnlinePartyDataConstPtr PartyData)
{
	
}

bool FPartyInterfaceBeamable::SendInvitation(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FPartyInvitationRecipient& Recipient, const FOnSendPartyInvitationComplete& Delegate)
{
	return false;
}

void FPartyInterfaceBeamable::CancelInvitation(const FUniqueNetId& LocalUserId, const FUniqueNetId& TargetUserId, const FOnlinePartyId& PartyId, const FOnCancelPartyInvitationComplete& Delegate)
{
	
}

bool FPartyInterfaceBeamable::RejectInvitation(const FUniqueNetId& LocalUserId, const FUniqueNetId& SenderId)
{
	return false;
}

void FPartyInterfaceBeamable::ClearInvitations(const FUniqueNetId& LocalUserId, const FUniqueNetId& SenderId, const FOnlinePartyId* PartyId)
{
	return;
}

bool FPartyInterfaceBeamable::KickMember(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& TargetMemberId, const FOnKickPartyMemberComplete& Delegate)
{
	return false;
}

bool FPartyInterfaceBeamable::PromoteMember(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& TargetMemberId, const FOnPromotePartyMemberComplete& Delegate)
{
	return false;
}

bool FPartyInterfaceBeamable::UpdatePartyData(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FName& Namespace, const FOnlinePartyData& PartyData)
{
	return false;
}

bool FPartyInterfaceBeamable::UpdatePartyMemberData(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FName& Namespace, const FOnlinePartyData& PartyMemberData)
{
	return false;
}

bool FPartyInterfaceBeamable::IsMemberLeader(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& MemberId) const
{
	return false;
}

uint32 FPartyInterfaceBeamable::GetPartyMemberCount(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId) const
{
	return 0;
}

FOnlinePartyConstPtr FPartyInterfaceBeamable::GetParty(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId) const
{
	return nullptr;
}

FOnlinePartyConstPtr FPartyInterfaceBeamable::GetParty(const FUniqueNetId& LocalUserId, const FOnlinePartyTypeId& PartyTypeId) const
{
	return nullptr;
}

FOnlinePartyMemberConstPtr FPartyInterfaceBeamable::GetPartyMember(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& MemberId) const
{
	return nullptr;
}

FOnlinePartyDataConstPtr FPartyInterfaceBeamable::GetPartyData(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FName& Namespace) const
{
	return nullptr;
}

FOnlinePartyDataConstPtr FPartyInterfaceBeamable::GetPartyMemberData(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& MemberId, const FName& Namespace) const
{
	return nullptr;
}

IOnlinePartyJoinInfoConstPtr FPartyInterfaceBeamable::GetAdvertisedParty(const FUniqueNetId& LocalUserId, const FUniqueNetId& UserId, const FOnlinePartyTypeId PartyTypeId) const
{
	return nullptr;
}

bool FPartyInterfaceBeamable::GetJoinedParties(const FUniqueNetId& LocalUserId, TArray<TSharedRef<const FOnlinePartyId>>& OutPartyIdArray) const
{
	return false;
}

bool FPartyInterfaceBeamable::GetPartyMembers(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, TArray<FOnlinePartyMemberConstRef>& OutPartyMembersArray) const
{
	return false;
}

bool FPartyInterfaceBeamable::GetPendingInvites(const FUniqueNetId& LocalUserId, TArray<IOnlinePartyJoinInfoConstRef>& OutPendingInvitesArray) const
{
	return false;
}

bool FPartyInterfaceBeamable::GetPendingJoinRequests(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, TArray<IOnlinePartyPendingJoinRequestInfoConstRef>& OutPendingJoinRequestArray) const
{
	return false;
}

bool FPartyInterfaceBeamable::GetPendingInvitedUsers(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, TArray<FUniqueNetIdRef>& OutPendingInvitedUserArray) const
{
	return false;
}

bool FPartyInterfaceBeamable::GetPendingRequestsToJoin(const FUniqueNetId& LocalUserId, TArray<IOnlinePartyRequestToJoinInfoConstRef>& OutRequestsToJoin) const
{
	return false;
}

FString FPartyInterfaceBeamable::MakeJoinInfoJson(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId)
{
	return "{}";
}

FString FPartyInterfaceBeamable::MakeTokenFromJoinInfo(const IOnlinePartyJoinInfo& JoinInfo) const
{
	return "";
}

IOnlinePartyJoinInfoConstPtr FPartyInterfaceBeamable::MakeJoinInfoFromJson(const FString& JoinInfoJson)
{
	return nullptr;
}

IOnlinePartyJoinInfoConstPtr FPartyInterfaceBeamable::MakeJoinInfo(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId)
{
	return nullptr;
}

IOnlinePartyJoinInfoConstPtr FPartyInterfaceBeamable::MakeJoinInfoFromToken(const FString& Token) const
{
	return nullptr;
}

IOnlinePartyJoinInfoConstPtr FPartyInterfaceBeamable::ConsumePendingCommandLineInvite()
{
	return nullptr;	
}

void FPartyInterfaceBeamable::DumpPartyState()
{
	
}
