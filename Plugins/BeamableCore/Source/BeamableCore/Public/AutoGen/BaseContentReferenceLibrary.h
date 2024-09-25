#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/BaseContentReference.h"

#include "BaseContentReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBaseContentReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - BaseContentReference To JSON String")
	static FString BaseContentReferenceToJsonString(const UBaseContentReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make BaseContentReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBaseContentReference* Make(UContentReference* Content, UTextReference* Text, UBinaryReference* Binary, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break BaseContentReference", meta=(NativeBreakFunc))
	static void Break(const UBaseContentReference* Serializable, UContentReference*& Content, UTextReference*& Text, UBinaryReference*& Binary);
};