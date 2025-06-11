#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetChampionsResponse.h"

#include "GetChampionsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetChampionsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Json", DisplayName="GetChampionsResponse To JSON String")
	static FString GetChampionsResponseToJsonString(const UGetChampionsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make GetChampionsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetChampionsResponse* Make(TArray<UChampionScore*> Entries, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Break GetChampionsResponse", meta=(NativeBreakFunc))
	static void Break(const UGetChampionsResponse* Serializable, TArray<UChampionScore*>& Entries);
};