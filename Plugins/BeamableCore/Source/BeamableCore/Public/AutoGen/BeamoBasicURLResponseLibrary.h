#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoBasicURLResponse.h"

#include "BeamoBasicURLResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoBasicURLResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - BeamoBasicURLResponse To JSON String")
	static FString BeamoBasicURLResponseToJsonString(const UBeamoBasicURLResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make BeamoBasicURLResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBeamoBasicURLResponse* Make(FString ServiceName, TArray<UUploadURL*> S3URLs, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break BeamoBasicURLResponse", meta=(NativeBreakFunc))
	static void Break(const UBeamoBasicURLResponse* Serializable, FString& ServiceName, TArray<UUploadURL*>& S3URLs);
};