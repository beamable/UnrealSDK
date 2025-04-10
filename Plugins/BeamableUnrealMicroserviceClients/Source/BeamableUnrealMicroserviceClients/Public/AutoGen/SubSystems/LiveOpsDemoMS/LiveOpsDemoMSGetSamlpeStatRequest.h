
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetSamlpeStatRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSGetSamlpeStatResponse.h"

#include "LiveOpsDemoMSGetSamlpeStatRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API ULiveOpsDemoMSGetSamlpeStatRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UGetSamlpeStatRequestArgs* Body = {};

	// Beam Base Request Declaration
	ULiveOpsDemoMSGetSamlpeStatRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|2 - Backend|LiveOpsDemoMS", DisplayName="Make LiveOpsDemoMSGetSamlpeStat",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static ULiveOpsDemoMSGetSamlpeStatRequest* Make(int64 _UserID, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLiveOpsDemoMSGetSamlpeStatSuccess, FBeamRequestContext, Context, ULiveOpsDemoMSGetSamlpeStatRequest*, Request, ULiveOpsDemoMSGetSamlpeStatResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLiveOpsDemoMSGetSamlpeStatError, FBeamRequestContext, Context, ULiveOpsDemoMSGetSamlpeStatRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnLiveOpsDemoMSGetSamlpeStatComplete, FBeamRequestContext, Context, ULiveOpsDemoMSGetSamlpeStatRequest*, Request);

using FLiveOpsDemoMSGetSamlpeStatFullResponse = FBeamFullResponse<ULiveOpsDemoMSGetSamlpeStatRequest*, ULiveOpsDemoMSGetSamlpeStatResponse*>;
DECLARE_DELEGATE_OneParam(FOnLiveOpsDemoMSGetSamlpeStatFullResponse, FLiveOpsDemoMSGetSamlpeStatFullResponse);
