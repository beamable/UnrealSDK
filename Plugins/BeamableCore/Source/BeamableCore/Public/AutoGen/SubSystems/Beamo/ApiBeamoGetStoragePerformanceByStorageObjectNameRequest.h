
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalDateTime.h"
#include "BeamableCore/Public/AutoGen/BeamoV2StoragePerformance.h"

#include "ApiBeamoGetStoragePerformanceByStorageObjectNameRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiBeamoGetStoragePerformanceByStorageObjectNameRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Storage Object Name", Category="Beam")
	FString StorageObjectName = {};
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Period", Category="Beam")
	FOptionalString Period = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start Time", Category="Beam")
	FOptionalDateTime StartTime = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="End Time", Category="Beam")
	FOptionalDateTime EndTime = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Granularity", Category="Beam")
	FOptionalString Granularity = {};

	// Body Params
	

	// Beam Base Request Declaration
	UApiBeamoGetStoragePerformanceByStorageObjectNameRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ApiBeamoGetStoragePerformanceByStorageObjectName",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Period,_StartTime,_EndTime,_Granularity,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiBeamoGetStoragePerformanceByStorageObjectNameRequest* Make(FString _StorageObjectName, FOptionalString _Period, FOptionalDateTime _StartTime, FOptionalDateTime _EndTime, FOptionalString _Granularity, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiBeamoGetStoragePerformanceByStorageObjectNameSuccess, FBeamRequestContext, Context, UApiBeamoGetStoragePerformanceByStorageObjectNameRequest*, Request, UBeamoV2StoragePerformance*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiBeamoGetStoragePerformanceByStorageObjectNameError, FBeamRequestContext, Context, UApiBeamoGetStoragePerformanceByStorageObjectNameRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiBeamoGetStoragePerformanceByStorageObjectNameComplete, FBeamRequestContext, Context, UApiBeamoGetStoragePerformanceByStorageObjectNameRequest*, Request);

using FApiBeamoGetStoragePerformanceByStorageObjectNameFullResponse = FBeamFullResponse<UApiBeamoGetStoragePerformanceByStorageObjectNameRequest*, UBeamoV2StoragePerformance*>;
DECLARE_DELEGATE_OneParam(FOnApiBeamoGetStoragePerformanceByStorageObjectNameFullResponse, FApiBeamoGetStoragePerformanceByStorageObjectNameFullResponse);
