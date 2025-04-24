#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GroupMemberInfo.h"

#include "GroupMemberInfoLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupMemberInfoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Json", DisplayName="GroupMemberInfo To JSON String")
	static FString GroupMemberInfoToJsonString(const UGroupMemberInfo* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Make GroupMemberInfo", meta=(DefaultToSelf="Outer", AdvancedDisplay="Guild, Subgroup, Outer", NativeMakeFunc))
	static UGroupMemberInfo* Make(FOptionalArrayOfGroupUserMember Guild, FOptionalArrayOfGroupUserMember Subgroup, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Break GroupMemberInfo", meta=(NativeBreakFunc))
	static void Break(const UGroupMemberInfo* Serializable, FOptionalArrayOfGroupUserMember& Guild, FOptionalArrayOfGroupUserMember& Subgroup);
};