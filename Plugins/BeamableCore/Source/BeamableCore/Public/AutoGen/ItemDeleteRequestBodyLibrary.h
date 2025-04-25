#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ItemDeleteRequestBody.h"

#include "ItemDeleteRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UItemDeleteRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Json", DisplayName="ItemDeleteRequestBody To JSON String")
	static FString ItemDeleteRequestBodyToJsonString(const UItemDeleteRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make ItemDeleteRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UItemDeleteRequestBody* Make(FString ContentId, int64 Id, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break ItemDeleteRequestBody", meta=(NativeBreakFunc))
	static void Break(const UItemDeleteRequestBody* Serializable, FString& ContentId, int64& Id);
};