#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystemTypes.h"
#include "IPAddress.h"
#include "Beamable/OnlineSubsystemBeamableDefines.h"
#include "AutoGen/Ticket.h"

class FOnlineSubsystemBeamable;

// from OnlineSubsystemTypes.h
TEMP_UNIQUENETIDSTRING_SUBCLASS(FUniqueNetIdBeamable, BEAMABLE_SUBSYSTEM);

/** 
 * Implementation of session information
 */
class FOnlineSessionInfoBeamable : public FOnlineSessionInfo
{
	/** Hidden on purpose */
	FOnlineSessionInfoBeamable(const FOnlineSessionInfoBeamable& Src) = delete;
	FOnlineSessionInfoBeamable& operator=(const FOnlineSessionInfoBeamable& Src) = delete;

public:
	/** Constructor */
	FOnlineSessionInfoBeamable();
	FOnlineSessionInfoBeamable(FString LobbyId);

	/** 
	 * Initialize a Beamable session info with the address of this machine
	 * and an id for the session
	 */
	static void Init(const FOnlineSubsystemBeamable& Subsystem);

	/** The ip & port that the host is listening on (valid for LAN/GameServer) */
	TSharedPtr<class FInternetAddr> HostAddr;
	/** Unique Id for this session */
	FUniqueNetIdBeamableRef SessionId;

public:

	virtual ~FOnlineSessionInfoBeamable() {}

	bool operator==(const FOnlineSessionInfoBeamable& Other) const
	{
		return false;
	}

	virtual const uint8* GetBytes() const override
	{
		return nullptr;
	}

	virtual int32 GetSize() const override
	{
		return sizeof(uint64) + sizeof(TSharedPtr<class FInternetAddr>);
	}

	virtual bool IsValid() const override
	{
		return HostAddr->IsValid();
	}

	virtual FString ToString() const override
	{
		return SessionId->ToString();
	}

	virtual FString ToDebugString() const override
	{
		return FString::Printf(TEXT("HostIP: %s SessionId: %s"), 
			HostAddr.IsValid() ? *HostAddr->ToString(true) : TEXT("INVALID"), 
			*SessionId->ToDebugString());
	}

	virtual const FUniqueNetId& GetSessionId() const override
	{
		return *SessionId;
	}
};

typedef TSharedPtr<UTicket> FOnlineMatchmakingTicketInfoPtr;