
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "PASuggestedIndex.generated.h"

UCLASS(BlueprintType)
class UPASuggestedIndex : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Weight")
	FString Weight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Impact")
	TArray<FString> Impact;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Namespace")
	FString Namespace;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Index")
	TArray<FString> Index;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};