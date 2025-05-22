
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CreateMatchResultRequestArgs.h"
#include "Serialization/BeamPlainTextResponseBody.h"

#include "BeamballMsCreateMatchResultRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamballMsCreateMatchResultRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCreateMatchResultRequestArgs* Body = {};

	// Beam Base Request Declaration
	UBeamballMsCreateMatchResultRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Make BeamballMsCreateMatchResult",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamballMsCreateMatchResultRequest* Make(FString _LobbyId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamballMsCreateMatchResultSuccess, FBeamRequestContext, Context, UBeamballMsCreateMatchResultRequest*, Request, UBeamPlainTextResponseBody*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamballMsCreateMatchResultError, FBeamRequestContext, Context, UBeamballMsCreateMatchResultRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamballMsCreateMatchResultComplete, FBeamRequestContext, Context, UBeamballMsCreateMatchResultRequest*, Request);

using FBeamballMsCreateMatchResultFullResponse = FBeamFullResponse<UBeamballMsCreateMatchResultRequest*, UBeamPlainTextResponseBody*>;
DECLARE_DELEGATE_OneParam(FOnBeamballMsCreateMatchResultFullResponse, FBeamballMsCreateMatchResultFullResponse);
