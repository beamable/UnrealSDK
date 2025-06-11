#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"

#include "TokenResponse.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UTokenResponse : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Expires In", Category="Beam")
	int64 ExpiresIn = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Token Type", Category="Beam")
	FString TokenType = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Access Token", Category="Beam")
	FOptionalString AccessToken = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Refresh Token", Category="Beam")
	FOptionalString RefreshToken = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Challenge Token", Category="Beam")
	FOptionalString ChallengeToken = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scopes", Category="Beam")
	FOptionalArrayOfString Scopes = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};