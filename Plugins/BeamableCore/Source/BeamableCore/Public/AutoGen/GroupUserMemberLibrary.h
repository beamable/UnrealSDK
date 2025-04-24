#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GroupUserMember.h"

#include "GroupUserMemberLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupUserMemberLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Json", DisplayName="GroupUserMember To JSON String")
	static FString GroupUserMemberToJsonString(const UGroupUserMember* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Make GroupUserMember", meta=(DefaultToSelf="Outer", AdvancedDisplay="Joined, Outer", NativeMakeFunc))
	static UGroupUserMember* Make(int64 Id, TArray<UGroupUserMember*> SubGroups, FOptionalInt64 Joined, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Break GroupUserMember", meta=(NativeBreakFunc))
	static void Break(const UGroupUserMember* Serializable, int64& Id, TArray<UGroupUserMember*>& SubGroups, FOptionalInt64& Joined);
};