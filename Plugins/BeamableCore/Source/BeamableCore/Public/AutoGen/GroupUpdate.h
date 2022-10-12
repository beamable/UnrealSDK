
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalInt64.h"

#include "GroupUpdate.generated.h"

UCLASS(BlueprintType)
class UGroupUpdate : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FOptionalString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Enrollment Type")
	FOptionalString EnrollmentType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tag")
	FOptionalString Tag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Slogan")
	FOptionalString Slogan;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Requirement")
	FOptionalInt64 Requirement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Motd")
	FOptionalString Motd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Client Data")
	FOptionalString ClientData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sub Group")
	FOptionalInt64 SubGroup;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};