/**
 * This file contains all data types for back-end communication that we declare by hand
 * and expect to be excluded from the code-gen process.
 *
 * The use case for this is so that we can safely depend on them in core classes
 * that want 0-dependency to code-gen'ed types (such as BeamBackend and others).
 */

#pragma once

#include "BeamCoreTypes.h"

#include "BeamSharedTypes.generated.h"

USTRUCT(BlueprintType)
struct FTokenResponse : public FBeamJsonSerializable
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString AccessToken;

	UPROPERTY(BlueprintReadOnly)
	FString TokenType;

	UPROPERTY(BlueprintReadOnly)
	FString RefreshToken;

	UPROPERTY(BlueprintReadOnly)
	int64 ExpiresIn;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};

/**

  _____   ____   _____ _______   _                 _         _____       __               _       _______    _              
 |  __ \ / __ \ / ____|__   __| | |               (_)       |  __ \     / _|             | |     |__   __|  | |             
 | |__) | |  | | (___    | |    | |     ___   __ _ _ _ __   | |__) |___| |_ _ __ ___  ___| |__      | | ___ | | _____ _ __  
 |  ___/| |  | |\___ \   | |    | |    / _ \ / _` | | '_ \  |  _  // _ \  _| '__/ _ \/ __| '_ \     | |/ _ \| |/ / _ \ '_ \ 
 | |    | |__| |____) |  | |    | |___| (_) | (_| | | | | | | | \ \  __/ | | | |  __/\__ \ | | |    | | (_) |   <  __/ | | |
 |_|     \____/|_____/   |_|    |______\___/ \__, |_|_| |_| |_|  \_\___|_| |_|  \___||___/_| |_|    |_|\___/|_|\_\___|_| |_|
											  __/ |                                                                         
											 |___/                                                                          
 
 */

USTRUCT(BlueprintType)
struct FLoginRefreshTokenRequestBody : public FBeamJsonSerializable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString GrantType = "refresh_token";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RefreshToken;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};

USTRUCT(BlueprintType)
struct FLoginRefreshTokenRequest : public FBeamBaseRequest
{
	GENERATED_BODY()	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLoginRefreshTokenRequestBody Body;
	
	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;
};

USTRUCT(BlueprintType)
struct FLoginRefreshTokenResponse : public FBeamBaseResponse
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTokenResponse Body;
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLoginRefreshTokenSuccess, int64, RequestId, FLoginRefreshTokenRequest, Request, FLoginRefreshTokenResponse, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLoginRefreshTokenError, int64, RequestId, FLoginRefreshTokenRequest, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnLoginRefreshTokenComplete, int64, RequestId, FLoginRefreshTokenRequest, Request);

using FLoginRefreshTokenFullResponse = FBeamFullResponse<FLoginRefreshTokenRequest, FLoginRefreshTokenResponse>;
DECLARE_DELEGATE_OneParam(FOnLoginRefreshTokenFullResponse, FLoginRefreshTokenFullResponse);
