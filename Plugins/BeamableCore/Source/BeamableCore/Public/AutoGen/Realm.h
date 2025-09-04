#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfString.h"

#include "Realm.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API URealm : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is Archived", Category="Beam")
	FOptionalBool bIsArchived = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Sharded", Category="Beam")
	FOptionalBool bSharded = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FOptionalString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Secret", Category="Beam")
	FOptionalString Secret = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Plan", Category="Beam")
	FOptionalString Plan = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Display Name", Category="Beam")
	FOptionalString DisplayName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Parent", Category="Beam")
	FOptionalString Parent = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Children", Category="Beam")
	FOptionalArrayOfString Children = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Config", Category="Beam")
	FOptionalMapOfString Config = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};