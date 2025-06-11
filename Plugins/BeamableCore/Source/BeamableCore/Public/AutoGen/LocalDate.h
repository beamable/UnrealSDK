#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/IsoChronology.h"
#include "BeamableCore/Public/AutoGen/Era.h"

#include "LocalDate.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API ULocalDate : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Leap Year", Category="Beam")
	bool bLeapYear = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Day Of Year", Category="Beam")
	int32 DayOfYear = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Chronology", Category="Beam")
	UIsoChronology* Chronology = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Day Of Week", Category="Beam")
	FString DayOfWeek = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Month Value", Category="Beam")
	int32 MonthValue = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Day Of Month", Category="Beam")
	int32 DayOfMonth = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Year", Category="Beam")
	int32 Year = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Era", Category="Beam")
	UEra* Era = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Month", Category="Beam")
	FString Month = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};