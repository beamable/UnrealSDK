// Copyright 2023 Hathora, Inc.
#pragma once

#include "CoreMinimal.h"
#include "HathoraTypes.h"
#include "HathoraSDKConfig.h"
#include "Delegates/Delegate.h"
#include "Kismet/BlueprintFunctionLibrary.h"

class FHathoraSDKAuthV1;
class FHathoraSDKDiscoveryV1;
class FHathoraSDKLobbyV3;
class FHathoraSDKRoomV2;

class HATHORASDK_API FHathoraSDK
{
public:

	static FHathoraSDK* Instance();
	
	// Get ping times to all available Hathora Cloud regions.
	// Each region is pinged NumPingsPerRegion times and the
	// minimum is returned.
	// Pings are returned in milliseconds.
	// @param OnComplete The delegate to call when the request is complete with averaged ping times.
	// @param NumPingsPerRegion The number of pings to send to each region.
	static void GetRegionalPings(const FHathoraOnGetRegionalPings& OnComplete, int32 NumPingsPerRegion = 3);

	// Set the credentials of this SDK instance.
	// @param AppId The ID of your Hathora App (e.g. "app-88871e9f-ca62-413c-beab-da226f2afd71").
	// @param Security The security configuration for your Hathora App; primarily used to provide the Dev Token.
	void SetCredentials(FString AppId, FHathoraSDKSecurity Security);

	FHathoraSDKAuthV1* AuthV1;

	FHathoraSDKDiscoveryV1* DiscoveryV1;

	FHathoraSDKLobbyV3* LobbyV3;

	FHathoraSDKRoomV2* RoomV2;

	EHathoraCloudRegion GetPreferredCloudRegion() const { return PreferredCloudRegion; }
	void SetPreferredCloudRegion(EHathoraCloudRegion Region);
	
private:
	
	EHathoraCloudRegion PreferredCloudRegion = EHathoraCloudRegion::Chicago;
};
