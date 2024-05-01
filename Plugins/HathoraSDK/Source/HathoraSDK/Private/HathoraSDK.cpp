// Copyright 2023 Hathora, Inc.

#include "HathoraSDK.h"
#include "HathoraSDKModule.h"
#include "HathoraSDKAuthV1.h"
#include "HathoraSDKDiscoveryV1.h"
#include "HathoraSDKLobbyV3.h"
#include "HathoraSDKRoomV2.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

FHathoraSDK* FHathoraSDK::Instance()
{
	static FHathoraSDK sdk;
	static bool initialized = false;
	if (!initialized)
	{
		initialized = true;
		
		sdk.AuthV1 = FHathoraSDKAuthV1::Instance();
		sdk.DiscoveryV1 = FHathoraSDKDiscoveryV1::Instance();
		sdk.LobbyV3 = FHathoraSDKLobbyV3::Instance();
		sdk.RoomV2 = FHathoraSDKRoomV2::Instance();

		// Should the game force a relaunch in Steam if the client isn't already loaded
		FString appId;
		GConfig->GetString(TEXT("HathoraSDK"), TEXT("AppId"), appId, GEngineIni);
		
		// @param AppId The ID of your Hathora App (e.g. "app-88871e9f-ca62-413c-beab-da226f2afd71").
		// @param Security The security configuration for your Hathora App; primarily used to provide the Dev Token.
		sdk.SetCredentials(appId, FHathoraSDKSecurity());
	}

	return &sdk;
}

void FHathoraSDK::GetRegionalPings(const FHathoraOnGetRegionalPings& OnComplete, int32 NumPingsPerRegion)
{
	FHathoraSDK* SDK = Instance();
	SDK->DiscoveryV1->GetRegionalPings(FHathoraOnGetRegionalPings::CreateLambda([SDK,OnComplete](const FHathoraRegionPings& result)
	{
		OnComplete.ExecuteIfBound(result);
	}));
}

void FHathoraSDK::SetCredentials(FString AppId, FHathoraSDKSecurity Security)
{
	AuthV1->SetCredentials(AppId, Security);
	DiscoveryV1->SetCredentials(AppId, Security);
	LobbyV3->SetCredentials(AppId, Security);
	RoomV2->SetCredentials(AppId, Security);
}

void FHathoraSDK::SetPreferredCloudRegion(EHathoraCloudRegion Region)
{
	PreferredCloudRegion = Region < EHathoraCloudRegion::Unknown ? Region : EHathoraCloudRegion::Chicago;
}
