
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnreal/AutoGen/StandaloneMicroserviceAlwaysTrueRequestArgs.h"
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceMsAlwaysTrueResponse.h"

#include "StandaloneMicroserviceMsAlwaysTrueRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREAL_API UStandaloneMicroserviceMsAlwaysTrueRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UStandaloneMicroserviceAlwaysTrueRequestArgs* Body;

	// Beam Base Request Declaration
	UStandaloneMicroserviceMsAlwaysTrueRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|StandaloneMicroserviceMs", DisplayName="Beam - Make StandaloneMicroserviceMsAlwaysTrue",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner"))
	static UStandaloneMicroserviceMsAlwaysTrueRequest* Make(FString _Text, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnStandaloneMicroserviceMsAlwaysTrueSuccess, FBeamRequestContext, Context, UStandaloneMicroserviceMsAlwaysTrueRequest*, Request, UStandaloneMicroserviceMsAlwaysTrueResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnStandaloneMicroserviceMsAlwaysTrueError, FBeamRequestContext, Context, UStandaloneMicroserviceMsAlwaysTrueRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnStandaloneMicroserviceMsAlwaysTrueComplete, FBeamRequestContext, Context, UStandaloneMicroserviceMsAlwaysTrueRequest*, Request);

using FStandaloneMicroserviceMsAlwaysTrueFullResponse = FBeamFullResponse<UStandaloneMicroserviceMsAlwaysTrueRequest*, UStandaloneMicroserviceMsAlwaysTrueResponse*>;
DECLARE_DELEGATE_OneParam(FOnStandaloneMicroserviceMsAlwaysTrueFullResponse, FStandaloneMicroserviceMsAlwaysTrueFullResponse);
