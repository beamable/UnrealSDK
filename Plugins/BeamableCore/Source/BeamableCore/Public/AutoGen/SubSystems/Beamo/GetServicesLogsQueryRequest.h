
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/BeamoV2SignedRequestBody.h"

#include "GetServicesLogsQueryRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetServicesLogsQueryRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Query Id", Category="Beam")
	FString QueryId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetServicesLogsQueryRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make GetServicesLogsQuery",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetServicesLogsQueryRequest* Make(FString _QueryId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetServicesLogsQuerySuccess, FBeamRequestContext, Context, UGetServicesLogsQueryRequest*, Request, UBeamoV2SignedRequestBody*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetServicesLogsQueryError, FBeamRequestContext, Context, UGetServicesLogsQueryRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetServicesLogsQueryComplete, FBeamRequestContext, Context, UGetServicesLogsQueryRequest*, Request);

using FGetServicesLogsQueryFullResponse = FBeamFullResponse<UGetServicesLogsQueryRequest*, UBeamoV2SignedRequestBody*>;
DECLARE_DELEGATE_OneParam(FOnGetServicesLogsQueryFullResponse, FGetServicesLogsQueryFullResponse);
