// Copyright 2023 Hathora, Inc.

#pragma once

#include "CoreMinimal.h"
#include "HathoraSDK.h"
#include "HathoraSDKAPI.h"
#include "HathoraTypes.h"

class HATHORASDK_API FHathoraSDKDiscoveryV1 : public FHathoraSDKAPI
{
public:
	
	static FHathoraSDKDiscoveryV1* Instance();
	
	// Get ping times to all available Hathora Cloud regions.
	// Each region is pinged NumPingsPerRegion times and the
	// minimum is returned.
	// Pings are returned in milliseconds.
	// @param OnComplete The delegate to call when the request is complete with averaged ping times.
	// @param NumPingsPerRegion The number of pings to send to each region.
	void GetRegionalPings(const FHathoraOnGetRegionalPings& OnComplete, int32 NumPingsPerRegion = 3);

	DECLARE_DELEGATE_OneParam(FHathoraOnGetPingServiceEndpoints, const TArray<FHathoraDiscoveredPingEndpoint>&);

	// Returns an array of all regions with a host that a client can ping via ICMP.
	// See the "Get Regional Pings" functions that will handle the full ping process for you.
	// @param OnComplete The delegate to call when the request is complete.
	void GetPingServiceEndpoints(const FHathoraOnGetPingServiceEndpoints& OnComplete);

private:
	TArray<FHathoraDiscoveredPingEndpoint> PingEndpoints;
	int32 NumPingsPerRegion;
	int32 NumPingsPerRegionCompleted;
	TSharedPtr<TMap<FString, TArray<int32>>> PingResults;

	DECLARE_DELEGATE_TwoParams(FOnGetPingDelegate, int32 /* Ping */, bool /* bWasSuccessful */);

	void InitiatePings(const TArray<FHathoraDiscoveredPingEndpoint>& PingEndpoints, const FHathoraOnGetRegionalPings& OnComplete);

	void PingEachRegion(const FHathoraOnGetRegionalPings& OnComplete);
};
