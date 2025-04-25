#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoBasicURLResponse.h"

#include "BeamoBasicURLResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoBasicURLResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoBasicURLResponse To JSON String")
	static FString BeamoBasicURLResponseToJsonString(const UBeamoBasicURLResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoBasicURLResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBeamoBasicURLResponse* Make(FString ServiceName, TArray<UUploadURL*> S3URLs, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoBasicURLResponse", meta=(NativeBreakFunc))
	static void Break(const UBeamoBasicURLResponse* Serializable, FString& ServiceName, TArray<UUploadURL*>& S3URLs);
};