
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfMailObjectMessage.h"

#include "MailSearchResponseClause.generated.h"

UCLASS(BlueprintType)
class UMailSearchResponseClause : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Count")
	int64 Count;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content")
	FOptionalArrayOfMailObjectMessage Content;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};