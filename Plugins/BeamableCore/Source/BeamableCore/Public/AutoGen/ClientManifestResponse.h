#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/ClientContentInfo.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"

#include "ClientManifestResponse.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UClientManifestResponse : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Items", Category="Beam")
	TArray<UClientContentInfo*> Items = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created At", Category="Beam")
	FOptionalInt64 CreatedAt = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Latest Update", Category="Beam")
	FOptionalInt64 LatestUpdate = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};