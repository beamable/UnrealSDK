#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"

#include "GroupUpdate.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UGroupUpdate : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FOptionalString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Enrollment Type", Category="Beam")
	FOptionalString EnrollmentType = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tag", Category="Beam")
	FOptionalString Tag = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Slogan", Category="Beam")
	FOptionalString Slogan = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Requirement", Category="Beam")
	FOptionalInt64 Requirement = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Motd", Category="Beam")
	FOptionalString Motd = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Client Data", Category="Beam")
	FOptionalString ClientData = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sub Group", Category="Beam")
	FOptionalInt64 SubGroup = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};