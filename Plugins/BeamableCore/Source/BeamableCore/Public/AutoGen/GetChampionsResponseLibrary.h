#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetChampionsResponse.h"

#include "GetChampionsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetChampionsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetChampionsResponse To JSON String")
	static FString GetChampionsResponseToJsonString(const UGetChampionsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetChampionsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetChampionsResponse* Make(TArray<UChampionScore*> Entries, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetChampionsResponse", meta=(NativeBreakFunc))
	static void Break(const UGetChampionsResponse* Serializable, TArray<UChampionScore*>& Entries);
};