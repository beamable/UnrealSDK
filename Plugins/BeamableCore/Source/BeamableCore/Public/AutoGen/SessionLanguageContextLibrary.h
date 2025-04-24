#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SessionLanguageContext.h"

#include "SessionLanguageContextLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USessionLanguageContextLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Json", DisplayName="SessionLanguageContext To JSON String")
	static FString SessionLanguageContextToJsonString(const USessionLanguageContext* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Make SessionLanguageContext", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USessionLanguageContext* Make(FString Code, FString Ctx, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Break SessionLanguageContext", meta=(NativeBreakFunc))
	static void Break(const USessionLanguageContext* Serializable, FString& Code, FString& Ctx);
};