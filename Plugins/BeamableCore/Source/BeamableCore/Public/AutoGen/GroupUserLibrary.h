#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GroupUser.h"

#include "GroupUserLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupUserLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Json", DisplayName="GroupUser To JSON String")
	static FString GroupUserToJsonString(const UGroupUser* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Make GroupUser", meta=(DefaultToSelf="Outer", AdvancedDisplay="InFlight, Scores, Outer", NativeMakeFunc))
	static UGroupUser* Make(int64 GamerTag, int64 Updated, UGroupMemberInfo* Member, TArray<UGroupUserMember*> AllGroups, FOptionalArrayOfInFlightMessage InFlight, FOptionalArrayOfGroupScoreBinding Scores, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Break GroupUser", meta=(NativeBreakFunc))
	static void Break(const UGroupUser* Serializable, int64& GamerTag, int64& Updated, UGroupMemberInfo*& Member, TArray<UGroupUserMember*>& AllGroups, FOptionalArrayOfInFlightMessage& InFlight, FOptionalArrayOfGroupScoreBinding& Scores);
};