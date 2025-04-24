#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ProjectView.h"

#include "ProjectViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UProjectViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="ProjectView To JSON String")
	static FString ProjectViewToJsonString(const UProjectView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make ProjectView", meta=(DefaultToSelf="Outer", AdvancedDisplay="bArchived, bSharded, Secret, Parent, Cid, Children, Outer", NativeMakeFunc))
	static UProjectView* Make(FString ProjectName, FBeamPid Pid, FOptionalBool bArchived, FOptionalBool bSharded, FOptionalString Secret, FOptionalBeamPid Parent, FOptionalBeamCid Cid, FOptionalArrayOfBeamPid Children, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break ProjectView", meta=(NativeBreakFunc))
	static void Break(const UProjectView* Serializable, FString& ProjectName, FBeamPid& Pid, FOptionalBool& bArchived, FOptionalBool& bSharded, FOptionalString& Secret, FOptionalBeamPid& Parent, FOptionalBeamCid& Cid, FOptionalArrayOfBeamPid& Children);
};