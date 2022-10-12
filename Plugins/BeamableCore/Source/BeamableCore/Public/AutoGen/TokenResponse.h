
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"

#include "TokenResponse.generated.h"

UCLASS(BlueprintType)
class UTokenResponse : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Access Token")
	FString AccessToken;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Expires In")
	int64 ExpiresIn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Refresh Token")
	FString RefreshToken;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scopes")
	FOptionalArrayOfString Scopes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Token Type")
	FString TokenType;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};