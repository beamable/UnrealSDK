// Copyright 2023 Hathora, Inc.

#include "HathoraSDKDiscoveryV1.h"
#include "HathoraSDKModule.h"
#include "HathoraSDKConfig.h"
#include "JsonObjectConverter.h"
#include "Icmp.h"

void FHathoraSDKDiscoveryV1::GetPingServiceEndpoints(const FHathoraOnGetPingServiceEndpoints& OnComplete)
{
	SendRequest(
		TEXT("GET"),
		TEXT("/discovery/v1/ping"),
		[OnComplete](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) mutable
	{
		TArray<FHathoraDiscoveredPingEndpoint> PingEndpointsResult;
		if (bSuccess && Response.IsValid())
		{
			FJsonObjectConverter::JsonArrayStringToUStruct(Response->GetContentAsString(), &PingEndpointsResult);
		}
		else
		{
			UE_LOG(LogHathoraSDK, Warning, TEXT("Could not retrieve ping endpoints"));
		}

		if (!OnComplete.ExecuteIfBound(PingEndpointsResult))
		{
			UE_LOG(LogHathoraSDK, Warning, TEXT("[GetPingServiceEndpoints] function pointer was not valid, so OnComplete will not be called"));
		}
	});
}

void FHathoraSDKDiscoveryV1::GetRegionalPings(const FHathoraOnGetRegionalPings& OnComplete, int32 InNumPingsPerRegion)
{
	if (InNumPingsPerRegion <= 0)
	{
		UE_LOG(LogHathoraSDK, Warning, TEXT("Cannot ping a region less than 1 time; defaulting to 3 pings per region."));
		InNumPingsPerRegion = 3;
	}

	NumPingsPerRegion = InNumPingsPerRegion;
	GetPingServiceEndpoints(FHathoraOnGetPingServiceEndpoints::CreateLambda([this,OnComplete](const TArray<FHathoraDiscoveredPingEndpoint>& InPingEndpoints)
	{
		this->InitiatePings(InPingEndpoints,OnComplete);
	}));
}

FHathoraSDKDiscoveryV1* FHathoraSDKDiscoveryV1::Instance()
{
	static FHathoraSDKDiscoveryV1 discV1;
	return &discV1;
}

void FHathoraSDKDiscoveryV1::InitiatePings(const TArray<FHathoraDiscoveredPingEndpoint>& InPingEndpoints, const FHathoraOnGetRegionalPings& OnComplete)
{
	PingEndpoints = InPingEndpoints;
	NumPingsPerRegionCompleted = 0;
	PingResults = MakeShared<TMap<FString, TArray<int32>>>();
	PingEachRegion(OnComplete);
}

void FHathoraSDKDiscoveryV1::PingEachRegion(const FHathoraOnGetRegionalPings& OnComplete)
{
	// recursively call this function until we have pinged each region
	// the desired number of times, and then aggregate the results and return
	// this ensures subsequent pings to a particular region are done sequentially
	// instead of simultaneously
	if (NumPingsPerRegionCompleted >= NumPingsPerRegion)
	{
		UE_LOG(LogHathoraSDK, Log, TEXT("Completed multiple pings to each Hathora region; returning the averages."));

		FHathoraRegionPings FinalResult;

		for (const TPair<FString, TArray<int32>>& PingResult : *PingResults)
		{
			int32 Min = -1;
			for (int32 PingTime : PingResult.Value)
			{
				if (Min == -1 || PingTime < Min)
				{
					Min = PingTime;
				}
			}
			FinalResult.Pings.Add(PingResult.Key, Min);
		}

		OnComplete.ExecuteIfBound(FinalResult);

		return;
	}

	NumPingsPerRegionCompleted++;

	TSharedPtr<int32> CompletedPings = MakeShared<int32>(0);
	const int32 PingsToComplete = PingEndpoints.Num();

	// ping each region once
	for (const FHathoraDiscoveredPingEndpoint& PingEndpoint : PingEndpoints)
	{
		FIcmp::IcmpEcho(
			PingEndpoint.Host,
			GetDefault<UHathoraSDKConfig>()->GetPingTimeoutSeconds(),
			[this, PingEndpoint, CompletedPings, PingsToComplete, OnComplete](FIcmpEchoResult Result)
			{
				if (Result.Status == EIcmpResponseStatus::Success)
				{
					int32 PingTime = Result.Time * 1000;
					UE_LOG(LogHathoraSDK, Log, TEXT("Ping to %s (%s) took: %d ms"), *PingEndpoint.Region, *PingEndpoint.Host, PingTime);
					TArray<int32>* RegionPings = PingResults->Find(PingEndpoint.Region);
					if (RegionPings == nullptr)
					{
						TArray<int32> NewRegionPings;
						NewRegionPings.Add(PingTime);
						PingResults->Add(PingEndpoint.Region, NewRegionPings);
					}
					else
					{
						RegionPings->Add(PingTime);
					}
				}
				else
				{
					UE_LOG(LogHathoraSDK, Warning, TEXT("Ping to %s (%s) failed: %s"), *PingEndpoint.Region, *PingEndpoint.Host, LexToString(Result.Status));
				}

				// Regardless of whether the ping was successful, we will mark it complete.
				if (++(*CompletedPings) == PingsToComplete)
				{
					UE_LOG(LogHathoraSDK, Log, TEXT("Pings to each region complete; triggering another set of pings."));
					PingEachRegion(OnComplete);
				}
			}
		);
	}
}