#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GroupSearchRequestBody.h"

#include "GroupSearchRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupSearchRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Json", DisplayName="GroupSearchRequestBody To JSON String")
	static FString GroupSearchRequestBodyToJsonString(const UGroupSearchRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Make GroupSearchRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bHasSlots, bSubGroup, Name, ScoreMin, SortField, UserScore, EnrollmentTypes, Offset, ScoreMax, SortValue, Limit, Outer", NativeMakeFunc))
	static UGroupSearchRequestBody* Make(EBeamGroupType Type, FOptionalBool bHasSlots, FOptionalBool bSubGroup, FOptionalString Name, FOptionalInt64 ScoreMin, FOptionalString SortField, FOptionalInt64 UserScore, FOptionalString EnrollmentTypes, FOptionalInt32 Offset, FOptionalInt64 ScoreMax, FOptionalInt32 SortValue, FOptionalInt32 Limit, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Break GroupSearchRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGroupSearchRequestBody* Serializable, EBeamGroupType& Type, FOptionalBool& bHasSlots, FOptionalBool& bSubGroup, FOptionalString& Name, FOptionalInt64& ScoreMin, FOptionalString& SortField, FOptionalInt64& UserScore, FOptionalString& EnrollmentTypes, FOptionalInt32& Offset, FOptionalInt64& ScoreMax, FOptionalInt32& SortValue, FOptionalInt32& Limit);
};