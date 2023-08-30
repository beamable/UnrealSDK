#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ProjectView.h"

#include "ProjectViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UProjectViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ProjectView To JSON String")
	static FString ProjectViewToJsonString(const UProjectView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ProjectView", meta=(DefaultToSelf="Outer", AdvancedDisplay="bArchived, bSharded, Secret, Parent, Children, Cid, Outer", NativeMakeFunc))
	static UProjectView* Make(FString ProjectName, FBeamPid Pid, FOptionalBool bArchived, FOptionalBool bSharded, FOptionalString Secret, FOptionalBeamPid Parent, FOptionalBeamPid Children, FOptionalBeamCid Cid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ProjectView", meta=(NativeBreakFunc))
	static void Break(const UProjectView* Serializable, FString& ProjectName, FBeamPid& Pid, FOptionalBool& bArchived, FOptionalBool& bSharded, FOptionalString& Secret, FOptionalBeamPid& Parent, FOptionalBeamPid& Children, FOptionalBeamCid& Cid);
};