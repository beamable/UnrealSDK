#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "CustomerActorAliasAvailableResponse.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UCustomerActorAliasAvailableResponse : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Alias", Category="Beam")
	FString Alias = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Available", Category="Beam")
	bool bAvailable = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Customer Id", Category="Beam")
	FOptionalString CustomerId = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};