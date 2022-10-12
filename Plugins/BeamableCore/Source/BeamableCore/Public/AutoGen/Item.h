
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/ItemProperty.h"

#include "Item.generated.h"

UCLASS(BlueprintType)
class UItem : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Updated At")
	FOptionalInt64 UpdatedAt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Proxy Id")
	FOptionalString ProxyId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id")
	int64 Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Properties")
	TArray<UItemProperty*> Properties;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created At")
	FOptionalInt64 CreatedAt;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};