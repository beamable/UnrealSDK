#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetChampionsRequestBody.h"

#include "GetChampionsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetChampionsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Json", DisplayName="GetChampionsRequestBody To JSON String")
	static FString GetChampionsRequestBodyToJsonString(const UGetChampionsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make GetChampionsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="ContentId, Outer", NativeMakeFunc))
	static UGetChampionsRequestBody* Make(FString TournamentId, int32 Cycles, FOptionalString ContentId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Break GetChampionsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetChampionsRequestBody* Serializable, FString& TournamentId, int32& Cycles, FOptionalString& ContentId);
};