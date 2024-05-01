// Copyright 2023 Hathora, Inc.

#pragma once

#include "CoreMinimal.h"
#include "HathoraSDKAPI.h"
#include "HathoraTypes.h"

struct FHathoraLoginResult
{
	int32 StatusCode = 0;

	FString ErrorMessage;

	// A unique Hathora-signed JWT player token.
	FString Token;
};

class HATHORASDK_API FHathoraSDKAuthV1 : public FHathoraSDKAPI
{
public:
	DECLARE_DELEGATE_OneParam(FHathoraOnLogin, FHathoraLoginResult); 

	static FHathoraSDKAuthV1* Instance();
	
	// Returns a unique player token for an anonymous user.
	//UFUNCTION(BlueprintCallable, Category = "HathoraSDK | AuthV1")
	void LoginAnonymous(const FHathoraOnLogin& OnComplete);

	// Returns a unique player token with a specified nickname for a user.
	// @param Nickname An alias to represent a player.
	//UFUNCTION(BlueprintCallable, Category = "HathoraSDK | AuthV1")
	void LoginNickname(FString Nickname, const FHathoraOnLogin& OnComplete);

	// Returns a unique player token using a Google-signed OIDC idToken.
	// @param IdToken A Google-signed OIDC ID token representing a player's
	//                authenticated identity. Learn how to get an idToken
	//                [here](https://cloud.google.com/docs/authentication/get-id-token).
	//UFUNCTION(BlueprintCallable, Category = "HathoraSDK | AuthV1")
	void LoginGoogle(FString IdToken, const FHathoraOnLogin& OnComplete);

private:
	void Login(FString Path, FJsonObject Body, const FHathoraOnLogin& OnComplete);
};
