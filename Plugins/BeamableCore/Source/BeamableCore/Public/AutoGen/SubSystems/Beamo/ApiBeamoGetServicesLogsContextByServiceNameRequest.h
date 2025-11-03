
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceLoggingContext.h"

#include "ApiBeamoGetServicesLogsContextByServiceNameRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiBeamoGetServicesLogsContextByServiceNameRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Name", Category="Beam")
	FString ServiceName = {};
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Routing Key", Category="Beam")
	FOptionalString RoutingKey = {};

	// Body Params
	

	// Beam Base Request Declaration
	UApiBeamoGetServicesLogsContextByServiceNameRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ApiBeamoGetServicesLogsContextByServiceName",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_RoutingKey,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiBeamoGetServicesLogsContextByServiceNameRequest* Make(FString _ServiceName, FOptionalString _RoutingKey, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiBeamoGetServicesLogsContextByServiceNameSuccess, FBeamRequestContext, Context, UApiBeamoGetServicesLogsContextByServiceNameRequest*, Request, UBeamoV2ServiceLoggingContext*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiBeamoGetServicesLogsContextByServiceNameError, FBeamRequestContext, Context, UApiBeamoGetServicesLogsContextByServiceNameRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiBeamoGetServicesLogsContextByServiceNameComplete, FBeamRequestContext, Context, UApiBeamoGetServicesLogsContextByServiceNameRequest*, Request);

using FApiBeamoGetServicesLogsContextByServiceNameFullResponse = FBeamFullResponse<UApiBeamoGetServicesLogsContextByServiceNameRequest*, UBeamoV2ServiceLoggingContext*>;
DECLARE_DELEGATE_OneParam(FOnApiBeamoGetServicesLogsContextByServiceNameFullResponse, FApiBeamoGetServicesLogsContextByServiceNameFullResponse);
