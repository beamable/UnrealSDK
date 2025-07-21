#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Dom/JsonObject.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamContentId.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamContentId.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamContentVisibility.h"

#include "ContentMeta.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UContentMeta : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	TSharedPtr<FJsonObject> Data = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Visibility", Category="Beam")
	EBeamContentVisibility Visibility = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Text", Category="Beam")
	FOptionalString Text = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Link", Category="Beam")
	FOptionalBeamContentId link = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Links", Category="Beam")
	FOptionalArrayOfBeamContentId links = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};