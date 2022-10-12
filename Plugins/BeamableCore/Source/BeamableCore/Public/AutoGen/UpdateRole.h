
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "UpdateRole.generated.h"

UCLASS(BlueprintType)
class UUpdateRole : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cid")
	FOptionalString Cid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Realm")
	FOptionalString Realm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Role")
	FOptionalString Role;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};