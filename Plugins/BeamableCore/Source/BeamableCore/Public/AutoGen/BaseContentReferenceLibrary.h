#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BaseContentReference.h"

#include "BaseContentReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBaseContentReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="BaseContentReference To JSON String")
	static FString BaseContentReferenceToJsonString(const UBaseContentReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make BaseContentReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBaseContentReference* Make(UContentReference* Content, UTextReference* Text, UBinaryReference* Binary, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break BaseContentReference", meta=(NativeBreakFunc))
	static void Break(const UBaseContentReference* Serializable, UContentReference*& Content, UTextReference*& Text, UBinaryReference*& Binary);
};