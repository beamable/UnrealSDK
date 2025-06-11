#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/ContentMeta.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfMapOfContentMeta.h"

#include "ContentDefinition.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UContentDefinition : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FBeamContentId Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Checksum", Category="Beam")
	FString Checksum = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Properties", Category="Beam")
	TMap<FString, UContentMeta*> Properties = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tags", Category="Beam")
	FOptionalArrayOfString Tags = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Variants", Category="Beam")
	FOptionalArrayOfMapOfContentMeta Variants = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};