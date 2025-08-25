
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/ProcessMatchResultRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/BeamballMsProcessMatchResultResponse.h"

#include "BeamballMsProcessMatchResultRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamballMsProcessMatchResultRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UProcessMatchResultRequestArgs* Body = {};

	// Beam Base Request Declaration
	UBeamballMsProcessMatchResultRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Make BeamballMsProcessMatchResult",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamballMsProcessMatchResultRequest* Make(FString _WinnerId, FString _LobbyId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamballMsProcessMatchResultSuccess, FBeamRequestContext, Context, UBeamballMsProcessMatchResultRequest*, Request, UBeamballMsProcessMatchResultResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamballMsProcessMatchResultError, FBeamRequestContext, Context, UBeamballMsProcessMatchResultRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamballMsProcessMatchResultComplete, FBeamRequestContext, Context, UBeamballMsProcessMatchResultRequest*, Request);

using FBeamballMsProcessMatchResultFullResponse = FBeamFullResponse<UBeamballMsProcessMatchResultRequest*, UBeamballMsProcessMatchResultResponse*>;
DECLARE_DELEGATE_OneParam(FOnBeamballMsProcessMatchResultFullResponse, FBeamballMsProcessMatchResultFullResponse);
