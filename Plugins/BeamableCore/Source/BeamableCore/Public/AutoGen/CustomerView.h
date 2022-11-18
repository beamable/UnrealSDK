
#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/ProjectView.h"

#include "CustomerView.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCustomerView : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cid", Category="Beam")
	int64 Cid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Projects", Category="Beam")
	TArray<UProjectView*> Projects;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Alias", Category="Beam")
	FOptionalString Alias;

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};