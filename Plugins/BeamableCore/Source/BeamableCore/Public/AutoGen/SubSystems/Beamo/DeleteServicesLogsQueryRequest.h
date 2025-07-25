
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse.h"

#include "DeleteServicesLogsQueryRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteServicesLogsQueryRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Query Id", Category="Beam")
	FString QueryId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UDeleteServicesLogsQueryRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make DeleteServicesLogsQuery",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteServicesLogsQueryRequest* Make(FString _QueryId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteServicesLogsQuerySuccess, FBeamRequestContext, Context, UDeleteServicesLogsQueryRequest*, Request, UBeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteServicesLogsQueryError, FBeamRequestContext, Context, UDeleteServicesLogsQueryRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteServicesLogsQueryComplete, FBeamRequestContext, Context, UDeleteServicesLogsQueryRequest*, Request);

using FDeleteServicesLogsQueryFullResponse = FBeamFullResponse<UDeleteServicesLogsQueryRequest*, UBeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteServicesLogsQueryFullResponse, FDeleteServicesLogsQueryFullResponse);
