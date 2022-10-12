
#pragma once

#include "CoreMinimal.h"
#include "GroupUserMember.h"

#include "GroupUserMemberLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGroupUserMemberLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GroupUserMember To JSON String")
	static FString GroupUserMemberToJsonString(const UGroupUserMember* Serializable, const bool Pretty);		
};