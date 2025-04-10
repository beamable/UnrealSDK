#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ScheduleDefinition.h"

#include "ScheduleDefinitionLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UScheduleDefinitionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Json", DisplayName="ScheduleDefinition To JSON String")
	static FString ScheduleDefinitionToJsonString(const UScheduleDefinition* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Make ScheduleDefinition", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UScheduleDefinition* Make(TArray<FString> DayOfWeek, TArray<FString> Minute, TArray<FString> DayOfMonth, TArray<FString> Year, TArray<FString> Hour, TArray<FString> Second, TArray<FString> Month, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Break ScheduleDefinition", meta=(NativeBreakFunc))
	static void Break(const UScheduleDefinition* Serializable, TArray<FString>& DayOfWeek, TArray<FString>& Minute, TArray<FString>& DayOfMonth, TArray<FString>& Year, TArray<FString>& Hour, TArray<FString>& Second, TArray<FString>& Month);
};