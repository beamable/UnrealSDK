#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CustomerActorUpdateGameHierarchyRequestBody.h"

#include "CustomerActorUpdateGameHierarchyRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCustomerActorUpdateGameHierarchyRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="CustomerActorUpdateGameHierarchyRequestBody To JSON String")
	static FString CustomerActorUpdateGameHierarchyRequestBodyToJsonString(const UCustomerActorUpdateGameHierarchyRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make CustomerActorUpdateGameHierarchyRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCustomerActorUpdateGameHierarchyRequestBody* Make(TArray<URealmView*> Realms, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break CustomerActorUpdateGameHierarchyRequestBody", meta=(NativeBreakFunc))
	static void Break(const UCustomerActorUpdateGameHierarchyRequestBody* Serializable, TArray<URealmView*>& Realms);
};