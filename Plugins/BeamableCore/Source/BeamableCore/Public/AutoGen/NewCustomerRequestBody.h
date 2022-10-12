
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalBool.h"

#include "NewCustomerRequestBody.generated.h"

UCLASS(BlueprintType)
class UNewCustomerRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Project Name")
	FString ProjectName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Email")
	FString Email;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Customer Name")
	FOptionalString CustomerName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Hierarchy")
	FOptionalBool bHierarchy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Alias")
	FOptionalString Alias;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Password")
	FString Password;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};