#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicUpdateGameHierarchyRequestBody.h"

#include "RealmsBasicUpdateGameHierarchyRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmsBasicUpdateGameHierarchyRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="RealmsBasicUpdateGameHierarchyRequestBody To JSON String")
	static FString RealmsBasicUpdateGameHierarchyRequestBodyToJsonString(const URealmsBasicUpdateGameHierarchyRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make RealmsBasicUpdateGameHierarchyRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URealmsBasicUpdateGameHierarchyRequestBody* Make(FBeamPid RootPID, TArray<UProjectView*> Projects, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break RealmsBasicUpdateGameHierarchyRequestBody", meta=(NativeBreakFunc))
	static void Break(const URealmsBasicUpdateGameHierarchyRequestBody* Serializable, FBeamPid& RootPID, TArray<UProjectView*>& Projects);
};