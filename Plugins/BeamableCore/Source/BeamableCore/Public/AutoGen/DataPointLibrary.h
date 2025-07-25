#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/DataPoint.h"

#include "DataPointLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDataPointLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="DataPoint To JSON String")
	static FString DataPointToJsonString(const UDataPoint* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make DataPoint", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UDataPoint* Make(FString Timestamp, FString Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break DataPoint", meta=(NativeBreakFunc))
	static void Break(const UDataPoint* Serializable, FString& Timestamp, FString& Value);
};