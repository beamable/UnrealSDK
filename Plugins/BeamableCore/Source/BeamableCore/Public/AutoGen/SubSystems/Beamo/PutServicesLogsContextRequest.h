
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceLoggingContext.h"
#include "BeamableCore/Public/AutoGen/BeamoV2EmptyMessage.h"

#include "PutServicesLogsContextRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutServicesLogsContextRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Name", Category="Beam")
	FString ServiceName = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UBeamoV2ServiceLoggingContext* Body = {};

	// Beam Base Request Declaration
	UPutServicesLogsContextRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PutServicesLogsContext",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Id,_Rules,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutServicesLogsContextRequest* Make(FString _ServiceName, FString Body_ServiceName, FString _RoutingKey, EBeamBeamoV2LogLevel _DefaultLogLevel, FOptionalString _Id, FOptionalArrayOfBeamoV2LogContextRule _Rules, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutServicesLogsContextSuccess, FBeamRequestContext, Context, UPutServicesLogsContextRequest*, Request, UBeamoV2EmptyMessage*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutServicesLogsContextError, FBeamRequestContext, Context, UPutServicesLogsContextRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutServicesLogsContextComplete, FBeamRequestContext, Context, UPutServicesLogsContextRequest*, Request);

using FPutServicesLogsContextFullResponse = FBeamFullResponse<UPutServicesLogsContextRequest*, UBeamoV2EmptyMessage*>;
DECLARE_DELEGATE_OneParam(FOnPutServicesLogsContextFullResponse, FPutServicesLogsContextFullResponse);
