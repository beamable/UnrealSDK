
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/BeamoV2GetAllServiceLoggingContexts.h"

#include "ApiBeamoGetServicesLogsContextRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiBeamoGetServicesLogsContextRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UApiBeamoGetServicesLogsContextRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ApiBeamoGetServicesLogsContext",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiBeamoGetServicesLogsContextRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiBeamoGetServicesLogsContextSuccess, FBeamRequestContext, Context, UApiBeamoGetServicesLogsContextRequest*, Request, UBeamoV2GetAllServiceLoggingContexts*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiBeamoGetServicesLogsContextError, FBeamRequestContext, Context, UApiBeamoGetServicesLogsContextRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiBeamoGetServicesLogsContextComplete, FBeamRequestContext, Context, UApiBeamoGetServicesLogsContextRequest*, Request);

using FApiBeamoGetServicesLogsContextFullResponse = FBeamFullResponse<UApiBeamoGetServicesLogsContextRequest*, UBeamoV2GetAllServiceLoggingContexts*>;
DECLARE_DELEGATE_OneParam(FOnApiBeamoGetServicesLogsContextFullResponse, FApiBeamoGetServicesLogsContextFullResponse);
