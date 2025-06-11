#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/UpdateGameHierarchyRequestBody.h"

#include "UpdateGameHierarchyRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUpdateGameHierarchyRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="UpdateGameHierarchyRequestBody To JSON String")
	static FString UpdateGameHierarchyRequestBodyToJsonString(const UUpdateGameHierarchyRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make UpdateGameHierarchyRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UUpdateGameHierarchyRequestBody* Make(FBeamPid RootPID, TArray<UProjectView*> Projects, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break UpdateGameHierarchyRequestBody", meta=(NativeBreakFunc))
	static void Break(const UUpdateGameHierarchyRequestBody* Serializable, FBeamPid& RootPID, TArray<UProjectView*>& Projects);
};