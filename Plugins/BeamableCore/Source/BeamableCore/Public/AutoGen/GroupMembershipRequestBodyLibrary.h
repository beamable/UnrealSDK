#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GroupMembershipRequestBody.h"

#include "GroupMembershipRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupMembershipRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Json", DisplayName="GroupMembershipRequestBody To JSON String")
	static FString GroupMembershipRequestBodyToJsonString(const UGroupMembershipRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Make GroupMembershipRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Successor, Score, SubGroup, Outer", NativeMakeFunc))
	static UGroupMembershipRequestBody* Make(EBeamGroupType Type, int64 Group, FOptionalInt64 Successor, FOptionalInt64 Score, FOptionalInt64 SubGroup, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Break GroupMembershipRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGroupMembershipRequestBody* Serializable, EBeamGroupType& Type, int64& Group, FOptionalInt64& Successor, FOptionalInt64& Score, FOptionalInt64& SubGroup);
};