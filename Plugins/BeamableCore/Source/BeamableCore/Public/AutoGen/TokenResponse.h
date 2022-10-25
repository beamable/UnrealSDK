
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"

#include "TokenResponse.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTokenResponse : public UObject, public FBeamJsonSerializable, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Access Token", Category="Beam")
	FString AccessToken;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Expires In", Category="Beam")
	int64 ExpiresIn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Refresh Token", Category="Beam")
	FString RefreshToken;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Token Type", Category="Beam")
	FString TokenType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scopes", Category="Beam")
	FOptionalArrayOfString Scopes;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};