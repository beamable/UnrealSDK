#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"


#include "ScheduleDefinition.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UScheduleDefinition : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Day Of Week", Category="Beam")
	TArray<FString> DayOfWeek = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Minute", Category="Beam")
	TArray<FString> Minute = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Day Of Month", Category="Beam")
	TArray<FString> DayOfMonth = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Year", Category="Beam")
	TArray<FString> Year = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Hour", Category="Beam")
	TArray<FString> Hour = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Second", Category="Beam")
	TArray<FString> Second = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Month", Category="Beam")
	TArray<FString> Month = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};