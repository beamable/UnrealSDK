#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GroupCreate.h"

#include "GroupCreateLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupCreateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Json", DisplayName="GroupCreate To JSON String")
	static FString GroupCreateToJsonString(const UGroupCreate* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Make GroupCreate", meta=(DefaultToSelf="Outer", AdvancedDisplay="Tag, ClientData, Time, Group, Scores, Outer", NativeMakeFunc))
	static UGroupCreate* Make(FString Name, FString EnrollmentType, int64 Requirement, EBeamGroupType Type, int32 MaxSize, FOptionalString Tag, FOptionalString ClientData, FOptionalInt64 Time, FOptionalInt64 Group, FOptionalArrayOfGroupScoreBinding Scores, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Break GroupCreate", meta=(NativeBreakFunc))
	static void Break(const UGroupCreate* Serializable, FString& Name, FString& EnrollmentType, int64& Requirement, EBeamGroupType& Type, int32& MaxSize, FOptionalString& Tag, FOptionalString& ClientData, FOptionalInt64& Time, FOptionalInt64& Group, FOptionalArrayOfGroupScoreBinding& Scores);
};