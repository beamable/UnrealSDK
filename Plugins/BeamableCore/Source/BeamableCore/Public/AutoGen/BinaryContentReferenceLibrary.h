#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BinaryContentReference.h"

#include "BinaryContentReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBinaryContentReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="BinaryContentReference To JSON String")
	static FString BinaryContentReferenceToJsonString(const UBinaryContentReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make BinaryContentReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBinaryContentReference* Make(FString ContentId, FString Version, FString Url, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break BinaryContentReference", meta=(NativeBreakFunc))
	static void Break(const UBinaryContentReference* Serializable, FString& ContentId, FString& Version, FString& Url);
};