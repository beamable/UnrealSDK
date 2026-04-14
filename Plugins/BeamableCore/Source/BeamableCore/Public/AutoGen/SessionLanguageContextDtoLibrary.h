#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SessionLanguageContextDto.h"

#include "SessionLanguageContextDtoLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USessionLanguageContextDtoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Json", DisplayName="SessionLanguageContextDto To JSON String")
	static FString SessionLanguageContextDtoToJsonString(const USessionLanguageContextDto* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Make SessionLanguageContextDto", meta=(DefaultToSelf="Outer", AdvancedDisplay="Code, Ctx, Outer", NativeMakeFunc))
	static USessionLanguageContextDto* Make(FOptionalString Code, FOptionalString Ctx, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Break SessionLanguageContextDto", meta=(NativeBreakFunc))
	static void Break(const USessionLanguageContextDto* Serializable, FOptionalString& Code, FOptionalString& Ctx);
};