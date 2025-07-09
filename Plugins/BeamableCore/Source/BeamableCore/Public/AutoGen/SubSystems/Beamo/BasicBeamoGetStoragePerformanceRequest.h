
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/PerformanceResponse.h"

#include "BasicBeamoGetStoragePerformanceRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicBeamoGetStoragePerformanceRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="End Date", Category="Beam")
	FOptionalString EndDate = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Storage Object Name", Category="Beam")
	FString StorageObjectName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Granularity", Category="Beam")
	FString Granularity = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start Date", Category="Beam")
	FOptionalString StartDate = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Period", Category="Beam")
	FOptionalString Period = {};

	// Body Params
	

	// Beam Base Request Declaration
	UBasicBeamoGetStoragePerformanceRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BasicBeamoGetStoragePerformance",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_EndDate,_StartDate,_Period,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicBeamoGetStoragePerformanceRequest* Make(FOptionalString _EndDate, FString _StorageObjectName, FString _Granularity, FOptionalString _StartDate, FOptionalString _Period, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicBeamoGetStoragePerformanceSuccess, FBeamRequestContext, Context, UBasicBeamoGetStoragePerformanceRequest*, Request, UPerformanceResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicBeamoGetStoragePerformanceError, FBeamRequestContext, Context, UBasicBeamoGetStoragePerformanceRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicBeamoGetStoragePerformanceComplete, FBeamRequestContext, Context, UBasicBeamoGetStoragePerformanceRequest*, Request);

using FBasicBeamoGetStoragePerformanceFullResponse = FBeamFullResponse<UBasicBeamoGetStoragePerformanceRequest*, UPerformanceResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicBeamoGetStoragePerformanceFullResponse, FBasicBeamoGetStoragePerformanceFullResponse);
