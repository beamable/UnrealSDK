#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Project.h"

#include "ProjectLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UProjectLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="Project To JSON String")
	static FString ProjectToJsonString(const UProject* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make Project", meta=(DefaultToSelf="Outer", AdvancedDisplay="bSharded, bSigval, DisplayName, Parent, Status, Created, Children, Config, Outer", NativeMakeFunc))
	static UProject* Make(bool bArchived, bool bRoot, FString Secret, FBeamPid Name, FString Plan, TMap<FString, FString> CustomCharts, FOptionalBool bSharded, FOptionalBool bSigval, FOptionalString DisplayName, FOptionalString Parent, FOptionalString Status, FOptionalInt64 Created, FOptionalArrayOfString Children, FOptionalMapOfString Config, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break Project", meta=(NativeBreakFunc))
	static void Break(const UProject* Serializable, bool& bArchived, bool& bRoot, FString& Secret, FBeamPid& Name, FString& Plan, TMap<FString, FString>& CustomCharts, FOptionalBool& bSharded, FOptionalBool& bSigval, FOptionalString& DisplayName, FOptionalString& Parent, FOptionalString& Status, FOptionalInt64& Created, FOptionalArrayOfString& Children, FOptionalMapOfString& Config);
};