#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"

#include "CustomerActorNewCustomerRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UCustomerActorNewCustomerRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Realm Name", Category="Beam")
	FString RealmName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Email", Category="Beam")
	FString Email = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Password", Category="Beam")
	FString Password = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Hierarchy", Category="Beam")
	FOptionalBool bHierarchy = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Customer Name", Category="Beam")
	FOptionalString CustomerName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Alias", Category="Beam")
	FOptionalString Alias = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};