#pragma once
#include "OnlineSubsystem.h"
#include "Beamable/OnlineSubsystemBeamable.h"

class FInternetAddressBeamable : public FInternetAddr
{
PACKAGE_SCOPE:
	/** The host to connect to */
	FString HostAddress;
	/** Port */
	int32 Port;

	/**
	 * Copy Constructor
	 */
	FInternetAddressBeamable(const FInternetAddressBeamable& Src) :
		HostAddress(Src.HostAddress),
		Port(Src.Port)
	{
	}

public:
	/**
	 * Constructor. Sets address to default state
	 */
	FInternetAddressBeamable() :
		HostAddress(TEXT("")),
		Port(0)
	{
	}

	/**
	 * Gets the ip address in a raw array stored in network byte order.
	 *
	 * @return The raw address stored in an array
	 */
	virtual TArray<uint8> GetRawIp() const override
	{
		UE_LOG_ONLINE(Warning, TEXT("FInternetAddressBeamable::GetRawIp is not supported."));
		return TArray<uint8>();
	}

	/**
	 * Sets the ip address from a raw network byte order array.
	 *
	 * @param RawAddr the new address to use (must be converted to network byte order)
	 */
	virtual void SetRawIp(const TArray<uint8>& RawAddr) override
	{
		UE_LOG_ONLINE(Warning, TEXT("FInternetAddressBeamable::SetRawIp is not supported."));
	}

	/**
	 * Sets the ip address from a host byte order uint32
	 *
	 * @param InAddr the new address to use (must convert to network byte order)
	 */
	void SetIp(uint32 InAddr) override
	{
		UE_LOG_ONLINE(Warning, TEXT("FInternetAddressBeamable::SetIp is not supported."));
	}

	/**
	 * Sets the ip address from a string ("A.B.C.D")
	 *
	 * @param InAddr the string containing the new ip address to use
	 */
	void SetIp(const TCHAR* InAddr, bool& bIsValid) override;

	/**
	 * Copies the network byte order ip address to a host byte order dword
	 *
	 * @param OutAddr the out param receiving the ip address
	 */
	void GetIp(uint32& OutAddr) const override
	{
		OutAddr = 0;
		UE_LOG_ONLINE(Warning, TEXT("FInternetAddressBeamable::GetIp is not supported and will set OutAddr to 0."));
	}

	/**
	 * Sets the port number from a host byte order int
	 *
	 * @param InPort the new port to use (must convert to network byte order)
	 */
	void SetPort(int32 InPort) override
	{
		Port = InPort;
	}

	/**
	 * Copies the port number from this address and places it into a host byte order int
	 *
	 * @param OutPort the host byte order int that receives the port
	 */
	void GetPort(int32& OutPort) const override
	{
		OutPort = Port;
	}

	/**
	 * Returns the port number from this address in host byte order
	 */
	int32 GetPort() const override
	{
		return Port;
	}

	/** Sets the address to be any address */
	void SetAnyAddress() override
	{
	}

	/** Sets the address to broadcast */
	void SetBroadcastAddress() override
	{
	}

	/** Sets the address to the loopback address */
	void SetLoopbackAddress() override
	{
	}

	/**
	 * Converts this internet ip address to string form
	 *
	 * @param bAppendPort whether to append the port information or not
	 */
	FString ToString(bool bAppendPort) const override
	{
		if (bAppendPort)
		{
			return FString::Printf(TEXT("%s:%d"), *HostAddress, Port);
		}
		else
		{
			return HostAddress;
		}
	}

	/**
	 * Compares two internet ip addresses for equality
	 *
	 * @param Other the address to compare against
	 */
	virtual bool operator==(const FInternetAddr& Other) const override
	{
		FInternetAddressBeamable& SteamOther = (FInternetAddressBeamable&)Other;
		return *HostAddress == *SteamOther.HostAddress && Port == SteamOther.Port;
	}

	bool operator==(const FInternetAddressBeamable& Other) const
	{
		return *HostAddress == *Other.HostAddress && Port == Other.Port;
	}

	bool operator!=(const FInternetAddressBeamable& Other) const
	{
		return !(FInternetAddressBeamable::operator==(Other));
	}

	virtual uint32 GetTypeHash() const override
	{
		return GetTypeHashHelper(ToString(true));
	}

	friend uint32 GetTypeHash(const FInternetAddressBeamable& A)
	{
		return A.GetTypeHash();
	}

	/**
	 * Is this a well formed internet address
	 *
	 * @return true if a valid IP, false otherwise
	 */
	virtual bool IsValid() const override
	{
		return !HostAddress.IsEmpty();
	}

	virtual FName GetProtocolType() const override
	{
		return FNetworkProtocolTypes::Beamable;
	}

	virtual TSharedRef<FInternetAddr> Clone() const override
	{
		TSharedRef<FInternetAddressBeamable> NewAddress = MakeShareable(new FInternetAddressBeamable);
		NewAddress->HostAddress = HostAddress;
		NewAddress->Port = Port;
		return NewAddress;
	}
};
