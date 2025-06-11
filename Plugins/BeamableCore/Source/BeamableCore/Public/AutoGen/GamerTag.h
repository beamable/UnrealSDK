#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfCohortEntry.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalSessionUser.h"

#include "GamerTag.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UGamerTag : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tag", Category="Beam")
	int64 Tag = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Platform", Category="Beam")
	FString Platform = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Alias", Category="Beam")
	FOptionalString Alias = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Added", Category="Beam")
	FOptionalInt64 Added = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="User", Category="Beam")
	FOptionalSessionUser User = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Trials", Category="Beam")
	FOptionalArrayOfCohortEntry Trials = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};