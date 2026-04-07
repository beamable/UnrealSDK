
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SetEdgegapLocationRequestArgs.h"
#include "Serialization/BeamPlainTextResponseBody.h"

#include "BeamballMsSetEdgegapLocationRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamballMsSetEdgegapLocationRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	USetEdgegapLocationRequestArgs* Body = {};

	// Beam Base Request Declaration
	UBeamballMsSetEdgegapLocationRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Make BeamballMsSetEdgegapLocation",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamballMsSetEdgegapLocationRequest* Make(float _Latitude, float _Longitude, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamballMsSetEdgegapLocationSuccess, FBeamRequestContext, Context, UBeamballMsSetEdgegapLocationRequest*, Request, UBeamPlainTextResponseBody*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamballMsSetEdgegapLocationError, FBeamRequestContext, Context, UBeamballMsSetEdgegapLocationRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamballMsSetEdgegapLocationComplete, FBeamRequestContext, Context, UBeamballMsSetEdgegapLocationRequest*, Request);

using FBeamballMsSetEdgegapLocationFullResponse = FBeamFullResponse<UBeamballMsSetEdgegapLocationRequest*, UBeamPlainTextResponseBody*>;
DECLARE_DELEGATE_OneParam(FOnBeamballMsSetEdgegapLocationFullResponse, FBeamballMsSetEdgegapLocationFullResponse);
