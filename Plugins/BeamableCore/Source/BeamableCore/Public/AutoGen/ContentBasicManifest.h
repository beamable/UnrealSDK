#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/BaseContentReference.h"
#include "BeamBackend/SemanticTypes/BeamContentManifestId.h"

#include "ContentBasicManifest.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UContentBasicManifest : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FBeamContentManifestId Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Checksum", Category="Beam")
	FString Checksum = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created", Category="Beam")
	int64 Created = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="References", Category="Beam")
	TArray<UBaseContentReference*> References = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Archived", Category="Beam")
	FOptionalBool bArchived = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};