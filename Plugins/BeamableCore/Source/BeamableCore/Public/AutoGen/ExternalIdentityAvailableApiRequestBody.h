#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "ExternalIdentityAvailableApiRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UExternalIdentityAvailableApiRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Provider Service", Category="Beam")
	FString ProviderService = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="User Id", Category="Beam")
	FString UserId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Provider Namespace", Category="Beam")
	FOptionalString ProviderNamespace = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};