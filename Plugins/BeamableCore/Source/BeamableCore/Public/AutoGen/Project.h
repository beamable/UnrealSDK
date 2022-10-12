
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"
#include "AutoGen/Optionals/OptionalMapOfString.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalInt64.h"

#include "Project.generated.h"

UCLASS(BlueprintType)
class UProject : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Display Name")
	FOptionalString DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Secret")
	FString Secret;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Parent")
	FOptionalString Parent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Children")
	FOptionalArrayOfString Children;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Custom Charts")
	TMap<FString, FString> CustomCharts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Root")
	bool bRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Archived")
	bool bArchived;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Config")
	FOptionalMapOfString Config;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Status")
	FOptionalString Status;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Sharded")
	FOptionalBool bSharded;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Sigval")
	FOptionalBool bSigval;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Plan")
	FString Plan;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created")
	FOptionalInt64 Created;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};