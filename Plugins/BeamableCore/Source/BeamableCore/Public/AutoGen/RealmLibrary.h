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

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make Realm", meta=(DefaultToSelf="Outer", AdvancedDisplay="bIsArchived, bSharded, Secret, DisplayName, Parent, Created, Children, Config, CustomCharts, Outer", NativeMakeFunc))
	static URealm* Make(FString Name, FString Plan, FOptionalBool bIsArchived, FOptionalBool bSharded, FOptionalString Secret, FOptionalString DisplayName, FOptionalString Parent, FOptionalDateTime Created, FOptionalArrayOfString Children, FOptionalMapOfString Config, FOptionalMapOfString CustomCharts, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break Realm", meta=(NativeBreakFunc))
	static void Break(const URealm* Serializable, FString& Name, FString& Plan, FOptionalBool& bIsArchived, FOptionalBool& bSharded, FOptionalString& Secret, FOptionalString& DisplayName, FOptionalString& Parent, FOptionalDateTime& Created, FOptionalArrayOfString& Children, FOptionalMapOfString& Config, FOptionalMapOfString& CustomCharts);
};