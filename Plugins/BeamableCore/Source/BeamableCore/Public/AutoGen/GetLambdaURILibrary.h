#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetLambdaURI.h"

#include "GetLambdaURILibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetLambdaURILibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="GetLambdaURI To JSON String")
	static FString GetLambdaURIToJsonString(const UGetLambdaURI* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make GetLambdaURI", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetLambdaURI* Make(FString Uri, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break GetLambdaURI", meta=(NativeBreakFunc))
	static void Break(const UGetLambdaURI* Serializable, FString& Uri);
};