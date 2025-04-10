#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ContentMeta.h"

#include "ContentMetaLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UContentMetaLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="ContentMeta To JSON String")
	static FString ContentMetaToJsonString(const UContentMeta* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make ContentMeta", meta=(DefaultToSelf="Outer", AdvancedDisplay="Text, Outer", NativeMakeFunc))
	static UContentMeta* Make(EContentVisibility Visibility, FOptionalString Text, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break ContentMeta", meta=(NativeBreakFunc))
	static void Break(const UContentMeta* Serializable, EContentVisibility& Visibility, FOptionalString& Text);
};