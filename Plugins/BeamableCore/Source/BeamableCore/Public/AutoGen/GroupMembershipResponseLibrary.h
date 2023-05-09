#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GroupMembershipResponse.h"

#include "GroupMembershipResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupMembershipResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GroupMembershipResponse To JSON String")
	static FString GroupMembershipResponseToJsonString(const UGroupMembershipResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GroupMembershipResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="GamerTag, Outer", NativeMakeFunc))
	static UGroupMembershipResponse* Make(bool bMember, EGroupType Type, UGroupMetaData* Group, TArray<int64> SubGroups, FOptionalInt64 GamerTag, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GroupMembershipResponse", meta=(NativeBreakFunc))
	static void Break(const UGroupMembershipResponse* Serializable, bool& bMember, EGroupType& Type, UGroupMetaData*& Group, TArray<int64>& SubGroups, FOptionalInt64& GamerTag);
};