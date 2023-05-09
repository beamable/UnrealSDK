#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SetContentRequestBody.h"

#include "SetContentRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USetContentRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - SetContentRequestBody To JSON String")
	static FString SetContentRequestBodyToJsonString(const USetContentRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make SetContentRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="RootEventId, OriginType, Outer", NativeMakeFunc))
	static USetContentRequestBody* Make(UEvent* Event, FString Origin, FOptionalString RootEventId, FOptionalString OriginType, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break SetContentRequestBody", meta=(NativeBreakFunc))
	static void Break(const USetContentRequestBody* Serializable, UEvent*& Event, FString& Origin, FOptionalString& RootEventId, FOptionalString& OriginType);
};