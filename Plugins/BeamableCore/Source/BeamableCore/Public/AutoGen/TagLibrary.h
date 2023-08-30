#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Tag.h"

#include "TagLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTagLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - Tag To JSON String")
	static FString TagToJsonString(const UTag* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make Tag", meta=(DefaultToSelf="Outer", AdvancedDisplay="Name, Value, Outer", NativeMakeFunc))
	static UTag* Make(FOptionalString Name, FOptionalString Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break Tag", meta=(NativeBreakFunc))
	static void Break(const UTag* Serializable, FOptionalString& Name, FOptionalString& Value);
};