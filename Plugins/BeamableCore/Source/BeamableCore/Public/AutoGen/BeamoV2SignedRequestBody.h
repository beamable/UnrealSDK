#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2StringStringKeyValuePair.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "BeamoV2SignedRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UBeamoV2SignedRequestBody : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Url", Category="Beam")
	FOptionalString Url = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Body", Category="Beam")
	FOptionalString Body = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Method", Category="Beam")
	FOptionalString Method = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Headers", Category="Beam")
	FOptionalArrayOfBeamoV2StringStringKeyValuePair Headers = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};