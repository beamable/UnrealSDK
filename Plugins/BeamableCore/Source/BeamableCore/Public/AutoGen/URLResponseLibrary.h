
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/URLResponse.h"

#include "URLResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UURLResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - URLResponse To JSON String")
	static FString URLResponseToJsonString(const UURLResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make URLResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UURLResponse* Make(FString Url, FString ObjectKey, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break URLResponse", meta=(NativeBreakFunc))
	static void Break(const UURLResponse* Serializable, FString& Url, FString& ObjectKey);
};