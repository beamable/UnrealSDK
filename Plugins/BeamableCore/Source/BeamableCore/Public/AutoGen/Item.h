#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/ItemProperty.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalFederationInfo.h"

#include "Item.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UItem : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	int64 Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Properties", Category="Beam")
	TArray<UItemProperty*> Properties = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Updated At", Category="Beam")
	FOptionalInt64 UpdatedAt = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Proxy Id", Category="Beam")
	FOptionalString ProxyId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Proxy", Category="Beam")
	FOptionalFederationInfo Proxy = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created At", Category="Beam")
	FOptionalInt64 CreatedAt = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};