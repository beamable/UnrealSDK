
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalInt64.h"

#include "ProjectView.generated.h"

UCLASS(BlueprintType)
class UProjectView : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Secret")
	FOptionalString Secret;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Parent")
	FOptionalString Parent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Children")
	FOptionalArrayOfString Children;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Project Name")
	FString ProjectName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Archived")
	FOptionalBool bArchived;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cid")
	FOptionalInt64 Cid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pid")
	FString Pid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Sharded")
	FOptionalBool bSharded;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};