
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/BeamoV2StartServiceLogsRequestBody.h"
#include "BeamableCore/Public/AutoGen/BeamoV2QueryResponse.h"

#include "PostServicesLogsQueryRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostServicesLogsQueryRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Name", Category="Beam")
	FString ServiceName = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UBeamoV2StartServiceLogsRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostServicesLogsQueryRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PostServicesLogsQuery",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="Body_ServiceName,_StartTime,_EndTime,_Order,_Limit,_Filters,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostServicesLogsQueryRequest* Make(FString _ServiceName, FOptionalString Body_ServiceName, FOptionalDateTime _StartTime, FOptionalDateTime _EndTime, FOptionalBeamoV2OrderDirection _Order, FOptionalInt32 _Limit, FOptionalArrayOfString _Filters, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostServicesLogsQuerySuccess, FBeamRequestContext, Context, UPostServicesLogsQueryRequest*, Request, UBeamoV2QueryResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostServicesLogsQueryError, FBeamRequestContext, Context, UPostServicesLogsQueryRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostServicesLogsQueryComplete, FBeamRequestContext, Context, UPostServicesLogsQueryRequest*, Request);

using FPostServicesLogsQueryFullResponse = FBeamFullResponse<UPostServicesLogsQueryRequest*, UBeamoV2QueryResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostServicesLogsQueryFullResponse, FPostServicesLogsQueryFullResponse);
