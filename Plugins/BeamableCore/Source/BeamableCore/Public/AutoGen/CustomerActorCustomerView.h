#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfRealmView.h"

#include "CustomerActorCustomerView.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UCustomerActorCustomerView : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Customer Id", Category="Beam")
	FString CustomerId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Alias", Category="Beam")
	FOptionalString Alias = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Realms", Category="Beam")
	FOptionalArrayOfRealmView Realms = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};