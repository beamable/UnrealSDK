/**
 * This file contains all data types for back-end communication that we declare by hand
 * and expect to be excluded from the code-gen process.
 *
 * The use case for this is so that we can safely depend on them in core classes
 * that want 0-dependency to code-gen'ed types (such as BeamBackend and others).
 */

#pragma once


#include "AutoGen/TokenResponse.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamFullResponse.h"
#include "Serialization/BeamJsonSerializable.h"

#include "BeamCustomRequests.generated.h"

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


UCLASS(BlueprintType)
class ULoginRefreshTokenRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString GrantType = "refresh_token";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RefreshToken;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;
};

UCLASS(BlueprintType)
class ULoginRefreshTokenResponse : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTokenResponse* Body;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLoginRefreshTokenSuccess, int64, RequestId, ULoginRefreshTokenRequest*, Request, ULoginRefreshTokenResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLoginRefreshTokenError, int64, RequestId, ULoginRefreshTokenRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnLoginRefreshTokenComplete, int64, RequestId, ULoginRefreshTokenRequest*, Request);

using FLoginRefreshTokenFullResponse = FBeamFullResponse<ULoginRefreshTokenRequest*, ULoginRefreshTokenResponse*>;
DECLARE_DELEGATE_OneParam(FOnLoginRefreshTokenFullResponse, FLoginRefreshTokenFullResponse);