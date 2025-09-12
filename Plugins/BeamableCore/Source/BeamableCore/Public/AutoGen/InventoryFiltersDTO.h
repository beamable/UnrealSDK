#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalContentTagFilter.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfPropertyFilterDTO.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalTimeRange.h"

#include "InventoryFiltersDTO.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UInventoryFiltersDTO : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Tag Filter", Category="Beam")
	FOptionalContentTagFilter ContentTagFilter = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created At", Category="Beam")
	FOptionalTimeRange CreatedAt = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Updated At", Category="Beam")
	FOptionalTimeRange UpdatedAt = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Properties", Category="Beam")
	FOptionalArrayOfPropertyFilterDTO Properties = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};