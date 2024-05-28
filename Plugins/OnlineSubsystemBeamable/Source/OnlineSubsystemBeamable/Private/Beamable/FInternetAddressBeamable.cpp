#include "Beamable/FInternetAddressBeamable.h"

/**
 * Sets the ip address from a string ("steam.STEAMID" or "STEAMID")
 *
 * @param InAddr the string containing the new ip address to use
 * @param bIsValid was the address valid for use
 */
void FInternetAddressBeamable::SetIp(const TCHAR* InAddr, bool& bIsValid)
{
	bIsValid = false;
	FString InAddrStr(InAddr);

	// Check for the steam. prefix
	FString BeamableIPAddrStr;
	BeamableIPAddrStr = InAddrStr;

	// Resolve the address/port
	FString hostName, port;
	if (BeamableIPAddrStr.Split(":", &hostName, &port, ESearchCase::CaseSensitive, ESearchDir::FromEnd))
	{
		HostAddress = hostName;
		Port = FCString::Atoi64(*port);
	}
	else
	{
		HostAddress = BeamableIPAddrStr;
	}

	bIsValid = true;
}
