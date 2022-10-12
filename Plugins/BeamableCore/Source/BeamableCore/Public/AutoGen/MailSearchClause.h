
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"
#include "AutoGen/Optionals/OptionalInt32.h"

#include "MailSearchClause.generated.h"

UCLASS(BlueprintType)
class UMailSearchClause : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="For Sender")
	FOptionalInt64 ForSender;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Only Count")
	bool bOnlyCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Categories")
	FOptionalArrayOfString Categories;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start")
	FOptionalInt64 Start;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit")
	FOptionalInt32 Limit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="States")
	FOptionalArrayOfString States;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};