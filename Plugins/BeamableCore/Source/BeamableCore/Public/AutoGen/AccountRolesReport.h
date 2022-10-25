
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/RealmRolesReport.h"

#include "AccountRolesReport.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAccountRolesReport : public UObject, public FBeamJsonSerializable, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Account Id", Category="Beam")
	int64 AccountId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Email", Category="Beam")
	FString Email;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Realms", Category="Beam")
	TArray<URealmRolesReport*> Realms;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};