#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RoleAssociation.h"

#include "RoleAssociationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URoleAssociationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="RoleAssociation To JSON String")
	static FString RoleAssociationToJsonString(const URoleAssociation* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make RoleAssociation", meta=(DefaultToSelf="Outer", AdvancedDisplay="RealmId, RoleString, Outer", NativeMakeFunc))
	static URoleAssociation* Make(FOptionalString RealmId, FOptionalString RoleString, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break RoleAssociation", meta=(NativeBreakFunc))
	static void Break(const URoleAssociation* Serializable, FOptionalString& RealmId, FOptionalString& RoleString);
};