#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/HtmlResponse.h"

#include "HtmlResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UHtmlResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="HtmlResponse To JSON String")
	static FString HtmlResponseToJsonString(const UHtmlResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make HtmlResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UHtmlResponse* Make(FString Html, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break HtmlResponse", meta=(NativeBreakFunc))
	static void Break(const UHtmlResponse* Serializable, FString& Html);
};