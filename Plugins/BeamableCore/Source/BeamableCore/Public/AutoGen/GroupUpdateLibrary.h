#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GroupUpdate.h"

#include "GroupUpdateLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupUpdateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Groups|Utils|Json", DisplayName="GroupUpdate To JSON String")
	static FString GroupUpdateToJsonString(const UGroupUpdate* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Groups|Utils|Make/Break", DisplayName="Make GroupUpdate", meta=(DefaultToSelf="Outer", AdvancedDisplay="Name, EnrollmentType, Tag, Slogan, Requirement, Motd, ClientData, SubGroup, Outer", NativeMakeFunc))
	static UGroupUpdate* Make(FOptionalString Name, FOptionalString EnrollmentType, FOptionalString Tag, FOptionalString Slogan, FOptionalInt64 Requirement, FOptionalString Motd, FOptionalString ClientData, FOptionalInt64 SubGroup, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Groups|Utils|Make/Break", DisplayName="Break GroupUpdate", meta=(NativeBreakFunc))
	static void Break(const UGroupUpdate* Serializable, FOptionalString& Name, FOptionalString& EnrollmentType, FOptionalString& Tag, FOptionalString& Slogan, FOptionalInt64& Requirement, FOptionalString& Motd, FOptionalString& ClientData, FOptionalInt64& SubGroup);
};