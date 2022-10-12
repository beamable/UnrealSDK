
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/RealmRolesReport.h"

#include "AccountRolesReport.generated.h"

UCLASS(BlueprintType)
class UAccountRolesReport : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Account Id")
	int64 AccountId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Email")
	FString Email;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Realms")
	TArray<URealmRolesReport*> Realms;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};