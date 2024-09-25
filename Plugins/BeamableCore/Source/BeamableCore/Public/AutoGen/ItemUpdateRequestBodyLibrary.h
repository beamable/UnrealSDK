#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/ItemUpdateRequestBody.h"

#include "ItemUpdateRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UItemUpdateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ItemUpdateRequestBody To JSON String")
	static FString ItemUpdateRequestBodyToJsonString(const UItemUpdateRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ItemUpdateRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UItemUpdateRequestBody* Make(FString ContentId, int64 Id, TArray<UItemProperty*> Properties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ItemUpdateRequestBody", meta=(NativeBreakFunc))
	static void Break(const UItemUpdateRequestBody* Serializable, FString& ContentId, int64& Id, TArray<UItemProperty*>& Properties);
};