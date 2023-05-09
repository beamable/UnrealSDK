#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ListDefinitionsResponse.h"

#include "ListDefinitionsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UListDefinitionsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ListDefinitionsResponse To JSON String")
	static FString ListDefinitionsResponseToJsonString(const UListDefinitionsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ListDefinitionsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UListDefinitionsResponse* Make(TArray<UAnnouncementDto*> Content, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ListDefinitionsResponse", meta=(NativeBreakFunc))
	static void Break(const UListDefinitionsResponse* Serializable, TArray<UAnnouncementDto*>& Content);
};