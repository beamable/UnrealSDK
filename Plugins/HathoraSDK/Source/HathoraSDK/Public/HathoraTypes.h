// Copyright 2023 Hathora, Inc.

#pragma once

#include "CoreMinimal.h"

#include "HathoraTypes.generated.h"

USTRUCT()
struct FHathoraDiscoveredPingEndpoint
{
	GENERATED_USTRUCT_BODY();
	
	// The name of the Hathora Cloud region (e.g. "Seattle").
	UPROPERTY()
	FString Region;

	// The pingable host of the Hathora Cloud region. The host for
	// a specific region may change from time to time. You can use
	// this host for both ICMP and WebSocket pings.
	UPROPERTY()
	FString Host;

	// The port to use if you're using the WebSocket echo server to
	// get ping results.
	UPROPERTY()
	int32 Port = 0;
};

struct FHathoraRegionPings
{
	// The ping times in milliseconds for each region. The key is the name of the region.
	TMap<FString, int32> Pings;
};

struct FHathoraSDKSecurity
{
	FHathoraSDKSecurity() {}

	FHathoraSDKSecurity(FString InAuthToken)
	{
		this->AuthToken = InAuthToken;
	}

	// The token to use in the Authorization HTTP header in API calls.
	// This can be either the HathoraDevToken for server/trusted calls,
	// or the player auth token for client/untrusted calls.
	FString AuthToken;
};

DECLARE_DELEGATE_OneParam(FHathoraOnGetRegionalPings, FHathoraRegionPings);

UENUM(BlueprintType)
enum class EHathoraCloudRegion : uint8
{
	Seattle,
	Los_Angeles,
	Washington_DC,
	Chicago,
	London,
	Frankfurt,
	Mumbai,
	Singapore,
	Tokyo,
	Sydney,
	Sao_Paulo,
	Unknown UMETA(Hidden)
};
