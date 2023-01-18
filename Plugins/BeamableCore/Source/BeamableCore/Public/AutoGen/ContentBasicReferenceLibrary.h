
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/ContentBasicReference.h"

#include "ContentBasicReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UContentBasicReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ContentBasicReference To JSON String")
	static FString ContentBasicReferenceToJsonString(const UContentBasicReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ContentBasicReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UContentBasicReference* Make(FString ContentPrefix, FString Visibility, EContentType Type, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ContentBasicReference", meta=(NativeBreakFunc))
	static void Break(const UContentBasicReference* Serializable, FString& ContentPrefix, FString& Visibility, EContentType& Type);
};