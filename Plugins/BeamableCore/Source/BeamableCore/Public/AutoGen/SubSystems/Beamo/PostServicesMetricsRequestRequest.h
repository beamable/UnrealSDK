
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/BeamoV2GetMetricsRequestBody.h"
#include "BeamableCore/Public/AutoGen/BeamoV2SignedRequestBody.h"

#include "PostServicesMetricsRequestRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostServicesMetricsRequestRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Name", Category="Beam")
	FString ServiceName = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UBeamoV2GetMetricsRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostServicesMetricsRequestRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PostServicesMetricsRequest",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_MetricName,_StartTime,_EndTime,_Period,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostServicesMetricsRequestRequest* Make(FString _ServiceName, FOptionalString _MetricName, FOptionalDateTime _StartTime, FOptionalDateTime _EndTime, FOptionalInt32 _Period, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostServicesMetricsRequestSuccess, FBeamRequestContext, Context, UPostServicesMetricsRequestRequest*, Request, UBeamoV2SignedRequestBody*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostServicesMetricsRequestError, FBeamRequestContext, Context, UPostServicesMetricsRequestRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostServicesMetricsRequestComplete, FBeamRequestContext, Context, UPostServicesMetricsRequestRequest*, Request);

using FPostServicesMetricsRequestFullResponse = FBeamFullResponse<UPostServicesMetricsRequestRequest*, UBeamoV2SignedRequestBody*>;
DECLARE_DELEGATE_OneParam(FOnPostServicesMetricsRequestFullResponse, FPostServicesMetricsRequestFullResponse);
