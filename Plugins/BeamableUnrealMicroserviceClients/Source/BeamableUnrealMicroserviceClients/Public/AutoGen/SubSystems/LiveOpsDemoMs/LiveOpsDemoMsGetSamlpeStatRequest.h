
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetSamlpeStatRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMsGetSamlpeStatResponse.h"

#include "LiveOpsDemoMsGetSamlpeStatRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API ULiveOpsDemoMsGetSamlpeStatRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UGetSamlpeStatRequestArgs* Body = {};

	// Beam Base Request Declaration
	ULiveOpsDemoMsGetSamlpeStatRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|LiveOpsDemoMs", DisplayName="Beam - Make LiveOpsDemoMsGetSamlpeStat",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static ULiveOpsDemoMsGetSamlpeStatRequest* Make(int64 _UserID, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLiveOpsDemoMsGetSamlpeStatSuccess, FBeamRequestContext, Context, ULiveOpsDemoMsGetSamlpeStatRequest*, Request, ULiveOpsDemoMsGetSamlpeStatResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLiveOpsDemoMsGetSamlpeStatError, FBeamRequestContext, Context, ULiveOpsDemoMsGetSamlpeStatRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnLiveOpsDemoMsGetSamlpeStatComplete, FBeamRequestContext, Context, ULiveOpsDemoMsGetSamlpeStatRequest*, Request);

using FLiveOpsDemoMsGetSamlpeStatFullResponse = FBeamFullResponse<ULiveOpsDemoMsGetSamlpeStatRequest*, ULiveOpsDemoMsGetSamlpeStatResponse*>;
DECLARE_DELEGATE_OneParam(FOnLiveOpsDemoMsGetSamlpeStatFullResponse, FLiveOpsDemoMsGetSamlpeStatFullResponse);
