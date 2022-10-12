
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/TokenResponse.h"

#include "NewCustomerResponse.generated.h"

UCLASS(BlueprintType)
class UNewCustomerResponse : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Project Name")
	FString ProjectName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Alias")
	FOptionalString Alias;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cid")
	int64 Cid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pid")
	FString Pid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Token")
	UTokenResponse* Token;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};