#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ItemCreateRequestBody.h"

#include "ItemCreateRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UItemCreateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Json", DisplayName="ItemCreateRequestBody To JSON String")
	static FString ItemCreateRequestBodyToJsonString(const UItemCreateRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Make ItemCreateRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UItemCreateRequestBody* Make(FString ContentId, TArray<UItemProperty*> Properties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Break ItemCreateRequestBody", meta=(NativeBreakFunc))
	static void Break(const UItemCreateRequestBody* Serializable, FString& ContentId, TArray<UItemProperty*>& Properties);
};