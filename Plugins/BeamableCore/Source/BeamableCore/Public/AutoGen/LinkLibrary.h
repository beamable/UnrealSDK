#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Link.h"

#include "LinkLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULinkLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="Link To JSON String")
	static FString LinkToJsonString(const ULink* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make Link", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULink* Make(FString Href, FString Rel, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break Link", meta=(NativeBreakFunc))
	static void Break(const ULink* Serializable, FString& Href, FString& Rel);
};