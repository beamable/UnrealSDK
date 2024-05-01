// Copyright 2023 Hathora, Inc.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/DeveloperSettings.h"

#include "HathoraSDKConfig.generated.h"

UCLASS(Config = Game, meta = (DisplayName = "Hathora SDK"))
class HATHORASDK_API UHathoraSDKConfig : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UHathoraSDKConfig()
	{
		CategoryName = TEXT("Plugins");
		SectionName = TEXT("HathoraSDK");
	}

	const FString& GetBaseUrl() const { return BaseUrl; };

	const float& GetPingTimeoutSeconds() const { return PingTimeoutSeconds; };

private:
	UPROPERTY(Config, EditAnywhere, Category = "Network")
	FString BaseUrl = "https://api.hathora.dev";

	UPROPERTY(Config, EditAnywhere, Category = "Network")
	float PingTimeoutSeconds = 1.0f;
};
