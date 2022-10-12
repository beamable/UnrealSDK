
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "ScheduleDefinition.generated.h"

UCLASS(BlueprintType)
class UScheduleDefinition : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Day Of Week")
	TArray<FString> DayOfWeek;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Minute")
	TArray<FString> Minute;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Day Of Month")
	TArray<FString> DayOfMonth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Year")
	TArray<FString> Year;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Hour")
	TArray<FString> Hour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Second")
	TArray<FString> Second;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Month")
	TArray<FString> Month;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};