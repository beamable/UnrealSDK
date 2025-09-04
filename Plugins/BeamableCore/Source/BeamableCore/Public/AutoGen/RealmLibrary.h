#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Realm.h"

#include "RealmLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="Realm To JSON String")
	static FString RealmToJsonString(const URealm* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make Realm", meta=(DefaultToSelf="Outer", AdvancedDisplay="bIsArchived, bSharded, Name, Secret, Plan, DisplayName, Parent, Children, Config, Outer", NativeMakeFunc))
	static URealm* Make(FOptionalBool bIsArchived, FOptionalBool bSharded, FOptionalString Name, FOptionalString Secret, FOptionalString Plan, FOptionalString DisplayName, FOptionalString Parent, FOptionalArrayOfString Children, FOptionalMapOfString Config, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break Realm", meta=(NativeBreakFunc))
	static void Break(const URealm* Serializable, FOptionalBool& bIsArchived, FOptionalBool& bSharded, FOptionalString& Name, FOptionalString& Secret, FOptionalString& Plan, FOptionalString& DisplayName, FOptionalString& Parent, FOptionalArrayOfString& Children, FOptionalMapOfString& Config);
};