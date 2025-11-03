
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/BeamoV2EmptyMessage.h"

#include "DeleteServicesLogsContextRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteServicesLogsContextRequest : public UObject, public IBeamBaseRequestInterface
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
	UDeleteServicesLogsContextRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make DeleteServicesLogsContext",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_RoutingKey,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteServicesLogsContextRequest* Make(FString _ServiceName, FOptionalString _RoutingKey, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteServicesLogsContextSuccess, FBeamRequestContext, Context, UDeleteServicesLogsContextRequest*, Request, UBeamoV2EmptyMessage*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteServicesLogsContextError, FBeamRequestContext, Context, UDeleteServicesLogsContextRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteServicesLogsContextComplete, FBeamRequestContext, Context, UDeleteServicesLogsContextRequest*, Request);

using FDeleteServicesLogsContextFullResponse = FBeamFullResponse<UDeleteServicesLogsContextRequest*, UBeamoV2EmptyMessage*>;
DECLARE_DELEGATE_OneParam(FOnDeleteServicesLogsContextFullResponse, FDeleteServicesLogsContextFullResponse);
