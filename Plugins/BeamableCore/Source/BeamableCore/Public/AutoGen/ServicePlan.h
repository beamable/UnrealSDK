#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/DataDomain.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalServiceLimits.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"

#include "ServicePlan.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UServicePlan : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Data Domain", Category="Beam")
	UDataDomain* DataDomain = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Min Customer Status Saved", Category="Beam")
	FOptionalString MinCustomerStatusSaved = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limits", Category="Beam")
	FOptionalServiceLimits Limits = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created", Category="Beam")
	FOptionalInt64 Created = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};