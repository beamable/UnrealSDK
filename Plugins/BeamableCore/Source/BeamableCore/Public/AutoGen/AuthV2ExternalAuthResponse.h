#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"

#include "AuthV2ExternalAuthResponse.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UAuthV2ExternalAuthResponse : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Has Access Token", Category="Beam")
	FOptionalBool bHasAccessToken = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Has Challenge Token", Category="Beam")
	FOptionalBool bHasChallengeToken = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Has Expires In Ms", Category="Beam")
	FOptionalBool bHasExpiresInMs = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Has Refresh Token", Category="Beam")
	FOptionalBool bHasRefreshToken = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Access Token", Category="Beam")
	FOptionalString AccessToken = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Refresh Token", Category="Beam")
	FOptionalString RefreshToken = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Challenge Token", Category="Beam")
	FOptionalString ChallengeToken = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Expires In Ms", Category="Beam")
	FOptionalInt64 ExpiresInMs = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};