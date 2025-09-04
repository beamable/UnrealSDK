#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamPromotableType.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfPromotion.h"

#include "PromotionScope.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UPromotionScope : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	EBeamPromotableType Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Promotions", Category="Beam")
	FOptionalArrayOfPromotion Promotions = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};